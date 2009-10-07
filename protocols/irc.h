#ifndef _BLAAT_PROTOCOL_PLUGIN_IRC_
#define _BLAAT_PROTOCOL_PLUGIN_IRC_
#include <pthread.h>
#include "bpp.h"
#include "irc_nummeric.h"
#include "../c.h"
//class cConnection;

class cIRCProtocol : public cProtocol {
  private:

  pthread_t receivethread;
  void Process           (char * data);
  void SplitUserNickHost (char * data, char * &user, char * &nick, char * &host);
  public:
  cIRCProtocol (cConnection *C);
  void   StartThread ();
  void   ReceiveThread ();
  void   SendLogin     ();
  void   SendAuth      ();

  void join       (const char *nick, const char *pass=NULL);
  
  void nick   (const char *nick);
  void privmsg(const char *target, const char *message);
  void notice (const char *target, const char *message);
  void action (const char *target, const char *message);
  void mode   (const char *target, const char *mode);
  void away   (const char *reason);
  void back   ();
  void quit   (const char *reason);
  void raw    (const char *raw);


};

#endif
