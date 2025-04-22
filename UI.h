#pragma once
#include <iostream>
#include "operation.h"

using namespace std;

class Bank;
class Account;

class UI {
	Bank* IBMS;
	Withdraw Withdrawer;
	Deposit Depositer;
	BalanceInquiry Inquiry;

	bool loggedIn = false;
	string currentUserRole = "";
	string currentUsername = "";
	void waitForEnter() const;
	int getIntInput() const;
	double getDoubleInput() const;
	string getTextInput() const;
public:
	Customer* getCurrentCustomer();
	Customer* currentCustomer;
	Account* selectedAccount;
	int selectedAccountNumber;
	UI();
	~UI();
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
	void showInquiryScreen();
	void showUserAccounts();
	void logout();
	void run();

	// Administrator-specific screens
	void showCreateUserScreen();
	void showDeleteUserScreen();
	void showViewAllAccountsScreen();
	void showViewAllUsersScreen();
	void showResetPasswordScreen();
};
