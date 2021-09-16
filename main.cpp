#include "Lexer.h"
using namespace std;

int main(int argc, char *argv[]) {

    string filename = argv[1];
    Lexer l; 
    l.Run(filename);
    l.printTokens();
    return 0;
}