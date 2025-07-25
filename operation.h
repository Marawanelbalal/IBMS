#pragma once
#include <string>
#include <ctime>
#include <vector>
#include "User.h"
#include "transaction.h"
#include "Account.h"
class Bank;
// Base Operation class
class Operation {
protected:
    Bank* IBMS;
    std::string message;
    Customer* currentCustomer = nullptr;
    Account* acc = nullptr;
    float amount;
    std::string operationID;
    std::string operationType;
    std::time_t timestamp;
    bool successful = false;
    std::string statusMessage;

public:
    Operation();
    Operation(const std::string& type, float amt = 0, const std::string& id = "");
    virtual ~Operation();

    virtual bool execute() = 0; // Pure virtual function
    virtual bool validate() = 0; // Pure virtual function

    std::string getOperationType() const;
    std::string getOperationID() const;
    std::time_t getTimestamp() const;
    bool getStatus() const;
    std::string getStatusMessage() const;
    void logOperation() const;
    bool accBelongsToCustomer();
    void loadParameters(Customer* c, Account* a = nullptr, float amt = 0);
    std::string getMessage();
};

// Derived classes
class LoginOperation : public Operation {
private:
    std::string username;
    std::string password;
    Customer user;
    int failedAttempts = 0;

public:
    LoginOperation(const std::string& uname, const std::string& pwd, Bank* IBMS);
    bool execute() override;
    bool validate() override;
    bool validateCredentials();
    bool createUserSession();
    void handleFailedLogin();
    Customer getLoggedInUser() const;
};

class TransferOperation : public Operation {
    std::string sourceAccountNumber;
    std::string destinationAccountNumber;
    std::string currency;
    Transaction* transaction = nullptr;
    Account* sourceAccount = nullptr;
    Account* destAccount = nullptr;
    Customer* currentCustomer = nullptr;
public:
    TransferOperation(Customer* currentCustomer, const std::string& source, const std::string& destination, float amt, Bank* IBMS);
    ~TransferOperation();

    bool execute() override;
    bool validate() override;
    bool collectTransferInfo();
    bool validateTransfer();
    bool executeTransfer();
    bool createTransactionRecord();
    Transaction* getTransaction() const;
};

class TransactionHistoryOperation : public Operation {
private:
    std::string accountNumber;
    std::time_t startDate;
    std::time_t endDate;
    std::string transactionType;
    std::vector<Transaction*> transactions;
    Customer* currentCustomer = nullptr;
    Account* account = nullptr;

public:
    TransactionHistoryOperation(Customer* currentCustomer,const std::string& account, Bank* IBMS);
    ~TransactionHistoryOperation();

    bool execute() override;
    bool validate() override;
    bool collectFilterCriteria();
    bool retrieveTransactions();
    void formatTransactionList();
    std::vector<Transaction*> getTransactions() const;
    void setDateRange(std::time_t start, std::time_t end);
    void setTransactionType(const std::string& type);
    std::string viewTransactionHistory();
};

class Deposit : public Operation {
public:
    bool execute() override;
    bool validate() override;
};

class Withdraw : public Operation {
public:
    bool execute() override;
    bool validate() override;
};

class BalanceInquiry : public Operation {
public:
    bool execute() override;
    bool validate() override;
};

class TransactionOperation : public Operation {
public:
    bool execute() override;
    bool validate() override;
    bool processTransaction();
};