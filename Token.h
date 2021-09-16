#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;

class Token
{
private:
    string tokenName;
    int lineNumber;
    string type;

public:
    void setType(string);
    void setValue(string);
    void setLine(int);


    string getType();
    string getValue();
    int getLine();
};

#endif // TOKEN_H

