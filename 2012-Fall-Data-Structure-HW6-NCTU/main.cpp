/*
 *       Compiler: g++ (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3
 *=========================================================================
 *
 *        Program: Data Structure Project 6 - QuickSort and HeapSort
 *
 *       Filename: main.cpp
 *
 *    Description: main of DS project6
 *
 *        Created: 2012/12/25 Tue 21:02:53
 *
 *         Author: shunyi
 *
 *=========================================================================
 */

#include "Table.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int myatoi(const char* const str)
{
    int r = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        r = 10*r + str[i] - '0';
    }
    return r;
}

void EditBufferForStrtok(char buffer[])
{
    int len = (int)strlen(buffer);
    buffer[len] = '\n';
    buffer[len+1] = '\0';
}

void Process(Table& T, char buffer[])
{
    char* Operation;
    Operation = strtok(buffer, " \n");
    switch(Operation[0])
    {
        case 'I':
        {
            string name;
            int data[5];
            name = strtok(NULL, " \n");
            for(int i = 0; i < 5; i++)
            {   
                data[i] = myatoi(strtok(NULL, " \n"));
            }
            T.insertNode(name, data[0], data[1], data[2], data[3], data[4]);
            break;
        }

        case 'S':
        {
            string attr1 = strtok(NULL, " \n");
            string attr2 = strtok(NULL, " \n");
            T.sort(attr1, attr2); //sorting data according to attribute1 and 2.
            break;
        }
    }
}

int main(int argc, const char *argv[])
{
    if (argc != 2)  //check argc
    {
        cout << "[usage]: " << argv[0] << " filename" << endl;
        return 0;
    }
    
    ifstream infile;
    
    if(!infile.good()) //check input file status
    {
        cout << "error while open file or file doesn't exist." << endl;
        return 1;
    }

    infile.open(argv[1]);
    Table T;
    char buffer[2048];
    bool end = false;
    while(infile.good() && !end)
    {
        infile.getline(buffer, 2048);
        switch(buffer[0])
        {
            case 'C':
                T.clearTable();
                continue;
            case 'E': //terminate and exit program
                end = true;
                break;
        }
        EditBufferForStrtok(buffer);
        Process(T, buffer);
    }
    infile.close();
    return 0;
}
