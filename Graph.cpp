// Graph.cpp: implementation of the Graph class.


#include "Graph.h"
#include <iostream>

// Construction/Destruction


Graph::Graph(int v)	:
	adj(v), degree(v,0),vcount(v),ecount(0)
{
		for(int i=0;i<v;i++)
			adj[i].assign(v,false);
		cout<< "Graph"<<endl;
}

Graph::~Graph()
{

}
void Graph::insert(Edge e){
	if(adj[e.u][e.v]==false){
		ecount++;
		++degree[e.u];
		++degree[e.v];
	}
	adj[e.u][e.v] = true;
	adj[e.v][e.u] = true;
	
}
void Graph::remove(Edge e){
	if(adj[e.u][e.v]==true){
		ecount--;
		--degree[e.u];
		--degree[e.v];
	}
	adj[e.u][e.v] = false;
	adj[e.v][e.u] = false;
}

//implement  the adjIterator which is a friend class to Graph

