#ifndef _BLAAT_IRC_BOT_
#define _BLAAT_IRC_BOT_
#include "bcp.h"
#include "../c.h"
#include <vector>
using namespace std;

class cIRCuser;
class cIRCchannel;
class cBotAuth;
class cBotModule;

class cBot : public cClient {
private: 
  vector <cIRCchannel*> Channels;  //channels the bot has joined
  vector <cIRCuser*>    Users;     //users speaking in PM or have global privileges 
//  vector <cBotAuth*>    Auth;      //authorisation modules
  vector <cBotModule*>    Mods;      //authorisation modules
public:
  void JoinChannels();
  cBot (cProtocol * P);
  void welcome(const char * serv, const char * nick, const char * mess);

// Messages
  void message ( char * targ,  char * nick,  char * user,  char * host,  char * mess);
  void action  ( char * targ,  char * nick,  char * user,  char * host,  char * mess);
  void notice  ( char * targ,  char * nick,  char * user,  char * host,  char * mess);
  void ctcp    ( char * targ,  char * nick,  char * user,  char * host,  char * mess);
  
// Events
  void join( char * targ,  char * nick,  char * user,  char * host);
  void part( char * targ,  char * nick,  char * user,  char * host,  char * mess);
  void kick( char * chan,  char * kick,  char * mess,  char * nick,  char * user,  char * host);
  void nick( char * nick,  char * user,  char * host,  char * newn);
  void quit( char * nick,  char * user,  char * host,  char * mess);
  void mode( char * nick,  char * user,  char * host,  char * mode,     char * targ);

// Channel Management
  void channel_clear   ( char * chann);
  void channel_add     ( char * chann,  char * nick,  char * user,  char * host,  char *serv,  char *mode,  char *real);
  
// Motd
  void motd_begin      ( char * nick,  char * user,  char * host,  char * mess);
  void motd            ( char * nick,  char * user,  char * host,  char * mess);
  void motd_end        ( char * nick,  char * user,  char * host,  char * mess);
  void motd_missing    ();
  
  void nickchangefail  ( char * oldn,  char * badn,  char * mess,  char * numb);
  void unknown_message ( char * targ,  char * nick,  char * user,  char * host,  char * mess);



};


class cIRCuser{
    public:
        cIRCuser();
       ~cIRCuser();
        char *nick;
        char *user;
        char *host;
        char *serv;
        char *mode;
        char *real;

        bool isChannelOP;
        bool isNetOP;
        bool isAway;

        char * awayReason;
        int  lines;
        vector <char *> oldnicks;
        char userlevel;
        time_t lasttime;
        char lasttype;
        char *lastsaid;

        FILE * logfile;
};



class cIRCchannel{
    public:
   cIRCchannel();
	~cIRCchannel();
	char *channel;
  char *topic;
  char *mode;
  vector <cIRCuser *> users;
  FILE * logfile;
};




#endif
