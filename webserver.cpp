/**
 * @file webserver.cpp
 * @brief Implementation of the WebServer class
 */

#include "webserver.h"

WebServer::WebServer(int deactivateTimeout)
: freeAtTime(-deactivateTimeout - 1), deactivateTimeout(deactivateTimeout)
{

}

void WebServer::ProcessRequest(Request request, int currentTime)
{
    freeAtTime = currentTime + request.processingTime;
}

bool WebServer::IsFree(int currentTime)
{
    return currentTime >= freeAtTime;
}

bool WebServer::IsActivated(int currentTime)
{
    return currentTime < freeAtTime + deactivateTimeout;
}

void WebServer::Print(int currentTime)
{
    cout << "Free at: " << freeAtTime << " (" << (IsFree(currentTime) ? "Free" : "Busy") << " (" << (IsActivated(currentTime) ? "Active" : "Deactivated") << ")" << endl;
}

