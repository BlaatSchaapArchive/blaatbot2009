#ifndef _BLAAT_BOT_MODULE_CALLBACK_
#define _BLAAT_BOT_MODULE_CALLBACK_

extern void (*bb_privmsg)( void * inst, const char *target, const char *message);
extern void (*bb_action) ( void * inst, const char *target, const char *message);
extern void (*bb_notice) ( void * inst, const char *target, const char *message);
extern void (*bb_ctcp)   ( void * inst, const char *target, const char *message);

extern void (*bb_mode)   ( void * inst, const char *target, const char *mode);
extern void (*bb_away)   ( void * inst, const char *reason);

extern void (*bb_quit)   ( void * inst, const char *reason);
extern void (*bb_nick)   ( void * inst, const char *nick);

extern void (*bb_back)   ( void * inst);


extern void (*bb_raw)    ( void * inst, const char *raw);

#endif
