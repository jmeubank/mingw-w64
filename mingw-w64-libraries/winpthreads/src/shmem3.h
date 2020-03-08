/* -- shmem3.h --
 *
 * The __SHMEM mechanism is for sharing named pointers among the instances of a
 * static library compiled into separate modules (binaries or shared libraries)
 * in one runtime program. It's used in libgcc, libstdc++, and winpthreads/
 * mcfgthread to create shared instances of all global or static variables.
 * This allows us to propagate exceptions out of shared libraries even when
 * libgcc and libstdc++ are compiled in statically, and to share thread-related
 * data among different instances of winpthreads/mcfgthread in the same process.
 *
 * This code is released into the public domain without warranty; it may be
 * freely used and redistributed.
 */


#ifndef __SHMEM3_H_INCLUDED
#define __SHMEM3_H_INCLUDED

#if (defined(_WIN32) || defined(_WIN64)) && !defined(SHARED) && !defined(DLL_EXPORT) && !defined(USE_SHMEM3)
#define USE_SHMEM3 1
#elif !defined (USE_SHMEM3)
#define USE_SHMEM3 0
#endif

#if USE_SHMEM3


#ifdef __cplusplus
#define __SHMEM_CLINK extern "C"
#else
#define __SHMEM_CLINK
#endif


#define __CONCAT2_INDIR(a, b) a ## b
#define __SHMEM_CONCAT2(a, b) __CONCAT2_INDIR(a, b)


#define __SHMEM_NAME(name) __SHMEM_CONCAT2(__shmem3_winpthreads_tdm_, name)
#define SHMEM_VERSION_PREFIX "__shmem3_winpthreads_tdm_"


#define __SHMEM_GET_NAMED_PTR(name) \
 ( \
 __SHMEM_NAME(local_shmem_region).head \
 ? \
 __SHMEM_NAME(local_shmem_region).head->name \
 : \
 __SHMEM_NAME(init_local_region)()->name \
 )


#define __SHMEM_DEFINE(type, name) \
 type __SHMEM_CONCAT2(__shmem_, name); \
 __SHMEM_CLINK type* __SHMEM_CONCAT2(__shmem_init_, name)(void); \
 __SHMEM_CLINK type* __SHMEM_CONCAT2(__shmem_init_, name)(void) \
 { \
   __SHMEM_NAME(local_shmem_region).head->name = &__SHMEM_CONCAT2(__shmem_, name); \
   return &__SHMEM_CONCAT2(__shmem_, name); \
 }

#define __SHMEM_DEFINE_INIT(type, name, initval) \
 type __SHMEM_CONCAT2(__shmem_, name) = initval; \
 __SHMEM_CLINK type* __SHMEM_CONCAT2(__shmem_init_, name)(void); \
 __SHMEM_CLINK type* __SHMEM_CONCAT2(__shmem_init_, name)(void) \
 { \
   __SHMEM_NAME(local_shmem_region).head->name = &__SHMEM_CONCAT2(__shmem_, name); \
   return &__SHMEM_CONCAT2(__shmem_, name); \
 }

#define __SHMEM_DEFINE_ARRAY(type, name, size) \
 type __SHMEM_CONCAT2(__shmem_, name)[size]; \
 __SHMEM_CLINK type* __SHMEM_CONCAT2(__shmem_init_, name)(void); \
 __SHMEM_CLINK type* __SHMEM_CONCAT2(__shmem_init_, name)(void) \
 { \
   __SHMEM_NAME(local_shmem_region).head->name = __SHMEM_CONCAT2(__shmem_, name); \
   return __SHMEM_CONCAT2(__shmem_, name); \
 }


#define __SHMEM_DECLARE(type, name) \
 __SHMEM_CLINK type* __SHMEM_CONCAT2(__shmem_init_, name)(void);


#define __SHMEM_GET(type, name) \
 (*(type*)( \
 __SHMEM_GET_NAMED_PTR(name) \
 ? \
 __SHMEM_GET_NAMED_PTR(name) \
 : \
 __SHMEM_CONCAT2(__shmem_init_, name)() \
 ))

#define __SHMEM_GET_ARRAY(type, name) \
 ((type*)( \
 __SHMEM_GET_NAMED_PTR(name) \
 ? \
 __SHMEM_GET_NAMED_PTR(name) \
 : \
 __SHMEM_CONCAT2(__shmem_init_, name)() \
 ))


#ifdef __cplusplus
extern "C" {
#endif

struct __SHMEM_NAME(region_struct_name)
{
    struct __SHMEM_NAME(region_struct_name)* head;
    struct __SHMEM_NAME(region_struct_name)* next;
    void* _pthread_key_dest_shmem;
    void* _pthread_cancelling_shmem;
    void* _pthread_concur_shmem;
    void* _pthread_tls_once_shmem;
    void* _pthread_tls_shmem;
    void* _pthread_key_lock_shmem;
    void* _pthread_key_max_shmem;
    void* _pthread_key_sch_shmem;
    void* pthr_root_shmem;
    void* pthr_last_shmem;
    void* mtx_pthr_locked_shmem;
    void* idList_shmem;
    void* idListCnt_shmem;
    void* idListMax_shmem;
    void* idListNextId_shmem;
    void* once_obj_shmem;
    void* once_global_shmem;
    void* dummy_concurrency_level_shmem;
    void* rwl_global_shmem;
    void* cond_locked_shmem_rwlock;
    void* cond_locked_shmem_cond;
    void* barrier_global_shmem;
};

typedef struct __SHMEM_NAME(region_struct_name) __SHMEM_NAME(region_struct);

extern __SHMEM_NAME(region_struct) __SHMEM_NAME(local_shmem_region);

__SHMEM_CLINK __SHMEM_NAME(region_struct)* __SHMEM_NAME(init_local_region)(void);

#ifdef __cplusplus
}
#endif


#else /* ! USE_SHMEM3 */


#define __SHMEM_DEFINE(type, name) type name;
#define __SHMEM_DEFINE_INIT(type, name, initval) type name = initval;
#define __SHMEM_DEFINE_ARRAY(type, name, size) type name[size];
#define __SHMEM_DECLARE(type, name) extern type name;
#define __SHMEM_GET(type, name) name
#define __SHMEM_GET_ARRAY(type, name) name


#endif /* ! USE_SHMEM3 */

#endif /* ! __SHMEM3_H_INCLUDED */
