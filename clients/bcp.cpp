#include "bcp.h" 
#include "../c.h"

void bc_welcome (void * inst, const char * serv, const char * nick, const char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->welcome(serv,nick,mess);
}


void bc_message ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->message(targ,nick,user,host,mess);
}

void bc_action  ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->action(targ,nick,user,host,mess);
}

void bc_notice  ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->notice(targ,nick,user,host,mess);
}

void bc_ctcp    ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->ctcp(targ,nick,user,host,mess);
}

// Events
void bc_join( void * inst, char * targ,  char * nick,  char * user,  char * host){
  cClient *c;
  c=(cClient*)inst;
  c->join(targ,nick,user,host);
}

void bc_part( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->part(targ,nick,user,host,mess);
}

void bc_kick( void * inst, char * chan,  char * kick,  char * mess,  char * nick,  char * user,  char * host){
  cClient *c;
  c=(cClient*)inst;
  c->kick(chan,kick,mess,nick,user,host);
}

void bc_nick( void * inst, char * nick,  char * user,  char * host,  char * newn){
  cClient *c;
  c=(cClient*)inst;
  c->nick(nick,user,host,newn);
}

void bc_quit( void * inst, char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->quit(nick,user,host,mess);
}

void bc_mode( void * inst, char * nick,  char * user,  char * host,  char * mode, char * targ){
  cClient *c;
  c=(cClient*)inst;
  c->mode(nick,user,host,mode,targ);
}

// Channel Management
//void bc_channel_clear   ( void * inst, char * chann );
void bc_channel_add     ( void * inst, char * chan,  char * nick,  char * user,  char * host,  char *serv,  char *mode,  char *real){
  cClient *c;
  c=(cClient*)inst;
  c->channel_add(chan, nick, user, host, serv, mode, real);
}

// Motd
void bc_motd_begin      ( void * inst, char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->motd_begin(nick,user,host,mess);
}

void bc_motd            ( void * inst, char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->motd(nick,user,host,mess);
}

void bc_motd_end        ( void * inst, char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->motd_end(nick,user,host,mess);
}

void bc_motd_missing    ( void * inst ){
  cClient *c;
  c=(cClient*)inst;
  c->motd_missing();
}

void bc_nickchangefail  ( void * inst, char * oldn,  char * badn,  char * mess,  char * numb){
  cClient *c;
  c=(cClient*)inst;
  c->nickchangefail(oldn,badn,mess,numb);
}

void bc_unknown_message ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess){
  cClient *c;
  c=(cClient*)inst;
  c->unknown_message(targ,nick,user,host,mess);
}
