#ifndef __VIM_COMMON_H__
#define __VIM_COMMON_H__

#include "vim_type.h"
#include "vim_math.h"
#include "vim_defines.h"
#include "vim_comm_video.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#ifndef VER_X
    #define VER_X 1
#endif

#ifndef VER_Y
    #define VER_Y 0
#endif

#ifndef VER_Z
    #define VER_Z 0
#endif

#ifndef VER_P
    #define VER_P 0
#endif

#ifndef VER_B
    #define VER_B 0
#endif

#ifdef VIM_DEBUG
    #define VER_D " Debug"
#else
    #define VER_D " Release"
#endif

#define __MK_VERSION(x,y,z,p,b) #x"."#y"."#z"."#p" B0"#b
#define MK_VERSION(x,y,z,p,b) __MK_VERSION(x,y,z,p,b)
#define MPP_VERSION  CHIP_NAME MPP_VER_PRIX MK_VERSION(VER_X,VER_Y,VER_Z,VER_P,VER_B) VER_D

#define VERSION_NAME_MAXLEN 64
typedef struct vimMPP_VERSION_S
{
    VIM_CHAR aVersion[VERSION_NAME_MAXLEN];
} MPP_VERSION_S;

typedef struct vimCROP_INFO_S
{
    VIM_BOOL bEnable;
    RECT_S  stRect;
} CROP_INFO_S;

typedef enum vimROTATE_E
{
    ROTATE_NONE = 0,
    ROTATE_90   = 1,
    ROTATE_180  = 2,
    ROTATE_270  = 3,
    ROTATE_BUTT
} ROTATE_E;

typedef struct vimBORDER_S
{
    VIM_U32 u32TopWidth;
    VIM_U32 u32BottomWidth;
    VIM_U32 u32LeftWidth;
    VIM_U32 u32RightWidth;
    VIM_U32 u32Color;
} BORDER_S;

typedef VIM_S32 AI_CHN;
typedef VIM_S32 AO_CHN;
typedef VIM_S32 AENC_CHN;
typedef VIM_S32 ADEC_CHN;
typedef VIM_S32 AUDIO_DEV;
typedef VIM_S32 AVENC_CHN;
typedef VIM_S32 VI_DEV;
typedef VIM_S32 VI_WAY;
typedef VIM_S32 VI_CHN;
typedef VIM_S32 VO_DEV;
typedef VIM_S32 VO_LAYER;
typedef VIM_S32 VO_CHN;
typedef VIM_S32 VO_MULMODE;
typedef VIM_S32 VO_WBC;
typedef VIM_S32 GRAPHIC_LAYER;
typedef VIM_S32 VENC_CHN;
typedef VIM_S32 VDEC_CHN;
typedef VIM_S32 VENC_GRP;
typedef VIM_S32 VO_GRP;
typedef VIM_S32 VDA_CHN;
typedef VIM_S32 IVE_HANDLE;
typedef VIM_S32 CLS_HANDLE;
typedef VIM_S32 FD_CHN;
typedef VIM_S32 MD_CHN;
typedef VIM_S32 ISP_DEV;
typedef VIM_S32 SENSOR_ID;
typedef VIM_S32 MIPI_DEV;
typedef VIM_S32 JPEG_CHN;
typedef VIM_S32 JDEC_CHN;



#define VIM_INVALID_CHN (-1)
#define VIM_INVALID_WAY (-1)
#define VIM_INVALID_LAYER (-1)
#define VIM_INVALID_DEV (-1)
#define VIM_INVALID_HANDLE (-1)
#define VIM_INVALID_VALUE (-1)
#define VIM_INVALID_TYPE (-1)

#define	MOD_SYS_TAG							"[SYS]"
#define	MOD_VB_TAG							"[VB]"
#define	MOD_VCCAP_TAG							"[VCCAP]"
#define	MOD_VIPP_TAG							"[VIPP]"
#define	MOD_VISP_TAG							"[VISP_CORE]"
#define	MOD_VISP_ALG_TAG						"[VISP_ALG]"
#define MOD_VISP_SNR_TAG						"[SENSOR]"
#define	MOD_VSIF_TAG							"[VSIF]"
#define MOD_GPIO_TAG							"[GPIO]"
#define MOD_DE_TAG							"[VOUT]"
#define	MOD_VI_TAG							"[VI]"
#define	MOD_VENC_TAG							"[VENC]"
#define	MOD_RGN_TAG							"[REGION]"
#define MOD_JPEG_TAG						"[JPEG]"
#define MOD_AI_TAG							"[AIO]"


typedef enum vimMOD_ID_E
{
    VIM_ID_VB      = VIM_BIT0,
    VIM_ID_SYS     = VIM_BIT1,
    VIM_ID_RGN	   = VIM_BIT2,
    VIM_ID_VDEC    = VIM_BIT3,
    VIM_ID_VENC    = VIM_BIT4,
    VIM_ID_VOU     = VIM_BIT5,
    VIM_ID_VIU     = VIM_BIT6,
    VIM_ID_AIO     = VIM_BIT7,
    //VIM_ID_AO    = VIM_BIT8,
    //VIM_ID_AENC  = VIM_BIT9,
    //VIM_ID_ADEC  = VIM_BIT10,
    VIM_ID_ISP	   = VIM_BIT8,
    //VIM_ID_GPIO	 VIM_=BIT12,
	VIM_ID_ISPALG  = VIM_BIT9,
	VIM_ID_JPEG    = VIM_BIT10,
    VIM_ID_NPU	   = VIM_BIT11,
    VIM_ID_AENC    = VIM_BIT12,
    VIM_ID_VPSS    = VIM_BIT13,
    VIM_ID_SENSOR  = VIM_BIT14,

    VIM_ID_BUTT,
} MOD_ID_E;

#define VIM_ID_GPIO  VIM_ID_SYS
//useless Module ID (invlalid)
#define VIM_ID_AI     VIM_BIT16
#define VIM_ID_AO     VIM_BIT17
//#define VIM_ID_AENC   VIM_BIT18
#define VIM_ID_ADEC   VIM_ID_AENC

typedef enum VIM_BIND_MOD_ID_E
{
    VIM_BD_MOD_ID_VIU     = VIM_ID_VIU,
    VIM_BD_MOD_ID_ISP     = VIM_ID_ISP,

    VIM_BD_MOD_ID_VPSS    = VIM_ID_VPSS,
    VIM_BD_MOD_ID_RGN     = VIM_ID_RGN,
    VIM_BD_MOD_ID_NPU     = VIM_ID_NPU,

    VIM_BD_MOD_ID_VDEC    = VIM_ID_VDEC,
    VIM_BD_MOD_ID_VENC    = VIM_ID_VENC,
    VIM_BD_MOD_ID_JPEG    = VIM_ID_JPEG,
    VIM_BD_MOD_ID_VOU     = VIM_ID_VOU,
    
    VIM_BD_MOD_ID_DCVI    = 0x2001,
    VIM_BD_MOD_ID_ROT     = 0x2002,

    VIM_BD_ID_BUTT,
} BIND_MOD_ID_E;

typedef struct vimMPP_CHN_S
{
    MOD_ID_E     enModId;
    VIM_S32      s32DevId;
    VIM_S32      s32ChnId;
} MPP_CHN_S;


typedef struct VIM_SYS_BIND_CHN_S
{
    BIND_MOD_ID_E   enModId;
    VIM_S32         s32DevId;
    VIM_S32         s32ChnId;
} SYS_BD_CHN_S;


typedef enum vimPROFILE_TYPE_E
{
    PROFILE_1080P_30 = 0,
    PROFILE_3M_30,
    PROFILE_1080P_60,
    PROFILE_5M_30,
    PROFILE_BUTT,
} PROFILE_TYPE_E;

#define MPP_MOD_VIU       "vi"
#define MPP_MOD_VOU       "vo"
#define MPP_MOD_HDMI      "hdmi"
#define MPP_MOD_DSU       "dsu"
#define MPP_MOD_VGS       "vgs"
#define MPP_MOD_FISHEYE   "fisheye"

#define MPP_MOD_CHNL      "chnl"
#define MPP_MOD_VENC      "venc"
#define MPP_MOD_GRP       "grp"
#define MPP_MOD_VDA       "vda"
#define MPP_MOD_VPSS      "vpss"
#define MPP_MOD_RGN       "rgn"
#define MPP_MOD_IVE       "ive"
#define MPP_MOD_FD        "fd"
#define MPP_MOD_MD		  "md"

#define MPP_MOD_H264E     "h264e"
#define MPP_MOD_H265E     "h265e"
#define MPP_MOD_JPEGE     "jpege"
#define MPP_MOD_MPEG4E    "mpeg4e"
#define MPP_MOD_VEDU      "vedu"

#define MPP_MOD_VDEC      "vdec"
#define MPP_MOD_H264D     "h264d"
#define MPP_MOD_JPEGD     "jpegd"

#define MPP_MOD_AI        "ai"
#define MPP_MOD_AO        "ao"
#define MPP_MOD_AENC      "aenc"
#define MPP_MOD_ADEC      "adec"
#define MPP_MOD_AIO       "aio"
#define MPP_MOD_ACODEC	  "acodec"

#define MPP_MOD_VB        "vb"
#define MPP_MOD_SYS       "sys"
#define MPP_MOD_CMPI      "cmpi"

#define MPP_MOD_PCIV      "pciv"
#define MPP_MOD_PCIVFMW   "pcivfmw"

#define MPP_MOD_PROC      "proc"
#define MPP_MOD_LOG       "logmpp"
#define MPP_MOD_MST_LOG   "mstlog"

#define MPP_MOD_DCCM      "dccm"
#define MPP_MOD_DCCS      "dccs"

#define MPP_MOD_VCMP      "vcmp"
#define MPP_MOD_FB        "fb"

#define MPP_MOD_RC        "rc"

#define MPP_MOD_VOIE      "voie"

#define MPP_MOD_TDE       "tde"
#define MPP_MOD_ISP       "isp"
#define MPP_MOD_USR       "usr"

/* We just coyp this value of payload type from RTP/RTSP definition */
typedef enum
{
    PT_PCMU          = 0,
    PT_1016          = 1,
    PT_G721          = 2,
    PT_GSM           = 3,
    PT_G723          = 4,
    PT_DVI4_8K       = 5,
    PT_DVI4_16K      = 6,
    PT_LPC           = 7,
    PT_PCMA          = 8,
    PT_G722          = 9,
    PT_S16BE_STEREO  = 10,
    PT_S16BE_MONO    = 11,
    PT_QCELP         = 12,
    PT_CN            = 13,
    PT_MPEGAUDIO     = 14,
    PT_G728          = 15,
    PT_DVI4_3        = 16,
    PT_DVI4_4        = 17,
    PT_G729          = 18,
    PT_G711A         = 19,
    PT_G711U         = 20,
    PT_G726          = 21,
    PT_G729A         = 22,
    PT_LPCM          = 23,
    PT_CelB          = 25,
    PT_JPEG          = 26,
    PT_CUSM          = 27,
    PT_NV            = 28,
    PT_PICW          = 29,
    PT_CPV           = 30,
    PT_H261          = 31,
    PT_MPEGVIDEO     = 32,
    PT_MPEG2TS       = 33,
    PT_H263          = 34,
    PT_SPEG          = 35,
    PT_MPEG2VIDEO    = 36,
    PT_AAC           = 37,
    PT_WMA9STD       = 38,
    PT_HEAAC         = 39,
    PT_PCM_VOICE     = 40,
    PT_PCM_AUDIO     = 41,
    PT_AACLC         = 42,
    PT_MP3           = 43,
    PT_ADPCMA        = 49,
    PT_AEC           = 50,
    PT_X_LD          = 95,
    PT_H264          = 96,
    PT_D_GSM_HR      = 200,
    PT_D_GSM_EFR     = 201,
    PT_D_L8          = 202,
    PT_D_RED         = 203,
    PT_D_VDVI        = 204,
    PT_D_BT656       = 220,
    PT_D_H263_1998   = 221,
    PT_D_MP1S        = 222,
    PT_D_MP2P        = 223,
    PT_D_BMPEG       = 224,
    PT_MP4VIDEO      = 230,
    PT_MP4AUDIO      = 237,
    PT_VC1           = 238,
    PT_JVC_ASF       = 255,
    PT_D_AVI         = 256,
    PT_DIVX3		 = 257,
    PT_AVS			 = 258,
    PT_REAL8		 = 259,
    PT_REAL9		 = 260,
    PT_VP6			 = 261,
    PT_VP6F			 = 262,
    PT_VP6A			 = 263,
    PT_SORENSON	 	 = 264,
    PT_H265          = 265,
    PT_MAX           = 266,
    /* add by hisilicon */
    PT_AMR           = 1001,
    PT_MJPEG         = 1002,
    PT_AMRWB         = 1003,

   /* add by chenxj */
    PT_SVAC			= 10001,
    PT_DIVA			= 10002,
    PT_SECY			= 10003,
    PT_DIVA_MAIN 	= 10004,
    PT_DIVA_SUB 		= 10005,
    PT_SVAC2	 		= 10006,
    PT_BUTT
} PAYLOAD_TYPE_E;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif  /* _VIM_COMMON_H_ */

