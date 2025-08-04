#include "Command.hpp"
#include "Lexer.hpp"
#include <iostream>
using namespace std;

Command *Command::fromInstruction(string &instr) {
    vector<Lexer::Token> tokens = Lexer::tokenize(instr);
    for (auto &token : tokens) {
        cout << token << endl;
    }
    return new Command();
}

void Command::run() {
    cout << "[run todo]" << endl;
}