/*************************************************************
	 * Name:  Pradhyumna Wagle                                    *
	 * Project:  Project 1 Pinochle C++                           *
	 * Class:  CMPS 366 01 OPL									  *
	 * Date:  10/21/2020										  *
	 *************************************************************/

#pragma once

#include <list> 
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

class Graph
{

private:
	// Number of vertices in graph
	int V;  
	
	//A vector containing vectors of int that stores pairs
	vector<vector<int>> pairs;

	//vector containing all vertices path as integer values
	vector<vector<int>> paths;

	void getPaths(vector<int> vertexVisited, vector<int> path, int s, int d, int& index);

public:

	Graph(int num);
	~Graph();

	void addEdge(int u, int v);
	void evaluateAllPaths(int s, int d);
	vector<vector<int>> getAllPaths();
};

