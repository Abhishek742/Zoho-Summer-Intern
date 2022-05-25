#include "flight.cpp"
using namespace std;

class Booking
{
    string passengerName, bookingID;
    Flight flight;
    float bill;
    bool mealOrdered;

public:
    Booking()
    {
        this->bill = 0;
        this->mealOrdered = false;
    }
    void generateBookingID()
    {
    }
    void bookTicket(Flight &flight)
    {
        cout << "Enter the class Economy(e) or Business(b) : ";
        char c;
        cin >> c;
        flight.printSeats(c);
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
            this->bookMeal();
            this->bill = flight.bookTicket(seats, c, mealOrdered);
            cout << "BIll AMount : " << this->bill << endl;
        }
        else
            cout << "invalid";
    }
    void bookMeal()
    {
        cout << "Do you want to book meal ? Y or N : " << endl;
        char s;
        cin >> s;
        if (s == 'Y')
            mealOrdered = true;
    }
    void cancelTicket()
    {
    }
    void bookingSummary()
    {
    }
};