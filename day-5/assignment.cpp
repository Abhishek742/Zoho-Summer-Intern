#include "mathoperations.h"
#include<iostream>
using namespace std;

int main(){
    mathoperations::Print a;
    a.printS();

    //using namespace alias
    namespace operations = mathoperations::arithmetic;

    cout<<"Arithmetic operations performed using functions defined in a namepace \"mathoperations\"\n";
    cout<<"4 + 5 = "<<operations::add(4,5)<<endl;
    cout<<"4.6 + 5.2 = "<<operations::add(4.6,5.2)<<endl;
    cout<<"5.0 - 3.6 = "<<operations::sub(5.0,3.6)<<endl;
    cout<<"4.0 * 5.4 = "<<operations::mul(4.0,5.4)<<endl;
    cout<<"4.0 / 5.4 = "<<operations::div(4.0,5.5)<<endl;
    
    //max and min defined as inline namespaces inside arithmetic
    cout<<"Max of 6 and 5 = "<<operations::max(6,5)<<endl;
    cout<<"Min of 6 and 5 = "<<operations::min(6,5)<<endl;
    return 0;
}