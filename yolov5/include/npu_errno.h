/******************************************************************************
  Copyright (C), 1999-2014, Vimicro Tech. Co., Ltd.
******************************************************************************
  File Name     : vim_errno.h
  Version       : Initial Draft
  Author        : Vimicro ICP team
  Created       : 2013/9/10
  Description   : define the format of error code
  History       :
  1.Date        : 
    Author      : 
    Modification: 
******************************************************************************/


#ifndef __VIM_ERRNO_H__
#define __VIM_ERRNO_H__




#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */


/* 1010 0000b
 * VTOP use APPID from 0~31
 * so  use APPID based on 32
 */
#define VIM_ERR_APPID_NPU  (0x80000000L + 0x20000000L)

typedef enum vimNPUERR_LEVEL_E
{
    EN_ERR_LEVEL_DEBUG = 0,  /* debug-level                                  */
    EN_ERR_LEVEL_INFO,       /* informational                                */
    EN_ERR_LEVEL_NOTICE,     /* normal but significant condition             */
    EN_ERR_LEVEL_WARNING,    /* warning conditions                           */
    EN_ERR_LEVEL_ERROR,      /* error conditions                             */
    EN_ERR_LEVEL_CRIT,       /* critical conditions                          */
    EN_ERR_LEVEL_ALERT,      /* action must be taken immediately             */
    EN_ERR_LEVEL_FATAL,      /* just for compatibility with previous version */
    EN_ERR_LEVEL_BUTT
}NPUERR_LEVEL_E;


/******************************************************************************
|----------------------------------------------------------------|
| 1 |   APP_ID   |   MOD_ID    | ERR_LEVEL |   ERR_ID            |
|----------------------------------------------------------------|
|<--><--7bits----><----8bits---><--3bits---><------13bits------->|
******************************************************************************/

#define VIM_NPUDEF_ERR( module, level, errid) \
    ((VIM_S32)( (VIM_ERR_APPID_NPU) | ((module) << 16 ) | ((level)<<13) | (errid) ))

/* NOTE! the following defined all common error code,
 * all module must reserved 0~63 for their common error code */
typedef enum vimEN_NPUERR_CODE_E
{
    EN_ERR_INVALID_DEVID = 1, /* invlalid device ID */
    EN_ERR_INVALID_CHNID = 2, /* invlalid channel ID */
    EN_ERR_ILLEGAL_PARAM = 3, /* at lease one parameter is illagal
                           * eg, an illegal enumeration value  */
    EN_ERR_EXIST = 4,         /* resource exists */
    EN_ERR_UNEXIST = 5,       /* resource unexists */

    EN_ERR_NULL_PTR = 6,      /* using a NULL point */

    EN_ERR_NOT_CONFIG = 7,    /* try to enable or initialize system,
                             device or channel, before configing attribute */
    EN_ERR_NOT_SUPPORT = 8,  /* operation or type is not supported by NOW */
    EN_ERR_NOT_PERM = 9,      /* operation is not permitted
                           * eg, try to change static attribute */

    EN_ERR_NOMEM = 12 ,         /* failure caused by malloc memory */
    EN_ERR_NOBUF = 13,         /* failure caused by malloc buffer */

    EN_ERR_BUF_EMPTY = 14,     /* no data in buffer */
    EN_ERR_BUF_FULL = 15,      /* no buffer for new data */

    /* System is not ready,maybe not initialed or loaded.
     * Returning the error code when opening a device file failed.
     */
    EN_ERR_SYS_NOTREADY = 16,

    EN_ERR_BADADDR = 17,       /* bad address, eg. used for copy_from_user & copy_to_user */

    EN_ERR_BUSY = 18,          /* resource is busy, eg. destroy a venc chn without unregistering it */

    EN_ERR_REMAP = 19, 
    EN_ERR_UNBIND = 20, 

    EN_ERR_TIMEOUT = 21,
    EN_ERR_HW_ERROR = 22,
    
    EN_ERR_BUTT = 63,     /* maxium code, private error code of all modules must be greater than it */
}EN_NPUERR_CODE_E;


/* following is an example for defining error code of MD module
 *
 * #define VIM_ERR_MD_INVALID_CHNID VIM_DEF_ERR(VIM_ID_MD, EN_ERR_LEVEL_ERROR, EN_ERR_INVALID_CHNID)
 *
 */
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __VIM_ERRNO_H__ */

