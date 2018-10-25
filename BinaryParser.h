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
 *
 */

class BinaryParser{
       public:
	
	BinaryParser(string fileName);
	bool isFormatCorrect{ return myFormatCorrect; };
	Instruction getNextInstruction;
	
//	void getDataFields(string line, string &Opcode, string *operand, int &num_operands);
//	int convertStringToNum(string str);

       private:
	
	vector<Instruction> myInstructions;
	int myIndex;
	int stringLength;
	bool myFormatCorrect;
	bool isValidBinaryEncoding(string s);//check if the line is an valid binary string
	RegisterTable registers;
	OpcodeTable opcodes;
	
	void decode(string line, Instruction i, Opcode o);//check if the opcode matches with any opcode in the opcodeTable, and determine which type the opcode stands for
	void decodeRType(Instruction i);
	void decodeIType(Instruction i);
	void decodeJType(Instruction i);
	int convertBinToDec(string s);
	string createAssembly(Instruction i); 


}


#endif
