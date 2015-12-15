#include "log.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//function headers
void source_parse(string s, int &a, int &b, int &c, int &d);
void dest_parse(string s, int &a, int &b, int &c, int &d);

int main() {

	//create vectors with class objects
	vector<log> sent;
	vector<log> received;

	//read in text file of log output
	ifstream infile("mpe_log_with_errors.txt");

	//initialize string for text input and counts
	string line;
	int countS = 0;
	int countR = 0;


	//while no new lines read in one line at a time
	while (getline(infile, line)) {

		//only 7 processes so remove first 4 chars for comp
		string hold = line.substr(4,23);

		//if an appropriate receiving line continue
		if(hold.compare("Starting MPI_Irecv with") == 0) {
			int a,b,c,d;
			//parse string for integer values
			source_parse(line, a, b, c, d);
			//create new log instance and push into vector, increment count
			log *p = new log(a, b, c, d);
			received.push_back(*p);
			countR++;
		}
		//similar to above
		if(hold.compare("Starting MPI_Isend with") == 0) {
			int a,b,c,d;
			dest_parse(line, a, b, c, d);
			log *p = new log(a, b, c, d);
			sent.push_back(*p);
			countS++;
		}
	}

	//iterate through sent and count
	for(int i=0; i<countS; i++) {
		for(int k=0; k<countR; k++) {
			//check for match, hit will allow uniqueness
			if(sent[i].match_opposite(received[k]) && !received[k].hit) {
				received[k].hit = true;
				sent[i].hit = true;
				//if a new match found, leave loop, do not keep setting
				//other matches to true
				break;
			}
		}
	}
	
	//output vector counts for sent and received
	cout<<"\nNumber Sent: " << countS<<endl;
	cout<<"Number Received: "<< countR<<endl<<endl;

	//find and output all sent items with no match
	for(int i=0; i<countS; i++) {
		if(sent[i].hit == false) {
			cout << "Process sent with no match received: " <<sent[i];
		}
	}
	cout<<endl;
	//find and output all received items with no match
	for(int k=0; k<countR; k++) {
		if(received[k].hit == false) {
			cout << "Process received with no match sent: " <<received[k];
		}
	}
	cout<<endl;

}

//parsing if "source" in string
void source_parse(string s, int &a, int &b, int &c, int &d) {
	//get first number
	a = stoi(s.substr(1,1));

	//create substring and extract second number
	string hold1 = s.substr(36, s.length()-36);
	b = stoi(hold1.substr(0,1));

	//create another substring and get third number
	string hold2 = hold1.substr(12, hold1.length()-12);
	string::size_type ccc = hold1.find(',');
	c = stoi(hold2.substr(0,ccc));

	//fourth num varys in length, search for = and . on either side of 
	//current substring and slice appropriately
	string::size_type dd = hold2.find('=');
	string::size_type ddd = hold2.find('.');
	d = stoi(hold2.substr(dd+2, ddd-dd-3));

}

//parsing if "dest" in string
void dest_parse(string s, int &a, int &b, int &c, int &d) {
	a = stoi(s.substr(1,1));

	string hold1 = s.substr(36, s.length()-36);
	b = stoi(hold1.substr(0,1));

	string hold2 = hold1.substr(10, hold1.length()-10);
	string::size_type ccc = hold1.find(',');
	c = stoi(hold2.substr(0,ccc));

	string::size_type dd = hold2.find('=');
	string::size_type ddd = hold2.find('.');
	d = stoi(hold2.substr(dd+2, ddd-dd-3));

}