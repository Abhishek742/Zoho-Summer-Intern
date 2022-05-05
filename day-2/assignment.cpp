#include<iostream>
#include<vector>
using namespace std;

//used bankdetails instead of Bank 
class BankDetails{
    protected:
    string name,establishedDate,bankType,branch;
    public:
    BankDetails(string name,string establishedDate,string bankType,string branch) : name(name),establishedDate(establishedDate),bankType(bankType),branch(branch){};
    
    virtual string getName() = 0;
    virtual string getEstablishedDate() = 0;
    virtual string getBankType() = 0;
    void getInfo(){
        cout<<"\nBank Details  \n";
        cout<<"Bank name - "<<name<<"\n";
        cout<<"Established Date - "<<establishedDate<<"\n";
        cout<<"Bank Type - "<<bankType<<"\n";
        cout<<"Branch - "<<branch<<"\n";
    }
};
class Loan{
    protected:
    bool goldLoan,landLoan,personalLoan;
    double interestRate;
    vector<string> goldLoanDocs,landLoanDocs,persLoanDocs;
    public:
    Loan(bool goldLoan,bool landLoan,bool personalLoan,double interestRate,vector<string> goldLoanDocs,vector<string> landLoanDocs,vector<string> persLoanDocs) : 
    goldLoan(goldLoan),landLoan(landLoan),personalLoan(personalLoan),interestRate(interestRate),goldLoanDocs(goldLoanDocs),persLoanDocs(persLoanDocs),landLoanDocs(landLoanDocs){};
    
    void getAvailableLoans(){
        cout<<"Available loans - ";
        if(goldLoan) cout<<"Gold Loan  ";
        if(landLoan) cout<<"Land Loan  ";
        if(personalLoan) cout<<" Personal Loan \n";
    }
    double getInterest(){
        return interestRate;
    }
    void getDocumentsRequired(){
        if(personalLoan && persLoanDocs.size()>0){
            cout<<"Documents Required for Personal Loan : \n";
            for(int i = 0;i<persLoanDocs.size();i++){
                cout<<persLoanDocs[i]<<"  ";
            }
            cout<<endl;
        }
        if(goldLoan && goldLoanDocs.size()>0){
            cout<<"Documents Required for Gold Loan : \n";
            for(int i = 0;i<goldLoanDocs.size();i++){
                cout<<goldLoanDocs[i]<<"  ";
            }
            cout<<endl;
        }
        if(landLoan && landLoanDocs.size()>0){
            cout<<"Documents Required for Land Loan : \n";
            for(int i = 0;i<landLoanDocs.size();i++){
                cout<<landLoanDocs[i]<<"  ";
            }
            cout<<endl;
        }
    }
    void getInfo(){
        getAvailableLoans();
        cout<<"Interest Rate - "<<getInterest()<<endl;
        getDocumentsRequired();
    }
};

//this class inherits the properties and methods of BankDetails and Loan.
class Bank : public BankDetails, public Loan{
    public:
    Bank(string name,string establishedDate,string bankType,string branch,
    bool goldLoan,bool landLoan,bool personalLoan,double interestRate,vector<string> goldLoanDocs,vector<string> landLoanDocs,vector<string> persLoanDocs)
    : BankDetails(name,establishedDate,bankType,branch),
    Loan(goldLoan,landLoan,personalLoan,interestRate, goldLoanDocs, landLoanDocs, persLoanDocs){};
    
    string getName(){
        return name;
    }
    string getEstablishedDate(){
        return establishedDate;
    }
    string getBankType(){
        return bankType;
    }

    void getInfo(){
        //calling base class functions with function overloading.
        BankDetails::getInfo();
        Loan::getInfo();
    }
};

class Broker{
    public:
    void printLowInterest(Bank &a){
        cout<<a.getName()<<" has lesser interest \n";
    }
    Bank& compare(Bank &a,Bank &b){
        if(a.getInterest()<b.getInterest()){
            return a;
        }
        return b;
    }
    Bank& compare(Bank &a,Bank &b,Bank &c){
        return compare(compare(a,b),c);
    }

    void compare(vector<Bank> &allBanks){
        Bank bank = allBanks[0];
        for(int i = 1;i<allBanks.size();i++){
            if(bank.getInterest() > allBanks[i].getInterest()){
                bank = allBanks[i];
            }
        }
        cout<<"\nAmong all the Banks "<<bank.getName()<<" has the lowest interest.\n";
    }
    void printBank(Bank &bank){
        bank.getInfo();
    }
    void printBank(vector<Bank> &banks){
        for(int i = 0;i<banks.size();i++) banks[i].getInfo();
    }
};
int main(){
    //temporary array of strings to represent required documents
    vector<string> bank1 = {"doc1","doc2","doc3"}, bank2 = {"doc2","doc3"};

    Bank HDFC("HDFC","02.05.2022","private","Tambaram",true,true,true,14.60,bank1,bank1,bank1);
    Bank SBI("SBI","04.05.2022","public","Adyar",true,false,true,12.00,bank2,bank2,bank2);
    Bank ICICI("ICICI","15.06.2021","private","Velachery",false,true,true,5.5,bank1,bank2,bank1);
    Bank IB("IB","04.05.2022","public","T Nagar",true,false,false,16.00,bank2,bank2,bank1);

    Broker b;
    vector<Bank> allBanks = {HDFC,SBI,ICICI,IB};


    //function call to print specific bank objects
    b.printBank(SBI);


    //function call to print multiple banks.
    b.printBank(allBanks);


    //function call to compare two banks with respect to interest rate
    cout<<"\nOn Comparing IB and HDFC, ";
    b.printLowInterest(b.compare(IB,HDFC));


    //function call to compare two banks with respect to interest rate 
    cout<<"\nOn Comparing HDFC, SBI and IB, ";
    b.printLowInterest(b.compare(HDFC,SBI,IB));

    //function call to compare all the banks or n different banks(can be done by varying the array of objects)
    b.compare(allBanks);


    return 0;
}