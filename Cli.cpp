#include "Cli.hpp"
#include "Utils.hpp"
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
        Utils::readInstruction(cin, instr);

        try {
            shared_ptr<Command> command = Command::fromString(instr);
            command->run();
        } catch (Exception &e) {
            cout << e.getMessage() << endl;
        }
    }
}