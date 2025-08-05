#include "Time.hpp"

Time::Time(const vector<Lexer::Token> &__tokens) : Command(__tokens) {
    //redirections -- TODO
}

void Time::run() {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    (*out()) << put_time(localtime(&now_c), "%H:%M:%S") << endl;
}
