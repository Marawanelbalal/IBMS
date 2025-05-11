#include "ApplicationManager.h"
#include <iostream>

ApplicationManager::ApplicationManager(const std::string& fileName) :
    bankUI(nullptr),
    bank(nullptr),
    dataFileName(fileName),
    isInitialized(false) {
    // Constructor initializes pointers to null and sets the data file name
}

ApplicationManager::~ApplicationManager() {
    // Clean up resources
    if (bankUI != nullptr) {
        delete bankUI;
        bankUI = nullptr;
    }

    // Note: Bank object is owned by UI and will be deleted by UI's destructor
}

bool ApplicationManager::initialize() {
    try {
        // Create UI instance
        bankUI = new UI();

        // Initialize the bank through UI
        bankUI->initializeBank();

        // Get reference to the bank
        bank = bankUI->getBank();

        if (!bank) {
            std::cerr << "Failed to initialize bank component!" << std::endl;
            return false;
        }

        isInitialized = true;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error during initialization: " << e.what() << std::endl;
        return false;
    }
}

bool ApplicationManager::loadData() {
    if (!isInitialized) {
        std::cerr << "Application not initialized! Call initialize() first." << std::endl;
        return false;
    }

    try {
        // Get reference to customers map
        std::map<std::string, Customer>& customers = bank->getCustomers();
        std::map<int, Account*>& accounts = bank->getAccounts();

        // Load data using FileManager
        FileManager::loadData(customers,accounts, dataFileName);

        // Update UI with loaded data
        bankUI->load(customers,accounts);

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        return false;
    }
}

bool ApplicationManager::saveData() {
    if (!isInitialized) {
        std::cerr << "Application not initialized! Call initialize() first." << std::endl;
        return false;
    }

    try {
        // Get reference to customers map
        std::map<std::string, Customer>& customers = bank->getCustomers();

        // Save data using FileManager
        FileManager::saveData(customers, dataFileName);

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving data: " << e.what() << std::endl;
        return false;
    }
}

void ApplicationManager::run() {
    if (!isInitialized) {
        std::cerr << "Application not initialized! Call initialize() first." << std::endl;
        return;
    }

    // Start the UI main loop
    bankUI->run();

    // Save data before exiting
    saveData();
}

UI* ApplicationManager::getUI() const {
    return bankUI;
}

Bank* ApplicationManager::getBank() const {
    return bank;
}

void ApplicationManager::setDataFileName(const std::string& fileName) {
    dataFileName = fileName;
}