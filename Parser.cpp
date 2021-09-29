#include "Parser.h"
#include <string>
#include <fstream>
using namespace std;



bool Parser::Parse(string file){

	
	myfile.open(file);
	bool alreadySchemed = false;
	closeFile = false;
	currentLetter = myfile.get();
	while (isspace(currentLetter)) {
		currentLetter = myfile.get();
	}
	while (!closeFile) {
		if (currentLetter == '#') {
			while (currentLetter != '\n') {
				currentLetter = myfile.get();
			}
			line = newLine(line);
			currentLetter = myfile.get();
		}
		if (currentLetter == '\n') {
			currentLetter = myfile.get();
			line = newLine(line);
		}
		if (isspace(currentLetter)) {
			currentLetter = myfile.get();
		}
		if (isalpha(currentLetter) && (!alreadySchemed)) {
			while (currentLetter != ':') {
				checkToken += currentLetter;
				currentLetter = myfile.get();
			}
			checkToken += currentLetter;
			line = newLine(line);
		}
		if (checkToken == "Schemes:") {
			if (!checkSchemes()) {
				allCorrect = false;
			}
			currentLetter = myfile.get();
			alreadySchemed = true;

		}
		if (checkToken == "Facts:") {
			if (!checkFacts()) {
				allCorrect = false;
			}											//todo
		}
		if (checkToken == "Rules:") {
			if (!checkRules()) {
				allCorrect = false;
			}												//todo
		}
		if (checkToken == "Queries:") {
			if (!checkQueries()) {
				allCorrect = false;
			}												//todo
		}
	}
	return allCorrect;

}

bool Parser::checkSchemes() {
	string str = "";
	string ID = "";
	while (currentLetter != '(') {
		if (currentLetter == ')') {
			myfile.close();
			closeFile = true;
			return false;
		}
		if (currentLetter == '#') {
			while (currentLetter != '\n') {
				currentLetter = myfile.get();
			}
			line = newLine(line);
		}
		if ((currentLetter != '\n') && (!isspace(currentLetter)) && (currentLetter != '(') && (currentLetter != ':')) {
			str += currentLetter;
		}
		if (str == "Facts") {
			if (!oneItem) {
				myfile.close();
				closeFile = true;
				errorMessage("FACTS", "Facts", line);
				return false;
			}
			line = newLine(line);
			checkToken = str + ':';
			return true;
		}
		if (str == "Rules") {
			myfile.close();
			closeFile = true;
			errorMessage("RULES", "Rules", line);
			return false;
		}
		if (str == "Queries") {
			myfile.close();
			closeFile = true;
			errorMessage("QUERIES", "Queries", line);
			return false;
		}
		currentLetter = myfile.get();
	}
	currentLetter = myfile.get();
	while (currentLetter != ')') {
	
		if (currentLetter == '#') {
			while (currentLetter != '\n') {
				currentLetter = myfile.get();
			}
			line = newLine(line);
		}
		if (currentLetter == '\'') {
			ID = "\'";
			currentLetter = myfile.get();
			while (currentLetter != '\'') {
				ID += currentLetter;
				currentLetter = myfile.get();
			}
			ID += currentLetter;
			errorMessage("STRING", ID, line);
			myfile.close();
			closeFile = true;
			return false;
		}
		else {
			currentLetter = myfile.get();
			ID += currentLetter;
		}
	}
	if (ID == "") {
		myfile.close();
		closeFile = true;
		line = newLine(line);
		errorMessage("RIGHT_PAREN", ")", line);
		return false;
	}
	if (currentLetter == '\n') {
		currentLetter = myfile.get();
		line = newLine(line);
	}
	
	oneItem = true;
	return true;
}

bool Parser::checkFacts() {
	string str = "";
	if (currentLetter == ':') {
		currentLetter = myfile.get();
	}
	while (currentLetter != '(') {
		if (currentLetter == ')') {
			myfile.close();
			closeFile = true;
			return false;
		}
		if (currentLetter == '#') {
			while (currentLetter != '\n') {
				currentLetter = myfile.get();
			}
			line = newLine(line);
		}
		if ((currentLetter != '\n') && (!isspace(currentLetter)) && (currentLetter != ':')) {
			str += currentLetter;
		}
		if (str == "Rules") {
			checkToken = str + ':';
			currentLetter = myfile.get();
			line = newLine(line);
			return true;
		}
		if (str == "Queries") {
			myfile.close();
			closeFile = true;
			errorMessage("QUERIES", "Queries", line);
			return false;
		}
		currentLetter = myfile.get();
	}
	currentLetter = myfile.get();
	while (currentLetter != ')') {
		if (currentLetter == '(') {
			myfile.close();
			closeFile = true;
			errorMessage("RULES", "Rules", line);
			return false;
		}
		if (currentLetter == '#') {
			while (currentLetter != '\n') {
				currentLetter = myfile.get();
			}
		}
		currentLetter = myfile.get();
	}
	currentLetter = myfile.get();
	if (currentLetter != '.') {
		myfile.close();
		closeFile = true;
		errorMessage("Period", ".", line);
		return false;
	}
	currentLetter = myfile.get();
	if (currentLetter == '\n') {
		currentLetter = myfile.get();
		line = newLine(line);
	}

	return true;
}

bool Parser::checkRules () {
	string str = "";
	
	while (currentLetter != '(') {
		if (currentLetter == ')') {
			myfile.close();
			closeFile = true;
			return false;
		}
		if (currentLetter == '#') {
			while (currentLetter != '\n') {
				currentLetter = myfile.get();
			}
			line = newLine(line);
		}
		if ((currentLetter != '\n') && (!isspace(currentLetter)) && (currentLetter != ':')) {
			str += currentLetter;
		}
		if (str == "Queries") {
			checkToken = str + ':';
			currentLetter = myfile.get();
			line = newLine(line);
			return true;
		}
		currentLetter = myfile.get();
	}
	currentLetter = myfile.get();
	while (currentLetter != ')') {
		if (currentLetter == '(') {
			myfile.close();
			closeFile = true;
			return false;
		}
		if (currentLetter == '#') {
			while (currentLetter != '\n') {
				currentLetter = myfile.get();
			}
			line = newLine(line);
		}
		currentLetter = myfile.get();
	}
	while (currentLetter != ':') {
		if (currentLetter == '\n') {
			myfile.close();
			closeFile = true;
			return false;
		}
		currentLetter = myfile.get();
	}
	
	if (currentLetter != ':' ) {
		myfile.close();
		closeFile = true;
		return false;
	}
	currentLetter = myfile.get();
	if (currentLetter != '-') {
		myfile.close();
		closeFile = true;
		return false;
	}
	currentLetter = myfile.get();
	do {
		while (currentLetter != '(') {
			if (currentLetter == ')') {
				myfile.close();
				closeFile = true;
				return false;
			}
			if (currentLetter == '#') {
				while (currentLetter != '\n') {
					currentLetter = myfile.get();
				}
				line = newLine(line);
			}
			currentLetter = myfile.get();
		}
		currentLetter = myfile.get();
		while (currentLetter != ')') {
			if (currentLetter == '(') {
				myfile.close();
				closeFile = true;
				return false;
			}
			if (currentLetter == '#') {
				while (currentLetter != '\n') {
					currentLetter = myfile.get();
				}
				line = newLine(line);
			}
			currentLetter = myfile.get();
		}
		currentLetter = myfile.get();
		
	} while (currentLetter == ',');
	if (currentLetter != '.') {
		myfile.close();
		closeFile = true;
		return false;
	}
	currentLetter = myfile.get();
	if (currentLetter == '\n') {
		line = newLine(line);
		currentLetter = myfile.get();
	}

	return true;
}

bool Parser::checkQueries() {
	currentLetter = myfile.get();
	if (myfile.peek() == EOF) {
		myfile.close();
		return true;
	}

	while (currentLetter != '(') {
		if (currentLetter == ')') {
			myfile.close();
			closeFile = true;
			return false;
		}
		if (currentLetter == '#') {
			while (currentLetter != '\n') {
				currentLetter = myfile.get();
			}

			if (myfile.peek() == EOF) {
				myfile.close();
				closeFile = true;
				return true;
			}
			line = newLine(line);
		}
		currentLetter = myfile.get();
	}
	currentLetter = myfile.get();
	while (currentLetter != ')') {
		if (currentLetter == '(') {
			myfile.close();
			closeFile = true;
			return false;
		}
		if (currentLetter == '#') {
			while (currentLetter != '\n') {
				currentLetter = myfile.get();
			}
			line = newLine(line);
		}
		currentLetter = myfile.get();
	}
	currentLetter = myfile.get();
	if (currentLetter == '\n') {
		currentLetter = myfile.get();
		line = newLine(line);
	}
	if (currentLetter != '?') {
		myfile.close();
		closeFile = true;
		errorMessage("PERIOD", ".", line);
		return false;
	}
	currentLetter = myfile.get();
	if (currentLetter == '\n') {
		line = newLine(line);
		currentLetter = myfile.get();
	}
	if (myfile.peek() == EOF) {
		myfile.close();
		closeFile = true;
		return true;
	}

	return true;
}

int Parser::newLine(int lineNumber) {
	lineNumber++;
	return lineNumber;
}

void Parser::errorMessage(string type, string ID, int whichLine) {
	string p = to_string(whichLine);
	error = "(" + type + ",\"" + ID + "\"," + p + ")";
}

string Parser::printError() {
	return error;
}

void Parser::readInput(string file) {
	myfile.open(file);
	string whichSection = "";
	currentLetter = myfile.get();
	while (whichSection != "Schemes:") {
		if (currentLetter == '#') {
			comment();
		}
		else {
			if (currentLetter == '\n') {
				currentLetter = myfile.get();
			}
			else {
				if (isalpha(currentLetter)) {
					while (currentLetter != ':') {
						if (!isspace(currentLetter)) {
							whichSection += currentLetter;
						}
						currentLetter = myfile.get();
					}
					whichSection += ':';
				}
				currentLetter = myfile.get();
			}
		}
	}
	while (isspace(currentLetter) || (currentLetter == '\n')) {
		currentLetter = myfile.get();
	}
	while (whichSection != "Facts:") {
		Tokens = "";
		whichSection = "";
		while (isspace(currentLetter)) {
			currentLetter = myfile.get();
		}
		if (currentLetter == '#') {
			comment();
		}
		else {
			while ((currentLetter != ')') && (currentLetter != ':')) {
				if (!isspace(currentLetter)) {
					whichSection += currentLetter;
					Tokens += currentLetter;
				}
				
				currentLetter = myfile.get();
			}
			whichSection += currentLetter;
			Tokens += currentLetter;
			currentLetter = myfile.get();
			if (whichSection != "Facts:") {
				Schemes.push_back(Tokens);
			}
		}
	}

	while (whichSection != "Rules:") {
		whichSection = "";
		Tokens = "";
		while (isspace(currentLetter)) {
			currentLetter = myfile.get();
		}
		if (currentLetter == '#') {
			comment();
		}
		else {
			while (currentLetter != '(') {
				
				
				if (!isspace(currentLetter)) {
					whichSection += currentLetter;
					Tokens += currentLetter;
				}
				currentLetter = myfile.get();
				if (currentLetter == ':') {
					currentLetter = '(';
					whichSection += ':';
				}
			}
			Tokens += currentLetter;
			currentLetter = myfile.get();
			if (whichSection != "Rules:") {
				while ((currentLetter != '.')) {
					IDName = "";
					if (currentLetter == '\'') {
						Tokens += currentLetter;
						IDName += currentLetter;
						currentLetter = myfile.get();
						while (currentLetter != '\'') {
							Tokens += currentLetter;
							IDName += currentLetter;
							currentLetter = myfile.get();
						}
						Tokens += currentLetter;
						IDName += currentLetter;
						stringID.push_back(IDName);
						currentLetter = myfile.get();
					}
					Tokens += currentLetter;
					currentLetter = myfile.get();

				}
				Tokens += currentLetter;
				currentLetter = myfile.get();
				Facts.push_back(Tokens);
			}
		}
	}

	while (whichSection != "Queries:") {
		whichSection = "";
		Tokens = "";
		while (isspace(currentLetter)) {
			currentLetter = myfile.get();
		}
		if (currentLetter == '#') {
			comment();
		}
		else {
			while (currentLetter != '(') {
				

				if (!isspace(currentLetter)) {
					whichSection += currentLetter;
					Tokens += currentLetter;
				}
				currentLetter = myfile.get();
				if (currentLetter == ':') {
					currentLetter = '(';
					whichSection += ':';
				}
			}
			Tokens += currentLetter;
			currentLetter = myfile.get();
			if (whichSection != "Queries:") {
				while ((currentLetter != '.')) {
					IDName = "";
					if (currentLetter == '\'') {
						Tokens += currentLetter;
						IDName += currentLetter;
						currentLetter = myfile.get();
						while (currentLetter != '\'') {
							Tokens += currentLetter;
							IDName += currentLetter;
							currentLetter = myfile.get();
						}
						Tokens += currentLetter;
						IDName += currentLetter;
						stringID.push_back(IDName);
						currentLetter = myfile.get();
					}
					if (!isspace(currentLetter)) {
						Tokens += currentLetter;
					}
					currentLetter = myfile.get();

				}
				Tokens += currentLetter;
				currentLetter = myfile.get();
				Rules.push_back(Tokens);
			}
		}
	}

	while (myfile.peek() != EOF) {
		Tokens = "";
		while (isspace(currentLetter)) {
			currentLetter = myfile.get();
		}
		if (myfile.peek() != EOF) {
			if (currentLetter == '#') {
				comment();
			}
			else {
				while ((currentLetter != '(')) {
					Tokens += currentLetter;
					currentLetter = myfile.get();
					if (currentLetter == '\n') {
						currentLetter = myfile.get();
					}
				}
				if (!isspace(currentLetter)) {
					Tokens += currentLetter;
				}
				currentLetter = myfile.get();
				if ((myfile.peek() != EOF) || (currentLetter != '?')) {
					while ((currentLetter != '?')) {
						if (currentLetter != '?') {
							IDName = "";
							if (currentLetter == '\'') {
								Tokens += currentLetter;
								IDName += currentLetter;
								currentLetter = myfile.get();
								while (currentLetter != '\'') {
									Tokens += currentLetter;
									IDName += currentLetter;
									currentLetter = myfile.get();
								}
								Tokens += currentLetter;
								IDName += currentLetter;
								currentLetter = myfile.get();
							}
							if (!isspace(currentLetter)) {
								Tokens += currentLetter;
							}
							currentLetter = myfile.get();
						}
						else {
							Tokens += currentLetter;
							currentLetter = '?';
						}
						
					}
					Tokens += currentLetter;
					currentLetter = myfile.get();
					Queries.push_back(Tokens);
				}
			}
		}
	}

}

void Parser::comment() {
	while (currentLetter != '\n') {
		currentLetter = myfile.get();
	}
	currentLetter = myfile.get();
}

string Parser::printTokens() {
	string print = "";
	print += "Schemes(";
	print += to_string(Schemes.size());
	print += "):";
	print += "\n";
	for (long unsigned int i = 0; i < Schemes.size(); ++i) {
		print += "  ";
		print += Schemes.at(i);
		print += "\n";
	}
	print += "Facts(";
	print += to_string(Facts.size());
	print += "):";
	print += "\n";
	for (long unsigned int i = 0; i < Facts.size(); ++i) {
		print += "  ";
		print += Facts.at(i);
		print += "\n";
	}
	print += "Rules(";
	print += to_string(Rules.size());
	print += "):";
	print += "\n";
	for (long unsigned int i = 0; i < Rules.size(); ++i) {
		print += "  ";
		print += Rules.at(i);
		print += "\n";
	}
	print += "Queries(";
	print += to_string(Queries.size());
	print += "):";
	print += "\n";
	for (long unsigned int i = 0; i < Queries.size(); ++i) {
		print += "  ";
		print += Queries.at(i);
		print += "\n";
	}
	print += "Domain(";
	print += to_string(stringID.size());
	print += "):";
	print += "\n";
	for (long unsigned int i = 0; i < stringID.size(); ++i) {
		print += "  ";
		print += stringID.at(i);
		print += "\n";
	}
	return print;
}

void Parser::sortAndErase() {
	set<string> s(stringID.begin(), stringID.end());
	stringID.assign(s.begin(), s.end());
}