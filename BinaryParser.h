#ifndef __BINARYPARSER_H__
#define __BINARYPARSER_H__

using namespace std;

#include <iostream>
#include <fstream>
#include "Instruction.h"
#include "RegisterTable.h"
#include "OpcodeTable.h"
#include <string>
#include <cstddef>
#include <math.h>
#include <vector>
#include <sstream>
#include <stdlib.h>

/* This file reads in a binary string encoding of a MIPS instruction. First it will check the syntax,
 * if the syntax is correct, it will create an insruction for each line of the file. It will iterate the file and read in every line.
 */

class BinaryParser{
       public:
	// Specify a file contains strings of 32-bits binary encoding of instructions. Check the syntax
	// correctness and create a list of instructions.
	BinaryParser(string fileName);
	
	// Return true if the format of the file is correct; false otherwise
	bool isFormatCorrect(){ return myFormatCorrect; };

	// Iterator that returns the next Instruction in the list
	Instruction getNextInstruction();
	

       private:
	
	vector<Instruction> myInstructions;// the list of instructions
	int myIndex; // iterator index
	int imm, rs, rt, rd, immILength, immJLength;//registers and length of data fields
	int regLength; // length of rs, rt, rd and R-type immediate registers
        unsigned int stringLength; //length of the string
 
	bool myFormatCorrect;
	bool isValidBinaryEncoding(string s);//check if the line is an valid binary string
		
	RegisterTable registers;//encodings for registers
	OpcodeTable opcodes;//encodings of opcodes
	
	
	//given a line of 32 bits binary string encoding of an instruction, the address of instruction, 
	//and Opcode, break and store the data fields into an Instruction instance 
	void decode(string s, Instruction &i, Opcode o);

	//given a line of 32 bits binary string encoding of an R-type instruction, the address ofinstruction, 
	//and Opcode, break and store the data fields of a R-type instruction into an Instruction instance
	void decodeRType(string s, Instruction &i, Opcode o);

	//given a line of 32 bits binary string encoding of an I-type instruction,the address of instruction, 
	//and Opcode, break and store the data fields of a I-type instruction into an Instruction instance
	void decodeIType(string s, Instruction &i, Opcode o);

	//given a line of 32 bits binary string encoding of an J-type instruction,the addredd of instruction, 
	//and Opcode, break and store the data fields of a J-type instruction into an Instruction instance
	void decodeJType(string s, Instruction &i, Opcode o);

	// given a line of 32 bits binary string encoding of an instruction, the instruction, and Opcode
	// return the corresponding assembly version of an instruction depends on its type
	string createAssembly(string s, Instruction i, Opcode o);

	// given a line of 32 bits binary string encoding of an R-type instruction, the instruction, and 
	// Opcode, return the corresponding assembly version of an I-type instruction
	string createRTypeAssembly(string s, Instruction i, Opcode o);

	// given a line of 32 bits binary string encoding of an I-type instruction, the instruction, and 
	// Opcode, return the corresponding assembly version of the I-type instruction
	string createITypeAssembly(string s, Instruction i, Opcode o);
	
	// given a line of 32 bits binary string encoding of an J-type instruction, the instruction, and 
	// Opcode, return the corresponding assembly version of the J-type instruction
	string createJTypeAssembly(string s, Instruction i, Opcode o);

	// convert string o binary to decimal
	int convertBinToDec(string s);

	// extend the string to 32-bits string in two's complement way
	string extendBits(string s); 
	
	//convert a two's complement binary string to decimal
	int twoCompBinToDec(string s);

};


#endif
