#include<iostream>
using namespace std;

class Person{
    friend class Animal;
    int age;
    string name;
    public:
    Person(int n,string s){
        age = n;
        name = s;
    }
    void printAgeName();
    //friend function
    friend void printAge(Person&);
};
//Friend class (we can access the private,protected and public members of class Person from class Animal)
class Animal{
    string name;
    public:
        Animal(string n){
            name = n;
        }
        void printPerson(Person& pers){
            cout<<"Friend of "<<name<<" is "<<pers.name<<endl;
        }
};
//scope operator to define the function outside the class(::).
void Person::printAgeName(){
        cout<<age<<"  "<<name<<endl;
}
void printAge(Person& person){
    cout<<person.age<<endl;
}
int main(){
    //the following object is stored in stack memory and therefore it will be destroyed when the scope ends.
    Person pers1(20,"Name1");
    pers1.printAgeName();

    //calling friend function for pers2
    printAge(pers1);

    Animal animal("Dog");
    animal.printPerson(pers1);
    //the below object on the other hand will be stored inside the heap memory by using the new keyword.
    //we need to create pointer to the class and must use the arrow operator to access the member variables and functions.
    Person *pers2 = new Person(21,"Name2");
    pers2->printAgeName();
}