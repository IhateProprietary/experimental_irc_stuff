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


int		main(int ac, char **av)
{

}

int		irc_parse_init(int ac, char **av)
{
	static const struct option[] = {
		{"host", required_argument, 0, 'h'},
		{"port", required_argument, 0, 'p'},
		{"limits", required_argument, 0, 'l'},
		{"slimits", required_argument, 0, 's'},
		{"bridge", no_argument, 0, 'b'},
		{(char *)0, 0, (int *)0, 0},
	}
}
