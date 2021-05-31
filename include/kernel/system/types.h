#ifndef _ADAMANTINE_TYPES_H
#define _ADAMANTINE_TYPES_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

/* Check if the '_TIME_T_' type has been defined */
#ifndef _TIME_T_										// If it hasn't,
#define _TIME_T_										// define it,
typedef unsigned long time_t;							// and create 'time_t' type
#endif	// !_TIME_T_

/* Check if the '_KERNEL_T_' type has been defined */
#ifndef _KERNEL_T_										// If it hasn't
#define _KERNEL_T_										// define it,
typedef void kernel_t;									// and create 'kernel_t' type
#endif	// !_KERNEL_T_
#endif	// !_ADAMANTINE_TYPES_H
