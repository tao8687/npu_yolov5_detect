#ifndef __NPU_COMM_H__
#define __NPU_COMM_H__
#include "vim_type.h"
#define NPU_INOUT_MAX 60
#define STR_LEN 64
#define MEM_NAME_LEN 64

#define UNSIGNBIT_8BIT		8	// 8bit位宽，无符号位
#define SIGNBIT_8BIT		7	// 8bit位宽，第7bit表示符号位
#define UNSIGNBIT_16BIT		16	// 16bit位宽，无符号位
#define SIGNBIT_16BIT		15	// 16bit位宽，第15bit表示符号位
#define WT_ALIGN			32  //256bits

typedef enum vimNPU_PADDING_TYPE_E
{
    NPU_PADDING_VALID = 0,
    NPU_PADDING_SAME,
    NPU_PADDING_BUTT
}NPU_PADDING_TYPE_E;

typedef enum vimNPU_POOLING_METHOD_E
{
    NPU_POOLING_MAX = 0,
    NPU_POOLING_AVE,//AVERAGE
    NPU_POOLING_BUTT
}NPU_POOLING_METHOD_E;

typedef enum vimNPU_ELTWISE_OPER_E
{
    NPU_ELTWISE_PROD = 0,
    NPU_ELTWISE_SUM,
    NPU_ELTWISE_MAX,
    NPU_ELTWISE_BUTT
}NPU_ELTWISE_OPER_E;

typedef enum vimNPU_REDCTION_OPER_E
{
	NPU_REDCTION_SUM = 0,
	NPU_REDCTION_ASUM,
	NPU_REDCTION_MAXMIN,
	NPU_REDCTION_SUMSQ
}NPU_REDCTION_OPER_E;

typedef enum vimNPU_THRESHOLD_OPER_E
{
	NPU_THRESHOLD_NORMAL = 0,
	NPU_THRESHOLD_ABS,
}NPU_THRESHOLD_OPER_E;


typedef enum vimNPU_DATA_TYPE_E
{
    NPU_U8  = 0x1,
    NPU_FLOAT = 0x2,
    NPU_S8  = 0x3,
    NPU_S16 = 0x4,
} NPU_DATA_TYPE_E;

typedef enum vimNPU_FD_E
{
    NPU_FD_OP_R = 0,
    NPU_FD_OP_W = 1,
    NPU_FD_OP_MAX = 2,
}NPU_FD_E;

typedef enum vimNPU_BUF_DIR_E
{
    NPU_INPUT  = 0x1,
    NPU_OUTPUT = 0x2,
} NPU_BUF_DIR_E;


typedef struct vimNPU_MEM_S
{
    VIM_U32 u32Paddr;
    VIM_U8 *pu8Vaddr;
}NPU_MEM_S;


//NPU CMD ADDR 
typedef struct vimNPU_MEMINFO_S
{
    VIM_U32 u32Paddr;
    VIM_U8 *pu8Vaddr;
    VIM_U32 u32Size;
    char memname[MEM_NAME_LEN];
}NPU_MEMINFO_S;


typedef struct vimNPU_BUF_INFO_S
{
    VIM_U32 u32LayerId;
    VIM_U32 u32BufId;
    VIM_U32 u32BitWidth;
    VIM_U32 u32BufSize;
    VIM_U32 u32Items;
    VIM_U32 u32Addr;
    VIM_U16 u32N; //sw,batch size
	VIM_U16 u32C; //sw,channel
	VIM_U16 u32H; //sw,height, the size of caffe
	VIM_U16 u32W; //sw,width
    VIM_S32 s32ShiftBits;
    NPU_BUF_DIR_E enDir;
    VIM_U8 *pu8Vaddr;
    VIM_CHAR  u8Name[STR_LEN];
}NPU_BUF_INFO_S;

typedef struct vimNPU_INFO_S
{
    VIM_U32 u32BufNum;
    NPU_BUF_INFO_S stBufInfo[NPU_INOUT_MAX];
} NPU_INFO_S;

typedef struct vimNPU_TASK_NODE_S
{
    VIM_U32 u32NetId;
    VIM_U32 u32HdlPhyAddr;
    VIM_U8* u8HdlKernelVir;
    VIM_U8* u8HdlUserVir;
    VIM_U32 u32Private;
} NPU_TASK_NODE_S;

 

#endif
