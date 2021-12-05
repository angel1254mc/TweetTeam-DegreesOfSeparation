#include "graph.h"
#include <vector>
#include <queue>
/*
Djikstra's implementation for Project 3
Jeya Iyadurai
*/

using namespace std;

double AdjList::djikstra(int from, int to){
	/*
	Notes: 
		Current implementation does not require "previous" vector.
		Returns the shortest path between two nodes.	
	*/
	priority_queue < pair<double, int>, vector< pair<double, int> >, greater< pair<double, int> > > pqueue; //(weight, vertex)
	
	vector<double> distances(this->total_size, INT_MAX);
	//vector<int> previous(this->total_size, -1);
	
	pqueue.push(pair<double, int>{0.0, from});
	
	distances[from] = 0.0;
	
	while(!queue.empty()){
		int vertex = queue.top().second;
		pqueue.pop();
		
		auto adjacentVertices = this->getAdjacent(vertex);
		for(auto adjacent : adjacentVertices){
			//USING PSEUDOCODE FROM AMAN'S LECTURE ON GRAPH ALGORITHMS FOR THIS RELAXATION//
			if(distances[vertex] + this->getWeight(vertex, adjacent) < distances[adjacent]){
				distances[adjacent] = distances[vertex] + this->getWeight(vertex, adjacent);
				//previous[adjacent] = vertex;
				pqueue.push(pair<double, int>{distances[adjacent], adjacent});
			}
		}
	}
	
	return distances[to];
}

//TODO
double EdgeList::djikstra(int from, int to){
	/*
	Notes: 
		Current implementation does not require "previous" vector.
		Returns the shortest path between two nodes.	
	*/
	priority_queue < pair<double, int>, vector< pair<double, int> >, greater< pair<double, int> > > queue; //(weight, vertex)
	
	vector<double> distances(this->total_size, INT_MAX);
	//vector<int> previous(this->total_size, -1);
	
	queue.push(pair<double, int>{0.0, from});
	
	distances[from] = 0.0;
	
	while(!queue.empty()){
		int vertex = queue.top().second;
		queue.pop();
		
		adjacentVertices = this->getAdjacent(vertex);
		for(auto adjacent : adjacentVertices){
			//USING PSEUDOCODE FROM AMAN'S LECTURE ON GRAPH ALGORITHMS FOR THIS RELAXATION//
			if(distances[vertex] + this->getWeight(vertex, adjacent) < distances[adjacent]){
				distances[adjacent] = distances[vertex] + this->getWeight(vertex, adjacent);
				//previous[adjacent] = vertex;
				queue.push(pair<double, int>{distances[adjacent], adjacent});
			}
			
		}
	}
	
	return distances[to];
}
	
