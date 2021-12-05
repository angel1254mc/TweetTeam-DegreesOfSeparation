#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include "graph.h"
#include "dataParse.h"
using namespace std;
//First, we need to obtain and initialize the graph. We need to take our input file (dataset), parse it correctly,
//and create our graph object.
//Later, we will also want to be able to quickly obtain user IDs from user names, so we can utilize a
//hash-based unordered map structure that would allow us to obtain in approx. O(1) time a user ID when provided
//A username.

//The program should then request the usernames of the two individuals we wish to evaluate for degrees of separation.
//Here we take advantage of the unordered Map. If there is no value corresponding to either of the usernames, we ask the user to try again
//We also give the user the option to change both of his decisions by starting again (user types -1)
int main() {
    EdgeList* NetworkGraph = new EdgeList();
    ifstream data;
    string user1;
    string user2;
    string trash;
    string searchAlgo;
    string terminate;
    data.open("../higgs-social_network.txt");
    dataParse::loadNetwork(&data, NetworkGraph);
    //The line below prints the full adjacency list.
    //NetworkGraph->printEdgeList();
    cout << "Amount of vertices: " << NetworkGraph->getNumVertices() << endl;
    cout << "Welcome to the TweetTeam's Degree of Separation Finder" << endl;
    cout << "For this stage of the project, we will be using a dataset containing twitter follower-following networks relating to the Higgs Boson discovery." << endl;
    cout << "These tweets are anonymized, so users are denoted by user ID's ranging from 1 to 456626" << endl;
    cout << endl;
    cout << "Input the userID of the first user" << endl;
    cin >> user1;
    getline(cin,trash); //flushes the newline operator
    cout << "Input the userID of the second user" << endl;
    cin >> user2;
    getline(cin,trash);
    cout << "Choose your preferred search method by inputting a number: " << endl;
    cout << "1 : Djikstra's with Adjacency Matrix"<< endl;
    cout << "2 : Djikstra's with Edge List" << endl;
    cin >> searchAlgo;
    cout << "Beginning search..." << endl;
    double dist = NetworkGraph->djikstra(stoi(user1), stoi(user2));
    cout << "The minimum degrees of separation between " << user1 << " and " << user2 << " is: " << dist << endl;
    cout << "type anything and press enter to terminate the program." << endl;
    cin >> terminate;
    data.close();
    delete NetworkGraph;
    return 0;
}
//Just a small graph to test that the adjacency list class is working
/**NetworkGraph->insertVertex("v1");
    NetworkGraph->insertVertex("v2");
    NetworkGraph->insertVertex("v3");
    NetworkGraph->insertVertex("v4");
    NetworkGraph->insertVertex("v5");
    NetworkGraph->insertVertex("v6");
    NetworkGraph->insertVertex("v7");
    NetworkGraph->insertVertex("v8");
    NetworkGraph->insertVertex("v9");
    NetworkGraph->insertVertex("v10");
    NetworkGraph->insertEdge("v1", "v2", 1);
    NetworkGraph->insertEdge("v2", "v3", 1);
    NetworkGraph->insertEdge("v3", "v4", 1);
    NetworkGraph->insertEdge("v4", "v5", 1);
    NetworkGraph->insertEdge("v5", "v6", 1);
    NetworkGraph->insertEdge("v6", "v7", 1);
    NetworkGraph->insertEdge("v7", "v8", 1);
    NetworkGraph->insertEdge("v8", "v9", 1);
    NetworkGraph->insertEdge("v9", "v10", 1);
    cout << "Weight of edge between v1 and v2: " << NetworkGraph->getWeight("v1", "v2") << endl;
    NetworkGraph->printAdjMatrix();*/