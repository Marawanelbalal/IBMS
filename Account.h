#pragma once

#include <string>
#include <vector>
#include "transaction.h"


using namespace std;
class Account
{
    string owner;

    string message;

    string currency;
    
    string accountType;
    
    float balance;
    
    int accountId;

    vector<Transaction> Transactions;

public:

    Account();

    Account(string currency, string owner, double balance, int  accountId,string accountType);
    
    float getBalance() const;

    int getAccountNumber() const;
    
    string getOwner() const;

    vector<Transaction> getTransactionHistory() const;

    string getAccountType() const;

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

