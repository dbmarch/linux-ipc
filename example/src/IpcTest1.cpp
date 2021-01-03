#include <signal.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include "StringIpc.h"

static bool serverRunning{true};


//*****************************************************************************
// FUNCTION:  sigintHandler
//*****************************************************************************
void sigintHandler (int sigNum) {
  signal (SIGINT, sigintHandler);
  serverRunning = false;
}

//*****************************************************************************
// FUNCTION:  main
//*****************************************************************************
int main(int argc, char* argv[])
{
  printf ("IpcTest\n");
  bool initialized{false};

  StringReceiver rx("test1");
  StringSender   tx("test2");

  rx.Initialize();

  std::string msg("Hello from #1\n");
  
  while (serverRunning) {
    if (!initialized) {
      tx.Initialize();
      initialized = true;
    }
    sleep(1);
    if (initialized) {
      tx.Write(msg);
    }
  };

  printf ("%s exiting\n", argv[0]);

  return 0;
}