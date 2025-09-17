#include "Account.h"
#include <ctime>
#include <iostream>
using namespace std;


Account::Account() : accountId(0), name(""), balance(0.0), pin(0), head(nullptr), nextTransactionId(1) {}

Account::Account(int id, const string& n, int p, double b)
    : accountId(id), name(n), balance(b), pin(p), head(nullptr), nextTransactionId(1) {}

string Account::getCurrentTime() const {
    time_t now = time(0);
    char* dt = ctime(&now);
    string str(dt);
    str.pop_back();
    return str;
}

void Account::deposit(double amount) {
    balance += amount;
    addTransaction("Deposit", amount);
}

void Account::withdraw(double amount) {
    if (amount > balance) {
        cout << "Insufficient balance!\n";
        return;
    }
    balance -= amount;
    addTransaction("Withdraw", amount);
}

void Account::display() const {
    cout << "Account ID: " << accountId
         << " | Name: " << name
         << " | Balance: " << balance << endl;
}

void Account::showAllTransactions() const {
    if (!head) {
        cout << "No transactions available.\n";
        return;
    }
    Transaction* temp = head;
    cout << "Transaction history for Account ID " << accountId << ":\n";
    while (temp) {
        cout << temp->transactionId << " | " << temp->type
             << " | " << temp->amount
             << " | " << temp->timestamp << endl;
        temp = temp->next;
    }
}

Transaction* Account::getHead() const { return head; }

void Account::addTransaction(const string& type, double amount) {
    Transaction* txn = new Transaction(nextTransactionId++, type, amount, getCurrentTime());
    txn->next = head;
    head = txn;
}

int Account::getId() const { return accountId; }
string Account::getName() const { return name; }
double Account::getBalance() const { return balance; }
int Account::getPin() const { return pin; }
