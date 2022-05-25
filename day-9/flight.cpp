#include <bits/stdc++.h>
using namespace std;

class SeatClass
{
    float price;
    int rowsCount;
    string seatClassName;
    vector<vector<char>> arrangement;
    vector<int> partitions;
    vector<vector<bool>> meals;

public:
    SeatClass() : price(0), rowsCount(0){};
    void setDetails(float price, string name)
    {
        this->price = price;
        this->seatClassName = name;
    }
    float getPrice()
    {
        return this->price;
    }
    void setPrice(float price)
    {
        this->price += price;
    }
    void initialiseSeats(string line)
    {
        int i = 0;
        while (i < line.size())
        {
            // identify the number of columns and rows from file
            if (line[i] == '{')
            {
                // find column count
                while (line[i] != '}')
                {
                    string partition_string = "";
                    i++;
                    while (line[i] != ',' && line[i] != ' ' && line[i] != '}')
                    {
                        partition_string += line[i];
                        i++;
                    }
                    if (partition_string.length() != 0)
                        partitions.push_back(stoi(partition_string));
                }
                // find number of rows
                string row_string = "";
                while (i < line.size())
                {
                    if (line[i] != ',' && line[i] != ' ' && line[i] != '}')
                    {
                        row_string += line[i];
                    }
                    i++;
                }
                rowsCount = stoi(row_string);
            }
            else
            {
                i++;
            }
        }
        // initialise the seats matrix(economic or business) with the seat type
        vector<char> row;
        for (int i = 0; i < partitions.size(); i++)
        {
            for (int j = 0; j < partitions[i]; j++)
            {
                if ((i == 0 && j == 0) || (i == partitions.size() - 1 && j == partitions[i] - 1))
                {
                    row.push_back('W');
                }
                else if (j == 0 || j == partitions[i] - 1)
                {
                    row.push_back('A');
                }
                else
                    row.push_back('M');
            }
        }
        for (int i = 0; i < rowsCount; i++)
        {
            arrangement.push_back(row);
        }
        for (int i = 0; i < arrangement.size(); i++)
        {
            vector<bool> mealRow(arrangement[i].size(), false);
            meals.push_back(mealRow);
        }
    }

    void printAvailableSeats()
    {
        cout << "Available " << this->seatClassName << " Seats\n";
        cout << "\t";
        for (int k = 0, m = 0, n = 0; k < arrangement[0].size(); k++)
        {
            cout << char(k + 'A') << "  ";
            m++;
            if (m == partitions[n])
            {
                cout << "  ";
                n++;
                m = 0;
                continue;
            }
        }
        cout << endl
             << endl;
        for (int i = 0; i < arrangement.size(); i++)
        {
            cout << i + 1 << "\t";
            for (int j = 0, m = 0, n = 0; j < arrangement[i].size(); j++)
            {
                cout << arrangement[i][j] << "  ";
                m++;
                if (m == partitions[n])
                {
                    cout << "  ";
                    n++;
                    m = 0;
                    continue;
                }
            }
            cout << endl;
        }
    }
    void printMealDetails()
    {
        cout << "Meal Details for " << this->seatClassName << "\n";
        cout << "\t";
        for (int k = 0, m = 0, n = 0; k < meals[0].size(); k++)
        {
            cout << char(k + 'A') << "  ";
            m++;
            if (m == partitions[n])
            {
                cout << "  ";
                n++;
                m = 0;
                continue;
            }
        }
        cout << endl
             << endl;
        for (int i = 0; i < meals.size(); i++)
        {
            cout << i + 1 << "\t";
            for (int j = 0, m = 0, n = 0; j < meals[i].size(); j++)
            {
                cout << meals[i][j] << "  ";
                m++;
                if (m == partitions[n])
                {
                    cout << "  ";
                    n++;
                    m = 0;
                    continue;
                }
            }
            cout << endl;
        }
    }
    bool checkValidSeat(vector<pair<int, int>> &seats)
    {
        for (int i = 0; i < seats.size(); i++)
        {
            if (seats[i].first >= arrangement.size() || seats[i].second >= arrangement[0].size() || arrangement[seats[i].first][seats[i].second] == '-')
                return false;
        }
        return true;
    }
    float bookTicket(vector<pair<int, int>> &seats, bool meal)
    {
        float bill = seats.size() * this->price;
        if (meal)
            bill += seats.size() * 200;
        for (int i = 0; i < seats.size(); i++)
        {
            if (arrangement[seats[i].first][seats[i].second] == 'W' || arrangement[seats[i].first][seats[i].second] == 'A')
                bill += 100;
            arrangement[seats[i].first][seats[i].second] = '-';
            if (meal)
                meals[seats[i].first][seats[i].second] = true;
        }
        this->printAvailableSeats();
        this->printMealDetails();
        return bill;
    }
};

class Flight
{
    float economicPrice, businessPrice;
    SeatClass economic, business;
    string name;

public:
    Flight() {}
    Flight(string flightname)
    {
        economic.setDetails(1000.0, "Economic");
        business.setDetails(2000.0, "Business");
        this->name = flightname;
        ifstream iFile;
        iFile.open(flightname + ".txt");
        string line;
        while (getline(iFile, line))
        {
            string classtype = "";
            int i = 0;
            while (line[i] != ' ')
            {
                classtype += tolower(line[i]);
                i++;
            }
            if (classtype == "business")
                business.initialiseSeats(line);
            else if (classtype == "economic")
                economic.initialiseSeats(line);
            else
                cout << "Class type invalid!!!\n";
        }
    }
    string getName()
    {
        return this->name;
    }
    void printSeats(char type = 'a')
    {
        if (type == 'b' || type == 'a')
        {
            business.printAvailableSeats();
        }
        if (type == 'e' || type == 'a')
        {
            economic.printAvailableSeats();
        }
    }
    bool checkValidTickets(vector<pair<int, int>> &seats, char type)
    {
        if (type == 'b')
            return business.checkValidSeat(seats);
        else if (type == 'e')
            return economic.checkValidSeat(seats);
        else
            return false;
    }
    float bookTicket(vector<pair<int, int>> &seats, char type, bool meal)
    {
        float bill;
        if (type == 'b')
        {
            bill = business.bookTicket(seats, meal);
            business.setPrice(200);
        }
        else
        {
            bill = economic.bookTicket(seats, meal);
            economic.setPrice(100);
        }
        return bill;
    }
    void cancelTicket()
    {
    }
};