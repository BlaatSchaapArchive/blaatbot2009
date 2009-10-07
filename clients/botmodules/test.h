#ifndef _BLAAT_TEST_MODULE_
#define _BLAAT_TEST_MODULE_


#ifdef __cplusplus
/* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

    bool  channel_message  (const char* chan, const char* nick, const char* user, const char* host, const char* mess);
    bool  channel_notice   (const char* chan, const char* nick, const char* user, const char* host, const char* mess);
    bool  channel_action   (const char* chan, const char* nick, const char* user, const char* host, const char* mess);
    bool  channel_ctcp     (const char* chan, const char* nick, const char* user, const char* host, const char* mess);

    bool  private_message(const char* nick, const char* user, const char* host, const char* mess);
    bool  private_notice (const char* nick, const char* user, const char* host, const char* mess);
    bool  private_action (const char* nick, const char* user, const char* host, const char* mess);
    bool  private_ctcp   (const char* nick, const char* user, const char* host, const char* mess);
    
    int bm_reg(int p, void * proc);

#ifdef __cplusplus
/* If this is a C++ compiler, end C linkage */
}
#endif


#endif
