#pragma once
#include "Account.h"
#include "UI.h"


class Withdraw
{
	UI display;
	string message;
public:
	void start(Account& acc, float amount);
};

