//using namespace std;
//
//int main() {
//    // Create a bank instance
//    UI displayer;
//    Bank bank(&displayer);
//
//    // Initialize demo data
//    bank.initializeDemoData();
//
//    // Display all users and accounts
//    bank.viewAllUsers();
//    bank.viewAllAccounts();
//
//    // Get customers by name
//    Customer* customer1 = bank.getCustomerByName("John Doe1");
//    Customer* customer2 = bank.getCustomerByName("John Doe2");
//
//    if (customer1 && customer2) {
//        // Display initial account information
//        cout << "Initial account balances:" << endl;
//        customer1->viewOwnAccounts();
//        customer2->viewOwnAccounts();
//
//        // Get account IDs
//        vector<Account> accounts1 = customer1->getAccounts();
//        vector<Account> accounts2 = customer2->getAccounts();
//
//        if (!accounts1.empty() && !accounts2.empty()) {
//            int acc1Id = accounts1[0].getAccountNumber();
//            int acc2Id = accounts1[1].getAccountNumber();
//            int acc3Id = accounts2[0].getAccountNumber();
//
//            // Perform transfers
//            cout << "\nTransferring 200 from acc1 to acc2..." << endl;
//            bank.transferMoney("John Doe1", acc1Id, "John Doe1", acc2Id, 200.0);
//
//            cout << "\nTransferring 50 from acc2 to acc3..." << endl;
//            bank.transferMoney("John Doe1", acc2Id, "John Doe2", acc3Id, 50.0);
//
//            cout << "\nTransferring 100 from acc3 to acc1..." << endl;
//            bank.transferMoney("John Doe2", acc3Id, "John Doe1", acc1Id, 100.0);
//
//            bank.transferMoney("John Doe1", acc1Id, "John Doe2", acc3Id, 50.0);
//
//            // Display final account information
//            cout << "\nFinal account balances:" << endl;
//            customer1->viewOwnAccounts();
//            customer2->viewOwnAccounts();
//        }
//    }
//
//    return 0;
//}
#include <iostream>
#include "ApplicationManager.h"

int main() {
    // Create the application manager with the data file name
    ApplicationManager appManager("sampleData2");

    // Initialize the application components
    if (!appManager.initialize()) {
        std::cerr << "Failed to initialize the application. Exiting..." << std::endl;
        return 1;
    }

    // Load data from file
    if (!appManager.loadData()) {
        std::cout << "Warning: Could not load data from file. Starting with empty database." << std::endl;
    }

    // Run the application
    appManager.run();

    std::cout << "Application terminated successfully." << std::endl;
    return 0;
}