#pragma once
#include <string>
#include <map>
#include "Bank.h"
#include "UI.h"
#include "FileManager.h"

/**
 * @class ApplicationManager
 * @brief Manages the lifecycle and core functionality of the banking application
 *
 * This class serves as the central controller for the banking application,
 * handling initialization, data loading/saving, and UI management.
 */
class ApplicationManager {
private:
    UI* bankUI;                      // User interface component
    Bank* bank;                      // Core banking logic component
    std::string dataFileName;        // File name for data persistence
    bool isInitialized;              // Flag to track initialization status

public:
    /**
     * @brief Constructor for ApplicationManager
     * @param fileName The name of the data file (without extension)
     */
    ApplicationManager(const std::string& fileName = "bankData");

    /**
     * @brief Destructor for ApplicationManager
     */
    ~ApplicationManager();

    /**
     * @brief Initialize the application components
     * @return True if initialization was successful, false otherwise
     */
    bool initialize();

    /**
     * @brief Load data from file
     * @return True if data was loaded successfully, false otherwise
     */
    bool loadData();

    /**
     * @brief Save data to file
     * @return True if data was saved successfully, false otherwise
     */
    bool saveData();

    /**
     * @brief Run the application main loop
     */
    void run();

    /**
     * @brief Get the UI component
     * @return Pointer to the UI component
     */
    UI* getUI() const;

    /**
     * @brief Get the Bank component
     * @return Pointer to the Bank component
     */
    Bank* getBank() const;

    /**
     * @brief Set the data file name
     * @param fileName The name of the data file (without extension)
     */
    void setDataFileName(const std::string& fileName);
};