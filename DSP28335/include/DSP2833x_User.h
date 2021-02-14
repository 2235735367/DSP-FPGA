// TI File $Revision: /main/7 $
// Checkin $Date: August 13, 2007   16:57:59 $
//###########################################################################
//
// FILE:   DSP2833x_Examples.h
//
// TITLE:  DSP2833x Device Definitions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#ifndef DSP2833x_EXAMPLES_H
#define DSP2833x_EXAMPLES_H


#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------------
      Specify the PLL control register (PLLCR) and divide select (DIVSEL) value.
-----------------------------------------------------------------------------*/
//#define DSP28_DIVSEL   0   // Enable /4 for SYSCLKOUT
//#define DSP28_DIVSEL   1   // Disable /4 for SYSCKOUT
#define DSP28_DIVSEL     2   // Enable /2 for SYSCLKOUT
//#define DSP28_DIVSEL   3 // Enable /1 for SYSCLKOUT

#define DSP28_PLLCR   10
//#define DSP28_PLLCR    9
//#define DSP28_PLLCR    8
//#define DSP28_PLLCR    7
//#define DSP28_PLLCR    6
//#define DSP28_PLLCR    5
//#define DSP28_PLLCR    4
//#define DSP28_PLLCR    3
//#define DSP28_PLLCR    2
//#define DSP28_PLLCR    1
//#define DSP28_PLLCR    0  // PLL is bypassed in this mode
//----------------------------------------------------------------------------


/*-----------------------------------------------------------------------------
      Specify the clock rate of the CPU (SYSCLKOUT) in nS.

      Take into account the input clock frequency and the PLL multiplier
      selected in step 1.

      Use one of the values provided, or define your own.
      The trailing L is required tells the compiler to treat
      the number as a 64-bit value.

      Only one statement should be uncommented.

      Example 1:150 MHz devices:
                CLKIN is a 30MHz crystal.

                In step 1 the user specified PLLCR = 0xA for a
                150Mhz CPU clock (SYSCLKOUT = 150MHz).

                In this case, the CPU_RATE will be 6.667L
                Uncomment the line:  #define CPU_RATE  6.667L

      Example 2:  100 MHz devices:
                  CLKIN is a 20MHz crystal.

	              In step 1 the user specified PLLCR = 0xA for a
	              100Mhz CPU clock (SYSCLKOUT = 100MHz).

	              In this case, the CPU_RATE will be 10.000L
                  Uncomment the line:  #define CPU_RATE  10.000L
-----------------------------------------------------------------------------*/
#define CPU_RATE    6.667L   // for a 150MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE    7.143L   // for a 140MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE    8.333L   // for a 120MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   10.000L   // for a 100MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   13.330L   // for a 75MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   20.000L   // for a 50MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   33.333L   // for a 30MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   41.667L   // for a 24MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   50.000L   // for a 20MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   66.667L   // for a 15MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE  100.000L   // for a 10MHz CPU clock speed  (SYSCLKOUT)

//----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
      Target device (in DSP2833x_Device.h) determines CPU frequency
      (for examples) - either 150 MHz (for 28335 and 28334) or 100 MHz
      (for 28332). User does not have to change anything here.
-----------------------------------------------------------------------------*/
#if DSP28_28332                   // DSP28_28332 device only
  #define CPU_FRQ_100MHZ    1     // 100 Mhz CPU Freq (20 MHz input freq)
  #define CPU_FRQ_150MHZ    0
#else
  #define CPU_FRQ_100MHZ    0     // DSP28_28335||DSP28_28334
  #define CPU_FRQ_150MHZ    1     // 150 MHz CPU Freq (30 MHz input freq) by DEFAULT
#endif


//MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
//---------------------------------------------------------------------------
// Include Example Header Files:
//

#include "DSP2833x_GlobalPrototypes.h"         // Prototypes for global functions within the
                                              // .c files.

#include "DSP2833x_ePwm_defines.h"             // Macros used for PWM examples.
#include "DSP2833x_Dma_defines.h"              // Macros used for DMA examples.
#include "DSP2833x_I2C_defines.h"              // Macros used for I2C examples.

#define PARTNO_28335  0xFA
#define PARTNO_28334  0xF9
#define PARTNO_28332  0xF8


// SRAM 读数据函数
extern 	Uint16	read_data(Uint16 Register);
// SRAM 写数据函数
extern void	write_data(Uint16 Register,Uint16 data);

void init_zone7(void);




// DAC寄存器SRAM地址
#define			Config_Reg_Addr					0x00001
#define			Monitor_Reg_Addr				0x00003
#define			GPIO_Reg_Addr					0x00005
#define			Offset_A_Reg_Addr				0x00007
#define			Offset_B_Reg_Addr				0x00009
#define			BusyFlag_Reg_Addr				0x00011
#define			Reserved_Reg_Addr				0x00013
#define			DAC_0_Reg_Addr					0x00015
#define			DAC_1_Reg_Addr					0x00017
#define			DAC_2_Reg_Addr					0x00019
#define			DAC_3_Reg_Addr					0x00021
#define			DAC_4_Reg_Addr					0x00023
#define			DAC_5_Reg_Addr					0x00025
#define			DAC_6_Reg_Addr					0x00027
#define			DAC_7_Reg_Addr					0x00029
#define			Zero_0_Reg_Addr					0x00031
#define			Gain_0_Reg_Addr					0x00033
#define			Zero_1_Reg_Addr					0x00035
#define			Gain_1_Reg_Addr					0x00037
#define			Zero_2_Reg_Addr					0x00039
#define			Gain_2_Reg_Addr					0x00041
#define			Zero_3_Reg_Addr					0x00043
#define			Gain_3_Reg_Addr					0x00045
#define			Zero_4_Reg_Addr					0x00047
#define			Gain_4_Reg_Addr					0x00049
#define			Zero_5_Reg_Addr					0x00051
#define			Gain_5_Reg_Addr					0x00053
#define			Zero_6_Reg_Addr					0x00055
#define			Gain_6_Reg_Addr					0x00057
#define			Zero_7_Reg_Addr					0x00059
#define			Gain_7_Reg_Addr					0x00061

#define			Config_Data_Reg_Addr			0x00002
#define			Monitor_Data_Reg_Addr			0x00004
#define			GPIO_Data_Reg_Addr				0x00006
#define			Offset_A_Data_Reg_Addr			0x00008
#define			Offset_B_Data_Reg_Addr			0x00010
#define			BusyFlag_Data_Reg_Addr			0x00012
#define			Reserved_Data_Reg_Addr			0x00014
#define			DAC_0_Data_Reg_Addr				0x00016
#define			DAC_1_Data_Reg_Addr				0x00018
#define			DAC_2_Data_Reg_Addr				0x00020
#define			DAC_3_Data_Reg_Addr				0x00022
#define			DAC_4_Data_Reg_Addr				0x00024
#define			DAC_5_Data_Reg_Addr				0x00026
#define			DAC_6_Data_Reg_Addr				0x00028
#define			DAC_7_Data_Reg_Addr				0x00030
#define			Zero_0_Data_Reg_Addr			0x00032
#define			Gain_0_Data_Reg_Addr			0x00034
#define			Zero_1_Data_Reg_Addr			0x00036
#define			Gain_1_Data_Reg_Addr			0x00038
#define			Zero_2_Data_Reg_Addr			0x00040
#define			Gain_2_Data_Reg_Addr			0x00042
#define			Zero_3_Data_Reg_Addr			0x00044
#define			Gain_3_Data_Reg_Addr			0x00046
#define			Zero_4_Data_Reg_Addr			0x00048
#define			Gain_4_Data_Reg_Addr			0x00050
#define			Zero_5_Data_Reg_Addr			0x00052
#define			Gain_5_Data_Reg_Addr			0x00054
#define			Zero_6_Data_Reg_Addr			0x00056
#define			Gain_6_Data_Reg_Addr			0x00058
#define			Zero_7_Data_Reg_Addr			0x00060
#define			Gain_7_Data_Reg_Addr			0x00062


// DAC寄存器实际地址
#define			Config_Reg_Data					0
#define			Monitor_Reg_Data				1
#define			GPIO_Reg_Data					2
#define			Offset_A_Reg_Data				3
#define			Offset_B_Reg_Data				4
#define			BusyFlag_Reg_Data				5
#define			Reserved_Reg_Data				6
#define			DAC_0_Reg_Data					8
#define			DAC_1_Reg_Data					9
#define			DAC_2_Reg_Data					10
#define			DAC_3_Reg_Data					11
#define			DAC_4_Reg_Data					12
#define			DAC_5_Reg_Data					13
#define			DAC_6_Reg_Data					14
#define			DAC_7_Reg_Data					15
#define			Zero_0_Reg_Data					16
#define			Gain_0_Reg_Data					24
#define			Zero_1_Reg_Data					17
#define			Gain_1_Reg_Data					25
#define			Zero_2_Reg_Data					18
#define			Gain_2_Reg_Data					26
#define			Zero_3_Reg_Data					19
#define			Gain_3_Reg_Data					27
#define			Zero_4_Reg_Data					20
#define			Gain_4_Reg_Data					28
#define			Zero_5_Reg_Data					21
#define			Gain_5_Reg_Data					29
#define			Zero_6_Reg_Data					22
#define			Gain_6_Reg_Data					30
#define			Zero_7_Reg_Data					23
#define			Gain_7_Reg_Data					31




// Include files not used with DSP/BIOS
#ifndef DSP28_BIOS
#include "DSP2833x_DefaultISR.h"
#endif


// DO NOT MODIFY THIS LINE.
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L)


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_EXAMPLES_H definition


//===========================================================================
// End of file.
//===========================================================================
