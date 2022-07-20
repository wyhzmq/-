#include "ecbm_core.h"  //加载库函数的头文件。


void main(void){        //main函数，必须的。
    system_init();      //系统初始化函数，也是必须的。
	
	//STC8系列一些型号的IO上电默认是高阻态，要设置成输出（推挽）态。
	gpio_mode(D33,GPIO_OUT);
	gpio_mode(D54,GPIO_OUT);//这里使用了P5.4脚。如果换成P0.0就填D00，以此类推。
	
	gpio_mode(D33,GPIO_OUT);
    while(1){
		gpio_toggle(D54);//闪烁灯就是IO高低电平切换使得LED闪烁，所以用了翻转函数。
		gpio_out_fast(GPIO_P3,GPIO_PIN_3,0);//P3.3脚输出低电平。 0
		delay_ms(500);//更改延时可以改变闪烁的频率。
    }
}
