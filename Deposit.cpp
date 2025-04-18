#include "Deposit.h"

void Deposit::start(Account& acc, float amount) {
	//Check if the given amount is positive or not first
	//Note: All instances of cout should be replaced by 'UI CLASS' functions.

	if (amount > 0) {
		acc.addAmount(amount);
		cout << "Successfully deposited: " << amount << " into account: " << acc.getAccountNumber() << ". New balance: " << acc.getBalance() << endl;
		return;
	}
	else { cout << "Given amount must be positive" << endl; return; }

}