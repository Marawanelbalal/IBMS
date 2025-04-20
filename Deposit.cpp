//#include "Deposit.h"
//
//void Deposit::execute(Account& acc, float amount) {
//	//Check if the given amount is positive or not first
//	//Note: All instances of cout should be replaced by 'UI CLASS' functions.
//
//	if (amount > 0) {
//		acc.addAmount(amount);
//		message = "Successfully deposited: " + to_string(amount) + " into account: " + to_string(acc.getAccountNumber()) + ". New balance: " + to_string(acc.getBalance()) + "\n";
//		display.displaySuccess(message);
//		return;
//	}
//	else { cout << "Given amount must be positive" << endl; return; }
//
//}