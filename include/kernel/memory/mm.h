/*
 *  File: mem-util.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_memORY_UTILITY
#define ADAMANTINE_memORY_UTILITY

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

// Declare the allocation type:
typedef struct 
{
	byte 				status;
	size_t 				size;
} alloc_t;

EXTERN	void mm_init(udword kernel_end);
EXTERN	void paging_map_virtual_to_physical(udword virt, udword physical);

EXTERN	void *pmalloc(size_t size);
EXTERN	void *malloc(size_t size);
EXTERN	void pfree(void *mem);
EXTERN	void free(void *mem);

EXTERN 	void *memchr(const void *str, int c, size_t n);
EXTERN 	int memcmp(const void *str1, const void *str2, size_t n);
EXTERN 	void *memcpy(void *dest, const void *src, size_t n);
EXTERN 	void *memmove(void *dest, const void *src, size_t n);
EXTERN 	void *memset(void *dest, int c, size_t n);
EXTERN	void *memset16(void *pointer,  udword value, size_t size);

udword	kmalloc_int(udword size, udword align, udword *physical_address);
udword	kmalloc_a(udword size);
udword	kmalloc_p(udword size_t, udword *physical_address);
udword	kmalloc_ap(udword size, udword *physical_address);
udword	kmalloc(udword size);

#endif	// !ADAMANTINE_memORY_UTILITY
