#include "ecbm_core.h"  //加载库函数的头文件。
#define TimeOutSet 3
#define COM_RX1_Lenth 100
u8 RECED_FLAG=0;
u8 RX_TimeOut=0;
u8 RX_Cnt=0;
u8 rcv_buff[COM_RX1_Lenth];//接受缓存
u8 i;
void main(void){        //main函数，必须的。
    
	system_init();      //系统初始化函数，也是必须的。
	  
	timer_init();//初始化定时器
	timer_set_timer_mode(0,20000);//timer0设置为2ms
	timer_start(0);//打开定时器0
	while(1){
		if(RX_TimeOut ==0)
		{
			if(RX_Cnt>0)
			{
				for(i=0;i<RX_Cnt;i++) uart_char(1,rcv_buff[i]);//收到的数据原
			}
			RX_Cnt=0;
			RX_TimeOut=TimeOutSet;
		}
    }
}
void uart1_receive_callback()
{
	if(RX_Cnt >= COM_RX1_Lenth) RX_Cnt = 0;
	rcv_buff[RX_Cnt++] = SBUF;//收到数据存入缓冲区
	RX_TimeOut=TimeOutSet;
}
void timer0_it_callback()
{
	if(RX_TimeOut >0) RX_TimeOut--;
}