/**************************************************************************************  
Name: Samantha Wagner and Vanessa Chammas
Username: cssc0411 and cssc0408
Project: CS530 Assignment 2
File: functions.h
Notes: This file holds all the functions we use in our main.
***************************************************************************************/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <map>
#include <string>
using namespace std;
class functions{
	
	public:							//Declaring function definitions for the file functions.cpp
		string opcodefinder(string temp);
		bool nflagset(string example);
		bool iflagset(string example);
		bool inflagsset(string example);
		bool xflagset(string binaryxbpe);
		bool bflagset(string binaryxbpe);
		bool pflagset(string binaryxbpe);
		bool eflagset(string binaryxbpe);
		string strtobinary(char A);
		int stringtoint(char A);
		int inttohex(int format,bool neg, string str);
		string uppercase(string userinput);
		string negativenum(int format,string str);
		void printtextrecord(int address,string label,string opcode,string instruction,string fullopcode,bool xflag,bool iflag,bool nflag,bool eflag,bool ltorg,bool base,ofstream& lisfile,ofstream& sicfile);
		string registers(char R);
		
};
#endif
