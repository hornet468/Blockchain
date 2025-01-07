#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "../block/block.h"
#include <vector>
#include "../transactions/transactions.h"

class Blockchain {
private:
    std::vector<Block> chain;                
    std::vector<Transactions> currentTransactions; 

public:
    Blockchain();  

    void createGenesisBlock(); 
    void addBlock(const Block& newBlock);  
    void addTransactions(const Transactions& tx);  
    void createNewBlock();  

    Block getLastBlock() const;
    std::string getCurrentTimestamp() const; 
    const std::vector<Block>& getChain() const; 
    const std::vector<Transactions>& getTransactions() const;
};

#endif