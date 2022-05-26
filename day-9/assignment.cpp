#include "booking.cpp"

namespace fs = std::filesystem;

class BookFlightTickets
{
    vector<Flight> flights;
    vector<Booking> bookings;

public:
    void addFlight()
    {
        // Get all flight details from the folder Flights
        // Open the directory and set the path
        vector<string> fileNames;
        string path = ".\\Flights";

        for (const auto &entry : fs::directory_iterator(path))
        {
            string fileName = "";
            string fileNameExt = entry.path().filename().string();
            int i = 0;
            while (fileNameExt[i] != '.')
            {
                fileName += fileNameExt[i];
                i++;
            }
            fileNames.push_back(fileName);
        }

        for (int i = 0; i < fileNames.size(); i++)
        {
            cout << fileNames[i] << "   ";
        }
        cout << endl;

        // add flights to flight vector based on the filename
        for (int i = 0; i < fileNames.size(); i++)
        {
            Flight flight(fileNames[i]);
            flights.push_back(flight);
        }
    }
    void printAvailableFlights()
    {
        cout << "Available Flights : ";
        for (int i = 0; i < flights.size(); i++)
        {
            cout << flights[i].getName() << "  ";
        }
        cout << endl;
    }
    void printFlightSeats()
    {
        printAvailableFlights();
        cout << "Enter Flight Number : ";
        string flightNumber;
        cin >> flightNumber;
        for (int i = 0; i < flights.size(); i++)
        {
            if (flightNumber == flights[i].getName())
            {
                flights[i].printSeats();
            }
        }
    }
    void printMealOrders()
    {
        printAvailableFlights();
        cout << "\nEnter Flight Number : ";
        string flightNumber;
        cin >> flightNumber;
        for (int i = 0; i < flights.size(); i++)
        {
            if (flightNumber == flights[i].getName())
            {
                flights[i].printMealBookings();
            }
        }
    }
    void bookTickets()
    {
        string flightNumber;
        printAvailableFlights();
        cout << "\nEnter the flight number : ";
        cin >> flightNumber;
        cout << flightNumber;
        Booking currentBooking;
        for (int i = 0; i < flights.size(); i++)
        {
            if (flightNumber == flights[i].getName())
            {
                currentBooking.bookTicket(&flights[i]);
            }
        }
        bookings.push_back(currentBooking);
    }
    void cancelTickets()
    {
        string bookingId;
        bool flag = false;
        while (1)
        {
            cout << "\nEnter the booking ID to cancel tickets.Example: A114-b-1 : ";
            cin >> bookingId;
            for (int i = 0; i < bookings.size(); i++)
            {
                if (bookingId == bookings[i].getBookingID())
                {
                    bookings[i].cancelTicket();
                    flag = true;
                }
            }
            if (flag)
                break;
            cout << "\nEnter Valid Booking ID!!!\n";
        }
    }

    void printBookedID()
    {
        cout << "Previously Booked ID's : \n";
        for (int i = 0; i < bookings.size(); i++)
        {
            cout << bookings[i].getBookingID() << "   ";
        }
    }

    void printSummary()
    {
        string bookingId;
        bool flag = false;
        while (1)
        {
            printBookedID();
            cout << "\nEnter the booking ID for summary. Example: A114-b-1 : ";
            cin >> bookingId;
            for (int i = 0; i < bookings.size(); i++)
            {
                if (bookingId == bookings[i].getBookingID())
                {
                    bookings[i].printBookingSummary();
                    flag = true;
                }
            }
            if (flag)
                break;
            cout << "\nEnter Valid Booking ID!!!\n";
        }
    }
};

void printMenu()
{
    system("CLS");
    cout << "FLIGHT TRACKING SYSTEM\n\n";
    cout << "1.Print Available Flights\n2.Print Available Seats for Flight\n3.Book Tickets\n4.Cancel Tickets\n5.Print Meal Orders for each Flight\n6.Print Summary\n7.Exit\n";
}

int main()
{
    BookFlightTickets bft;
    bft.addFlight();
    int choice;
    char ch;
    while (1)
    {
        printMenu();
        cout << "Enter Choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            bft.printAvailableFlights();
            break;
        case 2:
            bft.printFlightSeats();
            break;
        case 3:
            bft.bookTickets();
            break;
        case 4:
            bft.cancelTickets();
            break;
        case 5:
            bft.printMealOrders();
            break;
        case 6:
            bft.printSummary();
            break;
        case 7:
            return 0;
        }
        cout << "\n\nEnter any character to return to main menu : ";
        cin >> ch;
    }
}