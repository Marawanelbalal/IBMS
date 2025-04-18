#pragma once
#include "Account.h"
#include "UI.h"


class BalanceInquiry
{
	UI display;
	string message;
public:
	void start(Account& acc);
};

