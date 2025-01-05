#include <iostream>
#include "blockchain/blockchain.h"

int main() {
    Blockchain myBlockchain;

    myBlockchain.addBlock(Block(1, "2025-01-06", "Block 1", myBlockchain.getChain().back().getCurrentHash(), ""));
    myBlockchain.addBlock(Block(2, "2025-01-07", "Block 2", myBlockchain.getChain().back().getCurrentHash(), ""));

    for (const auto& block : myBlockchain.getChain()) {
        std::cout << "Block #" << block.getIndex() << " ["
                  << block.getTimeStamp() << "] : "
                  << block.getData() << ", Hash: "
                  << block.getCurrentHash() << std::endl;
    }
}