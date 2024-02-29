#include "DirectoryHandler.h"

class signUp
{

private:
    std::string username;
    std::string password;

public:
    signUp()
    { //default constructor
        username = "";
        password = "";
    }

    signUp(std::string username, std::string password) : username(std::move(username)), password(std::move(password)) {} //parametric constructor

    bool valid()
    {
        int spc = 0, nc = 0, ac = 0;
        for (int i = 0; i < password.length(); i++)
        {
            if ((password[i] <= 47 && password[i] >= 33) || (password[i] <= 64 && password[i] >= 58))
            {
                spc++; //special characters
            }
            if (password[i] <= 57 && password[i] >= 48)
            {
                nc++; //numbers
            }
            if ((password[i] <= 90 && password[i] >= 65) || (password[i] <= 122 && password[i] >= 97))
            {
                ac++; //characters A-Z and a-z
            }
        }
        if (spc >= 1 && nc >= 1 && ac >= 1 && password.length() >= 8)
        {
            return true; //validates the password for certain criteria
        }
        return false;
    }

    void signup()
    {
        if (username != "" && password != "")
        {
            string dirPath = createDirectory();
            if (dirPath == "USER_EXISTS")
            {
                return;
            }
            ofstream file; //create a file

            /***** password ******/
            string path = dirPath + string("\\\\password.txt");
            file.open(path.c_str()); //file name is username.txt
            file << username << endl
                 << password; //file holds username is first line and password in the other
            file.close();

            /******* reading books *********/
            path = dirPath + string("\\\\reading.txt");
            file.open(path.c_str());
            file.close();

            /******* completed books *********/
            path = dirPath + string("\\\\completed.txt");
            file.open(path.c_str());
            file.close();

            /******* shared books *********/
            path = dirPath + string("\\\\share.txt");
            file.open(path.c_str());
            file.close();

            /******* favourite books *********/
            path = dirPath + string("\\\\favourite.txt");
            file.open(path.c_str());
            file.close();
        }
    }

    string createDirectory()
    {
        DirectoryHandler d1;
        std::string dirpath = std::string(".\\\\") + std::string("Users\\\\") + username;
        d1.setDirName(dirpath.data());

        if (d1.exists())
        {
            std::cout << "Directory already exists";
            return ("USER_EXISTS");
        }
        else
        {
            d1.createDir();
            d1.hidedir();
        }

        return dirpath;
    }

    bool userExists()
    {
        DirectoryHandler checkUserDir;
        std::string checkDirPath = std::string(".\\\\") + std::string("Users\\\\") + username;
        checkUserDir.setDirName(checkDirPath.data());
        if (checkUserDir.exists())
        {
            return true;
        }
        /*checkuserDhl.setDirName("./");
        checkuserDhl.setDirForUse();
        checkuserDhl.displayfile();
        for(int i=0;i<checkuserDhl.dirDi.getsize();i++){
            if(checkuserDhl.dirDi.getinfo(i) == username)
                return true;
        }*/
        return false;
    }
};
