/**************************************************************************************  
Name: Samantha Wagner and Vanessa Chammas
Username: cssc0411 and cssc0408
Project: CS530 Assignment 2
File: opcode.cpp
Notes: This file hold the functions to search through maps.
***************************************************************************************/
#include "opcode.h"
#include "functions.h"
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <iterator>

using namespace std;

/***************************************************************************************
Function: searchbyValueS
Notes:takes in a string and see if that string is in the map.If it is,return the key. 
I/O:
Input: A string of the value.
Output: The key that corresponds to that value. 
***************************************************************************************/
string opcode::searchbyValueS(map<string, string> &opcodetable, string val){
	map<string, string> ::iterator iter = opcodetable.begin();
		while(iter!= opcodetable.end()){			//if its not the end of the map,keep going
			if(iter -> second == val){			//if the value in the map is equal to value inputed
				return iter->first;			//return the key
			}
			iter++;
		}
}

/***************************************************************************************
Function: searchbyValueB
Notes:takes in a string	and see	if that	string is in the map.If	it is,return true.
I/O:
Input: A string of the value. 
Output: True or false based off if the key is found.
***************************************************************************************/

bool opcode::searchbyValueB(map<string, string> &opcodetable, string val){	//Same as the function above but returns a boolean
	map<string, string> ::iterator iter = opcodetable.begin();
		while(iter!= opcodetable.end()){
			if(iter -> second ==val){
				return true;	
			}
			iter++;
		}
	return false;
}

