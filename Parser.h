#pragma once
#ifndef Parser_H
#define Parser_H
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

class Parser
{
private:
    bool closeFile;

public:
    
    string error;
    int line = 1;
    bool oneItem = false;
    string checkToken;
    char currentLetter;
    bool allCorrect = true;
    bool Parse(string);
    ifstream myfile;
    bool checkSchemes();
    bool checkFacts();
    bool checkRules();
    bool checkQueries();
    int newLine(int);
    void errorMessage(string, string, int);
    string printError();
    void readInput(string);
    void comment();
    vector<string> Schemes;
    vector<string> Facts;
    vector<string> Rules;
    vector<string> Queries;
    vector<string> stringID;
    string IDName;
    string Tokens;
    string printTokens();
    void sortAndErase();

};

#endif // LEXER_H