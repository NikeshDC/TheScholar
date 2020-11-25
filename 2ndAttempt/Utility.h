#include<dirent.h>
namespace Utility
{
    namespace String
    {
        void breakString(std::string &str,std::vector<std::string> &ptrs,std::string delims = " ")
        {
            int prevStrIndex = 0;
            for(int i=0;i<str.size();i++)
            {
                for(int j=0;j<delims.size();j++)
                {
                    if(str.at(i) == delims.at(j))
                    {
                        if(prevStrIndex != i)
                            ptrs.push_back(str.substr(prevStrIndex,i-prevStrIndex));
                        prevStrIndex = i+1;
                    }
                }
                if((i == str.size()-1)&& prevStrIndex != i+1)
                    ptrs.push_back(str.substr(prevStrIndex));
            }
        }
        int compStringWithLength(const std::string &str1, const std::string &str2)
        {
            int n = str1.size() >= str2.size() ? str2.size() : str1.size();
            for(int i=0;i<n;i++)
            {
                if(str1[i] > str2[i])
                    return 1;
                else if(str1[i] < str2[i])
                    return -1;
            }
            return 0;
        }
    }

    namespace FileHandler
    {
        inline bool exists(const std::string& filepath)
        {
            std::ifstream inStream(filepath.c_str());
            return inStream.good();
        }
        inline void openFileExternal(const std::string& filepath)
        {
            std::string command = std::string("start ") + filepath;
            system(command.c_str());
        }
    }

    namespace DirectoryHandler
    {
        inline bool exists(const std::string& dirpath)
        {
            DIR* dir = opendir(dirpath.c_str());
            if (dir){
                closedir(dir);
                return true;
            }
              else
                return false;
        }
        void setFilenames(const std::string& dirpath, std::vector<std::string> &names)
        {
            DIR *dir;
            struct dirent *ent;
            dir = opendir(dirpath.c_str());
            if(!dir)
                return;

            readdir(dir); //reading .
            readdir(dir); //reading ..
            while((ent = readdir(dir))!= NULL)
                names.push_back(ent->d_name);

            closedir(dir);
        }
    }
}
