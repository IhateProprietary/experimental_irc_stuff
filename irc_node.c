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

irc_node_t	ME;
irc_node_t	*irc_node;

int		main(int ac, char **av)
{
	
}

static int		ifconf_en0(int sockfd, void *buf, size_t size)
{
	struct ifconf 	ifconf;
	struct ifreq	*ifreq;

#if defined(__linux__)
#define SIZEOF_IFREQ sizeof(*ifreq)
#define IS_IPV4_ETHERNET(x) (memcmp((x)->ifr_name, "en", 2) == 0)
	ifconf.ifc_len = 0;
	ifconf.ifc_buf = NULL;
	if ((ioctl(sockfd, SIOCGIFCONF, &ifconf)) < 0)
		return (1);
	ifconf.ifc_buf = alloca(ifconf.ifc_len);
#else
#define IFCONF_SIZE 1024
#define SIZEOF_IFREQ IFNAMSIZ + ifreq->ifr_addr.sa_len
#define IS_IPV4_ETHERNET(x) (memcmp((x)->ifr_name, "en", 2) == 0 && (x)->ifr_addr.sa_family == AF_INET)
	ifconf.ifc_len = IFCONF_SIZE;
	ifconf.ifc_buf = alloca(IFCONF_SIZE);
#undef IFCONF_SIZE
#endif
	if ((ioctl(sockfd, SIOCGIFCONF, &ifconf)) < 0)
		return (1);
	ifreq = (struct ifreq *)ifconf.ifc_buf;
	for (size_t offset; ifconf.ifc_len; ifreq = ((void *)ifreq + offset), ifconf.ifc_len -= offset)
	{
		if (IS_IPV4_ETHERNET(ifreq))
		{
			memcpy(buf, &ifreq->ifr_addr, size);
			return (0);
		}
		offset = SIZEOF_IFREQ;
	}
	return (1);
#undef SIZEOF_IFREQ
#undef IS_IPV4_ETHERNET
}
