#ifndef BLOCK_H
#define BLOCK_H

#include <string>

class  Block
{
private:
   int index;
   std::string timestamp;
   std::string data;
   std::string previousHash;
   std::string currentHash;
public:
     Block(int indx, const std::string& ts,const std::string& dt,
     const std::string& ph,const std::string& ch) : index(indx),
     timestamp(ts), data(dt), previousHash(ph), currentHash(ch) {};
     int getIndex() const;
     std::string getTimeStamp() const;
     std::string getData() const;
     std::string getPreviousHash() const;
     std::string getCurrentHash() const;
     std::string calculateHash() const;
};

#endif