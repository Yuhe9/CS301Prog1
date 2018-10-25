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
				myFormatCorrect = false;
				break;
			}//check for invalid opcode
			string asm = decode(line, i, o);
			i.setAssembly(asm);
			myInstructions.push_back(i);
		}
	}
	myIndex = 0;
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
	

	string BinaryParser::decode(string s, Instruction i, Opcode o){
	//Given a line of 32 bits binary string encoding of an instruction, and an Opcode, break and transfer the data fields into the Instruction instance dependon its instuction type.
	string myInstruction;
	InstType type = opcodes.getInstType(o);
	if(type == RTYPE)
	  myInstruction = decodeRType(s, i, o);
	else if(type == ITYPE)
	  myInstruction = decodeIType(s, i, o);
	else
	  myInstruction = decodeJType(s, i, o);
	
	return myInstruction;

	}

	string BinaryParser::decodeRType(string s, Instruction i, Opcode o){
	  int rs, rt, rd, imm;
	  int rsStartIndex = 6;
	  int rtStartIndex = 11;
	  int rdStartIndex = 16;
	  int regLength = 5;
	  int immStartIndex = 21;
	  stringstream ss;
	  isstringstream sa;
	  Opcode op = opcodes.determineOpcode(s);
	  string rsField = s.substr(rsStartIndex, regLength);
	  string rtField = s.substr(rtStartIndex, regLength);
	  string rdField = s.substr(rdStartIndex, regLength );
	  string immediate = s.substr(immStartIndex, regLength);
	  sa(immediate) >> imm;
	
	  rs = registers.getNum(rsField);
	  rt = registers.getNum(rtField);
	  rd = registers.getNum(rdField);
	  imm = convertBinToDec(imm); 
	  
	  i.setValues(op, rs, rt, rd, imm); 	
	  
	  ss << i.getOpcode() << ", $"<< i.getRD()<< ", $" << i.getRS() << ", $" << i.getRD();//get the instuc
          return ss.str(); 
	}

	string BinaryParser::decodeIType(string s,Instruction i, Opcode o){
	  int rs, rt, rd, imm =  -1;
	  int rsStartInd = 6;
	  int rtStartInd = 11;
	  int immStartInd = 16;
	  int regLength = 5;
	  int immLength = 16;
	  stringstream ss;
	  isstringstream sa;
	  Opcode op = opcodes.determineOpcode(s);
	  
	  string rsField = s.substr(rsStartIndex, regLength);
	  string rtField = s.substr(rtStartIndex, regLength);
	  string immediate = s.substr(immStartIndex, immLength);	
	  sa(immediate) >> imm;
	  
	  rs = registers.getNum(rsField);
	  rt = registers.getNum(rtField);
	  imm = convertBinToDec(imm);
	  
	  i.setValues(op, rs, rt, rd, imm);
	  ss << i.getOpcode() << ", $"<< i.getRT()<< ", " << i.getImmediate() << "(" << i.getRS() << ")";//put the I-type instruction into a string
          return ss.str();
	}

	string BinaryParser::decodeJType(string s,Instruction i, Opcode o){
	  int immStartInd = 6;
	  int immLength = 26;
          int imm = rs = rt = rd = -1;
	  stringstream ss;
	  isstringstream sa;
	  Opcode op = opcodes.determineOpcode(s);
	  
	  string immediate = s.substr(6, immLength);
	  sa(immediate) >> imm;
	  imm = imm/4;//shift the binary encoding to offset the target address 
	  imm = convertBinToDec(imm);
	  i.setValues(op, rs, rt, rd, imm);

	  ss << i.getOpcode() << " "<< hex <<i.getImmediate();//get the J-type instruction
	  return ss.str();	
	}

	int BinaryParser::convertBinToDec(int bin){
	  int dec = 0,rem, num, base = 1;
	  num = bin;
	  while (num > 0)
    	 {
            rem = num % 10;
            dec = dec + rem * base;
            base = base * 2;
            num = num / 10;
     	 }
	
	 return dec;
	}	
