#include<iostream>
#define VehicleConstructor Vehicle(vehicleType,brand,model,color,mileage,price) 
using namespace std;

class Vehicle{
    protected:
    string vehicleType,brand,model,color;
    float mileage,price;
    public:
    Vehicle(string vehicleType,string brand,string model, string color,float mileage,int price){
        this->vehicleType = vehicleType;
        this->brand = brand;
        this->model = model;
        this->color = color;
        this->mileage = mileage;
        this->price = price;
    }
    bool operator >(Vehicle &v){
        return this->price > v.price;
    }
    friend ostream& operator <<(ostream &os,Vehicle &v){
        os<<"\nVehicle Details\n";
        os<<"Vehicle Type - "<<v.vehicleType<<"\n";
        os<<"Brand -  "<<v.brand<<"\n";
        os<<"Model - "<<v.model<<"\n";
        os<<"Color - "<<v.color<<"\n";
        os<<"Mileage - "<<v.mileage<<"\n";
        os<<"Price - "<<v.price<<"\n";
        return os;
    }
    //abstract method
    virtual int getNoOfWheels() = 0;
};
class Car : public Vehicle{
    int numberOfPersons;
    string carType;
    public:
    Car(string vehicleType,string brand,string model, string color,float mileage, int price ,int numberOfPersons,string carType) : VehicleConstructor{
            this->numberOfPersons = numberOfPersons;
            this-> carType = carType;
    }
    int getNoOfWheels(){
        return 4;
    }
};
class Bike : public Vehicle{
    float weight;
    string bikeType;
    public:
    Bike(string vehicleType,string brand,string model, string color,float mileage, int price ,float weight,string bikeType) : VehicleConstructor{
            this->weight = weight;
            this-> bikeType = bikeType;
    }
    int getNoOfWheels(){
        return 2;
    }
};
int main(){
    //initialise objects for car and bike
    Bike bike("petrol","Honda","Activa","Black",60.00,80000,70.00,"Scooter");
    Car car("petrol","maruti","swift","red",15.00,500000,4,"sedan");

    //get number of wheels for car and bike
    cout<<"Number of wheels for Car - "<<car.getNoOfWheels()<<endl;
    cout<<"Number of wheels for Bike - "<<bike.getNoOfWheels()<<endl;
    //> operator overloading. 
    cout<<"Price of bike greater than car - "<<( bike > car)<<endl;
    cout<<"Price of car greater than bike - "<<( car > bike)<<endl;
    cout << bike;
    cout << car;
}