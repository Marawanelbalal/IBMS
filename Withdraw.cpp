#include "Withdraw.h"
#include <iostream>
using namespace std;

void Withdraw::start(Account& acc, float amount) {
	if (amount <= 0) {
		display.displayError("Amount must be a positive number");
		return;
	} //Check if the given amount is positive or not first

	else {

		//Next, check if the user has enough balance in their account
		//Note: All instances of cout should be replaced with 'UI CLASS' functions

		if (acc.getBalance() < amount) {
			message = "Couldn't withdraw amount: " + to_string(amount) + " from account: " + to_string(acc.getAccountNumber()) + "with a balance of: " + to_string(acc.getBalance());
			display.displayError(message);
			return;
		}

		else {
			acc.subtractAmount(amount);
			message = "Successfully withdrew " + to_string(amount) + " from account " + to_string(acc.getAccountNumber()) + ". New balance: " + to_string(acc.getBalance()) + "\n";
			display.displaySuccess(message);
			return;
			}

		}

}
