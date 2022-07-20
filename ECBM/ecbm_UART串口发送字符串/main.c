#include "ecbm_core.h"  //加载库函数的头文件。
	
void main(void){        //main函数，必须的。
    
	system_init();      //系统初始化函数，也是必须的。

	
	while(1){
		delay_ms(1000);
	
		uart_string(1,"Hello world \r\n");
    }
}