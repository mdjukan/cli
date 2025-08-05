#include "Touch.hpp"
#include <filesystem>
#include <fstream>

Touch::Touch(const vector<Lexer::Token> &__tokens) : Command(__tokens) {
    auto tokenIt = tokens.begin()+1;

    if (tokenIt == tokens.end() || (*tokenIt).kind != Lexer::TokenKind::Name) {
        throw SyntaxError("Touch missing an argument");
    }

    fileName = (*tokenIt).value;
    //redirections -- TODO
}

void Touch::run()  {
    if (filesystem::exists(fileName)) {
        throw RuntimeError("File " + fileName + " already exists");
    }

    ofstream fs(fileName);
    if (!fs) {
        throw RuntimeError("Couldn't crate a file with name " + fileName);
    }

}
