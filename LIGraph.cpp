// LIGraph.cpp: implementation of the LIGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "LIGraph.h"
#include "Graph.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LIGraph::LIGraph(const Graph& G) :
	vcount(G.getV()), ecount(G.getE()), LIadj(G.getV()) , totalInfluence(G.getV()), Influenced(G.getV())
{
		for(int i= 0; i<G.getV();i++){
			LIadj[i].assign( G.getV(),0.0F);
			totalInfluence[i] = 0.0F;
			Influenced[i] = 0.0F;
		}
		cout<<"LI"<<endl;
}

LIGraph::~LIGraph()
{
	
}


void LIGraph::runLI(const Graph &G)
{
	// compute the Local influence to each node
	for(int i=0;i<vcount;i++){

		adjIterator iter(G,i);
		//Process the node that is adjacent to j
		for(int j = iter.bbeg(); iter.end()!= true; j= iter.next()){
			float temp;
			temp = 1.0F/static_cast<float>(G.getDegree(i));
			LIadj[i][j] += temp;
			totalInfluence[j] += temp;
			Influenced[i] += temp;
	
			adjIterator inneriter(G,j);
			//Process influence of two hop node
			for(int k = inneriter.bbeg(); !inneriter.end(); k =inneriter.next()){
				if((k!=i)&&(k!=j)){
				temp = VARIABLE_X/static_cast<float>((G.getDegree(j)-1)*G.getDegree(i));
				LIadj[i][k] += temp;
				totalInfluence[k] += temp;
				Influenced[i] += temp;

				//Insert the reinforcement influence
				if(G.getEdge(i,k) == true){
					LIadj[i][k] += temp*VARIABLE_Z;
					totalInfluence[k] += temp*VARIABLE_Z;
					Influenced[i] += temp*VARIABLE_Z;
				}//endif
				
				}//endif
			}//endfor
		} 
		
	}
}


