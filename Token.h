#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>
using namespace std;

class Token
{
private:
    string tokenName;
    int lineNumber;
    string type;

public:
    void setType(string);   //Schemes, Facts, Rules, Queries
    void setValue(string);   //name of Schemes, Fact, etc.
    void setLine(int);
    void addID(string);  // each ID in a Scheme, etc.
    string getID(int);
    int numberIDs();

    
    vector<string> IDValues;
    string getType();
    string getValue();
    string getLine();
};

#endif // TOKEN_H
