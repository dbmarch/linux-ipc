#include <stdio.h>
#include <string>
#include "LocalReceiver.h"
#include "LocalSender.h"



//*****************************************************************************
// FUNCTION:  main
//*****************************************************************************
int main()
{
  printf ("IpcTest\n");

  LocalReceiver rx("test1");
  LocalSender   tx("test1");

  rx.Initialize();
  tx.Initialize();

  std::string msg("Hello\n");
  LocalSocket::Buffer b{msg.begin(), msg.end()};

  tx.Write(b);
  return 0;
}