#ifndef __NPU_ALG_H__
#define __NPU_ALG_H__

#include "vim_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define MAX_NUM_PATHS   10
#define MAX_NUM_PRIOR   16

typedef enum vimNPU_DETECT_MODE_E
{
    NPU_FACE_DETECT_KEYPOINT = 1,
    NPU_FACE_DETECT_NOKEYPOINT = 2,
}NPU_DETECT_MODE_E;

typedef struct vimNPU_NMS_PARAM_S
{
    NPU_DETECT_MODE_E     enDetectFaceMode;
    VIM_U32     u32Numclasses;
    VIM_U32     u32ShareLocation;
    VIM_U32     u32BackgroundLabelId;

    VIM_U32     enCodetype;
    VIM_U32     u32VarianceEncodedInTarget;
    VIM_U32     u32KeepTopK;
    VIM_F32     f32ConfidenceThreshold;

    VIM_F32     f32NmsThreshold;
    VIM_F32     f32OverlapThreshold;
    VIM_U32     u32TopK;
    VIM_U32     u32NumPath;

    VIM_U32     au32InputSize[2];
    VIM_U32     u32NumAnchors;
	VIM_F32     f32PriorAddr[MAX_NUM_PATHS][MAX_NUM_PRIOR][2];
    VIM_U32     u32NormalizedBBox;
    VIM_U32     u32InputWidth;
    VIM_U32     u32InputHeight;
    VIM_U32     u32PathInfo[2][MAX_NUM_PATHS][3];
    
    VIM_F32     *pConfAddr[MAX_NUM_PATHS];
    VIM_F32     *pLocAddr[MAX_NUM_PATHS];
    VIM_F32     *pPriorAddr;
    VIM_F32     *pFaceAddr[MAX_NUM_PATHS];
}NPU_NMS_PARAM_S;

typedef struct vimNPU_PAR_S
{
    VIM_S32 u32Width;
    VIM_S32 u32Height;
    VIM_S32 u32CropSize;
    VIM_S32 u32CropSize_w;
    VIM_S32 u32CropSize_h;
    VIM_F32 rot_angle;
    VIM_F32 diff_angle;
    VIM_F32 articulation;
    VIM_S32 points[10];
	VIM_S32 isstretch;
}NPU_PAR_S;

typedef struct BPoint
{
	VIM_F32 x;
	VIM_F32 y;
}BPoint;

typedef struct vimHUMAN_RESULT_S
{
	VIM_F32 Pose_scores[18];
	VIM_S32 KeyPoint[18][2];
}HUMAN_RESULT_S;

typedef enum vimNPU_DETECT_OPENMODE_E
{
	OPENMODE_FORWARD =0, //?y3¡ê?¡ê¨º?
	OPENMODE_EVALUATE  = 1 //?¨¤1¨¤?¡ê¨º?
}NPU_DETECT_OPENMODE_E;


VIM_VOID Alg_Detect(VIM_VOID *pHandle, NPU_NMS_PARAM_S *pstParam, VIM_F32 *pOutAddr, VIM_U32 *u32Count);
VIM_VOID Alg_Detect_YoloV5(VIM_VOID *pHandle, NPU_NMS_PARAM_S *pstParam, VIM_F32 *pOutAddr, VIM_U32 *pu32Count);
VIM_VOID Alg_Detect_YoloV3(VIM_VOID *pHandle, NPU_NMS_PARAM_S *pstParam, VIM_F32 *pOutAddr, VIM_U32 *pu32Count);
VIM_VOID *Alg_Detect_Open(NPU_DETECT_OPENMODE_E openmode);

VIM_VOID Alg_Detect_Close(VIM_VOID *pHandle);

VIM_VOID Alg_Detect_Reset(VIM_VOID *pHandle);

VIM_F32 Alg_Detect_CalcMAp(VIM_VOID *pHandle, const VIM_CHAR *strApVersion);

VIM_VOID Alg_Detect_Evaluate(VIM_VOID *pHandle, NPU_NMS_PARAM_S *pstParam, VIM_F32 *pDetData, VIM_U32 u32DetNum, VIM_F32 *pGtData, VIM_U32 u32GtNum);

VIM_U32  Alg_TrackPedestrian_Init(VIM_U32 u32MaxFrameNum, VIM_U32 u32MaxFaceNum);

VIM_U32  Alg_Trackpedrstrain_GetTrackId(VIM_FLOAT* pOutAddr, VIM_U32 u32Count, VIM_U32 *pU32PedId);

VIM_U32  Alg_Trackpedrstrain_GetCounter(BPoint* border, VIM_U32 border_size, VIM_U32 u32Count, VIM_U32* u32boxcount);

VIM_U32  Alg_TrackPedestrian_UnInit();

VIM_F32  Alg_Get_Facequality(VIM_FLOAT* pOutAddr, VIM_U32 u32Count, VIM_F32 *pU32FaceScore,VIM_S32 s32Width,VIM_S32 s32Height,VIM_S32 min_pixel,VIM_S32 middle_pixel,VIM_F32 ratio,VIM_U8 *crgb709buf,VIM_S32 vague_enable,VIM_F32 *angle );

VIM_U32  Alg_AlignFace_YUV420P(VIM_U8 * buffer_in, VIM_U8 * buffer_out, NPU_PAR_S* pstPar);

VIM_U32  Alg_AlignFace_RGB709(VIM_U8 * buffer_in, VIM_U8 * buffer_out, NPU_PAR_S* pstPar);

VIM_U32  Alg_AlignFace_RGB888(VIM_U8 * buffer_in, VIM_U8 * buffer_out, NPU_PAR_S* pstPar);

VIM_U32  Alg_Resize_YUV420P(VIM_U8 * buffer_in, VIM_U8 * buffer_out, NPU_PAR_S* pstPar, VIM_S32 MeanPixel[3]);

VIM_U32  Alg_Resize_wh_YUV420P(VIM_U8 * buffer_in,VIM_U8 * buffer_out, NPU_PAR_S* pstPar, VIM_S32 MeanPixel[3]);

VIM_U32  Alg_Resize_wh_YUV400(unsigned char* buffer_in, unsigned char* buffer_out, NPU_PAR_S* pstPar, int MeanPixel[3]);

VIM_U32  Alg_Resize_wh_RGB709(VIM_U8 * buffer_in, VIM_U8 * buffer_out, NPU_PAR_S* pstPar, VIM_S32 MeanPixel[3]);

VIM_U32  Alg_Resize_wh_RGB709ToYUV(unsigned char* buffer_in, unsigned char* buffer_out, NPU_PAR_S* pstPar, int MeanPixel[3]);

VIM_U32  Alg_Resize_wh_YUV420PToRGB709(unsigned char* buffer_in, unsigned char* buffer_out, NPU_PAR_S* pstPar, int MeanPixel[3]);

VIM_U32  Alg_Resize_wh_YUV420SPToRGB709(unsigned char* buffer_in, unsigned char* buffer_out, NPU_PAR_S* pstPar, int MeanPixel[3]);

VIM_U32  Alg_Resize_wh_RGB709_stretch(VIM_U8* buffer_in, VIM_U8* buffer_out, NPU_PAR_S* pstPar, VIM_S32 MeanPixel[3]);

VIM_U32  Alg_Resize_wh_RGB888(VIM_U8 * buffer_in, VIM_U8* buffer_out, NPU_PAR_S* pstPar, VIM_S32 MeanPixel[3]);

VIM_S32  Alg_Trackface_GetTrackId(VIM_S32* x, VIM_S32* y, VIM_S32* ex, VIM_S32* ey, VIM_S32 num, VIM_S32* idarr);

VIM_VOID Alg_TrackFace_Init(VIM_S32 frame,float iou);

VIM_VOID Alg_TrackFace_UnInit();

VIM_VOID Alg_Image_Enhance(VIM_VOID * rgbbufin_b,VIM_VOID * rgbbufin_g,VIM_VOID * rgbbufin_r,VIM_U8 * rgbbufout,VIM_S32 width,VIM_S32 height);

VIM_DOUBLE ALG_GetBlur(VIM_U8 * rgb,VIM_S32 width,VIM_S32 height);

VIM_VOID Alg_Body_GetSingleKeyPoint(VIM_F32 bboxes[][4], VIM_F32 bbox_scores[], VIM_F32 pose_preds[][17][2], VIM_F32 pose_scores[][17],VIM_S32 personNum);

VIM_VOID Alg_Body_GetSinglePrediction(VIM_F32 hms[][17][80][64],VIM_F32 pose_preds[][17][2],VIM_F32 pose_scores[][17],VIM_S32 personNum,VIM_F32 lefttop[][2],VIM_F32 rightbottom[][2]);

VIM_S32 Alg_Body_GetAllKeyPoint(VIM_F32 *heatmap, VIM_F32 *pafsx, VIM_S32 width,VIM_S32 height,HUMAN_RESULT_S stHumanResult[]);

VIM_F32 Alg_Vague(VIM_U8 * Rbuf);

VIM_VOID Alg_Get_Version(VIM_CHAR pVersion[10]);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* __NPU_ALG_H__ */
