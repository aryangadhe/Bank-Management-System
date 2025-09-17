#include "Transaction.h"
#include <iostream>
using namespace std;

// Constructor
Transaction::Transaction(int id, string s, double a, string t) {
    transactionId = id;
    type = s;
    amount = a;
    timestamp = t;
    next = nullptr;   // initialize next pointer for linked list
}

// Display function
void Transaction::display() const {
    cout << "----------------------------------" << endl;
    cout << "Transaction Id: " << transactionId << endl;
    cout << "Type          : " << type << endl;
    cout << "Amount        : " << amount << endl;
    cout << "Timestamp     : " << timestamp << endl;
    cout << "----------------------------------" << endl;
}

// Getters
string Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
string Transaction::getTimeStamp() const { return timestamp; }
int Transaction::getTransactionId() const { return transactionId; }