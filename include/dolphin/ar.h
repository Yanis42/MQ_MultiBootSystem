#ifndef _DOLPHIN_AR_H_
#define _DOLPHIN_AR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dolphin/arq.h"
#include "dolphin/types.h"

#define AR_STACK_INDEX_ENTRY_SIZE sizeof(u32)

#define ARAM_DIR_MRAM_TO_ARAM 0x00
#define ARAM_DIR_ARAM_TO_MRAM 0x01

#define AR_CLEAR_INTERNAL_ALL 0x00
#define AR_CLEAR_INTERNAL_USER 0x01
#define AR_CLEAR_EXPANSION 0x02

#define __AR_ARAM_OS_BASE_ADDR 0x0000 // OS area at bottom of ARAM
#define __AR_ARAM_USR_BASE_ADDR 0x4000 // USR area at 16KB (0x4000)

typedef void (*ARCallback)(void);

u32 ARInit(u32* stack_index_addr, u32 num_entries);
u32 ARGetBaseAddress(void);
u32 ARGetDMAStatus(void);
void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length);

#define ARStartDMARead(mmem, aram, len) ARStartDMA(ARAM_DIR_ARAM_TO_MRAM, mmem, aram, len)
#define ARStartDMAWrite(mmem, aram, len) ARStartDMA(ARAM_DIR_MRAM_TO_ARAM, mmem, aram, len)

#ifdef __cplusplus
};
#endif

#endif
