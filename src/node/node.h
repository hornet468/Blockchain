#ifndef NODE
#define NODE

#include <string>
#include <vector>
#include "../blockchain/blockchain.h"

class Node
{
private:
    std::string id;
    std::vector<std::string> peers;
    Blockchain blockchain;
public:
    Node(const std::string& i);
    Blockchain getBlockchain() const;
    void addPeer(const std::string& peerAdress );
};



#endif