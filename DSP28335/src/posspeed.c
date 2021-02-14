#include "DSP2833x_Device.h"
#include "Posspeed.h"

/********速度计算函数********/
void POSSPEED_Calc(POSSPEED *p,Encoder_DATA *e)
{
	float  Pulse_Number = 0;//脉冲数

	//p->DirectionQep = e->dir_encoder;							// 检测当前转动方向	
	//p->Raw_Theta  = e->cnt_encoder + p->Calibrate_Angle;		// 检测位置计数器的值并进行补偿

	//if(p->Raw_Theta < 0)
	//{
	//	p->Raw_Theta = p->Raw_Theta + p->Encoder_N;
	//}
	//else if(p->Raw_Theta > p->Encoder_N)
	//{
	//	p->Raw_Theta = p->Encoder_N;
	//}

	//p->Mech_Theta = p->Mesh_Scaler * p->Raw_Theta ;				// 计算机械角度
	//p->Elec_Theta = p->Mech_Theta * p->Ploe_Pairs - floor(p->Mech_Theta * p->Ploe_Pairs); 		// 计算电角度

	p->Position_Cur = 1.0 * e->cnt_encoder;							//  保存当前的编码器脉冲个数
    //位置
    p->Position_angle= p->Position_Cur/11+360*e->cie_encoder;
	//确定单位时间内的脉冲数目Pulse_Number
	if(e->dir_encoder == 1)//顺时针转动减计数到-4000
	{

	    //p->Position_angle=- p->Position_Cur/11;//没有圈数信息，只能实现一圈以内的控制
		if( p->Position_Cur > p->Position_Old )//不在同一圈，增加到4000溢出
		{
			Pulse_Number = -p->Encoder_N - p->Position_Old + p->Position_Cur;
		}
		else
		{
			Pulse_Number = p->Position_Cur - p->Position_Old;
		}
	}
	else//逆时针增计数
	{
	    //p->Position_angle=p->Position_Cur/11;
		if( p->Position_Cur < p->Position_Old )
		{
			Pulse_Number =  p->Encoder_N - p->Position_Old + p->Position_Cur;
		}
		else
		{
			Pulse_Number = p->Position_Cur - p->Position_Old;
		}
	}
	
	if(Pulse_Number > p->Encoder_N)
	{
		p->Speed_Mr_Rpm = p->BaseRPM;
	}
	else if(Pulse_Number < (-p->Encoder_N))
	{
		p->Speed_Mr_Rpm = (- p->BaseRPM);
	}
	else 
	{
		p->Speed_Mr_Rpm = Pulse_Number *p->Speed_Mr_Rpm_Scaler;
	}
	
	p->Speed_Mr = p->Speed_Mr_Rpm/p->BaseRPM;
	
	p->Position_Old = p->Position_Cur;

}


