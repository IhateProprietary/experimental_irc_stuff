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

HASHTABLE	*hash_init(int hsize);
BUCKET		*hash_search(HASHTABLE *table, char *key);
BUCKET		*hash_insert(HASHTABLE *table, char *key, int mode);
int			hash_resizetable(HASHTABLE *table, int hsize);
void		hash_destroytable(HASHTABLE *table, void (*del)());
void		hash_delete(HASHTABLE *table, char *key, void (*del)());
uint32_t	hash_string(char *key);

#endif
