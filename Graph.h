// Graph.h: interface for the Graph class.

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Edge.h"
using namespace std;


class Graph  
{
public:
	Graph(int v);
/*	Graph(const Graph& G):degree(G.vcount),adj(G.vcount){
		vcount=G.vcount;
		ecount=G.ecount;
		for(int i=0;i<vcount;i++){
			degree[i] = G.degree[i];
			adj[i].assign(vcount);
			for(int j=0;j<vcount;j++){
				adj[i][j]= G.adj[i][j];
			}
		}
		
	}
*/
	virtual ~Graph();
	//return vcount,ecount
	int getV() const{return vcount;}
	int getE() const{return ecount;}

	//insert or remove an edge
	void insert(Edge e);
	void remove(Edge e);

	//Judge if the edge exists 
	bool getEdge(int u,int v) const {return adj[u][v];}

	//Get Degree of a node
	int getDegree(int v) const {return degree[v];}


	



private:
	//number of node and edge
	int vcount;
	int ecount;
	vector< int > degree;
	vector< vector<bool> > adj;


};

#endif 