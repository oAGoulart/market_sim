/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#ifndef BASE_H
#define BASE_H 1

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

/* stringify */
#define __str(s) #s
/* expand and stringify */
#define __xstr(s) __str(s)

typedef uint8_t boolean_t;

/* terminal color manipulation */
#if !defined(NCOLOR)
#define __c(c, str) "\033[" __str(c) "m" str "\033[m"
#define __cs(cs, str) "\033[" cs "m" str "\033[m"
#else
#define __c(c, str) str
#define __cs(cs, str) str
#endif

/* terminal cursor manipulation */
#define __csave() printf("\033\067")
#define __crestore() printf("\033\070")
#define __cmove(x, y) printf("\033[%lu;%luH", x, y)

/* terminal flush */
#define __tflush() printf("\033[1;1H\033[2J")


/* debugging helper */
#if !defined(NDEBUG)
#define __pdebug(str) \
{ \
  printf( \
		"%s\n" \
    "FILE: " __FILE__ " LINE: " __xstr(__LINE__) "\n" \
    "FUNC: %s\n", str, __func__ \
  ); \
}
#else
#define __pdebug(str)
#endif

/* exception handling */
#define __exception_invalid_argument __c(41, " FATAL ") "\tInvalid argument"
#define __exception_null_pointer __c(41, " FATAL ") "\tNULL pointer"
#define __exception_unimplemented __c(41, " FATAL ") "\tUnimplemented"
#define __exception_unexpected __c(41, " FATAL ") "\tUnexpected"
#define __exception_realloc_failed __c(41, " FATAL ") "\trealloc() failed"
#define __exception_malloc_failed __c(41, " FATAL ") "\tmalloc() failed"
#define __exception_out_of_range __c(41, " FATAL ") "\tIndex out of range"
#define __exception_fputc_failed __c(41, " FATAL ") "\tfputc() failed"
#define __exception_fputs_failed __c(41, " FATAL ") "\tfputs() failed"
#define __exception_fgets_failed __c(41, " FATAL ") "\tfgets() failed"
#define __exception_fscanf_failed __c(41, " FATAL ") "\tfscanf() failed"
#define __exception_snprintf_failed __c(41, " FATAL ") "\tsnprintf() failed"

#define __throw(e) \
{ \
  __pdebug(e); \
  __builtin_trap(); \
}

/* rand helper */
#define __rand(low, high) rand() % (high - low + 1) + low

#endif /* BASE_H */
