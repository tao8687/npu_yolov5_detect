#ifndef __VIM_TYPE_H__
#define __VIM_TYPE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdarg.h>

/*----------------------------------------------*
 * The common data type, will be used in the whole project.*
 *----------------------------------------------*/

typedef unsigned char           VIM_U8;
typedef unsigned short          VIM_U16;
typedef unsigned int            VIM_U32;

typedef signed char             VIM_S8;
typedef short                   VIM_S16;
typedef int                     VIM_S32;

typedef float                   VIM_F32;

/*float*/
typedef float                   VIM_FLOAT;
/*double*/
typedef double                  VIM_DOUBLE;


typedef unsigned long long      VIM_U64;
typedef long long               VIM_S64;

typedef char                    VIM_CHAR;
#define VIM_VOID                 void

/*----------------------------------------------*
 * const defination                             *
 *----------------------------------------------*/
typedef enum {
    VIM_FALSE = 0,
    VIM_TRUE  = 1,
} VIM_BOOL;
#ifndef __KERNEL__

typedef enum {
  VIM_BIT0 = 0x1,
  VIM_BIT1= 0x2,
	VIM_BIT2=0x4,
	VIM_BIT3=0x8,
	VIM_BIT4=0x10,
	VIM_BIT5=0x20,
	VIM_BIT6=0x40,
	VIM_BIT7=0x80,
	VIM_BIT8=0x100,
	VIM_BIT9=0x200,
	VIM_BIT10=0x400,
	VIM_BIT11=0x800,
	VIM_BIT12=0x1000,
	VIM_BIT13=0x2000,
	VIM_BIT14=0x4000,
	VIM_BIT15=0x8000,
	VIM_BIT16=0x10000,
	VIM_BIT17=0x20000,
	VIM_BIT18=0x40000,
	VIM_BIT19=0x80000,
	VIM_BIT20=0x100000,
	VIM_BIT21=0x200000,
	VIM_BIT22=0x400000,
	VIM_BIT23=0x800000,
	VIM_BIT24=0x1000000,
	VIM_BIT25=0x2000000,
	VIM_BIT26=0x4000000,
	VIM_BIT27=0x8000000,
	VIM_BIT28=0x10000000,
	VIM_BIT29=0x20000000,
	VIM_BIT30=0x40000000,
	VIM_BIT31=0x80000000,
	VIM_ALLBIT32=0xffffffff,
	VIM_ALLBIT16=0xffff,
	VIM_ALLBIT8=0xff
} VIM_BIT_DEFINE;
#endif
#ifndef NULL
    #define NULL    0L
#endif

#ifndef VIM_NULL
    #define VIM_NULL NULL
#endif

#define VIM_SUCCESS  0
#define VIM_FAILURE  (-1)

typedef void (*VIM_VPRINTF)(const char* format, va_list args_list);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __VIM_TYPE_H__ */

