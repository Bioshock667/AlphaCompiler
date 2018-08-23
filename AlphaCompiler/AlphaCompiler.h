#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <cctype>

struct Func {
public:
	std::string name;
	int startNum;
	int numParams;
	int ParamStartAddress;
	std::vector<std::string> ins;
	int ret_address;
};
class AlphaCompiler
{
public:
	AlphaCompiler(std::istream* sourceCode, std::ostream* assemblyCode);
	~AlphaCompiler();
	int compile();
private:
	static const int REG_SIZE = 4;
	std::vector<std::string> vars;
	std::string current_vars[REG_SIZE];
	std::vector<Func> funcs;
	Func* currentFunc;
	std::string scope;
	typedef void (AlphaCompiler::*FP)();
	std::vector<std::string> asmCode;
	bool start;
	std::istream* sCode;
	std::ostream* aCode;
	std::istringstream lineBuffer;
	std::string getNextString();
	int getNextInt();
	int registerVar(std::string name);
	int deregisterVar(std::string name);
	int getRegister(std::string name);
	void registerConst(std::string name, int value);
	void assign(int from, int to);
	void addTo(int from, int to);
	void iAddTo(int val, int to);
	void subtractTo(int from, int to);
	void iSubtractTo(int val, int to);
	void instantiateFunc(std::string name, int numParams);
	void expression_reader(int to);
};

