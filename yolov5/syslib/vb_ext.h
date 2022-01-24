#ifndef _VB_EXT_H_
#define _VB_EXT_H_

#include "vim_comm_vb.h"

#ifdef __cplusplus
extern "C" {
#endif

VB_POOL VB_CreatePool(VIM_U32 u32BlkSize,VIM_U32 u32BlkCnt,const VIM_CHAR *pcMmbName);
VIM_S32 VB_DestroyPool(VB_POOL Pool);
VB_BLK  VB_GetBlock(VB_POOL Pool, VIM_U32 u32BlkSize,const VIM_CHAR *pcMmzName);
VIM_S32 VB_ReleaseBlock(VB_BLK Block);
VIM_S32 VB_MmapPool(VB_POOL Pool, VIM_U32 bCached);
VIM_S32 VB_MunmapPool(VB_POOL Pool );
VIM_U32 VB_Handle2PhysAddr(VB_BLK Block );
VIM_S32 VB_GetBlkVirAddr(VB_POOL Pool, VIM_U32 u32PhyAddr, VIM_VOID **ppVirAddr );
VIM_U32 VB_GetLiveBockCnt( VB_POOL Pool);
VIM_U32 VB_GetBlkId( VB_POOL Pool, VIM_U32 u32PhyAddr );





#ifdef __cplusplus
}
#endif
#endif

