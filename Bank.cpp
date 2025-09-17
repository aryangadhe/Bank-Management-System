#include "Bank.h"
#include "Utils.h"
#include <iostream>
using namespace std;

void Bank::createAccount(string name, int pin, double initialDeposit) {
    Account newAcc(nextAccountId, name, pin, initialDeposit);
    accounts.insert(newAcc);
    cout << "Successfully created account with Account ID: "
         << nextAccountId << " for " << name << endl;
    nextAccountId++;
}


bool Bank::verifyPinInternal(const Account& acc) const {
    cout << "Enter PIN: ";
    string inputPin = Utils::getHiddenPin();
    return stoi(inputPin) == acc.getPin();
}

void Bank::deposit(int id, double amount) {
    Account* acc = accounts.search(id);
    if (acc){
        acc -> deposit(amount);
        cout << "Successfully Deposited amount " << amount << endl;
    } 
    else cout << "No account found for ID " << id << endl;
}

void Bank::withdraw(int id, double amount) {
    Account* acc = accounts.search(id);
    if (acc && verifyPinInternal(*acc)) {
        acc->withdraw(amount);
        cout << "Successfully Withdrawed amount " << amount << endl;
    }
    else cout << "No account found or invalid PIN.\n";
}

void Bank::showAccount(int id) const {
    const Account* acc = accounts.search(id);
    if (acc) {
        if (!const_cast<Bank*>(this)->verifyPinInternal(*acc)) return; //convert const to non const
        acc->display();
    } else {
        cout << "No account found for ID " << id << endl;
    }
}

void Bank::showTransactions(int id) const {
    const Account* acc = accounts.search(id);
    if (acc) acc->showAllTransactions();
    else cout << "No account found for ID " << id << endl;
}

bool Bank::login(int id) {
    Account* acc = accounts.search(id);
    if (acc && verifyPinInternal(*acc)) {
        loggedInId = id;
        cout << "Login successful. Welcome, " << acc->getName() << "!\n";
        return true;
    }
    cout << "Login failed.\n";
    return false;
}

void Bank::logout() {
    loggedInId = -1;
    cout << "Logged out successfully.\n";
}

bool Bank::isLoggedIn() const {
    return loggedInId != -1;
}

int Bank::getLoggedInId() const {
    return loggedInId;
}

void Bank::fundTransfer(int fromId, int toId, double amount){
    if(fromId == toId){
        cout << "You cannot transfer to the same account." << endl;
        return;
    }
    Account* fromAcc = accounts.search(fromId);
    Account* toAcc = accounts.search(toId);
    if(!fromAcc || !toAcc){
        cout << "Invalid account IDs." << endl;
        return;
    }
    if(amount <= 0){
        cout << "Please Enter Valid Amount." << endl;
        return;
    }
    if (fromAcc && toAcc && verifyPinInternal(*fromAcc)) {
        fromAcc->withdraw(amount);
        toAcc->deposit(amount);
        cout << "Fund transfer successful.\n";
    } else {
        cout << "Fund transfer failed.\n";
    }
}

void Bank::updateNextAccountId() {
    int maxId = 0;
    accounts.inorderTraversal([&](const Account& acc) {
        if (acc.getId() > maxId) maxId = acc.getId();
    });
    nextAccountId = maxId + 1;
}

void Bank::showMiniStatement(int id, int cnt) const{
    const Account* acc = accounts.search(id);
    if(!acc){
        cout << "No account ID found for id: "<< id << endl;
        return ;
    }

    Transaction* temp = acc -> getHead();
    if(!temp){
        cout << "No transactions available to show" << endl;
        return;
    }

    vector<Transaction*> allTxns;
    while(temp){
        allTxns.push_back(temp);
        temp = temp -> next;
    }

    cout << "----- Mini Statement (Last " << cnt  << " Transactions) for Account ID " << id << " -----" << endl;
    int start = max(0, (int)allTxns.size() - cnt);
    for(int i=allTxns.size()-1; i>=start; i--){
        Transaction* txn = allTxns[i];
        cout << txn -> transactionId << " | "
             << txn -> type << " | "
             << txn -> amount << " | "
             << txn -> timestamp << endl;
    } 
    cout << "-------------------------------------------------" << endl;
}

vector<Account> Bank::getAccountsByBalance(double minBalance) const {
    return accounts.searchByBalance(minBalance);
}

vector<Account> Bank::getAccountsByName(const string& name) const {
    return accounts.searchByName(name);
}

// ================= Search by Name =================
void Bank::searchByName(const string& name) const {
    cout << "Searching for accounts with name: " << name << "\n";
    bool found = false;

    accounts.inorderTraversal([&](const Account& acc) {
        if (acc.getName() == name) {
            acc.display();
            found = true;
        }
    });

    if (!found) {
        cout << "No accounts found with name: " << name << endl;
    }
}

// ================= Search by Balance =================
void Bank::searchByBalance(double minBalance) const {
    cout << "Searching for accounts with balance between "
         << minBalance << "\n";
    bool found = false;

    accounts.inorderTraversal([&](const Account& acc) {
        double bal = acc.getBalance();
        if (bal >= minBalance) {
            acc.display();
            found = true;
        }
    });

    if (!found) {
        cout << "No accounts found in the given balance range." << endl;
    }
}

bool Bank::adminLogin(const string& password) {
    if(password == adminPassword) {
        cout << "Admin login successful.\n";
        return true;
    }
    cout << "Admin login failed.\n";
    return false;
}

void Bank::adminLogout() {
    cout << "Admin logged out successfully.\n";
}

void Bank::showAllAccounts() const {
    accounts.inorderTraversal([](const Account& acc){
        acc.display();
    });
}

// Show all transaction histories
void Bank::showAllTransactionHistories() const {
    accounts.inorderTraversal([](const Account& acc){
        acc.showAllTransactions();
    });
}    
