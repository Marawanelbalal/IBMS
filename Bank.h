#pragma once
#include <map>
#include <string>
#include <vector>
#include "Account.h"
#include "User.h"

class UI;

class Bank {
    std::map<std::string, Customer> customers; // key: customer name, value: customer object
    std::map<int, Account*> accounts; // key: account id, value: account object
    std::map<std::string, User*> users; // key: user ID, value: user pointer
    UI* display;
    std::string message;
    
public:
    Bank(UI* display);
    Bank();
    ~Bank();
    
    // User management
    void viewAllUsers();
    void setCustomers(std::map<std::string, Customer>& customers);
    void setAccounts(std::map<int, Account*>& accounts);
    void setUsers(std::map<std::string, User*>& users);
    map<int, Account*>& getAccounts();
    map<std::string, Customer>& getCustomers();
    map<std::string, User*> getUsers();
    void viewAllAccounts();
    bool addUser(const std::string& id, const std::string& name, const std::string& password, const std::string& role, const std::string& phoneNumber);
    bool deleteUser(const std::string& userName);
    bool resetUserPassword(const std::string& userId, const std::string& newPassword, const std::string& newPhoneNumber);
    // Account management
    bool createAccount(const std::string& currency, const std::string& ownerName, float initialBalance, int accountId, string accountType);
    bool addAccountToCustomer(int accountId, const std::string& customerName);
    bool transferMoney(const std::string& fromCustomerName, int fromAccountId,
        const std::string& toCustomerName, int toAccountId, float amount);

    // Helper method to generate unique account ID

    int generateUniqueAccountId();

    // Customer management
    Customer* getCustomerByName(const std::string& name);
    Account* getAccountById(int accountId);

    // For testing/demo purposes
    void initializeDemoData();
};
