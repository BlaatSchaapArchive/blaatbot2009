#include "xmlParser.h"
#include "bpi.h"
#include "c.h"
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>



int main(){
  char * path = getcwd(NULL,0);
  XMLNode xBlaatNode   = XMLNode::openFileHelper("config.xml","blaat");
  XMLNode xEntryNode   = xBlaatNode.getChildNode("chat");
  while ( !xEntryNode.isEmpty() ) {
    XMLNode xml = xEntryNode.deepCopy();
    const char * host      = (xEntryNode.getChildNode("host").getText());
    const char * ipv4      = (xEntryNode.getChildNode("ipv4").getText());
    const char * ipv6      = (xEntryNode.getChildNode("ipv6").getText());    
    const char * port      = (xEntryNode.getChildNode("port").getText());
    const char * nick      = (xEntryNode.getChildNode("nick").getText());      
    const char * user      = (xEntryNode.getChildNode("user").getText());
    const char * auth      = (xEntryNode.getChildNode("auth").getText());    
    const char * client    = (xEntryNode.getChildNode("client").getText());        
    const char * password  = (xEntryNode.getChildNode("password").getText());
    const char * protocol  = (xEntryNode.getChildNode("protocol").getText());
    const char * realname  = (xEntryNode.getChildNode("realname").getText());
    if(host) printf("%s\n",host);
    if(ipv4) printf("%s\n",ipv4);
    if(ipv6) printf("%s\n",ipv6);
    if(port)printf("%s\n",port);
    if(nick)printf("%s\n",nick);
    if(user)printf("%s\n",user);
    if(auth)printf("%s\n",auth);
    if(password)printf("%s\n",password);
    if(protocol)printf("%s\n",protocol);
    printf("\n\n");

    if ( (host || ipv4 || ipv6) && (port) ) {
      if (protocol) {
        void *lib;
        char *libname;
        libname = (char*) malloc (strlen(protocol) + strlen(path)+ 20);
        sprintf(libname,"%s/protocols/lib%s.so",path,protocol);
        lib = dlopen(libname, RTLD_LAZY);
//        lib = dlopen(libname, RTLD_NOW);
        free(libname);
        if (lib) {
          libname = NULL;
          bp_id     = (t_f_pcar_v)  dlsym(lib, "bp_id"); 
          bp_client = (t_f_i_pchar) dlsym(lib, "bp_client");
          //bp_init   = (t_f_i_8pchar)dlsym(lib, "bp_init"); 
          bp_init   = (t_f_i_pv)dlsym(lib, "bp_init"); 
          if (bp_client) {
            if (bp_init) {
              if (!bp_client(client)) {
//--
  sConnectInfo *ConnectInfo;
  ConnectInfo = (sConnectInfo *) malloc (sizeof(sConnectInfo));
  memset (ConnectInfo,0,sizeof(sConnectInfo));
  

  ConnectInfo->xml = &xml;

  if(host){
    printf("Host...%s\n",host);
    ConnectInfo->host = (char*) malloc (strlen(host) +1 );
    strcpy(ConnectInfo->host,host);
  }

  if(ipv4){
    printf("Ipv4...%s\n",ipv4);
    ConnectInfo->ipv4 = (char*) malloc (strlen(ipv4) +1 );
    strcpy(ConnectInfo->ipv4,ipv4);
  }

  if(ipv6){
    printf("Ipv6...%s\n",ipv6);
    ConnectInfo->ipv6 = (char*) malloc (strlen(ipv6) +1 );
    strcpy(ConnectInfo->ipv6,ipv6);
  }

  if(port){
    printf("Port...%s\n",port);
    ConnectInfo->port = atoi (port);
  }

  if(nick){
    printf("Nick...%s\n",nick);
    ConnectInfo->nick = (char*) malloc (strlen(nick) +1 );
    strcpy(ConnectInfo->nick,nick);
  }

  if(user){
    printf("User...%s\n",user);
    ConnectInfo->user = (char*) malloc (strlen(user) +1 );
    strcpy(ConnectInfo->user,user);
  }

  if(auth){
    printf("Auth...%s\n",auth);
    ConnectInfo->auth = (char*) malloc (strlen(auth) +1 );
    strcpy(ConnectInfo->auth,auth);
  }

  if(password){
    printf("Password...%s\n",password);
    ConnectInfo->pass = (char*) malloc (strlen(password) +1 );
    strcpy(ConnectInfo->pass,password);
  }

  if(realname){
    printf("Password...%s\n",realname);
    ConnectInfo->real = (char*) malloc (strlen(realname) +1 );
    strcpy(ConnectInfo->real,realname);
  }

  if (! ((ConnectInfo->host||ConnectInfo->ipv4||ConnectInfo->ipv6)&&(ConnectInfo->port)) ) {
    printf("Server and port are required\n");
//    return false;
  }
  if (ConnectInfo->nick==NULL) {
    printf("Nick required!\n");
//    return false;
  }

  if (ConnectInfo->user==NULL) {
    printf("User missing!\n");
    ConnectInfo->user = (char*) malloc (strlen(ConnectInfo->nick)+1);
    strcpy(ConnectInfo->user,ConnectInfo->nick);
  }


  bp_init(ConnectInfo);

//--                bp_init(host, ipv4, ipv6, port, nick, user, auth, password);
              } else printf("blaat\n");
            } else {
              printf("Unable to initialise protocol (config) %s\n",protocol);          
              printf("%s\n",dlerror());
              dlclose(lib);
              bp_init = NULL;
              lib     = NULL;
            }
          } else {
          printf("Unable to initialise protocol (client) %s\n",protocol);          
          printf("%s\n",dlerror());
          dlclose(lib);
          bp_init = NULL;
          bp_client = NULL;
          lib       = NULL;
          }                
        } else {
          printf("Unable to load protocol %s\n",protocol);
          printf("%s\n",dlerror());
        }
      } else {
        printf("Protocol required\n");
      }
    } else {
    printf("Server and port are required\n");
    }
    xEntryNode.deleteNodeContent();  
    xEntryNode = xBlaatNode.getChildNode("chat");
  }
  loop:
  char c = getchar();
  if (c!='q') goto loop;
  free(path);
}
