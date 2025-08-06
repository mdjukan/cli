#pragma once
#include "../Command.hpp"
#include <vector>

class Pipeline : public Command {
    private:
    vector<shared_ptr<Command>> commands;
    vector<vector<Lexer::Token>> splitToSubcommands();
    bool tokensInvalid();

    public:
    Pipeline(const vector<Lexer::Token> &__tokens);
    void run() override ;
    void setOutputStream(shared_ptr<ostream> __outputStream) override;
};