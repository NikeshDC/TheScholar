#include "signUp.h"

class logIn
{
private:
    std::string username, un;
    std::string password, pw;

public:
    logIn()
    { //default constructor
        username = "";
        password = "";
    }

    logIn(std::string usernamed, std::string passwordd) : username(usernamed), password(passwordd) {} //parametric constructor

    bool IsLogedIn()
    {
        std::string path = std::string(".\\\\") + std::string("Users\\\\") + std::string(username) + std::string("\\\\password.txt");
        try
        {
            ifstream read((path).c_str());
            //read from file
            getline(read, un);
            getline(read, pw);
        }
        catch (...)
        {
            cout << endl
                 << "File could not be found" << endl;
        }
        if (username != "" && password != "")
        {
            if ((un == username) && (pw == password))
            {
                //check if user name and password match
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }
};
