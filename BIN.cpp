#include "BINParser.h"
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
	BINParser *myBinParser;

	if(argv < 2){
		cerr << "Please specify a 32bit binary string file for translation." << endl;
		exit(1);
	}

	myBinParser = new BINParser(argv[1]);

	if(myBinParser -> isFormatCorrect() == false){
		cerr << "The input format is incorrect" << endl;
		exit(1);
	}
	
	String str;
	Instruction i;
	//TODO: figure out how to use instruction.cpp to iterate the file
	str = myBinParser->getNextLine();
	while(str != UNDEFIND){
		cout << str;
		cout <<i.getDecoding;
		//



	}
	
	delete myBinParser;

	return 0;
}
