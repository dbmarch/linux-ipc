#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include "LocalSender.h"

//******************************************************************************
// FUNCTION:  LocalSender::LocalSender
//******************************************************************************
LocalSender::LocalSender(std::string name) :
   LocalSocket(name, LocalSocket::SENDER)
{
   if (mTrace) printf ("%s '%s' %s\n", __func__, mName.c_str(), ToString(mType).c_str());
}

//******************************************************************************
// FUNCTION:  LocalSender::~LocalSender
//******************************************************************************
LocalSender::~LocalSender()
{
}

//******************************************************************************
// FUNCTION:  LocalSender::Initialize
//******************************************************************************
bool LocalSender::Initialize()
{
   struct sockaddr_un addr;
  
   if ( (mFd = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1) 
   {
     if (mTrace) printf ("%s Error Opening Socket '%s'\n", __func__, strerror(errno));
     return false;
   }
   if (mTrace) printf ("%s socket opened\n", __func__);
   memset(&addr, 0, sizeof(addr));
   addr.sun_family = AF_UNIX;
   *addr.sun_path = '\0';
   strncpy(addr.sun_path+1, mName.c_str(), sizeof(addr.sun_path)-2);

   if (connect(mFd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
   {
      if (mTrace) printf ("%s connect failed '%s'\n", __func__, strerror(errno));
      Close();
      return false;
   }

   return true;
}


//******************************************************************************
// FUNCTION:  LocalSender::Initialize
//******************************************************************************
bool LocalSender::Write(LocalSocket::Buffer buf)
{
   int sz  = buf.size();
   
   int rc  = write(mFd, buf.data(), sz);
   
   if (rc == -1) 
   {
      if (mTrace) printf ("%s ERROR '%s'\n", __func__, strerror(errno));
      return false;
   }
   else if ( rc != sz)
   {
      if (mTrace) printf ("%s %d/%d bytes written\n", __func__, rc, sz);
      return false;
   }
   return true;
}