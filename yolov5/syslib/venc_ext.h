#ifndef _VENC_EXT_H_
#define _VENC_EXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vim_comm_venc.h"

VIM_S32 VENC_Bind(VENC_CHN VeChn, VENC_CHN ViChn);
VIM_S32 VENC_Unbind(VENC_CHN VeChn);

//VIM_VOID VENC_Register_Callback(VIM_U32 channel,VENC_callback *call_back,void *data);
//VIM_VOID VENC_Unregister_Callback(VIM_U32 channel);

VIM_S32 VENC_Get_PicFmt(VENC_CHN VeChn,PICFMT_S *Picfmt);

#ifdef __cplusplus
}
#endif
#endif

