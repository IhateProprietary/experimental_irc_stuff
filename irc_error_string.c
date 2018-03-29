#include "irc_error.h"
#include "irc_reply.h"

irc_no_t	irc_errstring[] = {
	{ERR_UNKNOW, (char *)0},
	{ERR_NOSUCHNICK, "%s :No such nick/channel"},
	{ERR_NOSUCHSERVER, "%s :No such server"},
	{ERR_NOSUCHCHANNEL, "%s :No such channel"},
	{ERR_CANNOTSENDTOCHAN, "%s :Cannot send to channel"},
	{ERR_TOOMANYCHANNEL, "%s :You have joined too many channels"},
	{ERR_WASNOSUCHNICK, "%s :There was no such nickname"},
	{ERR_TOOMANYTARGETS, "%s :Duplicate recipients. No message delivered"},
	{ERR_UNKNOW, (char *)0},
	{ERR_NOORIGIN, ":No origin specified"},
	{ERR_UNKNOW, (char *)0},
	{ERR_NORECIPIENT, ":No recipient given (%s)"},
	{ERR_NOTEXTTOSEND, ":No text to send"},
	{ERR_NOTOPLEVEL, "%s :No toplevel domain specified"},
	{ERR_WILDTOPLEVEL, "%s :Wildcard in toplevel domain"},
	{ERR_UNKNOWNCOMMAND, "%s :Unknown command"},
	
};
