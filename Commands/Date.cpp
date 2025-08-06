#include "Date.hpp"

Date::Date(const vector<Lexer::Token> &__tokens) : Command(__tokens) {
    //redirections -- TODO
}

void Date::run() {
    time_t currentTime = std::time(nullptr);
    tm localTime;
    localtime_r(&currentTime, &localTime);
    //localtime_s(&localTime, &currentTime); //WIN
    out() << localTime.tm_mday << "." << (localTime.tm_mon + 1) << "." << (localTime.tm_year+1900) << endl;
}
