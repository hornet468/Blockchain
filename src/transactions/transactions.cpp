#include "transactions.h"

Transactions::Transactions(const std::string& sn, const std::string& rv, const double am)
    : sender(sn), receiver(rv), amount(am) {}

std::string Transactions::getSender() const {
    return sender;
}

std::string Transactions::getReceiver() const {
    return receiver;
}

double Transactions::getAmount() const {
    return amount;
} 
