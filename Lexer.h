#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Token.h"
#include <iostream>
#include<fstream>
using namespace std;

class Lexer
{
private:

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    void Run(string);

    int lineNumber;
    int totalTokens;
    fstream myfile;
    vector<Token> tokenVector;
    char currentLetter;
    void pushComma();
    void pushPeriod();
    void pushQMark();
    void pushLeftParen();
    void pushRightParen();
    void colonOrColonDash();
    void pushColon();
    void pushColonDash();
    void pushMultiply();
    void pushAdd();
    void pushSchemes();
    void pushFacts();
    void pushRules();
    void pushQueries();
    void pushID(string);
    void pushString();
    void blockOrNormalComment();
    void pushComment(string, int);
    void pushUndefined(string, int);
    void pushEOF();
    void checkID();

    string printTokens();

};

#endif // LEXER_H
