#include "httplib.h"
#include "../node/node.h"
#include <iostream>
#include "../utils/json/json.hpp"

void server() {
    httplib::Server server;
    Node node("Node_one");

    server.Post("/add_peer", [&](const httplib::Request& req, httplib::Response& res) {
        std::string new_peer = req.body;  
        if (!new_peer.empty()) {
            node.addPeer(new_peer);
            res.set_content("Peer added: " + new_peer, "text/plain");
        } else {
            res.status = 400; 
            res.set_content("Invalid peer address", "text/plain");
        }
    });

    //
    server.Get("/get_peers", [&](const httplib::Request&, httplib::Response& res) {
        std::string peers_list;
        for (const auto& peer : node.getPeers()) {
            peers_list += peer + "\n";  
        }
        if (!peers_list.empty()) {
            res.set_content(peers_list, "text/plain");
        } else {
            res.set_content("No peers available", "text/plain");
        }
    });

   

   server.Post("/add_block", [&](const httplib::Request& req, httplib::Response& res) {
    std::string new_block_data = req.body;
    if (!new_block_data.empty()) {
        Block newBlock(node.getBlockchain().getChain().size(), node.getBlockchain().getCurrentTimestamp(), {}, node.getBlockchain().getLastBlock().getCurrentHash());
        node.getBlockchain().addBlock(newBlock);
        res.set_content("Block added", "text/plain");
    } else {
        res.set_content("No block available", "text/plain");
    }
});

server.Get("getBlockchain", [&](const httplib::Request& req, httplib::Response& res){
    Blockchain Blockchain = node.getBlockchain();
    nlohmann::json blockchainJson = Blockchain.toJson();

    res.set_content(blockchainJson.dump(), "application/json"); 
});

 std::cout << "Server is running on http://localhost:8080\n";
    server.listen("localhost", 8080);
}
