#ifndef __VIM_COMM_SYS_H__
#define __VIM_COMM_SYS_H__

#include <string.h>
#include "vim_type.h"
#include "vim_errno.h"
#include "vim_debug.h"
#include <vim_list.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define VIM_TRACE_SYS(level, fmt...) VIM_TRACE(level, VIM_ID_SYS,##fmt)
typedef struct vimMPP_SYS_CONF_S
{
    /* stride of picture buffer must be aligned with this value.
     * you can choose a value from 1 to 1024, and it must be multiple of 16.
     */
    VIM_U32 u32AlignWidth;

} MPP_SYS_CONF_S;

typedef struct vimSYS_VIRMEM_INFO_S
{
    VIM_U32  u32PhyAddr;
    VIM_BOOL bCached;
} SYS_VIRMEM_INFO_S;

typedef enum vimSCALE_RANGE_E
{
    SCALE_RANGE_0 = 0,      /* scale range <  1/4 */
    SCALE_RANGE_1,          /* scale range >= 1/4 */
    SCALE_RANGE_2,          /* scale range >= 1/3 */
    SCALE_RANGE_3,          /* scale range >= 1/2 */
    SCALE_RANGE_4,          /* scale range >= 3/4 */
    SCALE_RANGE_5,          /* scale range == 1/1 */
    SCALE_RANGE_6,          /* scale range >  1   */
    SCALE_RANGE_BUTT,
} SCALE_RANGE_E;

typedef enum vimCOEFF_LEVEL_E
{
    COEFF_LEVEL_0 = 0,      /* coefficient level 0 */
    COEFF_LEVEL_1,          /* coefficient level 1 */
    COEFF_LEVEL_2,          /* coefficient level 2 */
    COEFF_LEVEL_3,          /* coefficient level 3 */
    COEFF_LEVEL_4,          /* coefficient level 4 */
    COEFF_LEVEL_5,          /* coefficient level 5 */
    COEFF_LEVEL_6,          /* coefficient level 6 */
    COEFF_LEVEL_BUTT,
} COEFF_LEVEL_E;

typedef struct vimSCALE_COEFF_LEVEL_S
{
    COEFF_LEVEL_E enHorLum; /* horizontal luminance   coefficient level */    
    COEFF_LEVEL_E enHorChr; /* horizontal chrominance coefficient level */    
    COEFF_LEVEL_E enVerLum; /* vertical   luminance   coefficient level */    
    COEFF_LEVEL_E enVerChr; /* vertical   chrominance coefficient level */    
} SCALE_COEFF_LEVEL_S;

typedef struct vimSCALE_RANGE_S
{
    SCALE_RANGE_E enHorizontal;
    SCALE_RANGE_E enVertical;   
} SCALE_RANGE_S;

typedef struct vimSCALE_COEFF_INFO_S
{
    SCALE_RANGE_S stScaleRange;
    SCALE_COEFF_LEVEL_S stScaleCoeffLevel;   
} SCALE_COEFF_INFO_S;

typedef struct vimGPS_INFO_S
{
    VIM_CHAR  chGPSLatitudeRef;         /* GPS LatitudeRef Indicates whether the latitude is north or south latitude, 
                                    * 'N'/'S', default 'N' */
    VIM_U32   au32GPSLatitude[3][2];    /* GPS Latitude is expressed as degrees, minutes and seconds,a typical format like "dd/1,mm/1,ss/1", 
                                    *  default 0/0, 0/0, 0/0 */ 
    VIM_CHAR  chGPSLongitudeRef;        /* GPS LongitudeRef Indicates whether the longitude is east or west longitude, 
                                    * 'E'/'W', default 'E' */
    VIM_U32   au32GPSLongitude[3][2];   /* GPS Longitude is expressed as degrees, minutes and seconds,a typical format like "dd/1,mm/1,ss/1", 
                                    *  default 0/0, 0/0, 0/0 */ 
	VIM_U8    u8GPSAltitudeRef;         /* GPS AltitudeRef Indicates the reference altitude used, 0 - above sea level, 1 - below sea level
                                    * default 0 */
    VIM_U32   au32GPSAltitude[2];       /* GPS AltitudeRef Indicates the altitude based on the reference u8GPSAltitudeRef, the reference unit is meters,
                                    * default 0/0 */
} GPS_INFO_S;
struct SysBindNode
{
	MPP_CHN_S SrcChn;
	MPP_CHN_S DestChn;

	struct vim_list_head list;
};


#define VIM_ERR_SYS_NULL_PTR         VIM_DEF_ERR(VIM_ID_SYS, EN_ERR_LEVEL_ERROR, EN_ERR_NULL_PTR)
#define VIM_ERR_SYS_NOTREADY         VIM_DEF_ERR(VIM_ID_SYS, EN_ERR_LEVEL_ERROR, EN_ERR_SYS_NOTREADY)
#define VIM_ERR_SYS_NOT_PERM         VIM_DEF_ERR(VIM_ID_SYS, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_PERM)
#define VIM_ERR_SYS_NOMEM            VIM_DEF_ERR(VIM_ID_SYS, EN_ERR_LEVEL_ERROR, EN_ERR_NOMEM)
#define VIM_ERR_SYS_ILLEGAL_PARAM    VIM_DEF_ERR(VIM_ID_SYS, EN_ERR_LEVEL_ERROR, EN_ERR_ILLEGAL_PARAM)
#define VIM_ERR_SYS_BUSY             VIM_DEF_ERR(VIM_ID_SYS, EN_ERR_LEVEL_ERROR, EN_ERR_BUSY)
#define VIM_ERR_SYS_NOT_SUPPORT      VIM_DEF_ERR(VIM_ID_SYS, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_SUPPORT)

////BIND
#define VIM_ERR_SYS_NOBIND      VIM_DEF_ERR(VIM_ID_SYS, EN_ERR_LEVEL_ERROR, 21)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __VIM_COMM_SYS_H__ */

