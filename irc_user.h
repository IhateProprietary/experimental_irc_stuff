#ifndef __IRC_USER_H__
# define __IRC_USER_H__

# include <stddef.h>

typedef struct
{
	char		*name;
	int			fd;
	int			active;
	uint64_t	userid;
	struct sockaddr_in addr;
};

#endif
