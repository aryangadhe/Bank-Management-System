#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void FileManager::saveAccounts(const AVLTree &accounts, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Write header
    outFile << "ID, Name, Balance, Pin\n";

    accounts.inorderTraversal([&](const Account &acc) {
        outFile << acc.getId() << ","
                << acc.getName() << ","
                << acc.getBalance() << ","
                << acc.getPin() << "\n";
    });

    outFile.close();
}

void FileManager::loadAccounts(AVLTree &accounts, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "No file found: " << filename << endl;
        return;
    }

    string line;
    getline(inFile, line); // skip header line (if any)

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, name, balanceStr, pinStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, balanceStr, ',');
        getline(ss, pinStr, ',');

        try {
            int id = stoi(idStr);
            double balance = stod(balanceStr);
            int pin = stoi(pinStr);

            Account acc(id, name, pin, balance);
            accounts.insert(acc);
        } catch (const exception &e) {
            cerr << "Skipping invalid row: " << line << " (" << e.what() << ")\n";
        }
    }

    inFile.close();
}


void FileManager::saveTransactions(const AVLTree &accounts, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    outFile << "AccountID, TransactionID, Type, Amount, Timestamp\n";

    accounts.inorderTraversal([&](const Account &acc) {
        Transaction* txn = acc.getHead();
        while (txn) {
            outFile << acc.getId() << ","
                    << txn -> transactionId << ","
                    << txn->type << ","
                    << txn->amount << ","
                    << "\"" << txn->timestamp << "\""  // wrap timestamp
                    << "\n";
            txn = txn->next;
        }
    });

    outFile.close();
}

void FileManager::loadTransactions(AVLTree &accounts, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "No file found: " << filename << endl;
        return;
    }

    string line;
    getline(inFile, line); // skip header

    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, idTStr, type, amountStr, timestamp;

        getline(ss, idStr, ',');
        getline(ss, idTStr, ',');
        getline(ss, type, ',');
        getline(ss, amountStr, ',');
        getline(ss, timestamp, ',');

        // Remove quotes around timestamp if present
        if (!timestamp.empty() && timestamp.front() == '"' && timestamp.back() == '"') {
            timestamp = timestamp.substr(1, timestamp.size() - 2);
        }

        int accountId = stoi(idStr);
        double amount = stod(amountStr);

        Account *acc = accounts.search(accountId);
        if (acc) {
            acc->addTransaction(type, amount);  
        }
    }

    inFile.close();
}
