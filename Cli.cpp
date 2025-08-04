#include "Cli.hpp"
#include "Utils.hpp"
#include "Lexer.hpp"
#include "Command.hpp"
#include <iostream>
#include <string>
using namespace std;

void Cli::run() {
    string instr;
    while (true) {
        cout << "$ ";
        Utils::readInstruction(cin, instr);

        try {
            Command *command = Command::fromInstruction(instr); // generistati neke izuzetke
            command->run();
            delete command;
        } catch (Lexer::LexicalError &e) {
            cout << e.what() << endl;
        }

    }
}