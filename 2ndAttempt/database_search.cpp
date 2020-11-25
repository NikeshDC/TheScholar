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
    std::vector<std::string> authors;
    std::vector<std::string> genres;
    std::string date;
    std::vector<std::string> extrades;
    std::string path;

    void clearAll();
    void readFromFileForSearch();
    void readFromFileForDisplay();
};
    void BookDescriptor::clearAll()
    {
        bookPath = "";
        name = "";
        date = "";
        authors.clear();
        genres.clear();
        extrades.clear();
    }

    void BookDescriptor::readFromFileForSearch()
    {
        clearAll();
        std::string author;
        std::string genre;
        std::string extrade;
        std::ifstream inStream(path.c_str());
        getline(inStream, bookPath);
        getline(inStream, name);
        getline(inStream, author);
        Utility::String::breakString(author, authors, "$ ");
        getline(inStream, genre);
        Utility::String::breakString(genre, genres, "$ ");
        getline(inStream, date);
        getline(inStream, extrade);
        Utility::String::breakString(extrade, extrades, "$");
        inStream.close();
    }
    void BookDescriptor::readFromFileForDisplay()
    {
        clearAll();
        std::string author;
        std::string genre;
        std::string extrade;
        std::ifstream inStream(path.c_str());
        getline(inStream, bookPath);
        getline(inStream, name);
        getline(inStream, author);
        Utility::String::breakString(author, authors, "$");
        getline(inStream, genre);
        Utility::String::breakString(genre, genres, "$");
        getline(inStream, date);
        getline(inStream, extrade);
        Utility::String::breakString(extrade, extrades, "$");
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
                    for(int k=0; k<pribdlist[i].authors.size();k++ )
                    {
                        if(pribdlist[i].authors[k] == keyword)
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

void FullSearch(std::string keywords[], std::vector<BookDescriptor> &pribdlist)
{
    int i;
    std::string searchPath;
    std::string bookDesPath;
    std::ifstream reader;
    BookDescriptor bd;
    int resultCount = 0;
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
                    return;
                while(std::getline(reader,bookDesPath))
                {
                    bd.path = bookDesPath;
                    bd.readFromFileForSearch();
                    pribdlist.push_back(bd);
                }
                for(int m=i+1;m<SEARCH_KEYWORDS_SIZE;m++)
                    filterResult(pribdlist, m, keywords[m]);
                for(int k=0;k<authorWords.size();k++)
                    if(k!=i)
                        filterResult(pribdlist, AUTHOR, authorWords[k]);
                reader.close();
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
                    return;

                while(std::getline(reader,bookDesPath))
                {
                    bd.path = bookDesPath;
                    bd.readFromFileForSearch();
                    pribdlist.push_back(bd);
                }
                for(int m=i+1;m<SEARCH_KEYWORDS_SIZE;m++)
                    filterResult(pribdlist, m, keywords[m]);
                reader.close();

            }
            break;
        case DATE:
            {
                searchPath = SEARCH_DIRS::DATE + keywords[DATE];
                reader.open(searchPath);
                if(!reader.good())
                    return;

                while(std::getline(reader,bookDesPath))
                {
                    bd.path = bookDesPath;
                    bd.readFromFileForSearch();
                    pribdlist.push_back(bd);
                }
                for(int m=i+1;m<SEARCH_KEYWORDS_SIZE;m++)
                    filterResult(pribdlist, m, keywords[m]);
                reader.close();
            }
            break;
        case GENRE:
            {
                std::vector<std::string> genreWords;
                int i;
                Utility::String::breakString(keywords[GENRE], genreWords, std::string(" "));
                for(i=0; i<genreWords.size(); i++)
                {
                    searchPath = SEARCH_DIRS::GENRE + genreWords[i][0] + DIRECTORY_SEPERATOR + genreWords[i];
                    reader.open(searchPath);
                    if(reader.good())
                        break;
                }
                if(i == genreWords.size())
                    return;
                while(std::getline(reader,bookDesPath))
                {
                    bd.path = bookDesPath;
                    bd.readFromFileForSearch();
                    pribdlist.push_back(bd);
                }
                for(int m=i+1; m<SEARCH_KEYWORDS_SIZE; m++)
                    filterResult(pribdlist, m, keywords[m]);
                for(int j=0;j<genreWords.size();j++)
                    if(j!=i)
                        filterResult(pribdlist, GENRE, genreWords[j]);
                reader.close();

            }
            break;
        default:
            std::cout<<"\nEmpty keywords";
            break;
    }
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
    FullSearch(keywords, bdlist);
    for(int i=0;i<bdlist.size();i++)
    {
        bdlist[i].readFromFileForDisplay();
        std::cout<<"\n\nNAME: "<<bdlist[i].name;
        std::cout<<"\nAUTHORS: ";
        for(int j=0;j<bdlist[i].authors.size(); j++)
            std::cout<<"\t"<<bdlist[i].authors[j];
        std::cout<<"\nPUBLISHED DATE: "<<bdlist[i].date;
        std::cout<<"\nGENRES: ";
        for(int j=0;j<bdlist[i].genres.size(); j++)
            std::cout<<"\t"<<bdlist[i].genres[j];
        std::cout<<"\nDESCRIPTION: ";
        for(int j=0;j<bdlist[i].extrades.size(); j++)
            std::cout<<"\t"<<bdlist[i].extrades[j];
    }
}

