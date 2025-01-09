#include <iostream>
#include "blockchain/blockchain.h"
#include "transactions/transactions.h"


int main() {
    // Creating blockchain
    Blockchain blockchain;

    // Testing genesis block
    std::cout << "Genesis Block:" << std::endl;
    const Block& genesisBlock = blockchain.getChain().front();
    std::cout << "Index: " << genesisBlock.getIndex() << std::endl;
    std::cout << "Timestamp: " << genesisBlock.getTimeStamp() << std::endl;
    std::cout << "Data: " << genesisBlock.getData() << std::endl;
    std::cout << "Previous Hash: " << genesisBlock.getPreviousHash() << std::endl;
    std::cout << "Hash: " << genesisBlock.getCurrentHash() << std::endl;

    // Creating new transactions
    Transactions tx1("Alice", "Bob", 100);
    Transactions tx2("Bob", "Charlie", 50);
    
    blockchain.addTransactions(tx1);
    blockchain.addTransactions(tx2);

    // Maining new block with difficulty level of 4 (meaning the block hash must start with four 0s)
    std::cout << "\nMining new block with difficulty 4..." << std::endl;
    blockchain.mineNewBlock(4);

    // Checking the chain after adding a block
    std::cout << "\nBlockchain after mining and adding a new block:" << std::endl;
    for (const Block& block : blockchain.getChain()) {
        std::cout << "Index: " << block.getIndex() << ", Hash: " << block.getCurrentHash() << std::endl;
    }

    return 0;
}