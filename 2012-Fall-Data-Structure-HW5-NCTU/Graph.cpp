/*
 * =====================================================================================
 *
 *       Filename:  Graph.cpp
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
#include <iostream>
#include "Graph.h"

using namespace std;

Graph::Graph(int v) 
{   //v is the amount of vertex in the graph
    _vertex = v;
    _table = new int*[_vertex];
    for(int i = 0; i < _vertex; i++) 
    {
        _table[i] = new int[_vertex];
        for(int j = 0; j < _vertex; j++) _table[i][j] = -1;//initialize the table
    }
}

Graph::~Graph()
{
    for(int i = 0; i < _vertex; i++)
    {
        delete [] _table[i];
    }
    delete [] _table;
}

void Graph::insertEdge(int v1, int v2, int w)
{
    _table[v1][v2] = _table[v2][v1] = w;
}

bool Graph::checkNoEdgeVertex()
{
    bool noedge = false;
    for(int i = 0; i < _vertex; i++)
    {
        int count = 0;
        for(int j = 0; j < _vertex; j++)
        {
            if(_table[i][j] == -1) count++;
        }
        if(count == _vertex)
        {
            noedge = true;
            break;
        }
    }
    return noedge;
}

void Graph::findMinEdge(int* v1, int* v2, int* w, bool valid[])
{   //Prim's Algorithm
    int minV1 = -1, minV2 = -1, minE = -1;//vertex and weight of the minimum cost edge this run
    for(int i = 0; i < _vertex; i++)      //search all node
    {
        if(!valid[i]) continue;    //check if this node could be a source of an edge or not
        for(int j = 0; j < _vertex; j++)
        {
            if(valid[j]) continue;        //if node is in the valid array, it can't be the end of the edge
            if(_table[i][j] == -1) continue;
            if( (minE == -1) || (minE > _table[i][j]) ) //find the minimum cost edge when i is the source of this edge
            {
                minE  = _table[i][j];
                minV1 = i;
                minV2 = j;
            }
        }
    }
    *v1 = minV1;
    *v2 = minV2;
    *w  = minE;
    //cin.get();  //for debug
}

void Graph::initialBoolArray(bool arr[])
{
    for(int i = 0; i < _vertex; i++)
    {
        arr[i] = false;
    }
}

void Graph::computeMSTree(int** table, bool* split)
{
    //if all node have at least one edge, than find the MST of the graph
    bool* valid;
    valid = new bool[_vertex];
    initialBoolArray(valid);
    valid[0] = true;
    int i = 0;
    for(int VisitedEdge = 0; VisitedEdge < _vertex - 1; VisitedEdge++)
    {
        int v1, v2, w;
        findMinEdge(&v1, &v2, &w, valid);
        if(v1 == -1 || v2 == -1)
        {
            *split = true;
            continue;
        }
        valid[v2] = true;
        table[i][0] = v1;
        table[i][1] = v2;
        i++;
        //cout << "(" << v1 << "," << v2 << "); ";
    }
    //cout << endl;
    delete [] valid;
}

bool Graph::checkSplitMSTree(int** table)
{
    for(int i = 0; i < _vertex - 1; i++)
    {
        if(table[i][0] == -1 || table[i][1] == -1)
        {
            return true;
        }
    }
    return false;
}

void Graph::printMST() 
{
    //construct MSTreeTable
    int** MSTreeTable;
    MSTreeTable = new int*[_vertex];
    for(int i = 0; i < _vertex; i++)
    {
        MSTreeTable[i] = new int[2];
        MSTreeTable[i][0] = 0;
        MSTreeTable[i][1] = 0;
    }

    bool splitMST = false;
    computeMSTree(MSTreeTable, &splitMST);

    //bool splitMST = checkSplitMSTree(MSTreeTable);
    bool noMST = checkNoEdgeVertex();  

    //cout << noMST << ", " << splitMST << endl;
    //check whether the graph has any node with no edge
    if(noMST == true || splitMST == true)
    { 
        cout << "No spanning tree" << endl;
        return;
    }
    else
    {
        for(int i = 0; i < _vertex - 1; i++)
        {
            cout << "(" << MSTreeTable[i][0] << "," << MSTreeTable[i][1] << "); ";
        }
        cout << endl;
    }

    //delete MSTreeTable
    for(int i = 0; i < _vertex; i++)
    {
        delete [] MSTreeTable[i];
    }
    delete [] MSTreeTable;
}

void Graph::listEdge() //for debug, list all the edge of the graph
{
    cout << "=================  List all the edge of the graph =======================" << endl;
    for(int i = 0; i < _vertex; i++)
    {
        for(int j = 0; j < _vertex; j++)
        {
            if(_table[i][j] != -1)
            {
                cout << "(" << i << ", " << j << ", " << _table[i][j] << "); ";
            }
        }
        cout << endl;
    }
    cout << "=================  List all the edge of the graph =======================" << endl << endl;
}

void Graph::printPath(int Des, int previous[])
{   //trace back from the destination. recursive print out the path.
    if(previous[Des] == -1) return;
    printPath(previous[Des], previous);
    cout << "(" << previous[Des] << "," << Des << "); ";
}

bool Graph::checkIfSame(int src, int des)
{
    if(src == des) //source and destination are same.
    {   //output the message 
        cout << "(" << src << "," << des << "); " << endl;
        return true;
    }
    return false;
}

bool Graph::allNodeOut(bool out[])
{
    bool result = false;
    int count = 0;
    for(int i = 0; i < _vertex; i++)
    {
        int count = 0;
        if(out[i] == true) count++;
    }
    if(count == _vertex)
    {
        result = true;
    }
    return result;
}

void Graph::initialData(int dist[], int previous[], bool out[])
{
    for(int i = 0; i < _vertex; i++)
    {   //initialize the data
            dist[i] = -1;
        previous[i] = -1;
             out[i] = false;
    }
}

void Graph::chooseNode(int* minSrc, int* minDist, bool out[], int dist[])
{
    for(int i = 0; i < _vertex; i++)
    {
        if(out[i]) continue;
        if( ((dist[i] < *minDist) || (*minDist == -1)) && (dist[i] != -1) )
        {
            *minDist = dist[i];
            *minSrc  = i;
        }
    }
}

void Graph::updateDist(int minSrc, bool out[], int dist[], int previous[])
{   //update the distance table
    for(int i = 0; i < _vertex; i++)
    {
        if(out[i]) continue;

        int alt;
        if(_table[minSrc][i] != -1)
        {
            alt = dist[minSrc] + _table[minSrc][i];
            if(alt < dist[i] || dist[i] == -1)
            {   //if new found distance is shorter than old, replace it.
                dist[i] = alt;
                previous[i] = minSrc;
                //cout << "(" << minSrc << ", " << minDes << ", " << minE << ")" << endl;
            }
        }
    }
}

void Graph::printShortest(int src, int des) 
{   //use Dijkstra calculate the shortest path from src to des
    if(checkIfSame(src, des)) return;

    int dist[_vertex];    //distance table, note every node's distance between the source.
    int previous[_vertex];//note the previous node of current node. for trace back the path.
    bool out[_vertex];    //see which node can be the source node yet destination node in this turn.

    initialData(dist, previous, out);
    dist[src] = 0; //self distance is zero.

    while(true)
    {
        if(allNodeOut(out)) break;
        int minSrc = -1, minDist = -1;
        //choose the node which is smallest distance from src as source this run.
        chooseNode(&minSrc, &minDist, out, dist);
        out[minSrc] = true;
        if(minDist == -1)
        {   //all nodes have been traversed 
            break;
        }
        updateDist(minSrc, out, dist, previous);//update the distance table
    }

    bool debug = false;
    if(debug) printDistAndPrev(dist, previous);
    if(noPath(dist, des)) return;
    printPath(des, previous);
    cout << endl;

}

bool Graph::noPath(int dist[], int des)
{
    if(dist[des] == -1)
    {   //there is no path can go from src to des
        cout << "Not exist" << endl;
        return true;
    }
    return false;
}

void Graph::printDistAndPrev(int dist[], int previous[])
{
    //print out distance table //for debug
    cout << "dist: ";
    for(int i = 0; i < _vertex; i++) cout << dist[i] << " ";
    cout << endl;

    //print out previous node table //for debug
    cout << "pre:  ";
    for(int i = 0; i < _vertex; i++) cout << previous[i] << " ";
    cout << endl;
}
