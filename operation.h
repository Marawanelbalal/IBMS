#pragma once 
#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <ctime>
#include "User.h"
#include "transaction.h"
#include "Account.h"
// #include "Account.h" // Assuming this exists based on project description

// Base Operation class
class Operation {
protected:
    std::string operationID;
    std::string operationType;
    std::time_t timestamp;
    bool successful;
    std::string statusMessage;

public:
    // Constructor
    Operation(const std::string& id, const std::string& type);
    
    // Virtual destructor
    virtual ~Operation();
    
    // Core operation methods
    virtual bool execute() = 0; // Pure virtual function
    virtual bool validate() = 0; // Pure virtual function
    
    // Getters
    std::string getOperationType() const;
    std::string getOperationID() const;
    std::time_t getTimestamp() const;
    bool getStatus() const;
    std::string getStatusMessage() const;
    
    // Logging
    void logOperation() const;
};

// LoginOperation class
class LoginOperation : public Operation {
private:
    std::string username;
    std::string password;
    User* user; // Pointer to user if login is successful
    int failedAttempts;

public:
    // Constructor
    LoginOperation(const std::string& id, const std::string& username, const std::string& password);
    
    // Core methods
    bool execute() override;
    bool validate() override;
    
    // Specific methods
    bool validateCredentials();
    bool createUserSession();
    void handleFailedLogin();
    
    // Getter
    User* getLoggedInUser() const;
};

// TransferOperation class
class TransferOperation : public Operation {
private:
    std::string sourceAccountNumber;
    std::string destinationAccountNumber;
    double amount;
    std::string currency;
    Transaction* transaction; // The transaction object created for this transfer

public:
    // Constructor
    TransferOperation(const std::string& id, const std::string& source, 
                     const std::string& destination, double amt, const std::string& curr = "USD");
    
    // Destructor to clean up transaction pointer
    ~TransferOperation();
    
    // Core methods
    bool execute() override;
    bool validate() override;
    
    // Specific methods
    bool collectTransferInfo();
    bool validateTransfer();
    bool executeTransfer();
    bool createTransactionRecord();
    
    // Getter for the transaction
    Transaction* getTransaction() const;
};

// TransactionHistoryOperation class
class TransactionHistoryOperation : public Operation {
private:
    std::string accountNumber;
    std::time_t startDate;
    std::time_t endDate;
    std::string transactionType; // Filter by type (optional)
    std::vector<Transaction*> transactions; // List of transactions found

public:
    // Constructor
    TransactionHistoryOperation(const std::string& id, const std::string& account, 
                              std::time_t start = 0, std::time_t end = std::time(nullptr));
    
    // Core methods
    bool execute() override;
    bool validate() override;
    
    // Specific methods
    bool collectFilterCriteria();
    bool retrieveTransactions();
    void formatTransactionList() const;
    
    // Getters
    std::vector<Transaction*> getTransactions() const;
    void setDateRange(std::time_t start, std::time_t end);
    void setTransactionType(const std::string& type);
};

#endif // OPERATION_H