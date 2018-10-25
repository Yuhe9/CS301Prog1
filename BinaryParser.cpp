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
	  int rtStartIndex = 10;
	  int rdStartIndex = 15;
	  int immStartIndex = 20;
	  int immEndIndex = 24;
	  Opcode op = opcodes.getOpcodeField(o);
	  String rsField = s.substring(rsStartIndex, rdStartIndex - 1);
	  String rtField = s.substring(rtStartIndex, rdStartIndex - 1);
	  String rdField = s.substring(rdStartIndex, immStartIndex - 1);
	  String immediate = s.substring(immStartIndex, immEndIndex);
	  rs = convertBinToDec(rsField);
	  rt = convertBinToDec(rtField);
	  rd = convertBinToDec(rdField);
	  imm = convertBinToDec(immediate); 
	  i.setValues(op, rs, rt, rd, imm); 	

	}

	void BinaryParser::decodeIType(string s,Instruction i, Opcode o){
	


	}

	}


}

