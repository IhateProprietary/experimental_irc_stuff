#ifndef __IRC_CHANNEL_H__
# define __IRC_CHANNEL_H__

# include <stddef.h>

# define IRC_CHANNEL_MAXUSER	32

typedef struct irc_user_s irc_user_t;
typedef struct	irc_channel_s
{
	char		*name;
	char		*key;
	irc_user_t	**user;
	irc_user_t	*owner;
	irc_user_t	**oper;
	size_t		maxuser;
	int			cmode;
	int			prefix;
}	irc_channel_t;

#endif
