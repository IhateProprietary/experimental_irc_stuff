#include <stdint.h>
#include <stdlib.h>

#include "hashlib.h"

HASHTABLE	*hash_init(size_t hsize)
{
	HASHTABLE	*table;
	BUCKET		**buckets;

	if ((table = (HASHTABLE *)malloc(sizeof *table)) == (HASHTABLE *)0)
		return (HASHTABLE *)0;
	if ((buckets = (BUCKET **)malloc(sizeof *buckets * hsize)) == (BUCKET **)0)
	{
		free(table);
		return (HASHTABLE *)0;
	}
	table->buckets = buckets;
	table->nentries = 0;
	table->nbuckets = hsize;
	for (int i = 0; i < hsize; i++)
		buckets[i] = (BUCKET **)0;
	return table;
}

BUCKET		*hash_search(HASHTABLE *table, char *key)
{
	BUCKET		*buck;
	uint32_t	khash;

	khash = hash_string(key);
	buck = table->buckets[khash % table->nbuckets];
	while (buck)
	{
		if (buck->khash == khash)
			return buck;
		buck = buck->next;
	}
	return (BUCKET *)0;
}

BUCKET		*hash_insert(HASHTABLE *table, char *key, int mode)
{
	BUCKET		*buck;
	uint32_t	khash;

	buck = mode ? (BUCKET *)0 : hash_search(table, key);
	if (buck == (BUCKET *)0)
	{
		BUCKET	*fitem;

		if ((buck = (BUCKET *)malloc(sizeof *buck)) == (BUCKET *)0)
			return (BUCKET *)0;
		khash = hash_string(key);
		buck->key = key;
		buck->object = (void *)0;
		buck->next = (BUCKET *)0;
		buck->khash = khash;
		fitem = table->buckets[khash % table->nbuckets];
		table->buckets[khash % table->nbuckets] = buck;
		buck->next = fitem;
	}
	return buck;
}

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
