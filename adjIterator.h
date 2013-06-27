//Every node have a iterator to get every edge that is adjacent to it 
#ifndef ADJITERATOR_H
#define ADJITERATOR_H

#include "Graph.h"	
	class adjIterator{

private:
	const Graph &G;
	//v is current node which we choose to iterate
	//i is the position now 
	int i, v;
public:
	adjIterator(const Graph &G, int v) :
	G(G),v(v),i(-1)	{ }

	//return the first edge which is adjacent to v
	int bbeg(){ i = -1; int tmp =next();return tmp;}

	//return the next edge which is adjacent to v
	int next(){
		for(i++;i<G.getV();i++)
			if(G.getEdge(v,i)==true)return i;
		return -1;
	}

	//Judge if it is the end
	bool end(){ return i>=G.getV();}

};

#endif