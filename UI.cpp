#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include "UI.h"
#include "Bank.h"
#include "Deposit.h"

using namespace std;

    
    bool loggedIn = false;
    string currentUserRole = "";
    string currentUsername = "";
    UI::UI() : IBMS(nullptr) {};
    UI::~UI() {
        if (IBMS != nullptr) delete IBMS;
    }
    void UI::initializeBank() {
        if (IBMS == nullptr) {
            IBMS = new Bank(this);
        }
        
    }
    Customer* UI::getCurrentCustomer() {
        map<std::string, Customer> customers = IBMS->getCustomers();
        Customer* currentCustomer = new Customer(customers[currentUsername]);
        return currentCustomer;
    }
    int UI::generateUniqueAccountId() {
        // Generate a random 5-digit account ID
        map<int, Account> accounts = IBMS->getAccounts();
        int accountId;
        do {
            accountId = 10000 + std::rand() % 90000;
        } while (accounts.find(accountId) != accounts.end()); // Ensure it's unique

        return accountId;
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
        cout << "                                       **                         ISLAMIC BANK                            **\n";
        cout << "                                       **                [With us do NOT be worry FOREVER]                **\n";
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



        // simulate a successful login. kindly replace it with the real data after made the admin class, bro.
        if (username == "admin" || username == "ADMIN" && password == "202400993+") {
            loggedIn = true;
            currentUserRole = "Administrator";
            currentUsername = username;
            displaySuccess("   Login successful as an Administrator");
        }



        else {
            map<std::string, Customer> currentCustomers = IBMS->getCustomers();

            if  (currentCustomers.count(username) > 0) {
                Customer selectedCustomer = currentCustomers[username];
                if (selectedCustomer.getPassword() == password) {
                    loggedIn = true;
                    currentUserRole = "Customer";
                    currentUsername = username;
                    displaySuccess("   Login successful as a Customer");
                }
                else { displayError("   Invalid Username/Password"); }
            }
            else {
                displayError("   Invalid Username");
            }
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
            string userID = to_string(generateUniqueAccountId());
     
            IBMS->addUser(userID, username, password, "customer");

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
        cout << "   10. Currency Exchange\n\n";
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
        int accountID = generateUniqueAccountId();
        IBMS->createAccount(currencystr, currentUsername, initialAmount,accountID);
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

        // make this process a real deposit.
        displaySuccess("   Deposit completed successfully!");
        cout << "   Amount " << fixed << setprecision(2) << amount << " deposited to account #" << accountNumber << "\n";
        Account* selectedAccount = IBMS->getAccountById(accountNumber);
        Deposit D;

        waitForEnter();
    }

    void UI::showWithdrawalScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                      WITHDRAW FUNDS                             **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        cout << "   Enter Account Number: ";
        int accountNumber = getIntInput();

        cout << "   Enter Withdrawal Amount: ";
        double amount = getDoubleInput();

        // make this process a real withdrawal.
        displaySuccess("   Withdrawal completed successfully!");
        cout << "   Amount " << fixed << setprecision(2) << amount << " withdrawn from account #" << accountNumber << "\n";

        waitForEnter();
    }

    void UI::showTransferScreen() {
        clearScreen();
        displayHeader();
        cout << "                                       **                       TRANSFER FUNDS                            **\n";
        cout << "                                       **-----------------------------------------------------------------**\n";
        displayWelcome();

        cout << "   Enter Source Account Number: ";
        int sourceAccount = getIntInput();

        cout << "   Enter Destination Account Number: ";
        int destAccount = getIntInput();

        cout << "   Enter Transfer Amount: ";
        double amount = getDoubleInput();

        // make this process a real transfer.
        displaySuccess("   Transfer completed successfully!");
        cout << "   Amount " << fixed << setprecision(2) << amount
            << " transferred from account #" << sourceAccount
            << " to account #" << destAccount << "\n";

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
        int accountNumber = getIntInput();

        // transaction data

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
                    displayMessage("Creating user account...");
                    waitForEnter();
                    break;
                case 2: // Delete User Account
                    displayMessage("Deleting user account...");
                    waitForEnter();
                    break;
                case 3: // View All Accounts
                    displayMessage("Viewing all accounts...");
                    waitForEnter();
                    break;
                case 4: // View All Users
                    displayMessage("Viewing all users...");
                    waitForEnter();
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
                    displayMessage("Resetting user password...");
                    waitForEnter();
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
                    displayMessage("Viewing your accounts...");
                    currentCustomer = getCurrentCustomer();
                    currentCustomer->viewOwnAccounts();
                    waitForEnter();
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

  
