

#include <iostream>
#include <ctime>
#include "IO.h"
using namespace std;


void main(){
	cout<<"Enter the filename:"<<endl;
	char filename[30];
	cin>>filename;
//	cout<<"Enter the max threshold, min threshold and interval:"<<endl;
	float max,min,interval;
	cin>>max>>min>>interval;
	//Timer
	clock_t start,finish;
	double totaltime;
	start=clock();


   	IO Myio(filename,max,min,interval);
	Myio.IOInit();
	cout<<"Generate result in files "<<endl;

   //end time
   finish=clock();
   totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
   cout<<"RunTime:"<<totaltime<<"seconds"<<endl;

}