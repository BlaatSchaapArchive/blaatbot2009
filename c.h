#ifndef _BLAAT_CLASSES_
#define _BLAAT_CLASSES_
#include <vector>
#include "xmlParser.h"

class cProtocol;
class cClient;
class cBot;
class cConnection;
struct sConnectInfo;

using namespace std;

class cProtocol{
  protected:  
  cClient * Client;  
 
  public:
  cConnection *Connection;

  void SetClient (cClient *C) {Client = C;};

  virtual void   StartThread ()=0;
  virtual void   ReceiveThread ()=0;
  virtual void   SendLogin     ()=0;
  virtual void   SendAuth      ()=0;

  virtual void join       (const char *nick, const char *pass=NULL)=0;
  
  virtual void nick   (const char *nick)=0;
  virtual void privmsg(const char *target, const char *message)=0;
  virtual void notice (const char *target, const char *message)=0;
  virtual void action (const char *target, const char *message)=0;
  virtual void mode   (const char *target, const char *mode)=0;
  virtual void away   (const char *reason)=0;
  virtual void back   ()=0;
  virtual void quit   (const char *reason)=0;
  virtual void raw    (const char *raw)=0;

  sConnectInfo * GetConnectInfo();

};


struct sConnectInfo {
  char * host; 
  char * ipv4; 
  char * ipv6; 
  int    port; 
  char * nick; 
  char * user; 
  char * auth;
  char * pass;
  char * real;
  void * xml;
};


class cClient {
  protected: 
  char * mynick;
  char * myserv;
  XMLNode xml;
  public:
  cProtocol *Protocol;
//  cClient (cProtocol * P);
  cConnection *Connection;
virtual  void welcome(const char * serv, const char * nick, const char * mess)=0;
  
// Messages
virtual  void message ( char * targ,  char * nick,  char * user,  char * host,  char * mess)=0;
virtual  void action  ( char * targ,  char * nick,  char * user,  char * host,  char * mess)=0;
virtual  void notice  ( char * targ,  char * nick,  char * user,  char * host,  char * mess)=0;
virtual  void ctcp    ( char * targ,  char * nick,  char * user,  char * host,  char * mess)=0;
  
// Events
  virtual void join( char * targ,  char * nick,  char * user,  char * host)=0;
    virtual void part( char * targ,  char * nick,  char * user,  char * host,  char * mess)=0;
  virtual   void kick( char * chan,  char * kick,  char * mess,  char * nick,  char * user,  char * host)=0;
  virtual   void nick( char * nick,  char * user,  char * host,  char * newn)=0;
  virtual   void quit( char * nick,  char * user,  char * host,  char * mess)=0;
  virtual   void mode( char * nick,  char * user,  char * host,  char * mode,     char * targ)=0;

// Channel Management
    virtual void channel_clear   ( char * chann)=0;
  virtual   void channel_add     ( char * chann,  char * nick,  char * user,  char * host,  char *serv,  char *mode,  char *real)=0;
  
// Motd
  virtual   void motd_begin      ( char * nick,  char * user,  char * host,  char * mess)=0;
    virtual void motd            ( char * nick,  char * user,  char * host,  char * mess)=0;
  virtual   void motd_end        ( char * nick,  char * user,  char * host,  char * mess)=0;
  virtual   void motd_missing    ()=0;
  
  virtual   void nickchangefail  ( char * oldn,  char * badn,  char * mess,  char * numb)=0;
    virtual void unknown_message ( char * targ,  char * nick,  char * user,  char * host,  char * mess)=0;

};



class cConnection {
  private:
    int Socket;
    cProtocol* Protocol;
    cClient*   Client;
  public: 
    sConnectInfo *ConnectInfo;
    cConnection (sConnectInfo *CI);
    ~cConnection ();
    int Connect();
    int Disconnect();
    int Send(const char *);
    char * ReceiveLn();
    char * Receive0();
};

#endif
