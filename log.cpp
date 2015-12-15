
#include "log.h"
#include <iostream>

using namespace std;

//Default constructor
log::log() {
	first=0;
	count=0;
	mid=0;
	tag=0;
	hit=false;
}

//Special constructor
log::log(int f, int c, int m, int t) {
	first = f;
	count = c;
	mid = m;
	tag = t;
	hit = false;
}

bool log::match_opposite(log comp) {
	if (first == comp.mid && 
		count == comp.count &&
		mid == comp.first &&
		tag == comp.tag) {

		return true;
	}
	else {
		return false;
	}
}


ostream & operator<< (ostream &out, const log &a) {
	out<< "([";
	out<< a.first;
	out<< "], count: ";
	out<< a.count;
	out<< ", dest/source: ";
	out<< a.mid;
	out<< ", tag: ";
	out<< a.tag;
	out<< ")"<<endl;

	return out;
}
