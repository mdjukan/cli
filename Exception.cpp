
#include "Exception.hpp"

string LexicalError::getMessage() {
    stringstream ss;
    ss << "Error - " << message << ":" << endl;
    ss << instruction << endl;
    for (auto it = instruction.begin(); it < instruction.end(); it++) {
        if (errorBegin <= it && it < errorEnd) {
            ss << "^";
        } else {
            ss << " ";
        }
    }

    return ss.str();
}

string SyntaxError::getMessage()  {
    stringstream ss;
    ss << "Error - " << message << ".";
    return ss.str();
}

string RuntimeError::getMessage() {
    stringstream ss;
    ss << "Error - " << message << ".";
    return ss.str();
}
