#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include "../transactions/transactions.h"

class  Block
{
private:
   int index;
   int nonce;
   std::string timestamp;
   std::string data;
   std::string previousHash;
   std::string currentHash;
   std::string merkleRoot;
public:
     Block(int indx, const std::string& ts,const std::string& dt,
     const std::string& ph,const std::string& ch, 
     std::vector<Transactions> tsx);
     int getIndex() const;
     void mineBlock(int difficulty) ;
     std::string getTimeStamp() const;
     std::string getData() const;
     std::string getPreviousHash() const;
     std::string getCurrentHash() const;
     std::string calculateHash(const std::string& dataToHash) const;
     std::string calculateMerkleRoot();
     std::vector<Transactions> transactions;
};

#endif
