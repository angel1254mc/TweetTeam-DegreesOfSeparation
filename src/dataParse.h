#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <fstream>
#include "graph.h"
using namespace std;
/**
 * Static class that contains all functions related to parsing and storing dataset
 */
struct dataParse {
    static void loadNetwork(ifstream* dataStream, AdjMatrix* graph);
    static void loadNetwork(ifstream* dataStream, AdjList* graph);
};

/**
 * Takes in a read stream for a dataset and a pointer to a graph object. Parses dataset and stores it 
 * in the graph object
 * @param dataStream denotes the pointer to the ifstream
 * @param graph denotes a pointer to the graph object. Can either be an Adjacency List or an Edge List
 * @note ifstream needs to have opened file already open
 */
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