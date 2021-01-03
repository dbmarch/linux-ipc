#ifndef LOCALSOCKET_H__
#define LOCALSOCKET_H__

#include <string>
#include <vector>


//*****************************************************************************
// CLASS:  LocalSocket
//*****************************************************************************
class LocalSocket
{
public:

   enum LocalSocketType 
   {
      SENDER,           // for Sending
      RECEIVER          //  For RECEIVING
   };

   using Buffer = std::vector<uint8_t>;

   LocalSocket(std::string portName, LocalSocketType portType);

   virtual ~LocalSocket();
   
   LocalSocket(const LocalSocket&) = delete;
   LocalSocket& operator=(const LocalSocket&) = delete;

   virtual bool Initialize();

   static std::string ToString (LocalSocketType t);


protected:
   virtual void Close ();

   std::string mName;

   LocalSocketType mType;

   int mFd{-1};

   bool mTrace{true};

private:

};

#endif