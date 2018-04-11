#ifndef __HASHLIB_H__
# define __HASHLIB_H__

# include <stdint.h>

# define HASH_SEARCH	0
# define HASH_NOSEARCH	1

typedef struct	bucket_s
{
	char			*key;
	void			*object;
	struct bucket_s	*next;
	uint32_t		khash;
}	BUCKET;

typedef struct
{
	BUCKET	**buckets;
	int		nentries;
	int		nbuckets;
}	HASHTABLE;

HASHTABLE	*hash_init(size_t hsize);
BUCKET		*hash_search(HASHTABLE *table, char *key);
BUCKET		*hash_insert(HASHTABLE *table, char *key, int mode);
uint32_t	hash_string(char *key);

#endif
