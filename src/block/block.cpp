#include "block.h"
#include "../hash/sha256.h"

#include <sstream>
#include <string>


Block::Block(int indx, const std::string& ts,const std::string& dt,
     const std::string& ph,const std::string& ch) : index(indx),
     timestamp(ts), data(dt), previousHash(ph) {
        currentHash = calculateHash();
     }
     
     int Block::getIndex() const {
        return index;
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
        std::string dataToHash = std::to_string(index) + data +
        timestamp + previousHash;

        unsigned char hash[SHA256_BLOCK_SIZE];
        SHA256_CTX sha256Context;

        sha256_init(&sha256Context);

        sha256_update(&sha256Context, 
        reinterpret_cast<const unsigned char*>(dataToHash.c_str()),
        dataToHash.length());

        sha256_final(&sha256Context, hash);

        std::stringstream ss;
        for(int i = 0; i < SHA256_BLOCK_SIZE; i++) {
            ss << std::hex << (int)hash[i];
        }
        return ss.str();
    }