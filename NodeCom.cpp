// NodeCom.cpp: implementation of the NodeCom class.
//
//////////////////////////////////////////////////////////////////////

#include "NodeCom.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


NodeCom::NodeCom(const LIGraph &LG): cno(-1),position(-1), ComNodeadj(LG.getV(),0.0F),inflag(LG.getV(),0),InfluencePair(LG.getV())
	,waited(LG.getV()),waitedend(0),inthis(LG.getV(),false)
			
{	
	
	for(int i=0;i<LG.getV();i++){
		InfluencePair[i].node = i;
		InfluencePair[i].influence = LG.getTotalInfluence(i) ;
		//cout<<LG.getTotalInfluence(i)<<endl;
	}
	// sort based on the influence
	sort(InfluencePair.begin(), InfluencePair.end());
	double sum=0;
	for(int i=0;i<LG.getV();i++){
		cout<<setw(6)<<InfluencePair[i].node<<ends<<InfluencePair[i].influence<<ends<<LG.Influenced[i]<<endl;
		sum+=InfluencePair[i].influence;
	}
	cout<<"×ÜÊý"<<sum<<endl;

}

NodeCom::~NodeCom()
{

}


void NodeCom::create_Community(const LIGraph &LG, const Graph &G, int c){
	//set the functioning community and set restart
	cno = c;
	inthis[c]=true;
	position=-1;
	//set the flag which denotes that the node is in a community
	inflag[cno]++;

	for(int i=0;i<LG.getV();i++){
		ComNodeadj[i] = LG.getLI(i,cno);
	}
	waitedend=0;
	adjIterator iter(G,c);
	for(int i=iter.bbeg();iter.end()!=true;i=iter.next ()){
		waited[waitedend].node=i;
		waited[waitedend++].influence=LG.getTotalInfluence(i);

		inthis[i]=true;
		for(int j=0;j<LG.getV();j++){
			ComNodeadj[j]+=LG.getLI(j,i);
		}
	}
	sort(waited.begin(),waited.begin()+waitedend);
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
	++position;
	for(; position<LG.getV();position++){
		if((ComNodeadj[position] >= y)&&(position!=cno)&&(inflag[position]==0))return position;
	}
	return -1;
}

void NodeCom::run(const LIGraph &LG, const Graph &G,float y){
	//traverse all the node until all node join in at least one community
	     

	for(int i=0;i< LG.getV();i++){
		//v is the max influence node
		int v = InfluencePair[i].node;
		
		if(inflag[v]==0){

			//initialize
			inthis.assign(LG.getV(),false);
			create_Community(LG, G,v);			
			int flag;
			//begin a round
			flag = 0;					
			for(int j=0;j<waitedend;j++){
				int temp=waited[j].node;
				if(ComNodeadj[temp]>=y){
					ComToNode.insert(make_pair(cno, temp));
					inflag[temp]++;
					inthis[temp]=true;
					flag = 1;
				}
				else {
					for(int k=0;k<LG.getV();k++){
						ComNodeadj[k]-=LG.getLI(k,temp);
					}
						
				}
			}//endfor
				waitedend = 0;
				if(flag == 0)continue;
				int tempnode;
			while(true){
				flag = 0;
				position = -1;
				while(true){
				
					tempnode = get_NextNode(LG , y);
					if(tempnode == -1)break;
					inthis[tempnode] = true;
					flag = 1;
					join_Node(LG, tempnode);
				}
				if(flag == 0) break;
			}
			//Last round to join in the overlapping nodes
			float isolated= static_cast<float>(y * VARIABLE_LASTROUND);
			position = -1;
			while(true){
					tempnode = LG.getV();

					++position;
					for(; position<LG.getV();position++){
						//if the node already have community membership.
						if((ComNodeadj[position] >= y)&&(position!=cno)&&(inflag[position]!=0)&&(inthis[position]==false)){
							tempnode = position;
							break;
						}
						//if the node is the isolated node.
						else if((ComNodeadj[position] >= isolated)&&(position!=cno)&&(inflag[position]==0)){
							tempnode = position;
							break;
						}
					}
					if(tempnode == LG.getV())break;
					inthis[tempnode] = true;

					//Not add the influence of overlapping nodes
					//set flag
					inflag[tempnode]++;
	
					//join the community
					ComToNode.insert(make_pair(cno, tempnode));
			}
			

		/*		//Update the waitedqueue
				
				for(int j=0;j<insertedend;j++){
					adjIterator tempiter(G,inserted[j]);
					for(int k=tempiter.bbeg();tempiter.end()!=true;k=tempiter.next()){
						if(inthis[k]==false){
							waited[waitedend].node=k;
							waited[waitedend++].influence=LG.getTotalInfluence(k);
							inthis[k]=true;
							//Add the influence to the community influence
							
						}
					}//endfor
				}//endfor
				insertedend=0;

				//The influence of the neighbor of uninserted node is not considered. 
				for(int j=0;j<uninsertedend;j++){
					waited[waitedend].node=uninserted[j];
					waited[waitedend++].influence=LG.getTotalInfluence(uninserted[j]);
					//Add the influence of uninserted node,again
					
				}
				uninsertedend=0;
				sort(waited.begin(),waited.begin()+waitedend);
			

			while(true){
				flag = 0;					
				for(int j=0;j<waitedend;j++){
					int temp=waited[j].node;
					if(ComNodeadj[temp]>=y){
						join_Node(LG,temp);
						//Add the influence to the influence vector of the community
						for(int k=0;k<LG.getV();k++){
							ComNodeadj[k]+=LG.getLI(k,temp);
						}
						flag = 1;
					}
					else {
						uninserted[uninsertedend++]=temp;
						
					}
				}//endfor
				waitedend = 0;
				if(flag == 0) {
					insertedend=0;
					uninsertedend=0;
					break;
				}
				//Update the waitedqueue
				
				for(int j=0;j<insertedend;j++){
					adjIterator tempiter(G,inserted[j]);
					for(int k=tempiter.bbeg();tempiter.end()!=true;k=tempiter.next()){
						if(inthis[k]==false){
							waited[waitedend].node=k;
							waited[waitedend++].influence=LG.getTotalInfluence(k);
							inthis[k]=true;
							
						}
					}//endfor
				}//endfor
				insertedend=0;

				//The influence of the neighbor of uninserted node is not considered. 
				for(int j=0;j<uninsertedend;j++){
					waited[waitedend].node=uninserted[j];
					waited[waitedend++].influence=LG.getTotalInfluence(uninserted[j]);
					//Add the influence of uninserted node,again
				}
				uninsertedend=0;
				sort(waited.begin(),waited.begin()+waitedend);
				
			}//endwhile
			*/

		}//endif

	}//endfor
}