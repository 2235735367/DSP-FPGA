#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_User.h"   // DSP2833x Examples Include File


	Uint16    *ExRamStart = (Uint16 *)0x200000;//强制类型转换，将后面的地址转换为Uint16类型的指针
	                                                                        //表示外部接口区域7起始地址为0x200000

	Uint16		read_data(Uint16 Register)
	{
		Uint16	data_read = 0xFFFF;
		data_read = *(ExRamStart + Register);//该寄存器中所存储的数据，因为ExRamStart为起始地址，则
		                                                               //*(ExRamStart + Register)表示Register中的数据
		return data_read;
	}

	void write_data(Uint16 Register,Uint16 data)
	{
		*(ExRamStart + Register) = data;//定义Register中的数据为data
	}


	void init_zone7(void)
	{
		EALLOW;
	    // Make sure the XINTF clock is enabled
		SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;
		EDIS;
		// Configure the GPIO for XINTF with a 16-bit data bus
		// This function is in DSP2833x_Xintf.c
		InitXintf16Gpio();//16位数据宽度

	    // All Zones---------------------------------
	    // Timing for all zones based on XTIMCLK = SYSCLKOUT/2
		EALLOW;
	    XintfRegs.XINTCNF2.bit.XTIMCLK = 1;//二分频系统时钟
	    // Buffer up to 3 writes
	    XintfRegs.XINTCNF2.bit.WRBUFF = 3;//写缓冲寄存器深度
	    // XCLKOUT is enabled
	    XintfRegs.XINTCNF2.bit.CLKOFF = 0;//使能XCLKOUT
	    // XCLKOUT = XTIMCLK
	    XintfRegs.XINTCNF2.bit.CLKMODE = 0;//不分频即XCLKOUT = XTIMCLK

	    // Zone 6------------------------------------
	    // When using ready, ACTIVE must be 1 or greater
	    // Lead must always be 1 or greater
	    // Zone write timing
	    XintfRegs.XTIMING7.bit.XWRLEAD = 1;
	    XintfRegs.XTIMING7.bit.XWRACTIVE = 3;
	    XintfRegs.XTIMING7.bit.XWRTRAIL = 2;
	    // Zone read timing
	    XintfRegs.XTIMING7.bit.XRDLEAD = 1;
	    XintfRegs.XTIMING7.bit.XRDACTIVE = 4;
	    XintfRegs.XTIMING7.bit.XRDTRAIL = 2;//读写的建立时间、有效时间、跟踪时间

	    // do double all Zone read/write lead/active/trail timing
	    XintfRegs.XTIMING7.bit.X2TIMING = 1;//lead等实际值与寄存器设定值比值为2
	    // Zone will not sample XREADY signal
	    XintfRegs.XTIMING7.bit.USEREADY = 0;
	    XintfRegs.XTIMING7.bit.READYMODE = 0;//仅在USEREADY = 1有效

	    // 1,1 = x16 data bus
	    // 0,1 = x32 data bus
	    // other values are reserved
	    XintfRegs.XTIMING7.bit.XSIZE = 3;//16位数据总线
	    EDIS;
	   //Force a pipeline flush to ensure that the write to
	   //the last register configured occurs before returning.
	   asm(" RPT #7 || NOP");//会执行N+1次NOP指令，占用N+1个指令周期
	}

//===========================================================================
// No more.
//===========================================================================

