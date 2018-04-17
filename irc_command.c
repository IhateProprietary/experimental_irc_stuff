#include "irc_command.h"
#include "irc_task.h"

irc_command_t irc_cmd[] = {
	{"PASS", {IRC_ARGV_REQUIRED},
	 irc_PASS},
	{"NICK", {IRC_ARGV_REQUIRED, IRC_ARGV_SERVER},
	 irc_NICK},
	{"USER", {IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED,
			  IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED},
	 irc_USER},
	{"SERVER", {IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED,
				IRC_ARGV_REQUIRED},
	 irc_SERVER},
	{"OPER", {IRC_ARGV_REQUIRED, IRC_ARV_REQUIRED},
	 irc_OPER},
	{"QUIT", {IRC_ARGV_REQUIRED},
	 irc_QUIT},
	{"SQUIT", {IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED},
	 irc_SQUIT},
	{"JOIN", {IRC_ARGV_REQUIRED, IRC_ARGV_OPTIONAL},
	 irc_JOIN},
	{"PART", {IRC_ARGV_REQUIRED},
	 irc_PART},
	{"MODE", {IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED,
			  IRC_ARGV_OPTIONAL, IRC_ARGV_OPTIONAL,
			  IRC_ARGV_OPTIONAL},
	 irc_MODE},
	{"TOPIC", {IRC_ARGV_REQUIRED, IRC_ARGV_OPTIONAL},
	 irc_TOPIC},
	{"NAMES", {IRC_ARGV_REQUIRED},
	 irc_NAMES},
	{"LIST", {IRC_ARGV_REQUIRED},
	 irc_LIST},
	{"INVITE", {IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED},
	 irc_INVITE},
	{"KICK", {IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED,
			  IRC_ARGV_OPTIONAL},
	 irc_KICK},
/*  Server   */
	{"VERSION", {IRC_ARGV_OPTIONAL},
	 irc_VERSION},
	{"STATS", {IRC_ARGV_OPTIONAL, IRC_ARGV_OPTIONAL},
	 irc_STATS},
	{"LINKS", {IRC_ARGV_OPTIONAL, IRC_ARGV_OPTIONAL},
	 irc_LINKS},
	{"TIME", {IRC_ARGV_OPTIONAL},
	 irc_TIME},
	{"CONNECT", {IRC_ARGV_REQUIRED, IRC_ARGV_OPTIONAL},
	 irc_CONNECT},
	{"TRACE", {IRC_ARGV_REQUIRED},
	 irc_TRACE},
	{"ADMIN", {IRC_ARGV_OPTIONAL},
	 irc_ADMIN},
	{"INFO", {IRC_ARGV_OPTIONAL},
	 irc_INFO},
/*   Message   */
	{"PRIVMSG", {IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED},
	 irc_PRIVMSG},
	{"NOTICE", {IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED},
	 irc_NOTICE},
/*   user based query  */
	{"WHO", {IRC_ARGV_REQUIRED, IRC_ARGV_OPTIONAL},
	 irc_WHO},
	{"WHOIS", {IRC_ARGV_REQUIRED, IRC_ARGV_OPTIONAL},
	 irc_WHOIS},
	{"WHOWAS", {IRC_ARGV_REQUIRED, IRC_ARGV_OPTIONAL,
				IRC_ARGV_OPTIONAL},
	 irc_WHOWAS},
/*  Miscellaneous   */
	{"KILL", {IRC_ARGV_REQUIRED, IRC_ARGV_REQUIRED},
	 irc_KILL},
	{"PING", {IRC_ARGV_REQUIRED, IRC_ARGV_OPTIONAL},
	 irc_PING},
	{"PONG", {IRC_ARGV_REQUIRED, IRC_ARGV_OPTIONAL},
	 irc_PONG},
	{"ERROR", {IRC_ARGV_REQUIRED}
	 irc_ERROR},
/*  Optional  */
	{"AWAY", {IRC_ARGV_REQUIRED},
	 irc_AWAY},
	{"USERS", {IRC_ARGV_OPTIONAL},
	 irc_USERS},
	{"ISON", {IRC_ARGV_REQUIRED},
	 irc_ISON},
};

#include "hashlib.h"

HASHTABLE	*irc_hc;

int		irchc_init(void)
{
	if ((irc_hashcmd = hash_init(sizeof(irc_cmd) & ~3 * 4)) == (HASHTABLE *)0)
		return (1);
	for (BUCKET *buck,int i = 0; i < sizeof irc_cmd; i++)
	{
		if ((buck = hash_insert(irc_hashcmd, irc_cmd[i].cmd, HASH_NOSEARCH)) == (BUCKET *)0)
		{
			hash_destroytable(irc_hashcmd, (void (*)())0);
			return (1);
		}
		buck->object = irc_cmd + i;
	}
	return (0);
}

irc_cfunc_t	irchc_search(char *scmd)
{
	BUCKET			*buck;
	irc_command_t	*cmd;

	if ((buck = hash_search(irc_hc, scmd)) == (BUCKET *)0)
		return (irc_cfunc_t)0;
	cmd = (irc_command_t *)buck->object;
	return cmd->func;
}
