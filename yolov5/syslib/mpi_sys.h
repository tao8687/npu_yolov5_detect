#ifndef __MPI_SYS_H__
#define __MPI_SYS_H__

#include "vim_type.h"
#include "vim_common.h"
#include "vim_comm_sys.h"
#include "plat.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


typedef struct VIM_EFUSE_CHIP_INFO{

	VIM_U32 sn_num;
	VIM_U32 factory;
	VIM_U32 chiplevel;
	VIM_U32 year;
	VIM_U32 week;
	VIM_U32 check_code;

}EFUSE_CHIP_INFO;

 typedef enum
 {
	VIM_BIND_WK_TYPE_DRV=0x0,
	VIM_BIND_WK_TYPE_USR,
	VIM_BIND_WK_TYPE_BUTT,
 }VIM_BIND_WK_TYPE_E;

VIM_S32 VIM_MPI_SYS_Init();
VIM_S32 VIM_MPI_SYS_Exit();

VIM_S32 VIM_MPI_SYS_SetConf(const MPP_SYS_CONF_S* pstSysConf);
VIM_S32 VIM_MPI_SYS_GetConf(MPP_SYS_CONF_S* pstSysConf);

VIM_S32 VIM_MPI_SYS_Bind(VIM_U32 SrcNum,SYS_BD_CHN_S *pstSrcChn, VIM_U32 DstNum, SYS_BD_CHN_S *pstDestChn,VIM_BIND_WK_TYPE_E type);
VIM_S32 VIM_MPI_SYS_UnBind(VIM_U32 SrcNum,SYS_BD_CHN_S *pstSrcChn, VIM_U32 DstNum, SYS_BD_CHN_S *pstDestChn,VIM_BIND_WK_TYPE_E type);

VIM_U32 VIM_MPI_SYS_GetVersion(VIM_VOID);

/*
** u64Base is the global PTS of the system.
** ADVICE:
** 1. Better to call VIM_MPI_SYS_GetCurPts on the host board to get u64Base.
** 2. When os start up, call VIM_MPI_SYS_InitPtsBase to set the init PTS.
** 3. When media bussines is running, synchronize the PTS one time per minute
**     by calling VIM_MPI_SYS_SyncPts.
*/
VIM_S32 VIM_MPI_SYS_GetCurPts(VIM_U64* pu64CurPts);
VIM_S32 VIM_MPI_SYS_InitPtsBase(VIM_U64 u64PtsBase);
VIM_S32 VIM_MPI_SYS_SyncPts(VIM_U64 u64PtsBase);
VIM_S32 VIM_MPI_SYS_SetLogPrint(VIM_VPRINTF func);
VIM_S32 VIM_MPI_SYS_DMAOpen(VIM_S32 *vc);
VIM_S32 VIM_MPI_SYS_DMAClose(VIM_S32 fd);
VIM_S32 VIM_MPI_SYS_DMACopy(VIM_S32 fd, struct userdma_user_info *info);
VIM_S32 VIM_MPI_SYS_DMAPoll(VIM_S32 fd, VIM_S32 ms);

/* alloc mmz memory in user context                                         */
VIM_S32 VIM_MPI_SYS_MmzAlloc(VIM_U32* pu32PhyAddr, VIM_VOID** ppVirtAddr,
                           const VIM_CHAR* strMmb, const VIM_CHAR* strZone, VIM_U32 u32Len);

/* alloc mmz memory with cache */
VIM_S32 VIM_MPI_SYS_MmzAlloc_Cached(VIM_U32* pu32PhyAddr, VIM_VOID** ppVitAddr,
                                  const VIM_CHAR* pstrMmb, const VIM_CHAR* pstrZone, VIM_U32 u32Len);

/* free mmz memory in user context                                          */
VIM_S32 VIM_MPI_SYS_MmzFree(VIM_U32 u32PhyAddr, VIM_VOID* pVirtAddr);

/* flush cache */
VIM_S32 VIM_MPI_SYS_MmzFlushCache(VIM_U32 u32PhyAddr, VIM_VOID* pVitAddr, VIM_U32 u32Size);

/* clean cache */
VIM_S32 VIM_MPI_SYS_MmzCleanCache( VIM_U32 u32PhyAddr, VIM_VOID *pVitAddr, VIM_U32 u32Size );

/*
** Call the mmap function to map physical address to virtual address
** The system function mmap is too complicated, so we packge it.
*/
VIM_VOID* VIM_MPI_SYS_Mmap(VIM_U32 u32PhyAddr, VIM_U32 u32Size);
VIM_VOID* VIM_MPI_SYS_MmapCache(VIM_U32 u32PhyAddr, VIM_U32 u32Size);
VIM_S32 VIM_MPI_SYS_Munmap(VIM_VOID* pVirAddr, VIM_U32 u32Size);
VIM_S32 VIM_MPI_SYS_MflushCache(VIM_U32 u32PhyAddr, VIM_VOID *pVirAddr, VIM_U32 u32Size);

/*
** Access the physical address.
** You can use this function to access memory address or register address.
*/
VIM_S32 VIM_MPI_SYS_SetReg(VIM_U32 u32Addr, VIM_U32 u32Value);
VIM_S32 VIM_MPI_SYS_GetReg(VIM_U32 u32Addr, VIM_U32* pu32Value);

VIM_S32 VIM_MPI_SYS_SetMemConf(MPP_CHN_S* pstMppChn, const VIM_CHAR* pcMmzName);
VIM_S32 VIM_MPI_SYS_GetMemConf(MPP_CHN_S* pstMppChn, VIM_CHAR* pcMmzName);

/* Close all the FD which is used by sys module */
VIM_S32 VIM_MPI_SYS_CloseFd(VIM_VOID);

/* Get VI VO work mode, 0: offline, >0: online */
VIM_S32 VIM_MPI_SYS_GetViVoMode(VIM_U32* pu32Mode);

/* media profile setting, for low power */
VIM_S32 VIM_MPI_SYS_SetProfile(PROFILE_TYPE_E enProfile);

/* Get virtual meminfo according to virtual addr, should be in one process */
VIM_S32 VIM_MPI_SYS_GetVirMemInfo(const void* pVitAddr, SYS_VIRMEM_INFO_S* pstMemInfo);

/* Set/get Scale coefficient level for VPSS/VGS*/
VIM_S32 VIM_MPI_SYS_SetScaleCoefLevel(SCALE_RANGE_S *pstScaleRange,SCALE_COEFF_LEVEL_S *pstScaleCoeffLevel);
VIM_S32 VIM_MPI_SYS_GetScaleCoefLevel(SCALE_RANGE_S *pstScaleRange,SCALE_COEFF_LEVEL_S *pstScaleCoeffLevel);

/* Set/Get local timezone, range: [-86400, 86400] seconds (that is: [-24, 24] hours)  */
VIM_S32 VIM_MPI_SYS_SetTimeZone(VIM_S32 s32TimeZone);
VIM_S32 VIM_MPI_SYS_GetTimeZone(VIM_S32 *ps32TimeZone);

VIM_S32 VIM_MPI_SYS_SetGPSInfo(GPS_INFO_S *pstGPSInfo);
VIM_S32 VIM_MPI_SYS_GetGPSInfo(GPS_INFO_S *pstGPSInfo);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*__MPI_SYS_H__ */

