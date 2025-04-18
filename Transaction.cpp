#include "Transaction.h"
#include "Account.h"
//PLACEHOLDER transaction class
Transaction::Transaction(int acc1ID,int acc2ID, float amount) {
	this->acc1ID = acc1ID;
	this->acc2ID = acc2ID;
	this->amount = amount;
}
