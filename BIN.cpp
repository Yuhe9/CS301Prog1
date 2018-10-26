#include "BinaryParser.h"
#include <iostream>

using namespace std;

/* This .cpp file reads in a file that parse as a command line argument.
 * If every line of the file contains a 32 bit binary string that correctly
 * represent an encoding of a string, each line would be decoded. Then the 
 * 32 bit binary string and the translated MIPS assembly instruction are printed
 * to stdout, one for each line.
 *
 */

int main(int argc, char *argv[]){
	BinaryParser *myBinParser;

	if(argc < 2){
		cerr << "Please specify a 32bit binary string file for translation." << endl;
		exit(1);
	}

	myBinParser = new BinaryParser(argv[1]);

	if(myBinParser -> isFormatCorrect() == false){
		cerr << "The input format is incorrect" << endl;
		exit(1);
	}
	
	Instruction i;
	i = myBinParser->getNextInstruction();
	while(i.getOpcode() != UNDEFINED){
		cout << i.getEncoding() << "	" << i.getAssembly() << endl;
		i = myBinParser->getNextInstruction();

	}
	
	delete myBinParser;

}
