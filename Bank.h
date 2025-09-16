#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include "AVLTree.h"
#include <iostream>
using namespace std;

class Bank {
private:
    AVLTree accounts;   // AVL tree to store accounts
    int nextAccountId = 1;
    int loggedInId = -1;
    const std::string adminPassword = "admin@123";

    bool verifyPinInternal(const Account& acc) const; // internal PIN check

public:
    Bank() {}

    void createAccount(string name, int pin, double initialDeposit);
    void deposit(int id, double amount);
    void withdraw(int id, double amount);
    void showAccount(int id) const;
    void showTransactions(int id) const;
    void updateNextAccountId();
    void showAllAccounts() const;              // show all accounts
    void showAllTransactionHistories() const;

    bool login(int id);
    void logout();
    bool isLoggedIn() const;
    int getLoggedInId() const;
     bool adminLogin(const string& password);
    void adminLogout();

    AVLTree& getAccountsTree() { return accounts; }          // For FileManager
    const AVLTree& getAccountsTree() const { return accounts; }  // const version

    void fundTransfer(int from, int to, double amount);
    void showMiniStatement(int id, int count = 5) const;
    void downloadStatement(int id, const string& filename) const;
    vector<Account> getAccountsByBalance(double minBalance) const;
    vector<Account> getAccountsByName(const string& name) const;
    void searchByName(const string& name) const;
    void searchByBalance(double minBalance, double maxBalance) const;

};

#endif
