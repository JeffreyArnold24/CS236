#include "Lexer.h"
#include "Parser.h"
#include<fstream>
using namespace std;

int main(int argc, char* argv[]) {

    string filename = argv[1];
    Parser p;
    bool wasASuccess = p.Parse(filename);
    if (wasASuccess) {
        cout << "Success!" << endl;
        p.readInput(filename);
        p.sortAndErase();
        cout << p.printTokens();

    }
    else {
        cout << "Failure!" << endl;
        cout << "  " << p.printError() << endl;
    }
    
    return 0;
}