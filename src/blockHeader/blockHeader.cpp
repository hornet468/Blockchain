#include "blockHeader.h"
#include <openssl/sha.h>
#include <sstream>
#include <string>
#include <iostream>

BlockHeader::BlockHeader(int indx, const std::string& ts, const std::string& dt,
             const std::string& ph, const std::string& ch ): 
             index(indx), timestamp(ts), data(dt), previousHash(ph){
                currentHash = calculateHash(std::to_string(indx)+ ts +
                dt + ph);
             };


int BlockHeader::getIndex() const {
    return index;
}

std::string BlockHeader::getData() const {
    return data;
}

std::string BlockHeader::getPreviousHash() const {
    return previousHash;
}

std::string BlockHeader::getCurrentHash() const {
    return currentHash;
}

std::string BlockHeader::getTimeStamp() const {
    return timestamp;
}

std::string BlockHeader::calculateHash(const std::string& dataToHash) const {
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