#include <errno.h>
#include <string.h>

#include "bpp.h"
#include "irc.h"
#include "../bci.h" // BlaatSchaap Client Interface
#include "../c.h" // BlaatSchaap Classes


//-----------------------------------------------------------------------------

void __attribute__ ((constructor)) bpp_init(void){
  printf("Loading protocol library...\n");
  bc_message          = NULL;
  bc_action           = NULL;
  bc_notice           = NULL;
  bc_ctcp             = NULL;
  bc_join             = NULL;
  bc_part             = NULL;
  bc_kick             = NULL;
  bc_nick             = NULL;
  bc_quit             = NULL;
  bc_mode             = NULL;
  bc_channel_add      = NULL;
  bc_motd_begin       = NULL;
  bc_motd             = NULL;
  bc_motd_end         = NULL;
  bc_motd_missing     = NULL;
  bc_nickchangefail   = NULL;
  bc_unknown_message  = NULL;
  bc_welcome          = NULL;


  prot_so_init();

}

//-----------------------------------------------------------------------------

void __attribute__ ((destructor)) bpp_fini(void){
  printf("Unloading protocol library...\n");
  prot_so_fini();
}

//-----------------------------------------------------------------------------
/*
int bp_client(const char * c){
  char *path = getcwd(NULL,NULL);
  void *lib;
  char *libname;
  libname = (char*) malloc (strlen(c) + strlen(path)+ 15);
  sprintf(libname,"%s/clients/lib%s.so",path,c);
  lib = dlopen(libname, RTLD_LAZY);
  if (lib) {
    free(libname);
    libname = NULL;
    bc_id               = (t_f_pcar_v)  dlsym(lib,"bc_id"); 
    if(!bc_id) printf("%s\n",dlerror());
    bc_init             = (t_f_pv_pv)   dlsym(lib,"bc_init"); 
    if(!bc_init) printf("%s\n",dlerror());
  } else {
    printf("Unable to load client %s\n",c);
    printf("%s\n",dlerror());
  }
  free(path);
}
*/

int bp_client(const char * c){
  char *path = getcwd(NULL,0);
  void *lib;
  char *libname;
  libname = (char*) malloc (strlen(c) + strlen(path)+ 25);
  sprintf(libname,"%s/clients/lib%s.so",path,c);
//  lib = dlopen(libname, RTLD_LAZY);
  lib = dlopen(libname, RTLD_LAZY);
  if (lib) {
    free(libname);
    libname = NULL;

    bc_id               = (t_f_pcar_v)  dlsym(lib,"bc_id"); 
    if(!bc_id) printf("%s\n",dlerror());
    bc_init             = (t_f_pv_pv)   dlsym(lib,"bc_init"); 
    if(!bc_init) printf("%s\n",dlerror());;

    bc_motd_missing     = (t_f_v_pv)       dlsym(lib,"bc_motd_missing");     
    if(!bc_motd_missing) printf("%s\n",dlerror());
    bc_join             = (t_f_v_1pv4pchar)  dlsym(lib,"bc_join");
    if(!bc_join) printf("%s\n",dlerror());
    bc_nick             = (t_f_v_1pv4pchar)  dlsym(lib,"bc_nick");
    if(!bc_nick) printf("%s\n",dlerror());
    bc_quit             = (t_f_v_1pv4pchar)  dlsym(lib,"bc_quit");
    if(!bc_quit) printf("%s\n",dlerror());
    bc_motd             = (t_f_v_1pv4pchar)  dlsym(lib,"bc_motd");
    if(!bc_motd) printf("%s\n",dlerror());
    bc_motd_begin       = (t_f_v_1pv4pchar)  dlsym(lib,"bc_motd_begin");
    if(!bc_motd_begin) printf("%s\n",dlerror());
    bc_motd_end         = (t_f_v_1pv4pchar)  dlsym(lib,"bc_motd_end");
    if(!bc_motd_end) printf("%s\n",dlerror());
    bc_nickchangefail   = (t_f_v_1pv4pchar)  dlsym(lib,"bc_nickchangefail");
    if(!bc_nickchangefail) printf("%s\n",dlerror());

    bc_message          = (t_f_v_1pv5pchar)  dlsym(lib,"bc_message");
    if(!bc_message) printf("%s\n",dlerror());
    bc_action           = (t_f_v_1pv5pchar)  dlsym(lib,"bc_action"); 
    if(!bc_action) printf("%s\n",dlerror());
    bc_notice           = (t_f_v_1pv5pchar)  dlsym(lib,"bc_notice"); 
    if(!bc_notice) printf("%s\n",dlerror());
    bc_ctcp             = (t_f_v_1pv5pchar)  dlsym(lib,"bc_ctcp");  
    if(!bc_ctcp) printf("%s\n",dlerror());
    bc_mode             = (t_f_v_1pv5pchar)  dlsym(lib,"bc_mode");  
    if(!bc_mode) printf("%s\n",dlerror());
    bc_part             = (t_f_v_1pv5pchar)  dlsym(lib,"bc_part");  
    if(!bc_part) printf("%s\n",dlerror());
    bc_unknown_message  = (t_f_v_1pv5pchar)  dlsym(lib,"bc_unknown_message");
    if(!bc_unknown_message) printf("%s\n",dlerror());

    bc_kick             = (t_f_v_1pv6pchar)  dlsym(lib,"bc_kick");  
    if(!bc_kick) printf("%s\n",dlerror());
    bc_channel_add      = (t_f_v_1pv7pchar)  dlsym(lib,"bc_channel_add");  
    if(!bc_channel_add) printf("%s\n",dlerror());


    bc_welcome          = (t_f_v_1pv3pchar) dlsym(lib,"bc_welcome");  
    if(!bc_welcome) printf("%s\n",dlerror());

  } else {
    printf("Unable to load client %s\n",c);
    printf("%s\n",dlerror());
	free(path);
	return -1;
  }
  free(path);
	return 0;
}


int bp_init (sConnectInfo *ConnectInfo){
  printf("Initialising protocol library...\n");
  cConnection *Connection;
  if (prot_init (ConnectInfo)) {
    Connection = new cConnection (ConnectInfo) ; 
    Connection->Connect();
    return 0;
  } 
  return -1;
}

//-----------------------------------------------------------------------------
cConnection::cConnection (sConnectInfo *CI){
  ConnectInfo = CI;
}
//-----------------------------------------------------------------------------
cConnection::~cConnection (){
  if(ConnectInfo->host)      free(ConnectInfo->host);
  if(ConnectInfo->ipv4)      free(ConnectInfo->ipv4);    
  if(ConnectInfo->ipv6)      free(ConnectInfo->ipv6);
//  if(ConnectInfo->port)      free(ConnectInfo->port);   
  if(ConnectInfo->nick)      free(ConnectInfo->nick);    
  if(ConnectInfo->user)      free(ConnectInfo->user);    
  if(ConnectInfo->auth)      free(ConnectInfo->auth);
  if(ConnectInfo->pass)      free(ConnectInfo->pass);  
  free(ConnectInfo);
}
//-----------------------------------------------------------------------------
int cConnection::Connect(){
  bool Connected = false; 
  struct sockaddr_in   saServer4;
  struct sockaddr_in6  saServer6;
  memset(&saServer4,0,sizeof(sockaddr_in));
  memset(&saServer6,0,sizeof(sockaddr_in6));
  saServer4.sin_family=AF_INET;
  saServer4.sin_port=htons(ConnectInfo->port);
  saServer6.sin6_family=AF_INET6;
  saServer6.sin6_port=htons(ConnectInfo->port);


  struct hostent *hp = NULL;
#if defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__ || defined __bsdi__ || defined __DARWIN__ || defined __DragonFly__
// Are there the operating systems that use sin_len / sin6_len ? 
  saServer6.sin6_len = sizeof(sockaddr_in6);
  saServer4.sin_len = sizeof(sockaddr_in);

#endif 

  if(ConnectInfo->host) {
    printf("Trying to resolve %s to IPv6 ...\n",ConnectInfo->host);
    hp = gethostbyname2(ConnectInfo->host, AF_INET6);
    if (hp) {
      printf("%s resolved to IPv6 ",ConnectInfo->host);
      memcpy ( (saServer6.sin6_addr.s6_addr), (((struct in6_addr *)(hp->h_addr_list[0]))->s6_addr) , sizeof(in6_addr) ); 
      char temp[INET6_ADDRSTRLEN];
      printf("%s\n",        inet_ntop(AF_INET6, &(saServer6.sin6_addr), temp, INET6_ADDRSTRLEN));
    } 
    printf("Trying to resolve %s to IPv4 ...\n",ConnectInfo->host);
    hp = gethostbyname2(ConnectInfo->host, AF_INET);
    if (hp) {
      printf("%s resolved to IPv4. ",ConnectInfo->host);
      saServer4.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr_list[0]))->s_addr; 
      char temp[INET_ADDRSTRLEN];
//    printf("%s\n",inet_ntoa(saServer4.sin_addr));
      printf("%s\n",        inet_ntop(AF_INET, &(saServer4.sin_addr), temp, INET_ADDRSTRLEN));
    } else {
      printf("%s did not resolve to IPv4...\n");
    }
  }
  if (hp==NULL){
    if(ConnectInfo->ipv6){
      inet_pton(AF_INET6, ConnectInfo->ipv6, &(saServer6.sin6_addr));
    }
    if(ConnectInfo->ipv4){
      inet_pton(AF_INET, ConnectInfo->ipv4, &(saServer4.sin_addr));  
    }
  }

  if (*(saServer6.sin6_addr.s6_addr)) {
    printf("Connecting to server using IPv6...\n");
    Socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_IP);
    if (Socket) {
      if(connect(Socket, (struct sockaddr *)&saServer6, sizeof(saServer6))) {
        printf("Connection failed!\n");
      } else {
      printf("Connected\n");    
      Connected = true;      
      }
    }
  }
  if ((saServer4.sin_addr.s_addr) && !Connected) {
    printf("Connecting to server using IPv4...\n");
    Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (Socket) {
      if(connect(Socket, (struct sockaddr *)&saServer4, sizeof(saServer4))) {
        printf("Connection failed!\n");
      } else {
      printf("Connected\n");    
      Connected = true;      
      }
    }
  }
  if (Connected) {
    Protocol = new cIRCProtocol(this);

//  printf ("w Protocol %p \n",Protocol);
//  printf ("w Connection %p \n",Protocol->Connection);
//  printf ("w ConnectInfo %p \n",Protocol->Connection->ConnectInfo);
    Client = (cClient*)bc_init(Protocol); //new cClient(Protocol);

//  printf ("x Protocol %p \n",Protocol);
//  printf ("x Connection %p \n",Protocol->Connection);
//  printf ("x ConnectInfo %p \n",Protocol->Connection->ConnectInfo);

    Protocol->SetClient(Client);
//  printf ("y Protocol %p \n",Protocol);
//  printf ("y Connection %p \n",Protocol->Connection);
//  printf ("y ConnectInfo %p \n",Protocol->Connection->ConnectInfo);

    Protocol->SendLogin();
//  printf ("z Protocol %p \n",Protocol);
//  printf ("z Connection %p \n",Protocol->Connection);
//  printf ("z ConnectInfo %p \n",Protocol->Connection->ConnectInfo);

    Protocol->StartThread();
//  printf ("a Protocol %p \n",Protocol);
//  printf ("a Connection %p \n",Protocol->Connection);
//  printf ("a ConnectInfo %p \n",Protocol->Connection->ConnectInfo);

    return 0;
  }
  return -1;
}
//-----------------------------------------------------------------------------
int cConnection::Disconnect(){
  close(Socket);
  return 0;
}
//-----------------------------------------------------------------------------
int cConnection::Send(const char * data){
  send (Socket,data,strlen(data),0);
  return 0;
}
//-----------------------------------------------------------------------------
char * cConnection::ReceiveLn(){
//  printf("cConnection::ReceiveLn()\n");//debug?
//  printf("this   : %p \n",this);
//  printf("Socket : %p \n",Socket);
  char * temp = (char*)malloc(2048);
//  printf("temp   : %p \n",temp);
  if (temp == NULL) {
    printf("Memory error: %d %s\n", errno, strerror(errno));  
    return NULL;
  }
  memset(temp,0,2048);
//  printf("temp   : %p \n",temp);
  int received_size=0;
  while(received_size < 2047){
      if (!(recv(Socket, temp+received_size, 1, 0))) {
      printf("Socket error: %d %s\n", errno, strerror(errno));
      free(temp);
      return NULL;
    }
    putchar(temp[received_size]);
    if (temp[received_size] == 0x0A  ) {
      temp[received_size-1] = 0x00; //detect end of line.
//      printf(temp);
      return temp;
    }
    received_size++;
  } 
  printf("WARNING! Receive Buffer was full!\n");
  return temp; 
}
//-----------------------------------------------------------------------------
char * cConnection::Receive0(){
  char * temp = (char*)malloc(2048);
  int received_size=0;
  while(received_size < 2046){
    if (!(recv(Socket, temp+received_size, 1, 0))) {
      free(temp);
      return NULL;
    }
    received_size++;
    if (temp[received_size] == 0x00  ) {
      return temp;
    }
  }
  return NULL;
}
//-----------------------------------------------------------------------------

sConnectInfo * cProtocol::GetConnectInfo(){
  printf ("Connection  %p \n",Connection);
  printf ("ConnectInfo %p \n",Connection->ConnectInfo);

  return Connection->ConnectInfo;
}
