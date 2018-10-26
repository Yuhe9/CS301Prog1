#include "BinaryParser.h"

BinaryParser::BinaryParser(string fileName){
	Instruction i;
	myFormatCorrect = true;
	stringLength = 32;
	regLength = 5;
	imm = rs = rt = rd = -1;
	immILength = 16;
	immJLength = 26;

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
			decode(line, i, o);
			string assembly = createAssembly(line, i, o);
			i.setEncoding(line);
			i.setAssembly(assembly);
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
		// check if the string has 32 bits
			return false;
		}

		if(s.find_first_of("01") == string::npos){
		// check if the string contain any other character than 0 and 1	
			return false;
		}

		return true;
	}
	

	void BinaryParser::decode(string s, Instruction &i, Opcode o){
	//Given a line of 32 bits binary string encoding of an instruction, and an Opcode, break and transfer the data fields into the Instruction instance dependon its instuction type.
	InstType type = opcodes.getInstType(o);
	if(type == RTYPE)
	  decodeRType(s, i, o);
	else if(type == ITYPE)
	  decodeIType(s, i, o);
	else
	  decodeJType(s, i, o);
	

	}

	string BinaryParser::createAssembly(string s, Instruction i, Opcode o){	
	  string myInstruction;
	  InstType type = opcodes.getInstType(o);
          if(type == RTYPE) 
	    myInstruction = createRTypeAssembly(s, i, o);
	  else if (type == ITYPE)
	    myInstruction = createITypeAssembly(s, i, o);
	  else
	    myInstruction = createJTypeAssembly(s, i, o);

	  return myInstruction;
	}

	void BinaryParser::decodeRType(string s, Instruction &i, Opcode o){
	  Opcode op = opcodes.determineOpcode(s);
	  string rsField = s.substr(regLength + 1, regLength);
	  string rtField = s.substr(2*regLength + 1, regLength);
 	  string rdField = s.substr(3*regLength + 1, regLength );
	  string immediate = s.substr(4*regLength + 1, regLength);
	
	  rs = convertBinToDec(rsField);
	  rt = convertBinToDec(rtField);
	  rd = convertBinToDec(rdField);
	  imm = convertBinToDec(immediate); 
	 
	  i.setValues(op, rs, rt, rd, imm); 	
	  
	}

	void BinaryParser::decodeIType(string s,Instruction &i, Opcode o){
	  
	  Opcode op = opcodes.determineOpcode(s);
	  string rsField = s.substr(regLength + 1, regLength);
	  string rtField = s.substr(2*regLength + 1, regLength);
	  string immediate = s.substr(3*regLength + 1, immILength);	
 	  
	  rs = convertBinToDec(rsField);
	  rt = convertBinToDec(rtField);
	  immediate = extendBits(immediate);
	  imm = twoCompBinToDec(immediate);
	 
	  i.setValues(op, rs, rt, rd, imm);

	}

	void BinaryParser::decodeJType(string s,Instruction &i, Opcode o){
	 
	  Opcode op = opcodes.determineOpcode(s);
	  string immediate = s.substr(regLength + 1, immJLength);
	  imm = convertBinToDec(immediate);
	  imm = imm * 4; //offset to get the target address 
	
	  i.setValues(op, rs, rt, rd, imm);
	}

	string BinaryParser::createRTypeAssembly(string s, Instruction i, Opcode o){
	  stringstream ss;
	  string name = opcodes.getName(o);
	  ss << name;
	
	  if(i.getRD() != 0)
	    ss << "	$"<< i.getRD();
	    
            if(i.getRS() != 0 && i.getRD() != 0)
	      ss << ", $" << i.getRS();
 	    else if(i.getRS() != 0 && i.getRD() == 0)
	      ss << "	$" << i.getRS();

	    if(i.getRT() != 0)
	      ss << ", $" << i.getRT();

	    if(i.getImmediate() != 0)
              ss << ", " << i.getImmediate();
          return ss.str();

	} 
	

	string BinaryParser::createITypeAssembly(string s, Instruction i, Opcode o){
	  stringstream ss;
          string name = opcodes.getName(o);
	  ss << name;

	  if(name == "lb")	
	    ss << "	$"<< i.getRT() <<", "<< i.getImmediate() << "($"<< i.getRS() << ")";//get the string of lb instuction
	  else if (name == "beq"){
	    ss << "	$" << i.getRS() << ", $"<< i.getRT() <<", 0x";
	    if(i.getRS() == i.getRT())
	      ss << hex << i.getImmediate()*2;
	    else
	      ss << hex << i.getImmediate()*4;
	  }
	  else
	   ss <<"	$"<< i.getRT()<< ", $" << i.getRS() << ", " << i.getImmediate();
 
          return ss.str();

	}


	string BinaryParser::createJTypeAssembly(string s, Instruction i, Opcode o){
	  stringstream ss;
          string name = opcodes.getName(o);
 	 
	  ss << name << "	" << "0x" << hex << i.getImmediate(); //get the J-type assembly instruction
          return ss.str();

	}



	int BinaryParser::convertBinToDec(string s){
	  int val = 0;
	  int indexCounter = 0;
	  for(int i = s.length()-1;i>=0;i--){
	    if(s[i]=='1'){
       	       val += pow(2, indexCounter);
    	    }
    	    indexCounter++;
	  }
	  return val;
	}	

 	string BinaryParser::extendBits(string s){
	  string str;
	  string ones = "1111111111111111";
	  string zeros = "0000000000000000";
	  if(s[0] == '1')
	  str.append(ones);
	  else
	  str.append(zeros);

	  str.append(s);
	
	  return str;
	}

	int BinaryParser::twoCompBinToDec(string s){
          int val = 0;
          int indexCounter = 0;
	  if(s[0] == '1')
	    val = pow(-2, 31);
	  
          for(int i = s.length() - 1;i>0;i--){
            if(s[i]=='1'){
               val += pow(2, indexCounter);
            }
            indexCounter++;
          }

          return val;
        }

