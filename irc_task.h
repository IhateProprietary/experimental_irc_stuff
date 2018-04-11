#ifndef __IRC_TASK_H__
# define __IRC_TASK_H__

# include <stddef.h>
# include "irc_socket.h"

# define IRC_DEFAULT_MAX_TASK	1024

# define IRC_TASK_NONE		0
# define IRC_TASK_PRIVTASK	1
# define IRC_TASK_REPLY		2
# define IRC_TASK_ERROR		3

extern irc_task_pending_t	task;

typedef struct
{
	uint32_t	type:3;
	uint32_t	num:9;
	uint32_t	state:20;
}	__task_type_t;

typedef struct
{
	__task_type_t	stat;
	void			(*func)();
	char			**argv;
	irc_socket_t	*target;
}	irc_task_t;

typedef struct
{
	irc_task_t	*slot;
	size_t		pending;
	size_t		max;
}	irc_task_pending_t;

void		irc_add_pending_task(void *request);
void		irc_do_pending_task(void);
irc_task_t	*irc_get_task_slot(void);
#endif
