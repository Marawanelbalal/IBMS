#include "findAccount.h"
#include <string>
#include <stdexcept>
using namespace std;

Account& Customer::getAccountWithID(int accID) {
    for (Account& acc : Accounts) {
        if (acc.getAccountNumber() == accID) {
            return acc;
        }
    }
    throw runtime_error("Account not found: " + to_string(accID));
}