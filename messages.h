#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define NAME        "timer"
#define ERR_MSG     NAME ": "
#define USAGE_MSG   \
    NAME " [flags] [time]" "\n" \
    "flags" "\n" \
    "\t"    "-r" "\n" \
    "\t\t"  "repeating alarm times by default" "\n" \
    "\t"    "-R count" "\n" \
    "\t\t"  "repeating alarm count times" "\n" \
    "\t"    "-i | -I" "\n" \
    "\t\t"  "interactive or non-interactive mode" "\n" \
    "time" "\n" \
    "\t" "time in format Xd Xh Xm Xs"

#define INTER_PROMPT        "> "
#define INTER_INVCMD_MSG    "invalid command"
#define INTER_HELP_MSG      \
    "exit" "\t"     "unset timer and quit" "\n" \
    "help" "\t"     "help message" "\n" \
    "pause" "\t"    "pause timer" "\n" \
    "query" "\t"    "query remaining time" "\n" \
    "resume" "\t"   "resume timer"
#define INTER_PAUSED_MSG    "timer paused"
#define INTER_RESUMED_MSG   "timer resumed"

enum error {
    ERR_USAGE = 0,
    ERR_PTHREAD,
    ERR_MUTEX,
    ERR_SIO_OPEN,
    ERR_SIO_START,
    ERR_AFILE_OPEN,
    ERR_AFILE_READ,
    ERR_AFILE_CLOSE,
    ERR_READ,
    ERR_WRITE,
    ERR_MALLOC,
    ERR_LAST // needed for counting
};

void err(enum error e, const char *msg);

#endif // #ifndef __MESSAGES_H__
