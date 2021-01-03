#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <errno.h>

#include "LocalReceiver.h"

//******************************************************************************
// FUNCTION:  LocalReceiver::LocalReceiver
//******************************************************************************
LocalReceiver::LocalReceiver(std::string name) :
   LocalSocket(name,LocalSocket::RECEIVER )
{
   if (mTrace) printf ("%s '%s' %s\n", __func__, mName.c_str(), ToString(mType).c_str());

}

//******************************************************************************
// FUNCTION:  LocalReceiver::~LocalReceiver
//******************************************************************************
LocalReceiver::~LocalReceiver()
{
}

//******************************************************************************
// FUNCTION:  LocalReceiver::Initialize
//******************************************************************************
bool LocalReceiver::Initialize()
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
 
   if (bind(mFd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
   {
     printf ("%s bind error '%s'\n", __func__, strerror(errno));
     Close();
     return false;
   }
   if (listen(mFd, 5) == -1) 
   {
     printf ("%s listen error '%s'\n", __func__, strerror(errno));
     Close();
     return false;
   }

   mThread = std::thread(&LocalReceiver::ReceiveThread, this);
  return (true);
}

//******************************************************************************
// FUNCTION:  LocalReceiver::~LocalReceiver
//******************************************************************************
void LocalReceiver::Close()
{
  mRunning  = false;
  if (mThread.joinable()) {
    mThread.join();
  }
  LocalSocket::Close();

}

//******************************************************************************
// FUNCTION:  LocalReceiver::ReceiveThread
//******************************************************************************
void LocalReceiver::ReceiveThread() {
  char buf[4096];

  mRunning = true;
  printf ("Rx thread running\n");

  int cl = -1;
  while (mRunning)  {

    if (cl == -1) {
      cl = accept(mFd, nullptr, nullptr);
      if ( cl == -1) {
        perror("accept error");
        continue;
      }
    }

    if (cl >= 0) {
     int rc = read(cl, buf, sizeof(buf));
     if (rc  > 0) {
       Callback(buf, rc);
     } else if (rc == -1) {
       printf ("Read error %s\n", strerror(errno));
       sleep(1);
     }

    }
  }
  printf ("Receive Thread shutting down\n");
}

