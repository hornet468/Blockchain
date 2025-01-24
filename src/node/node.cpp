#include "node.h"

Node:: Node(const std::string& i) : id(i){};

Blockchain Node::getBlockchain() const {
    return blockchain;
}

void Node::addPeer(const std::string& peerAdress ) {
    peers.push_back(peerAdress);
}

std::vector<std::string> Node::getPeers() const {
    return peers;
}