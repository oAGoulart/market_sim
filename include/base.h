/*
  19:50:00 30/04/2022, Augusto Goulart 1901560080
*/
#ifndef BASE_H
#define BASE_H 1

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

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
		str "\n" \
    "FILE: " __FILE__ " LINE: " __xstr(__LINE__) "\n" \
  ); \
}
#else
#define __pdebug(str)
#endif

/* fatal error */
#define __throw(str) \
{ \
  __pdebug(__c(41, " FATAL ") "\t" str); \
  abort(); \
}

/* rand helper */
#define __rand(low, high) rand() % (high - low + 1) + low

#endif /* BASE_H */
