#pragma once
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/adjacency_matrix.hpp>
//#include <boost/graph/properties.hpp>
//#include <boost/graph/named_function_params.hpp>
#include <iostream>
using namespace std;
//using namespace boost;
struct UserNode {
    string username;
    string userID;
    string name;
    int weight;
    
    public:
        UserNode(string user_name, string user_ID, string Name, int weight) : 
        username(user_name), userID(user_ID), name(Name) {};
    
};

/**struct VertexData {
    UserNode* userData;
    string userID;
    VertexData(UserNode* user_Data = nullptr, string user_ID = "") :
    userData(user_Data), userID(user_ID) {};
};
*/
class AdjMatrix {
    private:
        //typedef adjacency_matrix<vecS, vecS, boost::directedS, boost::property<boost::vertex_name_t, string>, boost::property<boost::edge_weight_t, double>> boostMatrix;
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
class AdjList {
    private:
        //typedef adjacency_list<vecS,vecS, boost::bidirectionalS, boost::property<boost::vertex_name_t, string>, boost::property<boost::edge_weight_t,double>> boostList;
        //boostList BoostList;
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
    //boostMatrix BoostMatrix(vertices, );
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
AdjList::AdjList(int vertices)
{
    total_size = vertices;
    curr_size = 0;
    //boostList BoostList(vertices);
    adjList = vector<map<string, double>>(vertices);
    for (int i = 0; i < vertices; i++)
    adjList[i] = map<string, double>();
};
void AdjList::insertVertex(string vertex)
{
    if (vertices.find(vertex) == vertices.end())
    {
        vertices[vertex] = curr_size++;
        //auto vertex = add_vertex(BoostList);
    }
    //get(boost::vertex_name, BoostList)[vertices[vertex]] = vertex; 
};
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
double AdjList::getWeight(string from, string to)
{
    //return get(boost::edge_weight, BoostList)[edge(vertices[from], vertices[to], BoostList).first];
    return adjList[vertices[from]][to];
};
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

double AdjList::djikstra(string node1, string node2)
{
    //the vertices map holds the indices for all the nodes
    //vertices[string] will return the index corresponding to the string/node
    //The adjacency list is a vector of maps of <string, double> where the string denotes the userID and the double is the weight
    //the adjacency list is generally accessed using adjList[vertices[node1]][node2]
    return 0.0;
};