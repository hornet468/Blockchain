#include <iostream>
#include "blockchain/blockchain.h"
#include "transactions/transactions.h"
#include "server/server.h"

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

    // Create new Transactions
    Transactions tx1("Alice", "Bob", 100);
    Transactions tx2("Bob", "Charlie", 50);
    
    // Signature transactions
    tx1.generateKeyPair();
    tx1.signTransaction();
    std::cout << "Transaction 1 signature valid: " << (tx1.verifySignature() ? "Yes" : "No") << std::endl;

    tx2.generateKeyPair();
    tx2.signTransaction();
    std::cout << "Transaction 2 signature valid: " << (tx2.verifySignature() ? "Yes" : "No") << std::endl;

    // Adding transactions in pool
    blockchain.addTransactions(tx1);
    blockchain.addTransactions(tx2);

    // ining new block with difficulty 2
    std::cout << "\nMining new block with difficulty 2..." << std::endl;
    blockchain.mineNewBlock(2);

    // Checking chain after add new block
    std::cout << "\nBlockchain after mining and adding a new block:" << std::endl;
    for (const Block& block : blockchain.getChain()) {
        std::cout << "Index: " << block.getIndex() 
                  << ", Hash: " << block.getCurrentHash() 
                  << ", Previous Hash: " << block.getPreviousHash() 
                  << ", Timestamp: " << block.getTimeStamp() << std::endl;
    }

     server();

    return 0;
}