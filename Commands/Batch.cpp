#include "Batch.hpp"

Batch::Batch(const vector<Lexer::Token> &__tokens) : Command(__tokens) {
    auto tokenIt = tokens.begin()+1;

    if (tokenIt != tokens.end() && (*tokenIt).kind == Lexer::TokenKind::Name) {
        inputStreamFromFile((*tokenIt).value);
        tokenIt ++;
    } else if (tokenIt != tokens.end() && (*tokenIt).kind == Lexer::TokenKind::StringLiteral) {
        inputStreamFromStrLit((*tokenIt).value);
        tokenIt ++;
    }

    handleRedirects(tokenIt);
}

void Batch::run() {
    string instr;
    while (Lexer::readInstruction(in(), instr)) {
        try {
            vector<Lexer::Token> tokens = Lexer::tokenize(instr);
            shared_ptr<Command> command = Command::fromTokens(tokens);
            if (command->writesToStdout()) {
                command->setOutputStream(outputStream);
            }

            command->run();
        } catch (Exception &e) {
            out() << e.getMessage() << endl;
        }
    }

    in().clear();
}