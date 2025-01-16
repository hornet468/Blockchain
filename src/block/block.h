#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include "../transactions/transactions.h"

class Block {
private:
    int index;
    std::string timestamp;
    std::string data;
    std::string previousHash;
    std::string currentHash;
    std::string merkleRoot;
    int nonce = 0;

    std::vector<Transactions> transactions;

    std::string calculateHash(const std::string& dataToHash) const;
    std::string calculateMerkleRoot();

public:
    Block(int index, const std::string& timestamp, const std::string& data,
          const std::string& previousHash, const std::string& currentHash,
          std::vector<Transactions> transactions);

    int getIndex() const;
    std::string getData() const;
    std::string getPreviousHash() const;
    std::string getCurrentHash() const;
    std::string getTimeStamp() const;

    void mineBlock(int difficulty);
};

#endif