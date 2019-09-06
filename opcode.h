/**************************************************************************************  
Name: Samantha Wagner and Vanessa Chammas
Username: cssc0411 and cssc0408
Project: CS530 Assignment 2
File: opcode.h
Notes: This file holds allt he function declarations for opcode.cpp
***************************************************************************************/

#ifndef OPCODE_H
#define OPCODE_H

#include <map>
#include <string>

using namespace std;
class opcode{				//creates an opcode class that holds all our function definitions

	public:
		string searchbyValueS(map<string, string> &opcodetable, string val);
		bool searchbyValueB(map<string, string> &opcodetable, string val);
};


#endif
