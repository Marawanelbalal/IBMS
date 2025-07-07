# Islamic Bank Management System (IBMS)

**CSAI 151 - Project Spring 2025**  

## 📋 Project Overview

The Islamic Bank Management System (IBMS) is a comprehensive banking simulation that replicates real-world banking operations. This system provides a secure and efficient platform for managing various banking operations including account management, transactions, loans, and multi-currency support.

## 👥 Team Members

| Name | Student ID | Email |
|------|------------|-------|
| Almoatasembellah Aboubakr Jafer | 202400993 | s-almoatasembellah.gafer@zewailcity.edu.eg |
| Marawan Abdulrahim | 202402293 | s-marawan.elbalal@zewailcity.edu.eg |
| Rabie Al Sayed Mosa | 202400113 | s-rabie.mosa@zewailcity.edu.eg |
| Youssuf Hosameldin Mohammed | 202402592 | s-youssuf.hossameldin@zewailcity.edu.eg |

**Team Email:** s-almoatasembellah.gafer@zewailcity.edu.eg

## 🏦 System Features

### Core Banking Operations
- **Account Management**: Create and manage multiple bank accounts
- **Transactions**: Perform deposits, withdrawals, and transfers
- **Savings Accounts**: Generate yearly returns on savings
- **Loan System**: Apply for loans with staff approval process
- **Multi-Currency Support**: Each account can be assigned a specific currency
- **Transaction History**: Complete audit trail of all transactions

### User Management
- **Customer Portal**: Account viewing, transactions, and profile management
- **Administrator Panel**: System-wide operations and user management
- **Secure Authentication**: Login/logout functionality with password management

### System Features
- **Data Persistence**: File-based data storage with backup capabilities
- **Security**: Data encryption and access control
- **Reporting**: Comprehensive system and account reports
- **Error Handling**: Robust exception management

## 🏗️ System Architecture

### Core Classes

#### Account Management
- **Account Class**: Represents individual bank accounts with deposit, withdrawal, and interest calculation capabilities
- **Transaction Class**: Handles individual financial operations with validation and audit trail
- **Bank Class**: Manages all accounts and system-wide operations

#### User Management
- **User Class**: Base class for all system users with common authentication features
- **Administrator Class**: Bank staff with system management privileges
- **Customer Class**: Regular bank clients with account access

#### Operations Framework
- **Operation Classes**: Modular design for banking operations including:
  - LoginOperation
  - RegisterOperation
  - DepositOperation
  - WithdrawalOperation
  - TransferOperation
  - BalanceInquiryOperation
  - TransactionHistoryOperation
  - AccountCreationOperation
  - AccountDeletionOperation
  - ReportGenerationOperation

#### System Management
- **File Manager Class**: Handles data persistence, backup, and encryption
- **Application Manager Class**: Coordinates system components and manages application lifecycle
- **UI Class**: Manages user interface operations and display

## 🚀 Getting Started

### Prerequisites
- C++ compiler (C++11 or later)
- Standard Template Library (STL)

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Marawanelbalal/IBMS.git
   cd IBMS
   ```

2. Compile the project:
   ```bash
   g++ -o IBMS main.cpp
   ```

3. Run the application:
   ```bash
   ./IBMS
   ```

## 💡 Usage

### For Customers
1. **Login** with your credentials
2. **View Accounts** to see your current balances
3. **Make Transactions** (deposits, withdrawals, transfers)
4. **Apply for Loans** through the system
5. **Check Transaction History** for account activity

### For Administrators
1. **Login** with admin credentials
2. **Manage Users** (create, delete, reset passwords)
3. **View System Reports** for bank overview
4. **Approve Loans** from the loan fund
5. **Modify System Settings** as needed

## 📊 Project Structure

```
ibms-project/
├── src/
│   ├── core/
│   │   ├── Account.cpp
│   │   ├── Transaction.cpp
│   │   └── Bank.cpp
│   ├── users/
│   │   ├── User.cpp
│   │   ├── Administrator.cpp
│   │   └── Customer.cpp
│   ├── operations/
│   │   ├── Operation.cpp
│   │   ├── LoginOperation.cpp
│   │   └── [other operations]
│   ├── managers/
│   │   ├── FileManager.cpp
│   │   └── ApplicationManager.cpp
│   └── ui/
│       └── UI.cpp
├── include/
│   └── [header files]
├── data/
│   └── [data files]
├── docs/
│   └── [documentation]
└── README.md
```

## 🤝 Contributing

This is an academic project for CSAI 151. Contributions are limited to team members listed above.

## 📝 License

This project is developed for educational purposes as part of CSAI 151 coursework.

## 📞 Contact

For questions or issues, please contact the team leader at: s-almoatasembellah.gafer@zewailcity.edu.eg

---

**Note**: This system is designed for educational purposes and simulates banking operations. It is not intended for actual financial transactions.
