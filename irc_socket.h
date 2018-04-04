#ifndef __IRC_SOCKET_H__
# define __IRC_SOCKET_H__

# include <stddef.h>

# include "irc_server.h"
# include "irc_client.h"

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
	__irc_usocket_t	*connection;
# define irc_sockfd connection->irc_type.sockfd
# define irc_intype connection->irc_type.irc_intype
# define irc_alive connection->irc_type.alive
# define irc_client connection->client
# ifdef IRC_ALLOW_BRIDGE_CONNECTION
#  define irc_node connection->node
# endif
	size_t			cur;
	size_t			max;
}	irc_socket_t;
#endif
