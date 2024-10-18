/**
 * @file loadbalancer.cpp
 * @brief Implementation of the LoadBalancer class
 */

#include "loadbalancer.h"

LoadBalancer::LoadBalancer(int numServers, int deactivateTimeout, int maxQueueSize)
: servers(numServers, WebServer(deactivateTimeout)), currentTime(0), requestsProcessed(0), requestsDropped(0), requestsCompleted(0), maxQueueSize(maxQueueSize)
{
    
}

void LoadBalancer::EnqueueRequests(vector<Request> requests)
{
    int numDropped = 0;
    for (Request request : requests)
    {
        if ((int) requestQueue.size() < maxQueueSize)
        {
            requestQueue.push(request);
        }
        else
        {
            numDropped++;
        }
    }
    requestsDropped += numDropped;

    if (requests.size() - numDropped > 0)
    {
        printf("Time: %6d - Enqueued %d requests.\n", currentTime, (int) requests.size() - numDropped);
    }
    if (numDropped > 0)
    {
        printf("Time: %6d - Dropped %d requests.\n", currentTime, numDropped);
    }
}

void LoadBalancer::Tick()
{
    currentTime++;
    vector<pair<int, WebServer*> > freeServers;

    for (WebServer &server : servers)
    {
        if (server.freeAtTime == currentTime)
        {
            requestsCompleted++;
        }
        if (server.IsFree(currentTime))
        {
            freeServers.push_back(pair<int, WebServer*>(server.freeAtTime, &server));
        }
    }

    sort(freeServers.begin(), freeServers.end(), std::greater<pair<int, WebServer*> >());

    for (pair<int, WebServer*>& freeServer : freeServers)
    {
        if (!requestQueue.empty())
        {
            Request request = requestQueue.front();
            requestQueue.pop();
            freeServer.second->ProcessRequest(request, currentTime);
            requestsProcessed++;
        }
    }
}

int LoadBalancer::NumActiveServers()
{
    int count = 0;
    for (WebServer server : servers)
    {
        if (server.IsActivated(currentTime))
        {
            count++;
        }
    }
    return count;
}

int LoadBalancer::NumFreeServers()
{
    int count = 0;
    for (WebServer server : servers)
    {
        if (server.IsFree(currentTime))
        {
            count++;
        }
    }
    return count;
}

void LoadBalancer::Print()
{
    printf("Time: %6d - Currently-Processing Servers: %3d - Active Servers: %3d - Deactivated Servers: %3d - Queue Size: %5d - Requests Processed: %6d - Requests Dropped: %6d - Requests Completed: %6d\n", currentTime, (int) servers.size() - NumFreeServers(), NumActiveServers(), (int) servers.size() - NumActiveServers(), (int) requestQueue.size(), requestsProcessed, requestsDropped, requestsCompleted);
}

