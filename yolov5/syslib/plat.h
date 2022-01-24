#ifndef __VIM_PLAT_H__
#define __VIM_PLAT_H__

#include "vim_type.h"
#include "vim_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define VIML_MMZ_NAME_LEN				32
#define VIML_MMB_NAME_LEN				16

#define ENABLE_MMB_FIX_MAP
struct mmb_info {
	unsigned long phys_addr;	/* phys-memory address */
	unsigned long align;		/* if you need your phys-memory have special align size */
	unsigned long size;		/* length of memory you need, in bytes */
	unsigned int order;

	void *mapped;			/* userspace mapped ptr */

	union {
		struct {
			unsigned long prot  :8;	/* PROT_READ or PROT_WRITE */
			unsigned long flags :12;/* MAP_SHARED or MAP_PRIVATE */

#ifdef  ENABLE_MMB_FIX_MAP
//#ifdef __KERNEL__
			unsigned long reserved :8; /* reserved, do not use */
			unsigned long delayed_free :1;
			unsigned long map_cached :1;
#endif
		};
		unsigned long w32_stuf;
	};

	char mmb_name[VIML_MMB_NAME_LEN];
	char mmz_name[VIML_MMZ_NAME_LEN];
	unsigned long gfp;		/* reserved, do set to 0 */

#ifdef __KERNEL__
	int map_ref;
	int mmb_ref;

	struct vplat_list_head list;
	viml_mmb_t *mmb;
#endif
};

struct dirty_area
{
	unsigned long dirty_phys_start;	/* dirty physical address */
	unsigned long dirty_virt_start;	/* dirty virtual  address, must be coherent with dirty_phys_addr */
	unsigned long dirty_size;
};

#define MASTER_PORT_NUM   8
#define SLAVE_PORT_NUM    1
#define SUB_PORT_MAX_NUM  10
#define PORT_EN_MAX_NUM   2

#define MPORT_ID_LEN   10
#define SPORT_ID_LEN   13

enum func32_t
{
	FUNC32_OFF,
	FUNC32_SEP,
	FUNC32_ADDR,
	FUNC32_DATA,
	FUNC32_ST,
	FUNC32_LA,
	FUNC32_MAX
};

struct port_regs
{
    unsigned int RCFG0; 	//0x00
    unsigned int RREV[3];
    unsigned int RADDR;		//0x10
    unsigned int RDATA;	
    unsigned int RST;	
    unsigned int RLA;	
    unsigned int WCFG0; 	//0x20
    unsigned int WREV[3];
    unsigned int WADDR;		//0x30
    unsigned int WDATA;	
    unsigned int WST;	
    unsigned int WLA;	
    unsigned int RCF1;		//0x40
    unsigned int WCF1; 	
    unsigned int RLA_MAX;
    unsigned int RLA_MIN;
    unsigned int RLA_AVA;	//0x50
    unsigned int WLA_MAX;
    unsigned int WLA_MIN;
    unsigned int WLA_AVA;
    unsigned int RADDR_MAX;	//0x60
    unsigned int RDATA_MAX;
    unsigned int RST_MAX;
    unsigned int RADDR_MIN;
    unsigned int RDATA_MIN;	//0x70
    unsigned int RST_MIN;
    unsigned int WADDR_MAX;
    unsigned int WDATA_MAX;
    unsigned int WST_MAX;	//0x80
    unsigned int WADDR_MIN;
    unsigned int WDATA_MIN;
    unsigned int WST_MIN;
    unsigned int RADDR_AVA; //0x90
    unsigned int RDATA_AVA;
    unsigned int RST_AVA;
    unsigned int WADDR_AVA;
    unsigned int WDATA_AVA; //0xA0
    unsigned int WST_AVA;
};

struct mod_info
{
	char port_name[16];
	char mrid_str[16];
	char mwid_str[16];
	char srid_str[18];
	char swid_str[18];
	unsigned int mrid;
	unsigned int mwid;
	unsigned int srid;
	unsigned int swid;
};

struct port_calc
{
	float rthrough;
	float wthrough;
	float tthrough; //total
    float rburst;
    float wburst;
	long long rla;
	long long wla;
	long long tla;
};

struct port_info
{
    unsigned int port;
	unsigned int is_master;
    unsigned int offset; 
	unsigned int monnr;
    unsigned int grpr[PORT_EN_MAX_NUM];
    unsigned int grpw[PORT_EN_MAX_NUM];
	struct port_calc avg;
	struct port_calc peak;
	struct port_calc disp_peak;
};

typedef struct
{
    int fd_mem;              /* /dev/mem */
    int fd_marb;              /* /dev/marb */
	int fd_memalloc;         /* /dev/pmem */
    unsigned int regBase;
    unsigned int regSize;    
    unsigned int *vRegBase;  
    unsigned int  period;
    unsigned int  func32;
    unsigned int busfreq;  	/* KHz */
    unsigned int ddrfreq;  	/* KHz */
    unsigned int ddrwidth; 
	int (*cb)(void);
	struct mod_info (*mod)[SUB_PORT_MAX_NUM];
	struct port_info mp[MASTER_PORT_NUM];
	struct port_info sp[SLAVE_PORT_NUM];

} hmarb_t;

#define USERDMA_MAX_CH 4
#define MAX_LLI_NUM   16

struct userdma_lli {
    unsigned int src;
    unsigned int dst;
    unsigned int len;
};

struct userdma_user_info {
    unsigned int ch;
    unsigned int listnr;
    struct userdma_lli llis[MAX_LLI_NUM];
};

VIM_S32 VIM_PLAT_OpenMmz( VIM_VOID );
VIM_S32 VIM_PLAT_CloseMmz( VIM_S32 fd);
VIM_S32 VIM_PLAT_AllocMmz( VIM_S32 fd, struct mmb_info *info);
VIM_S32 VIM_PLAT_RemapMmz( VIM_S32 fd, struct mmb_info *info, VIM_S32 cached);
VIM_S32 VIM_PLAT_FreeMmz( VIM_S32 fd, struct mmb_info *info);
VIM_S32 VIM_PLAT_UnremapMmz( VIM_S32 fd, struct mmb_info *info);
VIM_S32 VIM_PLAT_FlushCache( VIM_S32 fd, struct dirty_area *area);
VIM_S32 VIM_PLAT_CleanCache( VIM_S32 fd, struct dirty_area *area);

VIM_S32 VIM_PLAT_OpenMem( VIM_VOID );
VIM_S32 VIM_PLAT_CloseMem( VIM_S32 fd);
VIM_VOID* VIM_PLAT_MapMem( VIM_S32 fd, VIM_U32 paddr, VIM_U32 size);
VIM_S32 VIM_PLAT_UnmapMem(VIM_VOID* vaddr, VIM_U32 size);
VIM_S32 VIM_PLAT_SetReg(VIM_S32 fd, VIM_U32 u32Addr, VIM_U32 u32Value);
VIM_S32 VIM_PLAT_GetReg(VIM_S32 fd, VIM_U32 u32Addr, VIM_U32 *pu32Value);
VIM_S32 VIM_PLAT_OpenDbg( VIM_VOID );
VIM_S32 VIM_PLAT_GetLogLevel(VIM_U32 mod, VIM_U32 level);
VIM_S32 VIM_PLAT_SetLogPrint(VIM_VPRINTF func);
VIM_S32 VIM_PLAT_Print(const char *fmt, ...);

VIM_S32 VIM_PLAT_OpenMod( VIM_VOID );
VIM_S32 VIM_PLAT_CloseMod( VIM_S32 fd);
VIM_S32 VIM_PLAT_InitMod( VIM_S32 fd );
VIM_S32 VIM_PLAT_ExitMod( VIM_S32 fd );

void* VIM_PLAT_OpenMarb(unsigned int period, unsigned int func32, unsigned int busfreq,
				unsigned int ddrfreq, unsigned int ddrwidth);
VIM_S32 VIM_PLAT_StartMarb(const void *inst);
void VIM_PLAT_StopMarb(const void *inst);

VIM_S32 VIM_PLAT_OpenWdt(VIM_VOID);
VIM_S32 VIM_PLAT_CloseWdt(VIM_VOID);
VIM_S32 VIM_PLAT_SetWdtTimeout(VIM_S32 timeout);
VIM_U32 VIM_PLAT_GetWdtStatus(VIM_U32 *status);
VIM_S32 VIM_PLAT_GetWdtTimeout(VIM_S32 *timeout);
VIM_S32 VIM_PLAT_KeepWdtAlive(VIM_VOID);
VIM_S32 VIM_PLAT_Reboot(VIM_S32 sec);
VIM_S32 VIM_PLAT_OpenDMA(VIM_S32 *vc);
VIM_S32 VIM_PLAT_CloseDMA( VIM_S32 fd);
VIM_S32 VIM_PLAT_CopyDMA(VIM_S32 fd, struct userdma_user_info *info);
VIM_S32 VIM_PLAT_PollDMA(VIM_S32 fd, VIM_S32 ms);
VIM_S32 VIM_PLAT_UseDeviceTree(VIM_VOID);

struct msg_st
{
        long int msg_type;
        unsigned int val;
};

#define WDT_MSG_KEY  1234
#define WDT_MSG_TYPE 7
#define WDT_BOOT_TIME 3

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*__VIM_PLAT_H__ */

