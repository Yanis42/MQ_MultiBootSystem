#ifndef _DOLPHIN_OSERROR
#define _DOLPHIN_OSERROR

#ifdef __cplusplus
extern "C" {
#endif

#include "dolphin/os/OSException.h"
#include "dolphin/types.h"

#define OS_ERROR_SYSTEM_RESET 0
#define OS_ERROR_MACHINE_CHECK 1
#define OS_ERROR_DSI 2
#define OS_ERROR_ISI 3
#define OS_ERROR_EXTERNAL_INTERRUPT 4
#define OS_ERROR_ALIGNMENT 5
#define OS_ERROR_PROGRAM 6
#define OS_ERROR_FLOATING_POINT 7
#define OS_ERROR_DECREMENTER 8
#define OS_ERROR_SYSTEM_CALL 9
#define OS_ERROR_TRACE 10
#define OS_ERROR_PERFORMACE_MONITOR 11
#define OS_ERROR_BREAKPOINT 12
#define OS_ERROR_SYSTEM_INTERRUPT 13
#define OS_ERROR_THERMAL_INTERRUPT 14
#define OS_ERROR_PROTECTION 15
#define OS_ERROR_FPE 16

#define OS_ERROR_MAX (OS_ERROR_FPE + 1)

typedef u16 OSError;
typedef void (*OSErrorHandler)(OSError error, OSContext* context, ...);

void OSReport(const char* msg, ...);
void OSPanic(const char* file, int line, const char* msg, ...);
OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler);
void __OSUnhandledException(__OSException exception, OSContext* context, u32 dsisr, u32 dar);

#ifdef __cplusplus
};
#endif

#endif // _DOLPHIN_OSERROR
