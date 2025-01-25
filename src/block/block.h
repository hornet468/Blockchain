#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <stdexcept>
#include "../transactions/transactions.h"
#include "../utils/json/json.hpp"
#include "../blockHeader/blockHeader.h"

class Block : public BlockHeader{
private:                 
    std::vector<Transactions> transactions;  
    std::string merkleRoot;
    std::string calculateMerkleRoot();       
public:
    Block(int index, const std::string& timestamp, const std::vector<Transactions>& tsx,
     const std::string& previousHash);
    void mineBlock(int difficulty);  
    nlohmann::json to_json() const;            
};

#endif