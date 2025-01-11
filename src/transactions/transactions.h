#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>

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
};

#endif
 