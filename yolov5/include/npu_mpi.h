#ifndef __NPU_MPI_H__
#define __NPU_MPI_H__
#include "npu_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

//初始化NPU模块
VIM_S32 NPU_MPI_Init(VIM_VOID);

//反初始化NPU模块
VIM_S32 NPU_MPI_UnInit(VIM_VOID);

//创建并加载一个网络模型 （模型的文件）
VIM_S32 NPU_MPI_CreateNetWork(VIM_U64* pu64NId, VIM_CHAR *ps8ModelFileName,
                                VIM_U32 u32Depth, VIM_U32 u32encrypt);                               
                             
//注销一个已经加载的网络模型                                
VIM_S32 NPU_MPI_DestroyNetWork(VIM_U64 u64NId);

//创建一个任务
VIM_S32 NPU_MPI_CreateTask(VIM_U64 u64NId, NPU_TASK_NODE_S* pstTaskNode);

//释放一个任务
VIM_S32 NPU_MPI_DestroyTask(VIM_U64 u64NId, NPU_TASK_NODE_S* pstTaskNode);

//提交一个任务
VIM_S32 NPU_MPI_Predict(VIM_U64 u64NId, NPU_TASK_NODE_S* pstTaskNode);

//等待任务运行完成
VIM_S32 NPU_MPI_GetRunDone(VIM_U64 u64NId, NPU_TASK_NODE_S* pstTaskNode);

//获取指定名字的输入层的地址信息
VIM_S32 NPU_MPI_GetTaskInTensor(NPU_TASK_NODE_S* pstTaskNode, VIM_CHAR* name, NPU_INFO_S* pstTensor);  

//获取指定名字的输出层地址信息
VIM_S32 NPU_MPI_GetTaskOutTensor(NPU_TASK_NODE_S* pstTaskNode, VIM_CHAR* name, NPU_INFO_S* pstTensor);


//获取输入输出层的浮点的数据
VIM_S32 NPU_MPI_GetFloatData(NPU_TASK_NODE_S* pstTaskNode, VIM_U32 u32LayerId,
            NPU_BUF_DIR_E enDir, VIM_U32 u32BufId, VIM_F32* pf32Addr);

//输入数据到u16的定点化处理
//u32Scale: 对数值进行缩放，mnist时，需要除256，则u32Scale=8
VIM_S32 NPU_MPI_Data2Fix(VIM_U64 u64NId, VIM_VOID *pIn, VIM_U32 *pOut, 
                            NPU_DATA_TYPE_E enDataType, 
                            NPU_BUF_INFO_S *pstBufInfo);

//任务数据下载接口，用于保存网络所有层的数据，包括输入，输出，权重，偏置等，主要用于调试
VIM_VOID NPU_MPI_Dump(NPU_TASK_NODE_S* pstTaskNode, VIM_CHAR* pSaveDir);
                         

//获取一个网络fd 主要用于select 机制
VIM_S32 NPU_MPI_GetNetFd(VIM_U64 u64NId, NPU_FD_E enFd);

//获取一个网络的输入输出层的buffer信息
VIM_U32 NPU_MPI_GetInfo(VIM_U64 u64NId, NPU_INFO_S *pstInfo);

//获取cahed 的虚拟地址
VIM_S32 NPU_MPI_GetVirCache(VIM_U32 pPhyBuff, VIM_U32* pVirBuff, VIM_U32 size);

//clean cache 
VIM_S32  NPU_MPI_CleanCache(VIM_U32 *pu32PhyAddr, void **ppVitAddr, VIM_U32 u32Len);

//invlai cache
VIM_S32 NPU_MPI_InvalidCache(VIM_U32 *pu32PhyAddr, void **ppVitAddr, VIM_U32 u32Len);

//release cache
VIM_VOID NPU_MPI_FreeCache(VIM_VOID);


//获取SDK版本号
VIM_VOID NPU_MPI_GetMpiVersion(VIM_CHAR cVersion[10]);




/*********以下部分内部使用************/

//设置网络的起始层
VIM_U32 NPU_MPI_SetStartEndLayer(VIM_U64 u64NId, VIM_S32 s32StartLayer,
                                    VIM_S32 s32EndLayer);                                   
//任务数据下载接口，用于保存网络所有层的数据，包括输入，输出，权重，偏置等，主要用于调试
VIM_VOID NPU_MPI_ToolDump(NPU_TASK_NODE_S* pstTaskNode, VIM_CHAR* pSaveDir, VIM_U32 u32DumpMode,                            VIM_S32 StartLayer,   VIM_S32 EndLayer);
//npu memalloc
VIM_S32 NPU_MPI_MemAlloc(VIM_U32 u32Size, NPU_MEMINFO_S *pstNpuMemInfo);
//npu memfree
VIM_S32 NPU_MPI_MemFree(NPU_MEMINFO_S *pstNpuMemInfo);    
/*
//创建分段函数 内部使用
VIM_S32 NPU_MPI_CreatNetSection(VIM_U64* pu64NId, VIM_S32 *ps32Model,
              VIM_U32 u32Depth, VIM_U32 u32StartLayer, VIM_U32 u32EndLayer);*/


 






#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
#endif     

