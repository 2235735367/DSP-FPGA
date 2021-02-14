#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_User.h"   // DSP2833x Examples Include File


	Uint16    *ExRamStart = (Uint16 *)0x200000;//ǿ������ת����������ĵ�ַת��ΪUint16���͵�ָ��
	                                                                        //��ʾ�ⲿ�ӿ�����7��ʼ��ַΪ0x200000

	Uint16		read_data(Uint16 Register)
	{
		Uint16	data_read = 0xFFFF;
		data_read = *(ExRamStart + Register);//�üĴ��������洢�����ݣ���ΪExRamStartΪ��ʼ��ַ����
		                                                               //*(ExRamStart + Register)��ʾRegister�е�����
		return data_read;
	}

	void write_data(Uint16 Register,Uint16 data)
	{
		*(ExRamStart + Register) = data;//����Register�е�����Ϊdata
	}


	void init_zone7(void)
	{
		EALLOW;
	    // Make sure the XINTF clock is enabled
		SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;
		EDIS;
		// Configure the GPIO for XINTF with a 16-bit data bus
		// This function is in DSP2833x_Xintf.c
		InitXintf16Gpio();//16λ���ݿ��

	    // All Zones---------------------------------
	    // Timing for all zones based on XTIMCLK = SYSCLKOUT/2
		EALLOW;
	    XintfRegs.XINTCNF2.bit.XTIMCLK = 1;//����Ƶϵͳʱ��
	    // Buffer up to 3 writes
	    XintfRegs.XINTCNF2.bit.WRBUFF = 3;//д����Ĵ������
	    // XCLKOUT is enabled
	    XintfRegs.XINTCNF2.bit.CLKOFF = 0;//ʹ��XCLKOUT
	    // XCLKOUT = XTIMCLK
	    XintfRegs.XINTCNF2.bit.CLKMODE = 0;//����Ƶ��XCLKOUT = XTIMCLK

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
	    XintfRegs.XTIMING7.bit.XRDTRAIL = 2;//��д�Ľ���ʱ�䡢��Чʱ�䡢����ʱ��

	    // do double all Zone read/write lead/active/trail timing
	    XintfRegs.XTIMING7.bit.X2TIMING = 1;//lead��ʵ��ֵ��Ĵ����趨ֵ��ֵΪ2
	    // Zone will not sample XREADY signal
	    XintfRegs.XTIMING7.bit.USEREADY = 0;
	    XintfRegs.XTIMING7.bit.READYMODE = 0;//����USEREADY = 1��Ч

	    // 1,1 = x16 data bus
	    // 0,1 = x32 data bus
	    // other values are reserved
	    XintfRegs.XTIMING7.bit.XSIZE = 3;//16λ��������
	    EDIS;
	   //Force a pipeline flush to ensure that the write to
	   //the last register configured occurs before returning.
	   asm(" RPT #7 || NOP");//��ִ��N+1��NOPָ�ռ��N+1��ָ������
	}

//===========================================================================
// No more.
//===========================================================================

