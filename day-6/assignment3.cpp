#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<string> courses = {"DSA","DBMS","OS","CN"};

class AgeNotWithinRangeException : public exception{
    public:
    const char* what() const throw(){
        return "Age is not within the range 15 to 21\n";
    }
};

class NameNotValidException : public exception{
    public:
    const char* what() const throw(){
        return "Name is not valid\n";
    }
};

class InvalidCourseException : public exception{
    public:
    const char* what() const throw(){
        return "Course Invalid\n";
    }
};

class MoreObjectsInitialised : public exception{
    public:
    const char* what() const throw(){
        return "Cannot initialise object more than once for class Student";
    }
};

class Student{
    public:
    int rollno,age;
    string name,course;
    static int count;
    Student(int rollno,int age,string name,string course) {
        if(count) throw MoreObjectsInitialised();
        this->rollno = rollno;
        if(age < 15 || age > 21) throw AgeNotWithinRangeException();
        this->age = age;
        if(!validName(name)) throw NameNotValidException();
        this->name = name;
        if(!courseAvailable(course)) throw InvalidCourseException();
        this->course = course;
        count++;
    } 
    bool validName(string s){
        for(int i = 0;i<s.length();i++){
            if(s[i] < 65 || (s[i] > 90 && s[i] < 97) || s[i] > 122) return false;
        }
    return true;
    }
    bool courseAvailable(string course){
        for(int i = 0;i<courses.size();i++){
            if(courses[i] == course){
                return true;
            }
        }
        return false;
    }
    void printDetails(){
        cout<<"Student Details \n";
        cout<<"Name : "<<this->name<<endl;
        cout<<"Roll Number : "<<this->rollno<<endl;
        cout<<"Age : "<<this->age<<endl;
        cout<<"Course : "<<this->course<<endl;
    }
};

int Student::count=0;

int main(){
    try{
        //this object will be succesfully initialized
        Student s(4,19,"Abhishek","DSA");

        //this object will throw age limit exception
        // Student s(4,22,"Abhishek","DSA");

        //this object will throw invalid name exception
        // Student s(4,19,"Abhi$h1k","DSA");

        //this object will throw invalid course exception
        // Student s(4,19,"Abhishek","OOPS");

        s.printDetails();
        
        //initialising second object for class student
        Student d(5,16,"Temp","DSA");
        d.printDetails();
    }catch(exception& e){
        cout<<e.what();
    }
}