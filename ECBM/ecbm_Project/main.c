#include "ecbm_core.h"  //���ؿ⺯����ͷ�ļ���


void main(void){        //main����������ġ�
    system_init();      //ϵͳ��ʼ��������Ҳ�Ǳ���ġ�
	
	//STC8ϵ��һЩ�ͺŵ�IO�ϵ�Ĭ���Ǹ���̬��Ҫ���ó���������죩̬��
	gpio_mode(D33,GPIO_OUT);
	gpio_mode(D54,GPIO_OUT);//����ʹ����P5.4�š��������P0.0����D00���Դ����ơ�
	
	gpio_mode(D33,GPIO_OUT);
    while(1){
		gpio_toggle(D54);//��˸�ƾ���IO�ߵ͵�ƽ�л�ʹ��LED��˸���������˷�ת������
		gpio_out_fast(GPIO_P3,GPIO_PIN_3,0);//P3.3������͵�ƽ�� 0
		delay_ms(500);//������ʱ���Ըı���˸��Ƶ�ʡ�
    }
}
