#include "blockchain.h"

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
    return chain.back();
}

std::string Blockchain::getCurrentTimestamp() const {
    return "2025-01-07"; 
}

const std::vector<Block>& Blockchain::getChain() const {
    return chain;
}

const std::vector<Transactions>& Blockchain::getTransactions() const {
    return currentTransactions;
}