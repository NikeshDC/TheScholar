#ifndef FILE_HANDLER
#define FILE_HANDLER

#include "logIn.h"
#include<stdio.h>
/******
 Read .txt file,choice are:
    1.Reading
    2.Completed
    3.Favourite
    4.Share
******/

/********** FILE READER CLASS **********/
class FileReader
{
private:
    int i = 1;
    std::string username, path, myText, pages;
    std::vector<std::string> books;
public:
    FileReader()
    {
        username = "";
    }

    FileReader(std::string username) : username(std::move(username)) {}

    std::vector<std::string> Reader(const int choice);
    std::string ReaderPage(const int choice,string book);
};

std::vector<std::string> FileReader::Reader(const int choice){
    if (username != "")
    {
        ifstream fileReader;
        path = std::string(".\\\\") + std::string("Users\\\\") + username;
        books.clear();
        if (choice == 1)
        {
            path = path + string("\\\\reading.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                //getline(fileReader,pages);
                books.push_back(myText);
                i++;
            }
            fileReader.close();
        }
        else if (choice == 2)
        {
            path = path + string("\\\\completed.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                //getline(fileReader,pages);
                books.push_back(myText);
                i++;
            }
            fileReader.close();
        }
        else if (choice == 3)
        {
            path = path + string("\\\\favourite.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                books.push_back(myText);
                i++;
            }
            fileReader.close();
        }
        else if (choice == 4)
        {
            path = path + string("\\\\share.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                //getline(fileReader,pages);
                books.push_back(myText);
                i++;
            }
            fileReader.close();
        }
        else
        {
            cout << "Invalid choice,unable to read";
        }
    }
    return books;
}

std::string FileReader::ReaderPage(const int choice,string book){
    ifstream fileReader;
        path = std::string(".\\\\") + std::string("Users\\\\") + username;
        if (choice == 1)
        {
            path = path + string("\\\\reading.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                getline(fileReader,pages);
                if(myText == book){
                    fileReader.close();
                    if(pages == "$")
                        pages ="";
                    return pages;
                }
            }
            fileReader.close();
            return "";
        }
        return "";
}

/***********  FILE WRITER CLASS ************/
class FileWriter
{
private:
    std::string username;

public:
    FileWriter(){
        username = "";
    }

    FileWriter(std::string username) : username(std::move(username)) {}
    void Writer(const int choice, std::string toWrite, std::string bookmarkPage= "$");
    void maskBookName(int position, char choice);
    bool UserExists();
    void updateBookmark(int position,char choice,std::string bookName,std::string newBookmark);
};

void FileWriter::Writer(const int choice, std::string toWrite, std::string bookmarkPage)
{
    if (username != "")
    {
        ofstream fileWrite;
        string path = std::string(".\\\\") + std::string("Users\\\\") + username;
        if(bookmarkPage=="")
            bookmarkPage="$";

        if (choice == 1)
        {
            path = path + string("\\\\reading.txt");
            fileWrite.open(path.c_str(), ios::app);
            fileWrite << toWrite << endl;
            fileWrite << bookmarkPage <<endl;
            fileWrite.close();
        }
        else if (choice == 2)
        {
            path = path + string("\\\\completed.txt");
            fileWrite.open(path.c_str(), ios::app);
            fileWrite << toWrite << endl;
            fileWrite << bookmarkPage <<endl;
            fileWrite.close();
        }
        else if (choice == 3)
        {
            path = path + string("\\\\favourite.txt");
            fileWrite.open(path.c_str(), ios::app);
            fileWrite << toWrite << endl;
            fileWrite.close();
        }
        else if (choice == 4)
        {
            path = path + string("\\\\share.txt");
            fileWrite.open(path.c_str(), ios::app);
            fileWrite << toWrite << endl;
            fileWrite << bookmarkPage <<endl;
            fileWrite.close();
        }
        else
        {
            cout << "Invalid choice,unable to write";
        }
    }
}

bool FileWriter::UserExists()
{
    DirectoryHandler checkUserDir;
    std::string checkDirPath = std::string(".\\\\") + std::string("Users\\\\") + username;
    checkUserDir.setDirName(checkDirPath.data());
    if (checkUserDir.exists()){
        return true;
    }
    return false;
}

void FileWriter::maskBookName(int position, char choice){
        ofstream fileWrite;
        ifstream fileReader;
        std::string path = std::string(".\\\\") + std::string("Users\\\\") + username;
        std::string pathTemp = path;
        std::string toWrite,skipper;
        int i = 0;
        if (choice == 'R')
        {
            path = path + string("\\\\reading.txt");
            fileReader.open(path.c_str());
            pathTemp = pathTemp +string("\\\\tempR.txt");
            fileWrite.open(pathTemp.c_str());
            i=1;
            position = 2*position +1;
            while(getline(fileReader,toWrite)){
                if(i != position){
                    fileWrite<<toWrite<<std::endl;
                }
                else{
                    getline(fileReader,toWrite);
                }
                i++;
            }
            fileReader.close();
            fileWrite.close();

            path = std::string(".\\\\") + std::string("Users\\\\") + username;
            remove((path+"\\\\reading.txt").c_str());
            rename((path+"\\\\tempR.txt").c_str(),(path+"\\\\reading.txt").c_str());
        }
        else if (choice == 'C')
        {
            path = path + string("\\\\completed.txt");
            fileReader.open(path.c_str());
            pathTemp = pathTemp + string("\\\\tempC.txt");
            fileWrite.open(pathTemp.c_str());
            i=1;
            position = 2*position +1;
            while(getline(fileReader,toWrite)){
                if(i != position){
                    fileWrite<<toWrite<<std::endl;
                }
                else{
                    getline(fileReader,toWrite);
                }
                i++;
            }
            fileReader.close();
            fileWrite.close();

            path = std::string(".\\\\") + std::string("Users\\\\") + username;
            remove((path+"\\\\completed.txt").c_str());
            rename((path+"\\\\tempC.txt").c_str(),(path+"\\\\completed.txt").c_str());

        }
        else if (choice == 'F')
        {
            std::cout<<"Fav\n";
            path = path + string("\\\\favourite.txt");
            fileReader.open(path.c_str());
            pathTemp = pathTemp + string("\\\\tempF.txt");
            fileWrite.open(pathTemp.c_str());
            while(getline(fileReader,toWrite)){
                if(i != position){
                    fileWrite<<toWrite<<std::endl;
                }
                i++;
            }
            fileReader.close();
            fileWrite.close();

            path = std::string(".\\\\") + std::string("Users\\\\") + username;
            remove((path+"\\\\favourite.txt").c_str());
            rename((path+"\\\\tempF.txt").c_str(),(path+"\\\\favourite.txt").c_str());
        }
        else if (choice == 'S')
        {
            path = path + string("\\\\share.txt");
            fileReader.open(path.c_str());
            pathTemp = pathTemp + string("\\\\tempS.txt");
            fileWrite.open(pathTemp.c_str());
            i=1;
            position = 2*position +1;
            while(getline(fileReader,toWrite)){
                if(i != position){
                    fileWrite<<toWrite<<std::endl;
                }
                else{
                    getline(fileReader,toWrite);
                }
                i++;
            }
            fileReader.close();
            fileWrite.close();

            path = std::string(".\\\\") + std::string("Users\\\\") + username;
            remove((path+"\\\\share.txt").c_str());
            rename((path+"\\\\tempS.txt").c_str(),(path+"\\\\share.txt").c_str());
        }
}

void FileWriter::updateBookmark(int position,char choice,std::string bookName,std::string newBookmark){
    ofstream fileWrite;
    ifstream fileReader;
    std::string path = std::string(".\\\\") + std::string("Users\\\\") + username;
    std::string pathTemp = path;
    std::string toWrite;
    int i = 0;
    if (choice == 'R')
    {
        path = path + string("\\\\reading.txt");
        fileReader.open(path.c_str());
        pathTemp = pathTemp +string("\\\\tempR.txt");
        fileWrite.open(pathTemp.c_str());
        position = 2*position +1;
        while(getline(fileReader,toWrite)){
            if(i != position){
                fileWrite<<toWrite<<std::endl;
            }
            else{
                fileWrite<<newBookmark<<std::endl;
            }
            i++;
        }
        fileReader.close();
        fileWrite.close();

        path = std::string(".\\\\") + std::string("Users\\\\") + username;
        remove((path+"\\\\reading.txt").c_str());
        rename((path+"\\\\tempR.txt").c_str(),(path+"\\\\reading.txt").c_str());
    }
    else if (choice == 'C')
    {
        path = path + string("\\\\completed.txt");
        fileReader.open(path.c_str());
        pathTemp = pathTemp + string("\\\\tempC.txt");
        fileWrite.open(pathTemp.c_str());
        position = 2*position +1;
        while(getline(fileReader,toWrite)){
            if(i != position){
                fileWrite<<toWrite<<std::endl;
            }
            else{
                fileWrite<<newBookmark<<std::endl;
            }
            i++;
        }
        fileReader.close();
        fileWrite.close();

        path = std::string(".\\\\") + std::string("Users\\\\") + username;
        remove((path+"\\\\completed.txt").c_str());
        rename((path+"\\\\tempC.txt").c_str(),(path+"\\\\completed.txt").c_str());
        }
    else if (choice == 'S')
    {
        path = path + string("\\\\share.txt");
        fileReader.open(path.c_str());
        pathTemp = pathTemp + string("\\\\tempS.txt");
        fileWrite.open(pathTemp.c_str());
        position = 2*position +1;
        while(getline(fileReader,toWrite)){
            if(i != position){
                fileWrite<<toWrite<<std::endl;
            }
            else{
                fileWrite<<newBookmark<<std::endl;
            }
            i++;
        }
        fileReader.close();
        fileWrite.close();

        path = std::string(".\\\\") + std::string("Users\\\\") + username;
        remove((path+"\\\\share.txt").c_str());
        rename((path+"\\\\tempS.txt").c_str(),(path+"\\\\share.txt").c_str());
    }
}
#endif // FILE_HANDLER
