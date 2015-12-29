/*
 *       Compiler: g++ 4.6.3
 *=============================================================================
 *
 *        Program: Data Structure Project 6 - QuickSort and HeapSort
 *
 *       Filename: Table.h
 *
 *    Description: header of Table.cpp
 *
 *        Created: 2012/12/25 Tue 20:43:38
 *
 *         Author: shunyi
 *
 *=============================================================================
 */

#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
using namespace std;

class Node;

class Table
{
    public:
        Table();
        ~Table();
        void insertNode(string iname, int iab, int ih, int ihr, int itb, int ibb); //I
        void clearTable();  //C
        void showTable();   //show all table for debug
        bool typeIsDouble(string attr); //check if attribute's value type is Double.
                                        //ex: avg, obp, slg, ops.
        void selectShowTable(string attr1, string attr2); //show name, attr1.value, attr2.value according to spec
        void interChange(Node* ary[], int i, int j); //swap ary[i] and ary[j].

        void quicksort(const int left, const int right, string attr1);
        
        //heapsort
        int leftChild(int i, int heap_size); //conut the index of i's leftChild
        int rightChild(int i, int heap_size);//conut the index of i's rightChild
        void Min_Heapify(Node* ary[], int root, int heap_size, string attr2); //Min_Heapify for descending order.
        void heapsort(int head, int heap_size, string attr2);
        void sliceHeapsort(string attr1, string attr2); //heapsort the data which have same attr1 value

        void sort(string attr1, string attr2);  //S
    
    private:
        Node* _table[100]; //spec said there will not more than 100 entries.
        int _tablesize; //the value of the table size.
        
};

class Node
{
    friend class Table;
    friend ostream & operator<<(ostream &os, Node &input); //overload << for Table.showTable()
    public:
        Node(string iname, int iab, int ih, int ihr, int itb, int ibb); //constructor
        double getValue(string attribute); //get one of the Node's attribute value.
    private:
        string _name;
        int _ab; //a positive integer, always greater than zero
        int _h;  //a non-negative integer
        int _hr; //a non-negative integer
        int _tb; //a non-negative integer
        int _bb; //a non-negative integer
        double _avg; //avg == h / ab
        double _obp; //obp == (h+bb) / (ab+bb)
        double _slg; //slg == tb / ab
        double _ops; //obp + slg
};

#endif
