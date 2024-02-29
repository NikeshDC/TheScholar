#ifndef _RELAVANT_SEARCH_
#define _RELAVANT_SEARCH_

namespace RELEVANT_OPTIONS
{
    const int MAX_AUTHOR_NAME = 15;
    const int MAX_RELEVANT_RESULT = 10;
    const char DIRECTORY_SEPERATOR = '/';
    const std::string PATH_FILE = "#.txt";
    const std::string FILE_AUTHOR_HEADER = "#header.txt";
    std::vector<std::string> results;
    int result_size = 0;

    namespace SEARCH_DIRS
    {
        std::string NAME;
        std::string AUTHOR;
        std::string GENRE;
        std::string DATE;

        void setDirsForBook()
        {
            NAME = "./search/book/name/";
            AUTHOR = "./search/book/author/";
            GENRE = "./search/book/genre/";
            DATE = "./search/book/date/";
        }
        void setDirsForArticle()
        {
            NAME = "./search/article/name/";
            AUTHOR = "./search/article/author/";
            GENRE = "./search/article/genre/";
            DATE = "./search/article/date/";
        }
    } // namespace SEARCH_DIRS

    void getMaxBookNames(const std::string dirPath, std::vector<std::string> &books, std::string name, int &result_size)
    {
        DIR *dir;
        struct dirent *ent;
        dir = opendir(dirPath.c_str());
        if (!dir)
        {
            std::cout<<"\ndir doesnt exist!!!"<<dirPath;
            return;
        }
            readdir(dir); //reading .
        readdir(dir);     //reading ..
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name == PATH_FILE)
            {
                if (result_size == MAX_RELEVANT_RESULT)
                {
                    closedir(dir);
                    return;
                }
                result_size++;
                books.push_back(name); //this has an extra blank space as last character
            }
            else
                getMaxBookNames(dirPath + DIRECTORY_SEPERATOR + ent->d_name, books, name + ent->d_name + " ", result_size);
        }
        closedir(dir);
    }

    void getRelevantBookNames(std::string keyword, std::vector<std::string> &books, int &result_size)
    {
        if (keyword.size() == 0)
        {
            //std::cout<<"\nNull keyword";
            return;
        }
        keyword = Utility::String::getLowerCase(keyword);
        std::string path;
        std::vector<std::string> names;
        std::string baseName = "";
        DIR *dir;
        struct dirent *ent;
        path = SEARCH_DIRS::NAME + keyword[0];
        Utility::String::breakString(keyword, names, " ");
        for (int i = 0; i < names.size() - 1; i++)
        {
            path += DIRECTORY_SEPERATOR + names[i];
            baseName += names[i] + " "; //contains extra blank space at last
        }
        dir = opendir(path.c_str());
        if (!dir)
        {
            //std::cout<<"\nNo result";
            return;
        }
        readdir(dir); //reading .
        readdir(dir); //reading ..
        while (((ent = readdir(dir)) != NULL) && result_size < MAX_RELEVANT_RESULT)
        {
            if (Utility::String::compStringWithLength(Utility::String::getLowerCase(ent->d_name), names.back()) == 0)
                getMaxBookNames(path + DIRECTORY_SEPERATOR + ent->d_name, books, std::string(ent->d_name) + " ", result_size);
        }
        closedir(dir);
        for (int i = 0; i < books.size(); i++)
        {
            books[i].pop_back(); //removing extra space at the end
            books[i] = baseName + books[i];
        }
    }

    void getRelevantBookGenres(std::string keyword, std::vector<std::string> &genres, int &result_size)
    {
        if (keyword.size() == 0)
        {
            //std::cout<<"\nNull keyword";
            return;
        }
        keyword = Utility::String::getLowerCase(keyword);
        std::string path;
        DIR *dir;
        struct dirent *ent;
        path = SEARCH_DIRS::GENRE + keyword[0];
        dir = opendir(path.c_str());
        if (!dir)
        {
            //std::cout<<"\nNo result";
            return;
        }
        readdir(dir); //reading .
        readdir(dir); //reading ..
        while (((ent = readdir(dir)) != NULL) && result_size < MAX_RELEVANT_RESULT)
        {
            if (Utility::String::compStringWithLength(Utility::String::getLowerCase(ent->d_name), keyword) == 0)
                genres.push_back(ent->d_name);
            result_size++;
        }
        closedir(dir);
    }

    void getString(std::ifstream &pf, std::string &str, const int MAX_STRSIZE, const char delim = ' ')
    {
        char r;
        str = "";
        for (int i = 0; i < MAX_STRSIZE; i++)
        {
            r = pf.get();
            if (r == delim)
                break;
            str.push_back(r);
        }
    }
    void getRelevantBookAuthors(std::string keyword, std::vector<std::string> &authors, int &result_size)
    {
        if (keyword.size() == 0)
        {
            //std::cout<<"\nNull keyword";
            return;
        }
        keyword = Utility::String::getLowerCase(keyword);
        std::string headerFilepath = SEARCH_DIRS::AUTHOR + keyword[0] + DIRECTORY_SEPERATOR + FILE_AUTHOR_HEADER;
        std::ifstream headerFile(headerFilepath.c_str());
        if (!headerFile.good())
        {
            //std::cout<<"\nNo result";
            return;
        }
        //binary search
        {
            std::string readAuthor;
            headerFile.seekg(0, std::ios::end);
            int noOfEls = headerFile.tellg() / MAX_AUTHOR_NAME;
            int low = 0;
            int high = noOfEls - 1;
            int mid;
            while (low <= high)
            {
                mid = (low + high) / 2;
                headerFile.seekg(mid * MAX_AUTHOR_NAME, std::ios::beg);
                getString(headerFile, readAuthor, MAX_AUTHOR_NAME);
                if (Utility::String::compStringWithLength(keyword, readAuthor) == 0)
                {
                    authors.push_back(readAuthor);
                    result_size++;
                    for (int i = mid - 1; i >= 0 && result_size < MAX_RELEVANT_RESULT; i--)
                    {
                        headerFile.seekg(i * MAX_AUTHOR_NAME, std::ios::beg);
                        getString(headerFile, readAuthor, MAX_AUTHOR_NAME);
                        if (Utility::String::compStringWithLength(keyword, Utility::String::getLowerCase(readAuthor)) != 0)
                            break;
                        authors.push_back(readAuthor);
                        result_size++;
                    }
                    for (int i = mid + 1; i < noOfEls && result_size < MAX_RELEVANT_RESULT; i++)
                    {
                        headerFile.seekg(i * MAX_AUTHOR_NAME, std::ios::beg);
                        getString(headerFile, readAuthor, MAX_AUTHOR_NAME);
                        if (Utility::String::compStringWithLength(keyword, Utility::String::getLowerCase(readAuthor)) != 0)
                            break;
                        authors.push_back(readAuthor);
                        result_size++;
                    }
                    return;
                }
                else if (keyword < readAuthor)
                    high = mid - 1;
                else
                    low = mid + 1;
            }
        }
    }

} // namespace RELEVANT_OPTIONS

#endif
