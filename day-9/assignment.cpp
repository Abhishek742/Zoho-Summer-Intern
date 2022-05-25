#include "booking.cpp"
using namespace std;

class BookFlightTickets
{
    vector<Flight> flights;
    vector<Booking> bookings;

public:
    void addFlight()
    {
        Flight f("A114");
        flights.push_back(f);
    }
    void bookTickets()
    {
        string flightNumber;
        Booking currentBooking;
        cout << "Enter the flight number : ";
        cin >> flightNumber;
        for (int i = 0; i < flights.size(); i++)
        {
            if (flightNumber == flights[i].getName())
            {
                currentBooking.bookTicket(flights[i]);
            }
        }
    }
};

int main()
{
    BookFlightTickets bft;
    bft.addFlight();
    bft.bookTickets();
}