#include <block.h>

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
    