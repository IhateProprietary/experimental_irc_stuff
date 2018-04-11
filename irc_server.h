#ifndef __IRC_SERVER_H__
# define __IRC_SERVER_H__

# ifndef __IRC_SOCKET_H__
#  error "include irc_socket.h instead"
# endif

# define IRC_TYPE_SERVER	1
# define IRC_DEFAULT_HOSTNAME "irc.localhost"
# define IRC_DEFAULT_PORT	 6667

typedef struct
{
	int			sockfd;
	uint16_t	intype;
	uint16_t	nmode;
	int			cycle;
	char		*msg;
	char		*hostname;
	struct sockaddr	addr;
}	irc_node_t;
#endif
