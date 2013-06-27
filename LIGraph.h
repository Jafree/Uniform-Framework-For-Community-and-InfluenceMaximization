// LIGraph.h: interface for the LIGraph class.


#ifndef LIGRAPH_H
#define LIGRAPH_H

#ifndef VARIABLE_X       //Set the variable x
#define VARIABLE_X 0.5
#endif
#ifndef VARIABLE_Z       //Set the variable z
#define VARIABLE_Z 1.0
#endif

#include "adjIterator.h"
#include <vector>

#include "Graph.h"
using namespace std;

//define the Local Influence Graph class for computing the Local Influence matrix
class LIGraph  
{
public:
	
	
	LIGraph(const Graph &G);
	virtual ~LIGraph();

	//Compute the Local Influence for all the node
	void runLI(const Graph &G);

	int getV() const{return vcount;}

	int getE() const{return ecount;}

	float getTotalInfluence(int i) const{return totalInfluence[i];}
	
	//return the influence that v did to u
	float getLI(int u, int v) const{return LIadj[u][v];}
	friend class NodeCom;

protected:
	
	  

	//store the variable Graph's v,e
	int vcount,ecount;
	
	//store the totol influence of a node
	vector< float >  totalInfluence;

	vector< float >  Influenced;

	vector< vector< float > > LIadj;

};

#endif 
