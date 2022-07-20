#include "ecbm_core.h"  //加载库函数的头文件。

void main(void){        //main函数，必须的。
    system_init();      //系统初始化函数，也是必须的。
	//设置IO口工作模式函数
	gpio_mode(D54,GPIO_OUT);
	//初始化定时器
	timer_init();
	//定时器设定定时模式函数。50000us 也就是50ms
	timer_set_timer_mode(0,50000);
	//打开定时器0
	timer_start(0);
    while(1){
		delay_ms(5000);
    }
}
void timer0_it_callback(){
	LED=0;
}