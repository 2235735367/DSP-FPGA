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
{               float Elec_Theta;			// �����Ƕ�0
				float Mech_Theta;			// �����е�Ƕ�0
                int   DirectionQep;			// �����ת����0
                int   Ploe_Pairs;			// ����ļ�����	2
                int   Line_Encoder;			// ����һ�ܵ�������1000
                int   Encoder_N;			// ����һ�����������ı�4000
                int   Calibrate_Angle;		// ���A�����������Index�ź�֮��ļн�0
                float Mesh_Scaler;			// 1/Encoder_N  1/4000
                float Raw_Theta;			// ��ʼ��λ�󣬵��ת��D��Ͷ���A������֮�����������̼���ֵ0
                int   Index_Sync_Flag;		// Index_Sync_Flag ����ź�0
                float BaseRPM;				// ����Ķת��4000
                float Speed_Mr_Rpm_Scaler;	// 6000/�� Encoder_N * T ����TΪM�����ٵ�ʱ����5
                float Speed_Mr_Rpm;			// M��������ת�٣� r.p.m  0
                float Speed_Mr;				// M��������ת�٣����ֵ per-uint   0
                float Position_Cur;			// ��ǰλ��0
                float Position_Old;			// ��һ��λ��0
                float Position_angle;     //λ��
                void (*calc)();				// ת�١�λ�ü��㺯��ָ��
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




