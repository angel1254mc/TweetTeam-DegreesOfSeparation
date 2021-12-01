#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <fstream>
#include "graph.h"
using namespace std;

struct dataParse {
    static void loadNetwork(ifstream* dataStream, AdjMatrix* graph);
    static void loadNetwork(ifstream* dataStream, AdjList* graph);
};

void dataParse::loadNetwork(ifstream* dataStream, AdjMatrix* graph)
{
    int weight = 1; // This weight changes depending on the dataset. In this case, its just 1.
    vector<pair<string, string>> EdgeList;
    string parse = "not empty";
    string temp;
    while (parse != "")
    {
        getline(*dataStream, parse, ' ');
        temp = parse;
        getline(*dataStream, parse, '\n');
        if (parse == "")
            break;
        EdgeList.push_back(pair<string,string>(temp, parse));
    }
    for (auto pair : EdgeList)
    {
        graph->insertEdge(pair.first, pair.second, weight);
    }
}
void dataParse::loadNetwork(ifstream* dataStream, AdjList* graph)
{
    int weight = 1; // This weight changes depending on the dataset. In this case, its just 1.
    vector<pair<string, string>> EdgeList;
    string parse = "not empty";
    string temp;
    while (parse != "")
    {
        getline(*dataStream, parse, ' ');
        temp = parse;
        getline(*dataStream, parse, '\n');
        if (parse == "")
            break;
        EdgeList.push_back(pair<string,string>(temp, parse));
    }
    for (auto pair : EdgeList)
    {
        graph->insertEdge(pair.first, pair.second, weight);
    }
}