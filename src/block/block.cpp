#include "block.h"
#include <openssl/sha.h>
#include <sstream>
#include <string>
#include <iostream>

Block::Block(int indx, const std::string& ts, const std::string& dt,
             const std::string& ph, const std::string& ch, std::vector<Transactions> tsx)
    : index(indx), timestamp(ts), data(dt), previousHash(ph), transactions(tsx) {
    currentHash = calculateHash();
}

int Block::getIndex() const {
    return index;
}

void Block::mineBlock(int difficulty) {
    std::string str(difficulty, '0'); 

    while(currentHash.substr(0, difficulty) != str) {
    nonce++;
    currentHash = calculateHash();
    std::cout << "Attempting hash: " << currentHash << std::endl;  // Debug output
}

    std::cout << "Block is mined: " << currentHash << "\n";
}

std::string Block::getData() const {
    return data;
}

std::string Block::getPreviousHash() const {
    return previousHash;
}

std::string Block::getCurrentHash() const {
    return currentHash;
}

std::string Block::getTimeStamp() const {
    return timestamp;
}

std::string Block::calculateHash() const {
    std::string txData;
    for (const auto& tx : transactions) {
        txData += tx.getSender() + tx.getReceiver() + std::to_string(tx.getAmount());
    }

    std::string dataToHash = std::to_string(index) + data +
                             timestamp + previousHash + txData + std::to_string(nonce);

  
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256Context;

    SHA256_Init(&sha256Context);
    SHA256_Update(&sha256Context, 
                  reinterpret_cast<const unsigned char*>(dataToHash.c_str()),
                  dataToHash.length());
    SHA256_Final(hash, &sha256Context);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << (int)hash[i];
    }
    return ss.str();
}
