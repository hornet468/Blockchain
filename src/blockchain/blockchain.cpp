#include "blockchain.h"
#include <ctime>
#include <iostream>
#include <stdexcept>

Blockchain::Blockchain() {
    createGenesisBlock();
}


void Blockchain::createGenesisBlock() {
    Block genesisBlock(0, "2025-01-05", "Genesis Block", "0", "", {}); 
    chain.push_back(genesisBlock); 
}

void Blockchain::addBlock(const Block& newBlock) {
    chain.push_back(newBlock);
}

void Blockchain::addTransactions(const Transactions& tx) {
    currentTransactions.push_back(tx);
}

void Blockchain::createNewBlock() {
    if (!currentTransactions.empty()) {
        Block newBlock(chain.size(), 
        getCurrentTimestamp(), "New Block Data", 
        getLastBlock().getCurrentHash(), "", currentTransactions);
        
        addBlock(newBlock);
        currentTransactions.clear();
    }
}

Block Blockchain::getLastBlock() const {
    if (chain.empty()) {
        throw 
        std::runtime_error("Blockchain is empty, cannot get the last block");
}
    return chain.back();
}

std::string Blockchain::getCurrentTimestamp() const {
    std::time_t now = std::time(0);  
    char buffer[80];
    struct tm* timeinfo = std::localtime(&now);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

const std::vector<Block>& Blockchain::getChain() const {
    return chain;
}

const std::vector<Transactions>& Blockchain::getTransactions() const {
    return currentTransactions;
}

void Blockchain::mineNewBlock(int difficulty) {
      if (!currentTransactions.empty()) {
        Block newBlock(chain.size(), 
        getCurrentTimestamp(), "New Block Data", 
        getLastBlock().getCurrentHash(), "", currentTransactions);

        newBlock.mineBlock(difficulty);
        addBlock(newBlock);
        currentTransactions.clear();
       }
}


