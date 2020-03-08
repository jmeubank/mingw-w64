/* -- shmem.h --
 *
 * The __SHMEM mechanism is for sharing named pointers among the instances of a
 * static library compiled into separate modules (binaries or shared libraries)
 * in one runtime program. It's used in libgcc and libstdc++ to be able to
 * propagate exceptions out of shared libraries even which libgcc and libstdc++
 * are compiled in statically.
 *
 * This code is released into the public domain without warranty; it may be
 * freely used and redistributed.
 */


#if defined(_WIN32) || defined(_WIN64)
#define HAVE_SHMEM_IMPL 1
#else
#define HAVE_SHMEM_IMPL 0
#endif

/*
#if defined(SHARED) || defined(DLL_EXPORT)
#define USE_SHMEM 0
#else
*/
#define USE_SHMEM 1
/*
#endif
*/

#if HAVE_SHMEM_IMPL && USE_SHMEM


#define SHMEM_NAMESPACE __shmem_winpthreads_


#ifdef __cplusplus
#define __SHMEM_CLINK extern "C"
#else
#define __SHMEM_CLINK
#endif


#define __SHMEM_CONCAT2(a, b) __CONCAT2_INDIR(a, b)
#define __CONCAT2_INDIR(a, b) a ## b
#define __SHMEM_CONCAT3(a, b, c) __CONCAT3_INDIR(a, b, c)
#define __CONCAT3_INDIR(a, b, c) a ## b ## c


__SHMEM_CLINK void* __SHMEM_CONCAT2(SHMEM_NAMESPACE, grab)(const char *name, int size, void (*initfunc)(void *));


#define __SHMEM_DEFINE(type, name) \
 type* __SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name) = 0; \
 type* __SHMEM_CONCAT3(SHMEM_NAMESPACE, grabber_, name)(); \
 type* __SHMEM_CONCAT3(SHMEM_NAMESPACE, grabber_, name)() \
 { \
   return (type*)__SHMEM_CONCAT2(SHMEM_NAMESPACE, grab)(# name, sizeof(type), 0); \
 }

#define __SHMEM_DEFINE_INIT(type, name, initval) \
 type* __SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name) = 0; \
 __SHMEM_CLINK void __SHMEM_CONCAT3(SHMEM_NAMESPACE, init_, name)(void *mem) \
 { \
   type temp = initval; \
   *((type*)mem) = temp; \
 } \
 type* __SHMEM_CONCAT3(SHMEM_NAMESPACE, grabber_, name)() \
 { \
   return (type*)__SHMEM_CONCAT2(SHMEM_NAMESPACE, grab)(# name, sizeof(type), __SHMEM_CONCAT3(SHMEM_NAMESPACE, init_, name)); \
 }

#define __SHMEM_DEFINE_ARRAY(type, name, size) \
 type* __SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name) = 0; \
 type* __SHMEM_CONCAT3(SHMEM_NAMESPACE, grabber_, name)() \
 { \
   return (type*)__SHMEM_CONCAT2(SHMEM_NAMESPACE, grab)(# name, sizeof(type) * size, 0); \
 }


#define __SHMEM_DECLARE(type, name) \
 extern type* __SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name); \
 type* __SHMEM_CONCAT3(SHMEM_NAMESPACE, grabber_, name)();


#define __SHMEM_GET(name) \
 (*( \
 (__SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name)) \
 ? \
 (__SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name)) \
 : \
 ((__SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name)) = __SHMEM_CONCAT3(SHMEM_NAMESPACE, grabber_, name)()) \
 ))

#define __SHMEM_GET_ARRAY(name) \
 ( \
 (__SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name)) \
 ? \
 (__SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name)) \
 : \
 ((__SHMEM_CONCAT3(SHMEM_NAMESPACE, ptr_, name)) = __SHMEM_CONCAT3(SHMEM_NAMESPACE, grabber_, name)()) \
 )


#else


#define __SHMEM_DEFINE(type, name) type name;
#define __SHMEM_DEFINE_INIT(type, name, initval) type name = initval;
#define __SHMEM_DEFINE_ARRAY(type, name, size) type name[size];
#define __SHMEM_DECLARE(type, name) extern type name;
#define __SHMEM_GET(name) name
#define __SHMEM_GET_ARRAY(name) name


#endif
