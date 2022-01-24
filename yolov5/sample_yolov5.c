#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "sample_comm.h"
#include "npu_alg.h"

#define QUEUE_DEEP          3
#define YOLOV_DATA_FILE_SIZE   (416 * 416 * 3) //fixed bin



#define CONV_INPUT_NODE  "input0"
#define CONV_OUTPUT0_NODE  "Sigmoid164"
#define CONV_OUTPUT1_NODE  "Sigmoid166"
#define CONV_OUTPUT2_NODE  "Sigmoid168"


/*
#define CONV_INPUT_NODE  "ImageData_Input1"
#define CONV_OUTPUT0_NODE  "sigmoid1"
#define CONV_OUTPUT1_NODE  "sigmoid2"
#define CONV_OUTPUT2_NODE  "sigmoid3"
*/

SAMPLE_COMM_INOUTMEM_S g_stMemInfo;
VIM_U64    g_u64NId = -1;
NPU_INFO_S g_stInfo;
char g_astrDataFileList[1000][_FILENAME_LEN];
VIM_U32 g_u32DataType = 0;
VIM_S32 g_s32TotalNum = 0;
VIM_U32 gRunPicNum = 3;
NPU_NMS_PARAM_S g_stParam;

void    *g_pLmdbFd = NULL;
VIM_U8  *g_pImageData = NULL;
VIM_U8  *g_pLabelData = NULL;

VIM_U32 g_bSaveDetectOut = 0;

static VIM_VOID *g_pLabelQueueHandle=NULL;
static VIM_VOID *g_pLabelMapHandle=NULL;
#define LABEL_DATA_DEPTH 3
NPU_NMS_PARAM_S gstParam_yoloAll =
{
    NPU_FACE_DETECT_NOKEYPOINT,
    80,     //u16Numclasses;
    1,      //u16ShareLocation;
    0xff,   //u16BackgroundLabelId;

    2,      //enCodetype; option: PriorBoxParameter_CodeType
    0,      //u16VarianceEncodedInTarget;
    100,    //u16KeepTopK;
    0.001,  //u16ConfidenceThreshold;

    0.1,    //u16NmsThreshold;
    0.5,    //u32OverlapThreshold;
    300,    //u16TopK;
    3,      //u16NumPath; 
    //yolov start
   {416, 416}, //au32InputSize
    3,      //u32NumAnchors
    {
         {{ 10.,  13.}, { 16.,  30.}, {  33.,  23.}},
        {{ 30.,  61.}, { 62.,  45.}, {  59., 119.}},
        {{116.,  90.}, {156., 198.}, { 373., 326.}},
    },       //f32PriorAdd
    VIM_FALSE,	//u32NormalizedBBox;
	416,		//u32InputWidth;
	416,		//u32InputHeight;
    {
        {
            {85, 52, 52},
            {85, 26, 26},
            {85, 13, 13},
        },
    },      // u32PathInfo[2][10][3];  //(loc/conf)(layer)(feats,w,h,bw,lsb)
};


VIM_U32 NPU_FILE_GetSize(const char *filename)
{
    FILE *pFile = NULL;
    VIM_U32 u32Len = 0;

    if (filename == NULL)
    {
        printf("the filename is NULL.\n");
        return 0;
    }

    pFile = fopen(filename, "rb");
    if (pFile == NULL)
    {
        printf("cant open %s\n", filename);
        return 0;
    }

    fseek(pFile, 0L, SEEK_END);
    u32Len = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
    fclose(pFile);
    return u32Len;
}


VIM_U32 NPU_FILE_Load(const char *filename, VIM_S32 *pData, VIM_U32 u32Len)
{
    FILE *pFile = NULL;

    if (filename == NULL)
    {
        printf("the filename is NULL.\n");
        return 1;
    }

    pFile = fopen(filename, "rb");
    if (pFile == NULL)
    {
        printf("cant open %s\n", filename);
        return 1;
    }

    if (u32Len != fread(pData, 1, u32Len, pFile))
    {
        printf("read %s error.\n", filename);
        return 1;
    }

    fclose(pFile);
    return 0;
}



static VIM_VOID *g_pNmsHandle=NULL;
void SAMPLE_YoloDetect(VIM_F32 *pLocAddr[], VIM_F32 *pConfAddr[], VIM_U32 u32Lable)
{
    VIM_U32 u32DetCnt = 0;
    float pDetData[4096];
    static int loadflag = 0;

    if(loadflag == 0)
    {
        g_stParam = gstParam_yoloAll;
        g_pNmsHandle = Alg_Detect_Open(OPENMODE_EVALUATE);
	    loadflag = 1;
    }

    g_stParam.pLocAddr[0] = pLocAddr[0];
    g_stParam.pLocAddr[1] = pLocAddr[1];
    g_stParam.pLocAddr[2] = pLocAddr[2];

    Alg_Detect_YoloV5(g_pNmsHandle, &g_stParam, pDetData, &u32DetCnt);

#if 1
    VIM_U32 i=0, width = 0, height = 0;
    printf("     there are %d objects\n", u32DetCnt);
    width = g_stParam.au32InputSize[0];
    height = g_stParam.au32InputSize[1];
    for (i = 0; i < u32DetCnt; i++) 
    {      
        if (pDetData[7*i+2] > 0.3)
        {
            /*
             printf("nms det: %d, Type=%f,  score=%f,  x1=%f,  y1=%f, x2=%f, y2=%f \n",
                    i, pDetData[7*i+1], pDetData[7*i+2], 
                    pDetData[7*i+3]* width, pDetData[7*i+4]*height,
                    pDetData[7*i+5]* width, pDetData[7*i+6]*height);  
                    */
                                               
        }  
     }
    
#endif

	VIM_VOID *pvLabel;
    if (SAMPLE_COMM_MapGet(g_pLabelMapHandle, u32Lable, &pvLabel) != VIM_SUCCESS)
	{
          printf("Get label map failed.\n");
         return;
    }

    //printf("gt get: %d %d %f %f %f %f %f\n", u32Lable, *(VIM_U32*)pvLabel, *(VIM_F32*)(pvLabel+20), *(VIM_F32*)(pvLabel+28), *(VIM_F32*)(pvLabel+32), *(VIM_F32*)(pvLabel+36), *(VIM_F32*)(pvLabel+40));
    Alg_Detect_Evaluate(g_pNmsHandle, &g_stParam, pDetData, u32DetCnt, (VIM_F32*)(pvLabel+16), *(VIM_U32*)pvLabel);

    //printf("Put label map addr %d.\n", u32Lable);
    //printf("there is %d objects\n",u32DetCnt);
    SAMPLE_COMM_QueuePush(g_pLabelQueueHandle, pvLabel);


    return;
}


VIM_VOID SAMPLE_YOLO_SumResult(VIM_VOID)
{
    VIM_F32 mAp;
 /*
#if defined(ARM_LINUX)
    printf("*********************YOLO SUM RESULT Start*****************\n");
#else
    printf("*********************YOLO MMODEL SUM RESULT Start*****************\n");
#endif
*/
    mAp = Alg_Detect_CalcMAp(g_pNmsHandle, "yolo");
    printf("mAp: %f.\n", mAp);
    
#if defined(ARM_LINUX)
    printf("*********************YOLO SUM RESULT End*******************\n");
#else
    printf("*********************YOLO MMODEL SUM RESULT End*******************\n");
#endif

}

VIM_S32 SAMPLE_YOLO_GetData(VIM_U32 u32NetId, NPU_INFO_S* pstTensor, VIM_U32 *pu32Label)
{
    VIM_S32 s32Ret = VIM_SUCCESS;
    VIM_U8 *pu8In = pstTensor->stBufInfo[0].pu8Vaddr;
    VIM_U32 u32LabelIdx = 0;
    VIM_VOID *pvLabel;

    SAMPLE_COMM_QueuePop(g_pLabelQueueHandle, &pvLabel);
   
   g_u32DataType = DATA_TYPE_FIXED_BIN;

   
    if (g_u32DataType == DATA_TYPE_ANNOLMDB) 
    {
        s32Ret = SAMPLE_COMM_ReadAnnoLmdb(g_pLmdbFd, pu8In, pvLabel, &u32LabelIdx);
    } 
    else if (g_u32DataType == DATA_TYPE_FIXED_BIN) 
    {
        s32Ret = SAMPLE_COMM_ReadBinData(g_astrDataFileList, pu8In, pvLabel, &u32LabelIdx, YOLOV_DATA_FILE_SIZE);
        printf(" g_astrDataFileList name  = %s  \n ", g_astrDataFileList[u32LabelIdx]);
    }
    else if (g_u32DataType == DATA_TYPE_FLOAT_BIN) 
    {
        printf("Unsupport yet, please wait.\n");
        return VIM_FAILURE;
    } 
    else 
    {
        printf("Unsupport yet, please wait.\n");
        return VIM_FAILURE;
    }

    if (s32Ret != VIM_SUCCESS) 
    {
        printf("Read data failed.\n");
        goto end3;
    }

    s32Ret = SAMPLE_COMM_MapSet(g_pLabelMapHandle, u32LabelIdx, pvLabel);
    if(s32Ret != VIM_SUCCESS) {
        printf("Set label map failed.\n");
        goto end3;
    }
    *pu32Label = u32LabelIdx;
    return s32Ret;
end3:
    SAMPLE_COMM_QueuePush(g_pLabelQueueHandle, &pvLabel);
    return s32Ret;
}

VIM_S32 SAMPLE_YOLO_Predict(VIM_U64 u64NId)
{
    VIM_S32 s32Ret = VIM_SUCCESS;
    NPU_TASK_NODE_S stTaskNode;
    VIM_U32 u32Label;
    NPU_INFO_S stInTensor;

    s32Ret = NPU_MPI_CreateTask(u64NId, &stTaskNode);
    if (s32Ret != VIM_SUCCESS)
    {
        printf("NPU_MPI_CreateTask err %x!\n", s32Ret);
        return s32Ret;
    }

    //获取输入层的地址
    s32Ret =  NPU_MPI_GetTaskInTensor(&stTaskNode, CONV_INPUT_NODE, &stInTensor);
    if (s32Ret != VIM_SUCCESS)
    {
        printf("NPU_MPI_GetTaskInTensor err %x!\n", s32Ret);
        return s32Ret;
    }

    //填充输入数据
    s32Ret = SAMPLE_YOLO_GetData(u64NId, &stInTensor, &u32Label);
    if(s32Ret != VIM_SUCCESS)
    {
        return VIM_FAILURE;
    }

    //提交一个任务

       #if 0
                    //printf("read in0.bin\n");
                    int len = NPU_FILE_GetSize("ssd_in0.bin");
                    printf("len = 0x%x\n ", len);
                    NPU_FILE_Load("ssd_in0.bin",(VIM_S32 *)stInTensor.stBufInfo[0].pu8Vaddr,len);
        #endif
    stTaskNode.u32Private = u32Label;
    s32Ret = NPU_MPI_Predict(u64NId, &stTaskNode);
    if (s32Ret != VIM_SUCCESS)
    {
        printf("NPU_MPI_Predict err %x!\n", s32Ret);
        return s32Ret;
    }

    return s32Ret;
}


VIM_S32 SAMPLE_YOLO_GetResult(VIM_U64 u64NId)
{
    VIM_S32 s32Ret = VIM_SUCCESS;
    VIM_U32 i = 0;
    VIM_F32 *pLocAddr[6] = {VIM_NULL};
    NPU_TASK_NODE_S stTaskNode;
    VIM_F32 *pf32Addr;
    NPU_INFO_S stOutTensor;
    VIM_U32 u32LocNum = 0, u32ConfNum = 0;
    VIM_CHAR  u8NameLoc[3][STR_LEN];

    //LOC 输出层的名字
    memcpy(u8NameLoc[i++], CONV_OUTPUT0_NODE,sizeof(CONV_OUTPUT0_NODE));
    memcpy(u8NameLoc[i++], CONV_OUTPUT1_NODE,sizeof(CONV_OUTPUT1_NODE));
    memcpy(u8NameLoc[i++], CONV_OUTPUT2_NODE,sizeof(CONV_OUTPUT2_NODE));
    u32LocNum = i;

    //等待运行结果
    s32Ret = NPU_MPI_GetRunDone(u64NId, &stTaskNode);
    if (s32Ret != VIM_SUCCESS)
    {
        printf("NPU_MPI_GetResult err %x!\n\r", s32Ret);
        return s32Ret;
    }

     //NPU_MPI_ToolDump(&stTaskNode, "npu_dump", 6, -1, -1);

    //获取3个sigmoid层的输出信息
    for(i = 0; i < u32LocNum; i++)
    {
        s32Ret =  NPU_MPI_GetTaskOutTensor(&stTaskNode, u8NameLoc[i], &stOutTensor);
        if (s32Ret != VIM_SUCCESS)
        {
            printf("NPU_MPI_GetTaskOutTensor Loc num =%d  err %x!\n", i, s32Ret);
            return s32Ret;
        }
        //得到浮点的地址

        pf32Addr = (VIM_F32*)malloc(stOutTensor.stBufInfo[0].u32BufSize * 4);
        if (pf32Addr == VIM_NULL)
        {
            printf("malloc output buffer failed!\n");
            return s32Ret;
        }
        pLocAddr[i] = pf32Addr;
        NPU_MPI_GetFloatData(&stTaskNode, stOutTensor.stBufInfo[0].u32LayerId,
                 stOutTensor.stBufInfo[0].enDir, stOutTensor.stBufInfo[0].u32BufId, pf32Addr);
        gstParam_yoloAll.u32PathInfo[0][i][0] = stOutTensor.stBufInfo[0].u32C;
        gstParam_yoloAll.u32PathInfo[0][i][1] = stOutTensor.stBufInfo[0].u32W;
        gstParam_yoloAll.u32PathInfo[0][i][2] = stOutTensor.stBufInfo[0].u32H;
        /*printf("xxx i = %d ,loc name =%s , featurenum =%d, w =%d, h=%d \n",
                           i, u8NameLoc[i], stOutTensor.stBufInfo[0].u32FeatureNum, stOutTensor.stBufInfo[0].u32Col, stOutTensor.stBufInfo[0].u32Row);*/

    }

    //printf("SAMPLE_YoloDetect\n");
    //detect的结果写文件
    SAMPLE_YoloDetect(pLocAddr, VIM_NULL, stTaskNode.u32Private);

    s32Ret = NPU_MPI_DestroyTask(u64NId, &stTaskNode);
    if (s32Ret != VIM_SUCCESS)
    {
        printf("NPU_MPI_DestroyTask err %x!\n", s32Ret);
        return s32Ret;
    }
    for(i = 0; i < u32LocNum; i++)
    {
        free(pLocAddr[i]);
    }
    return s32Ret;
}

VIM_VOID * SAMPLE_YOLO_PredictProc(VIM_VOID *p)
{
#if defined(ARM_LINUX)
    fd_set fsetw;
    VIM_S32 s32Fd;
    struct timeval stTimeoutVal;
    s32Fd = NPU_MPI_GetNetFd(g_u64NId, NPU_FD_OP_W);
    VIM_U32 iCounter = 0;
    while(iCounter < gRunPicNum)
    {
        FD_ZERO(&fsetw);
        FD_SET(s32Fd, &fsetw);
        stTimeoutVal.tv_sec  = 60;
        stTimeoutVal.tv_usec = 0;
        VIM_S32 s32Ret = select(s32Fd+1, NULL, &fsetw, NULL, &stTimeoutVal);
        if (s32Ret <= 0)
        {
            printf("SAMPLE_YOLO_Predict select timeout!  s32Ret %d\n",s32Ret);
            break;
        }
        s32Ret = SAMPLE_YOLO_Predict(g_u64NId);
        if (s32Ret != VIM_SUCCESS)
        {
            printf("SAMPLE_YOLO_Predict err %x!\n", s32Ret);
            break;
        }
        if(++iCounter==g_s32TotalNum)
        {
            printf("Predict over!\n");
            break;
        }
    }
#endif
    return NULL;
}

VIM_VOID * SAMPLE_YOLO_GetResultProc(VIM_VOID *p)
{
#if defined(ARM_LINUX)
    fd_set fsetr;
    VIM_S32 s32Fd;
    struct timeval stTimeoutVal;
    s32Fd = NPU_MPI_GetNetFd(g_u64NId, NPU_FD_OP_R);
    VIM_U32 iCounter = 0;
    while(iCounter < gRunPicNum)
    {
        FD_ZERO(&fsetr);
        FD_SET(s32Fd, &fsetr);
        stTimeoutVal.tv_sec  = 60;
        stTimeoutVal.tv_usec = 0;

        VIM_S32 s32Ret = select(s32Fd+1, &fsetr, NULL, NULL, &stTimeoutVal);
        if (s32Ret <= 0)
        {
            printf("SAMPLE_YOLO_GetResultProc select timeout! s32Ret %d\n",s32Ret);
            break;
        }
        s32Ret = SAMPLE_YOLO_GetResult(g_u64NId);
        if (s32Ret != VIM_SUCCESS)
        {
            printf("SAMPLE_YOLO_GetResult err %x!\n", s32Ret);
            break;
        }
        if(++iCounter==g_s32TotalNum)
        {
            printf("GetResult over!\n");
            break;
        }
    }
#endif
    return NULL;
}


/******************************************************************************
* function : YOLO sample run func
******************************************************************************/
VIM_VOID SAMPLE_YOLO_Run(VIM_CHAR *pCFileNpuModel)
{
    VIM_S32 s32Ret = VIM_SUCCESS;
    VIM_S32 s32Cnt = 0;
    /******************************************
     step 1: init mpi system
    ******************************************/
    s32Ret = NPU_MPI_Init();
    if (VIM_SUCCESS != s32Ret)
    {
        printf("NPU_MPI_Init fail! s32Ret = 0x%x\n", s32Ret);
        return;
    }

    /******************************************
     step 2: create net work
    ******************************************/
    int u32Encrypt = 0;
    s32Ret = NPU_MPI_CreateNetWork(&g_u64NId, pCFileNpuModel, QUEUE_DEEP,u32Encrypt);
    if (VIM_SUCCESS != s32Ret)
    {
        printf("NPU_MPI_CreatNetWork fail! s32Ret = 0x%x\n", s32Ret);
        NPU_MPI_UnInit();
        return;
    }

    
	s32Ret = NPU_MPI_GetInfo(g_u64NId, &g_stInfo);
    if (VIM_SUCCESS != s32Ret)
	{
		printf("NPU_MPI_GetInfo fail, there is no any input or output! s32Ret = 0x%x\n", s32Ret);
		return ;
	}

    /******************************************
     step 3: predict and get result
    ******************************************/
#if defined(ARM_LINUX)
    pthread_t pthreadset,pthreadget;
    s32Ret = pthread_create(&pthreadset,NULL,SAMPLE_YOLO_PredictProc,NULL);
    s32Ret = pthread_create(&pthreadget,NULL,SAMPLE_YOLO_GetResultProc,NULL);

    pthread_join(pthreadset,NULL);
    pthread_join(pthreadget,NULL);
#else
    while (s32Cnt < gRunPicNum)
    {
    	printf("No%d  ",s32Cnt);
        s32Ret = SAMPLE_YOLO_Predict(g_u64NId);
        if (s32Ret != VIM_SUCCESS)
        {
            printf("SAMPLE_YOLO_Predict err %x!\n", s32Ret);
            break;
        }

        s32Ret = SAMPLE_YOLO_GetResult(g_u64NId);
        if (s32Ret != VIM_SUCCESS)
        {
            printf("SAMPLE_YOLO_GetResult err %x!\n", s32Ret);
            break;
        }
   
        s32Cnt++;
    }
#endif


    /******************************************
     step 5: connt result
    ******************************************/
    if (s32Ret == VIM_SUCCESS)
    {
        SAMPLE_YOLO_SumResult();
    }
    /******************************************
     step 5: FREE memory,destroy net,uninit
    ******************************************/

    if (g_pNmsHandle != NULL)
    {
        Alg_Detect_Close(g_pNmsHandle);
    }
    NPU_MPI_DestroyNetWork(g_u64NId); 
    NPU_MPI_UnInit();    
    return;
}

void SAMPLE_YOLO_Usage(char *sPrgNm)
{
    printf( "%s {<options>}\n",sPrgNm);
    printf( "help                   :display this help\n");
    printf( "model=<string>         :enter modelname. default model/ssd.npumodel\n");
	printf( "lmdb=<string>          :enter data folder, only for lmdb data \n");
	printf( "data_path=<string>     :enter bin data path, only for bin data \n");
	printf( "data_type=<string>     :enter data type \n");
    printf( "num=<int>              :is unnessesary, if enter a value for picnum, run picnum times, default run all pic\n");
    return;
}

/******************************************************************************
* function    : main()
* Description : YOLO sample
******************************************************************************/
int main(int argc, char* argv[])
{
    VIM_CHAR *pCFileNpuModel = "model/yolov5.npumodel";
    VIM_CHAR *pCFileDataPath = "./bin_data/";
    VIM_CHAR *pCFileDataType = "bin";
    VIM_CHAR *pCFileLmdbFile = NULL;
    VIM_VOID *pf32LabelData;

    if (SAMPLE_COMM_CheckCmdLineFlag(argc, (const char **)argv, "help"))
   	{
        SAMPLE_YOLO_Usage(argv[0]);
        return -1;
    }
    if (SAMPLE_COMM_CheckCmdLineFlag(argc, (const char **)argv, "model"))
   	{
        SAMPLE_COMM_GetCmdLineArgumentString(argc, (const char **)argv, "model", &pCFileNpuModel);
    }
    if (SAMPLE_COMM_CheckCmdLineFlag(argc, (const char **)argv, "lmdb"))
   	{
        SAMPLE_COMM_GetCmdLineArgumentString(argc, (const char **)argv, "lmdb", &pCFileLmdbFile);
    }
    if (SAMPLE_COMM_CheckCmdLineFlag(argc, (const char **)argv, "data_path"))
   	{
        SAMPLE_COMM_GetCmdLineArgumentString(argc, (const char **)argv, "data_path", &pCFileDataPath);
    }
    if (SAMPLE_COMM_CheckCmdLineFlag(argc, (const char **)argv, "data_type"))
   	{
        SAMPLE_COMM_GetCmdLineArgumentString(argc, (const char **)argv, "data_type", &pCFileDataType);
    }
    if (SAMPLE_COMM_CheckCmdLineFlag(argc, (const char **)argv, "num"))
   	{
        gRunPicNum = SAMPLE_COMM_GetCmdLineArgumentInt(argc, (const char **)argv, "num");
    }

    //printf(" gRunPicNum  = %d\n", gRunPicNum);
    if (!strcmp(pCFileDataType, "bin"))
        g_u32DataType = DATA_TYPE_FIXED_BIN;
    else if (!strcmp(pCFileDataType, "fbin"))
        g_u32DataType = DATA_TYPE_FLOAT_BIN;
    else if (!strcmp(pCFileDataType, "anno_lmdb"))
        g_u32DataType = DATA_TYPE_ANNOLMDB;
    else {
        printf("Unsupported data type \"%s\"\n", pCFileDataType);
        return -1;
    }

    if (g_u32DataType == DATA_TYPE_ANNOLMDB) 
    {
        if (pCFileLmdbFile == VIM_NULL) 
        {
            printf("Please indicate lmdb file path\n");
            return -1;
        }
        if (SAMPLE_COMM_OpenLmdb(pCFileLmdbFile, &g_pLmdbFd) == VIM_FAILURE) {
            printf("Open lmdb file %s failed!\n", pCFileLmdbFile);
            return -1;
        }
        g_s32TotalNum = -1;
    } 
    else if (g_u32DataType == DATA_TYPE_FIXED_BIN || g_u32DataType == DATA_TYPE_FLOAT_BIN) 
    {
        if (pCFileDataPath == VIM_NULL) 
        {
            printf("Please indicate data path\n");
            return -1;
        }
        g_s32TotalNum = SAMPLE_COMM_SearchFile(pCFileDataPath, ".bin", g_astrDataFileList);
    } 
    else 
    {
        //TODO: read jpg/bin file list into data_filename
        //TODO: set g_s32TotalNum as list lenth
    }

    g_pLabelQueueHandle = SAMPLE_COMM_QueueCreate();
    g_pLabelMapHandle = SAMPLE_COMM_MapCreate();
    for (int i=0; i<LABEL_DATA_DEPTH; i++) 
    {
        pf32LabelData = malloc(16384);
        SAMPLE_COMM_QueuePush(g_pLabelQueueHandle, pf32LabelData);
    }

    SAMPLE_YOLO_Run(pCFileNpuModel);

    VIM_U32 u32Ret;
    u32Ret = SAMPLE_COMM_MapSize(g_pLabelMapHandle);
    if (u32Ret != 0)
        printf("Proc does not exist safely, there's %d elements in common map, it would cause memory leak!\n", u32Ret);
    u32Ret = SAMPLE_COMM_QueueSize(g_pLabelQueueHandle);
    if (u32Ret != LABEL_DATA_DEPTH)
        printf("Proc does not exist safely, there's %d elements in common queue, it would cause memory leak!\n", u32Ret);
    while (SAMPLE_COMM_QueueTryPop(g_pLabelQueueHandle, &pf32LabelData) == VIM_SUCCESS) {
        free(pf32LabelData);
    }
    SAMPLE_COMM_QueueDestroy(g_pLabelQueueHandle);
    SAMPLE_COMM_MapDestroy(g_pLabelMapHandle);
    if (g_u32DataType == DATA_TYPE_ANNOLMDB)
        SAMPLE_COMM_CloseLmdb(g_pLmdbFd);
    return 0;
}

