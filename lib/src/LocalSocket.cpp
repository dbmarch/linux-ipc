#include <stdio.h>
#include <unistd.h>
#include "LocalSocket.h"

//*****************************************************************************
// FUNCTION:  LocalSocket::LocalSocket
//*****************************************************************************
LocalSocket::LocalSocket(std::string portName, LocalSocket::LocalSocketType portType) :
   mName(portName),
   mType(portType)
{
   if (mTrace) printf ("%s '%s' %s\n", __func__, mName.c_str(), ToString(mType).c_str());
}

//*****************************************************************************
// FUNCTION:  LocalSocket::~LocalSocket
//*****************************************************************************
LocalSocket::~LocalSocket()
{
   Close();
}

//*****************************************************************************
// FUNCTION:  LocalSocket::Initialize
//*****************************************************************************
bool LocalSocket::Initialize()
{
   return false;
}

//*****************************************************************************
// FUNCTION:  LocalSocket::ToString
//*****************************************************************************
std::string LocalSocket::ToString (LocalSocket::LocalSocketType t)
{
   std::string rval{"?"};
   switch (t)
   {
      case LocalSocket::SENDER:     return "SENDER";
      case LocalSocket::RECEIVER:       return "RECEIVER";
   }
   return rval;
}

//*****************************************************************************
// FUNCTION:  LocalSocket::Close
//*****************************************************************************
void LocalSocket::Close ()
{
   if (mFd >= 0)
   {
      close (mFd);
   }
   mFd = -1;
}