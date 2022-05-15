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
        cout << this->name << (this->name == "Door" ? " Opened\n" : " turned ON\n");
    }
    void turnOff()
    {
        if (!this->turnedOn)
            return;

        this->turnedOn = false;
        cout << this->name << (this->name == "Door" ? " Closed\n" : " turned OFF\n");
    }
};

Device fan("Fan"), light("Light"), door("Door"), alarm("Alarm");

class Sensor
{
    friend class ClientApplication;
    float value, battery, limit;
    string opr, devicename, func, name;
    bool status;

public:
    Sensor(string name, float value, float battery) : name(name), value(value), battery(battery){};
    void setConditionAction(vector<string> &cond, vector<string> &act)
    {
        this->status = true;
        this->opr = cond[2];
        this->limit = stof(cond[3]);
        this->devicename = act[1];
        this->func = act[2];
    }
    void changeValue(char ch, bool (*checkCondition)(Sensor *), void (*action)(Sensor *), void (*inverseAction)(Sensor *), void (*onBatteryChange)(Sensor *))
    {
        // check if the sensor is online
        if (this->status)
        {
            // increase / decrease value of sensor
            if (ch == 'i')
                this->value++;
            else
                this->value--;
            cout << "\nSensor Reading - " << this->value << "\nBattery percentage - " << this->battery - 1 << endl
                 << endl;
            // check if the condition for the event to occur is met
            if (checkCondition(this))
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
};

// Sensor obj(obj_name,initial_value,battery_percentage)
Sensor temperature("Temperature ", 20.56f, 60.00), motion("Motion ", 20.34f, 3.00), waterLevel("Water Level ", 18.90f, 30.00), gas("Gas ", 20.89f, 30.00);

class ClientApplication
{
public:
    void onConnect()
    {
        if (temperature.status)
        {
            cout << "\nTemperature Sensor Connected \n";
        }
        if (motion.status)
        {
            cout << "\nMotion Sensor Connected \n";
        }
        if (waterLevel.status)
        {
            cout << "\nWater Level Sensor Connected \n";
        }
        if (gas.status)
        {
            cout << "\nGas Sensor Connected \n";
        }
    }
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
        onConnect();
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
            // check if the given command is invalid
            if (sense.length() != 2 || ((sense[0] != 't' && sense[0] != 'w' && sense[0] != 'g' && sense[0] != 'm') || (sense[1] != 'i' && sense[1] != 'd')))
            {
                cout << "Enter valid command\n";
                continue;
            }
            onChange(sense);
        }
    }
    void onChange(string sense)
    {
        // lambda functions
        bool (*checkCondtion)(Sensor *) = [](Sensor *s)
        {
            if (s->opr == ">")
                return (s->value > s->limit);
            if (s->opr == ">=")
                return (s->value >= s->limit);
            if (s->opr == "==")
                return (s->value == s->limit);
            if (s->opr == "<")
                return (s->value < s->limit);
            if (s->opr == "<=")
                return (s->value <= s->limit);
            return false;
        };
        void (*action)(Sensor *) = [](Sensor *s)
        {
            if (s->devicename == "fan")
            {
                if (s->func == "turnon")
                    fan.turnOn();
                else
                    fan.turnOff();
            }
            else if (s->devicename == "light")
            {
                if (s->func == "turnon")
                    light.turnOn();
                else
                    light.turnOff();
            }
            else if (s->devicename == "door")
            {
                if (s->func == "open")
                    door.turnOn();
                else
                    door.turnOff();
            }
            else if (s->devicename == "alarm")
            {
                if (s->func == "turnon")
                    alarm.turnOn();
                else
                    alarm.turnOff();
            }
        };
        void (*inverseAction)(Sensor *) = [](Sensor *s)
        {
            if (s->devicename == "fan")
            {
                if (s->func == "turnon")
                    fan.turnOff();
                else
                    fan.turnOn();
            }
            else if (s->devicename == "light")
            {
                if (s->func == "turnon")
                    light.turnOff();
                else
                    light.turnOn();
            }
            else if (s->devicename == "door")
            {
                if (s->func == "open")
                    door.turnOff();
                else
                    door.turnOn();
            }
            else if (s->devicename == "alarm")
            {
                if (s->func == "turnon")
                    alarm.turnOff();
                else
                    alarm.turnOn();
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
            temperature.changeValue(sense[1], checkCondtion, action, inverseAction, onBatteryChange);
        else if (sense[0] == 'w')
            waterLevel.changeValue(sense[1], checkCondtion, action, inverseAction, onBatteryChange);
        else if (sense[0] == 'g')
            gas.changeValue(sense[1], checkCondtion, action, inverseAction, onBatteryChange);
        else if (sense[0] == 'm')
            motion.changeValue(sense[1], checkCondtion, action, inverseAction, onBatteryChange);
    }
    void onDisconnect()
    {
        if (temperature.status)
        {
            cout << "\nTemperature Sensor Disconnected \n";
        }
        if (motion.status)
        {
            cout << "\nMotion Sensor Disconnected \n";
        }
        if (waterLevel.status)
        {
            cout << "\nWater Level Sensor Disconnected \n";
        }
        if (gas.status)
        {
            cout << "\nGas Sensor Disconnected \n";
        }
    }
};

int main()
{
    system("CLS");
    ClientApplication cli;
    cout << "\n\n\t\t\t\t\tDevice Automation\n\n";
    cli.automateCommands();
    cli.onDisconnect();
    char c;
    cin >> c;
}