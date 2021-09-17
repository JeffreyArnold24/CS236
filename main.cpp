#include "Lexer.h"
#include<ifstream>
using namespace std;

int main(int argc, char* argv[]) {

    string filename = argv[1];
    Lexer l;
    l.Run(filename);  
    cout << l.printTokens();
    return 0;
}