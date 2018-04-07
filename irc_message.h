#ifndef __IRC_MESSAGE_H__
# define __IRC_MESSAGE_H__

# include <stddef.h>
# include "irc_anwser.h"
# include "irc_error.h"
# include "irc_socket.h"

typedef struct
{
	char			*tosend;
	irc_socket_t	*target;
}	irc_msg_t;

typedef struct
{
	irc_msg_t	*msg;
	size_t		pending;
	size_t		max;
}	irc_msg_pending_t;

#endif
