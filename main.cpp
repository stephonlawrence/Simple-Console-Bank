#include <iostream>
#include "BankAccountClass.cpp"
#include <fstream>
#include <new>
using namespace std;
ifstream File("Accounts.txt");

//Operational Functions
void startMenu();
void BeginPrompt(BankAccount account[], int max_accounts, int num_accounts);
int accountNumPrompt();
void error(string msg);
int read_accts(BankAccount account[], int max_accounts);
void print_accts(BankAccount account[], int num_accts);
int find_acct(BankAccount account[], int num_accts, int request_acct);
void withdrawl(BankAccount account[], int num_accts);
void deposit(BankAccount account[], int num_accts);
int newAccount(BankAccount account[], int max_accounts, int num_accts);
void balance(BankAccount account[], int num_accts);
void accountInfo(BankAccount account[], int num_accts);
int closeAccount(BankAccount account[], int max_accounts, int num_accts);
void quit();

int main(){
    //Max Number of Back Accounts
    const int MAX_NUM = 200;
    //Bank Account array
    BankAccount account[MAX_NUM];
    //amount of accounts
    int aAccounts = 0;
    //set the amount of accounts to how much is read in from the file
    aAccounts = read_accts(account, MAX_NUM);
    //print out account information
    print_accts(account, aAccounts);
    //show start menu
    startMenu();
    //start program
    BeginPrompt(account, MAX_NUM, aAccounts);
    
    return 0;
}
//Main Menu Functions -------------------------------------------------------------------------------------------------
void startMenu(){
    //Welcome Screen
    cout << endl << "Welcome User!" << endl;
}
void BeginPrompt(BankAccount account[], int max_accounts, int num_accounts){
    //Allow user to choose which transaction to make
    string choice;
    cout << endl <<"Type 'W' - Widthdrawl" << endl;
    cout << "Type 'D' - Deposit" << endl;
    cout << "Type 'N' - New Account" << endl;
    cout << "Type 'B' - Balance" << endl;
    cout << "Type 'I' - Account Info" << endl;
    cout << "Type 'C' - Close Account" << endl;
    cout << "Type 'Q' - Quit" << endl;
    cin >> choice;
    if(choice == "W"){
        withdrawl(account, num_accounts);
        //Restart Transaction Prompt
        BeginPrompt(account, max_accounts, num_accounts);
    }else if(choice == "D"){
        deposit(account, num_accounts);
        //Restart Transaction Prompt
        BeginPrompt(account, max_accounts, num_accounts);
    }else if(choice == "N"){
        num_accounts = newAccount(account, max_accounts, num_accounts);
        print_accts(account, num_accounts);
        //Restart Transaction Prompt
        BeginPrompt(account, max_accounts, num_accounts);
    }else if(choice == "B"){
        balance(account, num_accounts);
        //Restart Transaction Prompt
        BeginPrompt(account, max_accounts, num_accounts);
    }else if(choice == "I"){
        accountInfo(account, num_accounts);
        //Restart Transaction Prompt
        BeginPrompt(account, max_accounts, num_accounts);
    }else if(choice == "C"){
        num_accounts = closeAccount(account, max_accounts, num_accounts);
        print_accts(account, num_accounts);
        //Restart Transaction Prompt
        BeginPrompt(account, max_accounts, num_accounts);
    }else if(choice == "Q"){
        quit();
    }else{
        cout << endl << choice << " is not a valid choice." << endl;
        //Restart Transaction Prompt
        BeginPrompt(account, max_accounts, num_accounts);
    }
}
int accountNumPrompt(){
    int accountnumber = 0;
    cout << endl << "Please enter the account number" << endl;
    cin >> accountnumber;
    return accountnumber;
}
//This function is to allow for a standard way of showing there was an error.
void error(string msg){
    //More noticible for users to see the Error message.
    cout << endl << "---------------------------" << endl;
    cout << endl << "ERROR: " << msg << endl;
    cout << endl << "---------------------------" << endl;
}
//Account Functions --------------------------------------------------------------------------------------------------------
int read_accts(BankAccount account[], int max_accounts){
    //start counter
    int count = 0;
    //temporary variables
    string fname, lname, type;
    int SSN;
    double acctbalance;
    //count how moany entries are in the file.
    while(!File.eof() && count < max_accounts){
        File >> fname >> lname >> SSN >> type >> acctbalance;

        count++;
    }
    //loop back to top of file.
    File.clear();
    File.seekg(0, ios::beg);
    //counter for our current account
    int i = 0;
    //create pointer for changing the values at the direct address in memory
    BankAccount * b;
    //loop trhough file and save and set values
    while(!File.eof() && i < count){
        //set our current account into our pointer variable
        b = &account[i];
        //define our file format
        File >> fname >> lname >> SSN >> type >> acctbalance;
        //set all of our values
        b->setFirstName(fname);
        b->setLastName(lname);
        b->setSSN(SSN);
        b->setAccountNumber(i);
        b->setAccountType(type);
        b->setAccountBalance(acctbalance);
        i++;
    }
    return count;
}
void print_accts(BankAccount account[], int num_accts){
    //create pointer variable
    BankAccount * b;
    for(int i=0; i<num_accts; i++){
        //stores our current account
        b = &account[i];
        cout << "name: " << b->getFirstName() << " " << b->getLastName() << endl;
        cout << "\t\tAccount Number: " << b->getAccountNumber() << endl;
        cout << "\t\tAccount Type: " << b->getAccountType() << endl;
        cout << "\t\tAccount Balance: " << b->getAccountBalance() << endl;
    }
}
int find_acct(BankAccount account[], int num_accts, int request_acct){
    //creats pointer variable
    BankAccount * b;
    int num = 0;
    //bool for telling when we have found the right account
    bool found = false;
    for(int i=0; i<num_accts; i++){
        //store current account
        b = &account[i];
        if(b->getAccountNumber() == request_acct){
            //store account number when it matches the requested number
            num = i;
            found = true;
            break;
        }
    }
    if(found){
        return num;
    }else{
        return -1;
    }
}
void withdrawl(BankAccount account[], int num_accts){
    int accountnum = 0;
    //prompt the user for an account number
    accountnum = accountNumPrompt();
    //validate that account number
    accountnum = find_acct(account, num_accts, accountnum);
    if(accountnum == -1){
        //give error if its not found
        string message = "We couldn't find an account by that number";
        error(message);
        withdrawl(account, num_accts);
    }else{
        //keep asking until you get a valid amount
        BankAccount * b = &account[accountnum];
        while(true){
            double howmuch = 0.00;
            cout << endl << "How much do you want to withdraw?" << endl;
            cin >> howmuch;
            if(b->withdraw(howmuch)){
                cout << endl << howmuch << " has been withdrawn from account: " << b->getAccountNumber() << endl;
                break;
            }else{
                cout << "Acount " << b->getAccountNumber() << " does not have sufficient funds." << endl;
                
            }
        }
    }
}
void deposit(BankAccount account[], int num_accts){
    int accountnum = 0;
    accountnum = accountNumPrompt();
    accountnum = find_acct(account, num_accts, accountnum);
    if(accountnum == -1){
        string message = "We couldn't find an account by that number";
        error(message);
        deposit(account, num_accts);
    }else{
        BankAccount * b = &account[accountnum];
        double howmuch = 0.00;
        cout << endl << "How much do you want to deposit?" << endl;
        cin >> howmuch;
        b->addAccountBalance(howmuch);
        cout << endl << howmuch << " has been deposited int account: " << b->getAccountNumber() << endl;
    }
}
int newAccount(BankAccount account[], int max_accounts, int num_accts){
    BankAccount * b;
    //make sure there is space left
    if(num_accts+1 <= max_accounts){
        b = &account[num_accts];
        string fname, lname, type;
        int SSN;
        double acctbalance;
        cout << endl << "Please enter first name: ";
        cin >> fname;
        cout << endl << "Please enter last name: ";
        cin >> lname;
        cout << endl << "Please enter SSN (Social Security Number): ";
        cin >> SSN;
        cout << endl << "Please enter Account Type: ";
        cin >> type;
        cout << endl << "Please enter Account starting Balance: ";
        cin >> acctbalance;
        b->setFirstName(fname);
        b->setLastName(lname);
        b->setSSN(SSN);
        //increment the account number
        int greatest = 0;
        BankAccount * g;
        for(int i=0; i < num_accts; i++){
            g = &account[i];
            if(g->getAccountNumber() > greatest){
                greatest = g->getAccountNumber();
            }
        }
        greatest++;
        b->setAccountNumber(greatest);
        b->setAccountType(type);
        b->setAccountBalance(acctbalance);
        num_accts++;
        return num_accts;
    }
}
void balance(BankAccount account[], int num_accts){
    int accountnum = 0;
    accountnum = accountNumPrompt();
    accountnum = find_acct(account, num_accts, accountnum);
    if(accountnum == -1){
        string message = "We couldn't find an account by that number";
        error(message);
        balance(account, num_accts);
    }else{
        double howmuch = 0.00;
        cout << endl << "Here is your balance: $" << account[accountnum].getAccountBalance() << endl;
    }
}
void accountInfo(BankAccount account[], int num_accts){
    int accountnum = 0;
    accountnum = accountNumPrompt();
    accountnum = find_acct(account, num_accts, accountnum);
    if(accountnum == -1){
        string message = "We couldn't find an account by that number";
        error(message);
        accountInfo(account, num_accts);
    }else{
        cout << endl << "Here is your Account Info." << endl << endl;
        
        cout << "name: " << account[accountnum].getFirstName() << " " << account[accountnum].getLastName() << endl ;
        
        cout << "\t\tAccount Number: " << account[accountnum].getAccountNumber() << endl;
        cout << "\t\tAccount Type: " << account[accountnum].getAccountType() << endl;
        cout << "\t\tAccount Balance: " << account[accountnum].getAccountBalance() << endl;
    }
}
int closeAccount(BankAccount account[], int max_accounts, int num_accts){
    int accountnum = 0;
    accountnum = accountNumPrompt();
    accountnum = find_acct(account, num_accts, accountnum);
    if(accountnum == -1){
        string message = "We couldn't find an account by that number";
        error(message);
        closeAccount(account, max_accounts, num_accts);
    }else{
        if(num_accts-1 >= 0){
            BankAccount * b = &account[accountnum];
            //delete all values
            b->setFirstName("");
            b->setLastName("");
            b->setSSN(0);
            b->setAccountNumber(0);
            b->setAccountType("");
            b->setAccountBalance(0);
            int i=accountnum;
            int j = 0;
            // make sure there is no empty spaces in the account array
            while(i+1 < num_accts){
                j = i+1;
                b = &account[i];
                b->setFirstName(account[j].getFirstName());
                b->setLastName( account[j].getLastName());
                b->setSSN(account[j].getSSN());
                b->setAccountNumber(account[j].getAccountNumber());
                b->setAccountType(account[j].getAccountType());
                b->setAccountBalance(account[j].getAccountBalance());
                i++;
            }
            num_accts--;
            return num_accts;
        }
    }
}
void quit(){
    cout << endl << "Program is now ending!" << endl;
}
