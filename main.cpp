#include <iostream>

#include "TinyLog.h"

using namespace std;

int main() {
    g_tinylog.SetLogLevel(Utils::INFO);

    cerr << "start time: " << Utils::GetCurrentTime() << endl;

    for (int i = 0; i < 10000000; i++)
    {
        LOG_INFO << "hello world";
    }

    cerr << "end time: " << Utils::GetCurrentTime() << endl;
    cin.get();

    return 0;
}