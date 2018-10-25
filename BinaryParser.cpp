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
			string asm = decode(line, i, o);
			i.setAssembly(asm);
			myInstructions.push_back(i);
		}
	}
	myIndex = 0;

	
	}
}

	Instruction BinaryParser::getNextInstruction(){
		if(myIndex < (int)(myInstructions.size())){
    			myIndex++;
    		return myInstructions[myIndex-1];
		}

		Instruction i;
 		return i;

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
	

	string BinaryParser::decode(string s, Instruction &i, Opcode o){
	//Given a line of 32 bits binary string encoding of an instruction, and an Opcode, break and transfer the data fields into the Instruction instance dependon its instuction type.
	string myInstruction;
	InstType type = opcodes.getInstType(o);
	if(type == RType)
	  myInstruction = decodeRType(s, &i, o);
	else if(type == IType)
	  myInstruction = decodeIType(s, &i, o);
	else
	  myInstruction = decodeJType(s, &i, o);
	
	return myInstruction;

	}

	string BinaryParser::decodeRType(string s, Instruction i, Opcode o){
	  int rs, rt, rd, imm;
	  int rsStartIndex = 6;
	  int rtStartIndex = 11;
	  int rdStartIndex = 16;
	  int immStartIndex = 21;
	  int immEndIndex = 25;
	  stringstream ss;
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
	  
	  ss << i.getOpcode() << ", $"<< i.getRD()<< ", $" << i.getRS() << ", $" << i.getRD();//get the instuc
          return ss.str(); 
	}

	string BinaryParser::decodeIType(string s,Instruction i, Opcode o){
	  int rs, rt, rd, imm;
	  int rd = -1;
	  int rsStartInd = 6;
	  int rtStartInd = 11;
	  int immStartInd = 16;
	  stringstream ss;
	  Opcode op = opcodes.getOpcodeField(o);
	  
	  String rsField = s.substring(rsStartIndex, rdStartIndex - 1);
	  String rtField = s.substring(rtStartIndex, immStartIndex - 1);
	  String immediate = s.substring(immStartIndex, stringLength - 1);	
	  rs = registers.getNum(rsField);
	  rt = registers.getNum(rtField);
	  imm = convertBinToDec(immediate);
	  
	  i.setValues(op, rs, rt, rd, imm);
	  ss << i.getOpcode() << ", $"<< i.getRT()<< ", " << i.getImmediate() << "(" << i.getRS() << ")";//put the I-type instruction into a string
          return ss.str();
	}

	string BinaryParser::decodeJType(string s,Instruction i, Opcode o){
	  int immStartInd = 6;
          int imm = rs = rt = rd = -1;
	  Opcode op = opcodes.getOpcodeField(o);
	  string immediate = s.substring(6, stringLength - 1);
	  imm = convertBinToDec(immediate);
	  imm = imm/4;//shift the binary encoding to offset the target address 
	  i.setValues(op, rs, rt, rd, imm);

	  ss << i.getOpcode() << " "<< hex <<i.getImmediate();//get the J-type instruction
	  return ss.str();	
	}

	int BinaryParser::convertBinToDec(string s){
	  int bin, dec = 0,rem, num, base = 1;
	  isstringstream(s) >> bin;
	  while (num > 0)
    	 {
            rem = num % 10;
            dec = dec + rem * base;
            base = base * 2;
            num = num / 10;
     	 }
	
	 return dec;
	}	
