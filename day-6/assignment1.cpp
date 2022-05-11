#include<iostream>
#include<string>
#include<exception>
#include<vector>
using namespace std;

int divide(int x,int y){
    if(y == 0) throw runtime_error("Division by 0");
    return x/y;
}

class MyException : public exception{
    const char* msg;
    public:
    MyException(const char* s){
        this->msg = s;
    }
    const char* what() const throw(){
        return msg;
    }
};

int main(){
    //try catch block to find divide by 0 exception
    try{
        int x,y,res;
        cout<<"Enter x and y : ";
        cin>>x>>y;
        res = divide(x,y);
        cout<<res;
    }catch(runtime_error& e){
        cout<<e.what()<<endl;
    }

    //try catch block to handle insufficient heap memory

    try{
        long size = 0x8fffffff;
        cout<<"\nHeap memory allocation \n";
        const char* s = new char[size];
        cout<<"Memory Allocated\n";
    }catch(bad_alloc& e){
        cout<<"Memory is compromised\n";
    }

    // try catch block to handle format mismatch
    try{
        int x;
        string s;
        cout<<"Enter the number to be parsed to int : ";
        cin>>s;
        x = stoi(s);
    }catch(invalid_argument& e){
        cout<<"Format mismatch\n";
    }

    //try catch block to handle string index out of bounds
    try{
        string s = "Hello";
        int index;
        cout<<"Enter the index to access from \"Hello\" : ";
        cin>>index;
        if(index < 0 || index >= s.length()) throw "Index is invalid\n";
        cout<<s[index]<<endl;
    }catch(const char* s){
        cout<<s;
    }

    //try catch block to handle array out of bounds
    try{
        int arr[4] = {1,2,3,4};
        int index;
        cout<<"Enter the index to access from the array of size 4 : ";
        cin>>index;
        if(index < 0 || index >= 4) throw "Array index is invalid\n";

        cout<<"Value at index "<<index<<" is "<<arr[index]<<endl;
    }catch(const char* s){
        cout<<s;
    }

    cout<<"User Defined Exception\n";
    //user defined exception with parameter
    try{
        throw MyException("exception parameter");
    }catch(MyException& e){
        cout<<"MyException ["<<e.what()<<"]";
    }

    //demonstrate catch(...)
    try{
        throw runtime_error("This is a runtime error");
    }catch(const char* s){
        cout<<s;
    }catch(...){
        cout<<"\nException Occured\n";
    }

    cout<<"Exception Handling Accomplished";
    return 0;
}