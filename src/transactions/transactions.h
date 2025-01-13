#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include "../json/single_include/nlohmann/json.hpp"


class Transactions {
private:
    std::string sender;
    std::string receiver;
    std::string signature;
    double amount;

public:
    Transactions(const std::string& sn, const std::string& rv, const double am, const std::string& sig);

    std::string getSender() const;
    std::string getReceiver() const;
    std::string setSignature(const std::string& sig);
    std::string getSignature() const;
    double getAmount() const;
    nlohmann::json toJson() const;
    std::string hashTransactions(const Transactions& transaction);
    void signTransaction(unsigned char* private_key, unsigned char* public_key);
    std::string toHexString(const unsigned char* data, size_t length);
    void verifySignature(const std::string& signature,const std::string& message, unsigned char* public_key);
};

#endif
 