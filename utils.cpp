
#include "utils.h"

using std::to_string;


string RandomIp()
{
    string ip = "";
    for (int i = 0; i < 4; i++)
    {
        ip += to_string(rand() % 256);
        if (i < 3)
        {
            ip += ".";
        }
    }
    return ip;
}
