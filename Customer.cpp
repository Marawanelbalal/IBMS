#include "Customer.h"
#include "Deposit.h"
#include "Withdraw.h"
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

//IMPORTANT: All instances of cout should be replaced by the 'UI CLASS' functions:



Customer::Customer()
{
		name = "Unknown";
		address = "Unknown";
		phoneNumber = 1040440440;
}

Customer::Customer(string name, string address, int phoneNumber) {
	this-> name = name;
	this-> address = address;
	this-> phoneNumber = phoneNumber;
}

string Customer::getName() { return name; }

string Customer::getAddress() { return address; }

int Customer::getPhoneNumber() { return phoneNumber; }

void Customer::setAccounts(vector<Account> Accounts) {
	this->Accounts = Accounts;
}
vector<Account> Customer::getAccounts() { return Accounts; }
//Store accounts in a vector.


void Customer::viewOwnAccounts() const {
	//First check if the customer has any accounts
	if (Accounts.empty()) {
		cout << "User does not own any accounts to show." << endl;
		return;
	}
	else {
		cout << "For Customer: " << name << endl << "The available accounts are: " << endl;
		//Loop through the accounts vector using this format: for(type iterator : vector)
		//Use a reference (Account&) instead of the actual class, since classes are not easy to handle like primitive data types.
		for (const Account& acc : Accounts)
			cout << acc.getAccountNumber() << " : " << acc.getBalance() << " " << acc.getCurrency() << endl;
		return;
	}

}

void Customer::updateContactInfo(string name, string address, int phoneNumber) {
	this->name = name;
	this->address = address;
	this->phoneNumber = phoneNumber;
}


void Customer::transferMoney(Account& acc1, Account& acc2,Customer& recipient, float amount) {
	//Note: All instances of cout should be replaced with 'UI CLASS' functions
	
	//Check if the user is transferring between unique accounts
	vector<Account> recipientAccounts = recipient.getAccounts();

	if (acc1 == acc2) {
		cout << "Error! Can't transfer from an account to the same account." << endl;
		return;
	}

	//Check if the given amount is valid
	if (amount <= 0) {
		cout << "Error! Given amount must be a positive number" << endl;
		return;
	}

	//Check if acc1 has enough balance for the transaction
	if (amount > acc1.getBalance()) {
		cout << "Error! Not enough balance to complete the transaction" << endl;
		return;
	}

	//Check if the user has any accounts first, before checking if the user owns acc1
	if (Accounts.empty() || recipientAccounts.empty()) {
		cout << "User/Recipient does not own any accounts to transfer money from/to." << endl;
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
		cout << "User does not own account: " << acc1.getAccountNumber();
		return;
	}

	//Check if recipient owns acc2 by iterating through their accounts
	bool recipientOwnsAccount = false;
	for (const Account& acc : recipient.getAccounts()){
		if (acc2 == acc) {
			recipientOwnsAccount = true;
			break;
		}
	}
	if (not recipientOwnsAccount) {
		cout << "User does not own account: " << acc2.getAccountNumber();
		return;
	}


	//Complete the transaction after passing all checks

	acc1.subtractAmount(amount);
	acc2.addAmount(amount);


	cout << "Successfully transferred " << amount << " from account: " << acc1.getAccountNumber() << " to account: " << acc2.getAccountNumber() << endl;
	cout << "Current balance for account: " << acc1.getAccountNumber() << " is: " << acc1.getBalance() << endl;

	Transaction T(acc1.getAccountNumber(), acc2.getAccountNumber(), amount);
	acc1.addTransaction(T);
	acc2.addTransaction(T);

	for (int i = 0; i < Accounts.size(); i++) {
		if (Accounts[i] == acc1) {
			Accounts[i] = acc1;
			break;
		}
	}
	for (int i = 0; i < recipientAccounts.size(); i++) {
		if (recipientAccounts[i] == acc2) {
			recipientAccounts[i] = acc2;
			recipient.setAccounts(recipientAccounts);
			break;
		}
	}


	

}

void Customer::viewTransactionHistory() {
	if (Customer::Accounts.empty()) {
		cout << "User does not own any accounts to show transactions from." << endl;
		return;
	}
	else {
		cout << "For Customer: " << name << endl << "The past transactions are: " << endl;
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
