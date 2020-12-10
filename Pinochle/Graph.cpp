/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#include "Graph.h"


/* *********************************************************************
Function Name: Graph
Purpose: To initialize all member variables of the class. 
Parameters: None
Return Value: None
Local Variables: None
Algorithm: 
		1) Assign the number of vertices as integer value received in parameter
		2)  assign the pointer of an array of size V, containing adjacency lists
Assistance Received: None
********************************************************************* */
Graph::Graph(int num)
{
	V = num;
	pairs = {};
	paths = {};
}


/* *********************************************************************
Function Name: ~Graph
Purpose: To delete all objects of the class.
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Graph::~Graph()
{
}

/* *********************************************************************
Function Name: addEdge
Purpose: To add an edge in the array containing adjacency lists
Parameters: 
		first, the integer value whose list we are accessing
		second, the integer value to be added into 'first's' list
Return Value: None
Local Variables: None
Algorithm: 
		1) Add integer second to intefer first's list as an edge
Assistance Received: None
********************************************************************* */
void Graph::addEdge(int first, int second)
{
	if (pairs.size() <= first) {
		while (pairs.size() <= first) {
			pairs.push_back({});
		}
	}
	pairs[first].push_back(second);
}


/* *********************************************************************
Function Name: evaluateAllPaths
Purpose: To evaluate all paths from vertex s to vertex d
Parameters:
		s, source vertex as an integer
		d, destination vertex as an integer
Return Value: None
Local Variables: 
		vertexVisited, an integer vector that keeps track if a vertex is visited or not
		path, an integer vectors that stores a path
Algorithm:
		1) Create a vector of int to keep track if each vertex is visited
		2) Create a vector to store all paths
		3) Assign all vertices as not visited which is 0
		4) Evaluate all paths using a recursive helper function 
Assistance Received: None
********************************************************************* */
void Graph::evaluateAllPaths(int s, int d)
{
	vector<int> vertexVisited;
	vector<int> path;

	int index = 0; 

	// Assign all vertices as not visited
	for (int i = 0; i < V; i++) {
		vertexVisited.push_back(0);
	}
	getPaths(vertexVisited, path, s, d, index);
}


/* *********************************************************************
Function Name: getAllPaths
Purpose: To get all paths from a source to destination recursively and store in the paths vector
Parameters:
		s, source vertex as an integer
		d, destination vertex as an integer
		visited[], an array that stores if a vertex has been visited
		path[], integer array that stores paths between source and destination
		path_index, an index in path array 
Return Value: None
Local Variables: None
Algorithm:
		1) Go to a current vertex and store in path array
		2) Assign the vertex as visited
		3) Check if the destination has been reached, if yes, add the individual path into 
			a vector and push the vector into all paths vector
		4) If destination has not been reached, recursively call the same function for all adjacent vertices 
		5) Remove the vertex from path array and assign the vertex as not visited in the boolean array 
Assistance Received: None
********************************************************************* */
void Graph::getPaths(vector<int> vertexVisited, vector<int> path, int s, int d, int& index)
{
	// Mark the current vertex and store it in path array
	vertexVisited[s] = 1;
	

	if (path.size() == index) {
		path.push_back(0);
	}
	path[index] = s;


	index += 1;

	// If destination reached, add to vector 
	if (s == d) {
		vector<int> singlePath;
		for (int i = 0; i < index; i++) {
			singlePath.push_back(path[i]);
		}
		paths.push_back(singlePath);
	}
	//If destination not reached
	else 
	{		
		vector<int>::iterator it;
		//for all adjacent nodes, recursively call self
		for (it = pairs[s].begin(); it != pairs[s].end(); ++it) {
			if (!vertexVisited[*it]) {
				getPaths(vertexVisited, path, *it, d, index);
			}
		}
	}

	vertexVisited[s] = 0;
	index -= 1;
	
}

/* *********************************************************************
Function Name: getPaths
Purpose: To return a vector with all paths generated
Parameters: None
Return Value: A vector containing vector of integers that stores all paths
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
vector<vector<int>> Graph::getAllPaths() {
	return paths;
}
