#include "Bank.h"
#include <iostream>
#include <random>
#include <ctime>
#include "UI.h"

Bank::Bank(UI* display) {
    // Initialize random seed for account ID generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    this->display = display;
}
Bank::Bank() {
    // Initialize random seed for account ID generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}



map<int, Account*> Bank::getAccounts() { return accounts; }

void Bank::setCustomers(std::map<std::string, Customer>& customers) {
    this->customers = customers;
}

Bank::~Bank() {
    // Clean up dynamically allocated User objects
    for (auto& pair : users) {
        delete pair.second;
    }
    for (auto& pair : accounts) {
        delete pair.second;
    }
}
map<std::string, Customer>& Bank::getCustomers() {
    return customers;
}

int Bank::generateUniqueAccountId() {
    // Generate a random 5-digit account ID
    int accountId;
    do {
        accountId = 10000 + std::rand() % 90000;
    } while (accounts.find(accountId) != accounts.end()); // Ensure it's unique

    return accountId;
}

void Bank::viewAllUsers() {
    if (users.empty()) {
        message = "No users in the system.";
        display->displayMessage(message);
        return;
    }

    message = "All Users in the System:\n";
    display->displayMessage(message);

    for (const auto& pair : users) {
        User* user = pair.second;
        message = "User ID: " + user->getUserID() + ", Name: " + user->getName() +
            ", Role: " + user->getRole();
        display->displayMessage(message);
    }
}

void Bank::viewAllAccounts() {
    if (accounts.empty()) {
        message = "No accounts in the system.";
        display->displayMessage(message);
        return;
    }

    message = "All Accounts in the System:\n";
    display->displayMessage(message);

    for (const auto& pair : accounts) {
        Account* account = pair.second;
        message = "Account ID: " + std::to_string(account->getAccountNumber()) +
            ", Balance: " + std::to_string(account->getBalance()) +
            " " + account->getCurrency();
        display->displayMessage(message);
    }
}

bool Bank::addUser(const std::string& id, const std::string& name, const std::string& password, const std::string& role, const std::string& phoneNumber) {
    // Check if user ID already exists
    if (users.find(id) != users.end()) {
        message = "User ID already exists: " + id;
        display->displayError(message);
        return false;
    }

    // Create user based on role
    User* newUser = nullptr;
    if (role == "admin") {
        newUser = new Administrator(id, name, password);
    }
    else if (role == "customer") {
        newUser = new Customer(name, id, password,phoneNumber);

        // Also add to customers map if it's a customer
        customers[name] = *dynamic_cast<Customer*>(newUser);
    }
    else {
        message = "Invalid role: " + role;
        display->displayError(message);
        return false;
    }

    // Add to users map
    users[id] = newUser;

    message = "User added successfully: " + name;
    display->displaySuccess(message);
    return true;
}

bool Bank::deleteUser(const std::string& userName) {
    // Find user by name
    User* userToDelete = nullptr;
    std::string userIdToDelete;

    for (const auto& pair : users) {
        if (pair.second->getName() == userName) {
            userToDelete = pair.second;
            userIdToDelete = pair.first;
            break;
        }
    }

    if (!userToDelete) {
        message = "User not found: " + userName;
        display->displayError(message);
        return false;
    }

    // If it's a customer, remove from customers map
    if (userToDelete->getRole() == "customer") {
        customers.erase(userName);
    }

    // Delete user object and remove from users map
    delete userToDelete;
    users.erase(userIdToDelete);

    message = "User deleted successfully: " + userName;
    display->displaySuccess(message);
    return true;
}

bool Bank::resetUserPassword(const std::string& userId, const std::string& newPassword,const std::string& newPhoneNumber) {
    // Find user by ID
    auto it = users.find(userId);
    if (it == users.end()) {
        message = "User ID not found: " + userId;
        display->displayError(message);
        return false;
    }

    // Get the user and update their password directly
    User* user = it->second;
    std::string oldPassword = user->getPassword();
    
    // If this is a customer, we need to update the customer map as well
    if (user->getRole() == "customer") {
        std::string customerName = user->getName();
        auto customerIt = customers.find(customerName);
        if (customerIt != customers.end()) {
            // Create a new customer with the new password
            Customer updatedCustomer(customerName, userId, newPassword,newPhoneNumber);
            
            // Copy over accounts from the original customer
            updatedCustomer.setAccounts(customerIt->second.getAccounts());
            
            // Replace the customer in the map
            customers[customerName] = updatedCustomer;
        } else {
            message = "Warning: Customer not found in customer map: " + customerName;
            display->displayError(message);
            // Don't return false, still try to update the User password
        }
    }
    
    // Change password in the User object
    if (user->changePassword(oldPassword, newPassword)) {
        message = "Password reset successfully for user ID: " + userId;
        display->displaySuccess(message);
        return true;
    } else {
        message = "Failed to reset password for user ID: " + userId;
        display->displayError(message);
        return false;
    }
}

bool Bank::createAccount(const std::string& currency, const std::string& ownerName, float initialBalance, int accountId, string accountType) {
    // Generate a unique account ID

    // Create the account
    Account newAccount(currency, ownerName, initialBalance, accountId, accountType);

    // Add to accounts map
    accounts[accountId] = new Account(currency,ownerName,initialBalance,accountId,accountType);

    message = "Account created successfully. Account ID: " + std::to_string(accountId);
    display->displaySuccess(message);

    return true;
}

bool Bank::addAccountToCustomer(int accountId, const std::string& customerName) {
    // Check if account exists
    auto accountIt = accounts.find(accountId);
    if (accountIt == accounts.end()) {
        message = "Account not found: " + std::to_string(accountId);
        display->displayError(message);
        return false;
    }

    // Check if customer exists
    auto customerIt = customers.find(customerName);
    if (customerIt == customers.end()) {
        message = "Customer not found: " + customerName;
        display->displayError(message);
        return false;
    }

    // Add account to customer
    customerIt->second.addAccount(accountIt->second);

    message = "Account " + std::to_string(accountId) + " added to customer " + customerName;
    display->displaySuccess(message);

    return true;
}

bool Bank::transferMoney(const std::string& fromCustomerName, int fromAccountId,
    const std::string& toCustomerName, int toAccountId, float amount) {
    // Check if customers exist
    Customer* fromCustomer = getCustomerByName(fromCustomerName);
    Customer* toCustomer = getCustomerByName(toCustomerName);

    if (!fromCustomer) {
        message = "Source customer not found: " + fromCustomerName;
        display->displayError(message);
        return false;
    }

    if (!toCustomer) {
        message = "Destination customer not found: " + toCustomerName;
        display->displayError(message);
        return false;
    }

    // Get accounts
    Account* fromAccount = nullptr;
    Account* toAccount = nullptr;

    try {
        fromAccount = fromCustomer->getAccountWithID(fromAccountId);
        toAccount = toCustomer->getAccountWithID(toAccountId);
    }
    catch (const std::runtime_error& e) {
        message = e.what();
        display->displayError(message);
        return false;
    }

    // Perform transfer
    fromCustomer->transferMoney(*fromAccount, *toAccount, *toCustomer, amount);

    // Update accounts in the map
    accounts[fromAccountId] = fromAccount;
    accounts[toAccountId] = toAccount;

    return true;
}

Customer* Bank::getCustomerByName(const std::string& name) {
    auto it = customers.find(name);
    if (it != customers.end()) {
        return &it->second;
    }
    return nullptr;
}

Account* Bank::getAccountById(int accountId) {
    auto it = accounts.find(accountId);
    if (it != accounts.end()) {
        return it->second;
    }
    return nullptr;
}

void Bank::initializeDemoData() {
    // Create customers
    addUser("1019", "John Doe1", "password1", "customer","010050502202");
    addUser("1020", "John Doe2", "password2", "customer","010050502202");

    // Create accounts
    int ID1 = generateUniqueAccountId();
    int ID2 = generateUniqueAccountId();
    int ID3 = generateUniqueAccountId();
    createAccount("USD", "John Doe1", 500.0,ID1,"Savings");
    createAccount("USD", "John Doe1", 500.0,ID2,"Savings");
    createAccount("USD", "John Doe2", 100.0,ID3,"Savings");

    // Add accounts to customers (assuming account IDs are as created)
    // In a real system, you would store the account IDs when created
    auto &accountIds = accounts;
    int id1 = 0, id2 = 0, id3 = 0;
    int i = 0;
    for (const auto& pair : accountIds) {
        if (i == 0) id1 = pair.first;
        else if (i == 1) id2 = pair.first;
        else if (i == 2) id3 = pair.first;
        i++;
    }

    addAccountToCustomer(id1, "John Doe1");
    addAccountToCustomer(id2, "John Doe1");
    addAccountToCustomer(id3, "John Doe2");

    message = "Demo data initialized successfully.";
    display->displaySuccess(message);
}

map<std::string, User*> Bank::getUsers() {
    return users;
}
