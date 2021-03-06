#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <chrono>
using namespace std::chrono;
typedef steady_clock Clock;

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
    int numVert = 456627;
    string vert;
    ifstream data;
    int user1;
    int user2;
    string trash;
    int searchAlgo;
    double dist = 0;
    string chosenFile = "../";
    string terminate = "";
    bool higgs = false;


    //The line below prints the full adjacency list.
    //NetworkGraph->printEdgeList();
    //cout << "Amount of vertices: " << NetworkGraph->getNumVertices() << endl;

    cout << "Welcome to the TweetTeam's Degree of Separation Finder" << endl;
    cout << "Please enter the name of the file containing the dataset you would like to analyze. If you would like to use the Higgs-Boson dataset, enter 1." << endl;
    cin >> chosenFile;
    if (chosenFile == "1") {
        chosenFile = "../higgs-social_network.txt";
        higgs = true;
    }
    else {
        chosenFile = "../" + chosenFile;
        cout << "Enter the number of vertices in this graph" << endl;
        cin >> vert;
        numVert = stoi(vert);
    }
    AdjList* AdjListGraph = new AdjList(numVert);
    EdgeList* EdgeListGraph = new EdgeList();
    cout << "loading graph..." << endl;
    auto t1 = Clock::now();
    data.open(chosenFile);
    dataParse::loadNetworkDual(&data, AdjListGraph, EdgeListGraph);
    auto t2 = Clock::now();
    std::cout << "This graph took ";
        if (higgs) {
            cout << duration_cast<seconds>(t2 - t1).count();
            cout  << " seconds to parse" << '\n';
        }
        else {
            cout << duration_cast<microseconds>(t2 - t1).count();
            cout  << " microseconds to parse" << '\n';
        }
       
       
    data.close();
    cout << endl;

    if (higgs) {
        cout << "For this stage of the project, we will be using a dataset containing twitter follower-following networks relating to the Higgs Boson discovery." << endl;
        cout << "These tweets are anonymized, so users are denoted by user ID's ranging from 1 to 456626" << endl;
        cout << endl;
    }

    while (terminate != "n")
    {
        cout << "Input the userID of the first user:" << endl;
        while (true)
        {
            if (cin >> user1)
                break;
            else
            {
                cout << "Enter a valid integer in the range [1,456626]" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        getline(cin, trash); //flushes the newline operator
        cout << "Input the userID of the second user:" << endl;
        while (true)
        {
            if (cin >> user2)
            {
                if (user2 == user1)
                {
                    cout << "Second user cannot have same ID as first user." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                break;
            }
            else
            {
                cout << "Enter a valid integer in the range [1,456626]" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        getline(cin, trash); //flushes the newline operator;
        cout << "Choose your preferred search method by inputting a number: " << endl;
        cout << "1 : Find the calculated distance between users using Djikstra's Algorithm with Adjacency List" << endl;
        cout << "2 : Find the calculated distance between users using Djikstra's Algorithm with Edge List" << endl;
        cout << "3 : Find degrees of separation between users using BFS with Adjacency List" << endl;
        cout << "4 : Find degrees of separation between users using BFS with Edge List" << endl;
        while (true)
        {
            if (cin >> searchAlgo)
                break;
            else
            {
                cout << "Enter a valid integer in the range [1,4]" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cout << "Beginning search..." << endl;
        switch (searchAlgo) {
        case 1:
            t1 = Clock::now();
            dist = AdjListGraph->djikstra(user1, user2);
            t2 = Clock::now();
            std::cout << "This search took ";
            if (higgs) {
                cout << duration_cast<seconds>(t2 - t1).count();
               cout  << " seconds!" << '\n';
            }
            else {
                cout << duration_cast<microseconds>(t2 - t1).count();
                cout << " microseconds!" << endl;
            }
            cout << "The shortest weighted path between " << user1 << " and " << user2 << " is: " << dist << endl;
            break;
        case 2:
            t1 = Clock::now();
            dist = EdgeListGraph->djikstra(user1, user2);
            t2 = Clock::now();
            std::cout << "This search took ";
            if (higgs) {
                cout << duration_cast<seconds>(t2 - t1).count();
                cout << " seconds!" << '\n';
            }
            else {
                cout << duration_cast<microseconds>(t2 - t1).count();
                cout <<  " microseconds!" << endl;
            }
            cout << "The shortest weighted path between " << user1 << " and " << user2 << " is: " << dist << endl;
            break;
        case 3:
            t1 = Clock::now();
            dist = AdjListGraph->degrees_of_separation(user1, user2);
            t2 = Clock::now();
            std::cout << "This search took ";
            if (higgs) {
                cout << duration_cast<seconds>(t2 - t1).count();
                cout << " seconds!" << '\n';
            }
            else {
                cout << duration_cast<microseconds>(t2 - t1).count();
                cout << " microseconds!" << endl;
            }
            cout << "The minimum degrees of separation between " << user1 << " and " << user2 << " is: " << dist << endl;
            break;
        case 4:
            t1 = Clock::now();
            dist = EdgeListGraph->degrees_of_separation(user1, user2);
            t2 = Clock::now();
            std::cout << "This search took ";
            if (higgs) {
                cout << duration_cast<seconds>(t2 - t1).count();
                cout << " seconds!" << '\n';
            }
            else {
                cout << duration_cast<microseconds>(t2 - t1).count();
                cout << " microseconds!" << endl;
            }
            cout << "The minimum degrees of separation between " << user1 << " and " << user2 << " is: " << dist << endl;
            break;
        default:
            cout << "Something went wrong with the program" << endl;
        };

        cout << "Would you like to search again? (type 'y' for \"yes\", or 'n' for \"no\"" << endl;
        cin >> terminate;
    }
    delete AdjListGraph;
    delete EdgeListGraph;
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
