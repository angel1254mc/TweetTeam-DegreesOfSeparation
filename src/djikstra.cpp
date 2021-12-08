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
		Not in use, use function from graph.h
	*/
	priority_queue < pair<double, int>, vector< pair<double, int> >, greater< pair<double, int> > > pqueue; //(weight, vertex)
	
	vector<double> distances(this->curr_size+1, INT_MAX);
	//vector<int> previous(this->total_size, -1);
	
	pqueue.push(pair<double, int>{0.0, from});
	
	distances[from] = 0.0;
	//int count = 0;
	
	while(!pqueue.empty()){
		int vertex = pqueue.top().second;
		pqueue.pop();
		
		/*count++;
		if(count%1000 == 0){
			cout << "1k processed" << endl;
		}*/
		
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

double EdgeList::djikstra(int from, int to){
	/*
	Notes: 
		Not in use, use function from graph.h
	*/
	priority_queue < pair<double, int>, vector< pair<double, int> >, greater< pair<double, int> > > pqueue; //(weight, vertex)
	int vertices_count = this->getNumVertices();
	vector<double> distances(vertices_count + 1, INT_MAX);
	//vector<int> previous(this->total_size, -1);
	
	pqueue.push(pair<double, int>{0.0, from});
	
	distances[from] = 0.0;
	//int count = 0;
	while(!pqueue.empty()){
		int vertex = pqueue.top().second;
		pqueue.pop();
		/*count++;
		if(count%1000 == 0){
			cout << "1k processed";
		}*/
		//cout << pqueue.size() << endl;
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
	
