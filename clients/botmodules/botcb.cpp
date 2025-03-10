void (*bb_notice)(void *inst, const char *target, const char *message);
void (*bb_action)(void *inst, const char *target, const char *message);
void (*bb_mode)(void *inst, const char *target, const char *mode);
void (*bb_away)(void *inst, const char *reason);
void (*bb_back)(void *inst);
void (*bb_quit)(void *inst, const char *reason);
void (*bb_raw)(void *inst, const char *raw);
void (*bb_nick)(void *inst, const char *nick);
void (*bb_privmsg)(void *inst, const char *target, const char *message);
void (*bb_ctcp)(void *inst, const char *target, const char *message);
