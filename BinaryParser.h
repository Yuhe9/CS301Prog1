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
	bool isFormatCorrect(){ return myFormatCorrect; };
	Instruction getNextInstruction();
	
//	void getDataFields(string line, string &Opcode, string *operand, int &num_operands);
//	int convertStringToNum(string str);

       private:
	
	vector<Instruction> myInstructions;
	int myIndex;
	int imm, rs, rt, rd, immILength, immJLength;
	int regLength;
        int stringLength; 
 
	bool myFormatCorrect;
	bool isValidBinaryEncoding(string s);//check if the line is an valid binary string
		
	RegisterTable registers;
	OpcodeTable opcodes;
	
	
//	istringstream sa;

	void decode(string s, Instruction &i, Opcode o);//check if the opcode matches with any opcode in the opcodeTable, and determine which type the opcode stands for
	void decodeRType(string s, Instruction &i, Opcode o);
	void decodeIType(string s, Instruction &i, Opcode o);
	void decodeJType(string s, Instruction &i, Opcode o);
	string createAssembly(string s, Instruction i, Opcode o);
	string createRTypeAssembly(string s, Instruction i, Opcode o); 
	string createITypeAssembly(string s, Instruction i, Opcode o);
	string createJTypeAssembly(string s, Instruction i, Opcode o);

	int convertBinToDec(string s);
	string extendBits(string s);
	int twoCompBinToDec(string s);
	//string setAssembly(Instruction i); 
	//string setAssemblyRType(i);
	//string setAssemblyIType(i);
	//string setAssemblyJType(i);

};


#endif
