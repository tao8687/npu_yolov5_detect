/******************************************************************************
  Vimicro VC0758NPU sample programs head file.

  Copyright (C), 2015-2020, Vimicro Tech. Co., Ltd.
 ******************************************************************************
    Modification:  2015-2 Created
******************************************************************************/


#ifndef __SAMPLE_COMM_H__
#define __SAMPLE_COMM_H__

#include "vim_type.h"
#include "npu_mpi.h"
#ifdef USE_LMDB
#include "lmdb.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define SAMPLE_COMM_INOUT_MAX NPU_INOUT_MAX
#define SAMPLE_COMM_DEPTH_MAX 5
#define _FILENAME_LEN 256

typedef VIM_VOID* NPUHandle;

enum {
    DATA_TYPE_LMDB=0,
    DATA_TYPE_ANNOLMDB,
    DATA_TYPE_FIXED_BIN,
    DATA_TYPE_FLOAT_BIN,
    DATA_TYPE_JPG
};

typedef struct vimSAMPLE_COMM_PTHREAD_ARG
{
    VIM_CHAR *     pImagePathFile;
    VIM_S32        s32Toatlnum;
    NPUHandle      handle;
} SAMPLE_COMM_PTHREAD_ARG;

typedef struct vimSAMPLE_COMM_INOUT_BLK_S
{
    VIM_BOOL   bUsed;
    VIM_BOOL   bValid;
    NPU_MEM_S  stMem;
}SAMPLE_COMM_INOUT_BLK_S;

typedef struct vimSAMPLE_COMM_INOUT_POOL_S
{
    SAMPLE_COMM_INOUT_BLK_S stBlk[SAMPLE_COMM_DEPTH_MAX];
}SAMPLE_COMM_INOUT_POOL_S;

typedef struct vimSAMPLE_COMM_INOUTMEM_S
{
    SAMPLE_COMM_INOUT_POOL_S stPool[SAMPLE_COMM_INOUT_MAX];
}SAMPLE_COMM_INOUTMEM_S;

VIM_U32 SAMPLE_COMM_FileGetSize(const VIM_CHAR *filename);
VIM_U32 SAMPLE_COMM_FileLoad(const VIM_CHAR *filename, VIM_S32 *pData, VIM_U32 u32Len);
VIM_U32 SAMPLE_COMM_FileSave(VIM_CHAR *filename, VIM_S32 *pData, VIM_U32 u32Len);

VIM_S32 SAMPLE_COMM_ToolU8toFloat(VIM_U8 *pIn, VIM_F32 *pOut, VIM_U32 u32FileSize);
VIM_S32 SAMPLE_COMM_SearchFile(VIM_CHAR path[], VIM_CHAR pSuffix[], VIM_CHAR filename[][_FILENAME_LEN]);

VIM_U32 SAMPLE_COMM_GetFileSize(const char *filename);
VIM_U32 SAMPLE_COMM_LoadFile(const char *filename, VIM_S32 *pData, VIM_U32 u32Len);

VIM_S32 SAMPLE_COMM_CheckCmdLineFlag(const VIM_S32 argc, const VIM_CHAR **argv, const VIM_CHAR *string_ref);
VIM_S32 SAMPLE_COMM_GetCmdLineArgumentInt(const VIM_S32 argc, const VIM_CHAR **argv, const VIM_CHAR *string_ref);
VIM_S32 SAMPLE_COMM_GetCmdLineArgumentString(const VIM_S32 argc, const VIM_CHAR **argv,
            const VIM_CHAR *string_ref, VIM_CHAR **string_retval);

VIM_S32 SAMPLE_COMM_OpenLmdb(const char *filename, void **lmdb_fd);
VIM_VOID SAMPLE_COMM_CloseLmdb(void *lmdb_fd);
VIM_S32 SAMPLE_COMM_ReadLmdb(void *fd, void *data, void *label, VIM_U32 *idx);
VIM_S32 SAMPLE_COMM_ReadAnnoLmdb(void *fd, void *data, void *label, VIM_U32 *idx);
VIM_S32 SAMPLE_COMM_GetLmdbItemSize(void *fd, VIM_U32 *data_size, VIM_U32 *label_size);
VIM_S32 SAMPLE_COMM_GetAnnoItemSize(void *fd, VIM_U32 *data_size, VIM_U32 *label_size);
VIM_S32 SAMPLE_COMM_ReadBinData(char astrDataFileList[][_FILENAME_LEN], void *data, void *label, VIM_U32 *idx, VIM_U32 fsize);
VIM_S32 SAMPLE_COMM_ReadBin(char astrDataFileList[][_FILENAME_LEN], void *data,  VIM_U32 fsize, VIM_U32 DataIndex);
//void Alg_Detect_YoloV5(VIM_VOID *pHandle, NPU_NMS_PARAM_S *pstParam, VIM_F32 *pOutAddr, VIM_U32 *pu32Count);
VIM_S32 SAMPLE_COMM_ReadBin(char astrDataFileList[][_FILENAME_LEN], void *data,  VIM_U32 fsize, VIM_U32 DataIndex);

VIM_VOID *SAMPLE_COMM_MapCreate(VIM_VOID);
VIM_VOID SAMPLE_COMM_MapDestroy(VIM_VOID *handle);
VIM_S32 SAMPLE_COMM_MapSet(VIM_VOID *handle, int id, VIM_VOID *element);
VIM_S32 SAMPLE_COMM_MapGet(VIM_VOID *handle, int id, VIM_VOID **element);
VIM_U32 SAMPLE_COMM_MapSize(VIM_VOID *handle);

VIM_VOID *SAMPLE_COMM_QueueCreate(VIM_VOID);
VIM_VOID SAMPLE_COMM_QueueDestroy(VIM_VOID *handle);
VIM_VOID SAMPLE_COMM_QueuePush(VIM_VOID *handle, VIM_VOID *element);
VIM_VOID SAMPLE_COMM_QueuePop(VIM_VOID *handle, VIM_VOID **element);
VIM_U32 SAMPLE_COMM_QueueTryPop(VIM_VOID *handle, VIM_VOID **element);
VIM_U32 SAMPLE_COMM_QueueSize(VIM_VOID *handle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
