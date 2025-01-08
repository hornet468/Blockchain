#include "block.h"
#include "../hash/sha256.h"

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

  
    unsigned char hash[SHA256_BLOCK_SIZE];
    SHA256_CTX sha256Context;

    sha256_init(&sha256Context);
    sha256_update(&sha256Context, 
                  reinterpret_cast<const unsigned char*>(dataToHash.c_str()),
                  dataToHash.length());
    sha256_final(&sha256Context, hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        ss << std::hex << (int)hash[i];
    }
    return ss.str();
}