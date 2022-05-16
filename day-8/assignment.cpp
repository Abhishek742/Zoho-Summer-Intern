#include <bits/stdc++.h>
using namespace std;

class MobileConnection
{
public:
    string number;
    float dueAmount;
    MobileConnection() : number(""), dueAmount(0){};
    MobileConnection(string number, float dueAmount) : number(number), dueAmount(dueAmount){};
    bool isFound(string num)
    {
        if (this->number == num && num.length() == 10)
            return true;
        else
            return false;
    }
    void printConnection()
    {
        cout << "\nNumber - " << this->number << "\nDue Amount - " << this->dueAmount << "\n";
    }
};
class LandlineConnection
{
public:
    string number, stdcode;
    float dueAmount;
    LandlineConnection() : number(""), stdcode(""), dueAmount(0){};
    LandlineConnection(string number, string stdcode, float dueAmount) : number(number), stdcode(stdcode), dueAmount(dueAmount){};
    bool isFound(string num)
    {
        if (this->stdcode == num.substr(0, num.length() - 6) && this->number == num.substr(num.length() - 6, num.length() - 1))
            return true;
        else
            return false;
    }
    void printConnection()
    {
        cout << "\nNumber - " << this->number << "\nSTD code - " << this->stdcode << "\nDue Amount - " << this->dueAmount << "\n";
    }
};

template <class T>
class BillPayment
{
    vector<T> connections;

public:
    void addConnection(T connection)
    {
        connections.push_back(connection);
    }
    bool payBill(string num)
    {
        int index = findConnection(num);
        if (index == -1)
            return false;
        connections[index].dueAmount = 0;
        return true;
    }
    bool updateBill(string num, float amount)
    {
        int index = findConnection(num);
        if (index == -1)
            return false;
        connections[index].dueAmount += amount;
        return true;
    }
    int findConnection(string num)
    {
        for (int i = 0; i < connections.size(); i++)
        {
            if (connections[i].isFound(num))
                return i;
        }
        // indicate number not found
        return -1;
    }
    void showConnections()
    {
        for_each(connections.begin(), connections.end(), [](T connection)
                 { connection.printConnection(); });
    }
};

int main()
{
    BillPayment<MobileConnection> mobc;
    BillPayment<LandlineConnection> landc;

    MobileConnection mob;
    LandlineConnection lan;
    string num;
    float due;
    int choice = 0;
    while (choice != 7)
    {
        system("CLS");
        cout << "Common Billing System\n";
        cout << "1) Add new mobile connection\n";
        cout << "2) Add new landline connection\n";
        cout << "3) Pay bill using connection number\n";
        cout << "4) Update bill using connection number\n";
        cout << "5) Show Mobile Connections\n";
        cout << "6) Show Landline Connections\n";
        cout << "7) Exit\n";
        cout << "Enter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Mobile number and due amount to add connection : \n";
            cin >> mob.number >> mob.dueAmount;
            if (mob.number.length() != 10)
            {
                cout << "Mobile number invalid - must be of 10 digits!!!\n";
                break;
            }
            mobc.addConnection(mob);
            break;
        case 2:
            cout << "Enter Landline number,STD code and due amount to add connection : \n";
            cin >> lan.stdcode >> lan.number >> lan.dueAmount;
            if (lan.number.length() != 6)
            {
                cout << "Landline number invalid - Number must be of 6 digits!!!\n";
                break;
            }
            landc.addConnection(lan);
            break;
        case 3:
            cout << "Enter Number to pay bill : ";
            cin >> num;
            if (mobc.payBill(num) || landc.payBill(num))
                cout << "Bill paid successfully!!!\n";
            else
                cout << "Number not found in common billing system!!!\n";
            break;
        case 4:
            cout << "Enter Number and amount to update bill : ";
            cin >> num >> due;
            if (mobc.updateBill(num, due) || landc.updateBill(num, due))
                cout << "Bill updated successfully!!!\n";
            else
                cout << "Number not found in common billing system!!!\n";
            break;
        case 5:
            cout << "\nMobile Connections\n";
            mobc.showConnections();
            break;
        case 6:
            cout << "\nLandline Connections\n";
            landc.showConnections();
            break;
        case 7:
            exit(0);
        }
        char c;
        cout << "\nEnter any character to go to main menu : ";
        cin >> c;
    }
    return 0;
}