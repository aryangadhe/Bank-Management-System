#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
using namespace std;

class Transaction {
public:
    int transactionId;
    string type;
    double amount;
    string timestamp;
    Transaction* next;  // pointer to the next transaction (for linked list)

    // Constructor

    Transaction(int id, string s, double a, string t);

    void display() const;
    string getType() const;
    double getAmount() const;
    string getTimeStamp() const;
    int getTransactionId() const;
};

#endif
