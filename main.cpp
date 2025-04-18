#include <iostream>
#include <vector>
#include <string>
#include "Customer.h"
#include "Account.h"
#include "Transaction.h"
#include "user.h"

using namespace std;

int main() {
    // Create accounts with the correct constructor parameters
    Account acc1("USD", "John Doe1", 500.0, 12345);
    Account acc2("USD", "John Doe1", 1000.0, 67890);
    Account acc3("USD", "John Doe2", 150.0, 11111);

    // Create a customer
    Customer customer1("John Doe1","1019", "1234567890");
    Customer customer2("John Doe1","1020", "1234567890");


    // Add accounts to the customer
    customer1.addAccount(acc1);
    customer1.addAccount(acc2);
    customer2.addAccount(acc3);

    // Display initial account information
    cout << "Initial account balances:" << endl;
    customer1.viewOwnAccounts();
    customer2.viewOwnAccounts();

    // Perform some transfers
    cout << "\nTransferring 200 from acc1 to acc2..." << endl;
    customer1.transferMoney(acc1, acc2,customer1, 200.0);

    cout << "\nTransferring 50 from acc2 to acc3..." << endl;
    customer1.transferMoney(acc2, acc3,customer2, 50.0);

    cout << "\nTransferring 100 from acc3 to acc1..." << endl;
    customer2.transferMoney(acc3, acc1, customer1, 100.0);
    
    customer1.transferMoney(acc1, acc3, customer2, 50.0);
    // Display final account information
    cout << "\nFinal account balances:" << endl;
    customer1.viewOwnAccounts();
    customer2.viewOwnAccounts();


    return 0;
}
