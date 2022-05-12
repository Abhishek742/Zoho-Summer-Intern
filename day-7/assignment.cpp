#include <bits/stdc++.h>
using namespace std;

void split(string s, vector<string> &arr)
{
    stringstream ss(s);
    string temp;
    while (getline(ss, temp, ' '))
    {
        arr.push_back(temp);
    }
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].size(); j++)
        {
            if (isalpha(arr[i][j]))
                arr[i][j] = tolower(arr[i][j]);
        }
    }
}

void truncateFloat(string &s)
{
    int i = 0;
    while (!isalpha(s[i]))
    {
        i++;
    }
    s = s.substr(0, i);
}

class Device
{
    bool turnedOn;
    string name;

public:
    Device(string name) : name(name){};
    void turnOn()
    {
        this->turnedOn = true;
        cout << this->name << " turned ON\n";
    }
    void turnOff()
    {
        this->turnedOn = false;
        cout << this->name << " turned OFF\n";
    }
};

Device fan("Fan"), light("Light"), door("Door"), alarm("Alarm");

class Sensor
{
    float value;
    float limit;
    string opr, devicename, func;

public:
    Sensor(float value) : value(value){};
    void onChange()
    {
        if (checkCondition())
            action();
    }
    void changeValue(char ch)
    {
        if (ch == 'i')
            this->value++;
        if (ch == 'd')
            this->value--;
        onChange();
    }
    void setConditionAction(vector<string> &cond, vector<string> &act)
    {
        this->opr = cond[2];
        this->limit = stof(cond[3]);
        this->devicename = act[1];
        this->func = act[2];
    }
    bool checkCondition()
    {
        if (this->opr == ">")
            return (value > limit);
        if (this->opr == ">=")
            return (value >= limit);
        if (this->opr == "==")
            return (value == limit);
        if (this->opr == "<")
            return (value < limit);
        if (this->opr == "<=")
            return (value <= limit);
        return false;
    }
    void action()
    {
        if (devicename == "fan")
        {
            if (func == "turnon")
                fan.turnOn();
            else
                fan.turnOff();
        }
        else if (devicename == "light")
        {
            if (func == "turnon")
                light.turnOn();
            else
                light.turnOff();
        }
        else if (devicename == "door")
        {
            if (func == "open")
                door.turnOn();
            else
                door.turnOff();
        }
        else if (devicename == "alarm")
        {
            if (func == "turnon")
                alarm.turnOn();
            else
                alarm.turnOff();
        }
    }
};
Sensor temperature(20.56f), motion(20.34f), waterLevel(18.90f), gas(89.89f);

class ClientApplication
{
public:
    void onConnect()
    {
        cout << "List Of Available Devices and Sensors \nSensors - Temperature,Motion,WaterLevel,Gas\nDevices - SmartFan,SmartLight,DoorControl\n";
        cout << "\nEnter Automation commands in the given syntax\n";
        cout << "If: <sensor_name> <comparision> <sensor_value>\nThen: <device><function>\n\n";
        string condition, action;
        vector<string> cond, act;
        int i = 0;
        while (i < 4)
        {
            getline(cin >> ws, condition);
            getline(cin >> ws, action);
            split(condition, cond);
            split(action, act);
            truncateFloat(cond[3]);
            if (cond[1] == "Temperature")
                temperature.setConditionAction(cond, act);
            else if (cond[1] == "Motion")
                motion.setConditionAction(cond, act);
            else if (cond[1] == "WaterLevel")
                waterLevel.setConditionAction(cond, act);
            else if (cond[1] == "Gas")
                gas.setConditionAction(cond, act);
            else
                cout << "Enter a sensor from the ones mentioned above\n";
            i++;
        }
    }
    void onDisconnect()
    {
    }
    void onBatteryLevelChange()
    {
    }
};

int main()
{
    ClientApplication cli;
    cli.onConnect();
    temperature.changeValue('i');
}