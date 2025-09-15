
#include<bits/stdc++.h>
using namespace std;

class Transaction{
    private: 
        int transactionId;
        string type;
        double amount;
        string timestamp;
    
    public:
        Transaction(int id, string t, double a, string time){
            transactionId = id;
            type = t;
            amount = a;
            timestamp = time;
        }

        void display(){
            cout <<"----------------------------------"<< endl;
            cout << "Transactio ID: " << transactionId << endl;
            cout << "Type         : " << type << endl;
            cout << "Amount       : " << amount << endl;
            cout << "Timestamp    : " << timestamp << endl;
            cout <<"----------------------------------"<< endl;
        }
        string getType() {
            return type;
        }
        double getAmount() {
            return amount;  
        }
        string getTimeStamp(){
            return timestamp;
        }
};

class Account{
    private:
        int accountId;
        string name;
        double balance;
        vector<Transaction> transactions;
        int next_transactionId = 1;

        string getCurrentTime(){
            time_t now = time(0);
            char* dt = ctime(&now);
            string str(dt);
            str.pop_back();
            return str;
        }
    public:
        Account() : accountId(0), name(""), balance(0.0) {}
        Account(int id, string n, double b = 0.0){
            accountId = id;
            name = n;
            balance = b;
        }    
        int getId(){
            return accountId;
        }
        string getName(){
            return name;
        }
        double getBalance(){
            return balance;
        }

        void deposit(double amount){
            if(amount > 0){
                balance += amount;
                cout << "Successfully deposited: " << amount << endl;
                cout << "Total balance: " << balance << endl;

                transactions.push_back(Transaction(next_transactionId++, "Deposit", amount, getCurrentTime()));
            }
            else{
                cout << "Invalid Amount: "<< endl;
            }
            
        }
        void withdraw(double amount){
            if(amount > 0){
                if(balance >= amount){
                    balance -= amount;
                    cout << "Successfully withdrawn: " << amount << endl;
                    cout << "Total balance: " << balance << endl;

                    transactions.push_back(Transaction(next_transactionId++, "Withdrawal", amount, getCurrentTime()));
                }
                else{
                    cout << "Insufficient balance: " << endl;
                    cout << "Total balance: " << balance << endl;
                }
            }
            
            else{
                cout << "Invalid Amount: " << endl;
            }
        }

        void display(){
            cout << "---------------------------------" << endl;
            cout << "Account ID: " << accountId << endl;
            cout << "Name      : " << name << endl;
            cout << "Balance   : " << balance << endl;
            cout << "---------------------------------" << endl;

        }

        void showAllTransactions(){
            if(transactions.empty()){
                cout << "No Transactions Found" << endl;
            }
            else{
                cout << "\n=== Transaction History for Account Id" << accountId << " ===" << endl;
                for(auto &it: transactions){
                    it.display();
                }
            }
        }
};

class Bank{
    private:
        std::map<int, Account> accounts;
        int nextAccountId = 1;
    public:
        
        void createAccount(string name, double initialDeposit){
            Account newAcc(nextAccountId, name, initialDeposit);
            accounts[nextAccountId] = newAcc;;
            cout << "Successfully created account with Account ID: " << nextAccountId << "For: " << name << endl;
            nextAccountId++;
        }

        void deposit(int id, double amount){
            if(accounts.find(id) != accounts.end()){
                accounts[id].deposit(amount);
            }
            else{
                cout << "No Account ID found for id: " << id << endl;
            }
        }

        void withdraw(int id, double amount){
            if(accounts.find(id) != accounts.end()){
                accounts[id].withdraw(amount);
            }
            else{
                cout << "No Account ID found for id: " << id << endl;
            }
        }

        void showAccount(int id){
            if(accounts.find(id) != accounts.end()){
                accounts[id].display();
            }
            else{
                cout << "No Account ID found for id: " << id << endl;
            }
        }

        void showTransactions(int id){
            if(accounts.find(id) != accounts.end()){
                accounts[id].showAllTransactions();
            }
            else{
                cout << "No Account ID found for id: " << id << endl;
            }
        }
};

int main(){
    Bank bank;
    int choice;
    while(true){
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create New Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdray Money" << endl;
        cout << "4. Show Account Details" << endl;
        cout << "5. Show Transaction History" <<  endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1){
            string name;
            double initialDeposit;
            cout << "Please Enter your Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Please Enter Initial Deposit Amount: ";
            cin >> initialDeposit;

            bank.createAccount(name, initialDeposit);
        }
        else if(choice == 2) {
            int id;
            int amount;
            cout << "Please Enter your Account ID: ";
            cin >> id;
            cout << "Please Enter Deposit Amount: ";
            cin >> amount;
            bank.deposit(id, amount);
        }
        else if(choice == 3){
            int id;
            int amount;
            cout << "Please Enter your Account Id: ";
            cin >> id;
            cout << "Please Enter Withdrawal Amount: ";
            cin >> amount;
            bank.withdraw(id, amount);
        }
        else if(choice == 4){
            int id;
            cout << "Please Enter your Account ID: ";
            cin >> id;
            bank.showAccount(id);
        }
        else if(choice == 5){
            int id;
            cout << "Please Enter your Account ID: ";
            cin >> id;
            bank.showTransactions(id);
        }
        else if(choice == 6){
            cout << "Exiting... Thank You! " << endl;
            break;
        }
        else{
            cout << "Invalid Choice" << endl;
        }
    }
    return 0;
}