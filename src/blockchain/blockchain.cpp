#include "blockchain.h"


void Blockchain::createGenesisBlock() {
    Block genesisBlock(0, "2025-01-05", "Genesis Block", "0", ""); 
    chain.push_back(genesisBlock);
}
void Blockchain::addBlock(const Block& newBlock) {
    chain.push_back(newBlock);
}
