#include "./user-portal/user-portal.cpp"
using namespace std;

class Notepad
{
    bool userLoggedIn;
    UserPortal up;
    int currUser;
public:
    Notepad()
    {
        this->userLoggedIn = false;
    }
    bool isLoggedIn(){
        return userLoggedIn;
    }
    void loginAccount()
    {
        cout << "MINI NOTEPAD\n";
        int choice;
        while (1)
        {
            cout << "\n1)Sign In\n2)Sign Up\n3)Exit\n";
            cin >> choice;
            switch (choice)
            {
            case 1:
                currUser = up.login();
                if (currUser != -1)
                {
                    this->userLoggedIn = true;
                    return;
                }
                break;

            case 2:
                up.signup();
                break;

            case 3:
                return;
            }
        }
    }
    void openProjectsPortal(){
        cout<<"Entered Project Portal for user : "<<currUser<<endl;
    }
};

int main()
{
    Notepad notepad;
    notepad.loginAccount();
    if(notepad.isLoggedIn()) notepad.openProjectsPortal();
    return 0;
}