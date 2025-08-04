#include "Lexer.hpp"
#include <cctype>
#include <iostream>

string Lexer::LexicalError::what() {
    string errorMessage(string("Error - ") + message + string(":\n"));
    errorMessage += instruction + string("\n");
    for (auto it = instruction.begin(); it < instruction.end(); it++) {
        if (errorBegin <= it && it < errorEnd) {
            errorMessage += "^";
        } else {
            errorMessage += " ";
        }
    }
    return errorMessage;
}

ostream &Lexer::operator<<(ostream &out, const Lexer::Token &token) {
    switch (token.kind) {
        case Lexer::TokenKind::Name:
        out << "[Name] ";
        break;
        case Lexer::TokenKind::Option:
        out << "[Option] ";
        break;
        case Lexer::TokenKind::StringLiteral:
        out << "[StringLiteral] ";
        break;
        case Lexer::TokenKind::Redirection:
        out << "[Redirection] ";
        break;
        case Lexer::TokenKind::Pipe:
        out << "[Pipe] ";
    }

   return out << token.value;
}

bool Lexer::isSpace(char c) {
    return (c == ' ') || (c == '\t');
}

bool Lexer::validChar(Lexer::TokenKind kind, char c) {
    if (kind == TokenKind::Name) {
        return (c == '.') || (c == '_') || isalpha(c) || isdigit(c);
    } else if (kind == TokenKind::Option) {
        return isalpha(c) || isdigit(c);
    }

    return false; //ne bi trebalo da se poziva za druge tipove
}

vector<Lexer::Token> Lexer::tokenize(string &instr) {
    auto it = instr.begin();
    vector<Token> tokens;
    while (it != instr.end()) {
        if (isSpace(*it)) {
            it ++;
        } else if (*it == '|') {
            auto begin = it;
            tokens.emplace_back(TokenKind::Pipe, string(begin, ++it)); //[)
        } else if (*it == '<') {
            auto begin = it;
            tokens.emplace_back(TokenKind::Redirection, string(begin, ++it));
        } else if (*it == '>') { // > >>
            auto begin = it;
            if (*(it+1) == '>') {
                it++;
            }
            tokens.emplace_back(TokenKind::Redirection, string(begin, ++it));
        } else if (*it == '"') {
            auto begin = it++;
            while (it != instr.end() && *it != '"') {
                it ++;
            }

            if (it == instr.end()) {
                throw LexicalError(instr, "String Literal not closed", begin, it);
            }

            tokens.emplace_back(TokenKind::StringLiteral, string(begin, ++it));
        } else if (*it == '-') {
            auto begin = it++;
            while (it != instr.end() && validChar(TokenKind::Option, *it)) {
                it ++;
            }

            if (it != instr.end() && !isSpace(*it)) {
                throw LexicalError(instr, "Invalid char in command option", it, it+1);
            }

            tokens.emplace_back(TokenKind::Option, string(begin, it));
        } else {
            auto begin = it;
            while (it != instr.end() && validChar(TokenKind::Name, *it)) {
                it ++;
            }
            
            if (it != instr.end() && !isSpace(*it)) {
                throw LexicalError(instr, "Invalid char in command/arg", it, it+1);
            }
            tokens.emplace_back(TokenKind::Name, string(begin, it));
        }
    }

    return tokens;
}