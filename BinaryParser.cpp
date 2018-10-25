#include "BinaryParser.h"

BinaryParser::BinaryParser(string fileName){
	Instruction i;
	myFormatCorrect = true;
	int stringLength = 32;
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
	  decodeRType(&i);
	else if(type == IType)
	  decodeIType(&i);
	else
	  decodeJType(&i);
	}

	void BinaryParser::decodeRType(Instruction i){
	  int rs, rt, rd, imm;
	

	


	}



	}


}

