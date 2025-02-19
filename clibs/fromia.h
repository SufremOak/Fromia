#ifndef FROMIA_H
#define FROMIA_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>

#define main <void> int main()
#define subVoid void

#define execute(x) exit(x)
#define extern "C"

typedef struct {
  void(*onStart)(int);
} FromiaSystem;

static inline void _fromia_onStart(intCode) { execute(code); }
static const FromiaSystem System = { _fromia_onStart };

typedef struct {
  struct {
   int (*printf)(const char*, ...);
  } sysFunc;
} FromiaEs;

static const FromiaEs Es = { { printf  } };

#define <subVoid> {
#define }<subVoid> }

#ifdef __cplusplus
}
#endif

#endif // FROMIA_H
