#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include "Account.h"
#include "user.h"

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


Customer::Customer()
{
	name = "Unknown";
	address = "Unknown";
	phoneNumber = 1040440440;
}
Customer::Customer(const std::string& userName,const std::string& id, const std::string& pwd)
	: User(id, userName, pwd, "customer"), phoneNumber(10040005000){
}



string Customer::getName() { return name; }

string Customer::getAddress() { return address; }

int Customer::getPhoneNumber() { return phoneNumber; }

string Customer::getPassword() { return password; }

void Customer::setAccounts(vector<Account*> Accounts) {
	this->Accounts = Accounts;
}
vector<Account*> Customer::getAccounts() { return Accounts; }
//Store accounts in a vector.



void Customer::updateContactInfo(string address, int phoneNumber) {
	this->address = address;
	this->phoneNumber = phoneNumber;
}


void Customer::transferMoney(Account& acc1, Account& acc2, Customer& recipient, float amount) {
	//This should become its own functionality class.
	//Note: All instances of cout should be replaced with 'UI CLASS' functions

	// Assuming Account::operator== is defined and compares account numbers
	if (acc1 == acc2) {
		message = "Can't transfer from an account to the same account.";
		cout << message;
		//display.displayError(message);
		return;
	}

	//Check if the given amount is valid
	if (amount <= 0) {
		message = "Error! Given amount must be a positive number";
		cout << message;
		//display.displayError(message);
		return;
	}

	//Check if acc1 has enough balance for the transaction
	if (amount > acc1.getBalance()) {
		message = "Error! Not enough balance to complete the transaction";
		cout << message;
		//display.displayError(message);
		return;
	}


	// Complete the transaction after passing all checks
	// acc1 and acc2 are references to the Account objects within the customer's vectors,
	// so modifying them here updates the state directly in the vectors.
	acc1.subtractAmount(amount);
	acc2.addAmount(amount);


	message = "Successfully transferred " + std::to_string(amount) + " from account: " + std::to_string(acc1.getAccountNumber()) + " to account: " + std::to_string(acc2.getAccountNumber()) + "\n";
	message += "Current balance for account: " + std::to_string(acc1.getAccountNumber()) + " is: " + std::to_string(acc1.getBalance()) + "\n";
	message += "Current balance for account: " + std::to_string(acc2.getAccountNumber()) + " is: " + std::to_string(acc2.getBalance()) + "\n";
	cout << message;
	//display.displaySuccess(message);

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

}

void Customer::viewTransactionHistory() {
	//This should become its own functionality class.
	if (Customer::Accounts.empty()) {
		message = "User does not own any accounts to show transactions from.";
		cout << message;
		return;
	}
	else {
		message = "For Customer: " + name + "\n" + "The past transactions are: " + "\n";
		cout << message;
		//display.displayMessage(message);
		for (Account* acc : Accounts)
			acc->viewTransactionsHistory();
	}
}

void Customer::addAccount(Account* acc) { Accounts.push_back(acc); }

//Allows us to get the pointer to the current logged in account by using the id only in the UI class.
Account* Customer::getAccountWithID(int accID) {
	for (Account* acc : Accounts) {
		if (acc->getAccountNumber() == accID) return acc;
	}
	throw runtime_error("Account not found: " + to_string(accID));
}

void Customer::requestNewAccount() {

}

