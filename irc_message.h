#ifndef __IRC_MESSAGE_H__
# define __IRC_MESSAGE_H__

# include <stddef.h>
# include "irc_anwser.h"
# include "irc_error.h"
# include "irc_socket.h"

# define IRC_MSG_UNDEFINED	0
# define IRC_MSG_PRIVMSG	1
# define IRC_MSG_REPLY		2
# define IRC_MSG_ERROR		3

typedef struct
{
	uint32_t	type:3;
	uint32_t	num:9;
	uint32_t	cur:20;
}	irc_task_type_t;

typedef struct
{
	irc_task_type_t	type;
	char			*tosend;
	irc_socket_t	*target;
}	irc_pending_task_t;

typedef struct
{
	irc_pending_task_t	*task;
	size_t				max;
}	irc_pending_t;

#endif
