#include "BalanceInquiry.h"
#include "Account.h"
#include "UI.h"
#include <iostream>
using namespace std;

//Note: All instances of cout should be replaced by UI class functions.
void BalanceInquiry::start(Account& acc) {
	message = "The balance for account: " + to_string(acc.getAccountNumber()) + " is: " + to_string(acc.getBalance()) + " " + acc.getCurrency() + "\n";
	display.displayMessage(message);
}
