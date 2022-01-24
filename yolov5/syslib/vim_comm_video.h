/*******************************************************************************
  Copyright (C), 2001-2011, Vimicro Tech. Co., Ltd.

 ******************************************************************************
 File Name     : vim_comm_video.h
 Version       : Initial Draft
 Author        : c42025
 Created       : 2006/11/09
 Description   :
 History       :
 1.Date        : 2006/11/03
   Author      : c42025
   Modification: Created file

 2.Date        : 2007/12/11
   Author      : c42025
   Modification: delelte all about digital watermark

 3.Date        :   2008/10/31
   Author      :   z44949
   Modification:   Translate the chinese comment
******************************************************************************/

#ifndef __VIM_COMM_VIDEO_H__
#define __VIM_COMM_VIDEO_H__

#include "vim_type.h"
#include "vim_defines.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef struct vimPOINT_S
{
    VIM_S32 s32X;
    VIM_S32 s32Y;
} POINT_S;

typedef struct vimSIZE_S
{
    VIM_U32 u32Width;
    VIM_U32 u32Height;
} SIZE_S;

typedef struct vimRECT_S
{
    VIM_S32 s32X;
    VIM_S32 s32Y;
    VIM_U32 u32Width;
    VIM_U32 u32Height;
} RECT_S;

typedef struct vimAREA_S
{
    VIM_S32 s32StartX;
    VIM_S32 s32StartY;
    VIM_S32 s32EndX;
    VIM_S32 s32EndY;
} AREA_S;
typedef enum vimPIC_SIZE_E
{
    PIC_QCIF = 0,
    PIC_CIF,
    PIC_2CIF,
    PIC_HD1,
    PIC_D1,
    PIC_960H,

    PIC_QVGA,    /* 320 * 240 */
    PIC_VGA,     /* 640 * 480 */
    PIC_XGA,     /* 1024 * 768 */
    PIC_SXGA,    /* 1400 * 1050 */
    PIC_UXGA,    /* 1600 * 1200 */
    PIC_QXGA,    /* 2048 * 1536 */

    PIC_WVGA,    /* 854 * 480 */
    PIC_WSXGA,   /* 1680 * 1050 */
    PIC_WUXGA,   /* 1920 * 1200 */
    PIC_WQXGA,   /* 2560 * 1600 */

    PIC_HD720,   /* 1280 * 720 */
    PIC_HD1080,  /* 1920 * 1080 */
    PIC_HD1920,
    PIC_2304x1296, /* 3M:2304 * 1296 */
    PIC_2592x1520, /* 4M:2592 * 1520 */
	PIC_4M,
    PIC_5M,        /* 2592 * 1944 */
    PIC_UHD4K,     /* 3840 * 2160 */
    PIC_3Kx3K,      /* 3000 * 3000 */
	PIC_12M,     	/* 4000 * 3000 */
	PIC_16M,     	/* 4608 * 3456 */

//xierong 20180524 move from git
    PIC_HD1088,  /* 1920 * 1088 */    
    PIC_DIVA,  /* 320 * 180 */
    PIC_CAR, /* 1280 * 960*/
    PIC_SVGA,/*800*600*/
    PIC_IPPM1,/*2688*1520*/
    PIC_IPPM2,/*2464*2040*/
    PIC_FACE, 
    PIC_FACE1,
    PIC_FACE2,
    PIC_HHD1080,
    PIC_4CIF,
    PIC_480_272,
	PIC_640_368,	

    PIC_BUTT
} PIC_SIZE_E;

typedef enum vimVIDEO_NORM_E
{
    VIDEO_ENCODING_MODE_PAL = 0,
    VIDEO_ENCODING_MODE_NTSC,
    VIDEO_ENCODING_MODE_AUTO,
    VIDEO_ENCODING_MODE_BUTT
} VIDEO_NORM_E;

typedef enum vimVIDEO_CONTROL_MODE_E
{
    VIDEO_CONTROL_MODE_SLAVER = 0,
    VIDEO_CONTROL_MODE_MASTER,
    VIDEO_CONTROL_MODE_BUTT
} VIDEO_CONTROL_MODE_E;

/* we ONLY define picture format used, all unused will be deleted!*/
typedef enum vimPIXEL_FORMAT_E
{   
    PIXEL_FORMAT_RGB_1BPP = 0,
    PIXEL_FORMAT_RGB_2BPP,
    PIXEL_FORMAT_RGB_4BPP,
    PIXEL_FORMAT_RGB_8BPP,
    PIXEL_FORMAT_RGB_444,
    PIXEL_FORMAT_RGB_4444,
    PIXEL_FORMAT_RGB_555,
    PIXEL_FORMAT_RGB_565,
    PIXEL_FORMAT_RGB_1555,

    /*  9 reserved */
    PIXEL_FORMAT_RGB_888,
    PIXEL_FORMAT_RGB_8888,
    PIXEL_FORMAT_RGB_PLANAR_888,
    PIXEL_FORMAT_RGB_BAYER_8BPP,
    PIXEL_FORMAT_RGB_BAYER_10BPP,
    PIXEL_FORMAT_RGB_BAYER_12BPP,
    PIXEL_FORMAT_RGB_BAYER_14BPP,
    PIXEL_FORMAT_RGB_BAYER,

    PIXEL_FORMAT_YUV_A422,
    PIXEL_FORMAT_YUV_A444,

    PIXEL_FORMAT_YUV_PLANAR_422,
    PIXEL_FORMAT_YUV_PLANAR_420,
    PIXEL_FORMAT_YUV_PLANAR_444,

    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    PIXEL_FORMAT_YUV_SEMIPLANAR_420,
    PIXEL_FORMAT_YUV_SEMIPLANAR_444,
//21
    PIXEL_FORMAT_UYVY_PACKAGE_422,
    PIXEL_FORMAT_YUYV_PACKAGE_422,
    PIXEL_FORMAT_VYUY_PACKAGE_422,
    PIXEL_FORMAT_YCbCr_PLANAR,

    PIXEL_FORMAT_RGB_422,
    PIXEL_FORMAT_RGB_420,

    PIXEL_FORMAT_YUV_PLANAR_400,
    PIXEL_FORMAT_YUV_PLANAR_422_P10,
    PIXEL_FORMAT_YUV_PLANAR_420_P10,
    PIXEL_FORMAT_YUV_PLANAR_420_P10_32BIT_LSB,
    PIXEL_FORMAT_YUV_PLANAR_400_P10,
    PIXEL_FORMAT_YUV_SEMIPLANAR_422_P10,
    PIXEL_FORMAT_YUV_SEMIPLANAR_420_P10,
    PIXEL_FORMAT_YUV_SEMIPLANAR_420_P10_32BIT_LSB,

    //33
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER8BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER10BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER12BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER14BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER16BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_ToneMapping_RGB16BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_toYUV422_YUV444,
    PIXEL_FORMAT_ISP_DEBUG_IN_CE_YUV422,

    //41
    PIXEL_FORMAT_ISP_DEBUG_OUT_DPC_BAYER16BIT,
    PIXEL_FORMAT_ISP_DEBUG_OUT_CFA_RGB16BIT,
    PIXEL_FORMAT_ISP_DEBUG_OUT_RgbGains2_RGB10BIT,
    PIXEL_FORMAT_ISP_DEBUG_OUT_toYUV422_YUV422,
    PIXEL_FORMAT_ISP_DEBUG_OUT_BCHS_10BIT_YUV422,
    PIXEL_FORMAT_ISP_DEBUG_OUT_INPUT_BAYER16BIT,
    
    //47
    PIXEL_FORMAT_SIF_OUT_PIXEL_1BYTE,
    PIXEL_FORMAT_SIF_OUT_PIXEL_2BYTE,

    //49
    PIXEL_FORMAT_RGB_PLANAR_601,
    PIXEL_FORMAT_RGB_PLANAR_601_P10,
    PIXEL_FORMAT_RGB_PLANAR_709,
    PIXEL_FORMAT_RGB_PLANAR_709_P10,	

    //53
    PIXEL_FORMAT_ISP_DEBUG_OUT_BCHS_8BIT_YUV422,

    PIXEL_FORMAT_YUV_SEMIPLANAR_411,
    PIXEL_FORMAT_YUV_SEMIPLANAR_400,
    
    PIXEL_FORMAT_YUV_400,
    PIXEL_FORMAT_BUTT   
} PIXEL_FORMAT_E;

typedef enum vimVIDEO_DATA_FORMAT
{
	// Only for Layer Graphic
	PIXEL_FMT_RGB8 = 0,
	PIXEL_FMT_RGB565,
	PIXEL_FMT_RGB888_UNPACKED,
	PIXEL_FMT_ARGB1555,
	PIXEL_FMT_ARGB8888,
	PIXEL_FMT_RGBA8888,//5

	// Only for Layer Video
	PIXEL_FMT_YUV422_UYVY,
	PIXEL_FMT_YUV422_VYUY,
	PIXEL_FMT_YUV422_YUYV,
	PIXEL_FMT_YUV422_YVYU,
	PIXEL_FMT_YUV422_SP_UV,//10
	PIXEL_FMT_YUV422_SP_VU,
	PIXEL_FMT_YUV420_SP_UV,
	PIXEL_FMT_YUV420_SP_VU,
	PIXEL_FMT_YUV422_P_YUYV,
	PIXEL_FMT_YUV422_P_YVYU,
	PIXEL_FMT_YUV420_P_YUYV,
	PIXEL_FMT_YUV420_P_YVYU,

	PIXEL_FMT_UNKNOWN,
}PIXEL_FMT_E;

#if 0
typedef enum vimPIXEL_FORMAT_E
{   
	PIXEL_FORMAT_RESERVED = 0,
	PIXEL_FORMAT_RGB_565,
	PIXEL_FORMAT_RGB_888,
	PIXEL_FORMAT_ARGB_1555,
	PIXEL_FORMAT_ARGB_8888,
	PIXEL_FORMAT_RGBA_8888,

	PIXEL_FORMAT_UYVY_INTERLEAVED_422,
	PIXEL_FORMAT_VYUY_INTERLEAVED_422,
	PIXEL_FORMAT_YUYV_INTERLEAVED_422,
	PIXEL_FORMAT_YVYU_INTERLEAVED_422,
	PIXEL_FORMAT_UV_SEMIPLANAR_YUV422,
	PIXEL_FORMAT_VU_SEMIPLANAR_YUV422,	
	PIXEL_FORMAT_UV_SEMIPLANAR_YUV420,
	PIXEL_FORMAT_VU_SEMIPLANAR_YUV420,

#if 0
    PIXEL_FORMAT_RGB_1BPP = 0,
    PIXEL_FORMAT_RGB_2BPP,
    PIXEL_FORMAT_RGB_4BPP,
    PIXEL_FORMAT_RGB_8BPP,
    PIXEL_FORMAT_RGB_444,
    PIXEL_FORMAT_RGB_4444,
    PIXEL_FORMAT_RGB_555,
    PIXEL_FORMAT_RGB_565,
    PIXEL_FORMAT_RGB_1555,

    /*  9 reserved */
    PIXEL_FORMAT_RGB_888,
    PIXEL_FORMAT_RGB_8888,
    PIXEL_FORMAT_RGB_PLANAR_888,
    PIXEL_FORMAT_RGB_BAYER_8BPP,
    PIXEL_FORMAT_RGB_BAYER_10BPP,
    PIXEL_FORMAT_RGB_BAYER_12BPP,
    PIXEL_FORMAT_RGB_BAYER_14BPP,
    PIXEL_FORMAT_RGB_BAYER,

    PIXEL_FORMAT_YUV_A422,
    PIXEL_FORMAT_YUV_A444,

    PIXEL_FORMAT_YUV_PLANAR_422,
    PIXEL_FORMAT_YUV_PLANAR_420,
    PIXEL_FORMAT_YUV_PLANAR_444,

    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    PIXEL_FORMAT_YUV_SEMIPLANAR_420,
    PIXEL_FORMAT_YUV_SEMIPLANAR_444,
//21
    PIXEL_FORMAT_UYVY_PACKAGE_422,
    PIXEL_FORMAT_YUYV_PACKAGE_422,
    PIXEL_FORMAT_VYUY_PACKAGE_422,
    PIXEL_FORMAT_YCbCr_PLANAR,

    PIXEL_FORMAT_RGB_422,
    PIXEL_FORMAT_RGB_420,

    PIXEL_FORMAT_YUV_PLANAR_400,
    PIXEL_FORMAT_YUV_PLANAR_422_P10,
    PIXEL_FORMAT_YUV_PLANAR_420_P10,
    PIXEL_FORMAT_YUV_PLANAR_400_P10,
    PIXEL_FORMAT_YUV_SEMIPLANAR_422_P10,
    PIXEL_FORMAT_YUV_SEMIPLANAR_420_P10,

    //33
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER8BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER10BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER12BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER14BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_BAYER16BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_ToneMapping_RGB16BIT,
    PIXEL_FORMAT_ISP_DEBUG_IN_toYUV422_YUV444,
    PIXEL_FORMAT_ISP_DEBUG_IN_CE_YUV422,

    //41
    PIXEL_FORMAT_ISP_DEBUG_OUT_DPC_BAYER16BIT,
    PIXEL_FORMAT_ISP_DEBUG_OUT_CFA_RGB16BIT,
    PIXEL_FORMAT_ISP_DEBUG_OUT_RgbGains2_RGB10BIT,
    PIXEL_FORMAT_ISP_DEBUG_OUT_toYUV422_YUV422,
    PIXEL_FORMAT_ISP_DEBUG_OUT_BCHS_10BIT_YUV422,
    PIXEL_FORMAT_ISP_DEBUG_OUT_INPUT_BAYER16BIT,
    
    //47
    PIXEL_FORMAT_SIF_OUT_PIXEL_1BYTE,
    PIXEL_FORMAT_SIF_OUT_PIXEL_2BYTE,

    //49
    PIXEL_FORMAT_RGB_PLANAR_601,
    PIXEL_FORMAT_RGB_PLANAR_601_P10,
    PIXEL_FORMAT_RGB_PLANAR_709,
    PIXEL_FORMAT_RGB_PLANAR_709_P10,	

    //53
    PIXEL_FORMAT_ISP_DEBUG_OUT_BCHS_8BIT_YUV422,

    PIXEL_FORMAT_YUV_SEMIPLANAR_411,
    PIXEL_FORMAT_YUV_SEMIPLANAR_400,
    
    PIXEL_FORMAT_YUV_400,
#endif    
    PIXEL_FORMAT_BUTT   
} PIXEL_FORMAT_E;
#endif

typedef struct vimVIDEO_VBI_INFO_S
{
    VIM_U32 au32Data[VIU_MAX_VBI_LEN];
    VIM_U32 u32Len;
} VIDEO_VBI_INFO_S;

typedef enum vimVIDEO_FIELD_E
{
    VIDEO_FIELD_TOP         = 0x1,    /* even field */
    VIDEO_FIELD_BOTTOM      = 0x2,    /* odd field */
    VIDEO_FIELD_INTERLACED  = 0x3,    /* two interlaced fields */
    VIDEO_FIELD_FRAME       = 0x4,    /* frame */
    VIDEO_FIELD_BUTT
} VIDEO_FIELD_E;

typedef enum vimVIDEO_FORMAT_E
{
    VIDEO_FORMAT_LINEAR		= 0x0,		/* nature video line */
    VIDEO_FORMAT_TILE		= 0x1,		/* tile cell: 256pixel x 16line, default tile mode */
    VIDEO_FORMAT_TILE64		= 0x2,		/* tile cell: 64pixel x 16line */
    VIDEO_FORMAT_BUTT
} VIDEO_FORMAT_E;

typedef enum vimCOMPRESS_MODE_E
{
    COMPRESS_MODE_NONE		= 0x0,		/* no compress */
    COMPRESS_MODE_SEG		= 0x1,		/* compress unit is 256 bytes as a segment, default seg mode */
    COMPRESS_MODE_SEG128	= 0x2,		/* compress unit is 128 bytes as a segment */
    COMPRESS_MODE_LINE		= 0x3,		/* compress unit is the whole line */
    COMPRESS_MODE_FRAME		= 0x4,		/* compress unit is the whole frame */

    COMPRESS_MODE_BUTT
} COMPRESS_MODE_E;

typedef enum vimREAL_TIME__MODE_E
{
    REAL_TIME_MODE_NONE		= 0x0,
    REAL_TIME_MODE_CLOSE    = 0x10,	
    REAL_TIME_MODE_OPEN	    = 0x20,
    REAL_TIME_MODE_BUTT
} REAL_TIME_MODE_E;

typedef enum vimGET_FRAME_MODE_E
{
    GET_FRAME_MODE_NONE		= 0x0,
    GET_FRAME_MODE_CLOSE    = 0x10,	
    GET_FRAME_MODE_OPEN	    = 0x20,
    GET_FRAME_MODE_BUTT
} GET_FRAME_MODE_E;

typedef enum vimVIDEO_DISPLAY_MODE_E
{
    VIDEO_DISPLAY_MODE_PREVIEW		= 0x0,
    VIDEO_DISPLAY_MODE_PLAYBACK		= 0x1,
    VIDEO_DISPLAY_MODE_BUTT
} VIDEO_DISPLAY_MODE_E;


#define DCF_DRSCRIPTION_LENGTH      32
#define DCF_CAPTURE_TIME_LENGTH     20

typedef struct vimISP_DCF_INFO_S
{
    VIM_U8       au8ImageDescription[DCF_DRSCRIPTION_LENGTH];        /*Describes image*/
    VIM_U8       au8Make[DCF_DRSCRIPTION_LENGTH];                    /*Shows manufacturer of digital cameras*/
    VIM_U8       au8Model[DCF_DRSCRIPTION_LENGTH];                   /*Shows model number of digital cameras*/
    VIM_U8       au8Software[DCF_DRSCRIPTION_LENGTH];                /*Shows firmware (internal software of digital cameras) version number*/

    VIM_U16      u16ISOSpeedRatings;                                 /*CCD sensitivity equivalent to Ag-Hr film speedrate*/
    VIM_U32      u32FNumber;                                         /*The actual F-number (F-stop) of lens when the image was taken*/
    VIM_U32      u32MaxApertureValue;                                /*Maximum aperture value of lens.*/
    VIM_U32      u32ExposureTime;                                    /*Exposure time (reciprocal of shutter speed).*/
    VIM_U32      u32ExposureBiasValue;                               /*Exposure bias (compensation) value of taking picture*/
    VIM_U8       u8ExposureProgram;                                  /*Exposure program that the camera used when image was taken. '1' means manual control, '2'
                                                                              program normal, '3' aperture priority, '4' shutter priority, '5' program creative (slow program),
                                                                              '6' program action(high-speed program), '7' portrait mode, '8' landscape mode*/
    VIM_U8       u8MeteringMode;                                     /*Exposure metering method. '0' means unknown, '1' average, '2' center weighted average, '3'
                                                                              spot, '4' multi-spot, '5' multi-segment, '6' partial, '255' other*/
    VIM_U8       u8LightSource;                                      /*Light source, actually this means white balance setting. '0' means unknown, '1' daylight, '2'
                                                                               fluorescent, '3' tungsten, '10' flash, '17' standard light A, '18' standard light B, '19' standard light
                                                                               C, '20' D55, '21' D65, '22' D75, '255' other*/
    VIM_U32      u32FocalLength;                                     /*Focal length of lens used to take image. Unit is millimeter*/
    VIM_U8       u8SceneType;                                        /*Indicates the type of scene. Value '0x01' means that the image was directly photographed.*/
    VIM_U8       u8CustomRendered;                                   /*Indicates the use of special processing on image data, such as rendering geared to output.
                                                                               0 = Normal process  1 = Custom process   */
    VIM_U8       u8ExposureMode;                                     /*Indicates the exposure mode set when the image was shot.
                                                                              0 = Auto exposure,1 = Manual exposure, 2 = Auto bracket*/
    VIM_U8       u8WhiteBalance;                                     /* Indicates the white balance mode set when the image was shot.
                                                                                0 = Auto white balance ,1 = Manual white balance */
    VIM_U8       u8FocalLengthIn35mmFilm;                            /*Indicates the equivalent focal length assuming a 35mm film camera, in mm*/
    VIM_U8       u8SceneCaptureType;                                 /*Indicates the type of scene that was shot. 0 = Standard,1 = Landscape,2 = Portrait,3 = Night scene. */
    VIM_U8       u8GainControl;                                      /*Indicates the degree of overall image gain adjustment. 0 = None,1 = Low gain up,2 = High gain up,3 = Low gain down,4 = High gain down. */
    VIM_U8       u8Contrast;                                         /*Indicates the direction of contrast processing applied by the camera when the image was shot.
                                                                               0 = Normal,1 = Soft,2 = Hard */
    VIM_U8       u8Saturation;                                       /*Indicates the direction of saturation processing applied by the camera when the image was shot.
                                                                              0 = Normal,1 = Low saturation,2 = High saturation*/
    VIM_U8       u8Sharpness;                                        /*Indicates the direction of sharpness processing applied by the camera when the image was shot.
                                                                              0 = Normal,1 = Soft,2 = Hard .*/
} ISP_DCF_INFO_S;

typedef struct vimJPEG_DCF_S
{
    VIM_U8           au8CaptureTime[DCF_CAPTURE_TIME_LENGTH];            /*The date and time when the picture data was generated*/
    VIM_U8           bFlash;                                             /*whether the picture is captured when a flash lamp is on*/
    VIM_U32          u32DigitalZoomRatio;                                /*Indicates the digital zoom ratio when the image was shot.
                                                                                   If the numerator of the recorded value is 0, this indicates that digital zoom was not used.*/
    ISP_DCF_INFO_S  stIspDCFInfo;

} JPEG_DCF_S;

typedef struct vimFRAME_SUPPLEMENT_INFO_S
{
	VIM_U32		u32ISO; 								            /*ISP internal ISO : Again*Dgain*ISPgain*/
    VIM_U32      u32ExposureTime;                                    /*Exposure time (reciprocal of shutter speed).*/
    VIM_U32      u32FNumber;                                         /*The actual F-number (F-stop) of lens when the image was taken*/
    VIM_U32 		u32IspNrStrength[4];
} FRAME_SUPPLEMENT_INFO_S;

typedef enum vimFRAME_FLASH_TYPE_E
{
    FRAME_FLASH_OFF  = 0,
    FRAME_FLASH_ON   = 1,
    FRAME_FLASH_BUTT,
} FRAME_FLASH_TYPE_E;

#define FRAME_FLAG_FRAME_TYPE_MASK  (0xF << 8)
#define FRAME_FLAG_REF_TYPE_MASK    (0xF << 4)
#define FRAME_FLAG_FLASH_TYPE_MASK  (0x1 << 0)

typedef enum vimFRAME_STATE_E
{
    FRAME_FLAG_FLASH_OFF     = 0,
    FRAME_FLAG_FLASH_ON      = 1,
    FRAME_FLAG_SNAP_0REF_CUR     = 0x4 << 4,
    FRAME_FLAG_SNAP_2REF_REF = 0x2 << 4,
    FRAME_FLAG_SNAP_2REF_CUR  = 0x6 << 4,
    FRAME_FLAG_SNAP_NORMAL      = 0x1 << 8,
    FRAME_FLAG_SNAP_PRO      = 0x2 << 8,
	FRAME_FLAG_SNAP_END      = 0x1 << 31,
    FRAME_FLAG_BUTT
} FRAME_FLAG_E;

typedef enum vimSNAP_ISP_STATE_E
{
    SNAP_STATE_NULL = 0,
    SNAP_STATE_CFG  = 1,
    SNAP_STATE_EFF  = 2,
    SNAP_STATE_BUTT
} SNAP_ISP_STATE_E;

typedef struct vimSNAP_ISP_INFO_S
{
    VIM_U32  u32Iso;
    VIM_U32  u32IspDgain;
    VIM_U32  u32ExposureTime;
    VIM_U32  au32WhiteBalanceGain[4];
    VIM_U32  u32ColorTemp;
    VIM_U16  au16CapCCM[9];
    SNAP_ISP_STATE_E enCapState;
} ISP_CONFIG_INFO_S;

typedef enum vimSNAP_TYPE_E
{
    SNAP_TYPE_NONE = 0, /* video mode */
    SNAP_TYPE_NORMAL,   /* ZSL and none-ZSL type */
    SNAP_TYPE_PRO,      /* Professional type support HDR, AEB, LongExposure */
    SNAP_TYPE_USER,     /* USER SEND RAW type */
    SNAP_TYPE_BUTT
} SNAP_TYPE_E;

typedef struct vimISP_FRAME_INFO_S
{
    VIM_U32 u32Iso;
    VIM_U32 u32ExposureTime;
} ISP_FRAME_INFO_S;

#define ISP_AE_ZONE_ROW                 (15)
#define ISP_AE_ZONE_COLUMN              (17)
#define ISP_AWB_ZONE_ROW                (32)
#define ISP_AWB_ZONE_COLUMN             (32)
#define ISP_AWB_ZONE_NUM                (ISP_AWB_ZONE_ROW * ISP_AWB_ZONE_COLUMN) 
#define ISP_BAYER_CHN   (4)
typedef struct vimISP_AE_STAT_INFO_S
{
	VIM_U16	au16ZoneAvg[ISP_AE_ZONE_ROW][ISP_AE_ZONE_COLUMN][ISP_BAYER_CHN];	
}ISP_AE_STAT_INFO_S;
typedef struct vimISP_AWB_STAT_INFO_S
{
	VIM_U16 au16ZoneAvgR[ISP_AWB_ZONE_NUM];            /*RO, Zone Average R, Range: [0x0, 0xFFFF]*/   
	VIM_U16 au16ZoneAvgG[ISP_AWB_ZONE_NUM];            /*RO, Zone Average G, Range: [0x0, 0xFFFF]*/   
	VIM_U16 au16ZoneAvgB[ISP_AWB_ZONE_NUM];            /*RO, Zone Average B, Range: [0x0, 0xFFFF]*/   
	VIM_U16 au16ZoneCountAll[ISP_AWB_ZONE_NUM];        /*RO, normalized number of Gray points, Range: [0x0, 0xFFFF]*/   
	VIM_U16 au16ZoneCountMin[ISP_AWB_ZONE_NUM];        /*RO, normalized number of pixels under BlackLevel, Range: [0x0, 0xFFFF]*/   
	VIM_U16 au16ZoneCountMax[ISP_AWB_ZONE_NUM];        /*RO, normalized number of pixels above Whitelevel, Range: [0x0, 0xFFFF]*/ 
} ISP_AWB_STAT_INFO_S;
#define HIST_1024_NUM   (1024)
typedef struct vimISP_AE_HISTOGRAM_S
{    
    VIM_U32  au32AeHistogramStat[HIST_1024_NUM];
} ISP_AE_HISTOGRAM_S;
typedef struct vimISP_RAW_STAT_INFO_S
{
	ISP_AE_STAT_INFO_S	stIspAeInfo;	
	ISP_AE_HISTOGRAM_S 	stAeHistogram;
	ISP_AWB_STAT_INFO_S	stIspAwbInfo;
} ISP_RAW_STAT_INFO_S;
typedef struct vimVIDEO_SUPPLEMENT_S
{
    VIM_U32   enFlashType;
    VIM_U32   u32JpegDcfPhyAddr;
    VIM_VOID* pJpegDcfVirAddr;
    VIM_U32   u32FrameSupplementPhyAddr;
    VIM_VOID* pFrameSupplementVirAddr;

    VIM_U64   u64RawPts;
    VIM_U32   u32IspInfoPhyAddr;
    VIM_VOID* pIspInfoVirAddr;
	VIM_U32   u32IspStatPhyAddr;
	VIM_VOID* pIspStatVirAddr;
} VIDEO_SUPPLEMENT_S;

typedef struct vimVIDEO_FRAME_S
{
    VIM_U32          u32Width;
    VIM_U32          u32Height;
    VIDEO_FIELD_E   u32Field;
    PIXEL_FORMAT_E  enPixelFormat;

    VIDEO_FORMAT_E  enVideoFormat;
    COMPRESS_MODE_E	enCompressMode;

    VIM_U32          viSequence;	
    VIM_U32          yuvbufidx;
    VIM_U32          viLlcInfo[8];

    VIM_U32          u32PhyAddr[3];
    VIM_VOID*        pVirAddr[3];
    VIM_U32          u32Stride[3];
    VIM_U32          u32Size[3];

    VIM_U32          u32HeaderPhyAddr[3];
    VIM_VOID*        pHeaderVirAddr[3];
    VIM_U32          u32HeaderStride[3];

    VIM_S16          s16OffsetTop;		/* top offset of show area */
    VIM_S16          s16OffsetBottom;	/* bottom offset of show area */
    VIM_S16          s16OffsetLeft;		/* left offset of show area */
    VIM_S16          s16OffsetRight;		/* right offset of show area */

    VIM_U64          u64pts;
    VIM_U32          u32TimeRef;

    unsigned long    u32PrivateData;
    VIDEO_SUPPLEMENT_S stSupplement;
	GET_FRAME_MODE_E enGetFrameMode;
} VIDEO_FRAME_S;

typedef struct vimVIDEO_FRAME_INFO_S
{
    VIDEO_FRAME_S stVFrame;
    VIM_U32 u32PoolId;
} VIDEO_FRAME_INFO_S;

typedef struct vimBITMAP_S
{
    PIXEL_FORMAT_E enPixelFormat;  /* Bitmap's pixel format */
    VIM_U32 u32Width;               /* Bitmap's width */
    VIM_U32 u32Height;              /* Bitmap's height */
    VIM_VOID* pData;                /* Address of Bitmap's data */
} BITMAP_S;

/* VI Mix-Capture info. */
typedef struct vimVI_MIXCAP_STAT_S
{
    VIM_BOOL bMixCapMode;    /* In mix-capture mode or not. */
    VIM_BOOL bHasDownScale;  /* VI Frame is downscaled or not. */
} VI_MIXCAP_STAT_S;

/* VI output frame info. */
typedef struct vimVI_FRAME_INFO_S
{
    VI_MIXCAP_STAT_S stMixCapState; /* VI Mix-Capture info. */
    VIDEO_FRAME_INFO_S stViFrmInfo; /* Video frame info. */
} VI_FRAME_INFO_S;

typedef enum vimLDC_VIEW_TYPE_E
{
    LDC_VIEW_TYPE_ALL 	= 0,  	/* View scale all but x and y independtly, this will keep both x and y axis ,but corner maybe lost*/
    LDC_VIEW_TYPE_CROP	= 1,	/* Not use view scale, this will lost some side and corner */

    LDC_VIEW_TYPE_BUTT,
} LDC_VIEW_TYPE_E;

typedef struct vimLDC_ATTR_S
{
    LDC_VIEW_TYPE_E enViewType;
    VIM_S32 s32CenterXOffset;        /* Horizontal offset of the image distortion center relative to image center.*/
    VIM_S32 s32CenterYOffset;        /* Vertical offset of the image distortion center relative to image center.*/
    VIM_S32 s32Ratio;                /* Distortion ratio.*/
	VIM_S32 s32MinRatio;
} LDC_ATTR_S;

typedef enum vimWDR_MODE_E
{
    WDR_MODE_NONE = 0,
    WDR_MODE_BUILT_IN,

    WDR_MODE_2To1_LINE,
    WDR_MODE_2To1_FRAME,
    WDR_MODE_2To1_FRAME_FULL_RATE,

    WDR_MODE_3To1_LINE,
    WDR_MODE_3To1_FRAME,
    WDR_MODE_3To1_FRAME_FULL_RATE,

    WDR_MODE_4To1_LINE,
    WDR_MODE_4To1_FRAME,
    WDR_MODE_4To1_FRAME_FULL_RATE,

    WDR_MODE_BUTT,
}WDR_MODE_E;

typedef struct vimISP_DCF_UPDATE_INFO_S
{
    VIM_U16      u16ISOSpeedRatings;                                 /*CCD sensitivity equivalent to Ag-Hr film speedrate*/
    VIM_U32      u32ExposureTime;                                    /*Exposure time (reciprocal of shutter speed).*/
    VIM_U32      u32ExposureBiasValue;                               /*Exposure bias (compensation) value of taking picture*/
    VIM_U8       u8ExposureProgram;                                  /*Exposure program that the camera used when image was taken. '1' means manual control, '2'
                                                                              program normal, '3' aperture priority, '4' shutter priority, '5' program creative (slow program),
                                                                              '6' program action(high-speed program), '7' portrait mode, '8' landscape mode*/
    VIM_U32      u32FNumber;                                         /*The actual F-number (F-stop) of lens when the image was taken*/
    VIM_U32      u32MaxApertureValue;                                /*Maximum aperture value of lens.*/
    VIM_U8       u8MeteringMode;                                     /*Exposure metering method. '0' means unknown, '1' average, '2' center weighted average, '3'
                                                                              spot, '4' multi-spot, '5' multi-segment, '6' partial, '255' other*/
    VIM_U8       u8ExposureMode;                                     /*Indicates the exposure mode set when the image was shot.
                                                                              0 = Auto exposure,1 = Manual exposure, 2 = Auto bracket*/
    VIM_U8       u8WhiteBalance;                                     /* Indicates the white balance mode set when the image was shot.
                                                                                0 = Auto white balance ,1 = Manual white balance */
} ISP_DCF_UPDATE_INFO_S;


typedef struct PICFMT_S
{
	VIM_U32 Chn;
    PIXEL_FORMAT_E enPixelFormat;  /* pic's pixel format */
    VIM_U32 u32Width;               /* pic's width */
    VIM_U32 u32Height;              /* pic's height */
} PICFMT_S;



/*vi register info  start ---------*/
typedef struct __ipp_call_data{
	VIM_U32 width;
	VIM_U32 height;
	VIM_U32 addr;
	VIM_U32 addr_uv;
	VIM_U32 vaddr;
	VIM_U32 frame_no;
	VIM_U32 out_mode;
	VIM_U32 bit_mode;
	void* data;
//	struct timeval timestamp;
}st_ipp_cb_data;


/***********************************
  * VC0768 新增结构
 **********************************/
typedef enum{
    EM_CMP_NORMAL=0,
    EM_CMP_LLC,
    EM_CMP_CFRAME,
    EM_CMP_BUTT,
}VIM_VIDEO_CMP_FORMAT_E;


typedef enum
{
    EM_FORMAT_RAW8=0x10,
    EM_FORMAT_RAW10,
    EM_FORMAT_RAW12,
    EM_FORMAT_RAW14,
    EM_FORMAT_RAW16,
    EM_FORMAT_YUV420S_8BIT=0x20,
    EM_FORMAT_YUV420S_10BIT,
    EM_FORMAT_YUV422S_8BIT,
    EM_FORMAT_YUV422S_10BIT,
    EM_FORMAT_YUV420P_8BIT,
    EM_FORMAT_YUV420P_10BIT,
    EM_FORMAT_YUV422P_8BIT,
    EM_FORMAT_YUV422P_10BIT,
    EM_FORMAT_BUTT
}VIM_PIXEL_FORMAT_E;

/**********************
 * plane_num:  有效范围 (1-3)
 * 
 * 当plane_num=1 适用于仅需要单组地址标识的情况,如 uyvyI422 10bit
 * 仅使用 Y相关地址信息(y_phyaddr..)
 * 
 * 当plane_num=2 适用于需要两组地址标识的情况,如 RAW odd帧和event帧 或者
 * YUV420 422使用 Y+UV地址的信息(y_phyaddr+uv_phyaddr..)
 * 
 * 当plane_num=3  适用于需要三组地址标识的情况,如 
 * YUV420 422 独立分量地址， 使用 Y+U+V相关地址信息，此时的uv地址仅作为u地址使用
 * (y_phyaddr+uv_phyaddr+v_phyaddr);
 * 
 * 
 * *********************/
typedef struct __video_addr_info_s{
    VIM_U32     plane_num;   
    VIM_U32     y_phyaddr;  //Y帧或者odd帧物理地址
    VIM_VOID    *y_vaddr;   //Y帧或者odd帧虚拟地址
    VIM_U32     y_lenth;    //Y帧或者odd帧长度,  非压缩模式可不填
    VIM_U32     uv_phyaddr; //UV帧或者even帧物理地址
    VIM_VOID    *uv_vaddr;  //UV帧或者even帧虚拟地址
    VIM_U32     uv_lenth;   //UV帧或者even帧长度, 非压缩模式可不填
    VIM_U32     v_phyaddr;  //V帧的物理地址
    VIM_VOID    *v_vaddr;   //V帧的虚拟地址
    VIM_U32     v_lenth;    //V帧的长度，非压缩模式可不填
}VIM_VIDEO_FRAME_INFO_S;

typedef struct __video_attr_s{

    VIM_BOOL                b_cmp_enbale;   //压缩开关
    VIM_VIDEO_CMP_FORMAT_E  cmp_format;     //压缩格式
    VIM_PIXEL_FORMAT_E      pixel_format;   //RAW/YUV格式
    VIM_U32     width;      //图像宽度
    VIM_U32     height;     //图像高度
    VIM_U32     r_mode;     //旋转方式 R/L/V/H
    VIM_U32     line_stride;    //行模式下 输入行数据大小
    VIM_U32     aligned_type;   //128/64/0 (bit)三种对齐方式.
    VIM_U32     frame_num;      //帧号信息
    VIM_U32     frame_vchn;     //vo模块保留字,默认为0. 用于描述帧的虚拟chn编号
    VIM_U32     reserve[4];      //保留字
    VIM_VOID*   pPrivate;       //保留私有指针
    VIM_VIDEO_FRAME_INFO_S  addrs; //帧地址信息
}VIM_VIDEO_ATTR_S;


//SIF<-->ISP DMA交互使用的子结构
typedef struct __sif_dma_info_s
{
    VIM_U32             vb_id;      //VideoBuf的id
    VIM_U32             dev_type;   //源设备类型
    WDR_MODE_E          wdr_mode;   //WDR模式
    VIM_VIDEO_ATTR_S    video_attrs;//视频属性
    VIM_VIDEO_FRAME_INFO_S extend_addrs[3];//扩展地址用来存放WDR多曝光地址
}SIF_DMA_INFO_S;

typedef SIF_DMA_INFO_S  ISP_FRAMES_INFO_S;

//ISP<-->IPP/RATATION/DE..  DMA交互使用的子结构
typedef struct __isp_dma_info_s
{
    VIM_VIDEO_ATTR_S    video_attrs;
}ISP_DMA_INFO_S;

/*********************************
  * VC0768 新增结构
*********************************/


typedef VIM_U32 ipp_dma_callback(st_ipp_cb_data *video_param);

extern void ipp_register_callback(VIM_U32 channel, VIM_U32 priority, ipp_dma_callback * call_back,  void *data);
extern void ipp_unregister_callback(VIM_U32 channel, VIM_U32 priority);
/*vi register info  end ---------*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _HI_COMM_VIDEO_H_ */

