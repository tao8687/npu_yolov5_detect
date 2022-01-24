#ifndef _REGION_EXT_H_
#define _REGION_EXT_H_


#ifdef __cplusplus
extern "C" {
#endif

#define EFUSE_BASE		0x6005A000
/************************************************************************
*
*	Register EFUSE
*
************************************************************************/
#define	EFUSE_STATUS            		(EFUSE_BASE+0x00)
#define	EFUSE_CTRL               		(EFUSE_BASE+0x04)
#define	EFUSE_REQ              			(EFUSE_BASE+0x08)
#define	EFUSE_ADDR              		(EFUSE_BASE+0x0c)
#define	EFUSE_DATA_0            		(EFUSE_BASE+0x10)
#define	EFUSE_DATA_1            		(EFUSE_BASE+0x14)
#define	EFUSE_LOAD_ERR          		(EFUSE_BASE+0x18)
#define	EFUSE_PS_WIDTH          		(EFUSE_BASE+0x1c)
#define	EFUSE_STANDBY_WIDTH     	(EFUSE_BASE+0x20)
#define	EFUSE_PGM_WIDTH        		(EFUSE_BASE+0x24)
#define	EFUSE_READ_WIDTH       		(EFUSE_BASE+0x28)
#define	EFUSE_SRCPND            		(EFUSE_BASE+0x2c)
#define	EFUSE_INTMASK           		(EFUSE_BASE+0x30)
#define	EFUSE_INTSETMASK        		(EFUSE_BASE+0x34)
#define	EFUSE_INTUNMASK         		(EFUSE_BASE+0x38)
#define	EFUSE_ERR_RFH          		(EFUSE_BASE+0x3c)
#define	EFUSE_KEY_PROTECT_READ  	(EFUSE_BASE+0x40)
#define	EFUSE_KEY_PROTECT_WRITE	(EFUSE_BASE+0x44)
#define	EFUSE_RIR_FLAG			(EFUSE_BASE+0x48)

static VIM_U32 SYS_EFUSE_StatusCheck(VIM_U32 timeout);
static VIM_U32 SYS_EFUSE_SetEnable(VIM_U32 enable);
VIM_S32 VIM_MPI_EFUSE_Read(VIM_U32 read_addr);
VIM_S32 VIM_MPI_SYS_EfuseWrite(VIM_U32 write_addr,VIM_U32 value , VIM_U32 width, VIM_U32 timeout_ms);


#ifdef __cplusplus
}
#endif
#endif

