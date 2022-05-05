#include<iostream>
using namespace std;

class Bank{
    protected:
    string name,establishedDate,bankType;
    public:
    virtual void getName() = 0;
    virtual void getEstablishedDate() = 0;
    virtual void getBankType() = 0;
    virtual void getInfo() = 0;
};
class Loan{
    protected:
    bool goldLoan,landLoan,personalLoan;
    double interestRate;
    
    public:
    virtual void getAvailableLoans() = 0;
    virtual void getInterest() = 0;
    virtual void documentRequired() = 0;
};
int main(){
    return 0;
}