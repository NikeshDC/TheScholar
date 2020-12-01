#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <unistd.h>
#include<dirent.h>
#include "Utility.h"
#include "sort.h"

const char DIRECTORY_SEPERATOR = '/';
const int MAX_AUTHOR_NAME = 15;
const int FILE_NOT_SORTED = 0;
const int FILE_SORTED = 1;
const char AUTHOR_HEADER_BLANK_CHAR = ' ';
const std::string BOOKDES_EXT = ".des";
const std::string PATH_FILE = "#.txt";
const std::string FILE_AUTHOR_HEADER = "#header.txt";
const std::string FILE_AUTHOR_STATUS = "#status.txt";

namespace REQ_DIRS
{
    std::string DATA;
    std::string DATA_BOOK;
    std::string SEARCH;
    std::string SEARCH_BOOK;
    std::string SEARCH_BOOK_NAME;
    std::string SEARCH_BOOK_AUTHOR;
    std::string SEARCH_BOOK_GENRE;
    std::string SEARCH_BOOK_DATE;
    std::string FILE_BOOKCOUNT;

    void setDirsForBook()
    {
        DATA = "./data/";
        DATA_BOOK = DATA + "book/"; //"./data/book/";
        SEARCH = "./search/";
        SEARCH_BOOK = SEARCH + "book/";//"./search/book/";
        SEARCH_BOOK_NAME = SEARCH_BOOK + "name/";  //"./search/book/name/";
        SEARCH_BOOK_AUTHOR = SEARCH_BOOK + "author/"; //"./search/book/author/";
        SEARCH_BOOK_GENRE = SEARCH_BOOK + "genre/"; //"./search/book/genre/";
        SEARCH_BOOK_DATE = SEARCH_BOOK + "date/"; //"./search/book/date/";
        FILE_BOOKCOUNT = DATA_BOOK + "#bookcount.txt";
    }
    void setDirsForArticle()
    {
        DATA = "./data/";
        DATA_BOOK = DATA + "article/"; //"./data/article/";
        SEARCH = "./search/";
        SEARCH_BOOK = SEARCH + "article/";//"./search/article/";
        SEARCH_BOOK_NAME = SEARCH_BOOK + "name/"; //"./search/article/name/";
        SEARCH_BOOK_AUTHOR = SEARCH_BOOK + "author/"; //"./search/article/author/";
        SEARCH_BOOK_GENRE = SEARCH_BOOK + "genre/"; //"./search/article/genre/";
        SEARCH_BOOK_DATE = SEARCH_BOOK + "date/"; //"./search/article/date/";
        FILE_BOOKCOUNT = DATA_BOOK + "#bookcount.txt";
    }
    void create()
    {
        mkdir(DATA.c_str());
        mkdir(DATA_BOOK.c_str());
        mkdir(SEARCH.c_str());
        mkdir(SEARCH_BOOK.c_str());
        mkdir(SEARCH_BOOK_NAME.c_str());
        mkdir(SEARCH_BOOK_AUTHOR.c_str());
        mkdir(SEARCH_BOOK_GENRE.c_str());
        mkdir(SEARCH_BOOK_DATE.c_str());
        if(!Utility::FileHandler::exists(FILE_BOOKCOUNT))
        {
            std::ofstream outStream;
            outStream.open(FILE_BOOKCOUNT.c_str());
            outStream<<0;
        }
    }
};

class BookDescriptor
{
public:
    static const char SAME_FIELD_DELIM = '$';
    std::string bookPath;
    std::string name;
    std::string author;
    std::string genre;
    std::string date;
    std::string extrades;
    std::string path;

    void createDescriptorFile();
    void createAllDirectories();
private:
    void createDir_Name();
    void createDir_author();
    void createDir_date();
    void createDir_genre();
};
    void BookDescriptor::createDescriptorFile()
    {
        //if(descriptorFileAlreadyExists()) return;
        std::ifstream inStream(REQ_DIRS::FILE_BOOKCOUNT.c_str());
        int bc;
        inStream>>bc;
        inStream.close();
        bc++;
        path = REQ_DIRS::DATA_BOOK + std::to_string(bc) + BOOKDES_EXT;
        std::ofstream outStream(REQ_DIRS::FILE_BOOKCOUNT.c_str());
        outStream<<bc;
        outStream.close();

        outStream.open(path.c_str());
        outStream<<bookPath<<"\n";
        outStream<<name<<"\n";
        outStream<<author<<"\n";
        outStream<<genre<<"\n";
        outStream<<date<<"\n";
        outStream<<extrades<<"\n";
        outStream<<0<<'\n';
        outStream<<0;

        outStream.close();
    }

    void BookDescriptor::createDir_Name()
    {
        std::vector<std::string> bookWords;
        Utility::String::breakString(name,bookWords,std::string(" :"));
        std::string curBookPath = REQ_DIRS::SEARCH_BOOK_NAME + name[0];
        mkdir(curBookPath.c_str());
        for(int i=0;i<bookWords.size();i++)
        {
            curBookPath += DIRECTORY_SEPERATOR + bookWords[i];
            mkdir(curBookPath.c_str());
        }
        curBookPath += DIRECTORY_SEPERATOR + PATH_FILE;
        std::ofstream outstream;
        outstream.open(curBookPath.c_str(),std::ios_base::app);
        outstream<<path<<"\n";
        outstream.close();
    }
    void BookDescriptor::createDir_author()
    {
        std::vector<std::string> authors;
        Utility::String::breakString(author,authors,std::string(" $"));
        std::string baseBookPath = REQ_DIRS::SEARCH_BOOK_AUTHOR;
        std::string curBookPath;
        std::string headerPath;
        std::string statusPath;
        std::fstream outstream;
        int status = FILE_NOT_SORTED;
        for(int i=0;i<authors.size();i++)
        {
            baseBookPath.push_back(authors[i][0]);
            mkdir(baseBookPath.c_str());
            curBookPath = baseBookPath + DIRECTORY_SEPERATOR + authors[i];

            headerPath = baseBookPath + DIRECTORY_SEPERATOR + FILE_AUTHOR_HEADER;
            statusPath = baseBookPath + DIRECTORY_SEPERATOR + FILE_AUTHOR_STATUS;
            //GETTING STATUS FROM STATUS FILE/CREATING IF NOT EXIST
            if(!Utility::FileHandler::exists(statusPath))
            {
                outstream.open(statusPath.c_str(),std::ios_base::out);
                outstream<<FILE_NOT_SORTED;
                outstream.close();
            }
            else
            {
                outstream.open(statusPath.c_str(),std::ios_base::in);
                outstream>>status;
                outstream.close();
            }
            //WRITING AUTHOR NAME TO HEADER FILE
            if(!Utility::FileHandler::exists(curBookPath))
            {
                if(status == FILE_NOT_SORTED)
                {
                    outstream.open(headerPath.c_str(),std::ios_base::app);
                    for(int j=0;j<MAX_AUTHOR_NAME;j++)
                    {
                        if(j<authors[i].size())
                            outstream<<authors[i][j];
                        else
                            outstream<<AUTHOR_HEADER_BLANK_CHAR;
                    }
                }
                else
                {
                    outstream.open(headerPath.c_str());
                    outstream.seekg(0, std::ios::end);
                    int noOfEls = outstream.tellg() / MAX_AUTHOR_NAME;
                    outstream.seekg(0, std::ios::beg);
                    insertInSortedFile(outstream, authors[i], noOfEls, MAX_AUTHOR_NAME);
                }
                outstream.close();
            }

            outstream.open(curBookPath.c_str(),std::ios_base::app);
            outstream<<path<<"\n";
            outstream.close();

            baseBookPath.pop_back();
        }
    }
    void BookDescriptor::createDir_date()
    {
        std::string bookPath;
        bookPath = REQ_DIRS::SEARCH_BOOK_DATE + date;
        std::ofstream outstream;
        outstream.open(bookPath.c_str(),std::ios_base::app);
        outstream<<path<<"\n";
        outstream.close();
    }
    void BookDescriptor::createDir_genre()
    {
        std::vector<std::string> genres;
        Utility::String::breakString(genre,genres,std::string(" $"));
        std::string baseBookPath = REQ_DIRS::SEARCH_BOOK_GENRE;
        std::string curBookPath;
        std::ofstream outstream;
        for(int i=0;i<genres.size();i++)
        {
            baseBookPath.push_back(genres[i][0]);

            mkdir(baseBookPath.c_str());
            curBookPath = baseBookPath + DIRECTORY_SEPERATOR + genres[i];
            outstream.open(curBookPath.c_str(),std::ios_base::app);
            outstream<<path<<"\n";
            outstream.close();

            baseBookPath.pop_back();
        }
    }
    void BookDescriptor::createAllDirectories()
    {
        createDir_Name();
        createDir_author();
        createDir_genre();
        createDir_date();
    }

int main()
{
    REQ_DIRS::setDirsForBook();
    REQ_DIRS::create();

    BookDescriptor bd;
    std::string dbookname;

    std::cout<<"\nSEPERATE MULTIPLE AUTHORS,GENRES,DESCRIPTIONS BY $\n";
    std::cout<<"\nBook name: ";
    std::getline(std::cin,bd.name);
    std::cout<<"\nAuthor: ";
    std::getline(std::cin,bd.author);
    std::cout<<"\nGenre: ";
    std::getline(std::cin,bd.genre);
    std::cout<<"\nPublished date: ";
    std::getline(std::cin,bd.date);
    std::cout<<"\nExtra description: ";
    std::getline(std::cin,bd.extrades);
    std::cout<<"\nBook Name in Database(with extension): ";
    std::getline(std::cin,dbookname);
    bd.bookPath = REQ_DIRS::DATA_BOOK + dbookname;

    bd.createDescriptorFile();
    bd.createAllDirectories();
}
