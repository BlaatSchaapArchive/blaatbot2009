#ifndef _BLAAT_CLIENT_PLUGIN_
#define _BLAAT_CLIENT_PLUGIN_


#ifdef __cplusplus
/* If this is a C++ compiler, use C linkage */
extern "C" {
#endif
char * bc_id   (void);
void * bc_init (void * c);

// Messages
void bc_message ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess);
void bc_action  ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess);
void bc_notice  ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess);
void bc_ctcp    ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess);

// Events
void bc_join( void * inst, char * targ,  char * nick,  char * user,  char * host);
void bc_part( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess);
void bc_kick( void * inst, char * chan,  char * kick,  char * mess,  char * nick,  char * user,  char * host);
void bc_nick( void * inst, char * nick,  char * user,  char * host,  char * newn);
void bc_quit( void * inst, char * nick,  char * user,  char * host,  char * mess);
void bc_mode( void * inst, char * nick,  char * user,  char * host,  char * mode,     char * targ);

// Channel Management
//void bc_channel_clear   ( void * inst, char * chann );
void bc_channel_add     ( void * inst, char * chann,  char * nick,  char * user,  char * host,  char *serv,  char *mode,  char *real);

// Motd
void bc_motd_begin      ( void * inst, char * nick,  char * user,  char * host,  char * mess);
void bc_motd            ( void * inst, char * nick,  char * user,  char * host,  char * mess);
void bc_motd_end        ( void * inst, char * nick,  char * user,  char * host,  char * mess);
void bc_motd_missing    ( void * inst );

void bc_nickchangefail  ( void * inst, char * oldn,  char * badn,  char * mess,  char * numb);
void bc_unknown_message ( void * inst, char * targ,  char * nick,  char * user,  char * host,  char * mess);

void bc_welcome         ( void * inst, const char * serv, const char * nick, const char * mess);

#ifdef __cplusplus
/* If this is a C++ compiler, end C linkage */
}
#endif


#endif 
