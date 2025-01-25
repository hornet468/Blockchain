#include "transactions.h"
#include "sodium.h"
#include <stdexcept>

Transactions::Transactions(const std::string& sn, const std::string& rv, const double am)
    : sender(sn), receiver(rv), amount(am) {
    signature = "";
    publicKey = "";
}

std::string Transactions::getSender() const {
    return sender;
}

std::string Transactions::getReceiver() const {
    return receiver;
}

double Transactions::getAmount() const {
    return amount;
} 

void Transactions::generateKeyPair() {
    unsigned char pk[crypto_sign_PUBLICKEYBYTES];
    unsigned char sk[crypto_sign_SECRETKEYBYTES];

    if (crypto_sign_keypair(pk, sk) != 0) {
        throw std::runtime_error("Failed generate key pair");
    }

    publicKey.assign(reinterpret_cast<char*>(pk), crypto_sign_PUBLICKEYBYTES);
    privateKey.assign(reinterpret_cast<char*>(sk), crypto_sign_SECRETKEYBYTES);
}


void Transactions::signTransaction() {
    if (privateKey.empty()) {
        throw std::runtime_error("Failed generate private key");
    }

    std::string txData = sender + receiver + std::to_string(amount);
    unsigned char signedMessage[crypto_sign_BYTES + txData.size()];
    unsigned long long signedMessageLen;

    crypto_sign(signedMessage, &signedMessageLen,
                reinterpret_cast<const unsigned char*>(txData.c_str()), txData.size(),
                reinterpret_cast<const unsigned char*>(privateKey.c_str()));

    signature.assign(reinterpret_cast<char*>(signedMessage), signedMessageLen);
}

bool Transactions::verifySignature() const {
    if (publicKey.empty() || signature.empty()) {
        throw std::runtime_error("No public key or signature to verify!");
    }

    std::string txData = sender + receiver + std::to_string(amount);
    unsigned char unsignedMessage[signature.size()];
    unsigned long long unsignedMessageLen;

    int result = crypto_sign_open(unsignedMessage, &unsignedMessageLen,
                                  reinterpret_cast<const unsigned char*>(signature.c_str()), signature.size(),
                                  reinterpret_cast<const unsigned char*>(publicKey.c_str()));

    return result == 0; 
}


nlohmann::json Transactions::to_json() const {
    nlohmann::json j;
    j["sender"] = sender;
    j["receiver"] = receiver;
    j["amount"] = amount;
    j["signature"] = signature;  // Підпис
    j["publicKey"] = publicKey;  // Публічний ключ

    return j;
}