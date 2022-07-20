#include "ecbm_core.h"  //加载库函数的头文件。
float adc_value;
void main(void){        //main函数，必须的。
    
	system_init();      //系统初始化函数，也是必须的。
	adc_init();			//初始化ADC
	adc_value=adc_read_vref();//读取Vref的电压值。
	while(1){
		delay_ms(500);
		uart_printf(1,"ADC=%f\r\n",adc_voltage(0,adc_value));
		
		
    }
}