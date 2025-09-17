#include "Bank.h"
#include "FileManager.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    Bank bank;

    // Load data at start
    FileManager::loadAccounts(bank.getAccountsTree(), "accounts.csv");
    FileManager::loadTransactions(bank.getAccountsTree(), "transactions.csv");
    bank.updateNextAccountId();

    int choice;
    while (true) {
        cout << "\n===== Banking System =====\n";
        cout << "1. Create Account\n";
        cout << "2. User Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";
        // cout << "5. Show Account\n";
        // cout << "6. Show Transactions\n";
        // cout << "7. Fund Transfer\n";
        // cout << "8. Logout\n";
        // cout << "9. Exit\n";
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
            if(bank.login(id)){
                int userChoice;
                while(true){
                    cout << "\n===== User Panel =====\n";
                    cout << "1. Deposit\n";
                    cout << "2. Withdraw\n";
                    cout << "3. Show Account\n";
                    cout << "4. Mini Statement\n";
                    cout << "5. Fund Transfer\n";
                    cout << "6. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> userChoice;

                    if (userChoice == 1) {
                        double amount;
                        cout << "Enter deposit amount: ";
                        cin >> amount;
                        bank.deposit(bank.getLoggedInId(), amount);
                    }
                    else if (userChoice == 2) {
                        double amount;
                        cout << "Enter withdrawal amount: ";
                        cin >> amount;
                        bank.withdraw(bank.getLoggedInId(), amount);
                    }
                    else if (userChoice == 3) {
                        bank.showAccount(bank.getLoggedInId());
                    }
                    else if (userChoice == 4) {
                        bank.showMiniStatement(bank.getLoggedInId(), 10);
                    }
                    else if (userChoice == 5) {
                        int toId;
                        double amount;
                        cout << "Enter recipient Account ID: ";
                        cin >> toId;
                        cout << "Enter amount to transfer: ";
                        cin >> amount;
                        bank.fundTransfer(bank.getLoggedInId(), toId, amount);
                    }
                    else if (userChoice == 6) {
                        bank.logout();
                        break;
                    }
                    else {
                        cout << "Invalid choice!\n";
                    }
                }
            }
        }   
        else if (choice == 3) {
            string password;
            cout << "Enter Admin Password: ";
            cin >> password;
            if(bank.adminLogin(password)){
                int adminChoice;
                while(true){
                    cout << "\n--- Admin Menu ---\n";
                    cout << "1. Search Account by Name\n";
                    cout << "2. Search Account by Balance\n";
                    cout << "3. Show Account by ID\n";
                    cout << "4. Show Transaction History by ID\n";
                    cout << "5. Show All Accounts\n";
                    cout << "6. Show All Transaction Histories\n";
                    cout << "7. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;

                    if(adminChoice == 1){
                        string name;
                        cout << "Enter Name to search: ";
                        cin >> ws;
                        getline(cin, name);
                        bank.searchByName(name);
                    }
                    else if(adminChoice == 2){
                        double minBal, maxBal;
                        cout << "Enter minimum balance: ";
                        cin >> minBal;
                        cout << "Enter maximum balance: ";
                        cin >> maxBal;
                        bank.searchByBalance(minBal);
                    }
                    else if(adminChoice == 3){
                        int id;
                        cout << "Enter account ID: ";
                        cin >> id;
                        bank.showAccount(id);
                    }
                    else if(adminChoice == 4){
                        int id;
                        cout << "Enter account Id: ";
                        cin >> id;
                        bank.showTransactions(id);
                    }
                    else if(adminChoice == 5){
                        bank.showAllAccounts();
                    }
                    else if(adminChoice == 6){
                        bank.showAllTransactionHistories();
                    }
                    else if(adminChoice == 7){
                        cout << "Admin logged out \n";
                        break;
                    }
                    else{
                        cout << "Invalid Choice";
                    }
                }
            }
            else{
                cout << "Admin login failed \n";
            }
            
        }
        
        else if (choice == 4) {
            // Save before exit
            FileManager::saveAccounts(bank.getAccountsTree(), "accounts.csv");
            FileManager::saveTransactions(bank.getAccountsTree(), "transactions.csv");
            cout << "Data saved. Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
