#include "Withdraw.h"
#include <iostream>
using namespace std;

void Withdraw::start(Account& acc, float amount) {
	if (amount <= 0) {
		cout << "Error: Amount must be a positive number" << endl;
		return;
	} //Check if the given amount is positive or not first

	else {

		//Next, check if the user has enough balance in their account
		//Note: All instances of cout should be replaced with 'UI CLASS' functions

		if (acc.getBalance() < amount) {
			cout << "Error: Couldn't withdraw amount: " << amount << " from account " << acc.getAccountNumber() << " with a balance of: " << acc.getBalance() << endl;
			return;
		}

		else {
			acc.subtractAmount(amount);
			cout << "Successfully withdrew " << amount << " from account " << acc.getAccountNumber() << ". New balance: " << acc.getBalance() << endl;
			return;
			}

		}

}
