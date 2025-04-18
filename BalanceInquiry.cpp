#include "BalanceInquiry.h"
#include <iostream>
using namespace std;

//Note: All instances of cout should be replaced by UI class functions.
void BalanceInquiry::start(Account& acc) {
	cout << "The balance for account: " << acc.getAccountNumber() << " is: " << acc.getBalance() << " " << acc.getCurrency() << endl;
}
