/*
 *  File: input.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _INPUT_
#define _INPUT_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

EXTERN 	ubyte (read_portb(uword port));					        /* read 8-bit port. */
EXTERN 	uword (read_portw(uword port));					        /* read 16-bit port. */
EXTERN 	udword (read_portdw(uword port));                          /* read 32-bit port. */

#endif
