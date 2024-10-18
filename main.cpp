
#include <iostream>
#include "loadbalancer.h"
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
        cout << "Usage: ./loadbalancer <number of web servers> <time to run (cycles)>" << endl;
        return 1;
    }

    int numServers = atoi(argv[1]);
    int runLength = atoi(argv[2]);
    if (numServers <= 0 || runLength <= 0)
    {
        cout << "Error: Arguments must be positive integers." << endl;
        return 1;
    }

    /////// Initialize Load Balancer //////
    int maxQueueSize = numServers * 100;
    int deactivateTimeout = 10;
    LoadBalancer lb(numServers, deactivateTimeout, maxQueueSize);
    lb.Print();

    /////// Generate Initial Requests //////
    srand(time(NULL));
    int maxProcessingTime = 10;

    vector<Request> initialRequests;
    for (int i = 0; i < maxQueueSize; i++)
    {
        initialRequests.push_back(Request(maxProcessingTime));
    }
    lb.EnqueueRequests(initialRequests);

    /////// Run Load Balancer //////
    int currentTime;
    for (currentTime = 0; currentTime < runLength; currentTime++)
    {
        lb.Tick();

        if (currentTime % 10 == 0)
        {
            lb.Print();
        }
    }

    cout << "--- End of Simulation ---" << endl;
    lb.Print();

}

