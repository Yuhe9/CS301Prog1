#include "OpcodeTable.h"

// Sherry Yuhe Zhu
OpcodeTable::OpcodeTable()
// Initializes all the fields for every instruction in Opcode enum
{
  myArray[ADD].name = "add";  myArray[ADD].numOps = 3;   myArray[ADD].rdPos = 0;  myArray[ADD].rsPos = 1;  myArray[ADD].rtPos = 2;   myArray[ADD].immPos = -1;  myArray[ADD].instType = RTYPE; myArray[ADD].op_field = "000000"; myArray[ADD].funct_field = "100000";


  //addi
  myArray[ADDI].name = "addi";
  myArray[ADDI].numOps = 3;
  myArray[ADDI].rdPos = -1;
  myArray[ADDI].rsPos = 1;
  myArray[ADDI].rtPos = 0;
  myArray[ADDI].immPos = 2;
  myArray[ADDI].instType = ITYPE;
  myArray[ADDI].op_field = "001000";
  myArray[ADDI].funct_field = "";

  //xor
  myArray[XOR].name = "xor";
  myArray[XOR].numOps = 3;
  myArray[XOR].rdPos = 0;
  myArray[XOR].rsPos = 1;
  myArray[XOR].rtPos = 2;
  myArray[XOR].immPos = -1;
  myArray[XOR].instType = RTYPE;
  myArray[XOR].op_field = "000000";
  myArray[XOR].funct_field = "100110";

  //mult
  myArray[MULT].name = "mult";
  myArray[MULT].numOps = 2;
  myArray[MULT].rdPos = -1;
  myArray[MULT].rsPos = 0;
  myArray[MULT].rtPos = 1;
  myArray[MULT].immPos = -1;
  myArray[MULT].instType = RTYPE;
  myArray[MULT].op_field = "000000";
  myArray[MULT].funct_field = "011000";

  //mflo
  myArray[MFLO].name = "mflo";
  myArray[MFLO].numOps = 1;
  myArray[MFLO].rdPos = 0;
  myArray[MFLO].rsPos = -1;
  myArray[MFLO].rtPos = -1;
  myArray[MFLO].immPos = -1;
  myArray[MFLO].instType = RTYPE;
  myArray[MFLO].op_field = "000000";
  myArray[MFLO].funct_field = "010010";

  //sll
  myArray[SLL].name = "sll";
  myArray[SLL].numOps = 3;
  myArray[SLL].rdPos = 0;
  myArray[SLL].rsPos = -1;
  myArray[SLL].rtPos = 1;
  myArray[SLL].immPos = 2;
  myArray[SLL].instType = RTYPE;
  myArray[SLL].op_field = "000000";
  myArray[SLL].funct_field = "000000";

  //slt
  myArray[SLT].name = "slt";
  myArray[SLT].numOps = 3;
  myArray[SLT].rdPos = 0;
  myArray[SLT].rsPos = 1;
  myArray[SLT].rtPos = 2;
  myArray[SLT].immPos = -1;
  myArray[SLT].instType = RTYPE;
  myArray[SLT].op_field = "000000";
  myArray[SLT].funct_field = "101010";

  //slti
  myArray[SLTI].name = "slti";
  myArray[SLTI].numOps = 3;
  myArray[SLTI].rdPos = -1;
  myArray[SLTI].rsPos = 1;
  myArray[SLTI].rtPos = 0;
  myArray[SLTI].immPos = 2;
  myArray[SLTI].instType = ITYPE;
  myArray[SLTI].op_field = "001010";
  myArray[SLTI].funct_field = "";

  //LB
  myArray[LB].name = "lb";
  myArray[LB].numOps = 3;
  myArray[LB].rdPos = -1;
  myArray[LB].rsPos = 2;
  myArray[LB].rtPos = 0;
  myArray[LB].immPos = 1;
  myArray[LB].instType = ITYPE;
  myArray[LB].op_field = "100000";
  myArray[LB].funct_field = "";
  
  //BEQ
  myArray[BEQ].name = "beq";
  myArray[BEQ].numOps = 3;
  myArray[BEQ].rdPos = -1;
  myArray[BEQ].rsPos = 0;
  myArray[BEQ].rtPos = 1;
  myArray[BEQ].immPos = 2;
  myArray[BEQ].instType = ITYPE;
  myArray[BEQ].op_field = "000100";
  myArray[BEQ].funct_field = "";

  //J
  myArray[J].name = "j";
  myArray[J].numOps = 1;
  myArray[J].rdPos = -1;
  myArray[J].rsPos = -1;
  myArray[J].rtPos = -1;
  myArray[J].immPos = 0;
  myArray[J].immLabel = true;
  myArray[J].instType = JTYPE;
  myArray[J].op_field = "000010";
  myArray[J].funct_field = "";

}

Opcode OpcodeTable::getOpcode(string str)
// Given a valid MIPS assembly mnemonic, returns an Opcode which represents a
// template for that instruction.
{
  for(int i = 0; i < (int)UNDEFINED; i++){
    if(myArray[i].name == str){
      return (Opcode)i;
    }
  }
  return UNDEFINED;
}

Opcode OpcodeTable::determineOpcode(string str){
// Given a 32-bits binary string encoding of an instruction, returns an Opcode
// which reprsents a template for that instruction.
  
  string opField = str.substr(0, regLength);
  string funcField = str.substr(4*regLength + 2, regLength);
  
  for(int i = 0; i < (int)UNDEFINED; i++){
    if(myArray[i].op_field == opField && opField != "000000"){
      return (Opcode)i;

     } else if (myArray[i].op_field == opField && myArray[i].funct_field == funcField){
        return (Opcode)i;
       }
    }
  return UNDEFINED;

}

string OpcodeTable::getName(Opcode o){
//Given an opcode, returns a string representing the instruction's name
  string name = myArray[o].name;
  return name;
}


int OpcodeTable::numOperands(Opcode o)
// Given an Opcode, returns number of expected operands.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].numOps;
}


int OpcodeTable::RSposition(Opcode o)
// Given an Opcode, returns the position of RS field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rsPos;
}

int OpcodeTable::RTposition(Opcode o)
// Given an Opcode, returns the position of RT field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rtPos;
}

int OpcodeTable::RDposition(Opcode o)
// Given an Opcode, returns the position of RD field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rdPos;
}

int OpcodeTable::IMMposition(Opcode o)
// Given an Opcode, returns the position of IMM field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].immPos;
}

InstType OpcodeTable::getInstType(Opcode o)
// Given an Opcode, returns instruction type.
{
  if(o < 0 || o > UNDEFINED)
    return (InstType)-1;
  return myArray[o].instType;
}

string OpcodeTable::getOpcodeField(Opcode o)
// Given an Opcode, returns a string representing the binary encoding of the opcode
// field.
{
  if(o < 0 || o > UNDEFINED)
    return string("");
  return myArray[o].op_field;
}

string OpcodeTable::getFunctField(Opcode o)
// Given an Opcode, returns a string representing the binary encoding of the function
// field.
{
  if(o < 0 || o > UNDEFINED)
    return string("");
  return myArray[o].funct_field;
}

bool OpcodeTable::isIMMLabel(Opcode o)
// Given an Opcode, returns true if instruction expects a label in the instruction.
// See "J".
{
  if(o < 0 || o > UNDEFINED)
    return false;
  return myArray[o].immLabel;
}
