#include "Bank.h"
#include "FileManager.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    Bank bank;

    // Load data at start
    FileManager::loadAccounts(bank.getAccountsTree(), "accounts.txt");
    FileManager::loadTransactions(bank.getAccountsTree(), "transactions.txt");

    int choice;
    while (true) {
        cout << "\n===== Banking System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Show Account\n";
        cout << "6. Show Transactions\n";
        cout << "7. Logout\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            double initialDeposit;
            int pin;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter initial deposit: ";
            cin >> initialDeposit;
            cout << "Set a 4-digit PIN: ";
            cin >> pin;
            bank.createAccount(name, pin, initialDeposit);
        }
        else if(choice == 2){
            int id;
            cout << "Enter Your Account Id to Login: ";
            cin >> id;
            bank.login(id);
        }
        else if (choice == 3) {
            if(!bank.isLoggedIn()){
                cout << "Please login first"<< endl;
                continue;
            }
            double amount;
            cout << "Enter deposit amount: ";
            cin >> amount;
            bank.deposit(bank.getLoggedInId(), amount);
        }
        else if (choice == 4) {
            if(!bank.isLoggedIn()){
                cout << "Please login first"<< endl;
                continue;
            }
            double amount;
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            bank.withdraw(bank.getLoggedInId(), amount);
        }
        else if (choice == 5) {
            if(!bank.isLoggedIn()){
                cout << "Please login first"<< endl;
                continue;
            }
            bank.showAccount(bank.getLoggedInId());
        }
        else if (choice == 6) {
            if(!bank.isLoggedIn()){
                cout << "Please login first"<< endl;
                continue;
            }
            bank.showTransactions(bank.getLoggedInId());
        }
        else if(choice == 7){
            bank.logout();
        }
        else if (choice == 8) {
            // Save before exit
            FileManager::saveAccounts(bank.getAccountsTree(), "accounts.txt");
            FileManager::saveTransactions(bank.getAccountsTree(), "transactions.txt");
            cout << "Data saved. Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
