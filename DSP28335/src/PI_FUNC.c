/*
 DESCRIPTION:
    


 TEST RESULT: 

 DESIGNED TIME: 

 DESIGNER: ZhuHongshun/zhslove_2006@126.com

*/


#include "DSP2833x_Device.h"
#include <math.h>
#include "PI_FUNC.h"

//======== Definations for functions ===========================
//**********************************
/*
  @ Description:
  @ Param
  @ Return
*/
//**********************************
/*void PIfunc_calc(PI_FUNC *v)
{	
 //y(k) = (Kp+Ki*T) * x(k) - Kp * x(k-1) + y(k-1)   
   //float  T=0.0002,k1;
     float k1;
     k1 = v->Kp + v->T * v->Ki;
     v->PresentE = v->Give - v->Feedback;
     v->Output = k1 * v->PresentE - v->Kp * v->LastE + v->LastOutput;
    
     if(v->Output > v->OutMax) v->Output = v->OutMax;
     if(v->Output < v->OutMin) v->Output = v->OutMin;

	 v->LastE = v->PresentE;
	 v->LastOutput=v->Output;
		
} */
//************ÔöÁ¿Ê½PID***************//
void PIfunc_calc(PI_FUNC *v)
{
 //y(k) = (Kp+Ki*T) * x(k) - Kp * x(k-1) + y(k-1)
   //float  T=0.0002,k1;
    // float k1;
     //k1 = v->Kp + v->T * v->Ki;
     v->PresentE = v->Give - v->Feedback;
    // v->EkSum= v->EkSum+ v->PresentE;
     v->Output =v->Kp * (v->PresentE- v->LastE) + v->Ki * v->PresentE + v->Kd * (v->PresentE-2*v->LastE+v->LLastE)+v->Output;

     if(v->Output > v->OutMax) v->Output = v->OutMax;
     if(v->Output < v->OutMin) v->Output = v->OutMin;

     v->LLastE= v->LastE;
     v->LastE = v->PresentE;
     //v->LastOutput=v->Output;
} 







//==============================================================
//End of file.
//==============================================================



