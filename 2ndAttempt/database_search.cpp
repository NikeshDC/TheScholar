#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include "Utility.h"

enum search_keywords{AUTHOR, NAME, DATE, GENRE};
const int SEARCH_KEYWORDS_SIZE = 4;
const int MAX_RELEVANT_RESULT = 10;
const int MAX_SEARCH_RESULT = 20;
const char DIRECTORY_SEPERATOR = '/';
const std::string PATH_FILE = "#.txt";

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
}

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
        getline(inStream, bookPath);
        getline(inStream, name);
        getline(inStream, author);
        Utility::String::breakString(author, authors_search, "$ ");
        Utility::String::breakString(author, authors_display, "$");
        getline(inStream, genre);
        Utility::String::breakString(genre, genres, "$ ");
        getline(inStream, date);
        getline(inStream, extrade);
        Utility::String::breakString(extrade, extrades, "$");
        inStream>>noOfReveiws;
        inStream>>review;
        inStream.close();
    }

void filterResult(std::vector<BookDescriptor> &pribdlist,int keyword_index, std::string keyword , int pribdlistStart = 0)
{
    if(keyword.size() == 0)
        return;
    int eraseflag = 0;
    for(int i=pribdlistStart; i<pribdlist.size(); i++)
    {
        switch(keyword_index)
        {
            case AUTHOR:
                {
                    eraseflag = 1;
                    for(int k=0; k<pribdlist[i].authors_search.size();k++ )
                    {
                        if(pribdlist[i].authors_search[k] == keyword)
                        {
                            eraseflag = 0;
                            break;
                        }
                    }
                    if(eraseflag == 1)
                        pribdlist.erase(pribdlist.begin()+i);
                }
                break;
            case NAME:
                {
                        if(pribdlist[i].name != keyword)
                            pribdlist.erase(pribdlist.begin()+i);
                }
                break;
            case DATE:
                {
                    if(pribdlist[i].date != keyword)
                        pribdlist.erase(pribdlist.begin()+i);
                }
                break;
            case GENRE:
                {
                    eraseflag = 1;
                    for(int k=0; k<pribdlist[i].genres.size();k++)
                    {
                        if(pribdlist[i].genres[k] == keyword)
                        {
                            eraseflag = 0;
                            break;
                        }
                    }
                    if(eraseflag == 1)
                        pribdlist.erase(pribdlist.begin()+i);
                }
                break;
            default:
                std::cout<<"\nEmpty keyword";
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
    for(i=0; i<SEARCH_KEYWORDS_SIZE; i++)
        if(keywords[i].size() > 0)
            break;
    switch(i)
    {
        case AUTHOR:
            {
                std::vector<std::string> authorWords;
                int j;
                Utility::String::breakString(keywords[AUTHOR], authorWords, std::string(" "));
                for(j=0; j<authorWords.size(); j++)
                {
                    searchPath = SEARCH_DIRS::AUTHOR + authorWords[j][0] + DIRECTORY_SEPERATOR + authorWords[j] ;
                    reader.open(searchPath);
                    if(reader.good())
                        break;
                }
                if(j == authorWords.size())
                    return false;
                while(std::getline(reader,bookDesPath))
                {
                    bd.path = bookDesPath;
                    bd.readFromFile();
                    pribdlist.push_back(bd);
                }
                for(int m=i+1;m<SEARCH_KEYWORDS_SIZE;m++)
                    filterResult(pribdlist, m, keywords[m]);
            }
            break;
        case NAME:
            {
                std::vector<std::string> nameWords;
                Utility::String::breakString(keywords[NAME],nameWords,std::string(" "));
                searchPath = SEARCH_DIRS::NAME + keywords[NAME][0];
                for(int i=0;i<nameWords.size();i++)
                    searchPath+= DIRECTORY_SEPERATOR + nameWords[i];
                searchPath += DIRECTORY_SEPERATOR + PATH_FILE;
                reader.open(searchPath);
                if(!reader.good())
                    return false;

                while(std::getline(reader,bookDesPath))
                {
                    bd.path = bookDesPath;
                    bd.readFromFile();
                    pribdlist.push_back(bd);
                }
                for(int m=i+1;m<SEARCH_KEYWORDS_SIZE;m++)
                    filterResult(pribdlist, m, keywords[m]);
            }
            break;
        case DATE:
            {
                searchPath = SEARCH_DIRS::DATE + keywords[DATE];
                reader.open(searchPath);
                if(!reader.good())
                    return false;
                for(int b=0; b<searchIndex_start; b++)
                    std::getline(reader,bookDesPath);
                int prevResCount;

                    while(!fullResultRead && resultCount<= MAX_SEARCH_RESULT)
                    {
                        if(!std::getline(reader,bookDesPath))
                        {
                            fullResultRead = true;
                            break;
                        }
                        bd.path = bookDesPath;
                        bd.readFromFile();
                        pribdlist.push_back(bd);
                        prevResCount = pribdlist.size();
                        filterResult(pribdlist, GENRE, keywords[GENRE],prevResCount-1);
                        if(prevResCount == pribdlist.size())
                            resultCount++;
                    }
                    if(resultCount == MAX_SEARCH_RESULT + 1)
                        pribdlist.pop_back(); //extra element is kept at end just to be sure that more result can be found
                    return !fullResultRead;
            }
            break;
        case GENRE:
            {
                std::vector<std::string> genreWords;
                int j, prevResCount;
                Utility::String::breakString(keywords[GENRE], genreWords, std::string(" "));
                for(j=0; j<genreWords.size(); j++)
                {
                    searchPath = SEARCH_DIRS::GENRE + genreWords[j][0] + DIRECTORY_SEPERATOR + genreWords[j];
                    reader.open(searchPath);
                    if(reader.good())
                        break;
                }
                if(j == genreWords.size())
                    return false;
                while(!fullResultRead && resultCount<= MAX_SEARCH_RESULT)
                    {
                        if(!std::getline(reader,bookDesPath))
                        {
                            fullResultRead = true;
                            break;
                        }
                        bd.path = bookDesPath;
                        bd.readFromFile();
                        pribdlist.push_back(bd);
                        prevResCount = pribdlist.size();
                        if(prevResCount == pribdlist.size())
                            resultCount++;
                    }
                    if(resultCount == MAX_SEARCH_RESULT + 1)
                        pribdlist.pop_back(); //extra element is kept at end just to be sure that more result can be found
                    return !fullResultRead;
            }
            break;
        default:
            std::cout<<"\nEmpty keywords";
            break;
    }
    reader.close();
    return false;
}

int main()
{
    SEARCH_DIRS::setDirsForBook();
    std::string keywords[SEARCH_KEYWORDS_SIZE];
    std::vector<BookDescriptor> bdlist;
    std::cout<<"\nNAME: ";
    std::getline(std::cin, keywords[NAME]);
    std::cout<<"\nAUTHOR: ";
    std::getline(std::cin, keywords[AUTHOR]);
    std::cout<<"\nDATE: ";
    std::getline(std::cin, keywords[DATE]);
    std::cout<<"\nGENRE: ";
    std::getline(std::cin, keywords[GENRE]);

    for(int i=0;i<4;i++)
        if(keywords[i] == "$") //$ is regarded as empty keyword
            keywords[i] = "";
    std::cout<<"MORE RESULT CAN BE FOUND: "<<std::boolalpha<<FullSearch(keywords, bdlist);
    for(int i=0;i<bdlist.size();i++)
    {
        std::cout<<"\n\nNAME: "<<bdlist[i].name;
        std::cout<<"\nAUTHORS: ";
        for(int j=0;j<bdlist[i].authors_display.size(); j++)
            std::cout<<"\t"<<bdlist[i].authors_display[j];
        std::cout<<"\nPUBLISHED DATE: "<<bdlist[i].date;
        std::cout<<"\nGENRES: ";
        for(int j=0;j<bdlist[i].genres.size(); j++)
            std::cout<<"\t"<<bdlist[i].genres[j];
        std::cout<<"\nDESCRIPTION: ";
        for(int j=0;j<bdlist[i].extrades.size(); j++)
            std::cout<<"\t"<<bdlist[i].extrades[j];
        std::cout<<"\nNO OF REVIEWS: "<<bdlist[i].noOfReveiws;
        std::cout<<"\nRATING: "<<bdlist[i].review;
    }
}
