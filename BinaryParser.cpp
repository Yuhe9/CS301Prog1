#include "BinaryParser.h"

// Sherry Yuhe Zhu
BinaryParser::BinaryParser(string fileName){
// take in a file containing a single 32 bit binary string which is the encoding of an instruction.
// checks for the format correctness and create a list of instructions
	
	Instruction i;
	myFormatCorrect = true;

	stringLength = 32;
	regLength = 5;// length of rs, rt, and rd registers
	imm = rs = rt = rd = -1;
	immILength = 16;// length of I-type immediate fields
	immJLength = 26;// length of J-type immediate fields
	
	ifstream in;
	in.open(fileName.c_str());
	if(in.bad()){
	   myFormatCorrect = false;
	}
	else{
	   string line;
	   while(getline(in, line)){
	      if(isValidBinaryEncoding(line) == false){
	      // check if the line only contain 32 bits characters of only 0 and 1s.
	         myFormatCorrect = false;
		 break;
	      }
	      
	      //determine what is the opcode given the string of binary encoding of the instruction
	      Opcode o = opcodes.determineOpcode(line);
	      if(o == UNDEFINED){
	      // specify invalid opcode
	         myFormatCorrect = false;
		 break;
	      }
	     
	      // set the data fields of the binary string encodings into the instruction	
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
	// Iterator that returns the next Instruction in the list of Instructions
	   if(myIndex < (int)(myInstructions.size())){
    	      myIndex++;
    	      return myInstructions[myIndex-1];
	   }

	   Instruction i;
           return i;

	}

	bool BinaryParser::isValidBinaryEncoding(string s){
	// given the line of strings, check if it is valid
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
	// given a line of 32 bits binary string encoding of an instruction, the instruction, and the Opcode, 
	// break and store the data fields into the Instruction instance depends on its instuction type.
	   InstType type = opcodes.getInstType(o);
	   
	   if(type == RTYPE)
	     decodeRType(s, i, o);
	   else if(type == ITYPE)
	     decodeIType(s, i, o);
	   else
	     decodeJType(s, i, o);

	}

	string BinaryParser::createAssembly(string s, Instruction i, Opcode o){	
	// given a line of 32 bits binary string encoding of an instruction, the instruction, and Opcode,
	// return the corresponding assembly version of an instruction
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
	// given a line of 32 bits binary string encoding of an R-type instruction, the instruction, 
	// and Opcode, break and store the data fields into the Instruction instance  
	   string rsField = s.substr(regLength + 1, regLength);//rs field start at the index of 6 in the string
	   string rtField = s.substr(2*regLength + 1, regLength);//rf field start at the index of 11 in the string

 	   string rdField = s.substr(3*regLength + 1, regLength );//rd field start at the index of 16 in the string

	   string immediate = s.substr(4*regLength + 1, regLength);//immediate field start at the index of 21 in the string
	   
	   //convert the string representing rs,rt, rd, and imm field to decimal integer
	   rs = convertBinToDec(rsField);
	   rt = convertBinToDec(rtField);
	   rd = convertBinToDec(rdField);
	   imm = convertBinToDec(immediate); 
	 
	   i.setValues(o, rs, rt, rd, imm); 	
	  
	}

	void BinaryParser::decodeIType(string s,Instruction &i, Opcode o){
	// given a line of 32 bits binary string encoding of an I-type instruction, the instruction, a
	// nd Opcode, break and store the data fields into the Instruction instance
	   
  	   // get the string representing rs,rt, rd, and imm fields in the string
	   string rsField = s.substr(regLength + 1, regLength);
	   string rtField = s.substr(2*regLength + 1, regLength);
	   string immediate = s.substr(3*regLength + 1, immILength);	
 	  
	   //convert the string representing rs,rt, rd, and imm field to decimal integer
	   rs = convertBinToDec(rsField);
	   rt = convertBinToDec(rtField);
	   // extend the 16 bits immediate to 32 bits and encoded to decimal integer in two’s complement
	   immediate = extendBits(immediate);
	   imm = twoCompBinToDec(immediate);
	 
	   i.setValues(o, rs, rt, rd, imm);

	}

	void BinaryParser::decodeJType(string s,Instruction &i, Opcode o){
	// given a line of 32 bits binary string encoding of an J-type instruction, the instruction, a 
	// nd Opcode, break and store the data fields into the Instruction instance 
	
	   // get the string representing rs,rt, rd, and imm fields in the string
	   string immediate = s.substr(regLength + 1, immJLength);
	   imm = convertBinToDec(immediate);
	   imm = imm * 4; //offset to get the target label address 
	
	   i.setValues(o, rs, rt, rd, imm);
	}

	string BinaryParser::createRTypeAssembly(string s, Instruction i, Opcode o){
	// given a line of 32 bits binary string encoding of an R-typeinstruction, the instruction, and Opcode
	// return the corresponding assembly version of the instruction
	  
	   stringstream ss;
	   string name = opcodes.getName(o);
	   ss << name;
	
	   // check how many registers the instruction has and make the corresponding assembly representation
	   if(opcodes.numOperands(o) == 1)// if it is mflo
	      ss <<"	$" << i.getRD();
	   else if (opcodes.numOperands(o) == 2)// if it is mult
	      ss << "	$" << i.getRS() << ", $" << i.getRT();
	   else if (opcodes.IMMposition(o) != -1) // if it is sll
	      ss << "	$" << i.getRD() << ", $" << i.getRT() << ", " << i.getImmediate();
	   else	// for other R-type instructions
	      ss << "	$" << i.getRD() << ", $" << i.getRS() << ", $" << i.getRT(); 

           
	   return ss.str();

	} 
	

	string BinaryParser::createITypeAssembly(string s, Instruction i, Opcode o){
	// given a line of 32 bits binary string encoding of an I-typeinstruction, the instruction, and Opcode	      // return the corresponding assembly version of an instruction
	  
	   stringstream ss;
           string name = opcodes.getName(o);
	   ss << name;	

	   // check if the instruction is lb or beq, constructe the corresponding assembly representation for the two special cases
	   if(opcodes.IMMposition(o) == 1)// check if it is lb	
	      ss << "	$" << i.getRT() <<", "<< i.getImmediate() << "($"<< i.getRS() << ")";//get the string of lb instuction
	   else if (opcodes.RSposition(o) == 0){// check if it is beq 
	      ss << "	$" << i.getRS() << ", $" << i.getRT() << ", 0x";

	      // check if rs field equals to rt field to make the offset corresepondly
	      if(i.getRS() == i.getRT())
	         ss << hex << i.getImmediate()*2; //get the immediate, which is an address, in hex base
	      else
	         ss << hex << i.getImmediate()*4;

	   }else

	      ss <<"	$" << i.getRT()<< ", $" << i.getRS() << ", " << i.getImmediate();
 
          return ss.str();

	}


	string BinaryParser::createJTypeAssembly(string s, Instruction i, Opcode o){
	// given a line of 32 bits binary string encoding of an I-typeinstruction, the instruction, and Opcode
	// return the corresponding assembly version of an instruction
	   
	   stringstream ss;
           string name = opcodes.getName(o);
 	 
	   ss << name << "	" << "0x" << hex << i.getImmediate(); //get the J-type assembly instruction
          
 	   return ss.str();

	}


	int BinaryParser::convertBinToDec(string s){
	// given an string representing a data field, return the correseponding decimal integer
	   
	   int val = 0;
	   int indexCounter = 0;

	   // convert the binary string using the formula
	   for(int i = s.length()-1;i>=0;i--){
	       if(s[i]=='1'){ // if the binary string has a 1 at the position then add 2 to the power of its index
       	          val += pow(2, indexCounter);
    	       }
    	       indexCounter++;
	   }

	   return val;
	}	

 	string BinaryParser::extendBits(string s){
	// given a string of 16 bits, extend it to 32 bits using two’s complement by adding 1 before negative
	// or 0 before positive
	
	   string str;
	   string ones = "1111111111111111";// string of 16 1s that will be added before the binary string in two's complement
	   string zeros = "0000000000000000";//string of 16 0s that will be added before the binary string in two's complement
	  
	   if(s[0] == '1')//the sign bit is 1 suggesting the binary string represents a negative number
	      str.append(ones);
	   else // the binary string represents a positive number
	     str.append(zeros);

	   str.append(s);//append the origin string
	
	   return str;
	}

	int BinaryParser::twoCompBinToDec(string s){
	// given a binary string in two’s complement, return its decimal value
          
	   int val = 0;
           int indexCounter = 0;
	  
	   // check the sign bit
	   if(s[0] == '1')
	      val = pow(-2, 31);

	   // convert the string using two’s complement formula
           for(int i = s.length() - 1;i>0;i--){
              if(s[i]=='1'){
                 val += pow(2, indexCounter);
              }
              indexCounter++;
          }

           return val;
        }

