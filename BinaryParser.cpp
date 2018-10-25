#include "BinaryParser.h"

BinaryParser::BinaryParser(string fileName){
	Instruction i;
	myFormatCorrect = true;
	
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
			
			Opcode op = getOpcode(line);
			decode(line, i, op);
			String asm = createAssembly(i);
			i.setAssembly(asm);//TODO: write setAssembly method in instruction.cpp
			myInstructions.push_back(i);
		}
	}
	myIndex = 0;

	
	}
}
	bool isValidBinaryEncoding(string s){
		if(s.length() != 32){
			return false;
		}

		if(s.find_first_of("01")!= string::npos){	
			return false;
		}

		return true;
	}


