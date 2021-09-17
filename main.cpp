#include "Lexer.h"
#include<fstream>
#include<iostream>
using namespace std;

int main(int argc, char* argv[]) {

    string filename = argv[1];
    Lexer l;
    l.Run(filename);
    ofstream myfile;
    myfile.open("out.txt");
    myfile << l.printTokens();
    cout << l.printTokens();
    myfile << endl;
    myfile.close();
    return 0;
}