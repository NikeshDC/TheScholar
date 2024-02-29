#ifndef _DATABASE_SEARCH_
#define _DATABASE_SEARCH_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Utility.h"

namespace DATABASE_SEARCH
{
    enum search_keywords
    {
        AUTHOR,
        NAME,
        DATE,
        GENRE
    };
    const int SEARCH_KEYWORDS_SIZE = 4;
    const int MAX_RELEVANT_RESULT = 10;
    const int MAX_SEARCH_RESULT = 20;
    const char DIRECTORY_SEPERATOR = '/';
    const std::string PATH_FILE = "#.txt";

    std::string keywords[SEARCH_KEYWORDS_SIZE];
    std::vector<int> date_search_lines;

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

    class BookDescriptor
    {
    public:
        std::string bookPath;
        std::string name;
        std::vector<std::string> authors_search;
        std::vector<std::string> authors_display;
        std::vector<std::string> genres;
        std::string date;
        std::vector<std::string> extrades;
        std::string path;
        int noOfReveiws;
        float review;

        void clearAll();
        void readFromFile();
    };
    void BookDescriptor::clearAll()
    {
        bookPath = "";
        name = "";
        date = "";
        authors_search.clear();
        authors_display.clear();
        genres.clear();
        extrades.clear();
    }

    void BookDescriptor::readFromFile()
    {
        clearAll();
        std::string author;
        std::string genre;
        std::string extrade;
        std::ifstream inStream(path.c_str());
        if(!inStream.good())
        {
            std::cout<<"book doesn't exist at specified path";
            return;
        }
        getline(inStream, bookPath);
        getline(inStream, name);
        getline(inStream, author);
        Utility::String::breakString(author, authors_search, "$ ");
        Utility::String::breakString(author, authors_display, "$");
        getline(inStream, genre);
        Utility::String::breakString(genre, genres, "$");
        getline(inStream, date);
        getline(inStream, extrade);
        Utility::String::breakString(extrade, extrades, "$");
        inStream >> noOfReveiws;
        inStream >> review;
        inStream.close();
    }

    /****BOOKDESCRIPTOR LIST AFTER SEARCH****/
    std::vector<BookDescriptor> bdlist;

    void filterResult(std::vector<BookDescriptor> &pribdlist, int keyword_index, std::string keyword, int pribdlistStart = 0)
    {
        if (keyword.size() == 0)
            return;
        int eraseflag = 0;
        for (int i = pribdlistStart; i < pribdlist.size(); i++)
        {
            switch (keyword_index)
            {
            case AUTHOR:
            {
                eraseflag = 1;
                for (int k = 0; k < pribdlist[i].authors_search.size(); k++)
                {
                    if (Utility::String::getLowerCase(pribdlist[i].authors_search[k]) == keyword)
                    {
                        eraseflag = 0;
                        break;
                    }
                }
                if (eraseflag == 1)
                    pribdlist.erase(pribdlist.begin() + i);
            }
            break;
            case NAME:
            {
                if (Utility::String::getLowerCase(pribdlist[i].name) != keyword)
                    pribdlist.erase(pribdlist.begin() + i);
                //std::cout<<"\nDES_NAME: "<<pribdlist[i].name;
                //std::cout<<"\nKN: "<<keyword;
            }
            break;
            case DATE:
            {
                if (pribdlist[i].date != keyword)
                    pribdlist.erase(pribdlist.begin() + i);
            }
            break;
            case GENRE:
            {
                eraseflag = 1;
                for (int k = 0; k < pribdlist[i].genres.size(); k++)
                {
                    if (Utility::String::getLowerCase(pribdlist[i].genres[k]) == keyword)
                    {
                        eraseflag = 0;
                        break;
                    }
                }
                if (eraseflag == 1)
                    pribdlist.erase(pribdlist.begin() + i);
            }
            break;
            default:
                std::cout << "\nEmpty keyword";
                break;
            }
        }
    }

    //RETURNS TRUE IF MORE RESULT CAN BE FOUND
    bool FullSearch(std::string keywords[], std::vector<BookDescriptor> &pribdlist, int searchIndex_start = 0)
    {
        int i;
        std::string searchPath;
        std::string bookDesPath;
        std::ifstream reader;
        BookDescriptor bd;
        int resultCount = 0;
        bool fullResultRead = false;
         for (i = 0; i < SEARCH_KEYWORDS_SIZE; i++)
            keywords[i] =  Utility::String::getLowerCase(keywords[i]);
        for (i = 0; i < SEARCH_KEYWORDS_SIZE; i++)
            if (keywords[i].size() > 0)
                break;
        switch (i)
        {
        case AUTHOR:
        {
            std::vector<std::string> authorWords;
            int j;
            Utility::String::breakString(keywords[AUTHOR], authorWords, std::string(" "));
            for (j = 0; j < authorWords.size(); j++)
            {
                searchPath = SEARCH_DIRS::AUTHOR + authorWords[j][0] + DIRECTORY_SEPERATOR + authorWords[j];
                reader.open(searchPath);
                if (reader.good())
                    break;
            }
            if (j == authorWords.size())
                return false;
            while (std::getline(reader, bookDesPath))
            {
                bd.path = bookDesPath;
                bd.readFromFile();
                pribdlist.push_back(bd);
            }
            for (int m = i + 1; m < SEARCH_KEYWORDS_SIZE; m++)
                filterResult(pribdlist, m, keywords[m]);
        }
        break;
        case NAME:
        {
            std::vector<std::string> nameWords;
            Utility::String::breakString(keywords[NAME], nameWords, std::string(" "));
            searchPath = SEARCH_DIRS::NAME + keywords[NAME][0];
            for (int i = 0; i < nameWords.size(); i++)
                searchPath += DIRECTORY_SEPERATOR + nameWords[i];
            searchPath += DIRECTORY_SEPERATOR + PATH_FILE;
            reader.open(searchPath);
            if (!reader.good())
                return false;

            while (std::getline(reader, bookDesPath))
            {
                bd.path = bookDesPath;
                bd.readFromFile();
                pribdlist.push_back(bd);
            }
            for (int m = i + 1; m < SEARCH_KEYWORDS_SIZE; m++)
                filterResult(pribdlist, m, keywords[m]);
        }
        break;
        case DATE:
        {
            if(date_search_lines.size() == 0)
                date_search_lines.push_back(0);
            int pageIndex = searchIndex_start/MAX_SEARCH_RESULT;
            searchIndex_start = date_search_lines[pageIndex];

            searchPath = SEARCH_DIRS::DATE + keywords[DATE];
            reader.open(searchPath);
            if (!reader.good())
                return false;
            for (int b = 0; b < searchIndex_start; b++)
                std::getline(reader, bookDesPath);
            int prevResCount;
            int noOfLinesRead = 0;

            while (!fullResultRead && resultCount <= MAX_SEARCH_RESULT)
            {
                if (!std::getline(reader, bookDesPath))
                {
                    fullResultRead = true;
                    break;
                }
                else
                {
                    noOfLinesRead++;
                }
                bd.path = bookDesPath;
                bd.readFromFile();
                pribdlist.push_back(bd);
                prevResCount = pribdlist.size();
                filterResult(pribdlist, GENRE, keywords[GENRE], prevResCount - 1);
                if (prevResCount == pribdlist.size())
                    resultCount++;
            }
            if (resultCount == MAX_SEARCH_RESULT + 1)
                pribdlist.pop_back(); //extra element is kept at end just to be sure that more result can be found
            if(pageIndex == date_search_lines.size()-1)
            {
                date_search_lines.push_back(date_search_lines[pageIndex]+ noOfLinesRead-1);
            }
            else if(pageIndex > date_search_lines.size()-1)
            {
                std::cout<<"some error in page index";
            }
            return !fullResultRead;
        }
        break;
        case GENRE:
        {
            std::vector<std::string> genreWords;
            int j, prevResCount;
            Utility::String::breakString(keywords[GENRE], genreWords, std::string(" "));
            for (j = 0; j < genreWords.size(); j++)
            {
                searchPath = SEARCH_DIRS::GENRE + genreWords[j][0] + DIRECTORY_SEPERATOR + genreWords[j];
                reader.open(searchPath);
                if (reader.good())
                    break;
            }
            if (j == genreWords.size())
                return false;
            while (!fullResultRead && resultCount <= MAX_SEARCH_RESULT)
            {
                if (!std::getline(reader, bookDesPath))
                {
                    fullResultRead = true;
                    break;
                }
                bd.path = bookDesPath;
                bd.readFromFile();
                pribdlist.push_back(bd);
                prevResCount = pribdlist.size();
                if (prevResCount == pribdlist.size())
                    resultCount++;
            }
            if (resultCount == MAX_SEARCH_RESULT + 1)
                pribdlist.pop_back(); //extra element is kept at end just to be sure that more result can be found
            return !fullResultRead;
        }
        break;
        default:
            std::cout << "\nEmpty keywords";
            break;
        }
        reader.close();
        return false;
    }
} // namespace DATABASE_SEARCH
#endif // _DATABASE_SEARCH_
