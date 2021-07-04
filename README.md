# CLI sndio timer

## Usage

Running [sndio](http://sndio.org) sound server and `/usr/local/etc/alarm` sound
file are required for alarming.

```
timer [flags] [time]
```

### command-line arguments

#### `flags`

* `-r` repeating alarm times by default
* `-R count` repeating alarm `count` times
* `-i` | `-I` interactive or non-interactive mode, interactive by default

#### `time`

`time` in format `Xd Xh Xm Xs`

### interactive commands

* `exit` unset timer and quit
* `help` show help message
* `pause` pause timer
* `query` query remaining time
* `resume` resume timer

The commands are shortcut, which means you can type `r` instead of `resume`.

## Examples

`timer -R 3 5m 25m 1h30` command sets timer for the 1 hour 30 minutes and 30
seconds in the interactive mode and sets 3 times repeating alarm.

## Build requirements

1. Make build automation tool
1. C compiler
1. [sndio](http://sndio.org) library

## Build instructions

`make` builds timer named as `x`.

You can also specify a compiler and a compilation flags via make-variables
`COMP` and `FLAGS` respectively. Include and Lib path tunings should be done via
make-variables `INCLUDE` and `LIB` respectively.
