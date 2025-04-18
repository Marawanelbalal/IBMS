#pragma once

#include <string>
#include <vector>
#include <ctime>
// #include "Account.h" // Include the Account header

class Transaction {
private:
    std::string transactionID;
    double amount;
    std::time_t timestamp;
    std::string transactionType; // deposit, withdrawal, transfer, etc.
    std::vector<std::string> involvedAccountNumbers; // Account numbers involved
    bool isValid;
    std::string description;

public:
    // Constructor
    Transaction(const std::string& id, double amt, const std::string& type,
        const std::vector<std::string>& accounts);

    // Execute the transaction
    virtual bool execute();

    // Validate if the transaction can be performed
    virtual bool validateTransaction();

    // Getters
    double getAmount() const;
    std::time_t getTimestamp() const;
    std::string getTransactionType() const;
    std::string getTransactionID() const;
    std::vector<std::string> getInvolvedAccounts() const;
    bool getIsValid() const;
    std::string getDescription() const;

    // Setters
    void setDescription(const std::string& desc);
    void setIsValid(bool valid);
};
