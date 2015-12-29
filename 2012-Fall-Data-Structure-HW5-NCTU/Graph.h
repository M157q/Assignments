/*
 * =====================================================================================
 *
 *       Filename:  Graph.h
 *
 *    Description:  DS Project5 - Graph
 *
 *        Version:  1.0
 *        Created:  2012年12月11日 23時26分15秒
 *       Revision:  none
 *       Compiler:  g++ 4.6.3
 *
 *         Author:  shunyi
 *   Organization:  NCTUCS 
 *
 * =====================================================================================
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

using namespace std;

class Graph 
{
    public:
        Graph();
        Graph(int v);
        ~Graph();

        void insertEdge(int v1, int v2, int w);
        void printMST();
        void printShortest(int vs1, int vs2);
        void listEdge(); // for debug
    
    private:
        int** _table; 
        int   _vertex;
        int   _edge;

        bool checkNoEdgeVertex();
        bool checkSplitMSTree(int** table);
        void computeMSTree(int** table, bool* split);
        void findMinEdge(int* v1, int* v2, int* w, bool visited[]);
        void printPath(int vs2, int previous[]);
        void initialBoolArray(bool arr[]);
        bool checkIfSame(int src, int des);
        bool allNodeOut(bool out[]); 
        void printDistAndPrev(int dist[], int previous[]);
        void initialData(int dist[], int previous[], bool out[]);
        bool noPath(int dist[], int des);
        void chooseNode(int* minSrc, int* minDist, bool out[], int dist[]);
        void updateDist(int minSrc, bool out[], int dist[], int previous[]);
};

#endif 
