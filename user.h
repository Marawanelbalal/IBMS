#pragma once
#include <vector>
#include <string>
#include "Account.h"

class User {
protected:
    std::string userID;
    std::string name;
    std::string password;
    std::string role; // admin or customer
    bool isLoggedIn;

public:
    User();
    // Constructor
    User(const std::string& id, const std::string& userName, 
         const std::string& pwd, const std::string& userRole);
    
    // Virtual destructor for proper inheritance
    virtual ~User();
    
    // Authentication methods
    virtual bool login(const std::string& enteredPassword);
    virtual void logout();
    virtual bool changePassword(const std::string& oldPassword, const std::string& newPassword);
    
    // Getters
    std::string getUserID() const;
    std::string getName() const;
    std::string getRole() const;
    bool getIsLoggedIn() const;
    std::string getPassword() const;
    
    // Display menu options specific to user type

};

// Derived Administrator class
class Administrator : public User {
public:
    // Constructor
    Administrator(const std::string& id, const std::string& userName, const std::string& pwd);
    
    // Admin-specific methods
    bool createUserAccount(const std::string& id, const std::string& name, 
                          const std::string& password, const std::string& role);
    bool deleteUserAccount(const std::string& id);
    void viewAllAccounts() const;
    void viewAllUsers() const;
    void generateReports() const;
    void modifySystemSettings() const;
    bool resetUserPassword(const std::string& userId, const std::string& newPassword);
    
};

// Derived Customer class

class Customer : public User
{

    string message;

    vector<Account*> Accounts;

    string address;

    int phoneNumber;

public:

    Customer();

    Customer(const std::string& userName,const std::string& id, const std::string& pwd);

    string getPassword();

    string getName();

    string getAddress();

    int getPhoneNumber();

    vector<Account*> getAccounts();

    void updateContactInfo(string address, int PhoneNumber);

    void transferMoney(Account& acc1, Account& acc2, Customer& recipient, float amount);

    void requestNewAccount();

    void viewTransactionHistory();

    void addAccount(Account* acc);

    void setAccounts(vector<Account*> Account);

    Account* getAccountWithID(int accID);


};

//Previous Implementation of Customer (Might need functions from it)
//
//class Customer : public User {
//private:
//    std::vector<std::string> accountNumbers; // List of accounts owned by this customer
//    std::string contactInfo;
//    bool notificationsEnabled;
//
//public:
//    // Constructor
//    Customer(const std::string& id, const std::string& userName, const std::string& pwd);
//    
//    // Customer-specific methods
//    void viewOwnAccount() const;
//    bool transferMoney(const std::string& fromAccount, const std::string& toAccount, double amount);
//    bool requestNewAccount(const std::string& accountType, double initialDeposit);
//    void viewTransactionHistory(const std::string& accountNumber) const;
//    void updateContactInfo(const std::string& newContactInfo);
//    void setNotificationPreferences(bool enable);
//    
//    // Account management
//    void addAccount(const std::string& accountNumber);
//    std::vector<std::string> getAccounts() const;
//    
//    // Override display menu
//    void displayMenu() const override;


