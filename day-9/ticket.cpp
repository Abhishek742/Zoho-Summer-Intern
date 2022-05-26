#include <bits/stdc++.h>
using namespace std;
class Ticket
{
public:
    pair<int, int> seat;
    char seatPreference;
    bool mealPrefered;
    float price;
    Ticket() : price(0){};
    Ticket(pair<int, int> &seat, char seatPreference, float price, bool mealPrefered) : seat(seat), seatPreference(seatPreference), price(price), mealPrefered(mealPrefered){};
};