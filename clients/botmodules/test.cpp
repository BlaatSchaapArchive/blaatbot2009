#include "test.h"
#include "../../fptype.h"
#include "botcb.h"
#include <stdio.h>

void *inst;

//-----------------------------------------------------------------------------

void __attribute__((constructor)) bot_init(void) {
  printf("Loading sample bot library...\n");
  inst = NULL;
  bb_privmsg = NULL;
  bb_action = NULL;
  bb_notice = NULL;
  bb_ctcp = NULL;
  bb_mode = NULL;
  bb_away = NULL;
  bb_quit = NULL;
  bb_nick = NULL;
  bb_back = NULL;
  bb_raw = NULL;
}

//-----------------------------------------------------------------------------

void __attribute__((destructor)) bot_fini(void) {
  printf("Unloading sample bot library...\n");
}

//-----------------------------------------------------------------------------

int bm_reg(int p, void *proc) {
  switch (p) {
  case 0:
    inst = proc;
    break;
    printf("Register client instance\n");
  case 20:
    bb_privmsg = (t_f_v_1pv2pchar)proc;
    printf("Register privmsg\n");
    break;
  case 21:
    bb_action = (t_f_v_1pv2pchar)proc;
    break;
  case 22:
    bb_notice = (t_f_v_1pv2pchar)proc;
    break;
  case 23:
    bb_ctcp = (t_f_v_1pv2pchar)proc;
    break;
  default:
    printf("Unsupported!\n");
  }
  return 0;
}

bool channel_message(const char *chan, const char *nick, const char *user,
                     const char *host, const char *mess) {
  printf("channel_message\n");
  if (bb_privmsg)
    if (chan)
      if (mess)
        if (inst)
          bb_privmsg(inst, chan, mess);
        else
          printf("no client instance\n");
      else
        printf("no message\n");
    else
      printf("no channel\n");
  else
    printf("no function\n");
  return true;
}

bool channel_notice(const char *chan, const char *nick, const char *user,
                    const char *host, const char *mess) {
  return true;
}

bool channel_action(const char *chan, const char *nick, const char *user,
                    const char *host, const char *mess) {
  return true;
}

bool channel_ctcp(const char *chan, const char *nick, const char *user,
                  const char *host, const char *mess) {
  return true;
}

bool private_message(const char *nick, const char *user, const char *host,
                     const char *mess) {
  printf("private_message\n");

  return true;
}
bool private_notice(const char *nick, const char *user, const char *host,
                    const char *mess) {
  return true;
}
bool private_action(const char *nick, const char *user, const char *host,
                    const char *mess) {
  return true;
}
bool private_ctcp(const char *nick, const char *user, const char *host,
                  const char *mess) {
  return true;
}
