#include<bits/stdc++.h>
using namespace std;

class Rectangle{
unique_ptr<int> left,top,height,width,area=NULL;
public:
//default constructor
Rectangle(){
    left.reset(new int(0));
    top.reset(new int(0));
    height.reset(new int(0));
    width.reset(new int(0));
}
//parameterized constructor with height and width as parameters
Rectangle(int h,int w){
    left.reset(new int(0));
    top.reset(new int(0));
    height.reset(new int(w));
    width.reset(new int(h));
}
//parameterized constructor with all paramters
Rectangle(int t,int l,int h,int w){
    // left = make_unique<int> (new int(0));
    left.reset(new int(l));
    top.reset(new int(t));
    height.reset(new int(w));
    width.reset(new int(h));
}
Rectangle(float t,float l,float h,float w){
    left.reset(new int(round(l)));
    top.reset(new int(round(t)));   
    height.reset(new int(round(h)));
    width.reset(new int(round(w)));
}
Rectangle(Rectangle &obj){
    left.reset(new int(*obj.left));
    top.reset(new int(*obj.top)); 
    height.reset(new int(*obj.height));
    width.reset(new int(*obj.width));
    obj.area.reset(new int ((*height) * (*width)));
    area.reset(new int(*obj.area));
}
void print(){
    cout<<"Left - "<<*left<<endl;
    cout<<"Top - "<<*top<<endl;
    cout<<"Height - "<<*height<<endl;
    cout<<"Width - "<<*width<<endl;
    if(area) cout<<"Area - "<<*area<<endl;
}
~Rectangle(){
    cout<<"Destroyed"<<endl;
}
};

int main(){
    Rectangle a,b(20,10),c(10,10,10,10),d(12.1f,12.8f,1.5f,1.9f);
    
    //copy constructor from b to x
    Rectangle x(b);
    cout<<"\nA\n";
    a.print();
    cout<<"\nB\n";
    b.print();
    cout<<"\nC\n";
    c.print();
    cout<<"\nD\n";
    d.print();
    cout<<"\nX\n";
    x.print();

    return 0;
}