#ifndef __IRC_COMMAND_H__
# define __IRC_COMMAND_H__

# include <stddef.h>

enum
{
	IRC_ARGV_IGNORED,
	IRC_ARGV_REQUIRED,
	IRC_ARGV_OPTIONAL,
	IRC_ARGV_SERVER,
}

typedef struct
{
	char		*cmd;
	char		argv[8];
	uint32_t	hash;
}	irc_command_t;

extern char *irc_cmd[];

#endif
