#pragma once
#include <iostream>
using namespace std;

class Bank;
class Customer;

class UI {
	Bank* IBMS;
	bool loggedIn = false;
	string currentUserRole = "";
	string currentUsername = "";
	void waitForEnter() const;
	int getIntInput() const;
	double getDoubleInput() const;
	string getTextInput() const;
public:
	UI();
	~UI();
	Customer* getCurrentCustomer();
	Customer* currentCustomer;
	int generateUniqueAccountId();
	void initializeBank();
	void clearScreen() const;
	void displayHeader() const;
	void displayWelcome() const;
	void displayMessage(const string& message) const;
	void displayError(const string& message) const;
	void displaySuccess(const string& message) const;
	void showLoginScreen();
	void showRegisterScreen();
	int displayMainMenu();
	int displayAdminMenu();
	int displayCustomerMenu();
	void showAccountCreationScreen();
	void showDepositScreen();
	void showWithdrawalScreen();
	void showTransferScreen();
	void showTransactionDetails(int transactionId, const string& type, double amount,
		const string& accountInfo, const string& date);
	void showTransactionHistory();
	void showLoanApplicationScreen();
	void showLoanApprovalScreen();
	void logout();
	void run();
};
