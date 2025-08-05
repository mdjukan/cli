#include "WordCount.hpp"
#include <cctype>

WordCount::WordCount(const vector<Lexer::Token> &__tokens) : Command(__tokens) {
    auto tokenIt = tokens.begin()+1;

    if (tokenIt == tokens.end() || (*tokenIt).kind != Lexer::TokenKind::Option) {
        throw SyntaxError("WordCount without an option");
    }

    if ((*tokenIt).value == "-w") {
        target = WordCountTarget::Words;
    } else if ((*tokenIt).value == "-c") {
        target = WordCountTarget::Chars;
    } else {
        throw SyntaxError("Invalid option for WordCount");
    }

    tokenIt ++;

    if (tokenIt != tokens.end() && (*tokenIt).kind == Lexer::TokenKind::Name) {
        inputStreamFromFile((*tokenIt).value);
        tokenIt ++;
    } else if (tokenIt != tokens.end() && (*tokenIt).kind == Lexer::TokenKind::StringLiteral) {
        inputStreamFromStrLit((*tokenIt).value);
    }

    //TODO redirections
}

size_t WordCount::countChars() {
    size_t result = 0;
    string line;
    while (getline(*in(), line)) {
        result += line.size();
    }

    in()->clear();

    return result;
}

size_t WordCount::countWords() {
    size_t result = 0;
    string line;
    while (getline(*in(), line)) {
        bool inWord = false;
        for (char c : line) {
            if (inWord) {
                if (isspace(c)) {
                    inWord = false;
                }
            } else {
                if (!isspace(c)) {
                    inWord = true;
                    result += 1;
                }
            }
        }
    }

    in()->clear();

    return result;
}

void WordCount::run() {
    size_t result;
    switch (target) {
        case WordCountTarget::Words:
        result = countWords();
        break;
        case WordCountTarget::Chars:
        result = countChars();
    }

    (*out()) << result << endl;
}