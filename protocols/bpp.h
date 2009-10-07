#ifndef _BLAAT_PROTOCOL_PLUGIN_
#define _BLAAT_PROTOCOL_PLUGIN_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>       
#include <sys/types.h>      
#include <netinet/in.h>     
#include <arpa/inet.h>    
#include <netdb.h>
#include <vector>
#include <dlfcn.h>

using namespace std;
struct sConnectInfo;
class cConnection;
//-------------------------------------------------------------------
// The functions below are to be implemented for each protocol
// module
//-------------------------------------------------------------------

void prot_so_init(void);                    // module contructor
void prot_so_fini(void);                    // module destructor
int  prot_init(sConnectInfo * ConnectInfo); // initialise connection

//-------------------------------------------------------------------
#ifdef __cplusplus
/* If this is a C++ compiler, use C linkage */
extern "C" {
#endif
/* These functions get C linkage */

  void __attribute__ ((constructor)) my_init(void);
  void __attribute__ ((destructor)) my_fini(void);

//  int bp_init(const char * host, const char * ipv4, const char * ipv6, const char * port, const char * nick, const char * user, const char * auth, const char * password);
  int bp_init(sConnectInfo *);
  const char * bp_id();
  int bp_client(const char *);


#ifdef __cplusplus
/* If this is a C++ compiler, end C linkage */
}
#endif

//-------------------------------------------------------------------



#endif
