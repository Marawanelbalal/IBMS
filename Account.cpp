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
Account::Account(string currency, string owner, float balance, int  accountId) {
    this->currency = currency;
    this->owner = owner;
    this->balance = balance;
    this->accountId = accountId;
}
float Account::getBalance() const {
    return balance;
}
int Account::getAccountNumber() const {
    return accountId;
}

vector<Transaction> Account::getTransactionHistory() const{ return Transactions; }


void  Account::viewTransactionsHistory() {
    if (Transactions.empty()) {
        cout << "Account: " << accountId << " does not have any transactions to show." << endl;
        return;
    }
    else {
        cout << "For Account: " << accountId << endl << "The past transactions are: " << endl;
        for (const Transaction& T : Transactions)
            cout << "Transferred " << T.amount << " from account: " << T.acc1ID << " to account: " << T.acc2ID << endl;
    }
}

void Account::addTransaction(Transaction T) { Transactions.push_back(T); }

void Account::addAmount(float amount) {
    balance += amount;
}
void Account::subtractAmount(float amount) {
    balance -= amount;
}
string Account::getCurrency() const {
    return currency;
}
