// NodeCom.h: interface for the NodeCom class.
//
//////////////////////////////////////////////////////////////////////

#ifndef NODECOM_H
#define NODECOM_H

#include "LIGraph.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

struct InfluenceValue{
	int node;
	float influence;
	bool operator<(const InfluenceValue &IV){
		return IV.influence< influence;
	}
};

class NodeCom 
{
public:
	NodeCom(const LIGraph &LG);
	virtual ~NodeCom();
	//Create community around core
	void create_Community(const LIGraph &LG,int c);

	//Node Join the community
	void join_Node(const LIGraph &LG, int v);

	//Get the influence
	int get_NextNode(const LIGraph &LG, float y);

	void run(const LIGraph &LG, float y);
	//Store the node in community
	multimap< int , int > ComToNode;
private:
	
	//Community No
	int cno;

	//position
	int position;
	
	//store the CommunityNode adjacency matrix
	// The Community's influence to node
	vector<float >   ComNodeadj;
	
	//Store the total influence of a node
	vector< InfluenceValue> InfluencePair;
	
	
	
	//Show the number of community of a node
	vector<int> inflag;


 
};

#endif
