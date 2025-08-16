#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std ;

void Red()       {cout<< "\033[31m";}
void Green()     {cout<< "\033[32m";}
void Yellow()    {cout<< "\033[33m";}
void Blue()      {cout<< "\033[34m";}
void Magengta()  {cout<< "\033[35m";}
void Cyan()      {cout<< "\033[36m";}
void White()     {cout<< "\033[37m";}
void Reset()     {cout<< "\033[0m";}

class bankAccount {
    private :   
       string bankName = "SCB";  //  SONAL CODER BANK
       int bankCode; 
       string accountHolderName;
       string accountNumber;
       string accountPassword;
       string addaharNumber;
       string email;
       string phoneNumber;
       double balance; 
       vector<string> transactionHistory;  
    public :
       void savetoFile();
       void loadFromFile();
       void mainMenu();
       void createAccount();
       void loginBankAccount();
       void depositoMoney();
       void withdrawMoney();
       void checkBalance();
       void accountDetails();
       void allTransactionHistory();
};

void bankAccount::savetoFile(){            
    ofstream file(accountNumber + ".txt");  
    if(file.is_open()){

        file<<accountHolderName<<endl;
        file<<accountNumber<<endl;
        file<<accountPassword<<endl;
        file<<addaharNumber<<endl;
        file<<email<<endl;
        file<<phoneNumber<<endl;
        file<<balance<<endl;

        for(auto trasaction : transactionHistory){ 
            file<<trasaction<<endl; 
        }
        file.close();
    }else{
        cout<<"Error opening file!"<<endl;
    }
}

void bankAccount::loadFromFile(){ 
    ifstream file(accountNumber + ".txt");
    if(file.is_open()) {
        getline(file, accountHolderName);
        getline(file, accountNumber);
        getline(file, accountPassword);
        getline(file, addaharNumber);
        getline(file, email);
        getline(file, phoneNumber);
        file >> balance ;
        file.ignore();
        string transaction ;

        while (getline(file, transaction)) {
        }
        file.close();
    }else {
        cout<<"Error opening file"<<endl;
    }
}


void bankAccount::mainMenu(){
    int choice ;
   
    do { 
         cout<<"------------------------------------------------"<<endl;
         cout<<"Enter 1 for Deposite Money"<<endl;
          cout<<"Enter 2 for Withraw Money"<<endl;
         cout<<"Enter 3 for check Balance Money"<<endl;
         cout<<"Enter 4 for Account Details Money"<<endl;
         cout<<"Enter 5 for All Transaction History Money"<<endl;
         cout<<"Enter 6 for logout Money"<<endl;
         cout<<"------------------------------------------------"<<endl;
         cout<<"Enter your choice : "<<endl;
         cin>> choice;
         cin.ignore();  
         system("clear");  

        switch (choice){
            case 1 : 
                depositoMoney ();
                     break;
            case 2 : 
                withdrawMoney ();
                     break;
            case 3 :
                checkBalance ();
                     break;
            case 4 : 
                accountDetails ();
                     break;
            case 5 : 
                allTransactionHistory ();
                     break;
            case 6 : 
                cout<< " Loggin out...."<<endl;
                     break;
            default :
                cout<< "Invalid choice , Pleace try again,"<< endl;                      
        }
    } while (choice!=6);
}


void bankAccount::createAccount() {
    Green();
    cout<<"               create Account               "<<endl;
    cout<<"--------------------------------------------"<<endl;
    cout<<"Enter Your Full Name"<<endl;
    getline(cin, accountHolderName); 
    cout<<"Enter Your Email id            :"<<endl;
    getline(cin, email);
    cout<<" Enter Your Phone Number       :"<<endl;
    getline(cin,phoneNumber);
    cout<<"Enter Your Addahr Number       :"<<endl;
    getline(cin, addaharNumber);
    cout<<"Enter Your Account Password    :"<<endl;
    getline(cin,accountPassword);
    cout<<"---------------------------------------------"<<endl;
    Reset ();

    balance = 500.0 ; 
    ifstream file("Sonal-Coder-Bank.txt"); 
    if(file.is_open()) {

        file>>bankCode;
        file.close();
        ofstream output("Sonal-Coder-Bank.txt");

        if(output.is_open()) {

            output<<bankCode+1 ;
            output.close ();
        }
        else {
        cout<<"Enter opening file"<<endl;
        }
    }else {
        cout<<"Enter opening file"<<endl;
    }

    accountNumber = bankName+ to_string(bankCode);
    transactionHistory.push_back("Deposit :-" + to_string(balance));
    Yellow();

    cout<<"Account Created Successfully!"<<endl;
    cout<<"Account NUmber : "<<endl;
    cout<<"Account Password : "<<endl;
    cout<<"Minimum Balance : 500.0"<<endl;
    cout<<"-----------------------------------"<<endl;

    Reset();
    savetoFile ();
}

void bankAccount::loginBankAccount () {
    string enteredAccountNumber ;
    string enteredPassword ;
    Blue ();

    cout<<"       Login Account      "<<endl;
    cout<<"--------------------------"<<endl;
    cout<<"Enter Account Number     :"<<endl;
    getline(cin, enteredAccountNumber);
    accountNumber = enteredAccountNumber ;

    ifstream file(enteredAccountNumber + ".txt");
    if(file.is_open()) {
        loadFromFile();

        cout<<"Enter Account Password :"<<endl;
        getline(cin, enteredPassword);

        if(accountPassword == enteredPassword) {

            cout<<"Login Sucessfull!"<<endl;
            mainMenu();
        }else {
            cout<<"Invalid PAssword "<<endl;
        }
        file.close();
    } else {
        cout<<"Account not found!"<<endl;
    }
}

void bankAccount::depositoMoney() {
    double amount ;
    cout<<"Enter Amount to Deposite"<<endl;
    cin>> amount ;
    cin.ignore ();

    if (amount > 0) {

        balance += amount ;
        transactionHistory.push_back("Deposite :-" + to_string(amount));
        ofstream file(accountNumber + ".txt", ios::app); 
        
        if(file.is_open()) {
            cout<<"Deposite Successfull!"<<endl;
            cout<<"New Balance: "<<balance<<endl;
            file<<"Deposite :- " + to_string(amount) +"\n";
            file.close();
        }else {
            cout <<"Deposit Not Successfull!"<<endl;
        }
    }else {
        cout<<"Invalid Amount"<<endl;
    }
}

void bankAccount::withdrawMoney() {
    double amount ;
     cout<<"Enter Amount to Withdraw :"<<endl;
     cin>>amount;
     cin.ignore();

     if(amount > 0 && amount <= balance) {
        balance -= amount ;
        transactionHistory.push_back("Withdrwa :-" + to_string(amount));
        ofstream file (accountNumber +".txt",ios::app);
        if(file.is_open()) {
            cout<<"Withdraw Sucessfull!"<<endl;
            cout<<"New Balance :"<<balance<<endl;
            file<<"Withdraw :-" + to_string(amount) +"\n";
            file.close();
        }else{
            cout<<"Withdrawa Not Successfull!"<<endl;
        }
    } else {
        cout<<"Invalid amount!"<<endl;
    }
}

void bankAccount::checkBalance() {
    cout<<"Current Balance :"<<balance <<endl;
    cout<<"--------------------"<<endl;
}

void bankAccount::accountDetails() {

    Magengta();
    cout<<"|-------------------------|"<<endl;
    cout<<"|    SONAL CODER BANK     |"<<endl;
    cout<<"|-------------------------|"<<endl;
    Blue();

    cout<<" Account Holder Name  :"<<accountHolderName<<endl;
    cout<<" Account Number       :"<<accountNumber<<endl;
    cout<<" Addhar Number        :"<<addaharNumber<<endl;
    cout<<" Email Id             :"<<email<<endl;
    cout<<" Phone Number         :"<<phoneNumber<<endl;
    cout<<" Current Balance      :"<<balance<<endl;
    cout<<"--------------------------"<<endl;
    Reset();
}

void bankAccount::allTransactionHistory() {
    cout<<" Transaction History :-"<<endl;
    Yellow();
    cout<<"-------------------------------"<<endl;
    cout<<" Account Holder Name  :"<<accountHolderName<<endl;
    cout<<" Account Number       :"<<accountNumber<<endl;

    for(const auto& transaction : transactionHistory){
        cout<< transaction << endl;
    }
    cout<<"-------------------------------"<<endl;
    Reset();
}

int main (){

    bankAccount account;
    int choice ;

    do {
        cout<<"Welcome to SONAL CODER BANK"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"1. Create Account "<<endl;
        cout<<"2. Login "<<endl;
        cout<<"3. Exit "<<endl;
        cout<<"Enter your choice"<<endl;
        cin>>choice;

        cin.ignore();
        system ("clear");
        switch(choice) {
            case 1:
                account.createAccount();
                break;
            case 2:
                account.loginBankAccount();
                break;
            case 3:
                cout<<"Exiting..."<<endl;
                break;
            default :
                cout<<"Invalid choice. Please try again"<<endl;      
        }
    } while (choice != 3);
}
