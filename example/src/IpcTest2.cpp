#include <stdio.h>
#include <string>
#include <signal.h>
#include <unistd.h>

#include "StringIpc.h"


static bool serverRunning{true};

//*****************************************************************************
// FUNCTION:  main
//*****************************************************************************
int main(int argc, char*argv[])
{
  printf ("IpcTest1\n");
  bool initialized{false};

  StringReceiver rx("test2");
  StringSender   tx("test1");

  rx.Initialize();

  std::string msg("Hello from #2\n");


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