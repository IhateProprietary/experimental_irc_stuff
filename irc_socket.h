#ifndef __IRC_SOCKET_H__
# define __IRC_SOCKET_H__

# include <stddef.h>
# include <unistd.h>

# include "irc_channel.h"
# include "irc_server.h"
# include "irc_client.h"

# define IRC_RESERVED_FD	10
# define IRC_MAXCONNECTION	(sysconf(_SC_OPEN_MAX) - IRC_RESERVED_FD)

# define IRC_NET_KILLED   0
# define IRC_NET_STANDBY  1
# define IRC_NET_BUSY     2

typedef struct
{
	int		sockfd;
	int		intype;
	int		nmode;
}	__socket_type_t;

typedef union
{
	__socket_type_t	irc_type;
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
