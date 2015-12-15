
#ifndef LOG_H
#define LOG_H
#include <iostream>

using namespace std;

class log {
public:
	//Constructors
	log();
	log(int f, int c, int m, int t);
	//tests for a match between sent and received
	bool match_opposite(log comp);
	//overloaded output operator
	friend ostream & operator<< (ostream &out, const log &a);

	int first;
	int count;
	int mid;
	int tag;
	bool hit;

};

#endif