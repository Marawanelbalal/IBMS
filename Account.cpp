#include "Account.h"
#include <iostream>
#include <string>
using namespace std;
Account::Account() {
    this->currency = "EGP";
    this->owner = "Unknown";
    this->balance = 0.0;
    this->accountId = 00000;
}
Account::Account(string currency, string owner, double balance, int  accountId, string accountType) {
    this->currency = currency;
    this->owner = owner;
    this->balance = balance;
    this->accountId = accountId;
    this->accountType = accountType;
}
float Account::getBalance() const {
    return balance;
}
int Account::getAccountNumber() const {
    return accountId;
}
string Account::getOwner() const {
    return owner;
}
string Account::getCurrency() const {
    return currency;
}

string Account::getAccountType() const { return accountType; }

vector<Transaction> Account::getTransactionHistory() const{ return Transactions; }


void  Account::viewTransactionsHistory() {
    if (Transactions.empty()) {
        message = "Account: " + to_string(accountId) + " does not have any transactions to show.";
        cout << message;
        //display.displayError(message);
        return;
    }
    else {
        message = "For Account: " + to_string(accountId) + "\n" + "The past transactions are: " + "\n";
        cout << message;

        vector <string> involvedAccounts;
        double amount;
        for (const Transaction& Tran : Transactions) {
            involvedAccounts = Tran.getInvolvedAccounts();
            amount = Tran.getAmount();
            message = "Transferred " + to_string(amount) + " from account: " + involvedAccounts[0] + " to account: " + involvedAccounts[1] + "\n";
            cout << message;
            //display.displayMessage(message);
        }
    }
}

void Account::addTransaction(Transaction T) { Transactions.push_back(T); }

void Account::addAmount(float amount) {
    balance += amount;
}
void Account::subtractAmount(float amount) {
    balance -= amount;
}

