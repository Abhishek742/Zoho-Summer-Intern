#include "./user-portal/user-portal.cpp"
#include "./project-portal/project-portal.cpp"
using namespace std;

class Notepad
{
    bool userLoggedIn;
    Users users;
    UserPortal up;
    int currUser;

public:
    Notepad()
    {
        this->userLoggedIn = false;
    }
    bool isLoggedIn()
    {
        return userLoggedIn;
    }
    void readUsers()
    {
        ifstream inStream;
        inStream.open("./user-portal/users.txt", ios::in);
        users.ParseFromIstream(&inStream);
        inStream.close();
    }
    void writeUsers()
    {
        ofstream outStream;
        outStream.open("./user-portal/users.txt", ios::out);
        users.SerializeToOstream(&outStream);
        outStream.close();
    }
    void loginAccount()
    {
        cout << "MINI NOTEPAD\n";
        int choice;
        while (1)
        {
            system("clear");
            cout << "Login Portal\n";
            cout << "\n1)Sign In\n2)Sign Up\n3)Exit\n";
            cin >> choice;
            switch (choice)
            {
            case 1:
                readUsers();
                currUser = up.login(users);
                if (currUser != -1)
                {
                    this->userLoggedIn = true;
                    return;
                }
                break;

            case 2:
                readUsers();
                up.signup(users);
                writeUsers();
                break;

            case 3:
                exit(0);
            }

            string ch;
            cout<<"\nEnter any key to continue : ";
            getline(cin>>ws,ch);
        }
    }
    void openProjectsPortal()
    {
        // get the reference of the current user
        const User &user = users.users(currUser);
        // create a project portal with the current logged in user.
        ProjectPortal projectPortal(user.username());
        int choice;
        string ch;

        while (1)
        {
            system("clear");
            cout << "Projects Portal\n";
            cout << "\n1)Create New File\n2)List All Projects\n3)Open Project\n4)Logout\n";
            cin >> choice;
            switch (choice)
            {
            case 1:
                projectPortal.createNewProject();
                break;

            case 2:
                projectPortal.listAllProjects();
                break;

            case 3:
                projectPortal.openProject();
                break;
            case 4:
                return;
            default:
                break;
            }

            cout << "\nEnter any character to continue : ";
            getline(cin >> ws, ch);
        }
    }
};

int main()
{
    Notepad notepad;
    // prompt to login everytime
    while (1)
    {
        //exit condition is set inside loginAccount()
        notepad.loginAccount();
        if (notepad.isLoggedIn())
            notepad.openProjectsPortal();
    }

    return 0;
}