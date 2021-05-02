/*
   Copyright (c) 2011-2016  mingw-w64 project

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#ifdef __MINGW64__
#include <sys/timeb.h>
#endif

#ifndef WIN_PTHREADS_TIME_H
#define WIN_PTHREADS_TIME_H

/* Posix timers are supported */
#ifndef _POSIX_TIMERS
#define _POSIX_TIMERS           200809L
#endif

/* Monotonic clocks are available.  */
#ifndef _POSIX_MONOTONIC_CLOCK
#define _POSIX_MONOTONIC_CLOCK  200809L
#endif

/* CPU-time clocks are available.  */
#ifndef _POSIX_CPUTIME
#define _POSIX_CPUTIME          200809L
#endif

/* Clock support in threads are available.  */
#ifndef _POSIX_THREAD_CPUTIME
#define _POSIX_THREAD_CPUTIME   200809L
#endif

#ifndef __winpthreads_clockid_t_defined
typedef int __winpthreads_clockid_t;
#define __winpthreads_clockid_t_defined 1
#endif  /* __winpthreads_clockid_t_defined */

#if defined(__MINGW64__) && !defined (__clockid_t_defined)
typedef __winpthreads_clockid_t clockid_t;
#define __clockid_t_defined 1
#endif

#ifndef __WINPTHREADS_TIMER_ABSTIME
#define __WINPTHREADS_TIMER_ABSTIME   1
#endif
#ifndef TIMER_ABSTIME
#define TIMER_ABSTIME   1
#endif

#ifndef __WINPTHREADS_CLOCK_REALTIME
#define __WINPTHREADS_CLOCK_REALTIME              0
#endif
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME              0
#endif

#ifndef __WINPTHREADS_CLOCK_MONOTONIC
#define __WINPTHREADS_CLOCK_MONOTONIC             1
#endif
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC             1
#endif

#ifndef __WINPTHREADS_CLOCK_PROCESS_CPUTIME_ID
#define __WINPTHREADS_CLOCK_PROCESS_CPUTIME_ID    2
#endif
#ifndef CLOCK_PROCESS_CPUTIME_ID
#define CLOCK_PROCESS_CPUTIME_ID    2
#endif

#ifndef __WINPTHREADS_CLOCK_THREAD_CPUTIME_ID
#define __WINPTHREADS_CLOCK_THREAD_CPUTIME_ID     3
#endif
#ifndef CLOCK_THREAD_CPUTIME_ID
#define CLOCK_THREAD_CPUTIME_ID     3
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Make sure we provide default for WINPTHREAD_API, if not defined.  */
#pragma push_macro("WINPTHREAD_API")
#ifndef WINPTHREAD_API
#define WINPTHREAD_API
#endif

/* These should really be dllimport'ed if using winpthread dll */
int __cdecl WINPTHREAD_API nanosleep(const struct timespec *request, struct timespec *remain);

int __cdecl WINPTHREAD_API clock_nanosleep(__winpthreads_clockid_t clock_id, int flags, const struct timespec *request, struct timespec *remain);
int __cdecl WINPTHREAD_API __pthread_clock_getres(__winpthreads_clockid_t clock_id, struct timespec *res);
int __cdecl WINPTHREAD_API __pthread_clock_gettime(__winpthreads_clockid_t clock_id, struct timespec *tp);
int __cdecl WINPTHREAD_API __pthread_clock_settime(__winpthreads_clockid_t clock_id, const struct timespec *tp);

#ifdef __MINGW64__
inline int clock_getres(__winpthreads_clockid_t clock_id, struct timespec *res) { return __pthread_clock_getres(clock_id, res); }
inline int clock_gettime(__winpthreads_clockid_t clock_id, struct timespec *tp) { return __pthread_clock_gettime(clock_id, tp); }
inline int clock_settime(__winpthreads_clockid_t clock_id, const struct timespec *tp) { return __pthread_clock_settime(clock_id, tp); }
#endif

#pragma pop_macro("WINPTHREAD_API")

#ifdef __cplusplus
}
#endif

#endif /* WIN_PTHREADS_TIME_H */

