#include "Command.hpp"
#include "Lexer.hpp"
#include "Exception.hpp"
#include "Commands/Commands.hpp"
#include <iostream>
using namespace std;

shared_ptr<Command> Command::fromString(string &instr) {
    vector<Lexer::Token> tokens = Lexer::tokenize(instr);

    if (tokens.empty()) {
        throw SyntaxError("Empty instruction");
    }

    if (tokens.front().kind != Lexer::TokenKind::Name) {
        throw SyntaxError("Invalid instruction");
    }

    string command = tokens.front().value;
    if (command == "echo") {
        return  make_shared<Echo>(tokens);
    } else if (command == "time") {
        return make_shared<Time>(tokens);
    } else if (command == "date") {
        return make_shared<Date>(tokens);
    } else if (command == "touch") {
        return make_shared<Touch>(tokens);
    } else if (command == "wc") {
        return make_shared<WordCount>(tokens);
    }

    return nullptr; // temp
}

ostream *Command::out() {
    if (outputStream == nullptr) {
        return &cout;
    } else {
        return outputStream.get();
    }
}

istream *Command::in() {
    if (inputStream == nullptr) {
        return &cin;
    } else {
        return inputStream.get();
    }
}

void Command::inputStreamFromFile(string fileName) {
    shared_ptr<ifstream> fileStream = make_shared<ifstream>(fileName);
    if (!fileStream->is_open()) {
        throw RuntimeError("Can't open file " + fileName);
    }

    inputStream = fileStream;
}

void Command::inputStreamFromStrLit(string strLit) {
    inputStream = make_shared<stringstream>(strLit.substr(1, strLit.size()-2));
}