#ifndef __IRC_CLIENT_H__
# define __IRC_CLIENT_H__

# ifndef __IRC_SOCKET_H__
#  error "include irc_socket.h instead"
# endif

# define IRC_TYPE_USER	2
typedef struct irc_channel_s irc_channel_t;
typedef struct	irc_user_s
{
	int				sockfd;
	uint16_t		intype;
	uint16_t		nmode;
	int				cycle;
	char			*msg;
	char			*hostname;
	struct sockaddr_in	addr;
	char			*nickname;
	char			*servername;
	char			*realname;
	char			*awaymsg;
	char			*passwd;
	irc_channel_t	**channel;
	uint32_t		nmode;
}	irc_user_t;
#endif
