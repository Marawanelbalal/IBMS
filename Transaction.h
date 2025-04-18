#pragma once

//Transaction.h can't contain Account.h because Account.h contains Transaction.h
//Forward declare the class to avoid circular dependency
//PLACEHOLDER transaction class
class Transaction
{
	
public:
	int acc1ID;
	int acc2ID;
	float amount;
	Transaction(int acc1ID, int acc2ID, float amount);
};

