#include<iostream>
#include<fstream>
#include<dirent.h>
#include "sort.h"
#include<conio.h>

namespace SORT_AUTHOR_HEADERS
{

const std::string DIR_SEARCH_BOOK_AUTHOR = "./search/book/author/";
const std::string DIR_SEARCH_ARTICLE_AUTHOR = "./search/article/author/";
const std::string FILE_AUTHOR_HEADER = "#header.txt";
const std::string FILE_AUTHOR_STATUS = "#status.txt";
const int MAX_AUTHOR_NAME = 15;
const int FILE_NOT_SORTED = 0;
const int FILE_SORTED = 1;

void _sortHeaderFiles(std::string dirPath, int sortstatus)
{
    std::fstream headerfile;
    std::ofstream statusfile;
    std::string headerfilepath;
    std::string statusfilepath;
    DIR *dir;
    struct dirent *ent;
    dir = opendir(dirPath.c_str());
    if(!dir)
    {
        std::cout<<"\ndir doesnt exist!!!"<<dirPath;
        return;
    }
    readdir(dir); //reading .
    readdir(dir); //reading ..
    while((ent = readdir(dir))!= NULL)
    {
        headerfilepath = dirPath + ent->d_name + '/' + FILE_AUTHOR_HEADER;
        statusfilepath = dirPath + ent->d_name + '/' + FILE_AUTHOR_STATUS;
        headerfile.open(headerfilepath.c_str());
        HeapSort hs(headerfile, MAX_AUTHOR_NAME);
        hs.sort();
        headerfile.close();
        statusfile.open(statusfilepath.c_str());
        statusfile<<sortstatus;
        statusfile.close();
    }
}
void sortAuthorHeaderFiles(int sortstatus)
{
    _sortHeaderFiles(DIR_SEARCH_BOOK_AUTHOR, sortstatus);
    _sortHeaderFiles(DIR_SEARCH_ARTICLE_AUTHOR, sortstatus);
}

}

