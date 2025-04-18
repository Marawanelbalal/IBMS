#include "operation.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

// Base Operation implementation
Operation::Operation(const std::string& id, const std::string& type)
    : operationID(id), operationType(type), successful(false) {
    timestamp = std::time(nullptr);
}

Operation::~Operation() {
    // Virtual destructor implementation
}

std::string Operation::getOperationType() const {
    return operationType;
}

std::string Operation::getOperationID() const {
    return operationID;
}

std::time_t Operation::getTimestamp() const {
    return timestamp;
}

bool Operation::getStatus() const {
    return successful;
}

std::string Operation::getStatusMessage() const {
    return statusMessage;
}

void Operation::logOperation() const {
    // In a real implementation, this would write to a log file or database
    std::cout << "Operation log: " << operationID << " | " << operationType 
              << " | Status: " << (successful ? "Success" : "Failed")
              << " | Message: " << statusMessage << std::endl;
}

// LoginOperation implementation
LoginOperation::LoginOperation(const std::string& id, const std::string& uname, const std::string& pwd)
    : Operation(id, "Login"), username(uname), password(pwd), user(nullptr), failedAttempts(0) {
}

bool LoginOperation::execute() {
    if (!validate()) {
        handleFailedLogin();
        return false;
    }
    
    if (validateCredentials()) {
        successful = createUserSession();
        if (successful) {
            statusMessage = "Login successful for user: " + username;
        } else {
            statusMessage = "Failed to create session for user: " + username;
            handleFailedLogin();
        }
    } else {
        statusMessage = "Invalid credentials for user: " + username;
        handleFailedLogin();
    }
    
    logOperation();
    return successful;
}

bool LoginOperation::validate() {
    // Simple validation - check if username and password are not empty
    if (username.empty() || password.empty()) {
        statusMessage = "Username or password cannot be empty";
        return false;
    }
    return true;
}

bool LoginOperation::validateCredentials() {
    // In a real system, this would check against a database
    // For this example, we'll simulate finding the user and checking password
    
    // Simulated user repository check
    // This is where you would interact with your user database
    
    // For demonstration purposes only (replace with actual implementation)
    if (username == "admin" && password == "admin123") {
        user = new Administrator("A001", "Admin User", password);
        return true;
    } else if (username == "customer" && password == "customer123") {
        user = new Customer("NAME","C001", password);
        return true;
    }
    
    return false;
}

bool LoginOperation::createUserSession() {
    // In a real system, this would create a session token or similar
    if (user != nullptr) {
        return true; // Session created successfully
    }
    return false;
}

void LoginOperation::handleFailedLogin() {
    failedAttempts++;
    // In a real system, you might lock the account after multiple failed attempts
    if (failedAttempts >= 3) {
        statusMessage += " (Account temporarily locked due to multiple failed attempts)";
    }
}

User* LoginOperation::getLoggedInUser() const {
    return user;
}

// TransferOperation implementation
TransferOperation::TransferOperation(const std::string& id, const std::string& source, 
                                   const std::string& destination, double amt, const std::string& curr)
    : Operation(id, "Transfer"), sourceAccountNumber(source), 
      destinationAccountNumber(destination), amount(amt), currency(curr), transaction(nullptr) {
}

TransferOperation::~TransferOperation() {
    // Clean up the transaction pointer if needed
    delete transaction;
}

bool TransferOperation::execute() {
    if (!validate()) {
        return false;
    }
    
    if (collectTransferInfo() && validateTransfer()) {
        successful = executeTransfer();
        if (successful) {
            createTransactionRecord();
            statusMessage = "Transfer of " + std::to_string(amount) + " " + currency + 
                           " from " + sourceAccountNumber + " to " + destinationAccountNumber + " successful";
        } else {
            statusMessage = "Transfer failed";
        }
    } else {
        statusMessage = "Transfer validation failed";
    }
    
    logOperation();
    return successful;
}

bool TransferOperation::validate() {
    // Basic validation - check if account numbers and amount are valid
    if (sourceAccountNumber.empty() || destinationAccountNumber.empty()) {
        statusMessage = "Source or destination account number cannot be empty";
        return false;
    }
    
    if (amount <= 0) {
        statusMessage = "Transfer amount must be positive";
        return false;
    }
    
    return true;
}

bool TransferOperation::collectTransferInfo() {
    // In a real system, this might collect additional info or confirm details
    // For this example, we'll assume all needed info was provided in constructor
    return true;
}

bool TransferOperation::validateTransfer() {
    // In a real system, this would check:
    // 1. If source account exists and belongs to the requesting user
    // 2. If destination account exists
    // 3. If source account has sufficient funds
    // 4. Handle currency conversion if needed
    
    // For demonstration purposes only (replace with actual implementation)
    // Simulated account checks
    bool sourceExists = true; // Would check in database
    bool destExists = true;   // Would check in database
    bool sufficientFunds = true; // Would check balance
    
    return sourceExists && destExists && sufficientFunds;
}

bool TransferOperation::executeTransfer() {
    // In a real system, this would:
    // 1. Deduct from source account
    // 2. Add to destination account
    // 3. Handle atomicity (either both succeed or both fail)
    
    // For demonstration purposes only (replace with actual implementation)
    // Simulated transfer execution
    return true; // Assuming transfer succeeded
}

bool TransferOperation::createTransactionRecord() {
    // Create a Transaction record for this transfer
    std::vector<std::string> accounts = {sourceAccountNumber, destinationAccountNumber};
    transaction = new Transaction(operationID, amount, "Transfer", accounts);
    
    // Set additional details
    std::stringstream desc;
    desc << "Transfer of " << std::fixed << std::setprecision(2) << amount << " " << currency
         << " from account " << sourceAccountNumber 
         << " to account " << destinationAccountNumber;
    transaction->setDescription(desc.str());
    transaction->setIsValid(true);
    
    return true;
}

Transaction* TransferOperation::getTransaction() const {
    return transaction;
}

// TransactionHistoryOperation implementation
TransactionHistoryOperation::TransactionHistoryOperation(const std::string& id, 
                                                       const std::string& account,
                                                       std::time_t start, std::time_t end)
    : Operation(id, "TransactionHistory"), accountNumber(account), 
      startDate(start), endDate(end), transactionType("") {
}

bool TransactionHistoryOperation::execute() {
    if (!validate()) {
        return false;
    }
    
    if (collectFilterCriteria() && retrieveTransactions()) {
        formatTransactionList();
        successful = true;
        statusMessage = "Successfully retrieved " + std::to_string(transactions.size()) + 
                       " transactions for account " + accountNumber;
    } else {
        statusMessage = "Failed to retrieve transaction history";
    }
    
    logOperation();
    return successful;
}

bool TransactionHistoryOperation::validate() {
    // Check if account number is valid
    if (accountNumber.empty()) {
        statusMessage = "Account number cannot be empty";
        return false;
    }
    
    // Check if date range is valid
    if (endDate < startDate) {
        statusMessage = "End date cannot be before start date";
        return false;
    }
    
    return true;
}

bool TransactionHistoryOperation::collectFilterCriteria() {
    // In a real system, this might collect additional filter criteria
    // For this example, we'll assume all needed info was provided in constructor
    return true;
}

bool TransactionHistoryOperation::retrieveTransactions() {
    // In a real system, this would query a database for transactions
    // that match the filter criteria
    
    // For demonstration purposes only (replace with actual implementation)
    // Simulated transaction retrieval
    
    // Clear existing transactions
    for (auto* trans : transactions) {
        delete trans;
    }
    transactions.clear();
    
    // Create some sample transactions
    std::vector<std::string> accounts = {accountNumber};
    
    // Sample deposit
    Transaction* deposit = new Transaction("T001", 500.00, "Deposit", accounts);
    deposit->setDescription("Deposit to account " + accountNumber);
    transactions.push_back(deposit);
    
    // Sample withdrawal
    Transaction* withdrawal = new Transaction("T002", 200.00, "Withdrawal", accounts);
    withdrawal->setDescription("Withdrawal from account " + accountNumber);
    transactions.push_back(withdrawal);
    
    // Sample transfer if not filtering by type or if type is "Transfer"
    if (transactionType.empty() || transactionType == "Transfer") {
        std::vector<std::string> transferAccounts = {accountNumber, "ACC002"};
        Transaction* transfer = new Transaction("T003", 300.00, "Transfer", transferAccounts);
        transfer->setDescription("Transfer from account " + accountNumber + " to ACC002");
        transactions.push_back(transfer);
    }
    
    return true;
}

void TransactionHistoryOperation::formatTransactionList() const {
    // In a real system, this would format the transactions for display
    
    std::cout << "Transaction History for Account: " << accountNumber << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(10) << "ID" 
              << std::setw(15) << "Type" 
              << std::setw(15) << "Amount" 
              << "Description" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    
    for (const auto* trans : transactions) {
        std::cout << std::left << std::setw(10) << trans->getTransactionID() 
                  << std::setw(15) << trans->getTransactionType() 
                  << std::setw(15) << std::fixed << std::setprecision(2) << trans->getAmount() 
                  << trans->getDescription() << std::endl;
    }
    
    std::cout << "--------------------------------------------------" << std::endl;
}

std::vector<Transaction*> TransactionHistoryOperation::getTransactions() const {
    return transactions;
}

void TransactionHistoryOperation::setDateRange(std::time_t start, std::time_t end) {
    startDate = start;
    endDate = end;
}

void TransactionHistoryOperation::setTransactionType(const std::string& type) {
    transactionType = type;
}