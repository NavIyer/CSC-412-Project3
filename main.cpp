
#include <iostream>
#include "request.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
    /////// Arguments //////
    if (argc != 3)
    {
        cout << "Error: Two arguments expected." << endl;
        cout << "Usage: ./loadbalancer <number of web servers> <time to run (seconds)>" << endl;
        return 1;
    }

    int numServers = atoi(argv[1]);
    int runLength = atoi(argv[2]);
    if (numServers <= 0 || runLength <= 0)
    {
        cout << "Error: Arguments must be positive integers." << endl;
        return 1;
    }

    for (int i = 0; i < 100; i++)
    {
        Request(1000).Print();
    }
}


