#ifndef __IRC_CHANNEL_H__
# define __IRC_CHANNEL_H__

# include <stddef.h>

typedef struct
{
	char		*name;
	uint64_t	chanid;
	uint64_t	ownerid;
	char		prefix;
}

#endif
