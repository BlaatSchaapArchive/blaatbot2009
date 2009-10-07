#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include "bot.h"
#include "bcp.h"
#include "BotModule.h"
#include "../c.h"
#include "../xmlParser.h"

  cBot * client;
//-----------------------------------------------------------------------------

void __attribute__ ((constructor)) bpp_init(void){
  printf("Loading client library...\n");
}

//-----------------------------------------------------------------------------

void __attribute__ ((destructor)) bpp_fini(void){
  printf("Unloading client library...\n");
}

//-----------------------------------------------------------------------------

char * bc_id(void){
  return (char*)"blaat";
}

//-----------------------------------------------------------------------------
void * bc_init (void * P){
	printf("Init Client Lib\n");
  return (void*) new cBot ( (cProtocol*)P );

}

//-----------------------------------------------------------------------------

cBot::cBot(cProtocol * P){
  Protocol = P;
  mynick = NULL;
  myserv = NULL;
  printf("test %s \n",Protocol->Connection->ConnectInfo->nick);
  XMLNode *t =  (XMLNode*)(Protocol->Connection->ConnectInfo->xml);
  xml = *t;
  
  printf("loading modules\n");
  XMLNode ModuleToLoad = xml.getChildNode("module");
  if (ModuleToLoad.isEmpty()) printf("No Modules In Config\n");
  while ( !ModuleToLoad.isEmpty() ) {
    cBotModule *m = new cBotModule(ModuleToLoad.getText(),this);
    Mods.push_back(m);
    ModuleToLoad.deleteNodeContent();  
    ModuleToLoad = xml.getChildNode("module");
  }
  printf("loaded all modules in config!\n"); 


}

//-----------------------------------------------------------------------------
void cBot::welcome(const char * serv, const char * nick, const char * mess){
  if(nick) {
    mynick = (char*)malloc(strlen(nick)+1);
    strcpy(mynick,nick);
  }
  if (serv){
    myserv = (char*)malloc(strlen(serv)+1);
    strcpy(myserv,serv);
  }
}
//-----------------------------------------------------------------------------

void cBot::message (char * targ, char * nick, char * user, char * host, char * mess){
  if (targ && mynick) if (strcasecmp(targ,mynick)){
    printf("channel message\n");
    for (int i = 0  ; i < Mods.size() ; i++ ) {
      if (Mods[i]->ChannelMessage(targ,nick,user,host,mess)) break;  
    }
  } else {
  printf("private message\n");
    for (int i = 0  ; i < Mods.size() ; i++ ) {
      if (Mods[i]->PrivateMessage(nick,user,host,mess)) break;  
    }
  }
}
//-----------------------------------------------------------------------------
void cBot::action  ( char * targ,  char * nick,  char * user,  char * host,  char * mess){
if (targ && mynick) if (strcasecmp(targ,mynick)){
  printf("channel action \n");
  } else {
  printf("private action \n");
  }
}
//-----------------------------------------------------------------------------
void cBot::notice  ( char * targ,  char * nick,  char * user,  char * host,  char * mess){
  printf("targ : %s \n",targ);
  if (targ && mynick) if (strcasecmp(targ,mynick)){
  printf("channel notice \n");
  } else {
  printf("private notice \n");
  }
}
//-----------------------------------------------------------------------------
void cBot::ctcp    ( char * targ,  char * nick,  char * user,  char * host,  char * mess){
if (targ && mynick) if (strcasecmp(targ,mynick)){
  printf("channel ctcp   \n");
  } else {
  printf("private ctcp   \n");
  }
}
//-----------------------------------------------------------------------------
void cBot::join( char * targ,  char * nick,  char * user,  char * host){
  printf("join: ");
  if (targ && nick && user && host) {
    printf("%s (%s@%s) joined %s\n",nick,user,host,targ);
  }
}
//-----------------------------------------------------------------------------
void cBot::part( char * targ,  char * nick,  char * user,  char * host,  char * mess){
  printf("part: ");
  if (targ && nick && user && host) {
    printf("%s (%s@%s) parted %s",nick,user,host,targ);
    if (mess) printf (" reason : %s",mess); 
    printf("\n");
  }
}
//-----------------------------------------------------------------------------
void cBot::kick( char * chan,  char * kick,  char * mess,  char * nick,  char * user,  char * host){
  printf("kick: ");
}
//-----------------------------------------------------------------------------
void cBot::nick( char * nick,  char * user,  char * host,  char * newn){
    if (newn && nick && user && host) {
      printf("%s (%s@%s) changed nick to%s",nick,user,host,newn);
    }
}
//-----------------------------------------------------------------------------
void cBot::quit( char * nick,  char * user,  char * host,  char * mess){
  printf("quit: ");
}
//-----------------------------------------------------------------------------
void cBot::mode( char * nick,  char * user,  char * host,  char * mode,     char * targ){
  printf("mode: ");
}
//-----------------------------------------------------------------------------
void cBot::channel_clear   ( char * chann){
}
//-----------------------------------------------------------------------------
void cBot::channel_add     ( char * chann,  char * nick,  char * user,  char * host,  char *serv,  char *mode,  char *real){
}
//-----------------------------------------------------------------------------
void cBot::motd_begin      ( char * nick,  char * user,  char * host,  char * mess){
}
//-----------------------------------------------------------------------------
void cBot::motd            ( char * nick,  char * user,  char * host,  char * mess){
}
//-----------------------------------------------------------------------------
void cBot::motd_end        ( char * nick,  char * user,  char * host,  char * mess){
  printf("motd_end\n");
  JoinChannels();
}
//-----------------------------------------------------------------------------
void cBot::motd_missing    (){
  JoinChannels();
}
//-----------------------------------------------------------------------------
void cBot::nickchangefail  ( char * oldn,  char * badn,  char * mess,  char * numb){
}
//-----------------------------------------------------------------------------
void cBot::unknown_message ( char * targ,  char * nick,  char * user,  char * host,  char * mess){
  printf("Unimplemented Message Received! " );
  printf("%s %s %s %s %s\n", targ, nick, user, host, mess);

}
//-----------------------------------------------------------------------------
void cBot::JoinChannels(){
  printf("joining channels\n");
  XMLNode ChannelToJoin = xml.getChildNode("channel");
  if (ChannelToJoin.isEmpty()) printf("No Channels In COnfig\n");
  while ( !ChannelToJoin.isEmpty() ) {
    Protocol->join(ChannelToJoin.getText());
    ChannelToJoin.deleteNodeContent();  
    ChannelToJoin = xml.getChildNode("channel");
  }
  printf("joined all channels in config!\n"); 
}
