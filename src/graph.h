#pragma once
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
//Arbitrary UserNode class. Currently not in use.
struct UserNode {
    string username;
    string userID;
    string name;
    int weight;
    
    public:
        UserNode(string user_name, string user_ID, string Name, int weight) : 
        username(user_name), userID(user_ID), name(Name) {};
    
};

class AdjMatrix {
    private:
        int curr_size;
        int total_size;
        map<string, int> vertices;
        double** adjMatrix;
    public:
        AdjMatrix(int vertices);
        void insertEdge(string from, string to, double weight);
        void insertVertex(string vertex);
        bool isEdge(string from, string to);
        double getWeight(string from, string to);
        vector<string> getAdjacent(string vertex);
        void printAdjMatrix();
};

/**
 * Adjacency List implementation using a vector of maps with <string, double> key-value pairs. the double corresponds to the weight of an edge
 * @note Probably needs to be modified to take in integers rather than strings for storage optimization.
 */
class AdjList {
    private:
        int curr_size;
        int total_size;
        map<string, int> vertices;
        vector<map<string, double>> adjList;
    public:
        AdjList(int vertices);
        void insertEdge(string from, string to, double weight);
        void insertVertex(string vertex);
        bool isEdge(string from, string to);
        double getWeight(string from, string to);
        vector<string> getAdjacent(string vertex);
        void printAdjList();
        double djikstra(string node1, string node2);
};

AdjMatrix::AdjMatrix(int vertices)
{
    curr_size = 0;
    total_size = vertices;
    adjMatrix = new double*[vertices];
    for (int i = 0; i < vertices; i++)
    {
        adjMatrix[i] = new double[vertices]();
    }
    for (int i = 0; i < total_size; i++)
    {
        for (int j = 0; j < total_size; j++)
            adjMatrix[i][j] = 0;
    }

};

void AdjMatrix::insertVertex(string vertex)
{
    if(vertices.find(vertex) == vertices.end())
    {
        vertices[vertex] = curr_size++;
    }
}
void AdjMatrix::insertEdge(string from, string to, double weight)
{
    if (vertices.find(from) == vertices.end())
        vertices[from] = curr_size++;
    if (vertices.find(to) == vertices.end())
        vertices[to] = curr_size++;
    adjMatrix[vertices[from]][vertices[to]] = weight;
}

bool AdjMatrix::isEdge(string from, string to)
{
    if (adjMatrix[vertices[from]][vertices[to]] > 0)
        return true;
    return false;
}
double AdjMatrix::getWeight(string from, string to)
{
    return adjMatrix[vertices[from]][vertices[to]];
}
vector<string> AdjMatrix::getAdjacent(string vertex)
{
    vector<string> adjacentNodes;
    double* adjacent = adjMatrix[vertices[vertex]];
    for (auto vertex : vertices)
    {
        if (adjacent[vertex.second] != 0)
            adjacentNodes.push_back(vertex.first);
    }
    return adjacentNodes;
}
void AdjMatrix::printAdjMatrix()
{
    for (auto vertex : vertices)
    {
        cout << vertex.first << ": ";
        for (auto vertex2 : vertices)
        {
            if (adjMatrix[vertex.second][vertex2.second] > 0)
                cout << "[" << vertex2.first << " : " << adjMatrix[vertex.second][vertex2.second] << "], ";  
        }
        cout << endl;
    }
}
/**
 * Adjacency List constructor, takes in an integer that denotes the max number of vertices.
 * @param vertices describes the number of vertices
 * @note doubles are automatically 0 initialized, but it can be changed to another value
 */
AdjList::AdjList(int vertices)
{
    total_size = vertices;
    curr_size = 0;
    //boostList BoostList(vertices);
    adjList = vector<map<string, double>>(vertices);
    for (int i = 0; i < vertices; i++)
    adjList[i] = map<string, double>();
};

/**
 * Inserts vertex if it is not found in the vertices map
 * @param vertex is a string that contains the userID for the newly inserted vertex
 * @note commented lines in the function relate to the boost library.
 * We probably won't need this function much, since InsertEdge accomplishes the same thing
 */
void AdjList::insertVertex(string vertex)
{
    if (vertices.find(vertex) == vertices.end())
    {
        vertices[vertex] = curr_size++;
        //auto vertex = add_vertex(BoostList);
    }
    //get(boost::vertex_name, BoostList)[vertices[vertex]] = vertex; 
};
/**
 * Inserts edges and vertices if they are not already found in the vertices map
 * @param from denotes the origin string
 * @param to denotes the end of the edge
 * @param weight denotes the weight of the edge
 */
void AdjList::insertEdge(string from, string to, double weight)
{
    if (vertices.find(from) == vertices.end())
        vertices[from] = curr_size++;
    if (vertices.find(to) == vertices.end())
        vertices[to] = curr_size++;
    //auto edge =  add_edge(vertices[from], vertices[to], BoostList);
    //get(boost::edge_weight, BoostList)[edge.first] = weight;
    adjList.at(vertices[from])[to] = weight;
};
/**
 * Checks whether the edge exists
 * @param from denotes the origin vertex of the edge
 * @param to denotes the end of the edge
 * @note if the weight of the edge is 0, return false. Otherwise, return true
 */
bool AdjList::isEdge(string from, string to)
{
    /**
    if (edge(vertices[from], vertices[to], BoostList).second)
        return true;
    return false;
    */
    if (adjList[vertices[from]][to] > 0)
        return true;
    return false;
};

/** returns the weight of the edge between vertex from and vertex to
 * @param from denotes the origin vertex of the edge
 * @param to denotes the end of the edge
 */
double AdjList::getWeight(string from, string to)
{
    //return get(boost::edge_weight, BoostList)[edge(vertices[from], vertices[to], BoostList).first];
    return adjList[vertices[from]][to];
};
/** gets the out-edges of a particular vertex (does not get the in-edges)
 * @param vertex denotes the vertex whose out-edges we are trying to obtain
 * @note this function could be modified to include in-edges, but that depends on whether we will need it for conducting our graph search algorithms
 */
vector<string> AdjList::getAdjacent(string vertex)
{
    vector<string> adjacentNodes;
    if (vertices.find(vertex) == vertices.end())
        return vector<string>(0);
    map<string, double> adjacencyMap = adjList.at(vertices[vertex]);
    for (auto pair : adjacencyMap)
        adjacentNodes.push_back(pair.first);
        return adjacentNodes;
};
/** Prints the adjacency list
 * @note this function takes literal hours for anything above 400,000 vertices
 */
void AdjList::printAdjList()
{
    vector<pair<int,string>> ordered_indices;
    for (auto vertex : vertices){
        ordered_indices.push_back(pair<int,string>(vertex.second,vertex.first));
    }
    sort(ordered_indices.begin(), ordered_indices.end());
    for (auto vertex : ordered_indices)
    {
        cout << vertex.second << " : ";
        for (auto adjacent : adjList[vertex.first])
        {
            cout << "[" << adjacent.first << ", " << adjacent.second << "], ";
        }
        cout << endl;
    }
};

/** Algorithm that performs djikstra's search algorithm until the distance is found 
 * @param node1 denotes the origin node of the search
 * @param node2 denotes the end node of the search
 */
double AdjList::djikstra(string node1, string node2)
{
    //the vertices map holds the indices for all the nodes
    //vertices[string] will return the index corresponding to the string/node
    //The adjacency list is a vector of maps of <string, double> where the string denotes the userID and the double is the weight
    //the adjacency list is generally accessed using adjList[vertices[node1]][node2]
    return 0.0;
};