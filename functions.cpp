/**************************************************************************************  
Name: Samantha Wagner and Vanessa Chammas
Username: cssc0411 and cssc0408
Project: CS530 Assignment 2
File: functions.cpp
Notes: This file holds all the functions we use in our main.
***************************************************************************************/
#include "functions.h"
#include "opcode.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>
#include <cctype> //tolower
#include <algorithm>
#include <cmath> //exponent

opcode o2;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***************************************************************************************
Function: opcodefinder
Notes: This function groups the ni flags together by hardcoding the opcode endings by either 0,4,8, or C. 
I/O:
Input: A string of the opcode.
Output: Replaces the position to corresponding value, the dissassembled opcode. 
***************************************************************************************/

string functions::opcodefinder(string temp){
	if (temp.at(1) == '2' || temp.at(1) == '1' || (temp.at(1) == '3')){ 	// if 2, 1, or 3 willl become 0 
		temp.at(1) = '0';
	}					
	if (temp.at(1) == '4' || temp.at(1) == '5' || temp.at(1) == '6' || temp.at(1) == '7'){ 	// if 4,5,6, or 7  will become 4
		temp.at(1) = '4';
		
	}
	if (temp.at(1) == '8' || temp.at(1) == '9' || temp.at(1) == 'A' || temp.at(1) == 'B'){	// if 8,9,A, or B will become 8
		temp.at(1) = '8';
		
	}
	if (temp.at(1) == 'C' || temp.at(1) == 'D' || temp.at(1) == 'E' || temp.at(1) == 'F'){	// if C, D , E , or F will become C
		temp.at(1) = 'C';
		
	}
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***************************************************************************************
Function: nflagset, iflagset, inflagset
Notes: These next three functions are doing the same action. This function groups opcodes by n,i, or both and sets them to true.
I/O:
Input: The second position of the opcode string.
Output: Returns true.
***************************************************************************************/


bool functions::nflagset(string example){
    if (example.at(1) == '2' || example.at(1) == '6' || example.at(1) == 'A' || example.at(1) == 'E'){
        //this is n flag
		return true;
    }
	return false;
}

bool functions::iflagset(string example){
    if (example.at(1) == '1' || example.at(1) == '5' || example.at(1) == '9' || example.at(1) == 'D'){
    	//this is i flag 
		return true;
    }
	return false;
}

bool functions::inflagsset(string example){
    if (example.at(1) == '3' ||example.at(1) == '7' || example.at(1) == 'B' || example.at(1) == 'F') {
    	//this is both n and i flag 
		return true;
    }
	return false;
}

/***************************************************************************************
Function: xflagset, bflagset, pflagset, eflagset
Notes: The next four functions are doing the same action. This function takes the groups opcodes by the x,b,p,e flags and sets them to true. 
I/O:
Input: The thrid position of the opcode string.
Output: Returns true. 
***************************************************************************************/

bool functions::xflagset(string binaryxbpe){
    if( binaryxbpe.at(0) == '1'){ 		// if at position 0 is equal to 1 return true 
		return true;
    }
	return false;
}
bool functions::bflagset(string binaryxbpe){
    if( binaryxbpe.at(1) == '1'){		// if at position 1 is equal to 1 return true
		return true;
    }
	return false;
}
bool functions::pflagset(string binaryxbpe){
    if( binaryxbpe.at(2) == '1'){		// if at position 2 is equal to 1 return true 
		return true;
    }
	return false;
}
bool functions::eflagset(string binaryxbpe){
    if( binaryxbpe.at(3) == '1'){		// if at position 3 is equal to 1 return true
		return true;
    }
	return false;
}

/***************************************************************************************
Function: strtobinary
Notes: This function takes a hexadecimal number and returns the binary equivalent. 
I/O:
Input: A hexadecimal string. 
Output: The binary equivalent of the hexadecimal as a string. 
***************************************************************************************/


string functions::strtobinary(char A){		// 0 - F returns corresponding binary value
	if(A == '0'){return "0000";}
	if(A == '1'){return "0001";}
	if(A == '2'){return "0010";}
	if(A == '3'){return "0011";}
	if(A == '4'){return "0100";}
	if(A == '5'){return "0101";}
	if(A == '6'){return "0110";}
	if(A == '7'){return "0111";}
	if(A == '8'){return "1000";}
	if(A == '9'){return "1001";}
	if(A == 'A'){return "1010";}
	if(A == 'B'){return "1011";}
	if(A == 'C'){return "1100";}
	if(A == 'D'){return "1101";}
	if(A == 'E'){return "1110";}
	if(A == 'F'){return "1111";}				
}

/***************************************************************************************
Function: stringtoint
Notes: This function takes in a string and returns a integar. 
I/O:
Input: A string. 
Output: The equivalent of the string but in integar form.
***************************************************************************************/


int functions::stringtoint(char A){		// 0 - F returns corresponding hex 
	if(A == '0'){return 0;}
	if(A == '1'){return 1;}
	if(A == '2'){return 2;}
	if(A == '3'){return 3;}
	if(A == '4'){return 4;}
	if(A == '5'){return 5;}
	if(A == '6'){return 6;}
	if(A == '7'){return 7;}
	if(A == '8'){return 8;}
	if(A == '9'){return 9;}
	if(A == 'A'){return 10;}
	if(A == 'B'){return 11;}
	if(A == 'C'){return 12;}
	if(A == 'D'){return 13;}
	if(A == 'E'){return 14;}
	if(A == 'F'){return 15;}				
}

/***************************************************************************************
Function: inttohex
Notes: Takes an integar and makes it an hexadecimal integar. 
I/O:
Input: Takes in an integar. 
Output: Outputs an hexadecimal integar. 
***************************************************************************************/
int functions::inttohex(int format,bool neg, string str){
	char temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
	int temp1int,temp2int,temp3int,temp4int,temp5int,temp6int, temp7int, temp8int, number;
	temp1 = str.at(0);		// assigns temp values for specific positions of the string
	temp2 = str.at(1);
	temp3 = str.at(2);
	
	temp1int = stringtoint(temp1);		//  applies stringtoint function to our new temp value
	temp2int = stringtoint(temp2);
	temp3int = stringtoint(temp3);

    if (format == 3){					//should now be 6 in length to add all the F for the negative
		if(neg){
        	temp4 = str.at(3);
	    	temp5 = str.at(4);
			temp6 = str.at(5);	
			temp4int = stringtoint(temp4);
			temp5int = stringtoint(temp5);	
			temp6int = stringtoint(temp6); 	
			number = (temp1int * pow(16,5)) + (temp2int * pow(16,4)) + (temp3int * pow(16,3)) + (temp4int * pow(16,2)) + (temp5int * 16) + temp6int; // conversion to hexadecimal 
		}else{			
	    		number = (temp1int * pow(16,2)) + (temp2int * 16) + temp3int;		//calculates hex number
		}
    }
    if (format == 4){			//does the same but now for format 4 which has a total displacement of 5
        temp4 = str.at(3);
	temp5 = str.at(4);

        temp4int = stringtoint(temp4);
	temp5int = stringtoint(temp5);
        number = (temp1int * pow(16,4)) + (temp2int * pow(16,3)) + (temp3int * pow(16,2)) +(temp4int * 16) + temp5int;
	   
    }

	return number;
}

/***************************************************************************************
Function: uppercase
Notes: Takes in userinput string and returns uppercase string. 
I/O:
Input: Takes in string.
Output: Outputs the string in uppercase. 
***************************************************************************************/

string functions::uppercase(string userinput){
	for(string::iterator k = userinput.begin();k < userinput.end();k++){        //makes so its not case sensitive
			*k = toupper(*k);
	}
	return userinput;
}

/***************************************************************************************
Function: negativenum
Notes: Takes in the hex int and inserts F's when needed.
I/O:
Input: Takes in a hexadecimal integar. 
Output: Outputs an hexadecimal integar with corresponding F's to resemble the negative hex. 
***************************************************************************************/

string functions::negativenum(int format,string str){

	if(format ==3){
		while(str.length()<6){
			str.insert(0,"F");		// insert F's to make the string a negative hex
		}
	}
	if (format ==4){
		while(str.length()<8){
			str.insert(0,"F");		// insert F's again for format 4
		}
	}	
	return str;
}

/***************************************************************************************
Function: printtextrecord
Notes: Takes in all the parameters needed to print the text record and prints with proper spacing and columns.  
I/O:
Input: Takes in all parameters needed for printing. 
Output: Returns nothing, only prints out the text record. 
***************************************************************************************/

void functions::printtextrecord(int address,string label,string opcode,string instruction,string fullopcode,bool xflag,bool iflag,bool nflag,bool eflag,bool ltorg,bool base,ofstream& lisfile,ofstream& sicfile){
	lisfile<< setfill('0')<<setw(4)<<right<< address;    ///uppercase here
	lisfile<< setfill(' ')<<setw(2)<<" "; 
	lisfile<< setfill(' ')<<setw(6)<<left<<label;
	lisfile<< setfill(' ')<<setw(2)<<" ";
	sicfile<< setfill(' ')<<setw(6)<<left<<label;
	sicfile<< setfill(' ')<<setw(2)<<" ";
	if(eflag){					// set fills and setw for proper columns and spacing
		lisfile<<"+"<<setfill(' ')<<setw(6)<<left<<opcode;
		sicfile<<"+"<<setfill(' ')<<setw(6)<<left<<opcode;
	}else{
		lisfile<<setfill(' ')<<setw(7)<<opcode;
		sicfile<<setfill(' ')<<setw(7)<<opcode;
	}
	lisfile<<setfill(' ')<<setw(2)<<" ";
	sicfile<<setfill(' ')<<setw(2)<<" ";
	if(iflag){					// if i flag its immediate addressing, hence the #
		lisfile<<"#";
		lisfile<<setfill(' ')<<setw(7)<<left<<instruction;
		sicfile<<"#";
		sicfile<<setfill(' ')<<setw(7)<<left<<instruction;
	}else if(nflag){
		lisfile<<"@";				// if nflag its indirect addressing, hence the @
		sicfile<<"@";
		lisfile<<setfill(' ')<<setw(7)<<left<<instruction;
		sicfile<<setfill(' ')<<setw(7)<<left<<instruction;
	}else{
		if(ltorg){
			lisfile<<"="<<setfill(' ')<<setw(8)<<left<<instruction;
			sicfile<<"="<<setfill(' ')<<setw(8)<<left<<instruction;
		}else if (xflag){
			instruction = instruction + ",X";		// if xflag we print ,X
			lisfile<<setfill(' ')<<setw(8)<<left<<instruction;
			sicfile<<setfill(' ')<<setw(8)<<left<<instruction;
		}else{
			lisfile<<setfill(' ')<<setw(8)<<left<<instruction;
			sicfile<<setfill(' ')<<setw(8)<<left<<instruction;
		}
	}
	sicfile<<endl;
	lisfile<<" "<<setfill(' ')<<setw(8)<<left<<fullopcode<<endl;
	if(ltorg){								//if we have to print LTORG

		sicfile<< setfill(' ')<<setw(8)<<" "; 
		sicfile<<setfill(' ')<<setw(6)<<label;
		sicfile<<setfill(' ')<<setw(3)<<" ";
		sicfile<<setfill(' ')<<setw(7)<<left<<"LTORG"<<endl;	

		lisfile<< setfill(' ')<<setw(6)<<" "; 
		lisfile<<setfill(' ')<<setw(6)<<label;
		lisfile<<setfill(' ')<<setw(2)<<" ";
		lisfile<<setfill(' ')<<setw(7)<<left<<"LTORG"<<endl;
	}
		if(base){							//if we have to print BASE
		lisfile<< setfill('0')<<setw(4)<<right<< address;
		lisfile<< setfill(' ')<<setw(4)<<" "; 
		lisfile<<setfill(' ')<<setw(6)<<label;
		//lisfile<<setfill(' ')<<setw(2)<<" ";
		lisfile<<setfill(' ')<<setw(7)<<left<<"BASE";
		lisfile<<setfill(' ')<<setw(2)<<" ";
		lisfile<<setfill(' ')<<setw(24)<<left<<instruction<<endl;

		sicfile<<setfill(' ')<<setw(6)<<label;
		sicfile<<setfill(' ')<<setw(2)<<" ";
		sicfile<<setfill(' ')<<setw(7)<<left<<"BASE";
		sicfile<<setfill(' ')<<setw(2)<<" ";
		sicfile<<setfill(' ')<<setw(24)<<left<<instruction<<endl;

}


}

/***************************************************************************************
Function: registers
Notes: Takes register number and returns corresponding letter. 
I/O:
Input: Takes in a integar. 
Output: Outputs the corrsponding register letter. 
***************************************************************************************/

string functions::registers(char R){			// Takes in number returns corresponding register value
	if(R=='0'){return "A";}
	if(R=='1'){return "X";}
	if(R=='2'){return "L";}
	if(R=='3'){return "B";}
	if(R=='4'){return "S";}
	if(R=='5'){return "T";}
	if(R=='6'){return "F";}
}
