#include "ecbm_core.h"  //���ؿ⺯����ͷ�ļ���

void main(void){        //main����������ġ�
    system_init();      //ϵͳ��ʼ��������Ҳ�Ǳ���ġ�
	//����IO�ڹ���ģʽ����
	gpio_mode(D54,GPIO_OUT);
	//��ʼ����ʱ��
	timer_init();
	//��ʱ���趨��ʱģʽ������50000us Ҳ����50ms
	timer_set_timer_mode(0,50000);
	//�򿪶�ʱ��0
	timer_start(0);
    while(1){
		delay_ms(5000);
    }
}
void timer0_it_callback(){
	LED=0;
}