#ifndef __IRC_CHANNEL_H__
# define __IRC_CHANNEL_H__

# include <stddef.h>

# define IRC_CHANNEL_MAX_USER	32

typedef struct
{
	char			*name;
	char			*key;
	irc_user_t		*user;
	uint64_t		chanid;
	uint64_t		ownerid;
	uint64_t		*operuid;
	size_t			max;
	uint32_t		mode;
	char			prefix;
}	irc_channel_t;

#endif
