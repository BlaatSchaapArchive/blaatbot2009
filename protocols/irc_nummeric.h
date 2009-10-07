#ifndef _IRC_NUMMERIC_
#define _IRC_NUMMERIC_
// based upop http://www.alien.net.au/irc/irc2numerics.html
// note, this file is still incomplete!

#define RPL_WELCOME           "001"
#define RPL_YOURHOST          "002"
#define RPL_CREATED           "003"
#define RPL_MYINFO            "004"
#define RPL_ISUPPORT          "005"
#define RPL_MAP               "006"
#define RPL_MAPEND            "007"
#define RPL_SNOMASK           "008"
#define RPL_STATMEMTOT        "009"
#define RPL_BOUNCE            "010"

#define RPL_WHOREPLY          "352"
#define RPL_ENDOFWHO          "315"

#define RPL_MOTDSTART         "375"
#define RPL_MOTD              "372"
#define RPL_ENDOFMOTD         "376"

#define ERR_NOMOTD            "422"

#define ERR_EVENTNICKCHANGE   "430"
#define ERR_NONICKNAMEGIVEN   "431"
#define ERR_ERRONEUSNICKNAME  "432"
#define ERR_NICKNAMEINUSE     "433"
#define ERR_NICKCOLLISION     "436" 
#define ERR_NICKTOOFAST       "438"


#endif
