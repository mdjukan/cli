#include "Echo.hpp"

Echo::Echo(const vector<Lexer::Token> &__tokens) : Command(__tokens) {
    auto tokenIt = tokens.begin() + 1;
    if (tokenIt != tokens.end() && (*tokenIt).kind == Lexer::TokenKind::Name) {
        inputStreamFromFile((*tokenIt).value);
        tokenIt ++;
    } else if (tokenIt != tokens.end() && (*tokenIt).kind == Lexer::TokenKind::StringLiteral) {
        inputStreamFromStrLit((*tokenIt).value);
        tokenIt ++;
    }

    handleRedirects(tokenIt);
}

void Echo::run() {
    string line;
    while (getline(in(), line)) {
        out() << line << endl;
    }

    in().clear();
}
