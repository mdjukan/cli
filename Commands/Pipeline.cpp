#include "Pipeline.hpp"

vector<vector<Lexer::Token>> Pipeline::splitToSubcommands() {
        vector<vector<Lexer::Token>> result;
        vector<Lexer::Token> subcommand;
        for (auto it = tokens.begin(); it < tokens.end(); it++) {
            if ((*it).kind == Lexer::TokenKind::Pipe) {
                result.push_back(subcommand);
                subcommand.clear();
            } else {
                subcommand.push_back(*it);
            }
        }

        result.push_back(subcommand);
        return result;
}

bool Pipeline::tokensInvalid() {
    // moguce greske
    // | ...
    // .... |
    // ....||.....
    if (tokens.front().kind == Lexer::TokenKind::Pipe ||
        tokens.back().kind == Lexer::TokenKind::Pipe) {
            return true;
    }

    for (auto it = tokens.begin(); it+1 < tokens.end(); it ++) {
        if ((*it).kind == Lexer::TokenKind::Pipe && (*(it+1)).kind == Lexer::TokenKind::Pipe) {
            return true;
        }
    }

    return false;
}

Pipeline::Pipeline(const vector<Lexer::Token> &__tokens) : Command(__tokens) {
    if (tokensInvalid()) {
        throw SyntaxError("Invalid pipeline");
    }

    vector<vector<Lexer::Token>> subcommands = splitToSubcommands();

    for (auto &subcommand : subcommands) {
        shared_ptr<Command> command = Command::fromTokens(subcommand);
        commands.push_back(command);
    }

    for (auto it = commands.begin(); it+1 < commands.end(); it ++) {
        shared_ptr<stringstream> ss = make_shared<stringstream>();
        (*it)->setOutputStream(ss);
        (*(it+1))->setInputStream(ss);
    }
}

void Pipeline::run() {
    for (auto &command : commands) {
        command->run();
    }
}

void Pipeline::setOutputStream(shared_ptr<ostream> __outputStream) {
    commands.back()->setOutputStream(__outputStream);
}