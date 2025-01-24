#include "httplib.h"
#include "../node/node.h"
#include <iostream>

void server() {
    httplib::Server server;
    Node node("Node_one");

    server.Post("/add_peer", [&](const httplib::Request& req, httplib::Response& res) {
        std::string new_peer = req.body;  // Очікуємо адресу вузла в тілі запиту
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
            peers_list += peer + "\n";  // Додаємо кожного сусіда у список
        }
        if (!peers_list.empty()) {
            res.set_content(peers_list, "text/plain");
        } else {
            res.set_content("No peers available", "text/plain");
        }
    });

    std::cout << "Server is running on http://localhost:8080\n";
    server.listen("localhost", 8080);
}