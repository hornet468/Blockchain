#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include "../utils/json/json.hpp"

class Transactions {
private:
    std::string sender;
    std::string receiver;
    std::string signature;
    std::string publicKey;
    std::string privateKey;
    double amount;

public:
    Transactions(const std::string& sender, const std::string& receiver, const double amount);

    std::string getSender() const;
    std::string getReceiver() const;
    double getAmount() const;
    void generateKeyPair(); 
    void signTransaction(); 
    bool verifySignature() const; 
       nlohmann::json to_json() const;
};

#endif
 