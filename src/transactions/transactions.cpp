#include "transactions.h"
#include "../json/single_include/nlohmann/json.hpp"
#include "../ed25519/src/ed25519.h"
#include <openssl/sha.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

Transactions::Transactions(const std::string& sn, const std::string& rv, const double am, const std::string& sig)
    : sender(sn), receiver(rv), amount(am), signature(sig){}

std::string Transactions::getSender() const {
    return sender;
}

std::string Transactions::getSignature() const {
    return signature;
}
std::string Transactions::getReceiver() const {
    return receiver;
}

double Transactions::getAmount() const {
    return amount;
}

nlohmann::json Transactions::toJson() const {
    return {
        {"sender", sender},
        {"receiver", receiver},
        {"amount", amount}
    };
}

std::string Transactions::hashTransactions(const Transactions &transaction) {
    nlohmann::json jsonData = transaction.toJson();
    std::string jsonString = jsonData.dump();

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(jsonString.c_str()), jsonString.size(), hash);

    std::ostringstream oss;
    for (unsigned char byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return oss.str();
}

std::string Transactions::toHexString(const unsigned char* data, size_t length) {
    std::stringstream ss;
    for (size_t i = 0; i < length; ++i) {
        ss << std::setw(2) << std::setfill('0') << std::hex << (int)data[i];
    }
    return ss.str();
}

void Transactions::signTransaction(unsigned char* private_key, unsigned char* public_key) {
    std::string jsonData = toJson().dump();
    unsigned char signature[64];
    ed25519_sign(signature, reinterpret_cast<const unsigned char*>(jsonData.c_str()), 
                 jsonData.size(), public_key, private_key);
    this->signature = toHexString(signature, sizeof(signature));
}

void Transactions::verifySignature(const std::string& signature, const std::string& message, unsigned char* public_key) {
    unsigned char signature_bytes[64];
    
    for (size_t i = 0; i < signature.size() / 2; i++) {
        sscanf(signature.c_str() + 2*i, "%2hhx", &signature_bytes[i]);
    }

    bool valid = ed25519_verify(signature_bytes, reinterpret_cast<const unsigned char*>(message.c_str()), 
                                 message.size(), public_key);

    if (valid) {
        std::cout << "Valid signature\n";
    } else {
        std::cout << "Invalid signature\n";
    }
}