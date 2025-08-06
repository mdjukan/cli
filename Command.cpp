#include "Command.hpp"
#include "Lexer.hpp"
#include "Exception.hpp"
#include "Commands/Commands.hpp"
#include <iostream>
using namespace std;

shared_ptr<Command> Command::fromTokens(const vector<Lexer::Token> &tokens) {
    if (tokens.empty()) {
        throw SyntaxError("Empty instruction");
    }

    if (tokens.front().kind != Lexer::TokenKind::Name) {
        throw SyntaxError("Invalid instruction");
    }

    if (Lexer::isPipeline(tokens)) {
        return make_shared<Pipeline>(tokens);
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
    } else if (command == "batch") {
        return make_shared<Batch>(tokens);
    } else {
        throw SyntaxError("Unknown command");
    }
}

ostream &Command::out() {
    if (outputStream == nullptr) {
        return cout;
    } else {
        return *outputStream;
    }
}

istream &Command::in() {
    if (inputStream == nullptr) {
        return cin;
    } else {
        return *inputStream;
    }
}

void Command::inputStreamFromFile(string fileName) {
    if (inputStream != nullptr) {
        throw SyntaxError("Multiple assigns to input stream");
    }

    shared_ptr<ifstream> fileStream = make_shared<ifstream>(fileName);
    if (!fileStream->is_open()) {
        throw RuntimeError("Can't open file " + fileName);
    }

    inputStream = fileStream;
}

void Command::outputStreamFromFile(string fileName) {
    if (outputStream != nullptr) {
        throw SyntaxError("Multiple assigns to output stream");
    }

    shared_ptr<ofstream> fileStream = make_shared<ofstream>(fileName);
    if (!fileStream->is_open()) {
        throw RuntimeError("Can't open file " + fileName);
    }

    outputStream = fileStream;
}

void Command::outputStreamFromFileAppend(string fileName) {
    if (outputStream != nullptr) {
        throw SyntaxError("Multiple assigns to output stream");
    }

    shared_ptr<ofstream> fileStream = make_shared<ofstream>(fileName, ios::app);
    if (!fileStream->is_open()) {
        throw RuntimeError("Can't open file " + fileName);
    }

    outputStream = fileStream;
}

void Command::inputStreamFromStrLit(string strLit) {
    inputStream = make_shared<stringstream>(strLit.substr(1, strLit.size()-2));
}

void Command::handleRedirects(vector<Lexer::Token>::iterator &tokenIt) {
    // > file --- dva tokena prvi je Redirect drugi je Name
    // < file
    // >> file

    while (tokenIt != tokens.end()) {
        if (tokenIt != tokens.end() && (tokenIt + 1) != tokens.end() &&
            (*tokenIt).kind == Lexer::TokenKind::Redirection && 
            (*(tokenIt + 1)).kind == Lexer::TokenKind::Name) {
                string redirection = (*tokenIt).value;
                string fileName = (*(tokenIt + 1)).value;
                if (redirection == "<") {
                    inputStreamFromFile(fileName);
                } else if (redirection == ">") {
                    outputStreamFromFile(fileName);
                } else if (redirection == ">>") {
                    outputStreamFromFileAppend(fileName);
                }

                tokenIt += 2;
        } else {
                throw SyntaxError("Invalid redirections");
        }
    }
}

void Command::setInputStream(shared_ptr<istream> __inputStream) {
    if (inputStream != nullptr) {
        throw SyntaxError("Multiple assigns to input stream");
    }

    inputStream = __inputStream;
}

void Command::setOutputStream(shared_ptr<ostream> __outputStream) {
    if (outputStream != nullptr) {
        throw SyntaxError("Multiple assigns to input stream");
    }

    outputStream = __outputStream;
}

bool Command::writesToStdout() {
    return outputStream == nullptr;
}