#include "ecbm_core.h"  //加载库函数的头文件。
u8 count=0;	
void main(void){        //main函数，必须的。
    
	 system_init();      //系统初始化函数，也是必须的。
	  while(1){
    count++;//统计循环次数，也是为了演示uart_printf的功能。
		
		uart_printf(1,"Hello,ECBM is runing at %d times.\r\n",(u16)count);//向串口1发送字符串和count的值。
		//打开串口助手，设置好COM口，115200，8位，无校验，一位停止位。即可查看。
		//注意：所有在单片机上运行的printf函数，其占位符%d均无法支持u8型变量，请使用（u16）把变量强转成u16型才能正常输出。
		
		delay_ms(1000);//发送频率不用太快，否则串口助手会因大量数据而卡死。
		//当你不慎将串口发送数据间隔设置太小，导致单片机不能正常使用自动下载功能的时候。
		//请使用冷启动来下载程序，即先断电--在STCISP上点击下载--再上电。
    }
}