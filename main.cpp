
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
    cout << "Number of web servers: " << numServers << endl;
    cout << "Time to run (cycles): " << runLength << endl;
    cout << "Timeout to deactivate servers: " << deactivateTimeout << endl;
    cout << "Max queue size: " << maxQueueSize << endl;
    cout << "Range for request processing time: 1-10 cycles" << endl;
    cout << "Initial queue size: " << maxQueueSize << endl;
    cout << "--- Begin Simulation ---" << endl;
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
    const int printInterval = 10;
    for (currentTime = 0; currentTime < runLength; currentTime++)
    {
        // 5% chance of generating new requests
        if (rand() % 20 == 0)
        {
            vector<Request> newRequests;
            for (int i = 0; i < rand() % (numServers * 20); i++)  // Random number of requests between 0 and numServers*20
            {
                newRequests.push_back(Request(maxProcessingTime));
            }
            lb.EnqueueRequests(newRequests);
        }

        lb.Tick();

        if (currentTime % printInterval == 0)
        {
            lb.Print();
        }
    }

    cout << "--- End of Simulation ---" << endl;
    cout << "Servers active at end: " << lb.NumActiveServers() << endl;
    cout << "Servers free at end: " << lb.NumFreeServers() << endl;
    cout << "Servers deactivated at end: " << numServers - lb.NumActiveServers() << endl;
    cout << "Total requests processed: " << lb.requestsProcessed << endl;
    cout << "Total requests dropped: " << lb.requestsDropped << endl;
    cout << "Total requests completed: " << lb.requestsCompleted << endl;
    cout << "Final queue size: " << lb.requestQueue.size() << endl;
}

