/*
 *       Compiler: g++ (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3
 *=========================================================================
 *
 *        Program: Data Structure Project 6 - QuickSort and HeapSort
 *
 *       Filename: Table.cpp
 *
 *    Description: Declaration of Class Table
 *
 *        Created: 2012/12/25 Tue 21:02:14
 *
 *         Author: shunyi
 *
 *=========================================================================
 */

#include <iostream>
#include <string>
#include <cstdio>
#include "Table.h"
using namespace std;

Table::Table() //constructor
{
    for(int i = 0; i < 100; i++)
    {
        _table[i] = NULL;
    }
    _tablesize = 0;
}

Table::~Table() //destructor
{
    for(int i = 0; i < _tablesize; i++)
    {
        delete _table[i];
    }
}

void Table::insertNode(string iname, int iab, int ih, int ihr, int itb, int ibb) //i means input
{
    _table[_tablesize] = new Node(iname, iab, ih, ihr, itb, ibb);
    _tablesize++;
}


void Table::clearTable() //clear the table
{
    for(int i = 0; i < _tablesize; i++)
    {
        delete _table[i];
        _table[i] = NULL;
    }

    _tablesize = 0;

}

ostream& operator << (ostream &os, Node &input) //overload the << for showTable
{
    os << "(";
    os << input._name << ", \t";
    os << input._ab << ", \t";
    os << input._h << ", \t";
    os << input._hr << ", \t";
    os << input._tb << ", \t";
    os << input._bb << ", \t";
    printf("%.3f, \t", input._avg);
    printf("%.3f, \t", input._obp);
    printf("%.3f, \t", input._slg);
    printf("%.3f", input._ops);
    os << "); ";
    return os;
}

void Table::showTable() //show all table for debug
{
    //cout << "Name\t\tAB\tH\tHR\tTB\tBB\tAVG\tOBP\tSLG\tOPS" << endl;
    for(int i = 0; i < _tablesize; i++)
    {
        cout << *_table[i] << endl; //using << operator overloading
    }
}

bool Table::typeIsDouble(string attr) //check the attribute value is double or not
{
    if(attr == "AVG" || attr == "OBP" || attr == "SLG" || attr == "OPS") 
        return true;
    else 
        return false;
}

void Table::selectShowTable(string attr1, string attr2) 
{//show the data with selected attr1 and attr2 according to spec.
    for(int i = 0; i < _tablesize; i++)
    {
        cout << "(";
        cout << _table[i]->_name << ", ";
        if(typeIsDouble(attr1))//if value is double, set precision to 3.
            printf("%.3f, ", _table[i]->getValue(attr1)); 
        else cout << _table[i]->getValue(attr1) << ", ";
        if(typeIsDouble(attr2))//if value is double, set precision to 3.
            printf("%.3f", _table[i]->getValue(attr2)); 
        else cout << _table[i]->getValue(attr2);
        cout << "); ";
    }
    cout << endl;
}

void Table::interChange(Node* ary[], int i, int j)
{   //swap 
    Node* temp;
    temp = ary[i];
    ary[i] = ary[j];
    ary[j] = temp;
}


void Table::quicksort(const int left, const int right, string attr1)
{   //descending order
    if(left < right)
    {
        //cout << "left: " << left << ", right: " << right << endl; //cout right and left for debug
        int i = left, j = right + 1;
        double pivot = _table[left]->getValue(attr1); //double pivot for double type comparison, use int will failed.
        do {
            do {i++;} while (i < j && _table[i]->getValue(attr1) >= pivot);//descending order
            do {j--;} while (j >= i && _table[j]->getValue(attr1) <= pivot);//descending order
            if (i < j) interChange(_table, i, j);
        } while (i < j);
        interChange(_table, left, j);
        quicksort(left, j-1, attr1);
        quicksort(j+1, right, attr1);
    }
}

int Table::leftChild(int i, int heap_size)
{
    int l = (2*i + 1);
    if(l >= heap_size) return -1;
    return l;
}

int Table::rightChild(int i, int heap_size)
{
    int r = (2*i + 2);
    if(r >= heap_size) return -1;
    return r;
}

void Table::Min_Heapify(Node* ary[], int root, int heap_size, string attr2)
{   //use Min_Heapify for descending order
    int l = leftChild(root, heap_size);
    int r = rightChild(root, heap_size);
    int smallest;
    if(l == -1) return; //root is leaf node
    else if(r == -1) smallest = l; //no right child then choose left child
    else smallest = (ary[l]->getValue(attr2) < ary[r]->getValue(attr2)) ? l : r;

    if(ary[root]->getValue(attr2) > ary[smallest]->getValue(attr2))
    {
        interChange(ary, root, smallest);
        Min_Heapify(ary, smallest, heap_size, attr2);
    }
}

void Table::heapsort(int head, int heap_size, string attr2)
{
    //Build_Min_Heap
    for(int i = (heap_size - 2) / 2; i >= 0; i--) 
        Min_Heapify(_table+head, i, heap_size, attr2);
    //sort
    for(int i = heap_size-1; i >= 0; i--)
    {
        interChange(_table+head, 0, i);
        Min_Heapify(_table+head, 0, i, attr2);
    }
}

void Table::sliceHeapsort(string attr1, string attr2)
{
    int head = 0;
    int i;
    for(i = 0; i < _tablesize; i++)
    {
        if(_table[head]->getValue(attr1) != _table[i]->getValue(attr1))
        {   //devide the same value into a slice
            if(head != i-1) //two or more entry have same value
            {
                heapsort(head, (i-1)-head+1, attr2);
            }
            head = i;
        }
    }
    //do this for the last slice
    if(head != i-1) 
    {
        heapsort(head, (i-1)-head+1, attr2);
    }
}

void Table::sort(string attr1, string attr2)
{
    quicksort(0, _tablesize-1, attr1);
    sliceHeapsort(attr1, attr2);
    selectShowTable(attr1, attr2);
}


//Implementation of class Node ===========================
Node::Node(string iname, int iab, int ih, int ihr, int itb, int ibb) //i means input
{
    _name = iname;
    _ab = iab;
    _h = ih;
    _hr = ihr;
    _tb = itb;
    _bb = ibb;
    _avg = (double)ih / (double) iab;
    _obp = (double)(ih+ibb) / (double)(iab+ibb);
    _slg = (double)itb / (double)iab;
    _ops = _obp + _slg;
}

double Node::getValue(string attribute)
{
    if(attribute == "AB")  return (double)this->_ab;
    if(attribute == "H")   return (double)this->_h;
    if(attribute == "HR")  return (double)this->_hr;
    if(attribute == "TB")  return (double)this->_tb;
    if(attribute == "BB")  return (double)this->_bb;
    if(attribute == "AVG") return this->_avg;
    if(attribute == "OBP") return this->_obp;
    if(attribute == "SLG") return this->_slg;
    if(attribute == "OPS") return this->_ops;
}
