#include "Cli.hpp"
#include "Lexer.hpp"
#include "Lexer.hpp"
#include "Command.hpp"
#include "Exception.hpp"
#include <iostream>
#include <string>
using namespace std;

void Cli::run() {
    string instr;
    while (true) {
        cout << "$ ";
        
        try {
            Lexer::readInstruction(cin, instr);
            vector<Lexer::Token> tokens = Lexer::tokenize(instr);
            shared_ptr<Command> command = Command::fromTokens(tokens);
            command->run();
        } catch (Exception &e) {
            cout << e.getMessage() << endl;
        }
    }
}