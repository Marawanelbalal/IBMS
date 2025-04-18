#include "transaction.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Transaction::Transaction(const std::string& id, double amt, const std::string& type, 
                         const std::vector<std::string>& accounts)
    : transactionID(id), amount(amt), transactionType(type), 
      involvedAccountNumbers(accounts), isValid(false) {
    
    // Set timestamp to current time
    timestamp = std::time(nullptr);
    
    // Generate a default description
    std::stringstream ss;
    ss << type << " transaction of " << std::fixed << std::setprecision(2) << amount;
    if (accounts.size() > 1) {
        ss << " between accounts";
    } else if (accounts.size() == 1) {
        ss << " for account " << accounts[0];
    }
    description = ss.str();
}

bool Transaction::execute() {
    // Base class implementation - derived classes will override
    // Only execute if the transaction is valid
    return isValid;
}

bool Transaction::validateTransaction() {
    // Base class implementation - derived classes will override
    // Simple validation (amount > 0)
    isValid = (amount > 0);
    return isValid;
}

// Getters
double Transaction::getAmount() const {
    return amount;
}

std::time_t Transaction::getTimestamp() const {
    return timestamp;
}

std::string Transaction::getTransactionType() const {
    return transactionType;
}

std::string Transaction::getTransactionID() const {
    return transactionID;
}

std::vector<std::string> Transaction::getInvolvedAccounts() const {
    return involvedAccountNumbers;
}

bool Transaction::getIsValid() const {
    return isValid;
}

std::string Transaction::getDescription() const {
    return description;
}

// Setters
void Transaction::setDescription(const std::string& desc) {
    description = desc;
}

void Transaction::setIsValid(bool valid) {
    isValid = valid;
}