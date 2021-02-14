// TI File $Revision: /main/6 $
// Checkin $Date: August 9, 2007   17:15:33 $
//###########################################################################
//
// FILE:	Example_posspeed.h
//
// TITLE:	Pos/speed measurement using EQEP peripheral
//
// DESCRIPTION:
//
// Header file containing data type and object definitions and 
// initializers. 
//
//###########################################################################
// Original Author: SD
//
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#if (CPU_FRQ_150MHZ)
  #define CPU_CLK   150e6
#endif
#if (CPU_FRQ_100MHZ)
  #define CPU_CLK   100e6
#endif

#define PWM_CLK   5e3              // 5kHz (300rpm) EPWM1 frequency. Freq. can be changed here
#define SP       800
#define TBCTLVAL  0x200E           // up-down count, timebase=SYSCLKOUT

#ifndef __POSSPEED__
#define __POSSPEED__


#include "IQmathLib.h"         // Include header for IQmath library
/*-----------------------------------------------------------------------------
Define the structure of the POSSPEED Object 
-----------------------------------------------------------------------------*/
typedef struct
{               float Elec_Theta;			// 电机电角度0
				float Mech_Theta;			// 电机机械角度0
                int   DirectionQep;			// 电机旋转方向0
                int   Ploe_Pairs;			// 电机的极对数	2
                int   Line_Encoder;			// 码盘一周的脉冲数1000
                int   Encoder_N;			// 码盘一周脉冲数的四倍4000
                int   Calibrate_Angle;		// 电机A项绕组和码盘Index信号之间的夹角0
                float Mesh_Scaler;			// 1/Encoder_N  1/4000
                float Raw_Theta;			// 初始定位后，电机转子D轴和定子A相绕组之间所相差得码盘计数值0
                int   Index_Sync_Flag;		// Index_Sync_Flag 输出信号0
                float BaseRPM;				// 电机的额定转速4000
                float Speed_Mr_Rpm_Scaler;	// 6000/（ Encoder_N * T ），T为M法测速的时间间隔5
                float Speed_Mr_Rpm;			// M法测量的转速， r.p.m  0
                float Speed_Mr;				// M法测量的转速，标称值 per-uint   0
                float Position_Cur;			// 当前位置0
                float Position_Old;			// 上一次位置0
                float Position_angle;     //位置
                void (*calc)();				// 转速、位置计算函数指针
                }  POSSPEED;

typedef struct  { signedint cnt_encoder;
				  Uint32 dir_encoder;
				  signedint cie_encoder;
				} Encoder_DATA;
				
/*-----------------------------------------------------------------------------
Define a POSSPEED_handle
-----------------------------------------------------------------------------*/
typedef POSSPEED *POSSPEED_handle;
typedef Encoder_DATA *ENCODER_handle;


/*-----------------------------------------------------------------------------
Default initializer for the POSSPEED Object.
-----------------------------------------------------------------------------*/
	#define POSSPEED_DEFAULTS {0, 0,0,2,1000,4000,0,1.0/4000,0,\
        0,4000.0,15.0,0,0,0,0,0,\
        (void (*)(long))POSSPEED_Calc }
		
	#define ENCODER_DEFAULTS { 0,0,0}

/*-----------------------------------------------------------------------------
Prototypes for the functions in posspeed.c                                 
-----------------------------------------------------------------------------*/                                         
void POSSPEED_Calc(POSSPEED_handle,ENCODER_handle);
                
#endif /*  __POSSPEED__ */




