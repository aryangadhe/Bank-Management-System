#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Transaction.h"

#include <bits/stdc++.h>
using namespace std;

class Account {
private:
    int accountId;
    string name;
    double balance;
    int pin;
    Transaction* head;
    int nextTransactionId;

    string getCurrentTime() const;

public:
    Account();
    Account(int id, const string& n, int p, double b = 0.0);

    void deposit(double amount);
    void withdraw(double amount);
    void display() const;
    void showAllTransactions() const;

    Transaction* getHead() const;
    void addTransaction(const string& type, double amount);

    int getId() const;
    string getName() const;
    double getBalance() const;
    int getPin() const;
};

#endif
