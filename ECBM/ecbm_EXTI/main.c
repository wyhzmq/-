#include "ecbm_core.h"  //���ؿ⺯����ͷ�ļ���
	
void main(void){        //main����������ġ�
	
	/*
		P32����Ϊ�ⲿ�ж�0
	*/
	
	//ϵͳ��ʼ��������Ҳ�Ǳ���ġ�
	system_init();  
	//�򿪿��Ź�
	wdt_start();
	//��λ�Ĵ�����ʼ������
	power_rstcfg_init();
	//����IO�ڹ���ģʽ����
	gpio_mode(D33,GPIO_OUT);
	gpio_mode(D54,GPIO_OUT);
	//�жϺ�����ʼ��
	exti_init();
	//�ж�ģʽ���ú���
	exti_set_mode(0,EXTI_MODE_DOWN);
	//���жϺ���
	exti_start(0);
	while(1){
		//��D54������͵�ƽ����LED
		gpio_out(D54,0);
		//����֮��ι��
		wdt_feed();
    }
}
//�����ж�����
void exti0_it_callback(){
	
		//��D54������ߵ�ƽ���ر�LED
		gpio_out(D54,1);
		LED=0;
		delay_ms(500);
		LED=1;
	
}
