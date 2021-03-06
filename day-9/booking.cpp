#include "flight.cpp"

class Booking
{
    string passengerName, bookingID;
    char seatType;
    Flight *flight;
    float bill, cancellationFee;
    bool mealOrdered;
    vector<Ticket> ticketDetails;
    static int count;

public:
    Booking()
    {
        this->bill = 0;
        bookingID = "";
        this->mealOrdered = false;
        count++;
        cancellationFee = 0;
    }
    string getBookingID()
    {
        return this->bookingID;
    }
    void generateBookingID()
    {
        bookingID = flight->getName() + '-' + seatType + '-' + to_string(count);
        cout << "Booking ID : " << this->bookingID << endl;
    }

    pair<int, int> setSeat()
    {
        string s;
        cin >> s;
        int j = 0;
        string temp = "";
        pair<int, int> seat;
        while (s[j] != '_')
        {
            temp += s[j];
            j++;
        }
        seat.first = stoi(temp) - 1;
        seat.second = s[s.length() - 1] - 65;
        return seat;
    }

    void bookTicket(Flight *flight)
    {
        this->flight = flight;
        cout << "Enter your name : ";
        cin >> this->passengerName;
        cout << "\nEnter the class Economy(e) or Business(b) : ";
        cin >> this->seatType;
        flight->printSeats(this->seatType);
        int seatCount;
        cout << "\nEnter the number of seats to be booked : ";
        cin >> seatCount;
        cout << "\nEnter the seats to be booked in the format '5_F' : \n";
        vector<pair<int, int>> seats;
        for (int i = 0; i < seatCount; i++)
        {
            seats.push_back(this->setSeat());
        }
        if (flight->checkValidTickets(seats, seatType, 'b'))
        {
            this->bookMeal();
            ticketDetails = flight->bookTicket(seats, seatType, mealOrdered);
            calculateBill();
            generateBookingID();
            printBookingSummary();
        }
        else
            cout << "\nInvalid Seat number or Seats already Booked!!!\n";
    }
    void bookMeal()
    {
        cout << "\nDo you want to book meal ? Y or N : " << endl;
        char s;
        cin >> s;
        if (s == 'Y')
            mealOrdered = true;
        else
            mealOrdered = false;
    }
    void calculateBill()
    {
        this->bill = 0;
        for (int i = 0; i < ticketDetails.size(); i++)
        {
            this->bill += ticketDetails[i].price;
        }
        this->bill += cancellationFee;
    }

    void cancelTicket()
    {
        int seatCount;
        cout << "\nEnter the number of seats to be cancelled : ";
        cin >> seatCount;
        while (1)
        {
            vector<pair<int, int>> seats;
            cout << "\nEnter the seats to be cancelled : \n";
            for (int i = 0; i < seatCount; i++)
            {
                seats.push_back(this->setSeat());
            }
            if (flight->checkValidTickets(seats, seatType, 'c'))
            {
                vector<Ticket>::iterator ticket;
                for (int i = 0; i < seats.size(); i++)
                {
                    auto ticket = ticketDetails.begin();
                    while (ticket != ticketDetails.end())
                    {
                        if (ticket->seat.first == seats[i].first && ticket->seat.second == seats[i].second)
                        {
                            flight->cancelTicket(ticket, seatType);
                            cancellationFee += 200;
                            ticketDetails.erase(ticket);
                            break;
                        }
                        ticket++;
                    }
                }
                this->flight->printSeats(seatType);
                calculateBill();
                printBookingSummary();
                return;
            }
            cout << "\nEnter valid Seat numbers!!!";
        }
    }
    void printBookingSummary()
    {
        cout << "\n\nTickets Summary :";
        cout << "\nBooking ID : " << bookingID;
        cout << "\nBooked under User Name : " << passengerName;
        cout << "\nNumber of Tickets : " << ticketDetails.size();
        cout << "\nFlight Number : " << flight->getName();
        cout << "\nTotal Bill Amount - " << bill << endl;
        for (int i = 0; i < ticketDetails.size(); i++)
        {
            cout << "\nSeat Number - ";
            cout << ticketDetails[i].seat.first + 1 << "_" << char(ticketDetails[i].seat.second + 'A');
            cout << "\nSeat Type - ";
            cout << ticketDetails[i].seatPreference;
            cout << "\nPrice - ";
            cout << ticketDetails[i].price << endl
                 << endl;
        }
    }
};
int Booking::count = 0;