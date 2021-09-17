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

    lineNumber = 0;
    totalTokens = 0;
    myfile.open(filename);
    closeFile = false;
    if (myfile.peek() != EOF) {
        currentLetter = myfile.get();
        lineNumber++;
    }    
    else {
        closeFile = true;
        pushEOF();
    }
    
    while (!closeFile) {
        if (isspace(currentLetter)) {
            if (currentLetter == '\n') {
                lineNumber = lineNumber + 1;
            }
            if (myfile.peek() != EOF) {
                currentLetter = myfile.get();
            }
            else {
                pushEOF();
                closeFile = true;
            }

        }
        else {
            switch (currentLetter) {
            case',':
                pushComma();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            case'.':
                pushPeriod();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            case'?':
                pushQMark();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            case'(':
                pushLeftParen();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            case')':
                pushRightParen();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            case':':
                colonOrColonDash();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            case'*':
                pushMultiply();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            case'+':
                pushAdd();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            case'#':
                blockOrNormalComment();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            case EOF:
                pushEOF();
                myfile.close();
                closeFile = true;
                break;
            case '\'':
                pushString();
                if (myfile.peek() != EOF) {
                    currentLetter = myfile.get();
                }
                else {
                    pushEOF();
                    closeFile = true;
                }
                break;
            default:
                if (isalpha(currentLetter)) {
                    checkID();
                }
                else {
                    string str;
                    str = +currentLetter;
                    pushUndefined(str, lineNumber);
                    if (myfile.peek() != EOF) {
                        currentLetter = myfile.get();
                    }
                    else {
                        pushEOF();
                        closeFile = true;
                    }
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
        if (myfile.peek() != EOF) {
            currentLetter = myfile.get();
        }
        else {
            pushEOF();
            closeFile = true;
            return;
        }
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
        if (myfile.peek() != EOF) {
            currentLetter = myfile.get();
        }
        else {
            pushEOF();
            closeFile = true;
            return;
        }
        if (myfile.peek() != EOF) {
            currentLetter = myfile.get();
        }
        else {
            pushEOF();
            closeFile = true;
            return;
        }
        string str = "#|";
        while (!((currentLetter == '|') && (myfile.peek() == '#'))) {
            if (currentLetter == '\n') {
                lineNumber++;
            }
            if (myfile.peek() == EOF) {
                pushUndefined(str, skippedLines);
                return;
            }
            str += currentLetter;
            currentLetter = myfile.get();
        }
        str += "|#";
        if (myfile.peek() != EOF) {
            currentLetter = myfile.get();
        }
        else {
            pushEOF();
            closeFile = true;
            return;
        }
        pushComment(str, skippedLines);
    }
    else {
        if (myfile.peek() != EOF) {
            currentLetter = myfile.get();
        }
        else {
            pushEOF();
            closeFile = true;
            return;
        }
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
    if (myfile.peek() != EOF) {
        currentLetter = myfile.get();
    }
    else {
        pushEOF();
        closeFile = true;
        return;
    }
    bool endWhile = false;
    while (!endWhile) {
        if (currentLetter == '\'' && myfile.peek() == '\'') {
            str += currentLetter;
            if (myfile.peek() != EOF) {
                currentLetter = myfile.get();
            }
            else {
                pushEOF();
                closeFile = true;
                return;
            }
            str += currentLetter;
            if (myfile.peek() != EOF) {
                currentLetter = myfile.get();
            }
            else {
                pushEOF();
                closeFile = true;
                return;
            }
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
                        if (myfile.peek() != EOF) {
                            currentLetter = myfile.get();
                        }
                        else {
                            pushEOF();
                            closeFile = true;
                            return;
                        }

                    }
                    else {
                        str += currentLetter;
                        if (myfile.peek() != EOF) {
                            currentLetter = myfile.get();
                        }
                        else {
                            pushEOF();
                            closeFile = true;
                            return;
                        }
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
    myfile.close();
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
    str += '\n';
    return str;
}