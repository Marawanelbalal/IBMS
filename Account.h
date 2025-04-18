#pragma once
#include <string>
#include <vector>
#include "Transaction.h"
using namespace std;
class Account
{
    string owner;

    string currency;
    
    float balance;
    
    int accountId;

    vector<Transaction> Transactions;

public:
    Account();

    Account(string currency, string owner, float balance, int  accountId);
    
    float getBalance() const;

    int getAccountNumber() const;

    vector<Transaction> getTransactionHistory() const;

    void viewTransactionsHistory();


    void addTransaction(Transaction T);

    void addAmount(float amount);

    void subtractAmount(float amount);

    string getCurrency() const;


    //Define the meaning of == for members of the account class.
    bool operator==(const Account& otherAccount) const {
        return accountId == otherAccount.getAccountNumber();
    }
    

};

