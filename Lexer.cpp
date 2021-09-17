#include "Lexer.h"

using namespace std;

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    
}

void Lexer::CreateAutomata() {
    
}

void Lexer::Run(string filename) {
    
    lineNumber = 1;
    totalTokens = 0;
    myfile.open(filename);
    currentLetter = myfile.get();
    bool closeFile = false;
    while (!closeFile) {
        if (isspace(currentLetter)) {
            if (currentLetter == '\n') {
                lineNumber = lineNumber + 1;
            }
            currentLetter = myfile.get();

        }
        else {
            switch (currentLetter) {
            case',':
                pushComma();
                currentLetter = myfile.get();
                break;
            case'.':
                pushPeriod();
                currentLetter = myfile.get();
                break;
            case'?':
                pushQMark();
                currentLetter = myfile.get();
                break;
            case'(':
                pushLeftParen();
                currentLetter = myfile.get();
                break;
            case')':
                pushRightParen();
                currentLetter = myfile.get();
                break;
            case':':
                colonOrColonDash();
                currentLetter = myfile.get();
                break;
            case'*':
                pushMultiply();
                currentLetter = myfile.get();
                break;
            case'+':
                pushAdd();
                currentLetter = myfile.get();
                break;
            case'#':
                blockOrNormalComment();
                currentLetter = myfile.get();
                break;
            case EOF:
                pushEOF();
                myfile.close();
                closeFile = true;
                break;
            case '\'':
                pushString();
                currentLetter = myfile.get();
                break;
            default:
                if (isalpha(currentLetter)) {
                    checkID();
                }
                else {
                    string str;
                    str =+ currentLetter;
                    pushUndefined(str, lineNumber);
                    currentLetter = myfile.get();
                }
            }

        }
    }
        

}

void Lexer::pushComma() {
    Token t;
    t.setType("COMMA");
    t.setValue("\",\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;

}

void Lexer::pushPeriod() {
    Token t;
    t.setType("PERIOD");
    t.setValue("\".\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushLeftParen() {
    Token t;
    t.setType("LEFT_PAREN");
    t.setValue("\"(\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushRightParen() {
    Token t;
    t.setType("RIGHT_PAREN");
    t.setValue("\")\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushQMark() {
    Token t;
    t.setType("Q_MARK");
    t.setValue("\"?\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::colonOrColonDash() {
    string str = ":";
    if (myfile.peek() == '-') {
        str = ":-";
        currentLetter = myfile.get();
    }
    
    if (str == ":") {
        pushColon();
    }
    if (str == ":-") {
        pushColonDash();
    }
    
}

void Lexer::pushColon() {
    Token t;
    t.setType("COLON");
    t.setValue("\":\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushColonDash() {
    Token t;
    t.setType("COLON_DASH");
    t.setValue("\":-\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushMultiply() {
    Token t;
    t.setType("MULTIPLY");
    t.setValue("\"*\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushAdd() {
    Token t;
    t.setType("ADD");
    t.setValue("\"+\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushSchemes() {
    Token t;
    t.setType("SCHEMES");
    t.setValue("\"Schemes\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushFacts() {
    Token t;
    t.setType("FACTS");
    t.setValue("\"Facts\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushRules() {
    Token t;
    t.setType("RULES");
    t.setValue("\"Rules\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushQueries() {
    Token t;
    t.setType("QUERIES");
    t.setValue("\"Queries\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushID(string currentLetter) {
    Token t;
    string IDString = "\"" + currentLetter + "\"";
    t.setType("ID");
    t.setValue(IDString);
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::blockOrNormalComment() {
    int skippedLines = lineNumber;
    if (myfile.peek() == '|') {
        currentLetter = myfile.get();
        currentLetter = myfile.get();
        string str = "#|";
        while (!((currentLetter == '|') && (myfile.peek() == '#'))) {
            if (currentLetter == '\n') {
                lineNumber++;
            }
            if (currentLetter == EOF) {
                pushUndefined(str, skippedLines);
                return;
            }
            str += currentLetter;
            currentLetter = myfile.get();
        }
        str += "|#";
        currentLetter = myfile.get();
        pushComment(str, skippedLines);
    }
    else {
        currentLetter = myfile.get();
        string str = "#";
        while (currentLetter != '\n') {
            str += currentLetter;
            currentLetter = myfile.get();
        }
        lineNumber++;
        pushComment(str, skippedLines);
    }
}

void Lexer::pushComment(string comment, int line) {
    Token t;
    string pushComment = "\"" + comment + "\"";
    t.setType("COMMENT");
    t.setValue(pushComment);
    t.setLine(line);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushString() {
    int skippedLines = lineNumber;
    string str = "\'";
    currentLetter = myfile.get();
    bool endWhile = false;
    while (!endWhile) {
        if (currentLetter == '\'' && myfile.peek() == '\'') {
            str += currentLetter;
            currentLetter = myfile.get();
            str += currentLetter;
            currentLetter = myfile.get();
        }
        else {
            if (currentLetter == '\'') {
                endWhile = true;
            }
            else {
                if (currentLetter == EOF) {
                    myfile.unget();
                    endWhile = true;
                    pushUndefined(str, skippedLines);
                    return;
                }
                else {
                    if (currentLetter == '\n') {
                        lineNumber++;
                        str += currentLetter;
                        currentLetter = myfile.get();

                    }
                    else {
                        str += currentLetter;
                        currentLetter = myfile.get();
                    }
                }
            }
        }
       
        
    }
    str += "\'";
    Token t;
    string stringValue = "\"" + str + "\"";
    t.setType("STRING");
    t.setValue(stringValue);
    t.setLine(skippedLines);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushUndefined(string undefined, int startingLine) {
    Token t;
    string valuestring = "\"" + undefined + "\"";
    t.setType("UNDEFINED");
     t.setValue(valuestring);
    t.setLine(startingLine);
    tokenVector.push_back(t);
    totalTokens = totalTokens + 1;
}

void Lexer::pushEOF() {
    Token t;
    t.setType("EOF");
    t.setValue("\"\"");
    t.setLine(lineNumber);
    tokenVector.push_back(t);
    totalTokens++;
}

void Lexer::checkID() {
    string str;
    while (isalnum(currentLetter)) {
        str += currentLetter;
        currentLetter = myfile.get();
    }
    if (str == "Schemes")
        pushSchemes();
    else if (str == "Facts")
        pushFacts();
    else if (str == "Rules")
        pushRules();
    else if (str == "Queries")
        pushQueries();
    else
        pushID(str);
}

string Lexer::printTokens() {
    string str;
    for (long unsigned int i = 0; i < tokenVector.size(); i++) {
        str += "(";
        str += tokenVector[i].getType();
        str += ",";
        str += tokenVector[i].getValue();
        str += ",";
        str += tokenVector[i].getLine();
        str += ")";
        str += "\n";
    }
    str += "Total Tokens = ";
    str += to_string(totalTokens);
    return str;
}
