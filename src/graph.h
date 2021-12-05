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
    string userID;
    string name;
    int weight;
    int weight2;
    
    public:
        UserNode(string user_name, string user_ID, string Name, int weight) : userID(user_ID), name(Name) {};
    
};
/**
 * EdgeList implementation of graph using a map of pairs to doubles, where the pair contains the start vertex and end vertex of an edge, and the double denotes the weight of said edge
 * 
 */
class EdgeList {
    private:
        int curr_size;
        int vertices_amount;
        map<pair<int, int>, double>* edgeList;
        map<int, int> vertices;
    public:
        EdgeList();
        void insertEdge(int from, int to, double weight);
        bool isEdge(int from, int to);
        double getWeight(int from, int to);
        vector<int> getAdjacent(int vertex);
        void printEdgeList();
        double djikstra(int from, int to);
        int getNumVertices();
};

/**
 * EdgeList default constructor. Updates curr_size and creates a new map<pair<int,int>, double> object to store edges in.
 * @note unlike the adjacency list, curr_size here denotes the amount of unique edges
 */
EdgeList::EdgeList()
{
    curr_size = 0;
    vertices_amount = 0;
    edgeList = new map<pair<int,int>, double>();
};

/**
 * inserts an edge and updates the amount of unique edges by incrementing curr_size
 * 
 */
void EdgeList::insertEdge(int from, int to, double weight)
{
    if (vertices.find(from) == vertices.end())
        vertices[from] = vertices_amount++;
    if (vertices.find(to) == vertices.end())
        vertices[to] = vertices_amount++;
    pair<int,int> edge = pair<int,int>(from, to);
    if ((*edgeList)[edge] == 0)
        curr_size++;
    (*edgeList)[edge] = weight;
}

/**
 *  checks whether an edge exists in the edgeList map. If it exists, return true. Otherwise return false
 *  @param from is the origin vertex
 *  @param to is the end vertex of the edge
 *  @note works assuming we are using non-zero weights
 *  @returns bool
 */
bool EdgeList::isEdge(int from, int to)
{
    if (edgeList->find(pair<int,int>(from,to)) != edgeList->end())
        return true;
    return false;
}

/**
 * gets the weight of an edge. If zero is returned, that means the edge doesn't exist
 * @param from is the origin vertex
 * @param to is the end vertex of the edge
 * @note just because an edge from a to b doesn't exist does not mean that an edge from b to a doesn't exist
 * @returns the weight of the edge
 */
double EdgeList::getWeight(int from, int to)
{
    return (*edgeList)[pair<int,int>(from, to)];
}

/**
 * gets the outedges of a particular vertex
 * @param vertex denotes the vertex whose out-edges we are obtaining
 * @returns a vector of integers, where the integers are IDs of the end vertices of all the out-edges
 */
vector<int> EdgeList::getAdjacent(int vertex)
{
    vector<int> adjacentNodes;

    for (auto edge_weight_pair : *edgeList)
    {
        //basically what happens below is that we get the key of the map (map_iterator.first), since the key of the map is a pair (pair<int,int>) if pair.first == vertex, we've found an out-edge. If pair.second == vertex, we've found an in-edge
        if (edge_weight_pair.first.first == vertex)
            adjacentNodes.push_back(edge_weight_pair.first.second);
    }
    return adjacentNodes;
}

/**
 * prints the EdgeList
 * @note this is huge and it takes ages to finish printing
 */
void EdgeList::printEdgeList()
{
    for (auto edge_weight_pair : *edgeList)
    {
        cout << edge_weight_pair.first.first <<", " << edge_weight_pair.first.second <<  ": ";
        cout << edge_weight_pair.second << endl;
    }
}

/** Algorithm that performs djikstra's search algorithm until the distance is found 
 * @param node1 denotes the origin node of the search
 * @param node2 denotes the end node of the search
 */
double EdgeList::djikstra(int from, int to)
{
    //This structure holds edges. The edges can be accessed by either iterating over the map that holds them, or accessing them directly by using edgeList[pair<int,int>(start_vertex, end_vertex)]
    //You can use getAdjacent(vertex) to obtain the int values of the outedge vertices. 
    //For instance, if you have a graph 1->2 where 1 and 2 are vertices, using getAdjacent(1) will return a vector containing 2. If you want to obtain the weight of said edge, you can then use edgeList[pair<int,int>(1,2)]
    return 0.0;
}

int EdgeList::getNumVertices()
{
    return vertices_amount;
}


/**
 * Adjacency List implementation using a vector of maps with <string, double> key-value pairs. the double corresponds to the weight of an edge
 */
class AdjList {
    private:
        int curr_size;
        int total_size;
        map<int, int> vertices;
        vector<map<int, double>> adjList;
    public:
        AdjList(int vertices);
        void insertEdge(int from, int to, double weight);
        void insertVertex(int vertex);
        bool isEdge(int from, int to);
        double getWeight(int from, int to);
        vector<int> getAdjacent(int vertex);
        void printAdjList();
        double djikstra(int node1, int node2);
        int getNumVertices();
};

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
    adjList = vector<map<int, double>>(vertices);
    for (int i = 0; i < vertices; i++)
    adjList[i] = map<int, double>();
};

/**
 * Inserts vertex if it is not found in the vertices map
 * @param vertex is a string that contains the userID for the newly inserted vertex
 * @note commented lines in the function relate to the boost library.
 * We probably won't need this function much, since InsertEdge accomplishes the same thing
 */
void AdjList::insertVertex(int vertex)
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
void AdjList::insertEdge(int from, int to, double weight)
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
bool AdjList::isEdge(int from, int to)
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
double AdjList::getWeight(int from, int to)
{
    //return get(boost::edge_weight, BoostList)[edge(vertices[from], vertices[to], BoostList).first];
    return adjList[vertices[from]][to];
};
/** gets the out-edges of a particular vertex (does not get the in-edges)
 * @param vertex denotes the vertex whose out-edges we are trying to obtain
 * @note this function could be modified to include in-edges, but that depends on whether we will need it for conducting our graph search algorithms
 */
vector<int> AdjList::getAdjacent(int vertex)
{
    vector<int> adjacentNodes;
    if (vertices.find(vertex) == vertices.end())
        return vector<int>(0);
    map<int, double> adjacencyMap = adjList.at(vertices[vertex]);
    for (auto pair : adjacencyMap)
        adjacentNodes.push_back(pair.first);
        return adjacentNodes;
};
/** Prints the adjacency list
 * @note this function takes literal hours for anything above 400,000 vertices
 * @deprecated dont use this function gotta fix it lol
 */
void AdjList::printAdjList()
{
    vector<pair<int,int>> ordered_indices;
    for (auto vertex : vertices){
        ordered_indices.push_back(pair<int,int>(vertex.second,vertex.first));
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

int AdjList::getNumVertices()
{
    return curr_size;
}
double AdjList::djikstra(int node1, int node2)
{
    //the vertices map holds the indices for all the nodes
    //vertices[string] will return the index corresponding to the string/node
    //The adjacency list is a vector of maps of <string, double> where the string denotes the userID and the double is the weight
    //the adjacency list is generally accessed using adjList[vertices[node1]][node2]
    return 0.0;
};