#include "blockchain.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iostream>
#include <stdexcept>

Blockchain::Blockchain() {
    createGenesisBlock();
}

void Blockchain::createGenesisBlock() {
    Block genesisBlock(0, getCurrentTimestamp(), {}, "0"); 
    chain.push_back(genesisBlock);
}

void Blockchain::addBlock(const Block& newBlock) {
    chain.push_back(newBlock);
}

void Blockchain::addTransactions(const Transactions& tx) {
    Transactions signedTx = tx;
    signedTx.generateKeyPair(); 
    signedTx.signTransaction(); 
    currentTransactions.push_back(signedTx);
}

void Blockchain::createNewBlock() {
    if (!currentTransactions.empty()) {
        for (const auto& tx : currentTransactions) {
            if (!tx.verifySignature()) {
                throw std::runtime_error("Invalid transaction in pool!");
            }
        }

        Block newBlock(chain.size(), 
                       getCurrentTimestamp(), 
                       currentTransactions, 
                       getLastBlock().getCurrentHash());

        addBlock(newBlock);
        currentTransactions.clear();  
    }
}

Block Blockchain::getLastBlock() const {
    if (chain.empty()) {
        throw std::runtime_error("Blockchain is empty, cannot get the last block");
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
        for (const auto& tx : currentTransactions) {
            if (!tx.verifySignature()) {
                throw std::runtime_error("Invalid transaction in pool!");
            }
        }

        Block newBlock(chain.size(), 
                       getCurrentTimestamp(), 
                       currentTransactions, 
                       getLastBlock().getCurrentHash());

       
        newBlock.mineBlock(difficulty);

        
        addBlock(newBlock);
        currentTransactions.clear(); 
    }
}

nlohmann::json Blockchain::toJson() const {
    nlohmann::json j;
    j["chain"] = nlohmann::json::array();
    for (const auto& block : chain) {
        j["chain"].push_back(block.to_json());  
    }
    return j;
}
