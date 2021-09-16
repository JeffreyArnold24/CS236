#include "Lexer.h"
#include<fstream>
#include<iostream>
using namespace std;

int main(int argc, char *argv[]) {

    string filename = argv[1];
    Lexer l; 
    l.Run(filename);
    ofstream myfile;
    myfile.open("Lab1PassOffCases / out.txt");
    myfile << l.printTokens();
    myfile.close();
    return 0;
}