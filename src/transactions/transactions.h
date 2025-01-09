#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>

class Transactions {
private:
    std::string sender;
    std::string receiver;
    double amount;

public:
    Transactions(const std::string& sn, const std::string& rv, const double am);

    std::string getSender() const;
    std::string getReceiver() const;
    double getAmount() const;
};

#endif
 