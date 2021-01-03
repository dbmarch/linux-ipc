#ifndef STRINGIPC_H__
#define STRINGIPC_H__

#include "LocalSender.h"
#include "LocalReceiver.h"


class StringSender : public LocalSender {

public:
  StringSender(const char* name) :
   LocalSender(name){};

  void Write(const std::string &msg) {
    LocalSocket::Buffer buf{msg.begin(), msg.end()};
    LocalSender::Write(buf);
  }

};

class StringReceiver : public LocalReceiver {
public:
  StringReceiver(const char* name) :
   LocalReceiver(name){};

  virtual ~StringReceiver(){}

  virtual void Callback (void * payload, int count) override { printf ("RX CB %s\n", (char*) payload); }
   

};


#endif