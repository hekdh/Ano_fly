#include "Ano_duoji.h"
#include "stm32f4xx.h" 
#include "Drv_pwm_out.h"
#include "Ano_FlightCtrl.h"
#include "ANO_FcData.h"
void Ano_duoji(u8 dt)
{
 static u8 b=1;
 if(flag.tutu==2||b>10)	 
 {     b++;
	 if(flag.tutu==0)
	 TIM5->CCR3 = 1500;
     if(flag.tutu==1)
    TIM5->CCR3 =	2500;
     if(b>20)
      b--;
	 if(flag.tutu==2)
	TIM5->CCR3 = 500;
}
}

//ioesr05超声波数据接收函数
u8 UltraSonic_buf[10]; 
void UltraSonic_Byte_Get(u8 bytedata)
{
	static u8 rec_sta;
	u8 check_val=0;
	
	//
	UltraSonic_buf[rec_sta] = bytedata;
	//
	if(rec_sta==0)
	{
		if(bytedata==0xff)
		{
			rec_sta++;
		}
		else
		{
			rec_sta=0;
		}
	}
	else if(rec_sta==1)
	{
		if(bytedata >0x07)//(bytedata==0x29)未确定
		{
			rec_sta=0;
		}	
		else 
		{
			rec_sta++;
		}		
	}
	else if(rec_sta==2)
	{
			rec_sta++;
		
	}
	else if(rec_sta==3)
	{
			for(u8 i=0;i<3;i++)
		{
			check_val += UltraSonic_buf[i];
		}
		//
		if(check_val == bytedata)
		{
			//解析成功
			UltraSonic_Data_Analysis(UltraSonic_buf,4);
			//
			rec_sta=0;
		}
		else
		{
			rec_sta=0;
		}		
	}

}
static void UltraSonic_Data_Analysis(u8 *buf_data,u8 len)
{
if(buf_data[0]==0xff)
{
	if(buf_data[1]<=7)
	{
		flag.offline=0;
		flag.distance= buf_data[1]*256+buf_data[2];

	}
	else
	{
			flag.offline=1;
		flag.distance= 0;

	}
		
		
}




}