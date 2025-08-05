#pragma once
#include <string>
#include <vector>
using namespace std;

namespace Lexer {
    enum TokenKind {
        Option, //-w, -c, ... [a-z0-9] -n21 
        StringLiteral, // "...."
        Name, //wc, truncate, file.txt . [a-zA-Z0-0], ., _
        Redirection, // > < >>
        Pipe // |
    };

    struct Token {
        TokenKind kind;
        string value;

        Token(TokenKind kind, string value) : kind(kind), value(value) {}
        friend ostream &operator<<(ostream &out, const Token &token);
    };

    ostream &operator<<(ostream &out, const Token &token);

    bool isSpace(char c);
    bool validChar(TokenKind kind, char c);

    vector<Token> tokenize(string &instr);

    const size_t instructionLengthLimit = 512;
    void readInstruction(istream &in, string &instr);
};