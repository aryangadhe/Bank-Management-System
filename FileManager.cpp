#include "FileManager.h"
#include <fstream>
#include <iostream>
using namespace std;

// ================= SAVE ACCOUNTS =================
void FileManager::saveAccounts(const AVLTree &accounts, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    accounts.inorderTraversal([&](const Account &acc) {
        outFile << acc.getId() << " "
                << acc.getName() << " "
                << acc.getBalance() << " "
                << acc.getPin() << endl;
    });

    outFile.close();
}

// ================= LOAD ACCOUNTS =================
void FileManager::loadAccounts(AVLTree &accounts, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "No file found: " << filename << endl;
        return;
    }

    int id, pin;
    string name;
    double balance;

    while (inFile >> id >> name >> balance >> pin) {
        Account acc(id, name, pin, balance);
        accounts.insert(acc);
    }

    inFile.close();
}

void FileManager::saveTransactions(const AVLTree &accounts, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    accounts.inorderTraversal([&](const Account &acc) {
        Transaction* txn = acc.getHead();
        while (txn) {
            outFile << acc.getId() << " "
                    << txn->type << " "
                    << txn->amount << " "
                    << txn->timestamp << endl;
            txn = txn->next;
        }
    });

    outFile.close();
}


// ================= LOAD TRANSACTIONS =================
void FileManager::loadTransactions(AVLTree &accounts, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "No file found: " << filename << endl;
        return;
    }

    int accountId;
    string type, timestamp;
    double amount;

    while (inFile >> accountId >> type >> amount >> timestamp) {
        Account *acc = accounts.search(accountId);
        if (acc) {
            acc->addTransaction(type, amount);  // ✅ use Account’s addTransaction
        }
    }

    inFile.close();
}
