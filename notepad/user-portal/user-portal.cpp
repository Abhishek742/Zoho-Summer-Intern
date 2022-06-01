#include <bits/stdc++.h>
#include "../structure/notepad.pb.h"
using namespace std;

class UserPortal
{
    Users users;

public:
    void readUsers()
    {
        ifstream inStream;
        inStream.open("./user-portal/users.txt", ios::in);
        users.ParseFromIstream(&inStream);
    }
    void writeUsers()
    {
        ofstream outStream;
        outStream.open("./user-portal/users.txt", ios::out);
        users.SerializeToOstream(&outStream);
    }
    int isExistingUser(string username)
    {
        for (int i = 0; i < users.users_size(); i++)
        {
            const User &user = users.users(i);
            if (user.username() == username)
                return i;
        }
        return -1;
    }
    bool isEmailInValid(string email)
    {
        int atIndex = -1, dotIndex = -1;
        int i = 0;
        while (i < email.length())
        {
            if (email[i] == '@')
            {
                atIndex = i;
            }
            else if (atIndex != -1 && email[i] == '.')
            {
                dotIndex = i;
            }
            else
            {
                // if @ isnt visited, we can have alphabets and numbers ie)prefix portion of email
                if (atIndex == -1 && ((email[i] < 'a' || email[i] > 'z') && (email[i] < '0' || email[i] > '9') && email[i] != '.'))
                    return true;

                // after the prefix, only a-z should be present
                if (atIndex != -1 && (email[i] < 'a' || email[i] > 'z'))
                    return true;
            }
            i++;
        }
        //'@' or '.' is not found or present at the start or end of email
        if (atIndex == -1 || dotIndex == -1 || atIndex == 0 || dotIndex == atIndex + 1 || dotIndex == email.length() - 1)
            return true;

        return false;
    }
    void encrypt(string &password)
    {
        for (int i = 0; i < password.length(); i++)
        {
            password[i] = password[i] + password.length();
        }
    }
    void addUser(User *user, string name, string username, string email, string password, string location)
    {
        user->set_name(name);
        user->set_username(username);
        user->set_email(email);
        user->set_password(password);
        user->set_location(location);
    }
    void signup()
    {
        cout << "Sign Up to Notepad\n";
        // set the users who were added previously
        readUsers();

        string name, username, password, location, email;
        cout << "Enter Name : ";
        cin >> name;
        cout << "Enter User Name : ";
        cin >> username;
        cout << "Enter Email : ";
        cin >> email;
        cout << "Enter Password : ";
        cin >> password;
        cout << "Enter Location : ";
        cin >> location;

        // username aldready exists
        if (isExistingUser(username) != -1)
        {
            cout << "User Name Aldready exists!!!\n";
            return;
        }

        // email validation
        if (isEmailInValid(email))
        {
            cout << "Enter valid email id!!!\n";
            return;
        }

        // encrypt password
        encrypt(password);

        // add a user to the users
        addUser(users.add_users(), name, username, email, password, location);

        // write updated users object to the file
        writeUsers();
    }
    int login()
    {
        string username, password;
        cout << "\nEnter Login Details\n";
        cout << "User Name : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;
        int index = isExistingUser(username);
        if (index == -1)
        {
            cout << "Invalid User Name!!!";
            return -1;
        }
        encrypt(password);
        const User &user = users.users(index);
        if(user.password() == password) return index;

        cout<<"Invalid Password!!!\n";
        return -1;
    }

    // meant for debugging
    void printUsers()
    {
        cout << "\nUSERS\n";
        for (int i = 0; i < users.users_size(); i++)
        {
            const User &user = users.users(i);
            cout << "Name : " << user.name() << " Email : " << user.email() << " Password : " << user.password() << endl;
        }
    }
};