// NodeCom.cpp: implementation of the NodeCom class.
//
//////////////////////////////////////////////////////////////////////

#include "NodeCom.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


NodeCom::NodeCom(const LIGraph &LG): cno(-1), position(LG.getV()), ComNodeadj(LG.getV(),0.0F),inflag(LG.getV(),0),InfluencePair(LG.getV())
			
{	
	int i;
	for( i=0;i<LG.getV();i++){
		InfluencePair[i].node = i;
		InfluencePair[i].influence = LG.getTotalInfluence(i) ;
		//cout<<LG.getTotalInfluence(i)<<endl;
	}
	// sort based on the influence
	sort(InfluencePair.begin(), InfluencePair.end());
/*	double sum=0;
	for(i=0;i<LG.getV();i++){
		cout<<setw(6)<<InfluencePair[i].node<<ends<<InfluencePair[i].influence<<ends<<LG.Influenced[i]<<endl;
		sum+=InfluencePair[i].influence;
	}
	cout<<"×ÜÊý"<<sum<<endl;
*/
}

NodeCom::~NodeCom()
{

}


void NodeCom::create_Community(const LIGraph &LG, int c){
	//set the functioning community and set restart
	cno = c;
	position = LG.getV();

	//set the flag which denotes that the node is in a community
	inflag[cno]++;

	for(int i=0;i<LG.getV();i++){
		ComNodeadj[i] = LG.getLI(i,cno);
	}
	//cno join the community
	ComToNode.insert(make_pair(cno,cno));

}

//node join the community

void NodeCom::join_Node(const LIGraph &LG, int v){
	//set flag
	inflag[v]++;
	
	//join the community
	ComToNode.insert(make_pair(cno, v));
	
	// Compute the influence of the community to each node
	for(int i=0;i<LG.getV();i++){
		ComNodeadj[i]+=LG.getLI(i,v);
	}
}


//get next node to join the community,if exits
int NodeCom::get_NextNode(const LIGraph &LG, float y){
	--position;
	for(; position>=0;position--){
		if((ComNodeadj[position] >= y)&&(position!=cno))return position;
	}
	return -1;
}

void NodeCom::run(const LIGraph &LG, float y){
	//traverse all the node until all node join in at least one community
	vector<bool > inthis;      //if  in this community

	for(int i=0;i< LG.getV();i++){
		//v is the max influence node
		int v = InfluencePair[i].node;
		
		if(inflag[v]==0){
			//find the core

			//initialize
			inthis.assign(LG.getV(),false);

			create_Community(LG, v);
			int tempnode;
		//	int flag;
			int  runt = 2;
			//begin a round
			while(runt>=0){
		//		flag = 0;
				position = LG.getV();
			
				while(true){
				
					tempnode = get_NextNode(LG , y);
					if(tempnode == -1)break;
					if(inthis[tempnode] == true) continue;
					inthis[tempnode] = true;
		//			flag = 1;
					join_Node(LG, tempnode);
					
				}
		//		if(flag == 0) break;
				runt--;
			}
		}

	}
}