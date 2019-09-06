Samantha Wagner and Vanessa Chammas
cssc0411 and cssc0408
CS 530, Spring 2019
Assignment 2, XE Disassembler
README.md

xed.cpp functions.cpp functions.h opcode.cpp opcode.h Makefile

To compile: You can type make or you can do g++ xed.cpp functions.cpp opcode.cpp -o xed. This will compile the file and to run it, ./xed [filename].obj 

To compile using Makefile: Type make then type xed (filename).obj then to clean type make clean, this will clean every .o file .sic file and .lis file. 

A significant design decision we made was design decision was the use of maps to store our information and then call on the map to find the information we stored by key and value. Another design decision we made was to create a separate file for our functions to keep our main file shorter and easier to read. 

We used boolean flags to set our xbpe, and ni bits. If the bit was set we set the flag as true, this was helpful throughout the dissassembler because it kept things organized and running smoothly. 

Our sample2.obj worked on our computer but not on edoras.

A key lesson we learned was hardcoding, if we are sure register 0 is equivalent to A then creating a function and hardcoding this makes complex topics easier to understand. We also learned alot about planning our time wisely and coding in smaller sections to ensure the smaller parts are working properly before we attack the larger whole. 
