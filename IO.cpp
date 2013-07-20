// IO.cpp: implementation of the IO class.
//
//////////////////////////////////////////////////////////////////////

#include "IO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



IO::IO (const char *fl, float ma, float mi, float inter): filename(fl), max(ma), min(mi), interval(inter),mapno(-1)
{		

}

IO::~IO()
{

}

//get the node number of the graph
void IO::GML_GetNo(struct GML_pair* list, int *pcount){
	struct GML_pair* tmp = list;
	while(tmp){
		if(!strcmp(tmp->key,"node"))
		{
			(*pcount)++;
			mapno++;
			struct GML_pair* nexttmp = tmp->value.list;
			while(nexttmp){
				if(!strcmp(nexttmp->key,"id")||!strcmp(nexttmp->key,"ID")){
					OldToNewMap.insert(make_pair(nexttmp->value.integer,mapno));
					NewToOldMap.insert(make_pair(mapno,nexttmp->value.integer));
					break;
				}
				nexttmp=nexttmp->next;
			}
		}
		else{
			switch (tmp->kind) {
			case GML_INT:
			
			   break;

			case GML_DOUBLE:
			  
			    break;

			case GML_STRING:
			    break;
	    
			case GML_LIST:
			    GML_GetNo (tmp->value.list,pcount);
			  
				break;

			default:
			    break;
			}
		}
		tmp = tmp->next;
	}
}


// store the matrix in Graph G
void IO::GML_Graph_Matrix (Graph &G,struct GML_pair* list) {
    
    struct GML_pair* tmp = list;
    

    while (tmp) {
	
	

		if(!strcmp(tmp->key,"source")&&!strcmp(tmp->next->key,"target")){
			G.insert(Edge(OldToNewMap[tmp->value.integer],OldToNewMap[tmp->next->value.integer])) ;
			
		}
		else{
			switch (tmp->kind) {
			case GML_INT:
			   
			    break;

			case GML_DOUBLE:
			    
			    break;

			case GML_STRING:
			   
			    break;
	    
			case GML_LIST:
			   
				   GML_Graph_Matrix (G, tmp->value.list);
			    break;

			default:
				break;
			}
		}
	tmp = tmp->next;
    }
}



 Graph IO::getGraphGML(){
	struct GML_pair* list;
	struct GML_stat* stat=(struct GML_stat*)malloc(sizeof(struct GML_stat));
    stat->key_list = NULL;
	FILE* file = fopen(filename,"r");
	if(file==0){printf ("\n No such file: %s", filename);exit(0);}
	else{
		GML_init();
		list = GML_parser(file, stat, 0);
		if (stat->err.err_num != GML_OK) {
		printf ("An error occured while reading line %d column %d of %s:\n", stat->err.line, stat->err.column, filename);
		
		switch (stat->err.err_num) {
		case GML_UNEXPECTED:
		    printf ("UNEXPECTED CHARACTER");
		    break;
		    
		case GML_SYNTAX:
		    printf ("SYNTAX ERROR"); 
		    break;
		    
		case GML_PREMATURE_EOF:
		    printf ("PREMATURE EOF IN STRING");
		    break;
		    
		case GML_TOO_MANY_DIGITS:
		    printf ("NUMBER WITH TOO MANY DIGITS");
		    break;
		    
		case GML_OPEN_BRACKET:
		    printf ("OPEN BRACKETS LEFT AT EOF");
		    break;
		    
		case GML_TOO_MANY_BRACKETS:
		    printf ("TOO MANY CLOSING BRACKETS");
		    break;
		
		default:
		    break;
		}
		
		printf ("\n");
		exit(0);
		}
		int* pno = (int*)malloc(sizeof(int));
		*pno=0;
		GML_GetNo(list,pno);
		Graph G(*pno);
		GML_Graph_Matrix(G,list);
		GML_free_list(list, stat->key_list);
		return G;
	}

}

void IO::IOInit(){
	//initiate the LI
	Graph &G = getGraphGML();
	LIGraph LI(G);

	//calulate the Local Influence matrix
	LI.runLI(G);

	
	//test the influence matrix
	ofstream mat("LImatrix");
	mat<<LI.getE()<<ends<<LI.getV()<<ends<<(float)(2*LI.getE())/(float)LI.getV()<<endl;
	mat<<"   ";
	int i;
	for( i=0;i<LI.getV();i++){
		mat<<setw(8)<<i+1<<"  ";
	}
	mat<<endl;
	for( i=0;i<LI.getV();i++){
		mat<<setw(4)<<i+1;
		for(int j=0; j<LI.getV();j++){
		mat<<setw(8)<<setprecision(2)<<LI.getLI(i,j)<<"  ";
		
		}
		mat<<setw(4)<<i+1;
		mat<<endl;
	
	}
	mat<<"   ";
	
	for( i=0;i<LI.getV();i++){
		mat<<setw(8)<<i+1<<"  ";
	}
	mat.close();
//end test	
	float threshold = max;
	while(threshold >= min){
		//generate the overlapping community
		NodeCom NC(LI);
		NC.run(LI,G,threshold);
		char buf[20];
		_gcvt(threshold,7,buf);
		ofstream outfile(buf);
		outfile<<setw(10)<<"Community#"<<"  "<<"Node#"<<endl;
		for(multimap <int,int>::iterator iter = NC.ComToNode.begin();iter != NC.ComToNode.end();++iter){
			outfile<<setw(10)<<iter->first<<"   "<<iter->second<<endl;
		}
		outfile.close();

		threshold -= interval;
	} 
}
