#include "seatclass.cpp"

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
        iFile.open(".\\Flights\\" + flightname + ".txt");
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
    void printMealBookings(char type = 'a')
    {
        if (type == 'b' || type == 'a')
        {
            business.printMealDetails();
        }
        if (type == 'e' || type == 'a')
        {
            economic.printMealDetails();
        }
    }
    bool checkValidTickets(vector<pair<int, int>> &seats, char type, char action)
    {
        if (type == 'b')
            return business.checkValidSeat(seats, action);
        else if (type == 'e')
            return economic.checkValidSeat(seats, action);
        else
            return false;
    }
    vector<Ticket> bookTicket(vector<pair<int, int>> &seats, char type, bool meal)
    {
        vector<Ticket> tickets;
        float bill;
        if (type == 'b')
        {
            tickets = business.bookTicket(seats, meal);
            business.setPrice(200);
        }
        else
        {
            tickets = economic.bookTicket(seats, meal);
            economic.setPrice(100);
        }
        return tickets;
    }

    void cancelTicket(vector<Ticket>::iterator ticket, char seatType)
    {
        if (seatType == 'b')
        {
            business.cancelTicket(ticket);
        }
        else
            economic.cancelTicket(ticket);
        this->printSeats();
    }
};