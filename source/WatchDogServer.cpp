#pragma hdrstop
#include "WatchDogServer.h"
//---------------------------------------------------------------------------


WatchDogServer::WatchDogServer()
:
mIP(""),
mIP_MIB("")
{

}

void WatchDogServer::setIP(const string& ip)
{
	mIP = ip;
}
