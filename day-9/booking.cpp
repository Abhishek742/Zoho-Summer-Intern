#include "flight.cpp"
using namespace std;

class Booking
{
    string passengerName, bookingID;
    Flight flight;
    float bill;
public:
    Booking() {}
    void generateBookingID()
    {
    }
    void bookTicket(Flight &ft)
    {
        flight = ft;
        cout << "Enter the class Economy(e) or Business(b) : ";
        char c;
        cin >> c;
        ft.printSeats(c);
        int seatCount;
        cout << "Enter the number of seats to be booked : ";
        cin >> seatCount;
        cout << "Enter the seats to be booked in the format '5_F' : \n";
        vector<pair<int, int>> seats;
        for (int i = 0; i < seatCount; i++)
        {
            string s;
            getline(cin >> ws, s, '_');
            pair<int, int> seat;
            seat.first = stoi(s) - 1;
            getline(cin >> ws, s);
            seat.second = s[0] - 65;
            seats.push_back(seat);
        }
        if (flight.checkValidTickets(seats, c))
        {
            cout << "Valid";
            this->bill = flight.bookTicket(seats,c);
            
        }
        else
            cout << "invalid";
    }
    void bookMeal()
    {
    }
    void cancelTicket()
    {
    }
    void bookingSummary()
    {
    }
};