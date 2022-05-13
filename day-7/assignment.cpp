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
        if (this->turnedOn)
            return;
        this->turnedOn = true;
        cout << this->name << (this->name == "door" ? "Door Opened" : " turned ON\n ");
    }
    void turnOff()
    {
        if (!this->turnedOn)
            return;

        this->turnedOn = false;
        cout << this->name << " turned OFF\n";
    }
};

Device fan("Fan"), light("Light"), door("Door"), alarm("Alarm");

class Sensor
{
    float value, battery, limit;
    string opr, devicename, func, name;
    bool status;

public:
    Sensor(string name, float value, float battery) : name(name), value(value), battery(battery){};
    void onChange()
    {
        if (checkCondition())
            action();
        else
            inverseAction();
    }
    void changeValue(char ch)
    {
        if (ch == 'i')
            this->value++;
        else if (ch == 'd')
            this->value--;
        else
        {
            cout << "Enter valid command for sensing - i or d\n";
            return;
        }
        cout << endl
             << this->value << endl;
        if (this->status)
            onChange();
        else
            cout << this->name << " Offline - Low Battery\n";
        batteryChange();
    }
    void setConditionAction(vector<string> &cond, vector<string> &act)
    {
        this->status = true;
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
    void inverseAction()
    {
        if (devicename == "fan")
        {
            if (func == "turnon")
                fan.turnOff();
            else
                fan.turnOn();
        }
        else if (devicename == "light")
        {
            if (func == "turnon")
                light.turnOff();
            else
                light.turnOn();
        }
        else if (devicename == "door")
        {
            if (func == "open")
                door.turnOff();
            else
                door.turnOn();
        }
        else if (devicename == "alarm")
        {
            if (func == "turnon")
                alarm.turnOff();
            else
                alarm.turnOn();
        }
    }
    void batteryChange()
    {
        this->battery--;
        if (this->battery > 0)
            return;
        this->status = false;
    }
};
Sensor temperature("Temperature ", 20.56f, 3.00), motion("Motion ", 20.34f, 3.00), waterLevel("Water Level ", 18.90f, 3.00), gas("Gas ", 20.89f, 3.00);

class ClientApplication
{
public:
    void onConnect()
    {
        cout << "List Of Available Devices and Sensors \nSensors - Temperature,Motion,WaterLevel,Gas\nDevices - SmartFan,SmartLight,DoorControl\n";
        cout << "\nEnter Automation commands in the given syntax\n";
        cout << "If: <sensor_name> <comparision> <sensor_value>\nThen: <device><function>\n\n";
        int i = 0;
        while (i < 4)
        {
            string condition, action;
            vector<string> cond, act;
            getline(cin >> ws, condition);
            getline(cin >> ws, action);
            split(condition, cond);
            split(action, act);
            truncateFloat(cond[3]);
            if (cond[1] == "temperature")
            {
                temperature.setConditionAction(cond, act);
                cout << "Temperature Sensor ONLINE \n";
            }
            else if (cond[1] == "motion")
            {
                motion.setConditionAction(cond, act);
                cout << "Motion Sensor ONLINE \n";
            }

            else if (cond[1] == "waterlevel")
            {
                waterLevel.setConditionAction(cond, act);
                cout << "Water Level Sensor ONLINE \n";
            }
            else if (cond[1] == "gas")
            {
                gas.setConditionAction(cond, act);
                cout << "Gas Sensor ONLINE \n";
            }
            else
                cout << "Enter a sensor from the ones mentioned above\n";
            i++;
        }
        startSensing();
    }
    void startSensing()
    {
        string sense = "sensing";
        while (1)
        {
            cin >> sense;
            if (sense == "exit")
                return;
            if (sense.length() != 2)
            {
                cout << "Enter valid command\n";
                continue;
            }
            if (sense[0] == 't')
                temperature.changeValue(sense[1]);
            if (sense[0] == 'w')
                waterLevel.changeValue(sense[1]);
            if (sense[0] == 'g')
                gas.changeValue(sense[1]);
            if (sense[0] == 'm')
                motion.changeValue(sense[1]);
        }
    }
    void onDisconnect()
    {
    }
};

int main()
{
    ClientApplication cli;
    cout << "\n\n\t\t\t\t\tDevice Automation\n";
    cli.onConnect();
}