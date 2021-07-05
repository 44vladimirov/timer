#include <stddef.h>

#include "timer.h"
#include "defaults.h"
#include "args.h"

static int str2num(const char *str, unsigned *num) {
    unsigned i;
    if(str == NULL)
        return -1;
    for(*num = i = 0; (str[i] >= '0') && (str[i] <= '9'); i++)
        *num = *num * 10 + str[i] - '0';
    return str[i];
}

static int str2time(const char * const str, unsigned *time) {
    unsigned result, i, t;
    for(result = i = 0; str[i]; result += t, i += str[i] != 0) {
        for(t = 0; (str[i] >= '0') && (str[i] <= '9'); i++)
            t = t * 10 + str[i] - '0';
        switch(str[i]) {
        case 'd':
            t *= 24;
        case 'h':
            t *= 60;
        case 'm':
            t *= 60;
        case 's': case 0:
            break;
        default:
            return 1;
        }
    }
    *time += result;
    return 0;
}

static int parse_flag(char c, const char * const *argv, struct cmd_arg *arg) {
    switch(c) {
    case 'r':
        arg->flag |= FLAG_REPEAT;
        arg->repeat_count = ALARM_REPEAT_COUNT;
        return 0;
    case 'R':
        arg->flag |= FLAG_REPEAT;
        return str2num(argv[1], &arg->repeat_count) ? -1 : 1;
    case 'i':
        arg->flag |= FLAG_INTER;
        return 0;
    case 'I':
        arg->flag &= !FLAG_INTER;
        return 0;
    default:
        return -1;
    }
}

int parse_arg(struct cmd_arg *arg) {
    unsigned i;
    for(i = 1; (i < arg->argc) && (arg->argv[i][0] == '-'); i++) {
        unsigned j;
        const char *s;
        for(s = arg->argv[i], j = 1; s[j]; j++) {
            int k = parse_flag(s[j], arg->argv + i, arg);
            if(k < 0)
                return 1;
            i += k;
        }
    }
    for(; i < arg->argc; i++)
        if( str2time(arg->argv[i], &arg->time) )
            return 1;
    return 0;
}
