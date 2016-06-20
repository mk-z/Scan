#ifndef NVCM_GLOBAL_H
#define NVCM_GLOBAL_H

#if (defined(WIN32)||defined(_WIN32) \
  ||defined(__WIN32__)||defined(__NT__))
  #define OS_WIN32
#else
  #define OS_LINUX
#endif

#if defined(_MSC_VER)
  #define CC_MSVC
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifdef OS_WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
//#include <WINSOCK2.h>
#endif

#ifdef OS_LINUX
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <pthread.h>

#endif

#if defined(CC_MSVC)
#pragma warning(disable: 4251)
#pragma warning(disable: 4244)
#pragma warning(disable: 4275)
#pragma warning(disable: 4514)
#pragma warning(disable: 4800)
#pragma warning(disable: 4097)
#pragma warning(disable: 4706)
#pragma warning(disable: 4786)
#pragma warning(disable: 4660)
#pragma warning(disable: 4355)
#pragma warning(disable: 4231)
#pragma warning(disable: 4710)
#pragma warning(disable: 4530)
#endif

#define NAMESPACE_BEGIN(ns)	namespace ns {
#define NAMESPACE_END		};

#define USING(ns) using namespace ns;

#include <deque>
#include <list>
#include <map>
#include <vector>

USING(std)

#define DISABLE_COPY(Class) \
     Class(const Class &); \
     Class &operator=(const Class &);

template <int> class CUintForSize { public: typedef void Type; };
template <> class CUintForSize<4> { public: typedef unsigned int Type; };
template <typename T> class CUintForType : public CUintForSize<sizeof(T)> {};
typedef CUintForType<void *>::Type uintptr;

#ifndef NVCM_EXPORT
#  ifdef OS_WIN32
#    define NVCM_EXPORT __declspec(dllexport)
#  elif defined(VISIBILITY_AVAILABLE)
#    define NVCM_EXPORT __attribute__((visibility("default")))
#  endif
#  ifndef NVCM_EXPORT
#    define NVCM_EXPORT
#  endif
#endif

#ifndef NVCM_IMPORT
#  if defined(OS_WIN32)
#    define NVCM_IMPORT __declspec(dllimport)
#  else
#    define NVCM_IMPORT
#  endif
#endif

//#define NVCM_EXPORT

#endif // NVCM_GLOBAL_H

