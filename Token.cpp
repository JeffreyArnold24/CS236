#include "Token.h"
using namespace std;

void Token::setType(string recievedType) {
	type = recievedType;
}

void Token::setValue(string value) {
	tokenName = value;
}

void Token::setLine(int line) {
	lineNumber = line;
}

string Token::getType() {
	return type;
}

string Token::getValue() {
	return tokenName;
}

string Token::getLine() {
	string str = to_string(lineNumber);
	return str;
}