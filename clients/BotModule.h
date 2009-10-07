#ifndef _BLAAT_BOT_MODULE_SUPPORT_
#define _BLAAT_BOT_MODULE_SUPPORT_

#include "bot.h"

class cBotModule{
  private:
    void *lib;
    char *libname;
    cBot *bot;
    bool  (*channel_message)  ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  (*channel_notice)   ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  (*channel_action)   ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  (*channel_ctcp)     ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess);

    bool  (*private_message)( const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  (*private_notice) ( const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  (*private_action) ( const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  (*private_ctcp)   ( const char* nick,  const char* user,  const char* host,  const char* mess);

    int (*bm_reg) (int p, void * proc);
  
  public:
    cBotModule( const char * name, cBot *b);
    ~cBotModule();

    bool  ChannelMessage  ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  ChannelNotice   ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  ChannelAction   ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  ChannelCtcp     ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess);

    bool  PrivateMessage( const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  PrivateNotice ( const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  PrivateAction ( const char* nick,  const char* user,  const char* host,  const char* mess);
    bool  PrivateCtcp   ( const char* nick,  const char* user,  const char* host,  const char* mess);

};

#ifdef __cplusplus
/* If this is a C++ compiler, use C linkage */
extern "C" {
#endif
/* These functions get C linkage */

void bb_nick   (void * inst, const char *nick);
void bb_ctcp   (void * inst, const char *target, const char *message);
void bb_privmsg(void * inst, const char *target, const char *message);
void bb_notice (void * inst, const char *target, const char *message);
void bb_action (void * inst, const char *target, const char *message);
void bb_mode   (void * inst, const char *target, const char *mode);
void bb_away   (void * inst, const char *reason);
void bb_back   (void * inst);
void bb_quit   (void * inst, const char *reason);
void bb_raw    (void * inst, const char *raw);


#ifdef __cplusplus
/* If this is a C++ compiler, end C linkage */
}
#endif



#endif 
