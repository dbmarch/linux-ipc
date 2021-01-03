#ifndef LOCAL_SENDER_H__
#define LOCAL_SENDER_H__

#include "LocalSocket.h"


class LocalSender : 
   public LocalSocket
{
public:
   LocalSender(std::string portName);

   virtual ~LocalSender();
   
   LocalSender(const LocalSender&) = delete;
   LocalSender& operator=(const LocalSender&) = delete;

   virtual bool Initialize() override;

   bool Write(const LocalSocket::Buffer &buf);

protected:

private:

};

#endif