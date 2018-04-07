#ifndef __IRC_TASK_H__
# define __IRC_TASK_H__

# include <stddef.h>
# include "irc_socket.h"

# define IRC_TASK_UNDEFINED	0
# define IRC_TASK_PRIVTASK	1
# define IRC_TASK_REPLY		2
# define IRC_TASK_ERROR		3

typedef struct
{
	uint32_t	type:3;
	uint32_t	num:9;
	uint32_t	cur:20;
}	__task_type_t;

typedef struct
{
	__task_type_t	type;
	char			*request;
	irc_socket_t	*target;
}	irc_task_t;

typedef struct
{
	irc_task_t	*task;
	size_t		pending;
	size_t		max;
}	irc_task_pending_t;

#endif
