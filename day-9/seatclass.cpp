#include "ticket.cpp"
class SeatClass
{
    float price;
    int rowsCount;
    string seatClassName;
    vector<vector<char>> arrangement;
    vector<int> partitions;
    vector<vector<bool>> meals, seatsBooked;

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
            vector<bool> seatsBookedRow(arrangement[i].size(), false);
            seatsBooked.push_back(seatsBookedRow);
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
                cout << (seatsBooked[i][j] ? '-' : arrangement[i][j]) << "  ";
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
    bool checkValidSeat(vector<pair<int, int>> &seats, char action)
    {
        if (action == 'b')
        {
            for (int i = 0; i < seats.size(); i++)
            {
                if (seats[i].first >= arrangement.size() || seats[i].second >= arrangement[0].size() || seatsBooked[seats[i].first][seats[i].second] == true)
                    return false;
            }
            return true;
        }
        else
        {
            for (int i = 0; i < seats.size(); i++)
            {
                if (seats[i].first >= arrangement.size() || seats[i].second >= arrangement[0].size() || seatsBooked[seats[i].first][seats[i].second] == false)
                    return false;
            }
            return true;
        }
    }
    vector<Ticket> bookTicket(vector<pair<int, int>> &seats, bool meal)
    {
        vector<Ticket> tickets;
        for (int i = 0; i < seats.size(); i++)
        {
            float currPrice = this->price;
            if (arrangement[seats[i].first][seats[i].second] == 'W' || arrangement[seats[i].first][seats[i].second] == 'A')
                currPrice += 100;
            seatsBooked[seats[i].first][seats[i].second] = true;
            if (meal)
            {
                meals[seats[i].first][seats[i].second] = true;
                currPrice += 200;
            }
            Ticket currTicket(seats[i], arrangement[seats[i].first][seats[i].second], currPrice, meal);
            tickets.push_back(currTicket);
        }
        this->printAvailableSeats();
        this->printMealDetails();
        return tickets;
    }
    void cancelTicket(vector<Ticket>::iterator ticket)
    {
        if (seatsBooked[ticket->seat.first][ticket->seat.second])
        {
            seatsBooked[ticket->seat.first][ticket->seat.second] = false;
            meals[ticket->seat.first][ticket->seat.second] = false;
        }
        else
            cout << ticket->seat.first << " " << ticket->seat.second;
    }
};
