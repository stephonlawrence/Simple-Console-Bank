#include <iostream>
using namespace std;

class BankAccount
{
    private:
    string firstName;
    string lastName;
    int SSN;
    int accountNumber;
    string accountType;
    double accountBalance;
    
    public:
    
    void CloseAccount(){
        firstName = "";
        lastName = "";
        SSN = 0;
        accountNumber = 0;
        accountType = "";
        accountBalance = 0;
    }
    
    //Firstname
    void setFirstName(string n){
        firstName = n;
    }
    string getFirstName(){
        return firstName;
    }
    
    //lastname
    void setLastName(string n){
        lastName = n;
    }
    
    string getLastName(){
        return lastName;
    }
    
    //SSN
    void setSSN(int n){
        SSN = n;
    }
    int getSSN(){
        return SSN;
    }
    bool checkSSN(int n){
        if(SSN == n){
            return true;
        }else{
            return false;
        }
    }
    
    //Account Number
    void setAccountNumber(int n){
        accountNumber = n;
    }
    
    int getAccountNumber(){
        return accountNumber;
    }
    
    //Account Type
    void setAccountType(string type){
        if(type == "Checkings" || type == "Savings" || type == "CD"){
            accountType = type;
        }
    }
    string getAccountType(){
        return accountType;
    }
    
    //Account Balance
    void setAccountBalance(double a){
        accountBalance = a;
    }
    void addAccountBalance(double a){
        accountBalance += a;
    }
    double getAccountBalance(){
        return accountBalance;
    }
    
    //Withdraw
    bool withdraw(double a){
        if(accountBalance >= a){
            accountBalance -= a;
            return true;
        }else{
            return false;
        }
    }
     
}; 
