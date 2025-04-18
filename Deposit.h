#pragma once
#include <iostream>
#include "Account.h"
#include "UI.h"
using namespace std;
class Deposit
{
	UI display;
	string message;
public:
	void start(Account& acc, float amount);
};

