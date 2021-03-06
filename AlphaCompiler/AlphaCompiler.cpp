// AlphaCompiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AlphaCompiler.h"

using namespace std;

int main()
{
    return 0;
}



AlphaCompiler::AlphaCompiler(istream* sourceCode, ostream* assemblyCode)
{
	this->sCode = sourceCode;
	this->aCode = assemblyCode;
	this->currentFunc = NULL;
	for (int i = 0; i < REG_SIZE; i++)
		current_vars[i] = "";
}

std::string AlphaCompiler::getNextString()
{
	std::string word;
	lineBuffer >> word;
	if (lineBuffer.fail())
		throw std::runtime_error("Failed to read next String");
	else
		return word;
}
int AlphaCompiler::getNextInt()
{
	int i;
	lineBuffer >> i;
	if (lineBuffer.fail())
		throw std::runtime_error("Failed to read next Integer");
	else
		return i;
}
int AlphaCompiler::compile() {
	char c;
	std::string line, word;
	while (std::getline(*sCode, line)) {
		lineBuffer.str(line);
		try {
			word = getNextString();
			//if (opPointers.find(word) != opPointers.end()) {
				//(this->*opPointers[word])();
			//}
			if (word == "START")
				start = true;
			else if (word == "FSTART") {
				int NP;
				word = getNextString(); //word contains function name
				NP = getNextInt(); //number of params
				instantiateFunc(word, NP);
			}
			else if (word == "NEW") {
				word = getNextString(); //word contains variable name
				registerVar(word);
				string assignOp;
				lineBuffer >> assignOp;
				if (lineBuffer.good() && assignOp == "=") { //no exception needs to be thrown
					int to = getRegister(word);
					expression_reader(to);
				}
			}
		}
		catch (std::exception e) {
			std::cerr << e.what() << endl;
		}
	}
}
int AlphaCompiler::registerVar(std::string name)
{
	for (int i = 0; i < REG_SIZE; i++) {
		if (current_vars[i].empty()) {
			current_vars[i] == name;
			return 1;
		}
	}
	return 0;
}
int AlphaCompiler::deregisterVar(std::string name)
{
	int reg = getRegister(name);
	if (reg != -1) {
		current_vars[reg] = "";
		return 1;
	}
	return 0;
}
int AlphaCompiler::getRegister(std::string name)
{
	for (int i = 0; i < REG_SIZE; i++) {
		if (current_vars[i] == name)
			return i;
	}
	return -1;
}
void AlphaCompiler::expression_reader(int to)
{
	std::string word;
	int from, val;
	if (lineBuffer >> word) {
		if (word == "-") {
			word = getNextString();
			if (is_number(word))
			from = getRegister(word);
			if (from == -1)
				throw std::out_of_range("Error " + word + " is not declared");
		}
	}
	else {
		return
	}

	
}
AlphaCompiler::~AlphaCompiler()
{
}

void AlphaCompiler::instantiateFunc(std::string name, int numParams) {
	Func* myFunc = new Func;
	myFunc->name = name;
	myFunc->numParams = numParams;

	funcs.push_back(*myFunc);
	currentFunc = myFunc;
}