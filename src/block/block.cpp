#include "block.h"
#include <openssl/sha.h>
#include <sstream>
#include <string>
#include <iostream>

Block::Block(int index, const std::string& timestamp, const std::vector<Transactions>& tsx, 
             const std::string& previousHash)
    : BlockHeader(index, timestamp, "", previousHash, ""), transactions(tsx) {
    merkleRoot = calculateMerkleRoot(); 
    currentHash = calculateHash(std::to_string(index) + timestamp + previousHash + merkleRoot);

    for (const auto& tx : transactions) {
        if (!tx.verifySignature()) {
            throw std::runtime_error("Invalid block transaction!");
        }
    }
}

void Block::mineBlock(int difficulty) {
    std::string str(difficulty, '0'); 

    while (currentHash.substr(0, difficulty) != str) {
        nonce++; 
        std::string dataToHash = std::to_string(index) + timestamp + previousHash + merkleRoot + std::to_string(nonce);
        currentHash = calculateHash(dataToHash);

        std::cout << "Attempting hash: " << currentHash << std::endl;
    }

    std::cout << "Block is mined: " << currentHash << "\n";
}

std::string Block::calculateMerkleRoot() {
    std::vector<std::string> hashes;

    for (const auto& tx : transactions) {
        std::string txData = tx.getSender() + tx.getReceiver() + std::to_string(tx.getAmount());
        hashes.push_back(calculateHash(txData));
    }

    while (hashes.size() > 1) {
        std::vector<std::string> newHashes;
        for (size_t i = 0; i < hashes.size(); i += 2) {
            if (i + 1 < hashes.size()) {
                newHashes.push_back(calculateHash(hashes[i] + hashes[i + 1]));
            } else {
                newHashes.push_back(hashes[i]);
            }
        }
        hashes = newHashes;
    }

    return hashes.empty() ? "" : hashes[0];
}