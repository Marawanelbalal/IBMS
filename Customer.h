#pragma once
#include <vector>
#include "Account.h"
#include "Transaction.h"

class Customer
{
	vector<Account> Accounts;

	string name, address;
	
	int phoneNumber;
	
public:

	Customer();

	Customer(string name, string address, int phoneNumber);

	string getName();

	string getAddress();

	int getPhoneNumber();

	vector<Account> getAccounts();

	void updateContactInfo(string name, string address, int PhoneNumber);

	void viewOwnAccounts() const;

	void transferMoney(Account& acc1, Account& acc2,Customer& recipient, float amount);

	void requestNewAccount();

	void viewTransactionHistory();

	void addAccount(Account& acc);

	void setAccounts(vector<Account> Account);
	
	Account& getAccountWithID(int accID);
	
};

