#ifndef __VIM_COMM_VB_H__
#define __VIM_COMM_VB_H__

#include "vim_type.h"
#include "vim_errno.h"
#include "vim_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */
 
#define VB_MAX_POOLS 256
#define VB_MAX_COMM_POOLS 16
#define VB_MAX_MOD_COMM_POOLS 16


/* user ID for VB */
#define VB_MAX_USER   23

typedef enum vimVB_UID_E
{
	VB_UID_VIU			= 0,
	VB_UID_VOU			= 1,
	VB_UID_VGS			= 2,
	VB_UID_VENC 		= 3,
	VB_UID_VDEC 		= 4,
	VB_UID_VDA			= 5,
	VB_UID_H264E		= 6,
	VB_UID_JPEGE		= 7,
	VB_UID_MPEG4E		= 8,
	VB_UID_H264D		= 9,
	VB_UID_JPEGD		= 10,
	VB_UID_MPEG4D		= 11,
	VB_UID_VPSS 		= 12,
	VB_UID_GRP			= 13,
	VB_UID_MPI			= 14,
	VB_UID_PCIV 		= 15,
	VB_UID_AI			= 16,
	VB_UID_AENC 		= 17,
	VB_UID_RC			= 18,
	VB_UID_VFMW 		= 19,
	VB_UID_USER 		= 20,
	VB_UID_H265E		= 21,
	VB_UID_FISHEYE      = 22,
    VB_UID_BUTT
    
} VB_UID_E;

#define VB_INVALID_POOLID (-1U)
#define VB_INVALID_HANDLE (-1U)

/* Generall common pool use this owner id, module common pool use VB_UID as owner id */
#define POOL_OWNER_COMMON	-1

/* Private pool use this owner id */
#define POOL_OWNER_PRIVATE	-2

typedef enum vimPOOL_TYPE_E
{
	POOL_TYPE_COMMON			= 0,
	POOL_TYPE_PRIVATE			= 1,
	POOL_TYPE_MODULE_COMMON		= 2,
	POOL_TYPE_BUTT
} POOL_TYPE_E;

typedef VIM_U32 VB_POOL;
typedef VIM_U32 VB_BLK;

#define RESERVE_MMZ_NAME "window"

typedef struct vimVB_CONF_S
{
    VIM_U32 u32MaxPoolCnt;     /* max count of pools, (0,VB_MAX_POOLS]  */    
    struct vimVB_CPOOL_S
    {
        VIM_U32 u32BlkSize;
        VIM_U32 u32BlkCnt;
        VIM_CHAR acMmzName[MAX_MMZ_NAME_LEN];
        VIM_CHAR acMmbName[MAX_MMZ_NAME_LEN];
    }astCommPool[VB_MAX_COMM_POOLS];
} VB_CONF_S;

typedef struct vimVB_POOL_STATUS_S
{
	VIM_U32 bIsCommPool;
	VIM_U32 u32BlkCnt;
	VIM_U32 u32FreeBlkCnt;
}VB_POOL_STATUS_S;

#define VB_SUPPLEMENT_JPEG_MASK 0x1
#define VB_SUPPLEMENT_USERINFO_MASK 0x2
#define VB_SUPPLEMENT_ISPINFO_MASK  0x4
#define VB_SUPPLEMENT_ISPSTAT_MASK  0x8

typedef struct vimVB_SUPPLEMENT_CONF_S
{
    VIM_U32 u32SupplementConf;
}VB_SUPPLEMENT_CONF_S;


#define VIM_ERR_VB_NULL_PTR  VIM_DEF_ERR(VIM_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_NULL_PTR)
#define VIM_ERR_VB_NOMEM     VIM_DEF_ERR(VIM_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_NOMEM)
#define VIM_ERR_VB_NOBUF     VIM_DEF_ERR(VIM_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_NOBUF)
#define VIM_ERR_VB_UNEXIST   VIM_DEF_ERR(VIM_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_UNEXIST)
#define VIM_ERR_VB_ILLEGAL_PARAM VIM_DEF_ERR(VIM_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_ILLEGAL_PARAM)
#define VIM_ERR_VB_NOTREADY  VIM_DEF_ERR(VIM_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_SYS_NOTREADY)
#define VIM_ERR_VB_BUSY      VIM_DEF_ERR(VIM_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_BUSY)
#define VIM_ERR_VB_NOT_PERM  VIM_DEF_ERR(VIM_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_PERM)

#define VIM_ERR_VB_2MPOOLS VIM_DEF_ERR(VIM_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_BUTT + 1)

#define VIM_TRACE_VB(level,fmt...) VIM_TRACE(level, VIM_ID_VB,##fmt)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __VIM_COMM_VB_H_ */

