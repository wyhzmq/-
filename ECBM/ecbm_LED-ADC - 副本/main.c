#include "ecbm_core.h"  //���ؿ⺯����ͷ�ļ���
float vref;
void main(void){        //main����������ġ�
    
	system_init();      //ϵͳ��ʼ��������Ҳ�Ǳ���ġ�
	adc_init();
	vref=adc_read_vref();//��ȡVref�ĵ�ѹֵ��
	while(1){
		delay_ms(500);
		uart_printf(1,"ADC=%f\r\n",adc_voltage(0,vref));
		
		
    }
}