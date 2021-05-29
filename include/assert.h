#ifndef _ADAMANTINE_ASSERT_H
#define _ADAMANTINE_ASSERT_H

#define KERNEL_ONLY

#if defined(__cplusplus)
extern "C" {
#endif

void __assert(char *msg, char *filename, unsigned int lineno);

#if defined(__cplusplus)
}
#endif

#ifndef assert
#define assert(msg)     __assert(msg, __FILE__, __LINE__);
#endif

#endif  // !_ADAMANTINE_ASSERT_H
