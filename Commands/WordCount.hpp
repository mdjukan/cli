#pragma once
#include "../Command.hpp"

//wc -w|-c [argument]
class WordCount : public Command {
    enum WordCountTarget {
        Words,
        Chars
    };

    WordCountTarget target;   
    size_t countChars();
    size_t countWords();

    public:
    WordCount(const vector<Lexer::Token> &__tokens);
    void run() override ;
};