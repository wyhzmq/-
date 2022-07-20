#include "ecbm_core.h"  //加载库函数的头文件。
	
void main(void){        //main函数，必须的。
	
	/*
		P32设置为外部中断0
	*/
	
	//系统初始化函数，也是必须的。
	system_init();  
	//打开看门狗
	wdt_start();
	//复位寄存器初始化函数
	power_rstcfg_init();
	//设置IO口工作模式函数
	gpio_mode(D33,GPIO_OUT);
	gpio_mode(D54,GPIO_OUT);
	//中断函数初始化
	exti_init();
	//中断模式设置函数
	exti_set_mode(0,EXTI_MODE_DOWN);
	//打开中断函数
	exti_start(0);
	while(1){
		//把D54口输出低电平，打开LED
		gpio_out(D54,0);
		//做完之后喂狗
		wdt_feed();
    }
}
//触发中断请求
void exti0_it_callback(){
	
		//把D54口输出高电平，关闭LED
		gpio_out(D54,1);
		LED=0;
		delay_ms(500);
		LED=1;
	
}
