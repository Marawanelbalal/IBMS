#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include "Account.h"
#include "user.h"
#include "Deposit.h"
#include "Withdraw.h"
#include "Bank.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>


// User base class implementation
User::User() {
	isLoggedIn = false;

}
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

Customer::Customer()
{
	name = "Unknown";
	address = "Unknown";
	phoneNumber = 1040440440;
}
Customer::Customer(const std::string& userName,const std::string& id, const std::string& pwd)
	: User(id, userName, pwd, "customer"), phoneNumber(10040005000){
}



//Customer::Customer(string name, string address, int phoneNumber) {
//	this->name = name;
//	this->address = address;
//	this->phoneNumber = phoneNumber;
//}

string Customer::getName() { return name; }

string Customer::getAddress() { return address; }

int Customer::getPhoneNumber() { return phoneNumber; }

void Customer::setAccounts(vector<Account> Accounts) {
	this->Accounts = Accounts;
}
vector<Account> Customer::getAccounts() { return Accounts; }
//Store accounts in a vector.


void Customer::viewOwnAccounts() {
	//First check if the customer has any accounts
	if (Accounts.empty()) {
		message = "User does not own any accounts to show.";
		display.displayError(message);
		return;
	}
	else {
		message = "For Customer: " + name + "\n" + "The available accounts are: " + "\n";
		display.displayMessage(message);
		//Loop through the accounts vector using this format: for(type iterator : vector)
		//Use a reference (Account&) instead of the actual class, since classes are not easy to handle like primitive data types.
		for (const Account& acc : Accounts) {
			message = to_string(acc.getAccountNumber()) + " : " + to_string(acc.getBalance()) + " " + acc.getCurrency() + "\n";
			display.displayMessage(message);
		}
		return;
	}

}

void Customer::updateContactInfo(string address, int phoneNumber) {
	this->address = address;
	this->phoneNumber = phoneNumber;
}


void Customer::transferMoney(Account& acc1, Account& acc2, Customer& recipient, float amount) {
	//Note: All instances of cout should be replaced with 'UI CLASS' functions

	// Assuming Account::operator== is defined and compares account numbers
	if (acc1 == acc2) {
		message = "Can't transfer from an account to the same account.";
		display.displayError(message);
		return;
	}

	//Check if the given amount is valid
	if (amount <= 0) {
		message = "Error! Given amount must be a positive number";
		display.displayError(message);
		return;
	}

	//Check if acc1 has enough balance for the transaction
	if (amount > acc1.getBalance()) {
		message = "Error! Not enough balance to complete the transaction";
		display.displayError(message);
		return;
	}

	// The checks below for ownership are better handled by the caller (Bank)
	// ensuring that the acc1 and acc2 references obtained via getAccountWithID
	// actually belong to the respective customers.
	// For the current structure where getAccountWithID returns a reference
	// to an account within the customer's vector, these checks are implicitly
	// handled if getAccountWithID throws an error when the account is not found.
	// However, explicit checks can add robustness depending on the system's design.

	/*
	// Removed unnecessary and incorrect ownership checks and vector updates
	// Check if the user has any accounts first, before checking if the user owns acc1
	if (Accounts.empty() || recipient.getAccounts().empty()) {
		message = "User/Recipient does not own any accounts to transfer money from/to.";
		display.displayError(message);
		return;
	}

	//Check if the user owns acc1 by iterating through their accounts
	bool ownsAccount = false;
	for (const Account& acc : Accounts) {
		if (acc1 == acc) {
			ownsAccount = true;
			break;
		}
	}
	if (not ownsAccount) {
		message = "User does not own account: " + to_string(acc1.getAccountNumber());
		display.displayError(message);
		return;
	}

	//Check if recipient owns acc2 by iterating through their accounts
	bool recipientOwnsAccount = false;
	for (const Account& acc : recipient.getAccounts()) { // getAccounts returns a copy here
		if (acc2 == acc) {
			recipientOwnsAccount = true;
			break;
		}
	}
	if (not recipientOwnsAccount) {
		message = "User does not own account: " + to_string(acc2.getAccountNumber());
		display.displayError(message);
		return;
	}
	*/


	// Complete the transaction after passing all checks
	// acc1 and acc2 are references to the Account objects within the customer's vectors,
	// so modifying them here updates the state directly in the vectors.
	acc1.subtractAmount(amount);
	acc2.addAmount(amount);


	message = "Successfully transferred " + std::to_string(amount) + " from account: " + std::to_string(acc1.getAccountNumber()) + " to account: " + std::to_string(acc2.getAccountNumber()) + "\n";
	message += "Current balance for account: " + std::to_string(acc1.getAccountNumber()) + " is: " + std::to_string(acc1.getBalance()) + "\n";
	message += "Current balance for account: " + std::to_string(acc2.getAccountNumber()) + " is: " + std::to_string(acc2.getBalance()) + "\n";
	display.displaySuccess(message);

	// Transaction logging (assuming it's working correctly)
	std::vector<std::string> AccountNumbers;
	std::string acc1str = std::to_string(acc1.getAccountNumber());
	std::string acc2str = std::to_string(acc2.getAccountNumber());
	AccountNumbers.push_back(acc1str);
	AccountNumbers.push_back(acc2str);
	// Fix for random ID generation: Use a better range or UUIDs in production
	int ID = 1000 + std::rand() % 9000; // Simple 4-digit random ID
	std::string IDstr = std::to_string(ID);

	Transaction T(IDstr, amount, "Transfer", AccountNumbers);
	acc1.addTransaction(T);
	acc2.addTransaction(T);

	// Removed the redundant and incorrect loops below:
	/*
	for (int i = 0; i < Accounts.size(); i++) {
		if (Accounts[i] == acc1) {
			Accounts[i] = acc1;
			break;
		}
	}
	for (int i = 0; i < recipientAccounts.size(); i++) { // recipientAccounts is a local copy
		if (recipientAccounts[i] == acc2) {
			recipientAccounts[i] = acc2;
			recipient.setAccounts(recipientAccounts); // This is incorrect
			break;
		}
	}
	*/
}

void Customer::viewTransactionHistory() {
	if (Customer::Accounts.empty()) {
		message = "User does not own any accounts to show transactions from.";
		display.displayError(message);
		return;
	}
	else {
		message = "For Customer: " + name + "\n" + "The past transactions are: " + "\n";
		display.displayMessage(message);
		for (Account& acc : Accounts)
			acc.viewTransactionsHistory();
	}
}

void Customer::addAccount(Account& acc) { Accounts.push_back(acc); }

Account& Customer::getAccountWithID(int accID) {
	for (Account& acc : Accounts) {
		if (acc.getAccountNumber() == accID) return acc;
	}
	throw runtime_error("Account not found: " + to_string(accID));
}

void Customer::requestNewAccount() {

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

//// Customer class implementation

//
//void Customer::viewOwnAccount() const {
//    // Implementation would display all accounts owned by this customer
//    std::cout << "Accounts for customer " << getName() << ":" << std::endl;
//    for (const auto& accNum : accountNumbers) {
//        std::cout << "Account: " << accNum << std::endl;
//    }
//}
//
//bool Customer::transferMoney(const std::string& fromAccount, const std::string& toAccount, double amount) {
//    // Check if customer owns the fromAccount
//    auto it = std::find(accountNumbers.begin(), accountNumbers.end(), fromAccount);
//    if (it == accountNumbers.end()) {
//        std::cout << "You don't own the source account." << std::endl;
//        return false;
//    }
//    
//    // Implementation would create and execute a transfer transaction
//    std::cout << "Transferring $" << amount << " from " << fromAccount 
//              << " to " << toAccount << std::endl;
//    return true;
//}
//
//bool Customer::requestNewAccount(const std::string& accountType, double initialDeposit) {
//    // Implementation would create a new account request
//    std::cout << "Requesting new " << accountType << " account with initial deposit of $"
//              << initialDeposit << std::endl;
//    return true;
//}
//
//void Customer::viewTransactionHistory(const std::string& accountNumber) const {
//    // Check if customer owns the account
//    auto it = std::find(accountNumbers.begin(), accountNumbers.end(), accountNumber);
//    if (it == accountNumbers.end()) {
//        std::cout << "You don't own this account." << std::endl;
//        return;
//    }
//    
//    // Implementation would fetch and display transaction history
//    std::cout << "Transaction history for account " << accountNumber << ":" << std::endl;
//}
//
//void Customer::updateContactInfo(const std::string& newContactInfo) {
//    contactInfo = newContactInfo;
//    std::cout << "Contact information updated." << std::endl;
//}
//
//void Customer::setNotificationPreferences(bool enable) {
//    notificationsEnabled = enable;
//    std::cout << "Notifications " << (enable ? "enabled." : "disabled.") << std::endl;
//}
//
//void Customer::addAccount(const std::string& accountNumber) {
//    accountNumbers.push_back(accountNumber);
//}
//
//std::vector<std::string> Customer::getAccounts() const {
//    return accountNumbers;
//}
//
