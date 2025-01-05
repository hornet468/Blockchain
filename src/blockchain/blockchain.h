#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "../block/block.h"
#include <vector>

class Blockchain 
{
private:
   std::vector<Block> chain;    
public:
   Blockchain() {
    createGenesisBlock();
   }
   void createGenesisBlock();
   void addBlock(const Block& newBlock);

   const std::vector<Block>& getChain() const { return chain; }
};

#endif