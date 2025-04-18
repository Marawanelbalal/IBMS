#include "user.h"
#include <iostream>
#include <algorithm>

// User base class implementation
User::User(const std::string& id, const std::string& userName, 
           const std::string& pwd, const std::string& userRole)
    : userID(id), name(userName), password(pwd), role(userRole), isLoggedIn(false) {
}

User::~User() {
    // Virtual destructor implementation
}

bool User::login(const std::string& enteredPassword) {
    if (enteredPassword == password) {
        isLoggedIn = true;
        return true;
    }
    return false;
}

void User::logout() {
    isLoggedIn = false;
}

bool User::changePassword(const std::string& oldPassword, const std::string& newPassword) {
    if (oldPassword == password) {
        password = newPassword;
        return true;
    }
    return false;
}

std::string User::getUserID() const {
    return userID;
}

std::string User::getName() const {
    return name;
}

std::string User::getRole() const {
    return role;
}

bool User::getIsLoggedIn() const {
    return isLoggedIn;
}

// Administrator class implementation
Administrator::Administrator(const std::string& id, const std::string& userName, const std::string& pwd)
    : User(id, userName, pwd, "admin") {
}

bool Administrator::createUserAccount(const std::string& id, const std::string& name, 
                                     const std::string& password, const std::string& role) {
    // Implementation would interact with a user repository
    std::cout << "Created new user account: " << id << " with role: " << role << std::endl;
    return true;
}

bool Administrator::deleteUserAccount(const std::string& id) {
    // Implementation would interact with a user repository
    std::cout << "Deleted user account: " << id << std::endl;
    return true;
}

void Administrator::viewAllAccounts() const {
    // Implementation would fetch and display all accounts from a repository
    std::cout << "Displaying all bank accounts..." << std::endl;
}

void Administrator::viewAllUsers() const {
    // Implementation would fetch and display all users from a repository
    std::cout << "Displaying all system users..." << std::endl;
}

void Administrator::generateReports() const {
    // Implementation would generate various system reports
    std::cout << "Generating system reports..." << std::endl;
}

void Administrator::modifySystemSettings() const {
    // Implementation would allow changing system parameters
    std::cout << "Modifying system settings..." << std::endl;
}

bool Administrator::resetUserPassword(const std::string& userId, const std::string& newPassword) {
    // Implementation would find user and reset their password
    std::cout << "Reset password for user: " << userId << std::endl;
    return true;
}

void Administrator::displayMenu() const {
    std::cout << "\n--- Administrator Menu ---" << std::endl;
    std::cout << "1. Create User Account" << std::endl;
    std::cout << "2. Delete User Account" << std::endl;
    std::cout << "3. View All Accounts" << std::endl;
    std::cout << "4. View All Users" << std::endl;
    std::cout << "5. Generate Reports" << std::endl;
    std::cout << "6. Modify System Settings" << std::endl;
    std::cout << "7. Reset User Password" << std::endl;
    std::cout << "8. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}

// Customer class implementation
Customer::Customer(const std::string& id, const std::string& userName, const std::string& pwd)
    : User(id, userName, pwd, "customer"), contactInfo(""), notificationsEnabled(false) {
}

void Customer::viewOwnAccounts() const {
    // Implementation would display all accounts owned by this customer
    std::cout << "Accounts for customer " << getName() << ":" << std::endl;
    for (const auto& accNum : accountNumbers) {
        std::cout << "Account: " << accNum << std::endl;
    }
}

bool Customer::transferMoney(const std::string& fromAccount, const std::string& toAccount, double amount) {
    // Check if customer owns the fromAccount
    auto it = std::find(accountNumbers.begin(), accountNumbers.end(), fromAccount);
    if (it == accountNumbers.end()) {
        std::cout << "You don't own the source account." << std::endl;
        return false;
    }
    
    // Implementation would create and execute a transfer transaction
    std::cout << "Transferring $" << amount << " from " << fromAccount 
              << " to " << toAccount << std::endl;
    return true;
}

bool Customer::requestNewAccount(const std::string& accountType, double initialDeposit) {
    // Implementation would create a new account request
    std::cout << "Requesting new " << accountType << " account with initial deposit of $"
              << initialDeposit << std::endl;
    return true;
}

void Customer::viewTransactionHistory(const std::string& accountNumber) const {
    // Check if customer owns the account
    auto it = std::find(accountNumbers.begin(), accountNumbers.end(), accountNumber);
    if (it == accountNumbers.end()) {
        std::cout << "You don't own this account." << std::endl;
        return;
    }
    
    // Implementation would fetch and display transaction history
    std::cout << "Transaction history for account " << accountNumber << ":" << std::endl;
}

void Customer::updateContactInfo(const std::string& newContactInfo) {
    contactInfo = newContactInfo;
    std::cout << "Contact information updated." << std::endl;
}

void Customer::setNotificationPreferences(bool enable) {
    notificationsEnabled = enable;
    std::cout << "Notifications " << (enable ? "enabled." : "disabled.") << std::endl;
}

void Customer::addAccount(const std::string& accountNumber) {
    accountNumbers.push_back(accountNumber);
}

std::vector<std::string> Customer::getAccounts() const {
    return accountNumbers;
}

void Customer::displayMenu() const {
    std::cout << "\n--- Customer Menu ---" << std::endl;
    std::cout << "1. View My Accounts" << std::endl;
    std::cout << "2. Transfer Money" << std::endl;
    std::cout << "3. Request New Account" << std::endl;
    std::cout << "4. View Transaction History" << std::endl;
    std::cout << "5. Update Contact Information" << std::endl;
    std::cout << "6. Set Notification Preferences" << std::endl;
    std::cout << "7. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}