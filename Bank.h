#pragma once
#include <map>
#include <string>
#include <vector>
#include "Account.h"
#include "User.h"

class UI;

class Bank {
private:
    std::map<std::string, Customer> customers; // key: customer name, value: customer object
    std::map<int, Account*> accounts; // key: account id, value: account object
    std::map<std::string, User*> users; // key: user ID, value: user pointer
    UI* display;
    std::string message;

    // Helper method to generate unique account ID
    int generateUniqueAccountId();

public:
    Bank(UI* display);
    Bank();
    ~Bank();
    
    // User management
    void viewAllUsers();
    map<int, Account*> getAccounts();
    map<std::string, Customer> getCustomers();
    void viewAllAccounts();
    bool addUser(const std::string& id, const std::string& name, const std::string& password, const std::string& role);
    bool deleteUser(const std::string& userName);
    bool resetUserPassword(const std::string& userId, const std::string& newPassword);
    // Account management
    bool createAccount(const std::string& currency, const std::string& ownerName, float initialBalance, int accountId);
    bool addAccountToCustomer(int accountId, const std::string& customerName);
    bool transferMoney(const std::string& fromCustomerName, int fromAccountId,
        const std::string& toCustomerName, int toAccountId, float amount);

    // Customer management
    Customer* getCustomerByName(const std::string& name);
    Account* getAccountById(int accountId);

    // For testing/demo purposes
    void initializeDemoData();
};
