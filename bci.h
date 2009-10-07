#ifndef _BLAAT_CLIENT_INTERFACE_
#define _BLAAT_CLIENT_INTERFACE_

#include "fptype.h"

// Messages
extern void (*bc_message )(void * inst, const char * targ, const char * nick, const char * user, const char * host, const char * mess);
extern void (*bc_action  )(void * inst, const char * targ, const char * nick, const char * user, const char * host, const char * mess);
extern void (*bc_notice  )(void * inst, const char * targ, const char * nick, const char * user, const char * host, const char * mess);
extern void (*bc_ctcp    )(void * inst, const char * targ, const char * nick, const char * user, const char * host, const char * mess);

// Events
extern void (*bc_join)(void * inst, const char * targ, const char * nick, const char * user, const char * host);
extern void (*bc_part)(void * inst, const char * targ, const char * nick, const char * user, const char * host, const char * mess);
extern void (*bc_kick)(void * inst, const char * chan, const char * kick, const char * mess, const char * nick, const char * user, const char * host);
extern void (*bc_nick)(void * inst, const char * nick, const char * user, const char * host, const char * newn);
extern void (*bc_quit)(void * inst, const char * nick, const char * user, const char * host, const char * mess);
extern void (*bc_mode)(void * inst, const char * nick, const char * user, const char * host, const char * mode,    const char * targ);

// Channel Management
//void (*bc_channel_clear   )(const char * chann);
extern void (*bc_channel_add     )(void * inst, const char * chann, const char * nick, const char * user, const char * host, const char *serv, const char *mode, const char *real);

// Motd
extern void (*bc_motd_begin      )(void * inst, const char * nick, const char * user, const char * host, const char * mess);
extern void (*bc_motd            )(void * inst, const char * nick, const char * user, const char * host, const char * mess);
extern void (*bc_motd_end        )(void * inst, const char * nick, const char * user, const char * host, const char * mess);
extern void (*bc_motd_missing    )(void * inst);

extern void (*bc_nickchangefail  )(void * inst, const char * oldn, const char * badn, const char * mess, const char * numb);
extern void (*bc_unknown_message )(void * inst, const char * targ, const char * nick, const char * user, const char * host, const char * mess);

extern void (*bc_welcome)         (void * inst, const char * serv, const char * nick, const char * mess);

extern const char * (*bc_id)(void);
extern void * (*bc_init)(void * P);
#endif 
