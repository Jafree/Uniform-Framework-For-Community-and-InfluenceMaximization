// NodeCom.h: interface for the NodeCom class.
//
//////////////////////////////////////////////////////////////////////

#ifndef NODECOM_H
#define NODECOM_H

#include "LIGraph.h"
#include "Graph.h"
#include "adjIterator.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

struct InfluenceValue{
	int node;
	float influence;
	bool operator<(const InfluenceValue &IV)const{
		return IV.influence< influence;
	}
};

class NodeCom 
{
public:
	NodeCom(const LIGraph &LG);
	virtual ~NodeCom();
	//Create community around core
	void create_Community(const LIGraph &LG, const Graph &G , int c);

	//Node Join the community
	void join_Node(const LIGraph &LG, int v);

	//Get the influence
	int get_NextNode(const LIGraph &LG, float y);

	void run(const LIGraph &LG, const Graph &G, float y);
	//Store the node in community
	multimap< int , int > ComToNode;

	
private:
	
	//Community No
	int cno;

	
	
	//store the CommunityNode adjacency matrix
	// The Community's influence to node
	vector<float >   ComNodeadj;
	
	//Store the total influence of a node
	vector< InfluenceValue> InfluencePair;
		
	//Show the number of community of a node
	vector<int> inflag;
	//Indicate whether it is under consideration by this community
	vector<bool > inthis; 

	//Store the node waiting to check of joining the current community
	vector<InfluenceValue> waited; 
	int waitedend;
	
	int position;
};

#endif
