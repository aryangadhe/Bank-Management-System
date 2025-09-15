#include "Bank.h"
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
    int inputPin;
    cout << "Enter PIN: ";
    cin >> inputPin;
    return inputPin == acc.getPin();
}

void Bank::deposit(int id, double amount) {
    Account* acc = accounts.search(id);
    if (acc) acc->deposit(amount);
    else cout << "No account found for ID " << id << endl;
}

void Bank::withdraw(int id, double amount) {
    Account* acc = accounts.search(id);
    if (acc && verifyPinInternal(*acc)) acc->withdraw(amount);
    else cout << "No account found or invalid PIN.\n";
}

void Bank::showAccount(int id) const {
    const Account* acc = accounts.search(id);
    if (acc) {
        if (!const_cast<Bank*>(this)->verifyPinInternal(*acc)) return;
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
