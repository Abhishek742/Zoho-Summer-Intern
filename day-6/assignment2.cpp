#include<bits/stdc++.h>
using namespace std;

int main(){
    //outer try block
    try{
        //inner try block
        try{
            cout<<"Inside inner try block 1 (throws runtime error)\n";
            throw runtime_error("Runtime Error");
        }catch(runtime_error& e){
            cout<<e.what()<<" caught at inner catch block 1\n";
        }
        try{
            cout<<"\nInside inner try block 2 (throws out of range error)\n";
            throw out_of_range("Out of range");
        }catch(out_of_range& e){
            cout<<e.what()<<" caught at inner catch block 2\n";
            throw;
        }
    }catch(runtime_error& e){
            cout<<e.what()<<" caught at outer catch block 1\n";
    }catch(...){
        cout<<"No such notable exception found";
    }
    
    return 0;
}