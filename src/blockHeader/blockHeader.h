#ifndef BLOCK_HEADER
#define BLOCK_HEADER

#include <string>

class BlockHeader
{
protected:
    int index;
    std::string timestamp;
    std::string data;
    std::string previousHash;
    std::string currentHash;
    int nonce = 0;

     std::string calculateHash(const std::string& dataToHash) const;
public:
    BlockHeader(int index, const std::string& timestamp, const std::string& data,
          const std::string& previousHash, const std::string& currentHash);
    int getIndex() const;
    std::string getData() const;
    std::string getPreviousHash() const;
    std::string getCurrentHash() const;
    std::string getTimeStamp() const;
};



#endif