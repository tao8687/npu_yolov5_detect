#ifndef __VIM_DEBUG_H__
#define __VIM_DEBUG_H__

#ifndef __KERNEL__
#include <stdio.h>
#include <stdarg.h>
#endif

#include "vim_type.h"
#include "vim_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



#define _EX__FILE_LINE(fxx,lxx) "[File]:"fxx"\n[Line]:"#lxx"\n[Info]:"
#define EX__FILE_LINE(fxx,lxx) _EX__FILE_LINE(fxx,lxx)
#define __FILE_LINE__ EX__FILE_LINE(__FILE__, __LINE__)

//#define USE_DYNAMIC_PRINT   1

#define VIM_MOD_NAME_MAX_LEN		16
#define VIM_DBG_EMERG      0   /* system is unusable                   */
#define VIM_DBG_ALERT      1   /* action must be taken immediately     */
#define VIM_DBG_CRIT       2   /* critical conditions                  */
#define VIM_DBG_ERR        3   /* error conditions                     */
#define VIM_DBG_WARN       4   /* warning conditions                   */
#define VIM_DBG_NOTICE     5   /* normal but significant condition     */
#define VIM_DBG_INFO       6   /* informational                        */
#define VIM_DBG_DEBUG      7   /* debug-level messages                 */

/********************************************************************************
for user define
*******************************************************************************/

#define VIM_DEBUG_LEVEL VIM_DBG_DEBUG      //angela added for debug level
//extern volatile VIM_U32 * VIM_DEBUG_MODULE;
//#define LOGCAT_PRINT
//#define VIM_DEBUG_MODULE = VIM_ID_SYS|VIM_ID_VIU      //angela added for debug level

/*****************************************************
end
******************************************************/


typedef struct vimLOG_LEVEL_CONF_S
{
    MOD_ID_E  enModId;
    VIM_S32    s32Level;
    VIM_CHAR   cModName[VIM_MOD_NAME_MAX_LEN];
} LOG_LEVEL_CONF_S;

/******************************************************************************
** For User Mode : VIM_PRINT, VIM_ASSERT, VIM_TRACE
******************************************************************************/
#ifndef LOGCAT_PRINT
VIM_S32 VIM_PLAT_GetLogLevel(VIM_U32 mod, VIM_U32 level);
VIM_S32 VIM_PLAT_Print(const char *fmt, ...);
#define VIM_PRINT(...) VIM_PLAT_Print(__VA_ARGS__)

#else
#define VIM_PRINT
#endif

/* #ifdef VIM_DEBUG */
#if 1
    /* Using samples:   VIM_ASSERT(x>y); */
    #define VIM_ASSERT(expr)               \
    do{                                   \
        if (!(expr)) {                    \
            VIM_PRINT("\nASSERT failed at:\n"\
                   "  >File name: %s\n"   \
                   "  >Function : %s\n"   \
                   "  >Line No. : %d\n"   \
                   "  >Condition: %s\n",  \
                    __FILE__,__FUNCTION__, __LINE__, #expr);\
            _exit(-1);\
        } \
    }while(0)

    /* Using samples:
    ** VIM_TRACE(VIM_DBG_DEBUG, VIM_ID_SYS, "Test %d, %s\n", 12, "Test");
    **/
#define VIM_TRACE(level, enModId, fmt...) \
	if(0 != VIM_PLAT_GetLogLevel(enModId,level))\
	{\
		VIM_PRINT("\r\n\x1b[1;41;37m");\
		VIM_PRINT("[LIB]\x1b[0m\t");\
              VIM_PRINT(fmt);             \
	}
#else
    #define VIM_ASSERT(expr)
    #define VIM_TRACE(level, enModId, fmt...)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __VIM_DEBUG_H__ */

