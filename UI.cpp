#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include "UI.h"
#include "Bank.h"
#include "operation.h"

using namespace std;

    
    bool loggedIn = false;
    string currentUserRole = "";
    string currentUsername = "";
    UI::UI() : IBMS(nullptr){};
    UI::~UI() {
        if (IBMS != nullptr) delete IBMS;

    }

    void UI::initializeBank() {
        if (IBMS == nullptr) {
            IBMS = new Bank(this);
        }
        
    }
    void UI::load(map<std::string, Customer>& customers, std::map<int, Account*>& accounts) {
        IBMS->setCustomers(customers);
    }
    Bank* UI::getBank() const {
        return IBMS;
    }
    Customer* UI::getCurrentCustomer() {
        map<std::string, Customer> customers = IBMS->getCustomers();
        Customer* currentCustomer = new Customer(customers[currentUsername]);
        return currentCustomer;
    }

    // Helper methods
    void UI::waitForEnter() const {
        cout << "\n   Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int UI::getIntInput() const {
        int choice;
        cin >> choice;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "   Invalid input. Please enter a number: ";
            cin >> choice;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }

    double UI::getDoubleInput() const {
        double amount;
        cin >> amount;
        while (cin.fail() || amount < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "   Invalid input. Please enter a valid positive amount: ";
            cin >> amount;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return amount;
    }

    string UI::getTextInput() const {
        string input;
        getline(cin, input);
        return input;
    }


    void UI::clearScreen() const {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void UI::displayHeader() const {
        cout << "\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        cout << "                                       **                             ISLAMIC BANK                        **\n";
        cout << "                                       **                   [With us, do NOT worry FOREVER]               **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        cout << "                                       **     This program is just a work in progress till now. (Phase2)  **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
    }

    void UI::displayWelcome() const {
        if (loggedIn) {
            cout << "\n   Welcome, " << currentUsername << " [" << currentUserRole << "]\n";
        }
        cout << "\n";
    }
    void UI::displayMessage(const string& message) const {
        cout << "\n" << message << "\n";
    }

    void UI::displayError(const string& message) const {
        cout << "\n   [ERROR] " << message << "\n";
    }

    void UI::displaySuccess(const string& message) const {
        cout << "\n   [SUCCESS] " << message << "\n";
    }

    void UI::showLoginScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                         LOGIN SCREEN                            **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();
        cout << "   Username: ";
        string username = getTextInput();

        cout << "   Password: ";
        string password = getTextInput();

        
        
        // Admin login
        if ((username == "admin" || username == "ADMIN") && password == "202400993+") {
            loggedIn = true;
            currentUserRole = "Administrator";
            currentUsername = username;
            displaySuccess("   Login successful as an Administrator");
        }
        else {
            Operation* Op = new LoginOperation(username, password, IBMS);

            if (Op->execute()) {
                loggedIn = true;
                currentUserRole = "Customer";
                currentUsername = username;
                displaySuccess("    Login successful as a costumer");
            }
            else displayError(Op->getMessage());
        }
        waitForEnter();
    }

    void UI::showRegisterScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                   REGISTRATION SCREEN                           **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();


        cout << "   Enter Full Name: ";
        string fullName = getTextInput();

        cout << "   Enter Email: ";
        string email = getTextInput();

        cout << "   Add Phone Number: ";
        string phoneNumber = getTextInput();

        cout << "   Create Username: ";
        string username = getTextInput();

        cout << "   Create Password: ";
        string password = getTextInput();

        cout << "   Confirm Password: ";
        string confirmPassword = getTextInput();

        if (password != confirmPassword) {
            displayError("   Passwords do not match!");
        }
        else {
            displaySuccess("   Registration successful! Welcome to our great Islamic Bank.");
            string userID = to_string(IBMS->generateUniqueAccountId());
     
            IBMS->addUser(userID, username, password, "customer",phoneNumber);

        }

        waitForEnter();
    }

    

    int UI::displayMainMenu() {
        clearScreen();
        displayHeader();

        if (!loggedIn) {
            cout << "                                       **                          MAIN MENU                              **\n";
            cout << "                                       **-----------------------------------------------------------------**\n";
            displayWelcome();


            cout << "   1. Login\n";
            cout << "   2. Register\n\n";
            cout << "   0. Exit\n\n";

            cout << "   Enter your choice: ";
            return getIntInput();
        }
        else if (currentUserRole == "Administrator") {
            return displayAdminMenu();
        }
        else if (currentUserRole == "Customer") {
            return displayCustomerMenu();
        }

        return -1;
    }

    int UI::displayAdminMenu() {
        //displayHeaderForAdmin();

        cout << "                                       **                     ADMINISTRATOR MENU                          **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";

        displayWelcome();
        cout << "   1. Create User Account\n";
        cout << "   2. Delete User Account\n";
        cout << "   3. View All Accounts\n";
        cout << "   4. View All Users\n";
        cout << "   5. Generate Reports\n";
        cout << "   6. Modify System Settings\n";
        cout << "   7. Reset User Password\n";
        cout << "   8. Approve Loan Applications\n";
        cout << "   9. Manage Loan Fund\n";
        cout << "   10. Currency Exchange Rates\n\n";
        cout << "   99. Logout\n\n";
        cout << "   0. Exit\n\n";

        cout << "   Enter your choice: ";
        return getIntInput();
    }

    int UI::displayCustomerMenu() {
        cout << "                                       **                        CUSTOMER MENU                            **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";

        displayWelcome();
        cout << "   1. View My Accounts\n";
        cout << "   2. Create New Account\n";
        cout << "   3. Deposit Money\n";
        cout << "   4. Withdraw Money\n";
        cout << "   5. Transfer Money\n";
        cout << "   6. View Transaction History\n";
        cout << "   7. Apply for Loan\n";
        cout << "   8. View Loan Status\n";
        cout << "   9. Update Profile Information\n";
        cout << "   10. Currency Exchange\n";
        cout << "   11. Balance Inquiry\n\n";
        cout << "   99. Logout\n\n";
        cout << "   0. Exit\n\n";

        cout << "   Enter your choice: ";
        return getIntInput();
    }

    void UI::showAccountCreationScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                    CREATE A NEW ACCOUNT                         **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";

        displayWelcome();
        cout << "   Select Account Type:\n";
        cout << "   1. Savings Account\n";
        cout << "   2. Checking Account\n";
        cout << "   3. Investment Account\n";
        cout << "   Enter your choice: ";
        int accountType = getIntInput();
        string accountTypeStr;
        switch (accountType) {
        case 1:
            accountTypeStr = "Savings Account";
            break;
        case 2:
            accountTypeStr = "Checking Account";
            break;
        case 3:
            accountTypeStr = "Investment Account";
            break;
        default:
            displayError("Invalid Number Entered");
            break;
        }

        cout << "   Select Currency:\n";
        cout << "   1. USD (US Dollar)\n";
        cout << "   2. EUR (Euro)\n";
        cout << "   3. GBP (British Pound)\n";
        cout << "   4. LE  (Egyptian Pound)\n";
        cout << "   5. AED (UAE Dirham)\n";
        cout << "   Enter your choice: ";
        int currency = getIntInput();
        string currencystr;
        switch (currency) {
        case 1:
            currencystr = "USD";
            break;
        case 2:
            currencystr = "EUR";
            break;
        case 3:
            currencystr = "GBP";
            break;
        case 4:
            currencystr = "LE";
            break;
        case 5:
            currencystr = "AED";
            break;
        default:
            displayError("Invalid Currency");
            break;
        }
        cout << "   Initial Deposit Amount: ";
        double initialAmount = getDoubleInput();
        // make this create a real account.
        displaySuccess("Account created successfully!");
        currentCustomer = getCurrentCustomer();
        int accountID = IBMS->generateUniqueAccountId();
        IBMS->createAccount(currencystr, currentUsername, initialAmount,accountID,accountTypeStr);
        IBMS->addAccountToCustomer(accountID, currentUsername);
        cout << "   Account Details:\n";
        cout << "   Account Number: " << 1000000 + rand() % 9000000 << "\n";
        cout << "   Account Type: "
            << (accountType == 1 ? "Savings" : accountType == 2 ? "Checking" : "Investment") << "\n";
        cout << "   Currency: "
            << (currency == 1 ? "USD" : currency == 2 ? "EUR" : currency == 3 ? "GBP" : currency == 4 ? "LE" : "AED") << "\n";
        cout << "   Initial Balance: " << fixed << setprecision(2) << initialAmount << "\n";

        waitForEnter();
    }

    void UI::showDepositScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                         DEPOSIT FUNDS                           **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";

        displayWelcome();
        cout << "   Enter Account Number: ";
        int accountNumber = getIntInput();

        cout << "   Enter Deposit Amount: ";
        double amount = getDoubleInput();

        //Get the account selected by the user.
        selectedAccount = IBMS->getAccountById(accountNumber);

        //Update the pointer pointing at the current customer.
        currentCustomer = getCurrentCustomer();

        Operation* Operator = new Deposit();

        Operator->loadParameters(currentCustomer,selectedAccount, amount);

        //The operation has a validation function, if the user enters an incorrect account number, an error will show.
        if (Operator->execute()) {
            displaySuccess("   Deposit completed successfully!");
            cout << "   Amount " << fixed << setprecision(2) << amount << " deposited to account #" << accountNumber << "\n";
        }
        else displayError(Operator->getMessage());

        waitForEnter();
        delete Operator;

    }

    //The same logic for the deposit applies for the withdraw and balance inquiry operations.
    void UI::showWithdrawalScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                      WITHDRAW FUNDS                             **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        cout << "   Enter Account Number: ";
        selectedAccountNumber = getIntInput();

        cout << "   Enter Withdrawal Amount: ";
        double amount = getDoubleInput();

        selectedAccount = IBMS->getAccountById(selectedAccountNumber);

        currentCustomer = getCurrentCustomer();

        Operation* Operator = new Withdraw();

        Operator->loadParameters(currentCustomer,selectedAccount, amount);

        if (Operator->execute()) {
            displaySuccess("   Withdrawal completed successfully!");

            cout << "   Amount " << fixed << setprecision(2) << amount << " withdrawn from account #" << selectedAccountNumber << "\n";
        }
        else displayError(Operator->getMessage());
        waitForEnter();
        delete Operator;

    }

    void UI::showInquiryScreen() {

        clearScreen();
        displayHeader();
        cout << "                                       **                      BALANCE INQUIRY SCREEN                     **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();
        cout << "   Enter Account Number: ";
        selectedAccountNumber = getIntInput();

        selectedAccount = IBMS->getAccountById(selectedAccountNumber);

        currentCustomer = getCurrentCustomer();

        Operation* Operator = new BalanceInquiry();

        Operator->loadParameters(currentCustomer,selectedAccount);

        if (Operator->execute()) cout << Operator->getMessage();
        else displayError("User does not own account.");
        
        waitForEnter();
        delete Operator;
    }

    void UI::showUserAccounts() {
        clearScreen();
        displayHeader();
        cout << "                                       **                       USER ACCOUNTS SCREEN                      **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        currentCustomer = getCurrentCustomer();

        vector<Account*> Accounts = currentCustomer->getAccounts();

        if (Accounts.empty()) {
            displayError("User does not own any accounts to show.");
        }
        else {
            displayMessage("For Customer: " + currentUsername + "\n" + "The available accounts are: " + "\n");
            //Loop through the accounts vector using this format: for(type iterator : vector)
            //Use a pointer (Account*) instead of the actual class, since objects are not easy to handle like primitive data types.

            for (const Account* acc : Accounts) {
            displayMessage(to_string(acc->getAccountNumber()) + " : " + to_string(acc->getBalance()) + " " + acc->getCurrency() + "\n");
            }

        }
        waitForEnter();
    }

    void UI::showTransferScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                       TRANSFER FUNDS                            **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        cout << "   Enter Source Account Number: ";
        string sourceAccount = getTextInput();
  
        cout << "   Enter Destination Account Number: ";
        string destAccount = getTextInput();

        cout << "   Enter Transfer Amount: ";
        double amount = getDoubleInput();

        Operation* Operator = new TransferOperation(currentCustomer,sourceAccount,destAccount,amount,IBMS);
        if (Operator->execute()) {

            
        // make this process a real transfer.
            displaySuccess("   Transfer completed successfully!");
            cout << "   Amount " << fixed << setprecision(2) << amount
                << " transferred from account #" << sourceAccount
                << " to account #" << destAccount << "\n";
        }
        else displayError(Operator->getMessage());

        waitForEnter();
    }

    void UI::showTransactionDetails(int transactionId, const string& type, double amount,
        const string& accountInfo, const string& date) {
        cout << "                                       **                     TRANSACTION DETAILS                         **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        cout << "   Transaction ID: " << transactionId << "\n";
        cout << "   Type: " << type << "\n";
        cout << "   Amount: " << fixed << setprecision(2) << amount << "\n";
        cout << "   Account Information: " << accountInfo << "\n";
        cout << "   Date/Time: " << date << "\n";

        waitForEnter();
    }

    void UI::showTransactionHistory() {
        clearScreen();
        displayHeader();
        cout << "                                       **                     TRANSACTION HISTORY                         **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        cout << "   Enter Account Number: ";

        string accountNumber = getTextInput();

        bool foundAccount = false;
  
        vector<Account*> accounts = currentCustomer->getAccounts();
        for (Account* acc : accounts) {
            if (to_string(acc->getAccountNumber()) == accountNumber) {
                foundAccount = true;
                vector<Transaction> Transactions = acc->getTransactionHistory();
                if (Transactions.empty()) {
                    displayError("Account: " + accountNumber + " does not have any transactions to show.");
                }
                else {
             vector <string> involvedAccounts;
                    double amount;
                    for (const Transaction& Tran : Transactions) {
                        involvedAccounts = Tran.getInvolvedAccounts();
                        amount = Tran.getAmount();
                        displayMessage("Transferred " + to_string(amount) + " from account: " + involvedAccounts[0] + " to account: " + involvedAccounts[1] + "\n");
                    }
                
                }
            }
        }
        if (!foundAccount) displayError("Account not found.");           
        
        Operation* Operator = new TransactionHistoryOperation(currentCustomer,accountNumber,IBMS);
        if (Operator->execute()) {

        }
        else displayError(Operator->getMessage());
        waitForEnter();
    }

    void UI::showLoanApplicationScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                   LOAN APPLICATION FORM                         **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";

        displayWelcome();

        cout << "   Enter Account Number for Loan Association: ";
        int accountNumber = getIntInput();

        cout << "   Loan Amount Requested: ";
        double loanAmount = getDoubleInput();

        cout << "   Loan Purpose:\n";
        cout << "   1. Home Purchase\n";
        cout << "   2. Business Investment\n";
        cout << "   3. Education\n";
        cout << "   4. Vehicle Purchase\n";
        cout << "   5. Other\n";
        cout << "   Enter your choice: ";
        int purpose = getIntInput();

        cout << "   Loan Duration (in months): ";
        int duration = getIntInput();

        cout << "   Monthly Income: ";
        double income = getDoubleInput();

        // loan application.
        displaySuccess("   Loan application submitted successfully!");
        cout << "   Application will be reviewed by bank staff.\n";
        cout << "   Application Reference Number: " << "LN" << 10000 + rand() % 90000 << "\n";

        waitForEnter();
    }

    void UI::showLoanApprovalScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                  LOAN APPLICATIONS REVIEW                       **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        // loan application

        cout << "\n   Enter Application Reference Number to review: ";
        string refNumber = getTextInput();

        int decision = getIntInput();

        if (decision == 1) {
            displaySuccess("   Loan approved successfully!");
        }
        else if (decision == 2) {
            cout << "   Reason for rejection: ";
            string reason = getTextInput();
            displayMessage("Loan application rejected.");
        }
        else {
            cout << "   Additional information requested: ";
            string info = getTextInput();
            displayMessage("   Request for additional information sent to customer.");
        }

        waitForEnter();
    }

    void UI::logout() {
        loggedIn = false;
        currentUserRole = "";
        currentUsername = "";
        displayMessage("   Logged out successfully");
        waitForEnter();
    }

    void UI::showCreateUserScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                      CREATE USER ACCOUNT                         **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        cout << "   Enter User ID: ";
        string userId = getTextInput();

        cout << "   Enter Full Name: ";
        string fullName = getTextInput();

        cout << "   Add Phone Number: ";
        string phoneNumber = getTextInput();

        cout << "   Create Password: ";
        string password = getTextInput();

        cout << "   Select Role:\n";
        cout << "   1. Administrator\n";
        cout << "   2. Customer\n";
        cout << "   Enter your choice: ";
        int roleChoice = getIntInput();

        string role = (roleChoice == 1) ? "admin" : "customer";

        bool success = IBMS->addUser(userId, fullName, password, role,phoneNumber);

        if (success) {
            displaySuccess("User account created successfully!");
        } else {
            displayError("Failed to create user account. User ID may already exist.");
        }

        waitForEnter();
    }

    void UI::showDeleteUserScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                      DELETE USER ACCOUNT                         **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        // Show all users first to help the admin select the correct user
        displayMessage("Current users in the system:");
        IBMS->viewAllUsers();
        
        cout << "\n   Enter Username to delete: ";
        string username = getTextInput();

        if (username == currentUsername) {
            displayError("You cannot delete your own account!");
            waitForEnter();
            return;
        }

        cout << "   Are you sure you want to delete user '" << username << "'? (y/n): ";
        string confirmation = getTextInput();

        if (confirmation == "y" || confirmation == "Y") {
            bool success = IBMS->deleteUser(username);

            
            if (success) {
                displaySuccess("User account deleted successfully!");
            } else {
                displayError("Failed to delete user account. User not found or could not be deleted.");
            }
        } else {
            displayMessage("Operation cancelled.");
        }

        waitForEnter();
    }

    void UI::showViewAllAccountsScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                      ALL BANK ACCOUNTS                          **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        IBMS->viewAllAccounts();
        
        waitForEnter();
    }

    void UI::showViewAllUsersScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                      ALL SYSTEM USERS                           **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        IBMS->viewAllUsers();
        
        waitForEnter();
    }

    void UI::showResetPasswordScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                     RESET USER PASSWORD                         **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        // Show all users first to help the admin select the correct user ID
        displayMessage("Current users in the system:");
        IBMS->viewAllUsers();
        
        cout << "\n   Enter User ID (not Username) to reset password for: ";
        string userId = getTextInput();

        cout << "   Enter Phone Number: ";
        string phoneNumber = getTextInput();

        cout << "   Enter New Password: ";
        string newPassword = getTextInput();

        cout << "   Confirm New Password: ";
        string confirmPassword = getTextInput();

        if (newPassword != confirmPassword) {
            displayError("Passwords do not match!");
            waitForEnter();
            return;
        }

        bool success = IBMS->resetUserPassword(userId, newPassword,phoneNumber);
        
        if (success) {
            displaySuccess("Password reset successfully! User can now login with the new password.");
        } else {
            displayError("Failed to reset password. User ID not found.");
        }

        waitForEnter();
    }

    // Main application loop
    void UI::run() {
        int choice;

        do {
            choice = displayMainMenu();

            if (!loggedIn) {
                switch (choice) {
                case 1:
                    showLoginScreen();
                    break;
                case 2:
                    showRegisterScreen();
                    break;
                case 0:
                    displayMessage("   Thank you for using IBMS. Goodbye!");
                    break;
                default:
                    displayError("  Invalid choice. Please try again.");
                    waitForEnter();
                }
            }
            else if (currentUserRole == "Administrator") {
                // Admin menu choices
                switch (choice) {
                case 1: // Create User Account
                    showCreateUserScreen();
                    break;
                case 2: // Delete User Account
                    showDeleteUserScreen();
                    break;
                case 3: // View All Accounts
                    showViewAllAccountsScreen();
                    break;
                case 4: // View All Users
                    showViewAllUsersScreen();
                    break;
                case 5: // Generate Reports
                    displayMessage("Generating reports...");
                    waitForEnter();
                    break;
                case 6: // Modify System Settings
                    displayMessage("Modifying system settings...");
                    waitForEnter();
                    break;
                case 7: // Reset User Password
                    showResetPasswordScreen();
                    break;
                case 8: // Approve Loan Applications
                    showLoanApprovalScreen();
                    break;
                case 9: // Manage Loan Fund
                    displayMessage("Managing loan fund...");
                    waitForEnter();
                    break;
                case 10: // Currency Exchange Rates
                    displayMessage("Setting currency exchange rates...");
                    waitForEnter();
                    break;
                case 99: // Logout
                    logout();
                    break;
                case 0: // Exit
                    displayMessage("Thank you for using IBMS. Goodbye!");
                    break;
                default:
                    displayError("Invalid choice. Please try again.");
                    waitForEnter();
                }
            }
            else if (currentUserRole == "Customer") {
                // Customer menu choices
                switch (choice) {
                case 1: { // View My Accounts
                    showUserAccounts();
                    break;
                }
                case 2: // Create New Account
                    showAccountCreationScreen();
                    break;
                case 3: { // Deposit Money
                    showDepositScreen();
                    break;
                }
                case 4: // Withdraw Money
                    showWithdrawalScreen();
                    break;
                case 5: // Transfer Money
                    showTransferScreen();
                    break;
                case 6: // View Transaction History
                    showTransactionHistory();
                    break;
                case 7: // Apply for Loan
                    showLoanApplicationScreen();
                    break;
                case 8: // View Loan Status
                    displayMessage("Viewing loan status...");
                    waitForEnter();
                    break;
                case 9: // Update Profile Information
                    displayMessage("Updating profile information...");
                    waitForEnter();
                    break;
                case 10: // Currency Exchange
                    displayMessage("Performing currency exchange...");
                    waitForEnter();
                    break;
                case 11:
                    showInquiryScreen();
                    break;
                case 99: // Logout2
                    logout();
                    break;
                case 0: // Exit
                    displayMessage("Thank you for using IBMS. Goodbye!");
                    break;
                default:
                    displayError("Invalid choice. Please try again.");
                    waitForEnter();
                }
                }

            } while (choice != 0);
        }

  
