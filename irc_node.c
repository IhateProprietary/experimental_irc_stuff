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

#include "irc_server.h"

#ifdef IRC_ALLOW_BRIDGE_CONNECTION
# define IRC_DEFAULT_MAXLINK 16
irc_node_t	*other;
size_t		maxlink;
#endif

irc_node_t	ME;

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

int		main(int ac, char **av)
{
	static const struct option opt[] = {
		{"host", required_argument, 0, 'h'},
		{"port", required_argument, 0, 'p'},
		{"limits", required_argument, 0, 'l'},
		{"hostname", required_argument, 0, 'n'}
#ifdef IRC_ALLOW_BRIDGE_CONNECTION
		{"slimits", required_argument, 0, 's'},
		{"bridge", no_argument, 0, 'b'},
#endif
		{(char *)0, 0, (int *)0, 0},
	};

	for (int o; (o = getopt_long(ac, av, NULL, opt, NULL)) != -1;)
	{
		if (o == 'h')
		{
			uint32_t	net4;

			if ((net4 = irc_parse_inet4(optarg)) == -1)
			{
				dprintf(2, "%s: invalid host", av[0]);
				return (2);
			}
			ME.addr.sin_addr.s_addr = net4;
		}
		else if (o == 'p')
		{
			in_port_t port;

			if ((port = irc_parse_port(optarg)) == -1)
			{
				dprintf(2, "%s: invalid port", av[0]);
				return (2);
			}
			ME.addr.sin_port = port;
		}
		else if (o == 'l')
		{
			ME.maxuser = strtol(optarg, NULL, 10);
			if (ME.maxuser >= UINT64_MAX - 0xffff || ME.maxuser == 0)
			{
				dprintf(2, "%s: unrealistic max user", av[0]);
				return (2);
			}
		}
		else if (o == 'n')
		{
			ME.hostname = optarg;
		}
#ifdef IRC_ALLOW_BRIDGE_CONNECTION
		else if (o == 's')
		{
			maxlink = strtol(optarg, NULL, 10);
			if (maxlink >= UINT64_MAX - 0xffff)
			{
				dprintf(2, "%s: unrealistic max server link", av[0]);
				return (2);
			}
		}
		else if (o == 'b')
			ME.maxuser = 0;
#endif
		else
		{
			usage();
			return (2);
		}
	}
}

int		irc_parse_inet4(char *s)
{
	uint32_t	inet4 = 0;

	for (int i = 0; i < 4; i++)
	{
		if (strchr("0123456789", *s))
			return -1;
		inet4 |= atoi(s) << (24 - (8 * i));
		while (strchr("0123456789", *s))
			s++;
		s += 1;
	}
	return inet4;
}

in_port_t	irc_parse_port(char *s)
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
	return (in_port_t)p;
}

void	usage(void)
{
	dprintf(1, "usage %s [option...]");
}
