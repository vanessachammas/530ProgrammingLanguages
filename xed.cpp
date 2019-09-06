/**************************************************************************************  
Name: Samantha Wagner and Vanessa Chammas
Username: cssc0411 and cssc0408
Project: CS530 Assignment 2
File: xed.cpp
Notes: This is out main file. This file reads in the corrects file, makes the symmap 
and litmmap, reads the lines in line by line, and depending on the line H,T,M,E, does 
the correct conversions and preocedures to print out the correct things.
***************************************************************************************/

#include "functions.h"
#include "opcode.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <cctype> //tolower
#include <algorithm>
#include <iomanip>

using namespace std;


void filecheck(string filename){			//check to see if file can actually open
	fstream testfile(filename.c_str());
	if(!(testfile.is_open())){
		exit(EXIT_FAILURE);
	}
}

int base;
bool boolbase;



int main(int argc,char *argv[]){
	functions f1;
        opcode o1;
	map<string, string> opcodetable; 				//create the opcode map with all the instruction mnemonics
	opcodetable.insert(make_pair("ADD", "18"));
        opcodetable.insert(make_pair("ADDF", "58"));
        opcodetable.insert(make_pair("ADDR", "90"));
        opcodetable.insert(make_pair("AND", "40"));
        opcodetable.insert(make_pair("CLEAR", "B4"));
        opcodetable.insert(make_pair("COMP", "28"));
        opcodetable.insert(make_pair("COMPF", "88"));
        opcodetable.insert(make_pair("COMPR", "A0"));
        opcodetable.insert(make_pair("DIV", "24"));
        opcodetable.insert(make_pair("DIVF", "64"));
        opcodetable.insert(make_pair("DIVR", "9C"));
        opcodetable.insert(make_pair("LDX", "04"));
       	opcodetable.insert(make_pair("LPS", "D0"));
        opcodetable.insert(make_pair("MUL", "20"));
        opcodetable.insert(make_pair("MULF", "60"));
        opcodetable.insert(make_pair("NORM", "C8"));
        opcodetable.insert(make_pair("OR", "44"));
        opcodetable.insert(make_pair("RD", "D8"));
        opcodetable.insert(make_pair("RMO", "AC"));
        opcodetable.insert(make_pair("RSUB", "4C"));
        opcodetable.insert(make_pair("SHIFTL", "A4"));
        opcodetable.insert(make_pair("SHIFTR", "A8"));
        opcodetable.insert(make_pair("SIO", "F0"));
        opcodetable.insert(make_pair("SSK", "E6"));
        opcodetable.insert(make_pair("STA", "0C"));
        opcodetable.insert(make_pair("STB", "78"));
        opcodetable.insert(make_pair("STCH", "54"));
        opcodetable.insert(make_pair("STF", "80"));
	opcodetable.insert(make_pair("STI", "D4"));
        opcodetable.insert(make_pair("STL", "14"));
        opcodetable.insert(make_pair("STS", "7C"));
        opcodetable.insert(make_pair("STSW", "E8"));
        opcodetable.insert(make_pair("STT", "84"));
        opcodetable.insert(make_pair("STX", "10"));
        opcodetable.insert(make_pair("SUB", "1C"));
        opcodetable.insert(make_pair("SUBF", "5C"));
        opcodetable.insert(make_pair("SUBR", "94"));
        opcodetable.insert(make_pair("SBC", "B0"));
        opcodetable.insert(make_pair("TD", "E0"));
        opcodetable.insert(make_pair("TIO", "F8"));
        opcodetable.insert(make_pair("TIX", "2C"));
        opcodetable.insert(make_pair("TIXR", "B8"));
        opcodetable.insert(make_pair("WD", "DC"));	        



	map<string, string> symmap;			// declaring strings variables vectors and flags
	map<string, string> litmap;
	vector<string> valuevecstring;
	vector<int> valuevec;
	string filecontents;		
	string symstr;
	string endadd;
	string startadds;
	bool iflag = false;		
	bool nflag = false;
	bool xflag = false;
	bool bflag = false;
	bool pflag = false;
	bool eflag = false;
	int address = 0;
	bool ltorg = false;
	bool BASE = false;
	


	if( argc >= 3){			// checking if there are more than 3 files
		cout<< ("To many files.")<<endl;
		exit(EXIT_FAILURE);
	}

	if(argc == 2){ 		// if command line has two arguments 
		string sourcefile(argv[1]);
		string filename = sourcefile;
		filename = filename.erase(sourcefile.length() - 4,4);
		ofstream sicfile((filename + ".sic").c_str());
		ofstream lisfile((filename + ".lis").c_str());
		std::size_t found = sourcefile.find(".obj"); 	// checking for obj file 
		if(found != std::string::npos){
		}else{
			exit(EXIT_FAILURE);
		}	
		symstr = sourcefile;
		symstr.replace(found,4,".sym"); 		// setting second file as sym file
		filecheck(sourcefile);
		filecheck(symstr);
		fstream objf(sourcefile.c_str());
		fstream symf(symstr.c_str());
		if(symf.is_open()){
			map<string, string>::iterator itr;
			string line;
			while(getline (symf,line)){ 		// extracting information from sym file
				if (!(line[line.length()-1] == ':' || line[line.length()-1] == '-')){ 
			       		if(line.length()!= 0){
			            		if( line.at(0) == ' '){
			                		litmap.insert(pair<string,string>(line.substr(9,5),line.substr(24,6))); 
			            		}else{
							valuevecstring.push_back(line.substr(8,6));
			                		symmap.insert(pair<string,string>(line.substr(0,line.find(" ")),line.substr(8,6)));
			            		}
			        	}
			   	 }
			}
			
		
	

		symf.close();
		}
	    
		

		if(objf.is_open()){
			while(getline(objf,filecontents)){
				if(filecontents.at(0) == 'H'){ 		// if H were in header line 
					string startlabel = filecontents.substr(1,6);
					startadds = filecontents.substr(7,6);
					endadd = filecontents.substr(13,18);
					int startadd = f1.inttohex(3,false,startadds);
					lisfile<<setfill('0')<<setw(4)<<uppercase<<hex<<address;
					lisfile<< setfill(' ')<<setw(2)<<" "; 
					lisfile<<setfill(' ')<<setw(6)<<startlabel;
					sicfile<<setfill(' ')<<setw(6)<<startlabel;
					lisfile<<setfill(' ')<<setw(2)<<" ";
					sicfile<<setfill(' ')<<setw(2)<<" ";
					lisfile<<setfill(' ')<<setw(8)<<left<<"START";
					sicfile<<setfill(' ')<<setw(8)<<left<<"START";
					lisfile<<setfill(' ')<<setw(1)<<" ";
					sicfile<<setfill(' ')<<setw(1)<<" ";
					lisfile<<setfill(' ')<<setw(6)<<left<<hex<<startadd<<endl;
					sicfile<<setfill(' ')<<setw(6)<<left<<hex<<startadd<<endl;
				}

				if(filecontents.at(0) == 'T'){			//This is the text record
					string startadd = filecontents.substr(1,6);
					string oclength = filecontents.substr(7,2);
					string objectcodes = filecontents.substr(9);
					address = f1.inttohex(3,false,startadd);		//Make the address start at the starting address
					string fullopcode;				//This is the full opcode ie: all 6 or 8 numbers					
					string tempopcode;				//this is opcode number
				    	string opcode;					//this is worded opcode
					string tempxbpe;				//Use this to check xbpe flags
					string tempdis;					//The displacement of the code
					unsigned int tempdisint;			//Int version of displacement
					int TA;						//the TArget address int version
					string instruction;			
					int tempadd;
					int temp;
					bool neg = false;
					int current = 0;
					string label;
					stringstream labelnum;
					while(current < objectcodes.length()){
						ltorg = false;				//Set LTORG and BASE printouts to false
						BASE = false;
						// Get the opcode from string and dissasemble to correct opcode
						tempopcode = objectcodes.substr(current,2);
						iflag = f1.iflagset(tempopcode);
						nflag = f1.nflagset(tempopcode);	
						tempopcode = f1.opcodefinder(tempopcode);
						//Get the binary version of flags and then set all the flags
						tempxbpe = f1.strtobinary(objectcodes.at(current+2));		
						xflag = f1.xflagset(tempxbpe);
						bflag = f1.bflagset(tempxbpe);
						pflag = f1.pflagset(tempxbpe);
						eflag = f1.eflagset(tempxbpe);
						//see if opcode is on symbol table and set to opcode
						if(o1.searchbyValueB(opcodetable,tempopcode)){						
							opcode = o1.searchbyValueS(opcodetable,tempopcode);
						}
						if(tempopcode == "4C"){  			//check if opcode is RSUB
							label = "";
							instruction="";
							fullopcode = objectcodes.substr(current,6);
							f1.printtextrecord(address,label,opcode,instruction,fullopcode,xflag,iflag,nflag,eflag,ltorg,BASE,lisfile,sicfile);
							address = address + 3;
							current += 6;
					   
						//check if opcode is format 1
						}else if(tempopcode == "C4" ||tempopcode == "C0" ||tempopcode == "F4" ||tempopcode == "C8" || tempopcode =="F0" ||tempopcode == "F8"){
							fullopcode = objectcodes.substr(current,2);
							f1.printtextrecord(address," ",opcode," ",fullopcode,false,false,false,false,false,false,lisfile,sicfile);
							address = address +1;
							current += 2;
						//check if opcode is format 2
						}else if( tempopcode == "90" || tempopcode == "B4" || tempopcode == "A0" || tempopcode == "98" || tempopcode == "AC" || tempopcode == "A4" || tempopcode == "A8" || tempopcode == "94" || tempopcode == "B0" || tempopcode == "B8"){
							fullopcode = objectcodes.substr(current,4);
							char r1 = fullopcode.at(2);
							char r2 = fullopcode.at(3);
							string R1 = f1.registers(r1);
							string R2 = f1.registers(r2);
							instruction = R1 + "," + R2;
							lisfile<< setfill('0')<<setw(4)<<right<< address;
							lisfile<< setfill(' ')<<setw(12)<<" ";
							lisfile<<setfill(' ')<<setw(7)<<left<<opcode;
							sicfile<<setfill(' ')<<setw(7)<<left<<opcode;
							lisfile<< setfill(' ')<<setw(2)<<" ";
							sicfile<< setfill(' ')<<setw(2)<<" ";
							lisfile<<setfill(' ')<<setw(8)<<left<<instruction;
							sicfile<<setfill(' ')<<setw(8)<<left<<instruction;
							lisfile<<" "<<setfill(' ')<<setw(10)<<fullopcode<<endl;
							sicfile<<" "<<setfill(' ')<<setw(10)<<fullopcode<<endl;
							address = address +2;
							current += 4;
						//check if opcode is format 4
						}else if(eflag){
                        				fullopcode = objectcodes.substr(current,8);		//get the full 8 digit opcode to print later
    							tempdis =  objectcodes.substr(current+3,5);		//get the displacement of opcode        
                            				tempdisint =f1.inttohex(4,false,tempdis);			//get the int version of that temp dislacement	
							stringstream TAS;						
                           				TAS<<setw(6)<<setfill('0')<<hex<<tempdisint;	//Put that int diplacement into string form
                            				if(o1.searchbyValueB(symmap,f1.uppercase(TAS.str()))){			//check if diplacement is a symbol
								instruction = o1.searchbyValueS(symmap,f1.uppercase(TAS.str()));
                           				}
							if(tempopcode == "68"){						//check to see if opcode is LDB so we can assign BASE
								tempdis =  objectcodes.substr(current+3,5);
								tempdisint =f1.inttohex(4,false,tempdis);
								base = tempdisint;
								BASE = true;				//BASE is now true for print out
							}
							f1.printtextrecord(address,label,opcode,instruction,fullopcode,xflag,iflag,nflag,eflag,ltorg,BASE,lisfile,sicfile);
							address = address + 4;		//increase address by 4 and current by 8
							current += 8;
							//opcode is now format 3
						}else{
							fullopcode = objectcodes.substr(current,6);		//get the fullopcode for printout
							tempdis= objectcodes.substr(current+3,3);		//get temp displacement
							if(tempdis.at(0) == 'F'){						//If displacement is negative,make it positive
								tempdis = f1.negativenum(3,tempdis);
								tempdisint = f1.inttohex(3,true,tempdis);
								neg = true;
							}else{
								tempdisint =f1.inttohex(3,false,tempdis);
								neg = false;
							}
						
							stringstream TAS;
							stringstream addstr;
							addstr<<setw(6)<<setfill('0')<<hex<<address;
							if(o1.searchbyValueB(litmap,addstr.str())){
								ltorg = true;
								TAS<< f1.uppercase(addstr.str());
								if(neg){
									if(o1.searchbyValueB(symmap,f1.uppercase(TAS.str().substr(1,6)))){						//check if symbol
										instruction = o1.searchbyValueS(symmap,f1.uppercase(TAS.str().substr(1,6)));
									}
									if(o1.searchbyValueB(litmap,TAS.str().substr(1,6))){						//check if literal
										instruction = o1.searchbyValueS(litmap,TAS.str().substr(1,6));
									}
								}else{
									if(o1.searchbyValueB(litmap,TAS.str())){						//check if literal
										instruction = o1.searchbyValueS(litmap,TAS.str());
									}
									if(o1.searchbyValueB(symmap,f1.uppercase(TAS.str()))){						//check if symbol
										instruction = o1.searchbyValueS(symmap,f1.uppercase(TAS.str()));
									}
								}
								current+=2;
                          				}else if(tempopcode == "68"){
								BASE = true;
                                				base = tempdisint;
							}else if(iflag ||nflag){
								int number;
								stringstream tempstring;
								tempstring<<hex<<tempdisint;
								instruction = tempstring.str();
							}else if(pflag){										//PC Relative
								tempadd = address + 3;		
								TA = tempdisint + tempadd;
								TAS<<setw(6)<<setfill('0')<<hex<<TA; //TA.str();
								if(neg){
									if(o1.searchbyValueB(symmap,f1.uppercase(TAS.str().substr(1,6)))){						//check if symbol
										instruction = o1.searchbyValueS(symmap,f1.uppercase(TAS.str().substr(1,6)));
									}
									if(o1.searchbyValueB(litmap,TAS.str().substr(1,6))){						//check if literal
										instruction = o1.searchbyValueS(litmap,TAS.str().substr(1,6));
									}
								}else{
									if(o1.searchbyValueB(litmap,TAS.str())){						//check if literal
										instruction = o1.searchbyValueS(litmap,TAS.str());
									}
									if(o1.searchbyValueB(symmap,f1.uppercase(TAS.str()))){						//check if symbol
										instruction = o1.searchbyValueS(symmap,f1.uppercase(TAS.str()));
									}
								}
							
							}else{												//Base Relative
                                				TA = tempdisint + base;
                                				TAS<<setw(6)<<setfill('0')<<hex<<TA;
								if(neg){
									if(o1.searchbyValueB(symmap,f1.uppercase(TAS.str().substr(1,6)))){						//check if symbol
										instruction = o1.searchbyValueS(symmap,f1.uppercase(TAS.str().substr(1,6)));
									}
									if(o1.searchbyValueB(litmap,TAS.str().substr(1,6))){						//check if literal
										instruction = o1.searchbyValueS(litmap,TAS.str().substr(1,6));
									}
								}else{
									if(o1.searchbyValueB(litmap,f1.uppercase(TAS.str()))){						//check if literal
										instruction = o1.searchbyValueS(litmap,f1.uppercase(TAS.str()));
									}
									if(o1.searchbyValueB(symmap,f1.uppercase(TAS.str()))){						//check if symbol
										instruction = o1.searchbyValueS(symmap,f1.uppercase(TAS.str()));
									}
								}
							}
							stringstream labelnum;						
							labelnum<<setw(6)<<setfill('0')<<hex<<address; //TA.str();
						
							if(o1.searchbyValueB(symmap,f1.uppercase(labelnum.str()))){
								label = o1.searchbyValueS(symmap,f1.uppercase(labelnum.str()));					
							}else{
								label = " ";
							}
							f1.printtextrecord(address,label,opcode,instruction,fullopcode,xflag,iflag,nflag,eflag,ltorg,BASE,lisfile,sicfile); // our printing line with every parameter
							if(ltorg){
								address +=4;
							}else{
								address = address +3;
							}
							current += 6;
						}
					}	
				

//Check for RESW and RESB
					vector<string> valuevectest;
					stringstream conversion;		
					int symval;
					int num;
					vector<string>::iterator s;
					string m;
					for(s = valuevecstring.begin(); s!=valuevecstring.end();++s){
						m = *s;			// putting values from symbols into vectors
						num = f1.inttohex(3,true,m);
						valuevec.push_back(num);
					}
							
					for(int i=0; i<=valuevec.size(); i++){
						int size = (int)valuevec.size();
						bool RESW = false;
						bool RESB = false;
						int firstnum;
						int secondnum;
						if(address <= valuevec[i]){				// if address is less than value of the next spot in the vector then it is resw or resb
							if((i+1)<valuevec.size()){
								firstnum = valuevec[i+1] - valuevec[i];
								if(firstnum%3==0){ 			// if divisible by 3 then its a resw
									RESW = true;
									secondnum = firstnum/3;
								}else{ 				// else it is a resb
									RESB = true;
									secondnum = firstnum /1;
								}		
								stringstream RESinstruction;						
								RESinstruction<<setw(6)<<setfill('0')<<hex<<address;	
								if(o1.searchbyValueB(symmap,f1.uppercase(RESinstruction.str()))){						//check if symbol
									label = o1.searchbyValueS(symmap,f1.uppercase(RESinstruction.str()));
								}
								if(RESW){
									lisfile<< setfill('0')<<setw(4)<<right<<hex<< address; 			// all the setfills are used for correct columns
									lisfile<< setfill(' ')<<setw(2)<<" "; 
									lisfile<<setfill(' ')<<setw(6)<<left<<"RESW";
									sicfile<<setfill(' ')<<setw(6)<<left<<"RESW";
									lisfile<<setfill(' ')<<setw(2)<<" ";
									sicfile<<setfill(' ')<<setw(2)<<" ";
									lisfile<< setfill(' ')<<setw(6)<<left<<label;
									sicfile<< setfill(' ')<<setw(6)<<left<<label;
									lisfile<< setfill(' ')<<setw(3)<<"  ";
									sicfile<< setfill(' ')<<setw(3)<<"  ";
									lisfile<<setfill(' ')<<setw(4)<<setbase(10)<<secondnum<<endl;
									sicfile<<setfill(' ')<<setw(4)<<setbase(10)<<secondnum<<endl;
									address = address + firstnum;
								}else if(RESB){
									lisfile<< setfill('0')<<setw(4)<<right<<hex<< address;
									lisfile<< setfill(' ')<<setw(2)<<" "; 
									lisfile<<setfill(' ')<<setw(7)<<left<<"RESB";
									sicfile<<setfill(' ')<<setw(7)<<left<<"RESB";
									lisfile<<setfill(' ')<<setw(1)<<" ";
									sicfile<<setfill(' ')<<setw(1)<<" ";
									lisfile<< setfill(' ')<<setw(6)<<left<<label;
									sicfile<< setfill(' ')<<setw(6)<<left<<label;
									lisfile<< setfill(' ')<<setw(3)<<"  ";
									sicfile<< setfill(' ')<<setw(3)<<"  ";
									lisfile<<setfill(' ')<<setw(8)<<left<<setbase(10)<<secondnum<<endl;
									sicfile<<setfill(' ')<<setw(8)<<left<<setbase(10)<<secondnum<<endl;
									address = address + firstnum;
								}
							}
						else if((int)valuevec.size()== i){  
							int endaddnum = f1.inttohex(3,true,endadd);
							firstnum = endaddnum - address;
							if(firstnum%3==0){
								RESW = true;
								secondnum = firstnum/3;
							}else{
								RESB = true;
								secondnum = firstnum /1;
							}
							stringstream RESinstruction;						
							RESinstruction<<setw(6)<<setfill('0')<<hex<<address;	
							if(o1.searchbyValueB(symmap,f1.uppercase(RESinstruction.str()))){						//check if symbol
								label = o1.searchbyValueS(symmap,f1.uppercase(RESinstruction.str()));
							}
							if(RESW){
								lisfile<< setfill('0')<<setw(4)<<right<<hex<< address; 			// all the setfills are used for correct columns
								lisfile<< setfill(' ')<<setw(2)<<" "; 
								lisfile<<setfill(' ')<<setw(6)<<left<<"RESW";
								sicfile<<setfill(' ')<<setw(6)<<left<<"RESW";
								lisfile<<setfill(' ')<<setw(2)<<" ";
								sicfile<<setfill(' ')<<setw(2)<<" ";
								lisfile<< setfill(' ')<<setw(6)<<left<<label;
								sicfile<< setfill(' ')<<setw(6)<<left<<label;
								lisfile<< setfill(' ')<<setw(3)<<"  ";
								sicfile<< setfill(' ')<<setw(3)<<"  ";
								lisfile<<setfill(' ')<<setw(4)<<setbase(10)<<secondnum<<endl;
								sicfile<<setfill(' ')<<setw(4)<<setbase(10)<<secondnum<<endl;
								address = address + firstnum;
							}else if(RESB){
								lisfile<< setfill('0')<<setw(4)<<right<<hex<< address;
								lisfile<< setfill(' ')<<setw(2)<<" "; 
								lisfile<<setfill(' ')<<setw(7)<<left<<"RESB";
								sicfile<<setfill(' ')<<setw(7)<<left<<"RESB";
								lisfile<<setfill(' ')<<setw(1)<<" ";
								sicfile<<setfill(' ')<<setw(1)<<" ";
								lisfile<< setfill(' ')<<setw(6)<<left<<label;
								sicfile<< setfill(' ')<<setw(6)<<left<<label;
								lisfile<< setfill(' ')<<setw(3)<<"  ";
								sicfile<< setfill(' ')<<setw(3)<<"  ";
								lisfile<<setfill(' ')<<setw(8)<<left<<setbase(10)<<secondnum<<endl;
								sicfile<<setfill(' ')<<setw(8)<<left<<setbase(10)<<secondnum<<endl;
								address = address + firstnum;
							}
						}}		
					}

				} //TEXT RECORD
				if(filecontents.at(0) == 'M'){
					int modadd;
					int modlength;
					string modaddstr = filecontents.substr(1,6);
					string modlengthstr = filecontents.substr(7,2);
				}//MOD RECORD
				if(filecontents.at(0) == 'E'){
					string endexecution = filecontents.substr(1,6);
					string endinstruct;
					if(o1.searchbyValueB(symmap,f1.uppercase(endexecution))){	//check if symbol	
						endinstruct = o1.searchbyValueS(symmap,f1.uppercase(endexecution));
					}
					lisfile<< setfill(' ')<<setw(14)<<" ";
					lisfile<< setfill(' ')<<setw(6)<<left<<"END";
					sicfile<< setfill(' ')<<setw(6)<<left<<"END";
					lisfile<< setfill(' ')<<setw(3)<<" ";
					sicfile<< setfill(' ')<<setw(2)<<" ";
					lisfile<<setfill(' ')<<setw(8)<<left<<endinstruct<<endl;
					sicfile<<setfill(' ')<<setw(8)<<left<<endinstruct<<endl;
				}//END
			}	
		}
	}
}
