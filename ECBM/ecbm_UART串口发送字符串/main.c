#include "ecbm_core.h"  //���ؿ⺯����ͷ�ļ���
	
void main(void){        //main����������ġ�
    
	system_init();      //ϵͳ��ʼ��������Ҳ�Ǳ���ġ�

	
	while(1){
		delay_ms(1000);
	
		uart_string(1,"Hello world \r\n");
    }
}