#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "BotModule.h"
#include "../fptype.h"



cBotModule::cBotModule( const char * name, cBot * b){
  bot = b;
  char * path = getcwd(NULL,0);
  char * libname;
  libname = (char*) malloc (strlen(name) + strlen(path)+ 30);
  sprintf(libname,"%s/clients/botmodules/lib%s.so",path,name);
    printf("loading %s \n",libname);
  lib = dlopen(libname, RTLD_LAZY);
  if (lib) {
    free(libname);
    free(path);
    libname = NULL;
    path = NULL;
    channel_message = (t_f_b_5pchar)dlsym(lib, "channel_message"); 
    if(!channel_message) printf("%s\n",dlerror());;
    channel_notice  = (t_f_b_5pchar)dlsym(lib, "channel_notice"); 
    if(!channel_notice) printf("%s\n",dlerror());;
    channel_action  = (t_f_b_5pchar)dlsym(lib, "channel_action"); 
    if(!channel_action) printf("%s\n",dlerror());;
    channel_ctcp    = (t_f_b_5pchar)dlsym(lib, "channel_ctcp"); 
    if(!channel_ctcp) printf("%s\n",dlerror());;

    private_message = (t_f_b_4pchar)dlsym(lib, "private_message"); 
    if(!private_message) printf("%s\n",dlerror());;
    private_notice  = (t_f_b_4pchar)dlsym(lib, "private_message"); 
    if(!private_notice) printf("%s\n",dlerror());;
    private_action  = (t_f_b_4pchar)dlsym(lib, "private_message"); 
    if(!private_action) printf("%s\n",dlerror());;
    private_ctcp    = (t_f_b_4pchar)dlsym(lib, "private_message"); 
    if(!private_ctcp) printf("%s\n",dlerror());
    bm_reg          = (t_f_i_i_vp)dlsym(lib, "bm_reg"); 
    if(!private_ctcp) printf("%s\n",dlerror());
  } else printf("%s\n",dlerror());
  bm_reg(0,(void*) bot);
  bm_reg(20,(void*) bb_privmsg);
}

cBotModule::~cBotModule(){
  dlclose(lib);
}



    bool  cBotModule::ChannelMessage  ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess){
      if (channel_message) return channel_message(chan,nick,user,host,mess); else return false;
    };
    bool  cBotModule::ChannelNotice   ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess){
      if (channel_notice) return channel_notice(chan,nick,user,host,mess); else return false;
    };
    bool  cBotModule::ChannelAction   ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess){
      if (channel_action) return channel_action(chan,nick,user,host,mess); else return false;
    };
    bool  cBotModule::ChannelCtcp     ( const char* chan,  const char* nick,  const char* user,  const char* host,  const char* mess){
      if (channel_ctcp) return channel_ctcp(chan,nick,user,host,mess); else return false;
    }


    bool  cBotModule::PrivateMessage( const char* nick,  const char* user,  const char* host,  const char* mess){
      if (private_message) return private_message(nick,user,host,mess); else return false;
    }
    bool  cBotModule::PrivateNotice ( const char* nick,  const char* user,  const char* host,  const char* mess){
      if (private_notice) return private_notice(nick,user,host,mess); else return false;
    }
    bool  cBotModule::PrivateAction ( const char* nick,  const char* user,  const char* host,  const char* mess){
      if (private_action) return private_action(nick,user,host,mess); else return false;
    }
    bool  cBotModule::PrivateCtcp   ( const char* nick,  const char* user,  const char* host,  const char* mess){
      if (private_ctcp) return private_ctcp(nick,user,host,mess); else return false;
    }


//------

void bb_nick   (void * inst, const char *nick){
  cBot *c;
  c=(cBot*)inst;
  c->Protocol->nick(nick);
}


void bb_privmsg(void * inst, const char *target, const char *message){
  printf("plugin callback privmsg\n");
  cBot *c;
  c=(cBot*)inst;
  c->Protocol->privmsg(target,message);
}

void bb_notice (void * inst, const char *target, const char *message){}
void bb_action (void * inst, const char *target, const char *message){}
void bb_mode   (void * inst, const char *target, const char *mode){}
void bb_away   (void * inst, const char *reason){}
void bb_back   (void * inst){}
void bb_quit   (void * inst, const char *reason){}
void bb_raw    (void * inst, const char *raw){}




