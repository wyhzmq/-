#include "ecbm_core.h"  //���ؿ⺯����ͷ�ļ���
#define TimeOutSet 3
#define COM_RX1_Lenth 100
u8 RECED_FLAG=0;
u8 RX_TimeOut=0;
u8 RX_Cnt=0;
u8 rcv_buff[COM_RX1_Lenth];//���ܻ���
u8 i;
void main(void){        //main����������ġ�
    
	system_init();      //ϵͳ��ʼ��������Ҳ�Ǳ���ġ�
	  
	timer_init();//��ʼ����ʱ��
	timer_set_timer_mode(0,20000);//timer0����Ϊ2ms
	timer_start(0);//�򿪶�ʱ��0
	while(1){
		if(RX_TimeOut ==0)
		{
			if(RX_Cnt>0)
			{
				for(i=0;i<RX_Cnt;i++) uart_char(1,rcv_buff[i]);//�յ�������ԭ
			}
			RX_Cnt=0;
			RX_TimeOut=TimeOutSet;
		}
    }
}
void uart1_receive_callback()
{
	if(RX_Cnt >= COM_RX1_Lenth) RX_Cnt = 0;
	rcv_buff[RX_Cnt++] = SBUF;//�յ����ݴ��뻺����
	RX_TimeOut=TimeOutSet;
}
void timer0_it_callback()
{
	if(RX_TimeOut >0) RX_TimeOut--;
}