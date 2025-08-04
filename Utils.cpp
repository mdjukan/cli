#include "Utils.hpp"

const size_t instructionLengthLimit = 512;
void Utils::readInstruction(istream &in, string &instr) {
    getline(in, instr); 
    if (instr.size() > instructionLengthLimit) {
        instr.resize(instructionLengthLimit);
    }
}