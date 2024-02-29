#ifndef _SORT_
#define _SORT_

#include<fstream>

void getString(std::fstream& pf, std::string& str, const int MAX_STRSIZE,int ind = -1,int basepos = 0, char delim = ' ')
{
    char r;
    str = "";
    if(ind!= -1)
        pf.seekg(basepos + ind*MAX_STRSIZE);
    for(int i=0; i<MAX_STRSIZE; i++)
    {
        r = pf.get();
        if(r == delim)
            break;
        str.push_back(std::tolower(r));
    }
}
void putString(std::fstream& pf, std::string& str, const int MAX_STRSIZE,int ind = -1,int basepos = 0, char delim = ' ')
{
    if(ind!= -1)
        pf.seekp(basepos + ind*MAX_STRSIZE);
    for(int i=0; i<MAX_STRSIZE; i++)
    {
        if(i<str.size())
            pf.put(std::tolower(str[i]));
        else
            pf.put(delim);
    }
}

class QuickSort
{
    std::fstream &sortfile;
    int basepos;
    int noOfEls;
    int ELSIZE;
    char DELIM;
    std::string str1;
    std::string str2;
public:
    QuickSort(std::fstream& _file,int _noOfEls, int _ELSIZE, char _DELIM = ' '):sortfile(_file)
    {
        basepos = _file.tellg();
        noOfEls = _noOfEls;
        ELSIZE = _ELSIZE;
        DELIM = _DELIM;
    }
    QuickSort(std::fstream& _file, int _ELSIZE, char _DELIM = ' '):sortfile(_file)
    {
        basepos = _file.tellg();
        _file.seekg(0, std::ios::end);
        int endpos = _file.tellg();
        noOfEls = (endpos - basepos)/_ELSIZE;
        _file.seekg(basepos);
        ELSIZE = _ELSIZE;
        DELIM = _DELIM;
    }
private:
    int partition (int lb, int ub);
    void _sort(int low, int high);
public:
    void sort()
    { _sort(0 , noOfEls-1); }
};
    int QuickSort::partition (int lb, int ub)
    {
        if(lb == ub)
            return lb;
        std::string a;
        getString(sortfile, a, ELSIZE, lb, basepos); //pivot index element
        int up = ub;
        int down = lb;
        while(down < up)
        {
            getString(sortfile, str1, ELSIZE, down, basepos);
            while(str1 <= a && down < ub)
            {
                down++;
                getString(sortfile, str1, ELSIZE, down, basepos);
            }
            getString(sortfile, str2, ELSIZE, up, basepos);
            while(str2 > a)
            {
                up--;
                getString(sortfile, str2, ELSIZE, up, basepos);
            }
            if(down < up)
            {
                putString(sortfile, str1, ELSIZE, up, basepos);
                putString(sortfile, str2, ELSIZE, down, basepos);
            }
        }
        putString(sortfile, str2, ELSIZE, lb, basepos);
        putString(sortfile, a, ELSIZE, up, basepos);
        return up;
    }
    void QuickSort::_sort(int low, int high)
    {
        if (low < high)
        {
            int pivot = partition(low, high);
            _sort(low, pivot - 1);
            _sort(pivot + 1, high);
        }
    }


class HeapSort
{
    std::fstream &sortfile;
    int basepos;
    int noOfEls;
    int ELSIZE;
    char DELIM;
    std::string str1;
    std::string str2;
public:
    HeapSort(std::fstream& _file,int _noOfEls, int _ELSIZE, char _DELIM = ' '):sortfile(_file)
    {
        basepos = _file.tellg();
        noOfEls = _noOfEls;
        ELSIZE = _ELSIZE;
        DELIM = _DELIM;
    }
    HeapSort(std::fstream& _file, int _ELSIZE, char _DELIM = ' '):sortfile(_file)
    {
        basepos = _file.tellg();
        _file.seekg(0, std::ios::end);
        int endpos = _file.tellg();
        noOfEls = (endpos - basepos)/_ELSIZE;
        _file.seekg(basepos);
        ELSIZE = _ELSIZE;
        DELIM = _DELIM;
    }
private:
    void makeheap();
    void sortFromHeap();
public:
    void sort()
    {
        makeheap();
        sortFromHeap();
    }
};
void HeapSort::makeheap()
{
    int q;
    for(int i=1; i<noOfEls; i++)
        for(int j=i; j>=0;j = q)
        {
            q = (j-1)/2;
            getString(sortfile, str1, ELSIZE, j, basepos);
            getString(sortfile, str2, ELSIZE, q, basepos);
            //COMPARING WITH FATHER NODE
            if(str2<str1)
            {
                //SWAPPING FATHER AND CHILD
                putString(sortfile, str1, ELSIZE, q, basepos);
                putString(sortfile, str2, ELSIZE, j, basepos);
            }
            else
                break;
        }
}
void HeapSort::sortFromHeap()
{
    int r,l;
    std::string a;
    for(int i=noOfEls-1; i>0; i--)
     {
        //SWAPPING LARGEST ELEMENT FROM INDEX 0 TO PROPER POSITION
        getString(sortfile, str1, ELSIZE, 0, basepos);
        getString(sortfile, str2, ELSIZE, i, basepos);
        putString(sortfile, str1, ELSIZE, i, basepos);
        putString(sortfile, str2, ELSIZE, 0, basepos);
        //HEAPIFY THE REMAINING HEAP
        for(int j=0; 2*j+2<i;)
        {
            l = 2*j+1;
            r = 2*j+2;
            getString(sortfile, a, ELSIZE, j, basepos);
            getString(sortfile, str1, ELSIZE, l, basepos);
            getString(sortfile, str2, ELSIZE, r, basepos);

            if(a>= str1 && a>= str2)//FATHER NODE IS ALREADY LARGEST
                break;
            else
            {
                if(str1 >= str2)
                {
                    putString(sortfile, str1, ELSIZE, j, basepos);
                    putString(sortfile, a, ELSIZE, l, basepos);
                    j = l;
                }
                else
                {
                    putString(sortfile, str2, ELSIZE, j, basepos);
                    putString(sortfile, a, ELSIZE, r, basepos);
                    j = r;
                }
            }
        }
     }
}



void insertInSortedFile(std::fstream& sfile, const std::string &insert_String, const int noOfEls, const int ELSIZE, const char DELIM = ' ')
{
    int basepos = sfile.tellg();
    std::string readStr;
    int i;
    for(i=0; i<noOfEls; i++)
    {
        sfile.seekg(basepos + i*ELSIZE);
        getString(sfile, readStr, ELSIZE);
        if(insert_String == readStr)
            return;
        else if(insert_String < readStr)
            break;
    }
    if(i == noOfEls)
    {
        readStr = insert_String;
        sfile.seekg(basepos + i*ELSIZE);
        putString(sfile, readStr, ELSIZE);
    }
    else
    {
        for(int j=noOfEls; j>i; j--)
        {
            sfile.seekg(basepos + (j-1)*ELSIZE);
            getString(sfile, readStr, ELSIZE);
            sfile.seekp(basepos + j*ELSIZE);
            putString(sfile, readStr, ELSIZE);
        }
        readStr = insert_String;
        sfile.seekp(basepos + i*ELSIZE);
        putString(sfile, readStr, ELSIZE);
    }
}

#endif // _SORT_
