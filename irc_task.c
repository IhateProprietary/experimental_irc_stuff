#include <unistd.h>
#include "irc_task.h"
#include "irc_socket.h"
#include "irc_command.h"
#include <stdlib.h>

irc_task_pending_t	task;

void	irc_add_pending_task(void *request)
{
	__socket_common_t *desc;
	irc_task_t	*slot;
	ssize_t		bufs;
	char		buf[65536];
	int			sockfd;

	desc = (__socket_common_t *)request;
	if (desc->busy)
	{
		desc->nmode = IRC_NET_READY;
		return ;
	}
	sockfd = desc->sockfd;
	if ((slot = irc_get_task_slot()) == (irc_task_t *)0)
	{
		return ;
	}
	if ((bufs = recv(sockfd, buf, 65536, 0)) < 0)
	{
		desc->nmode = IRC_NET_PENDING;
		desc->msg = /*write error message to send*/;
	}
}

int			irc_init_task_slot(void)
{
	if ((task.slot = malloc(sizeof(irc_task_t) * task.max)) == (irc_task_t *)0)
		return (1);
	memset(task.slot, 0, sizeof(irc_task_t) * task.max);
	return (0);
}

irc_task_t	*irc_get_task_slot(void)
{
	for (int i = 0; i < task.max; i++)
	{
		if (task.slot[i].stat.type == IRC_TASK_NONE)
			return (task.slot + i);
	}
	return ((irc_task_t *)0);
}
