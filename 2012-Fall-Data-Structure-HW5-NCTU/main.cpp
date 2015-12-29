#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;

int myAtoi(const char *const input) 
{
    int result = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        result = result * 10 + input[i] - '0';
    }
    return result;
}

void splitToInt (int result[], char * const input)
{
    int i, head, index;
    index = 0;
    head = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ') {
            input[i] = '\0';
            result[index] = myAtoi(input+head);
            index++;
            head = i + 1;
        }
    }
    result[index] = myAtoi(input+head);
}

int main (const int argc, const char * const argv[]) 
{
    if (argc != 2) {
        cout << "usage:" << endl;
        cout << argv[0] << " filename" << endl;
        return 0;
    }

    ifstream file;
    char buffer[2048];
    int vertex;
    int edge;
    file.open(argv[1]);
    if(!file.good())
    {
        cout << "error while opening file" << endl;
        return 0;
    }
    bool end = false;
    while (!end) {
        //get vertex number
        file.getline(buffer, 2048);
        vertex = myAtoi(buffer);
        //cout << vertex << endl;
        Graph g(vertex);

        //get edge number
        file.getline(buffer, 2048);
        edge = myAtoi(buffer);
        //cout << edge << endl;
        
        //get edges
        for (int i = 0; i < edge; i++) {
            int E[3];
            file.getline(buffer, 2048);
            splitToInt(E, buffer);
            //cout << E[0] << ' '<< E[1] << ' ' << E[2] << endl;
            g.insertEdge(E[0], E[1], E[2]);
        }
        g.printMST();
        while (true) {
            file.getline(buffer, 2048);
            int path[2];
            splitToInt(path, buffer);
            if (buffer[0] == 'z') {
                end = false;
                break;
            } else if (buffer[0] == 'x') {
                end = true;
                break;
            }
            g.printShortest(path[0], path[1]);
        }
        cout << endl;
    }
    file.close();

    return 0;
}
