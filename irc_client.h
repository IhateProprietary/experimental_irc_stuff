#ifndef __IRC_CLIENT_H__
# define __IRC_CLIENT_H__

# ifndef __IRC_SOCKET_H__
#  error "include irc_socket.h instead"
# endif

# define IRC_TYPE_USER	2

typedef struct
{
	int			sockfd;
	int			intype;
	int			alive;
	uint32_t	mode;
	char		*nickname;
	char		*hostname;
	char		*servername;
	char		*realname;
	char		*awaymsg;
	char		*passwd;
	uint64_t	uid;
}	irc_user_t;

#endif
