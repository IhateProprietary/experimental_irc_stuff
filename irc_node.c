#include <sys/socket.h>
#include <net/route.h>
#include <net/if.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <getopt.h>

#include "irc_socket.h"
#include "irc_message.h"
#include "irc_task.h"
#ifdef IRC_ALLOW_BRIDGE_CONNECTION
# define IRC_DEFAULT_MAXLINK 16
#endif

#if defined(__APPLE__)
# define __BYTE_ORDER __BYTE_ORDER__
# define __LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
# define __BIG_ENDIAN __ORDER_BIG_ENDIAN__
#endif

struct ip_addr4_s
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	uint32_t	d:8; /* 0.0.0.x */
	uint32_t	c:8; /* 0.0.x.0 */
	uint32_t	b:8; /* 0.x.0.0 */
	uint32_t	a:8; /* x.0.0.0 */
#elif __BYTE_ORDER == __BIG_ENDIAN
	uint32_t	a:8; /* x.0.0.0 */
	uint32_t	b:8; /* 0.x.0.0 */
	uint32_t	c:8; /* 0.0.x.0 */
	uint32_t	d:8; /* 0.0.0.x */
#endif
};

typedef union
{
	struct ip_addr4_s	ip;
	uint32_t			_ip;
}	IP_ADDR4;

irc_node_t			ME;
irc_socket_t		IN;
irc_task_pending_t	task;

int		main(int ac, char **av)
{
	static const struct option opt[] = {
		{"host", required_argument, 0, 'H'},
		{"port", required_argument, 0, 'p'},
		{"limits", required_argument, 0, 'l'},
		{"hostname", required_argument, 0, 'n'},
		{"maxtask", required_argument, 0, 't'},
		{"help", no_argument, 0, 'h'},
#ifdef IRC_ALLOW_BRIDGE_CONNECTION
		{"bridge", no_argument, 0, 'b'},
#endif
		{(char *)0, 0, (int *)0, 0}
	};

	for (int o; (o = getopt_long(ac, av, NULL, opt, NULL)) != -1;)
	{
		if (o == 'H')
		{
			uint32_t	net4;

			if ((net4 = irc_parse_inet4(optarg)) == -1)
			{
				dprintf(2, "%s: invalid host\n", av[0]);
				return (2);
			}
			ME.irc_node_addr = net4;
		}
		else if (o == 'p')
		{
			in_port_t port;

			if ((port = irc_parse_port(optarg)) == -1)
			{
				dprintf(2, "%s: invalid port\n", av[0]);
				return (2);
			}
			ME.irc_node_port = port;
		}
		else if (o == 'l')
		{
			IN.max = strtol(optarg, NULL, 10);
			if (ME.maxuser >= IRC_MAXCONNECTION || ME.maxuser == 0)
			{
				dprintf(2, "%s: unrealistic max connection\n", av[0]);
				return (2);
			}
		}
		else if (o == 'n')
		{
			ME.hostname = optarg;
		}
		else if (o == 't')
		{
			size_t	max
		}
#ifdef IRC_ALLOW_BRIDGE_CONNECTION
		else if (o == 'b')
			IN.bridge_only = 1;
#endif
		else if (o == 'h')
		{
			usage();
			return (0);
		}
		else
		{
			usage();
			return (2);
		}
	}
/*  set default setting if omitted */
	if (ME.hostname == (char *)0)
		irc.hostname = IRC_DEFAULT_HOSTNAME;
	if (ME.irc_node_port == 0)
		ME.irc_node_port = htons(IRC_DEFAULT_PORT);
	ME.intype = IRC_TYPE_SERVER;
	ME.addr.sin_family = AF_INET;
	if (IN.max == 0)
		IN.max = IRC_DEFAULT_MAXIN;
/*  creating interface to listen */
	if ((ME.sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		dprintf(2, "%s: could not create socket\n", av[0]);
		return (1);
	}
	if ((bind(ME.sockfd, &ME.addr, sizeof ME.addr)) < 0)
	{
		dprintf(2, "%s: could not bind interface\n", av[0]);
		return (1);
	}
	if ((listen(ME.sockfd, IN.max)) < 0)
	{
		dprintf(2, "%s: could not listen on interface", av[0]);
		return (1);
	}
	errno = 0;
	for (;;)
	{
		fd_set	rfds;
		fd_set	wfds;
		int		ret;
		struct timeval timeout = {
			.tv_sec = 1, .tv_usec = 0
		};

		irc_set_rfds(&rfds);
		irc_set_wfds(&wfds);
		if ((ret = select(IN.max + 10, rfds, wfds, NULL, &timeout)) < 0)
		{
			dprintf(2, "%s: select error: %s\n", av[0], strerror(errno));
			return (1);
		}
		else if (ret > 0)
		{
			for (int i = 0; i < IN.max; i++)
			{
				if (FD_ISSET(IN._conn[i].desc.sockfd, &rfds))
					irc_add_pending_task();
				if (FD_ISSET(IN._conn[i].desc.sockfd, &wfds))
				{
					irc_write_pending_msg(IN._conn + i);
				}
			}
		}
		irc_ping_idle();
		irc_do_pending_task();
	}
	return (0);
}

void	irc_add_pending_task(void *request)
{
	__socket_type_t *desc;

	desc = (__socket_type_t *)request;
	if (desc->intype == IRC_TYPE_UNDEFINED)
	{
		return ;
	}
	/* task to do */
}

#define irc_write_msg(fd, buf, length) send(fd, buf, length, 0)

void	irc_write_pending_msg(void *pendtask)
{
	__socket_type_t *desc;

	desc = (__socket_type_t *)pendtask;
	if ((irc_write_msg(desc->sockfd, desc->msg, strlen(desc->msg))) < 0)
	{
		return ;
	}
	free(desc->msg);
	desc->msg = (char *)0;
	((__socket_type_t *)request)->nmode = IRC_NET_STANDBY;
}

void	irc_set_rfds(fd_set *rfds)
{
	FD_ZERO(rfds);
	for (int fmin = 3; fmin < IN.max; fmin++)
	{
		if (IN._conn[fmin].desc.nmode == IRC_NET_STANDBY)
			FD_SET(IN._conn[fmin].desc.sockfd, rfds);
	}
}

void	irc_set_wfds(fd_set *wfds)
{
	FD_ZERO(wfds);
	for (int fmin = 3; fmin < IN.max; fmin++)
	{
		if (IN._conn[fmin].desc.nmode == IRC_NET_PENDING)
			FD_SET(IN._conn[fmin].desc.sockfd, wfds);
	}
}

int		irc_parse_inet4(const char *s)
{
	uint32_t	inet4 = 0;

	for (int i = 0; i < 4; i++)
	{
		if (!strchr("0123456789", *s))
			return -1;
		inet4 |= atoi(s) << (24 - (8 * i));
		while (strchr("0123456789", *s))
			s++;
		s += 1;
	}
	return htonl(inet4);
}

in_port_t	irc_parse_port(const char *s)
{
	int		p;
	char	*cp;

	cp = s;
	for (; *cp; cp++)
	{
		if (!strchr("0123456789", *cp))
			return -1;
	}
	p = atoi(s);
	if (p > 65535)
		return -1;
	return htons((in_port_t)p);
}

void	usage(void)
{
	dprintf(2, "usage: %s [option...]\n");
	dprintf(2, "       --host=HOST Interface to listen, default listens all interface\n");
	dprintf(2, "       --port=PORT Port to listen, default port is 6667\n");
	dprintf(2, "       --limits=MAXUSERS Limits incoming connection to MAXUSERS, default is sysconf(_SC_OPEN_MAX)\n");
	dprintf(2, "                         It will deny connection on ENFILE or EMFILE\n");
	dprintf(2, "       --hostname=NAME Name of IRC, default is irc.localhost\n");
	dprintf(2, "       --maxtask=MAXTASK The number of simultaneous request it can take,\n");
	dprintf(2, "                         default is 256\n");
#ifdef IRC_ALLOW_BRIDGE_CONNECTION
	dprintf(2, "       --bridge Refuses incoming client connection, serves as link only\n");
#endif
	dprintf(2, "       --help Show this message\n")
}
