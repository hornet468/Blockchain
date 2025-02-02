#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "../block/block.h"
#include <vector>
#include <string>
#include "../transactions/transactions.h"
#include "../utils/json/json.hpp"


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
    void mineNewBlock(int difficulty);
    nlohmann::json toJson() const;
};

#endif