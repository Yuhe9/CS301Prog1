#include "BinaryParser.h"

BinaryParser::BinaryParser(string fileName){
	Instruction i;
	myFormatCorrect = true;
	stringLength = 32;
	ifstream in;
	in.open(fileName.c_str());
	if(in.bad()){
		myFormatCorrect = false;
	}
	else{
		string line;
		while(getline(in, line)){
			if(isValidBinaryEncoding(line) == false){
				myFormatCorrect = false;
				break;
			}
				
			Opcode o = opcodes.determineOpcode(line);
			if(o == UNDEFINED){
				myformatCorrect = false;
				break;
			}//check for invalid opcode
			decode(line, i, o);
			String asm = createAssembly(i);
			i.setAssembly(asm);//TODO: write setAssembly method in instruction.cpp
			myInstructions.push_back(i);
		}
	}
	myIndex = 0;

	
	}
}
	bool BinaryParser::isValidBinaryEncoding(string s){
		if(s.length() != stringLength){
			return false;
		}

		if(s.find_first_of("01")!= string::npos){	
			return false;
		}

		return true;
	}
	

	void BinaryParser::decode(string s, Instruction &i, Opcode o){
	//Given a line of 32 bits binary string encoding of an instruction, and an Opcode, break and transfer the data fields into the Instruction instance dependon its instuction type.
	InstType type = opcodes.getInstType(o);
	if(type == RType)
	  decodeRType(s, &i, o);
	else if(type == IType)
	  decodeIType(s, &i, o);
	else
	  decodeJType(s, &i, o);
	}

	void BinaryParser::decodeRType(string s, Instruction i, Opcode o){
	  int rs, rt, rd, imm;
	  int rsStartIndex = 6;
	  int rtStartIndex = 11;
	  int rdStartIndex = 16;
	  int immStartIndex = 21;
	  int immEndIndex = 25;
	  Opcode op = opcodes.getOpcodeField(o);
	  String rsField = s.substring(rsStartIndex, rdStartIndex - 1);
	  String rtField = s.substring(rtStartIndex, rdStartIndex - 1);
	  String rdField = s.substring(rdStartIndex, immStartIndex - 1);
	  String immediate = s.substring(immStartIndex, immEndIndex);
	  rs = registers.getNum(rsField);
	  rt = registers.getNum(rtField);
	  rd = registers.getNum(rdField);
	  imm = convertBinToDec(immediate); 
	  i.setValues(op, rs, rt, rd, imm); 	

	}

	void BinaryParser::decodeIType(string s,Instruction i, Opcode o){
	  int rs, rt, rd, imm;
	  int rd = -1;
	  int rsStartInd = 6;
	  int rtStartInd = 11;
	  int immStartInd = 16;
	  Opcode op = opcodes.getOpcodeField(o);
	  String rsField = s.substring(rsStartIndex, rdStartIndex - 1);
	  String rtField = s.substring(rtStartIndex, immStartIndex - 1);
	  String immediate = s.substring(immStartIndex, stringLength - 1);	
	  rs = registers.getNum(rsField);
	  rt = registers.getNum(rtField);
	  imm = convertBinToDec(immediate);
	  i.setValues(op, rs, rt, rd, imm);

	}

	void BinaryParser::decodeJType(string s,Instruction i, Opcode o){
	  int immStartInd = 6;
          int imm = rs = rt = rd = -1;
	  Opcode op = opcodes.getOpcodeField(o);
	  string immediate = s.substring(6, stringLength - 1);
	  imm = convertBinToDec(immediate);
	  imm = imm/4;//shift the binary encoding to offset the target address 
	  i.setValues(op, rs, rt, rd, imm);

	}
	
	string BinaryParser::createAssembly(Instruction i){
	


	}

