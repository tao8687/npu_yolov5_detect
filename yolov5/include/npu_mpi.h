#ifndef __NPU_MPI_H__
#define __NPU_MPI_H__
#include "npu_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

//��ʼ��NPUģ��
VIM_S32 NPU_MPI_Init(VIM_VOID);

//����ʼ��NPUģ��
VIM_S32 NPU_MPI_UnInit(VIM_VOID);

//����������һ������ģ�� ��ģ�͵��ļ���
VIM_S32 NPU_MPI_CreateNetWork(VIM_U64* pu64NId, VIM_CHAR *ps8ModelFileName,
                                VIM_U32 u32Depth, VIM_U32 u32encrypt);                               
                             
//ע��һ���Ѿ����ص�����ģ��                                
VIM_S32 NPU_MPI_DestroyNetWork(VIM_U64 u64NId);

//����һ������
VIM_S32 NPU_MPI_CreateTask(VIM_U64 u64NId, NPU_TASK_NODE_S* pstTaskNode);

//�ͷ�һ������
VIM_S32 NPU_MPI_DestroyTask(VIM_U64 u64NId, NPU_TASK_NODE_S* pstTaskNode);

//�ύһ������
VIM_S32 NPU_MPI_Predict(VIM_U64 u64NId, NPU_TASK_NODE_S* pstTaskNode);

//�ȴ������������
VIM_S32 NPU_MPI_GetRunDone(VIM_U64 u64NId, NPU_TASK_NODE_S* pstTaskNode);

//��ȡָ�����ֵ������ĵ�ַ��Ϣ
VIM_S32 NPU_MPI_GetTaskInTensor(NPU_TASK_NODE_S* pstTaskNode, VIM_CHAR* name, NPU_INFO_S* pstTensor);  

//��ȡָ�����ֵ�������ַ��Ϣ
VIM_S32 NPU_MPI_GetTaskOutTensor(NPU_TASK_NODE_S* pstTaskNode, VIM_CHAR* name, NPU_INFO_S* pstTensor);


//��ȡ���������ĸ��������
VIM_S32 NPU_MPI_GetFloatData(NPU_TASK_NODE_S* pstTaskNode, VIM_U32 u32LayerId,
            NPU_BUF_DIR_E enDir, VIM_U32 u32BufId, VIM_F32* pf32Addr);

//�������ݵ�u16�Ķ��㻯����
//u32Scale: ����ֵ�������ţ�mnistʱ����Ҫ��256����u32Scale=8
VIM_S32 NPU_MPI_Data2Fix(VIM_U64 u64NId, VIM_VOID *pIn, VIM_U32 *pOut, 
                            NPU_DATA_TYPE_E enDataType, 
                            NPU_BUF_INFO_S *pstBufInfo);

//�����������ؽӿڣ����ڱ����������в�����ݣ��������룬�����Ȩ�أ�ƫ�õȣ���Ҫ���ڵ���
VIM_VOID NPU_MPI_Dump(NPU_TASK_NODE_S* pstTaskNode, VIM_CHAR* pSaveDir);
                         

//��ȡһ������fd ��Ҫ����select ����
VIM_S32 NPU_MPI_GetNetFd(VIM_U64 u64NId, NPU_FD_E enFd);

//��ȡһ�����������������buffer��Ϣ
VIM_U32 NPU_MPI_GetInfo(VIM_U64 u64NId, NPU_INFO_S *pstInfo);

//��ȡcahed �������ַ
VIM_S32 NPU_MPI_GetVirCache(VIM_U32 pPhyBuff, VIM_U32* pVirBuff, VIM_U32 size);

//clean cache 
VIM_S32  NPU_MPI_CleanCache(VIM_U32 *pu32PhyAddr, void **ppVitAddr, VIM_U32 u32Len);

//invlai cache
VIM_S32 NPU_MPI_InvalidCache(VIM_U32 *pu32PhyAddr, void **ppVitAddr, VIM_U32 u32Len);

//release cache
VIM_VOID NPU_MPI_FreeCache(VIM_VOID);


//��ȡSDK�汾��
VIM_VOID NPU_MPI_GetMpiVersion(VIM_CHAR cVersion[10]);




/*********���²����ڲ�ʹ��************/

//�����������ʼ��
VIM_U32 NPU_MPI_SetStartEndLayer(VIM_U64 u64NId, VIM_S32 s32StartLayer,
                                    VIM_S32 s32EndLayer);                                   
//�����������ؽӿڣ����ڱ����������в�����ݣ��������룬�����Ȩ�أ�ƫ�õȣ���Ҫ���ڵ���
VIM_VOID NPU_MPI_ToolDump(NPU_TASK_NODE_S* pstTaskNode, VIM_CHAR* pSaveDir, VIM_U32 u32DumpMode,                            VIM_S32 StartLayer,   VIM_S32 EndLayer);
//npu memalloc
VIM_S32 NPU_MPI_MemAlloc(VIM_U32 u32Size, NPU_MEMINFO_S *pstNpuMemInfo);
//npu memfree
VIM_S32 NPU_MPI_MemFree(NPU_MEMINFO_S *pstNpuMemInfo);    
/*
//�����ֶκ��� �ڲ�ʹ��
VIM_S32 NPU_MPI_CreatNetSection(VIM_U64* pu64NId, VIM_S32 *ps32Model,
              VIM_U32 u32Depth, VIM_U32 u32StartLayer, VIM_U32 u32EndLayer);*/


 






#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
#endif     

