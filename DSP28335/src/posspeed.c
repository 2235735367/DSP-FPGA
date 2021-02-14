#include "DSP2833x_Device.h"
#include "Posspeed.h"

/********�ٶȼ��㺯��********/
void POSSPEED_Calc(POSSPEED *p,Encoder_DATA *e)
{
	float  Pulse_Number = 0;//������

	//p->DirectionQep = e->dir_encoder;							// ��⵱ǰת������	
	//p->Raw_Theta  = e->cnt_encoder + p->Calibrate_Angle;		// ���λ�ü�������ֵ�����в���

	//if(p->Raw_Theta < 0)
	//{
	//	p->Raw_Theta = p->Raw_Theta + p->Encoder_N;
	//}
	//else if(p->Raw_Theta > p->Encoder_N)
	//{
	//	p->Raw_Theta = p->Encoder_N;
	//}

	//p->Mech_Theta = p->Mesh_Scaler * p->Raw_Theta ;				// �����е�Ƕ�
	//p->Elec_Theta = p->Mech_Theta * p->Ploe_Pairs - floor(p->Mech_Theta * p->Ploe_Pairs); 		// �����Ƕ�

	p->Position_Cur = 1.0 * e->cnt_encoder;							//  ���浱ǰ�ı������������
    //λ��
    p->Position_angle= p->Position_Cur/11+360*e->cie_encoder;
	//ȷ����λʱ���ڵ�������ĿPulse_Number
	if(e->dir_encoder == 1)//˳ʱ��ת����������-4000
	{

	    //p->Position_angle=- p->Position_Cur/11;//û��Ȧ����Ϣ��ֻ��ʵ��һȦ���ڵĿ���
		if( p->Position_Cur > p->Position_Old )//����ͬһȦ�����ӵ�4000���
		{
			Pulse_Number = -p->Encoder_N - p->Position_Old + p->Position_Cur;
		}
		else
		{
			Pulse_Number = p->Position_Cur - p->Position_Old;
		}
	}
	else//��ʱ��������
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


