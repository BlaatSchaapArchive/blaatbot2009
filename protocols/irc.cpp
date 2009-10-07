#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bpp.h"    // BlaatSchaap Protocol Plugin
#include "irc.h"
#include "../bci.h" // BlaatSchaap Client Interface

//-----------------------------------------------------------------------------

void prot_so_init(void){
  printf("IRC protocol loaded\n");
/*  host      = NULL;
  ipv4      = NULL;
  ipv6      = NULL;
  port      = NULL;
  nick      = NULL;
  user      = NULL;
  auth      = NULL;  
  password  = NULL;
*/
}

//-----------------------------------------------------------------------------

void prot_so_fini(void){
  printf("IRC protocol unloaded\n");
/*
  if(host)      free(host);
  if(ipv4)      free(ipv4);    
  if(ipv6)      free(ipv6);
  if(port)      free(port);   
  if(nick)      free(nick);    
  if(user)      free(user);    
  if(auth)      free(auth);
  if(password)  free(password);
*/
}

//-----------------------------------------------------------------------------
int prot_init( sConnectInfo * ConnectInfo ){
	printf("prot itit \n");
  if (! ((ConnectInfo->host||ConnectInfo->ipv4||ConnectInfo->ipv6)&&(ConnectInfo->port)) ) {
    printf("Server and port are required\n");
    return false;
  }
  if (ConnectInfo->nick==NULL) {
    printf("Nick required!\n");
    return false;
  }

  if (ConnectInfo->user==NULL) {
    printf("User missing!\n");
    ConnectInfo->user = (char*) malloc (strlen(ConnectInfo->nick)+1);
    strcpy(ConnectInfo->user,ConnectInfo->nick);
  }

  return true;
}


//-----------------------------------------------------------------------------
cIRCProtocol::cIRCProtocol (cConnection *C){
  Connection = C;

  printf ("v Protocol %p \n",this);
  printf ("v Connection %p \n",this->Connection);
  printf ("v ConnectInfo %p \n",this->Connection->ConnectInfo);

}
//-----------------------------------------------------------------------------
void cIRCProtocol::join(const char *chan, const char * pass){
  char temp[666];
  if (pass)
    sprintf(temp,"JOIN %s %s\xd\xa",chan,pass);
  else 
    sprintf(temp,"JOIN %s\xd\xa",chan);
  Connection->Send(temp);
}
//-----------------------------------------------------------------------------
void cIRCProtocol::nick    (const char *nick){
  char temp[666];
  sprintf(temp,"NICK %s\xd\xa",nick);
  Connection->Send(temp);
}
//------------------------------------------------------------------------------
void cIRCProtocol::away    (const char *reason){
  char temp[666];
  sprintf(temp,"AWAY :%s\xd\xa",reason);
  Connection->Send(temp);
}
//------------------------------------------------------------------------------
void cIRCProtocol::back    (){
  Connection->Send("AWAY\xd\xa");
}
//------------------------------------------------------------------------------
void cIRCProtocol::quit    (const char *reason){
  char temp[666];
  sprintf(temp,"QUIT :%s\xd\xa",reason);
  Connection->Send(temp);
}
//------------------------------------------------------------------------------
void cIRCProtocol::privmsg    (const char *target, const char *message){
  char temp[666];
  sprintf(temp,"PRIVMSG %s %s\xD\xA",target,message);    
  Connection->Send(temp);
}
//------------------------------------------------------------------------------
void cIRCProtocol::notice    (const char *target, const char *message){
  char temp[666];
  sprintf(temp,"NOTICE %s %s\xD\xA",target,message);
  Connection->Send(temp);
}
//------------------------------------------------------------------------------
void cIRCProtocol::action    (const char *target, const char *message){
  char temp[666];
  sprintf(temp,"PRIVMSG %s \x01\x41\x43TION %s\x1\xD\xA",target,message);    
  Connection->Send(temp);
}
//------------------------------------------------------------------------------
void cIRCProtocol::mode    (const char *target, const char *mode){
  char temp[666];
	sprintf(temp,"MODE %s %s\xd\xa",target,mode);
  Connection->Send(temp);
}
//------------------------------------------------------------------------------
void cIRCProtocol::raw    (const char *raw){
  Connection->Send(raw);
}
//------------------------------------------------------------------------------
void * ReceiveThreadWrapper (void * C){
  cIRCProtocol *c = (cIRCProtocol*) C;
  c->ReceiveThread();
}
//------------------------------------------------------------------------------
void cIRCProtocol::StartThread (){
  pthread_create(&receivethread, NULL, ReceiveThreadWrapper, (void*)this); 
}
//------------------------------------------------------------------------------

void cIRCProtocol::ReceiveThread (){
//  printf("cIRCProtocol::ReceiveThread\n");//debug?
//  printf("Connection: %p \n",Connection);
  char * data;
  while (data = Connection->ReceiveLn()) {
  printf("Receive..\n");//debug?
    Process(data);
    free(data);
  }
  printf("No more data to receive.... receive Thead Stopping....\n");
}
//------------------------------------------------------------------------------
//void   cIRCProtocol::SendLogin(char * user, char * nick, char * pass) {
void   cIRCProtocol::SendLogin() {
  char * user = Connection->ConnectInfo->user; 
  char * nick = Connection->ConnectInfo->nick;  
  char * pass = Connection->ConnectInfo->pass;

  char temp[666];
  sprintf(temp,"USER %s host server :BlaatSchaap Coding Projects 2009 IRC\xd\xa",user);
  raw(temp);  
  if(pass) {
    sprintf(temp,"PASS %s\xd\xa",pass);
    raw(temp);  
  }
  this->nick(nick);
}
//------------------------------------------------------------------------------
void   cIRCProtocol::SendAuth      (){
  char * auth = Connection->ConnectInfo->auth;
  if (auth) raw(auth);  
}

//------------------------------------------------------------------------------
void   cIRCProtocol::SplitUserNickHost (char * data, char * &user, char * &nick, char * &host){
  nick = strtok (data+1,"!");
  user = strtok (NULL,"@");
  host = strtok (NULL,"");
}

//------------------------------------------------------------------------------
void   cIRCProtocol::Process      (char * data){
  char * protraw  = NULL;  
  char * userraw  = NULL; 
  char * user     = NULL;
  char * nick     = NULL; 
  char * host     = NULL;  
  char * protdata[25]; int protsize=0;
  userraw = strstr(data," :");
  if (userraw) {
    *(userraw++)=0;
    *(userraw++)=0;
  }
  protraw = data;

  protdata[protsize] = strtok(protraw," ");
  while (protdata[protsize++]) {
    protdata[protsize] = strtok(NULL," ");
  }

  SplitUserNickHost(protraw,user,nick,host);
  
  if (strcasecmp(protdata[0],"PING")==0){
    printf("PINGPONG %s\n",userraw);
    Connection->Send("PONG :");
    if (userraw) Connection->Send(userraw);
    Connection->Send("\r\n");
  } else
  
  if (strcasecmp(protdata[0],"ERROR")==0){
    Connection->Disconnect();
  } else
  
  if (protdata[1]) {
    if (strcasecmp(protdata[1],"PRIVMSG")==0){
      char * target = protdata[2];
      if (userraw) {
        if (userraw[0]==0x01) {
          if (strlen(userraw)>6) {
            if (strncasecmp(userraw+1,"ACTION",6)==0) {
              if(userraw[strlen(userraw)-1]==0x01) {
                //a correct ACTION
                bc_action(Client, target, nick, user, host, userraw);
              } else {
              //a malformed ACTION
                bc_action(Client, target, nick, user, host, userraw);
                printf("Malformed ACTION received!! Parsing as real ACTION anyways\n");
              } 
            } else {
            // CTCP, not action, longer then 6
              bc_ctcp(Client, target, nick, user, host, userraw);
            }
          } else {
          // CTCP shorter then 6
            bc_ctcp(Client, target, nick, user, host, userraw);
          }
        } else {
        // PRIVMSG
          bc_message(Client, target, nick, user, host, userraw);
        }
      }
    } else 
    if (strcasecmp(protdata[1],"NOTICE")==0){  
      char * target = protdata[2];
      if (userraw) {
        //NOTICE
        bc_notice(Client, target, nick, user, host, userraw);
      }
    } else
    if (strcasecmp(protdata[1],"JOIN")==0){
      bc_join(Client, userraw, nick, user, host);
    } else
    if (strcasecmp(protdata[1],"PART")==0){
      char * channel = protdata[2];
      bc_part(Client, channel, nick, user, host, userraw);
    } else
    if (strcasecmp(protdata[1],"QUIT")==0){
      bc_quit(Client, nick, user, host, userraw);
    } else
    if (strcasecmp(protdata[1],"NICK")==0){
      bc_nick(Client, nick, user, host, userraw);
    } else
    if (strcasecmp(protdata[1],"KICK")==0){
      char * channel = protdata[2];
      char * kicked  = protdata[3];
      bc_kick(Client, channel, kicked, userraw, nick, user, host);
    } else
    if (strcasecmp(protdata[1],"MODE")==0){
      char * target = protdata[2];
      char * mode   = protdata[3];
      bc_mode(Client, nick, user, host, mode, target);
    } else
    if (strcasecmp(protdata[1], RPL_WELCOME )==0){ 
      char * newnick = protdata[2];
      char * mess = userraw;
      bc_welcome (Client, nick,newnick,mess);
    } else
    if (strcasecmp(protdata[1], RPL_MOTDSTART )==0){ 
      bc_motd_begin (Client, nick,user,host,userraw);
    } else
    if (strcasecmp(protdata[1], RPL_MOTD )==0){ 
      bc_motd_begin (Client, nick,user,host,userraw);
    } else
    if (strcasecmp(protdata[1], RPL_ENDOFMOTD )==0){ 
      bc_motd_end (Client, nick,user,host,userraw);
    } else
    if (strcasecmp(protdata[1], ERR_NOMOTD )==0){ 
      bc_motd_missing (Client);
    } else
    if (strcasecmp(protdata[1], RPL_WHOREPLY )==0){ 
      char * chan    = protdata[3];
      char * user    = protdata[4];
      char * host    = protdata[5];
      char * serv    = protdata[6];
      char * nick    = protdata[7];
      char * mode    = protdata[8];
      bc_channel_add(Client, chan, nick, user, host , serv , mode , userraw);
    } else {
      //unk with at least one parameter, shoud be triggered a log
      //*bc_unknown_message )(const char * targ, const char * nick, const char * user, const char * host, const char * mess);
      bc_unknown_message (Client, protdata[2], nick, user, host, userraw);
    }
  } else {
    //unk (only one parameter??? should not happen I guess???) 
    bc_unknown_message (Client, protdata[2], nick, user, host, userraw);
  }
}
//------------------------------------------------------------------------------

