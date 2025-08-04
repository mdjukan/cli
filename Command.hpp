#pragma once
#include <string>
using namespace std;

class Command {
    public:
    virtual void run();
    static Command *fromInstruction(string &instr);
};