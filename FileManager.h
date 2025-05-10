#pragma once
#include "user.h"
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
class FileManager
{
public:
	static void saveData(std::map<std::string, Customer>& customers, std::string& filename);
	//static void saveAccounts(std::map<int, Account*>& accounts, std::string& filename);
	//static void saveUsers(std::map<std::string, User*>& users, std::string& filename);

	static void loadData(std::map<std::string, Customer>& customers, std::string& filename);
	//static void loadAccounts(std::map<int, Account*>& accounts, std::string& filename);
	//static void loadUsers(std::map<std::string, User*>& users, std::string& filename);
	
};

