#ifndef MEM_DBG_HASH_H
#define MEM_DBG_HASH_H

#include "../hash_func.h"
#include <string.h>

#define DBG_HASH_SIZE 1500

struct mem_dbg_entry {
	const char *file;
	const char *func;
	unsigned long line;
	unsigned long size;	/* total alloc'd size */
	unsigned long no_fragments;
	struct mem_dbg_entry *next;
};

typedef struct mem_dbg_entry* mem_dbg_htable_t[DBG_HASH_SIZE];

int dbg_ht_update(mem_dbg_htable_t htable, const char *file, const char *func, unsigned long line, unsigned long size);
void dbg_ht_free(mem_dbg_htable_t htable);
void dbg_ht_init(mem_dbg_htable_t htable);

static inline unsigned int get_dbg_hash(const char *file, const char *func, unsigned long line)
{
	str s1, s2;
	char buf[255];

	s1.s = (char *)file;
	s1.len = strlen(file);
	s2.len = strlen(func);
	memcpy(buf, func, s2.len);
	buf[0] += line;
	buf[1] += line >> 4;
	s2.s = buf;

	return core_hash(&s1, &s2, DBG_HASH_SIZE);
}

#endif