#ifndef LOCAL_RECEIVER_H__
#define LOCAL_RECEIVER_H__

#include "LocalSocket.h"


class LocalReceiverClient
{
public:
   LocalReceiverClient () =default;
   virtual ~LocalReceiverClient () =default;
   
   // Change to a  template later.
   virtual void Callback (void * payload, int count) { printf ("LocalReceiverClient Received %d bytes\n", count); };
};

class LocalReceiver : 
   public LocalSocket , 
   public LocalReceiverClient
{
public:
   LocalReceiver(std::string portName);
   virtual ~LocalReceiver();
   
   LocalReceiver(const LocalReceiver&) = delete;
   LocalReceiver& operator=(const LocalReceiver&) = delete;

   virtual bool Initialize() override;

protected:


private:
};

#endif