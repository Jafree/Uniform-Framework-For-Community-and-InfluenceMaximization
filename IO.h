// IO.h: interface for the IO class.
//
//////////////////////////////////////////////////////////////////////

#ifndef IO_H
#define IO_H

#include "gml_parser.h"
#include "NodeCom.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <iomanip>
#include <map>
using namespace std;
class IO  
{
public:
	IO(const char *filename, float max, float min, float interval);
	virtual ~IO();
	//Get the node number and new old node map
	void GML_GetNo(struct GML_pair* list, int *pcount);
	//Set the matrix
	void GML_Graph_Matrix (Graph &G,struct GML_pair* list);

	//get the Total Graph Interface
	Graph getGraphGML();

	//Initiate the process and give the result in file
	void IOInit();
private:
	const char *filename;
	float max;
	float min;
	float interval;

	//The map of node index
	map<int,int> NewToOldMap;   //used to draw the graphs based on the original info
	
	map<int, int> OldToNewMap;
	//The current node number that has been searched
	int mapno;

};

#endif 