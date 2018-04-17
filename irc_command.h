#ifndef __IRC_COMMAND_H__
# define __IRC_COMMAND_H__

# include <stdint.h>

enum
{
	IRC_ARGV_IGNORED,
	IRC_ARGV_REQUIRED,
	IRC_ARGV_OPTIONAL,
	IRC_ARGV_SERVER,
};

typedef int (*irc_cfunc_t)();

typedef struct
{
	char		*cmd;
	char		argv[8];
	irc_cfunc_t	func;
}	irc_command_t;

extern irc_command_t	irc_cmd[];

int			irchc_init(void);
irc_cfunc_t	irchc_search(char *scmd);

#endif
