#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_User.h"   // DSP2833x Examples Include File
#include "PI_FUNC.h"
#include "stdio.h"
#include<string.h>
#include<math.h>
//#include <std.h>
//#include <log.h>
//#include "position_loopcfg.h"
/****************Global variables and structure definitions*****************/
	POSSPEED qep_posspeed = POSSPEED_DEFAULTS;
	Encoder_DATA data_encoder = ENCODER_DEFAULTS;
	PI_FUNC POSITION_LOOP=PI_FUNC_DEFAULTS;
	PI_FUNC SPEED_LOOP=PI_FUNC_DEFAULTS;

    int run = 0;
    int begin= 0;
    double position_set=25000;
    double position_actual=0;
	float PositionKp = 200.0;
	float PositionKi = 0.1;
	float PositionKd = 0;
	
    float speed_set = 10000.0;        // target speed
    float speed_actual  = 0;  // actual speed
    //float SPEEDKp = 2;
    //float SPEEDKi = 0.1;
    //float SPEEDTd = 0;
	float SPEEDKp = 2;
	float SPEEDKi = 0.0001;
	float SPEEDTd = 0.0005;
	float SPEEDLimit = 11000;

	int i=0;
	
    //#pragma DATA_SECTION(array,"arrayFFF")
	 float array[1000];
	 //float tarray[1000];
	Uint16 DAC1_data = 33000;
	Uint16 DAC1_send = 33000;
	//Uint32 DAC1_data = 32767;
	//Uint32 DAC1_send = 32767;
	
	Uint32 CpuTimer0InterruptCount = 0;

/****************The interrupt function*****************/
	interrupt void ISRTimer0(void);		
	void pid_speed(void);

	void main(void)
	{

	// Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the DSP2833x_SysCtrl.c file.
	   InitSysCtrl();

	// Step 2. Initalize GPIO:
	// This example function is found in the DSP2833x_Gpio.c file and
	// illustrates how to set the GPIO to it's default state.
	// InitGpio();  // Skipped for this example
	  // InitXintf16Gpio();	//zq
	   init_zone7();
	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	   DINT;

	// Initialize the PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags
	// are cleared.
	// This function is found in the DSP2833x_PieCtrl.c file.
	   InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
	   IER = 0x0000;
	   IFR = 0x0000;
	   
	// Initialize the PIE vector table
	   InitPieVectTable();
	   
	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	   EALLOW;  // This is needed to write to EALLOW protected registers
		PieVectTable.TINT0 = &ISRTimer0;
	   EDIS;    // This is needed to disable write to EALLOW protected registers 

		InitCpuTimers();
		ConfigCpuTimer(&CpuTimer0 , 150 , 1000);//1/150*150*1000=1000微妙，也即1ms
		StartCpuTimer0();
		
	   IER |= M_INT1;
	   
	   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	   
	    EINT;   // Enable Global interrupt INTM
		ERTM;   // Enable Global realtime interrupt DBGM
	   
	// Step 4. Write Data to SRAM:

	   while(1)
	   {
	       DELAY_US(1000);
	       run++;
	      // LOG_printf(&trace, "writer  done.");
	       //LOG_printf(&trace,"current position is :%d/n",data_encoder.cnt_encoder);
	        //  if(CpuTimer0InterruptCount%10000==1)

	      // printf("%f\n",position_actual);  //      DAC1_data++;printf是一种非常花费时间的函数，实时性达不到要求
	   }

	}


	interrupt void ISRTimer0(void)
	{

	    if(begin==1)
	    {
	        CpuTimer0.InterruptCount++;
	        //position_set=200;
	        if(i==9)
	        {
	            i=0;
	            array[CpuTimer0InterruptCount]=position_actual;
	            if(CpuTimer0InterruptCount==999)
	            {
	                CpuTimer0InterruptCount=0;
	            }
	            else
	            {
	                CpuTimer0InterruptCount++;
	            }
	        }
	        else
	        {
	            i=i+1;
	        }
	    }
	    else
	    {
	        CpuTimer0.InterruptCount=0;
	        CpuTimer0InterruptCount=0;
	        memset(array,0,2000);
	    }

		PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
		CpuTimer0Regs.TCR.bit.TIF=1;//Clear the interrupt flag
		CpuTimer0Regs.TCR.bit.TRB=1;//Reload the count
		data_encoder.cie_encoder = read_data(0x0300);//Load the circulus at 0x0300
		data_encoder.dir_encoder = read_data(0x0200);//Load the direction at 0x0300
		data_encoder.cnt_encoder = read_data(0x0100);//Load the cnt at 0x0300
		  //printf("%f\n",position_actual);
		qep_posspeed.calc(&qep_posspeed,&data_encoder);//Calculated actual speed
		//position_set=CpuTimer0InterruptCount/1000*90;
		speed_actual = qep_posspeed.Speed_Mr_Rpm;//actual speed
		position_actual=qep_posspeed.Position_angle;//actual position
		//position PID control

		POSITION_LOOP.Give=position_set;
		POSITION_LOOP.Feedback=position_actual;
		POSITION_LOOP.Kp=PositionKp;
		POSITION_LOOP.Ki=PositionKi;
		POSITION_LOOP.Kd=PositionKd;
		POSITION_LOOP.OutMax=32767;
		POSITION_LOOP.OutMin=-32767;
		POSITION_LOOP.calc(&POSITION_LOOP);

		//speed PID control
		//SPEED_LOOP.Give=POSITION_LOOP.Output/32767*1000;
		SPEED_LOOP.Give=speed_set;
		SPEED_LOOP.Feedback=speed_actual;
		SPEED_LOOP.Kp=SPEEDKp;
		SPEED_LOOP.Ki=SPEEDKi;
		SPEED_LOOP.Ki=SPEEDTd;
		SPEED_LOOP.OutMax=SPEEDLimit;
		SPEED_LOOP.OutMin=-SPEEDLimit;
		SPEED_LOOP.calc(&SPEED_LOOP);  
	    //set parameter
		DAC1_data =(Uint16) (SPEED_LOOP.Output/2000*65535+32767);//      /2000*65535+32767  1000*65535+4000

		DAC1_send = DAC1_data;
		write_data(0x0010,DAC1_send);//0x0010 is the location of zone7

		//
	}
	

//===========================================================================
// No more.
//===========================================================================

