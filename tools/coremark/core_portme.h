/* Minimal Linux-userspace port for the HBL2-Test trace flow.
 *
 * coremark.h includes this file FIRST (line 38) before defining anything of
 * its own, so this header must be self-contained and ordered:
 *   1. configuration flags
 *   2. ee_* data types + CORE_TICKS
 *   3. default_num_contexts / CORE_PORTABLE_S / portable_init/portable_fini
 * Structure mirrors the posix port (posix/core_portme.h:112-119, 282-302).
 *
 * Port choices:
 *   - MEM_STATIC: core_main.c:85 owns the static block; no malloc can fire
 *     inside the trace window (brk page faults would emit FR/WR records and
 *     abort addr.py).
 *   - rdcycle timers: CORE_TICKS = uint64_t, time_in_secs() only feeds the
 *     ">= 10 secs" validity warning, which this port accepts.
 *   - MAIN_HAS_NOARGC + SEED_VOLATILE: rcS invokes the binary with no
 *     arguments, so run length (ITERATIONS) and seeds are fixed at compile
 *     time and every run is deterministic.
 */
#ifndef CORE_PORTME_H
#define CORE_PORTME_H

#include <stdint.h>
#include <stddef.h>

/************************/
/* Configuration flags  */
/************************/
#ifndef HAS_FLOAT
#define HAS_FLOAT 1
#endif
#ifndef HAS_TIME_H
#define HAS_TIME_H 0
#endif
#ifndef USE_CLOCK
#define USE_CLOCK 0
#endif
#ifndef HAS_STDIO
#define HAS_STDIO 1
#endif
#ifndef HAS_PRINTF
#define HAS_PRINTF 1
#endif

/* trace window + fixed seed: no arguments are passed at runtime */
#define MAIN_HAS_NOARGC 1
#define MAIN_HAS_NORETURN 0
#define PERFORMANCE_RUN 1

/* MEM_STATIC/MEM_MALLOC/MEM_STACK expand later, in coremark.h:34-36 */
#define MEM_METHOD MEM_STATIC
#define SEED_METHOD SEED_VOLATILE
#define MULTITHREAD 1

/* deterministic run length: enough passes to diversify icache/branch flow,
 * small enough to bound the replay trace */
#ifndef ITERATIONS
#define ITERATIONS 300
#endif

/************************/
/* Data types           */
/************************/
typedef signed short   ee_s16;
typedef unsigned short ee_u16;
typedef signed int     ee_s32;
typedef double         ee_f32;
typedef unsigned char  ee_u8;
typedef unsigned int   ee_u32;
typedef uintptr_t      ee_ptr_int;
typedef size_t         ee_size_t;
/* align an offset to point to a 32b value */
#define align_mem(x) (void *)(4 + (((ee_ptr_int)(x)-1) & ~3))

/************************/
/* Timer: rdcycle       */
/************************/
typedef uint64_t CORE_TICKS;

/************************/
/* Contexts             */
/************************/
extern ee_u32 default_num_contexts;

typedef struct CORE_PORTABLE_S
{
    ee_u8 portable_id;
} core_portable;

/* target specific init/fini (posix signature: both return void) */
void portable_init(core_portable *p, int *argc, char *argv[]);
void portable_fini(core_portable *p);

/* informational only */
#define COMPILER_VERSION "clang-stc riscv64 static"
#define COMPILER_FLAGS   "single-tu"
#define MEM_LOCATION     "static"

#endif /* CORE_PORTME_H */
