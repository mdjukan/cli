#include "Time.hpp"

Time::Time(const vector<Lexer::Token> &__tokens) : Command(__tokens) {
    //redirections -- TODO
}

void Time::run() {
    time_t currentTime = std::time(nullptr);
    tm localTime;
    localtime_r(&currentTime, &localTime);
    //localtime_s(&localTime, &currentTime); //WIN
    out() << localTime.tm_hour << ":" << localTime.tm_min << ":" << localTime.tm_sec << endl;
}
