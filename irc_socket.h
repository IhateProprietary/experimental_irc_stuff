#ifndef __IRC_SOCKET_H__
# define __IRC_SOCKET_H__

# include <stddef.h>
# include <unistd.h>

# define IRC_TYPE_UNDEFINED 0

# include "irc_channel.h"
# include "irc_server.h"
# include "irc_client.h"

# define IRC_RESERVED_FD	10
# define IRC_MAXCONNECTION	(sysconf(_SC_OPEN_MAX) - IRC_RESERVED_FD)

# define IRC_NET_KILLED   0
# define IRC_NET_STANDBY  1
# define IRC_NET_READY	  2
# define IRC_NET_PENDING  3
# define IRC_NET_IDLE     4
# define IRC_NET_TOKILL   5
# define IRC_NET_IDENT	  6
//# define IRC_NET_BUSY     7

# define IRC_QUERY_CLIENT	0
# define IRC_QUERY_SERVER	1
# define IRC_QUERY_REMOTE	2
# define IRC_QUERY_TRACE	3

typedef char *	__pending_msg_t;

typedef struct
{
	int				sockfd;
	uint16_t		intype;
	uint16_t		busy:1;
	uint16_t		nmode:15;
	int				cycle;
	__pending_msg_t	msg;
}	__socket_common_t;

typedef union
{
	__socket_common_t	desc;
# ifdef IRC_ALLOW_BRIDGE_CONNECTION
	irc_node_t		node;
# endif
	irc_user_t		client;
}	__irc_usocket_t;

typedef struct
{
	__irc_usocket_t	*_conn;
# ifdef IRC_ALLOW_BRIDGE_CONNECTION
	int			bridge_only;
# endif
	int			cur;
	int			max;
}	irc_socket_t;
#endif
