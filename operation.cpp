#include "operation.h"
#include "Bank.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

// Base Operation implementation
Operation::Operation() {

}
Operation::Operation(const std::string& type, float amt, const std::string& id)
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
    // Instead of printing to console, log the operation status to the UI or a log file
    // The UI can retrieve the `statusMessage` using `getStatusMessage()`
    // Example: UI can display `statusMessage` to the user
}

string Operation::getMessage() {
    return message;
}
bool Operation::accBelongsToCustomer() {
    //The message is returned to the UI class to display it as the error message.

    if (!currentCustomer || !acc) {
        message = "Account does not belong to customer";
        return false;
    }
    for (Account* account : currentCustomer->getAccounts()) {
        if (account == acc) return true;
    }
    message = "Account does not belong to customer";
    return false;
}
void Operation::loadParameters(Customer* customer, Account* account, float amt) {
    currentCustomer = customer;
    acc = account;
    amount = amt;
}

// LoginOperation implementation
LoginOperation::LoginOperation(const std::string& uname, const std::string& pwd, Bank* IBMS)
    : Operation("Login"), username(uname), password(pwd), user(), failedAttempts(0) {
    this->IBMS = IBMS;
}

bool LoginOperation::execute() {
    if (!validate()) {
        handleFailedLogin();
        return false;
    }

    if (validateCredentials()) {
        successful = createUserSession();
        if (successful) {
            message = "Login successful for user: " + username;
        }
        else {
            message = "Failed to create session for user: " + username;
            handleFailedLogin();
        }
    }
    else {
        message = "Invalid credentials for user: " + username;
        handleFailedLogin();
    }

    return successful;
}

bool LoginOperation::validate() {
    // Simple validation - check if username and password are not empty
    if (username.empty() || password.empty()) {
        message = "Username or password cannot be empty";
        return false;
    }
    return true;
}

bool LoginOperation::validateCredentials() {
    // Check against the users map in the Bank class
    map<std::string, Customer> currentCustomers = IBMS->getCustomers();
    auto it = currentCustomers.find(username);
    if (it != currentCustomers.end() && it->second.getPassword() == password) {
        user = it->second;
        return true;
    }

    user = Customer();
    return false;
}

bool LoginOperation::createUserSession() {
    //// In a real system, this would create a session token or similar
    //if (user != nullptr) {
    //    return true; // Session created successfully
    //}
    //return false;
    return true;
}

void LoginOperation::handleFailedLogin() {
    failedAttempts++;
    // In a real system, you might lock the account after multiple failed attempts
    if (failedAttempts >= 3) {
        message += " (Account temporarily locked due to multiple failed attempts)";
    }
}

Customer LoginOperation::getLoggedInUser() const {
    return user;
}

// TransferOperation implementation
TransferOperation::TransferOperation(Customer* currentCustomer,const std::string& source,
    const std::string& destination,float amt,Bank* IBMS)
    : Operation("Transfer"), sourceAccountNumber(source),
    destinationAccountNumber(destination), transaction(nullptr) {
    amount = amt;
    cout << "Amount given is: " << to_string(amount);
    this->currentCustomer = currentCustomer;
    this->IBMS = IBMS;
}

TransferOperation::~TransferOperation() {
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
            message = "Transfer of " + std::to_string(amount) + " " + currency +
                " from " + sourceAccountNumber + " to " + destinationAccountNumber + " successful";
        }
        else {
            message = "Transfer failed";
        }
    }
    else {
    }

    logOperation();
    return successful;
}

bool TransferOperation::validate() {
    // Basic validation - check if account numbers and amount are valid
    if (sourceAccountNumber.empty() || destinationAccountNumber.empty()) {
        message = "Source or destination account number cannot be empty";
        return false;
    }

    if (amount <= 0) {
        message = "Transfer amount must be positive: " + to_string(amount);
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
    // Check if source and destination accounts exist
    sourceAccount = currentCustomer->getAccountWithID(std::stoi(sourceAccountNumber));
    destAccount = IBMS->getAccountById(std::stoi(destinationAccountNumber));

    if (!sourceAccount || !destAccount) {
        message = "Source or destination account does not exist.";
        return false;
    }

    // Check if source account has sufficient funds
    if (sourceAccount->getBalance() < amount) {
        message = "Insufficient funds in source account.";
        return false;
    }

    return true;
}

bool TransferOperation::executeTransfer() {
    Account* sourceAccount = currentCustomer ? currentCustomer->getAccountWithID(std::stoi(sourceAccountNumber)) : nullptr;
    Account* destAccount = IBMS ? IBMS->getAccountById(std::stoi(destinationAccountNumber)) : nullptr;

    if (!sourceAccount || !destAccount) {
        return false;
    }

    // Deduct from source and add to destination
    sourceAccount->subtractAmount(amount);
    destAccount->addAmount(amount);
  
    return true;
}

bool TransferOperation::createTransactionRecord() {
    // Create a Transaction record for this transfer
    std::vector<std::string> accounts = { sourceAccountNumber, destinationAccountNumber };
    transaction = new Transaction(operationID, amount, "Transfer", accounts);
    sourceAccount->addTransaction(*transaction);
    destAccount->addTransaction(*transaction);
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
TransactionHistoryOperation::TransactionHistoryOperation(Customer* currentCustomer, const std::string& account, Bank* IBMS)
    : Operation("TransactionHistory"), accountNumber(account), currentCustomer(currentCustomer) {
    this->IBMS = IBMS;  
    this->account = currentCustomer ? currentCustomer->getAccountWithID(std::stoi(account)) : nullptr;

}

TransactionHistoryOperation::~TransactionHistoryOperation() {
    for (auto* trans : transactions) {
        delete trans;
    }
    transactions.clear();
}

bool TransactionHistoryOperation::execute() {
    if (!validate()) {
        return false;
    }

    if (collectFilterCriteria() && retrieveTransactions()) {
        formatTransactionList();
        successful = true;
        message = "Successfully retrieved " + std::to_string(transactions.size()) +
            " transactions for account " + accountNumber;
    }
    else {
        message = "Failed to retrieve transaction history";
    }

    bool foundAccount = false;

    vector<Account*> accounts = currentCustomer->getAccounts();
    for (Account* acc : accounts) {
        if (to_string(acc->getAccountNumber()) == accountNumber) {
            foundAccount = true;
            vector<Transaction> Transactions = acc->getTransactionHistory();
            if (Transactions.empty()) {
                message = "Account: " + accountNumber + " does not have any transactions to show.";
                return false;
            }
            else {
                vector <string> involvedAccounts;
                double amount;
                for (const Transaction& Tran : Transactions) {
                    involvedAccounts = Tran.getInvolvedAccounts();
                    amount = Tran.getAmount();
                    message = "Transferred " + to_string(amount) + " from account: " + involvedAccounts[0] + " to account: " + involvedAccounts[1] + "\n";
                }

            }
        }
    }
    if (!foundAccount) {
        message = "Account not found!";
        return false;
    }
    logOperation();
    return successful;
}

bool TransactionHistoryOperation::validate() {
    // Check if account number is valid
    if (accountNumber.empty()) {
        message = "Account number cannot be empty";
        return false;
    }

    // Check if date range is valid
    if (endDate < startDate) {
        message = "End date cannot be before start date";
        return false;
    }

    return true;
}

bool TransactionHistoryOperation::collectFilterCriteria() {

    return true;
}

bool TransactionHistoryOperation::retrieveTransactions() {
    // Clear existing transactions
    for (auto* trans : transactions) {
        delete trans;
    }
    transactions.clear();

    // Fetch transactions from the account
    account = currentCustomer->getAccountWithID(std::stoi(accountNumber));
    if (!account) {
        message = "Account not found.";
        return false;
    }

    std::vector<Transaction> accountTransactions = account->getTransactionHistory();
    for (const Transaction& trans : accountTransactions) {
        transactions.push_back(new Transaction(trans));
    }

    return true;
}

void TransactionHistoryOperation::formatTransactionList() {
    std::ostringstream formattedList;
    formattedList << "Transaction History for Account: " << accountNumber << "\n";
    formattedList << "--------------------------------------------------\n";
    formattedList << std::left << std::setw(10) << "ID"
        << std::setw(15) << "Type"
        << std::setw(15) << "Amount"
        << "Description\n";
    formattedList << "--------------------------------------------------\n";

    for (const auto* trans : transactions) {
        formattedList << std::left << std::setw(10) << trans->getTransactionID()
            << std::setw(15) << trans->getTransactionType()
            << std::setw(15) << std::fixed << std::setprecision(2) << trans->getAmount()
            << trans->getDescription() << "\n";
    }

    formattedList << "--------------------------------------------------\n";

    statusMessage = formattedList.str();
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

std::string TransactionHistoryOperation::viewTransactionHistory() {
    if (!execute()) {
        return "Failed to retrieve transaction history: " + statusMessage;
    }

    return statusMessage;
}

//Implementation of the Deposit functionality class.

bool Deposit::execute() {
    //Check if the given amount is positive or not first
    if (not validate()) {
        return false;
    }
    else {
        acc->addAmount(amount);
        return true;
    }

}
bool Deposit::validate() {
    //The message is returned to the UI class to display it as the error message.
    if (not accBelongsToCustomer()) {
        return false;
    }
    else if (amount <= 0) {
        message = "Amount must be a positive number";
        return false;
    }
    return true;
}




//Implementation of the Withdraw functionality class.

bool Withdraw::validate() {
    if (!accBelongsToCustomer()) {
        return false;
    }

    if (amount <= 0) {
        message = "Amount must be a positive number";
        return false;
    }

    if (!acc || acc->getBalance() < amount) {
        message = "Couldn't withdraw amount: " + std::to_string(amount) +
            " from account: " + std::to_string(acc->getAccountNumber()) +
            " with a balance of: " + std::to_string(acc->getBalance());
        return false;
    }

    return true;
}
bool Withdraw::execute() {
    if (not validate()) {
        return false;
    }
    else {
        acc->subtractAmount(amount);
        return true;
    }

}


//Implementation of the Balance Inquiry functionality class.

bool BalanceInquiry::execute() {
    //The message is returned to the UI class to display it as the error message.

    if (validate()) {
        message = "The balance for account: " + to_string(acc->getAccountNumber()) + " is: " + to_string(acc->getBalance()) + " " + acc->getCurrency() + "\n";
        return true;
    }
    return false;
}
bool BalanceInquiry::validate() {
    return accBelongsToCustomer();
}

//Implementation of the TransactionOperation functionality class.

bool TransactionOperation::execute() {
    if (!validate()) {
        statusMessage = "Transaction validation failed.";
        return false;
    }

    if (processTransaction()) {
        successful = true;
        statusMessage = "Transaction completed successfully.";
    }
    else {
        successful = false;
        statusMessage = "Transaction failed.";
    }

    logOperation();
    return successful;
}

bool TransactionOperation::validate() {
    // Basic validation logic
    if (amount <= 0) {
        statusMessage = "Transaction amount must be positive.";
        return false;
    }

    if (!accBelongsToCustomer()) {
        statusMessage = "Account does not belong to the customer.";
        return false;
    }

    return true;
}

bool TransactionOperation::processTransaction() {
    if (!acc) {
        statusMessage = "Account is not valid.";
        return false;
    }

    if (acc->getBalance() >= amount) {
        acc->subtractAmount(amount); // Deduct the amount
        return true;
    }
    else {
        statusMessage = "Insufficient balance for the transaction.";
        return false;
    }
}
