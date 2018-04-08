//#include <stddef.h>
#include <stdint.h>

uint32_t	hash_string(char *s)
{
	uint32_t	hash;

	for (hash = 0; *s != 0; s++)
	{
		hash ^= (*s << 16) | *s;
		hash *= 16777619;
	}
	return (hash);
}

#if 0

# include <stdio.h>

int		main(int ac, char **av)
{
	(void)ac;
	dprintf(1, "%#x", hash_string(av[1]));
}

#endif
