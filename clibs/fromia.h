#ifndef FROMIA_H
#define FROMIA_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>

#define main <void> int main()
#define subVoid void
#define intFunc int
#define floatFunc float
#define charFunc char
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

// Functions
#define <subVoid> {
#define }<subVoid> }
#define <intFunc> {
#define }<intFunc> }
#define <floatFunc> {
#define }<floatFunc> }
#define <charFunc> {
#define }<charFunc> }>

// If statements
#define ifCond(cond) if (cond) {
#define elifCond(cond) else if (cond) {
#define elseCond else {
#define }if }
#define }elif }
#define }else }

// Class definition
#define class(name) typedef struct name name; struct name {
#define }class ;

// Objective-C like definitions
#define @interface(name) typedef struct name name; struct name {
#define @end ;
#define @property(type, name) type name;
#define @implementation(name)
#define @endImpl
#define @synthesize(name)
#define @method(retType, name) retType name

// Fromia Import syntax
#define Fromia_Import(header) #include header

// Fromia Function syntax
#define Fromia_Function(retType, name) retType

// From.ff3.func
#define From_ff3_func(class, syscall) class syscall

// syscall.ifdef()
#define syscall_ifdef(symbol) #ifdef symbol
#define syscall_endif #endif

#ifdef __cplusplus
}
#endif

#endif // FROMIA_H

#ifdef __cplusplus
}
#endif

namespace Fromia {
  const char* Usr = getenv("USER"); // Fetch user
  const char* Home = getenv("HOME"); // Fetch home directory

  void log(const char* message) {
      printf("[LOG] %s\n", message);
  }

  void error(const char* message) {
      fprintf(stderr, "[ERROR] %s\n", message);
  }

  void endProgram(int code) {
      exit(code);
  }
}

#endif // FROMIA_H
