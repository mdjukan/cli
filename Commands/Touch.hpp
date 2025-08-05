#pragma once
#include "../Command.hpp"

//touch filename
class Touch : public Command {
    private:
    string fileName;

    public:
    Touch(const vector<Lexer::Token> &__tokens);
    void run() override ;
};