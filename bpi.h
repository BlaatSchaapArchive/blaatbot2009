#ifndef _BLAAT_PROTOCOL_INTERFACE_
#define _BLAAT_PROTOCOL_INTERFACE_

#include "fptype.h"

//int (*bp_init)(const char * host, const char * ipv4, const char * ipv6, const char * port, const char * nick, const char * user, const char * auth, const char * password);

int (*bp_init) (void *);
const char * (*bp_id)(void);

int (*bp_client)(const char *);






#endif
