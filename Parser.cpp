#include "Parser.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
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
		if (currentLetter == '\n') {
			line = newLine(line);
		}
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
				line = line - 1;
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
			line = line - 1;
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
		line = line - 1;
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
	string IDString = "";
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
		if (currentLetter == ',') {
			currentLetter = myfile.get();
			while (isspace(currentLetter)) {
				currentLetter = myfile.get();
			}
			if (currentLetter == '\'') {
				currentLetter = myfile.get();
				while (currentLetter != '\'') {
					currentLetter = myfile.get();
				}
				
			}
			else {
				while (currentLetter != ')') {
					if (isalpha(currentLetter)) {
						IDString += currentLetter;
						currentLetter = myfile.get();
					}

				}
				line = newLine(line);
				myfile.close();
				closeFile = true;
				errorMessage("ID", IDString, line);
				return false;
			}
		}
		currentLetter = myfile.get();
	}
	currentLetter = myfile.get();
	if (currentLetter != '.') {
		line = newLine(line);
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
		Token SchemeToken;
		Tokens = "";
		whichSection = "";
		while (isspace(currentLetter)) {
			currentLetter = myfile.get();
		}
		if (currentLetter == '#') {
			comment();
		}
		else {
			while ((currentLetter != '(') && (currentLetter != ':')) {
				if (!isspace(currentLetter)) {
					whichSection += currentLetter;
					Tokens += currentLetter;
				}

				currentLetter = myfile.get();
				if (currentLetter == ':') {
					whichSection += ':';
					
				}
			}
			if (whichSection != "Facts:") {
				SchemeToken.setType("Scheme");
				SchemeToken.setValue(Tokens);
				whichSection += currentLetter;
				Tokens += currentLetter;
				currentLetter = myfile.get();
				while (currentLetter != ')') {
					IDName = "";
					while (currentLetter != ',' && currentLetter != ')') {
						IDName += currentLetter;
						currentLetter = myfile.get();

					}
					SchemeToken.addID(IDName);
					if (currentLetter != ')') {
						currentLetter = myfile.get();
					}
				}
				Schemes.push_back(SchemeToken);
				currentLetter = myfile.get();
			}
			
		}
	}

	currentLetter = myfile.get();
	while (whichSection != "Rules:") {
		Token FactToken;
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
			currentLetter = myfile.get();
			FactToken.setValue(Tokens);
			if (whichSection != "Rules:") {
				FactToken.setType("Rules");
				FactToken.setType(Tokens);
				while ((currentLetter != '.')) {
					IDName = "";
					if (currentLetter == '\'') {
						IDName += currentLetter;
						currentLetter = myfile.get();
						while (currentLetter != '\'') {
							Tokens += currentLetter;
							IDName += currentLetter;
							currentLetter = myfile.get();
						}
						IDName += currentLetter;
						FactToken.addID(IDName);
						currentLetter = myfile.get();
					}
					currentLetter = myfile.get();

				}
				Tokens += currentLetter;
				currentLetter = myfile.get();
				Facts.push_back(FactToken);
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
				//Rules.push_back(Tokens);
			}
		}
	}

	while (myfile.peek() != EOF) {
		Tokens = "";
		Token QuerieToken;
		while (isspace(currentLetter)) {
			currentLetter = myfile.get();
		}
		if (myfile.peek() != EOF) {
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
				QuerieToken.setType("Queries");
				QuerieToken.setValue(Tokens);
				currentLetter = myfile.get();
				if ((myfile.peek() != EOF) || (currentLetter != '?')) {
					while ((currentLetter != '?')) {
						if (currentLetter != '?') {
							IDName = "";
							if (currentLetter != ')') {
								
								IDName += currentLetter;
								currentLetter = myfile.get();
								while ((currentLetter != ',') && currentLetter != ')') {
									IDName += currentLetter;
									currentLetter = myfile.get();
								}
								currentLetter = myfile.get();
								QuerieToken.addID(IDName);
							}
							
						}
						else {
							Tokens += currentLetter;
							currentLetter = '?';
						}
						
					}
					Tokens += currentLetter;
					currentLetter = myfile.get();
					Queries.push_back(QuerieToken);
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
	string variableSubs = "";
	bool matchingIDs = true;
	for (long unsigned int i = 0; i < Queries.size(); ++i) {
		vector<string> variableSubsVector;
		
		print += Queries.at(i).getValue() += "(";
		for (int j = 0; j < Queries.at(i).numberIDs(); ++j) {
			print += Queries.at(i).getID(j);
			if (j != (Queries.at(i).numberIDs() - 1)) {
				print += ",";
			}
			else {
				print += ")? ";
			}
		}
		for (long unsigned int j = 0; j < Facts.size(); ++j) {
			matchingIDs = true;
			if (Queries.at(i).getValue() == Facts.at(j).getValue()) {
				for (int k = 0; k < Queries.at(i).numberIDs(); ++k) {
					if (Queries.at(i).getID(k)[0] == '\'') {
						if (Queries.at(i).getID(k) != Facts.at(j).getID(k)) {
							matchingIDs = false;
						}
					}
				}
			}
			else {
				matchingIDs = false;
			}
			if (matchingIDs) {
				variableSubs = "  ";
				for (int k = 0; k < Queries.at(i).numberIDs(); ++k) {
					if (Queries.at(i).getID(k)[0] != '\'') {
						variableSubs += Queries.at(i).getID(k);
						variableSubs += "=";
						variableSubs += Facts.at(j).getID(k);
						if (k != Queries.at(i).numberIDs() - 1) {
							variableSubs += ", ";
						}
					}
					
				}
				variableSubs += '\n';
				variableSubsVector.push_back(variableSubs);
			}	
		}
		if (variableSubsVector.size() > 0) {
			sort(variableSubsVector.begin(), variableSubsVector.end());
			print += "Yes(";
			print += to_string(variableSubsVector.size());
			print += ")\n";
			for (long unsigned int j = 0; j < variableSubsVector.size(); ++j) {
				if (variableSubsVector.at(j) != "  \n") {
					print += variableSubsVector.at(j);
				}
			}
		}
		else {
			print += "No\n";
		}
	}
	return print;
}

void Parser::sortAndErase() {
	set<string> s(stringID.begin(), stringID.end());
	stringID.assign(s.begin(), s.end());
}