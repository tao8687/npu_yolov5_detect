#ifndef _VIM_MARB_SYS_H_
#define _VIM_MARB_SYS_H_

#define BASE_MARB			(unsigned int)(hmarb->vRegBase)

#define MARB_CLSRC                     (BASE_MARB + 0x0u)
#define MARB_CLASS                     (BASE_MARB + 0x4u)
#define MARB_AR_PWM                    (BASE_MARB + 0x8u)
#define MARB_AW_PWM                    (BASE_MARB + 0xcu)
#define MARB_MONCTRL                   (BASE_MARB + 0x10u)
#define MARB_MONTIME                   (BASE_MARB + 0x14u)
#define MARB_SRCPND                    (BASE_MARB + 0x18u)
#define MARB_INTMASK                   (BASE_MARB + 0x1cu)
#define MARB_SETMASK                   (BASE_MARB + 0x20u)
#define MARB_UNMASK                    (BASE_MARB + 0x24u)
#if 0
#define MARB_MP01_RID_CFG              (BASE_MARB + 0x100u)
#define MARB_MP01_RADDR_TX_NUM         (BASE_MARB + 0x110u)
#define MARB_MP01_RDATA_TX_NUM         (BASE_MARB + 0x114u)
#define MARB_MP01_RADDR_ST_CYC         (BASE_MARB + 0x118u)
#define MARB_MP01_RA2LSTRD_LATENCY     (BASE_MARB + 0x11cu)
#define MARB_MP01_WID_CFG              (BASE_MARB + 0x120u)
#define MARB_MP01_WADDR_TX_NUM         (BASE_MARB + 0x130u)
#define MARB_MP01_WDATA_TX_NUM         (BASE_MARB + 0x134u)
#define MARB_MP01_WADDR_ST_CYC         (BASE_MARB + 0x138u)
#define MARB_MP01_WA2BRESP_LATENCY     (BASE_MARB + 0x13cu)
#define MARB_MP02_RID_CFG              (BASE_MARB + 0x200u)
#define MARB_MP02_RADDR_TX_NUM         (BASE_MARB + 0x210u)
#define MARB_MP02_RDATA_TX_NUM         (BASE_MARB + 0x214u)
#define MARB_MP02_RADDR_ST_CYC         (BASE_MARB + 0x218u)
#define MARB_MP02_RA2LSTRD_LATENCY     (BASE_MARB + 0x21cu)
#define MARB_MP02_WID_CFG              (BASE_MARB + 0x220u)
#define MARB_MP02_WADDR_TX_NUM         (BASE_MARB + 0x230u)
#define MARB_MP02_WDATA_TX_NUM         (BASE_MARB + 0x234u)
#define MARB_MP02_WADDR_ST_CYC         (BASE_MARB + 0x238u)
#define MARB_MP02_WA2BRESP_LATENCY     (BASE_MARB + 0x23cu)
#define MARB_MP03_RID_CFG              (BASE_MARB + 0x300u)
#define MARB_MP03_RADDR_TX_NUM         (BASE_MARB + 0x310u)
#define MARB_MP03_RDATA_TX_NUM         (BASE_MARB + 0x314u)
#define MARB_MP03_RADDR_ST_CYC         (BASE_MARB + 0x318u)
#define MARB_MP03_RA2LSTRD_LATENCY     (BASE_MARB + 0x31cu)
#define MARB_MP03_WID_CFG              (BASE_MARB + 0x320u)
#define MARB_MP03_WADDR_TX_NUM         (BASE_MARB + 0x330u)
#define MARB_MP03_WDATA_TX_NUM         (BASE_MARB + 0x334u)
#define MARB_MP03_WADDR_ST_CYC         (BASE_MARB + 0x338u)
#define MARB_MP03_WA2BRESP_LATENCY     (BASE_MARB + 0x33cu)
#define MARB_MP04_RID_CFG              (BASE_MARB + 0x400u)
#define MARB_MP04_RADDR_TX_NUM         (BASE_MARB + 0x410u)
#define MARB_MP04_RDATA_TX_NUM         (BASE_MARB + 0x414u)
#define MARB_MP04_RADDR_ST_CYC         (BASE_MARB + 0x418u)
#define MARB_MP04_RA2LSTRD_LATENCY     (BASE_MARB + 0x41cu)
#define MARB_MP04_WID_CFG              (BASE_MARB + 0x420u)
#define MARB_MP04_WADDR_TX_NUM         (BASE_MARB + 0x430u)
#define MARB_MP04_WDATA_TX_NUM         (BASE_MARB + 0x434u)
#define MARB_MP04_WADDR_ST_CYC         (BASE_MARB + 0x438u)
#define MARB_MP04_WA2BRESP_LATENCY     (BASE_MARB + 0x43cu)
#define MARB_SP02_RID_CFG              (BASE_MARB + 0xc00u)
#define MARB_SP02_RADDR_TX_NUM         (BASE_MARB + 0xc10u)
#define MARB_SP02_RDATA_TX_NUM         (BASE_MARB + 0xc14u)
#define MARB_SP02_RADDR_ST_CYC         (BASE_MARB + 0xc18u)
#define MARB_SP02_RA2LSTRD_LATENCY     (BASE_MARB + 0xc1cu)
#define MARB_SP02_WID_CFG              (BASE_MARB + 0xc20u)
#define MARB_SP02_WADDR_TX_NUM         (BASE_MARB + 0xc30u)
#define MARB_SP02_WDATA_TX_NUM         (BASE_MARB + 0xc34u)
#define MARB_SP02_WADDR_ST_CYC         (BASE_MARB + 0xc38u)
#define MARB_SP02_WA2BRESP_LATENCY     (BASE_MARB + 0xc3cu)
#define MARB_SP02_RARB_VALID_NUM       (BASE_MARB + 0xd00u)
#define MARB_SP02_RARB_C0WIN_NUM       (BASE_MARB + 0xd10u)
#define MARB_SP02_RARB_C1WIN_NUM       (BASE_MARB + 0xd14u)
#define MARB_SP02_RARB_C2WIN_NUM       (BASE_MARB + 0xd18u)
#define MARB_SP02_RARB_C3WIN_NUM       (BASE_MARB + 0xd1cu)
#define MARB_SP02_WARB_VALID_NUM       (BASE_MARB + 0xd20u)
#define MARB_SP02_WARB_C0WIN_NUM       (BASE_MARB + 0xd30u)
#define MARB_SP02_WARB_C1WIN_NUM       (BASE_MARB + 0xd34u)
#define MARB_SP02_WARB_C2WIN_NUM       (BASE_MARB + 0xd38u)
#define MARB_SP02_WARB_C3WIN_NUM       (BASE_MARB + 0xd3cu)
#endif

#ifndef MARB_MODULE_PATH
#define MARB_MODULE_PATH             "/dev/marb"
#endif 

#define VCMARB_IOC_MAGIC  'm'
#define VCMARB_IOCGHWOFFSET      _IOR(VCMARB_IOC_MAGIC,  3, unsigned long *)
#define VCMARB_IOCGHWIOSIZE      _IOR(VCMARB_IOC_MAGIC,  4, unsigned int *)
#define VCMARB_IOCGFREQ          _IOR(VCMARB_IOC_MAGIC,  5, unsigned int *)

#define VIM_HAL_READ_REG(_register_) \
	(*(volatile unsigned int *)(_register_))
#define VIM_HAL_READ_REG32( _register_, _value_ ) \
	((_value_) = *((volatile int *)(_register_)))
#define VIM_HAL_WRITE_REG32( _register_, _value_ ) \
	(*((volatile int *)(_register_)) = (_value_))

unsigned int VIM_HAL_WriteRegBitVal(unsigned int adr, unsigned int sbit, unsigned int ebit, unsigned int val)
{
	unsigned int memVal;
	unsigned int tmp, tmp1;

	if((sbit == 0) && (ebit == 31))
	{
		VIM_HAL_WRITE_REG32(adr, val);
		VIM_HAL_READ_REG32(adr, memVal);
		return memVal;
	}
	
	VIM_HAL_READ_REG32(adr, memVal);
	if (sbit > ebit)
		return memVal;

	tmp1 = (1 << (ebit - sbit + 1)) - 1;
	val = val & tmp1;
	tmp1 <<= sbit;
	tmp =  memVal & (~tmp1);
	tmp |= (val << sbit) & tmp1;

	//if(tmp != memVal)
		VIM_HAL_WRITE_REG32(adr, tmp);

	return memVal;
}

#define VIM_HAL_WRITE_UINT32_BITVAL    VIM_HAL_WriteRegBitVal

#define __MARB_Montor_Period(data)			VIM_HAL_WRITE_UINT32_BITVAL(MARB_MONTIME, 0, 31, (data))
#define __MARB_Request()					VIM_HAL_WRITE_UINT32_BITVAL(MARB_MONCTRL, 0,0, 1)
#define __MARB_RequestDis()					VIM_HAL_WRITE_UINT32_BITVAL(MARB_MONCTRL, 0,0, 0)
#define __MARB_IntSetFunc32En(x )			VIM_HAL_WRITE_UINT32_BITVAL(MARB_MONCTRL, 16,16, (x))
#define __MARB_IntSetFunc32Mod(x )			VIM_HAL_WRITE_UINT32_BITVAL(MARB_MONCTRL, 18,21, (x))
#define __MARB_ClearSrcPending( x )			VIM_HAL_WRITE_REG32( MARB_SRCPND, ( x ))
#define __MARB_CheckSrcPending( x )			VIM_HAL_READ_REG( MARB_SRCPND)
#define __MARB_IntGetMask( x )				VIM_HAL_READ_REG( MARB_INTMASK)
#define __MARB_IntSetMask(x )				VIM_HAL_WRITE_REG32( MARB_SETMASK, ( x ))
#define __MARB_IntUnMask( x )				VIM_HAL_WRITE_REG32( MARB_UNMASK, ( x ))


#endif
