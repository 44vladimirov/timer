#ifndef __ARGS_H__
#define __ARGS_H__

#define FLAG_REPEAT     0x1
#define FLAG_INTER      0x2
#define FLAG_DEFAULT    (FLAG_INTER)

#define CMD_ARG_INIT(argc, argv) {(argc), (argv), FLAG_DEFAULT, 1, 0}

struct cmd_arg {
    const int argc;
    const char * const * const argv;
    int flag;
    unsigned repeat_count;
    unsigned time;
};

int parse_arg(struct cmd_arg *arg);

#endif // #ifndef __ARGS_H__
