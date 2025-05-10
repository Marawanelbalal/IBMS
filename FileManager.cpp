#include "FileManager.h"

void FileManager::saveData(std::map<std::string, Customer>& customers, std::string& filename)
{
	std::ofstream outFile(filename+".txt", std::ios::out);
	if (!outFile.is_open()) {
		std::cout << "Error opening file for writing!" << std::endl;
		return;
	}

		for (const auto& customerPair : customers) {
			Customer customer = customerPair.second;
			vector<Account*> accounts = customer.getAccounts();
			outFile << "Customer|" << customer.getName() << "|" << customer.getUserID() << "|" << customer.getPassword() << "|" << customer.getPhoneNumber() << "\n";

			if (not accounts.empty()) {

				for (Account* acc : accounts) {
					outFile << "Account|" << acc->getCurrency() << "|" << acc->getOwner() << "|" << acc->getBalance() << "|" << acc->getAccountNumber() << "|" << acc->getAccountType() << "\n";
					vector<Transaction> transactions = acc->getTransactionHistory();
					if (not transactions.empty()) {
						for (const Transaction T : transactions) {
							vector<std::string> involvedAccounts = T.getInvolvedAccounts();
							outFile << "Transaction|" << T.getTransactionID() << "|" << T.getAmount() << "|" << T.getTransactionType() << "|" << involvedAccounts[0] << "|" << involvedAccounts[1] << "\n";
						} outFile << "EndTransaction\n";
					}

					outFile << "EndAccount\n";
				}
			} else outFile << "No Accounts\n";
			outFile << "EndCustomer\n";			
		}
}

void FileManager::loadData(map<std::string, Customer>& customers, std::string& filename) {
	std::ifstream inFile(filename + ".txt");
	if (!inFile.is_open()) {
		std::cout << "Couldn't open file!\n";
		return;
	}
	else std::cout << "File loaded!";
	std::string currentLine;
	Customer currentCustomer;
	Account* currentAccount = nullptr;
	Transaction currentTransaction;
	vector<string> currentInvolvedAccounts;
	while (std::getline(inFile, currentLine)) {
		std::stringstream ss(currentLine);
		std::string part;
		std::vector<std::string> parts;

		while (std::getline(ss, part, '|')) {
			parts.push_back(part);
		}
		if (parts[0] == "Customer") {
			currentCustomer = Customer(parts[1], parts[2], parts[3], parts[4]);
		}

		else if (parts[0] == "Account") {
			currentAccount = new Account(parts[1],parts[2],stod(parts[3]),stoi(parts[4]),parts[5]);
		}
		else if (parts[0] == "Transaction") {
			currentInvolvedAccounts = { parts[4],parts[5] };
			currentTransaction = Transaction(parts[1], stod(parts[2]), parts[3], currentInvolvedAccounts);
			currentAccount->addTransaction(currentTransaction);
		}
		else if (parts[0] == "EndTransaction") {
			//DoNothing
		}
		else if (parts[0] == "EndAccount") {
			currentCustomer.addAccount(currentAccount);
			currentAccount = nullptr;
		}
		else if (parts[0] == "No Accounts" or parts[0] == "EndCustomer") {
			customers[currentCustomer.getName()] = currentCustomer;
			currentCustomer = Customer();
		}


	}

}