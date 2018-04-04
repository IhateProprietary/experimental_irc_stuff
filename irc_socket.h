#ifndef __IRC_SOCKET_H__
# define __IRC_SOCKET_H__

# include <stddef.h>

# include "irc_server.h"
# include "irc_client.h"

# define IRC_DEFAULT_MAXIN	(sysconf(_SC_OPEN_MAX) - 10)

# define IRC_NET_ALIVE  0
# define IRC_NET_VERIFY 1
# define IRC_NET_KILLED 2

typedef struct
{
	int		sockfd;
	int		intype;
	int		alive;
}	__irc_tsocket_t;

typedef union
{
	__irc_tsocket_t	irc_type;
# ifdef IRC_ALLOW_BRIDGE_CONNECTION
	irc_node_t	node;
# endif
	irc_user_t	client;
}	__irc_usocket_t;

typedef struct
{
	__irc_usocket_t	*_conn;
# define irc_sockfd _conn->irc_type.sockfd
# define irc_intype _conn->irc_type.irc_intype
# define irc_alive _conn->irc_type.alive
# define irc_client _conn->client
# ifdef IRC_ALLOW_BRIDGE_CONNECTION
#  define irc_node _conn->node
# endif
	int			bridge_only;
	int			cur;
	int			max;
}	irc_socket_t;
#endif
