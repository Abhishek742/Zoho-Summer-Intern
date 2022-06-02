#include<iostream>
#include<ctime>
using namespace std;

int main(){
    time_t t = time(0);
    string dt = string(ctime(&t));
    cout<<dt;
}