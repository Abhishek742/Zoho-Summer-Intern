#include <bits/stdc++.h>
using namespace std;

// using array of functions with lambda functions to set the condition for automation
vector<bool (*)(float, float)> conditions;
void setConditionFunctions()
{
    conditions.push_back([](float a, float b)
                         { return a > b; });
    conditions.push_back([](float a, float b)
                         { return a < b; });
    conditions.push_back([](float a, float b)
                         { return a >= b; });
    conditions.push_back([](float a, float b)
                         { return a <= b; });
    conditions.push_back([](float a, float b)
                         { return a == b; });
}

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
    bool turnedOn, connected;
    string name;

public:
    Device(string name) : name(name){};
    void turnOn()
    {
        if (this->turnedOn)
            return;
        this->turnedOn = true;
        cout << this->name << (this->name == "Door" ? " Opened\n" : " turned ON\n");
    }
    void turnOff()
    {
        if (!this->turnedOn)
            return;

        this->turnedOn = false;
        cout << this->name << (this->name == "Door" ? " Closed\n" : " turned OFF\n");
    }
    bool isConnected()
    {
        return this->connected;
    }
    void connect()
    {
        this->connected = true;
        cout << this->name << " Connected\n";
    }
    void disconnect()
    {
        this->connected = false;
        cout << this->name << " Disconnected\n";
    }
    string status()
    {
        if (this->turnedOn)
            return (this->name == "Door" ? "OPEN" : "ON");
        else
            return (this->name == "Door" ? "CLOSED" : "OFF");
    }
};

Device fan("Fan"), light("Light"), door("Door"), alarm("Alarm");

class Sensor
{
    friend class ClientApplication;
    float value, battery, limit;
    string devicename, func, name;
    bool status;

public:
    bool (*checkCondition)(float, float);
    Sensor(string name, float value, float battery) : name(name), value(value), battery(battery){};
    void setConditionAction(vector<string> &cond, vector<string> &act)
    {
        this->status = true;
        this->limit = stof(cond[3]);
        this->devicename = act[1];
        this->func = act[2];
        if (cond[2] == ">")
            this->checkCondition = conditions[0];
        else if (cond[2] == "<")
            this->checkCondition = conditions[1];
        else if (cond[2] == ">=")
            this->checkCondition = conditions[2];
        else if (cond[2] == "<=")
            this->checkCondition = conditions[3];
        else if (cond[2] == "=" || cond[2] == "==")
            this->checkCondition = conditions[4];
        else
            return;
    }
    void changeValue(char ch, void (*action)(Sensor *), void (*inverseAction)(Sensor *), void (*onBatteryChange)(Sensor *))
    {
        // check if the sensor is online
        if (this->status)
        {
            // increase / decrease value of sensor
            if (ch == 'i')
                this->value++;
            else
                this->value--;

            // check if the condition for the event to occur is met
            if (checkCondition(this->value, this->limit))
                action(this);
            else
                inverseAction(this);

            // invoke the battery change event
            onBatteryChange(this);
        }
        else
            cout << endl
                 << this->name << "Sensor Disconnected - Low Battery\n";
    }
    float getReading()
    {
        return this->value;
    }
    float getBattery()
    {
        return this->battery;
    }
};

// Sensor obj(obj_name,initial_value,battery_percentage)
Sensor temperature("Temperature ", 20.56f, 60.00), motion("Motion ", 20.34f, 3.00), waterLevel("Water Level ", 18.90f, 30.00), gas("Gas ", 20.89f, 30.00);

void printStatus()
{
    cout << "\nSENSORS\t\t\tSTATUS\n-------\t\t\t------\n";
    cout << "FAN\t\t\t" << fan.status() << endl;
    cout << "LIGHT\t\t\t" << light.status() << endl;
    cout << "ALARM\t\t\t" << alarm.status() << endl;
    cout << "DOOR\t\t\t" << door.status() << endl;
    cout << "TEMP\t\t\t"
         << "READING : " << temperature.getReading() << " BATTERY : " << temperature.getBattery() << endl;
    cout << "GAS\t\t\t"
         << "READING : " << gas.getReading() << " BATTERY : " << gas.getBattery() << endl;
    cout << "WATER\t\t\t"
         << "READING : " << waterLevel.getReading() << " BATTERY : " << waterLevel.getBattery() << endl;
    cout << "MOTION\t\t\t"
         << "READING : " << motion.getReading() << " BATTERY : " << motion.getBattery() << endl
         << endl;
}

class ClientApplication
{
public:
    void automateCommands()
    {
        cout << "List Of Available Devices and Sensors \n\nSensors - Temperature,Motion,WaterLevel,Gas\nDevices - SmartFan,SmartLight,DoorControl\n";
        cout << "\nEnter Automation commands in the given syntax\n\n";
        cout << "If: <sensor_name> <comparision> <sensor_value>\nThen: <device> <function>\n\n";
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
            if (cond[0] != "if:" || act[0] != "then:")
            {
                cout << "Enter valid command in the given syntax!!\n";
                continue;
            }
            if (cond[1] == "temperature")
            {
                temperature.setConditionAction(cond, act);
            }
            else if (cond[1] == "motion")
            {
                motion.setConditionAction(cond, act);
            }

            else if (cond[1] == "waterlevel")
            {
                waterLevel.setConditionAction(cond, act);
            }
            else if (cond[1] == "gas")
            {
                gas.setConditionAction(cond, act);
            }
            else
            {
                cout << "Enter a sensor from the ones mentioned above\n";
                continue;
            }
            i++;
        }
    }
    void startSensing()
    {
        string sense = "sensing";
        while (1)
        {
            cin >> sense;
            if (sense == "exit")
                return;
            // check if the given command is invalid
            if (sense.length() != 2 || ((sense[0] != 't' && sense[0] != 'w' && sense[0] != 'g' && sense[0] != 'm' && sense[0] != 'f' && sense[0] == 'l' && sense[0] == 'd' && sense[0] == 'a') || (sense[1] != 'i' && sense[1] != 'd' && sense[1] != 'c')))
            {
                cout << "Enter valid command\n";
                continue;
            }
            onChange(sense);
            printStatus();
        }
    }
    void onChange(string sense)
    {
        // lambda functions
        void (*action)(Sensor *) = [](Sensor *s)
        {
            if (s->devicename == "fan")
            {
                if (fan.isConnected())
                {
                    if (s->func == "turnon")
                        fan.turnOn();
                    else
                        fan.turnOff();
                }
                else
                {
                    cout << "Fan Disconnected!! Cannot Perform operations\n\n";
                }
            }
            else if (s->devicename == "light")
            {
                if (light.isConnected())
                {
                    if (s->func == "turnon")
                        light.turnOn();
                    else
                        light.turnOff();
                }
                else
                    cout << "Light Disconnected!! Cannot Perform Operations when device is disconnected\n";
            }
            else if (s->devicename == "door")
            {
                if (door.isConnected())
                {
                    if (s->func == "open")
                        door.turnOn();
                    else
                        door.turnOff();
                }
                else
                {
                    cout << "Door Disconnected!! Cannot Perform Operations when device is disconnected\n";
                }
            }
            else if (s->devicename == "alarm")
            {
                if (alarm.isConnected())
                {
                    if (s->func == "turnon")
                        alarm.turnOn();
                    else
                        alarm.turnOff();
                }
                else
                {
                    cout << "Alarm Disconnected!! Cannot Perform Operations when device is disconnected\n";
                }
            }
        };
        void (*inverseAction)(Sensor *) = [](Sensor *s)
        {
            if (s->devicename == "fan")
            {
                if (fan.isConnected())
                {
                    if (s->func == "turnon")
                        fan.turnOff();
                    else
                        fan.turnOn();
                }
                else
                {
                    cout << "Fan Disconnected!! Cannot Perform Operations when device is disconnected\n";
                }
            }
            else if (s->devicename == "light")
            {
                if (light.isConnected())
                {
                    if (s->func == "turnon")
                        light.turnOff();
                    else
                        light.turnOn();
                }
                else
                {
                    cout << "Light Disconnected!! Cannot Perform Operations when device is disconnected\n";
                }
            }
            else if (s->devicename == "door")
            {
                if (door.isConnected())
                {
                    if (s->func == "open")
                        door.turnOff();
                    else
                        door.turnOn();
                }
                else
                {
                    cout << "Door Disconnected!! Cannot Perform Operations when device is disconnected\n";
                }
            }
            else if (s->devicename == "alarm")
            {

                if (alarm.isConnected())
                {
                    if (s->func == "turnon")
                        alarm.turnOff();
                    else
                        alarm.turnOn();
                }
                else
                {
                    cout << "Alarm Disconnected!! Cannot Perform Operations when device is disconnected\n";
                }
            }
        };
        void (*onBatteryChange)(Sensor *) = [](Sensor *s)
        {
            if (s->status)
            {
                s->battery--;
                if (s->battery > 0)
                    return;
                s->status = false;
                cout << endl
                     << s->name << "Sensor Disconnected - Low Battery\n";
            }
        };

        // identify which sensor value is about to change and pass in the lambda functions as parameters
        if (sense[0] == 't')
            temperature.changeValue(sense[1], action, inverseAction, onBatteryChange);
        else if (sense[0] == 'w')
            waterLevel.changeValue(sense[1], action, inverseAction, onBatteryChange);
        else if (sense[0] == 'g')
            gas.changeValue(sense[1], action, inverseAction, onBatteryChange);
        else if (sense[0] == 'm')
            motion.changeValue(sense[1], action, inverseAction, onBatteryChange);
        else if (sense[1] == 'c')
            onConnect(sense);
        else if (sense[1] == 'd')
            onDisconnect(sense);
    }
    void onConnect(string sense)
    {
        if (sense[0] == 'f' && !fan.isConnected())
        {
            fan.connect();
        }
        else if (sense[0] == 'l' && !light.isConnected())
        {
            light.connect();
        }
        else if (sense[0] == 'a' && !alarm.isConnected())
        {
            alarm.connect();
        }
        else if (sense[0] == 'd' && !door.isConnected())
        {
            door.connect();
        }
        else
            return;
    }
    void onDisconnect(string sense)
    {
        if (sense[0] == 'f' && fan.isConnected())
        {
            fan.disconnect();
        }
        else if (sense[0] == 'l' && light.isConnected())
        {
            light.disconnect();
        }
        else if (sense[0] == 'a' && alarm.isConnected())
        {
            alarm.disconnect();
        }
        else if (sense[0] == 'd' && door.isConnected())
        {
            door.disconnect();
        }
        else
            return;
    }
};

int main()
{
    system("CLS");
    setConditionFunctions();
    ClientApplication cli;
    int choice = 1;
    while (1)
    {
        printStatus();
        cout << "1.Device Automation\n2.Simulate Input\n3.Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cli.automateCommands();
            break;
        case 2:
            cli.startSensing();
            break;
        case 3:
            return 0;
        }
    }
}