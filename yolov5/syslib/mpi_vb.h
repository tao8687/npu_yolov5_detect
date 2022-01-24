#ifndef __MPI_VB_H__
#define __MPI_VB_H__

#include "vim_comm_vb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

VB_POOL VIM_MPI_VB_CreatePool(VIM_U32 u32BlkSize,VIM_U32 u32BlkCnt,const VIM_CHAR *pcMmbName);
VIM_S32 VIM_MPI_VB_DestroyPool(VB_POOL Pool);

VB_BLK VIM_MPI_VB_GetBlock(VB_POOL Pool, VIM_U32 u32BlkSize,const VIM_CHAR *pcMmzName);
VIM_S32 VIM_MPI_VB_ReleaseBlock(VB_BLK Block);

VIM_U32 VIM_MPI_VB_Handle2PhysAddr(VB_BLK Block);
VB_POOL VIM_MPI_VB_Handle2PoolId(VB_BLK Block);

VIM_S32 VIM_MPI_VB_GetSupplementAddr(VB_BLK Block, VIDEO_SUPPLEMENT_S *pstSupplement);
VIM_S32 VIM_MPI_VB_SetSupplementConf(const VB_SUPPLEMENT_CONF_S *pstSupplementConf);
VIM_S32 VIM_MPI_VB_GetSupplementConf(VB_SUPPLEMENT_CONF_S *pstSupplementConf);


VIM_S32 VIM_MPI_VB_Init(VIM_VOID);
VIM_S32 VIM_MPI_VB_Exit(VIM_VOID);
VIM_S32 VIM_MPI_VB_SetConf(const VB_CONF_S *pstVbConf);
VIM_S32 VIM_MPI_VB_GetConf(VB_CONF_S *pstVbConf);

VIM_S32 VIM_MPI_VB_MmapPool(VB_POOL Pool);
VIM_S32 VIM_MPI_VB_MmapPoolParam( VB_POOL Pool, VIM_U32 bCached);
VIM_S32 VIM_MPI_VB_MunmapPool(VB_POOL Pool);

VIM_S32 VIM_MPI_VB_GetBlkVirAddr(VB_POOL Pool, VIM_U32 u32PhyAddr, VIM_VOID **ppVirAddr);

VIM_S32 VIM_MPI_VB_InitModCommPool(VB_UID_E enVbUid);
VIM_S32 VIM_MPI_VB_ExitModCommPool(VB_UID_E enVbUid);

VIM_S32 VIM_MPI_VB_SetModPoolConf(VB_UID_E enVbUid, const VB_CONF_S *pstVbConf);
VIM_S32 VIM_MPI_VB_GetModPoolConf(VB_UID_E enVbUid, VB_CONF_S *pstVbConf);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*__MPI_VI_H__ */

