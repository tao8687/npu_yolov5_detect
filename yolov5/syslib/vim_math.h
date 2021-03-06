#ifndef __VIM_MATH_H__
#define __VIM_MATH_H__

#include "vim_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/******************************************************************************
** Linear interpolation: x1<=x<=x2
******************************************************************************/
__inline static VIM_S32 LinearInterp(VIM_U32 x1, VIM_U32 x2, VIM_S32 y1, VIM_S32 y2, VIM_U32 x)
{
	VIM_S32 ret;
	ret = (y1*(VIM_S32)(x2-x)+y2*(VIM_S32)(x-x1))/(VIM_S32)(x2-x1);
	return(ret);
}

/******************************************************************************
** ABS(x)                 absolute value of x
** SIGN(x)                sign of x
** CMP(x,y)               0 if x==y; 1 if x>y; -1 if x<y
******************************************************************************/
#define ABS(x)          ( (x) >= 0 ? (x) : (-(x)) )
#define _SIGN(x)         ( (x) >= 0 ? 1 : -1 )
#define CMP(x,y)        (((x) == (y)) ? 0 : (((x) > (y)) ? 1 : -1))

/******************************************************************************
** MAX2(x,y)              maximum of x and y
** MIN2(x,y)              minimum of x and y
** MAX3(x,y,z)            maximum of x, y and z
** MIN3(x,y,z)            minimun of x, y and z
** MEDIAN(x,y,z)          median of x,y,z
** MEAN2(x,y)             mean of x,y
******************************************************************************/
#define MAX2(x,y)       ( (x)>(y) ? (x):(y) )
#define MIN2(x,y)       ( (x)<(y) ? (x):(y) )
#define MAX3(x,y,z)     ( (x)>(y) ? MAX2(x,z) : MAX2(y,z) )
#define MIN3(x,y,z)     ( (x)<(y) ? MIN2(x,z) : MIN2(y,z) )
#define MEDIAN(x,y,z)   (((x)+(y)+(z) - MAX3(x,y,z)) - MIN3(x,y,z) )
#define MEAN2(x,y)      (((x)+(y)) >> 1 )

/******************************************************************************
** CLIP3(x,min,max)       clip x within [min,max]
** WRAP_MAX(x,max,min)    wrap to min if x equal max
** WRAP_MIN(x,min,max)    wrap to max if x equal min
** VALUE_BETWEEN(x,min.max)   True if x is between [min,max] inclusively.
******************************************************************************/
#define CLIP3(x,min,max)         ( (x)< (min) ? (min) : ((x)>(max)?(max):(x)) )
#define CLIP_MAX(x,max)          ((x)>(max)?(max):(x)) 
#define WRAP_MAX(x,max,min)      ( (x)>=(max) ? (min) : (x) )
#define WRAP_MIN(x,min,max)      ( (x)<=(min) ? (max) : (x) )
#define VALUE_BETWEEN(x,min,max) (((x)>=(min)) && ((x) <= (max)))

/******************************************************************************
** MULTI_OF_2_POWER(x,a)  whether x is multiple of a(a must be power of 2)
** CEILING_2_POWER(x,a)   ceiling x to multiple of a(a must be power of 2)
** FLOOR_2_POWER(x,a)     floor x to multiple of a(a must be power of 2)
** HIALIGN(x, a)            align x to multiple of a
**
** Example:
** CEILING_2_POWER(5,4) = 8
** FLOOR_2_POWER(5,4)   = 4
******************************************************************************/
#define MULTI_OF_2_POWER(x,a)    (!((x) & ((a) - 1) ) )
#define CEILING_2_POWER(x,a)     ( ((x) + ((a) - 1) ) & ( ~((a) - 1) ) )
#define FLOOR_2_POWER(x,a)       (  (x) & (~((a) - 1) ) )
#define HIALIGN(x, a)              ((a) * (((x) + (a) - 1) / (a)))
#define HICEILING(x, a)           (((x)+(a)-1)/(a))

/******************************************************************************
** Get the span between two unsinged number, such as
** SPAN(VIM_U32, 100, 200) is 200 - 100 = 100
** SPAN(VIM_U32, 200, 100) is 0xFFFFFFFF - 200 + 100
** SPAN(VIM_U64, 200, 100) is 0xFFFFFFFFFFFFFFFF - 200 + 100
******************************************************************************/
#define SPAN(type, begin, end)\
({                            \
   type b = (begin);          \
   type e = (end);            \
   (type)((b >= e) ? (b - e) : (b + ((~((type)0))-e))); \
})

/******************************************************************************
** ENDIAN32(x,y)              little endian <---> big endian
** IS_LITTLE_END()            whether the system is little end mode
******************************************************************************/
#define  ENDIAN32( x )						\
	(   ( (x) << 24 ) |						\
		( ( (x) & 0x0000ff00 ) << 8 ) |		\
		( ( (x) & 0x00ff0000 ) >> 8 ) |		\
		( ( (x) >> 24 ) & 0x000000ff )  )

__inline static VIM_BOOL IS_LITTLE_END(void)
{
    union unEND_TEST_U
    {
        VIM_CHAR cTest[4];
        VIM_U32  u32Test;
    } unEndTest;

    unEndTest.cTest[0] = 0x01;
    unEndTest.cTest[1] = 0x02;
    unEndTest.cTest[2] = 0x03;
    unEndTest.cTest[3] = 0x04;
    
    return (unEndTest.u32Test > 0x01020304) ? (VIM_TRUE) : (VIM_FALSE);
}


/******************************************************************************
** FRACTION32(de,nu)          fraction: nu(minator) / de(nominator).
** NUMERATOR32(x)              of x(x is fraction)
** DENOMINATOR32(x)           Denominator of x(x is fraction)

** represent fraction in 32 bit. LSB 16 is numerator, MSB 16 is denominator
** It is integer if denominator is 0.
******************************************************************************/
#define FRACTION32(de,nu)       ( ((de) << 16) | (nu) ) 
#define NUMERATOR32(x)          ( (x) & 0xffff)
#define DENOMINATOR32(x)        ( (x) >> 16 )  

/******************************************************************************
** RGB(r,g,b)    assemble the r,g,b to 24bit color
** RGB_R(c)      get RED   from 24bit color
** RGB_G(c)      get GREEN from 24bit color
** RGB_B(c)      get BLUE  from 24bit color
******************************************************************************/
#define RGB(r,g,b) ((((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff))
#define RGB_R(c)   ( ((c) & 0xff0000) >> 16)
#define RGB_G(c)   ( ((c) & 0xff00) >> 8)
#define RGB_B(c)   (  (c) & 0xff)

/******************************************************************************
** YUV(y,u,v)    assemble the y,u,v to 24bit color
** YUV_Y(c)      get Y from 24bit color
** YUV_U(c)      get U from 24bit color
** YUV_V(c)      get V from 24bit color
******************************************************************************/
#define YUV(y,u,v) ((((y) & 0xff) << 16) | (((u) & 0xff) << 8) | ((v) & 0xff))
#define YUV_Y(c)   ( ((c) & 0xff0000) >> 16)
#define YUV_U(c)   ( ((c) & 0xff00) >> 8)
#define YUV_V(c)   (  (c) & 0xff)

/******************************************************************************
** Rgb2Yc(r, g, b, *y, *u, *u)    convert r,g,b to y,u,v
** Rgb2Yuv(rgb, *yuv)             convert rgb to yuv
******************************************************************************/
__inline static VIM_VOID Rgb2Yc(VIM_U8 r, VIM_U8 g, VIM_U8 b, VIM_U8 * py, VIM_U8 * pcb, VIM_U8 * pcr)
{
    /* Y */
    *py = (VIM_U8)(((r*66+g*129+b*25) >> 8) + 16);

    /* Cb */
    *pcb = (VIM_U8)((((b*112-r*38)-g*74) >> 8) + 128);

    /* Cr */
    *pcr = (VIM_U8)((((r*112-g*94)-b*18) >> 8) + 128);
}

__inline static VIM_U32 Rgb2Yuv(VIM_U32 u32Rgb)
{
    VIM_U8 y,u,v;

    Rgb2Yc(RGB_R(u32Rgb), RGB_G(u32Rgb), RGB_B(u32Rgb), &y, &u, &v);

    return YUV(y,u,v);
}

/******************************************************************************
** GetYCFromRGB(rgb, *y, *cbcr)    convert rgb to yyyy, uvuv, 
******************************************************************************/
__inline static VIM_VOID GetYCFromRGB(VIM_U32 rgb, VIM_U32 * pY, VIM_U32 * pC)
{
    VIM_U8 y, cb, cr;
    VIM_U32 color_y, color_c, tmp;

    Rgb2Yc(RGB_R(rgb), RGB_G(rgb), RGB_B(rgb), &y, &cb, &cr);

    tmp = y & 0xFF;
    color_y = (tmp<<24) + (tmp<<16) + (tmp<<8) + tmp;

    tmp = cb & 0xFF;
    color_c = (tmp<<24) + (tmp<<8);
    
    tmp = cr & 0xFF;
    color_c = color_c + (tmp<<16) + tmp;

    *pY = color_y;
    *pC = color_c;
}

/*******************************************************************************
** FpsControl Useing Sample:
**  FPS_CTRL_S g_stFpsCtrl;
**
**  Take 12 frame uniform in 25.
**  InitFps(&g_stFpsCtrl, 25, 12);
**
**  {
**       if(FpsControl(&g_stFpsCtrl)) printf("Yes, this frmae should be token");
**  }
**
*******************************************************************************/
typedef struct vimFPS_CTRL_S
{
    VIM_U32 u32Ffps;    /* Full frame rate    */
    VIM_U32 u32Tfps;    /* Target frame rate  */
    VIM_U32 u32FrmKey;  /* update key frame   */
} FPS_CTRL_S;

__inline static VIM_VOID InitFps(FPS_CTRL_S *pFrmCtrl, VIM_U32 u32FullFps,
                                VIM_U32 u32TagFps)
{
    pFrmCtrl->u32Ffps   = u32FullFps;
    pFrmCtrl->u32Tfps   = u32TagFps;
    pFrmCtrl->u32FrmKey = 0;
}

__inline static VIM_BOOL FpsControl(FPS_CTRL_S *pFrmCtrl)
{
    VIM_BOOL   bReturn       = VIM_FALSE;

    pFrmCtrl->u32FrmKey += pFrmCtrl->u32Tfps;
    if (pFrmCtrl->u32FrmKey >= pFrmCtrl->u32Ffps)
    {
        pFrmCtrl->u32FrmKey -= pFrmCtrl->u32Ffps;
        bReturn = VIM_TRUE;
    }
    
    return bReturn;
}


#ifdef __HuaweiLite__

#define hi_usleep(usec) \
do { \
	usleep(usec); \
} while (0)

#include <stdio.h>
#include <stdarg.h>

/* define the max length of the string */
#define SECUREC_STRING_MAX_LEN (0x7fffffffUL)

/*******************************************************************************
 * <NAME>
 *    snprintf_s
 *
 * <SYNOPSIS>
 *    __inline static VIM_S32 snprintf_s(VIM_CHAR* strDest, VIM_U32 destMax, VIM_U32 count, const VIM_CHAR* format, ...);
 *
 * <FUNCTION DESCRIPTION>
 *    The snprintf_s function formats and stores count or fewer characters in 
 *    strDest and appends a terminating null. Each argument (if any) is converted
 *    and output according to the corresponding format specification in format.
 *    The formatting is consistent with the printf family of functions; If copying
 *    occurs between strings that overlap, the behavior is undefined.
 *
 * <INPUT PARAMETERS>
 *    strDest                 Storage location for the output.
 *    destMax                 The size of the storage location for output. Size 
 *                            in bytes for snprintf_s.
 *    count                   Maximum number of character to store.
 *    format                  Format-control string.
 *
 * <OUTPUT PARAMETERS>
 *    strDest                 is updated
 *
 * <RETURN VALUE>
 *    snprintf_s returns the number of characters stored in strDest, not counting
 *    the terminating null character.
 *    If the storage required to store the data and a terminating null exceeds 
 *    destMax, format will be truncated as the first (destMax-1) characters and a terminating null. return (destMax-1).
 *    If strDest or format is a NULL pointer, or if destMax  is equal
 *    to zero or greater than SECUREC_STRING_MAX_LEN, or if count is greater than (SECUREC_STRING_MAX_LEN - 1), the function return -1.
 *******************************************************************************
*/

__inline static VIM_S32 snprintf_s (VIM_CHAR* strDest, VIM_U32 destMax, VIM_U32 count, const VIM_CHAR* format, ...)
{
	va_list args;
	VIM_S32 s32Ret;
	
	if (format == NULL || strDest == NULL || destMax == 0 || destMax > SECUREC_STRING_MAX_LEN || count > (SECUREC_STRING_MAX_LEN - 1))
    {
        if (strDest != NULL && destMax > 0)
        {
            strDest[0] = '\0';
        }
        return -1;
    }

	
	va_start(args, format);

    if (destMax > count)
    {
        s32Ret = vsnprintf(strDest, count + 1, format, args);
		s32Ret = ((s32Ret < 0) || (s32Ret < count)) ? s32Ret : count;
    }
    else /* destMax <= count */
    {
        s32Ret = vsnprintf(strDest, destMax, format, args);
		s32Ret = ((s32Ret < 0) || (s32Ret < destMax-1)) ? s32Ret : destMax-1;
	}
	
	va_end(args);

	return s32Ret;
}

#else

#define hi_usleep(usec) \
do { \
	struct timespec req; \
	req.tv_sec 	= (usec) / 1000000; \
	req.tv_nsec = ((usec) % 1000000) * 1000; \
	nanosleep (&req, NULL); \
} while (0)

#ifndef __KERNEL__
#include <stdio.h>
#include <stdarg.h>

/* define the max length of the string */
#define SECUREC_STRING_MAX_LEN (0x7fffffffUL)

/*******************************************************************************
 * <NAME>
 *    snprintf_s
 *
 * <SYNOPSIS>
 *    __inline static VIM_S32 snprintf_s(VIM_CHAR* strDest, VIM_U32 destMax, VIM_U32 count, const VIM_CHAR* format, ...);
 *
 * <FUNCTION DESCRIPTION>
 *    The snprintf_s function formats and stores count or fewer characters in 
 *    strDest and appends a terminating null. Each argument (if any) is converted
 *    and output according to the corresponding format specification in format.
 *    The formatting is consistent with the printf family of functions; If copying
 *    occurs between strings that overlap, the behavior is undefined.
 *
 * <INPUT PARAMETERS>
 *    strDest                 Storage location for the output.
 *    destMax                 The size of the storage location for output. Size 
 *                            in bytes for snprintf_s.
 *    count                   Maximum number of character to store.
 *    format                  Format-control string.
 *
 * <OUTPUT PARAMETERS>
 *    strDest                 is updated
 *
 * <RETURN VALUE>
 *    snprintf_s returns the number of characters stored in strDest, not counting
 *    the terminating null character.
 *    If the storage required to store the data and a terminating null exceeds 
 *    destMax, format will be truncated as the first (destMax-1) characters and a terminating null. return (destMax-1).
 *    If strDest or format is a NULL pointer, or if destMax  is equal
 *    to zero or greater than SECUREC_STRING_MAX_LEN, or if count is greater than (SECUREC_STRING_MAX_LEN - 1), the function return -1.
 *******************************************************************************
*/

__inline static VIM_S32 snprintf_s (VIM_CHAR* strDest, VIM_U32 destMax, VIM_U32 count, const VIM_CHAR* format, ...)
{
	va_list args;
	VIM_S32 s32Ret;
	
	if (format == NULL || strDest == NULL || destMax == 0 || destMax > SECUREC_STRING_MAX_LEN || count > (SECUREC_STRING_MAX_LEN - 1))
    {
        if (strDest != NULL && destMax > 0)
        {
            strDest[0] = '\0';
        }
        return -1;
    }

	
	va_start(args, format);

    if (destMax > count)
    {
        s32Ret = vsnprintf(strDest, count + 1, format, args);
		s32Ret = ((s32Ret < 0) || ((VIM_U32)s32Ret < count)) ? s32Ret : (VIM_S32)count;
    }
    else /* destMax <= count */
    {
        s32Ret = vsnprintf(strDest, destMax, format, args);
		s32Ret = ((s32Ret < 0) || ((VIM_U32)s32Ret < destMax-1)) ? s32Ret : (VIM_S32)(destMax-1);
	}
	
	va_end(args);

	return s32Ret;
}

#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VIM_MATH_H__ */

