#include "ecbm_core.h"
/*------------------------------------资源冲突警告---------------------------------*/
#if ECBM_AUTO_DOWNLOAD_EN
#   if ECBM_UART_LIB_EN == 0
#       warning 因串口库未使能,自动下载功能失效!
#   endif
#   if ECBM_UART1_EN == 0
#       error 自动下载功能因串口1未使能而开启失败,请前往uart.h使能串口1!
#   endif
#   if ECBM_UART1_IO != 0
#       error 自动下载功能需要串口1映射到P30和P31,请前往uart.h修改串口1的输出IO!
#   endif
#endif
/*-----------------------------------可选模块设定----------------------------------*/
union{
    u32 num32;
    u16 num16[2];
    u8  num8[4];
}fast_cout;
/*-------------------------------------------------------
毫秒级延时函数
-------------------------------------------------------*/
void delay_ms(u16 ms){
    u16 i;
    if(ms){
        do{
            i=ECBM_SYSCLK_SETTING/10000;
            while(--i);
        }while(--ms);    
    }
}
/*-------------------------------------------------------
微秒级延时函数（节拍）
-------------------------------------------------------*/
void delay_us(u16 us){
    u16 i;
    i=us;
	do{}while(--i);
}
/*-------------------------------------------------------
微秒级延时函数的节拍计算函数
-------------------------------------------------------*/
u16 delay_set_us(u16 us){
//公式计算所花的时间太长，拆分成两个函数。先用这个函数推算出延时的数值，再用下面的函数调用。
    fast_cout.num32=((u32)(ECBM_SYSCLK_SETTING/10000)*(u32)(us))*131;
    return fast_cout.num16[0]>>1;
}
/************************************串口调试模块***************/#if ((ECBM_AUTO_DOWNLOAD_EN)&&(ECBM_UART_LIB_EN))
/*-------------------------------------------------------
自动下载所需的变量 
-------------------------------------------------------*/
bit auto_download_en;            //自动下载的使能
u8 data auto_download_old_char;  //保存上一次接收的数据
u8 data auto_download_char_count;//相同数据计数
/*-------------------------------------------------------
下载流判断函数
-------------------------------------------------------*/
void system_uart_reset(){
    if(auto_download_old_char!=UART1_GET_REG_SBUF){ //判断重复字符，如果字符不重复
        auto_download_old_char=UART1_GET_REG_SBUF;  //就更新oldchar
        auto_download_char_count=0;                 //计数器清零
    }else{                                          //如果字符重复
        if(auto_download_en)auto_download_char_count++;//则重复计数器+1
    }
    if(auto_download_char_count>=233){              //接收到233个重复数据时
        EA_DISABLE;                                 //断开所有中断
        while(1)POWER_RESET;                        //一直尝试重启
    }
}
/****************************************************************************/#endif
/*-------------------------------------------------------
系统检查函数
-------------------------------------------------------*/
#if ((ECBM_MCU_CHECK_EN)&&(ECBM_UART_PRINTF_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_UART1_EN))
void system_check(){
    u8 i,j;    
    u16 aaa=0x1234;
#if         (ECBM_MCU&0xF00000)==0x100000
#   define	ECBM_MCU_NAME   "STC8F"
#elif       (ECBM_MCU&0xF00000)==0x200000
#   define	ECBM_MCU_NAME   "STC8A"
#elif       (ECBM_MCU&0xF00000)==0x300000
#   define	ECBM_MCU_NAME   "STC8G"
#elif       (ECBM_MCU&0xF00000)==0x400000
#   define	ECBM_MCU_NAME   "STC8H"
#elif       (ECBM_MCU&0xF00000)==0x500000
#   define	ECBM_MCU_NAME   "STC8C"
#endif
    uart_printf(1,"ECBM V%bu.%bu.%bu on %s",ECBM_FVN,ECBM_RVN,ECBM_BVN,ECBM_MCU_NAME);//输出版本号和单片机型号
    uart_printf(1,"%uK",(u16)((ECBM_MCU&0x0F0000)>>16));
    uart_printf(1,"%02u",(u16)(ECBM_MCU_ROM_SIZE));
#if     ECBM_MCU    ==    0x110301
    uart_printf(1,"-8PIN");
#elif   ECBM_MCU    ==    0x110302
    uart_printf(1,"S2-16PIN/20PIN");
#elif   ECBM_MCU    ==    0x120502
    uart_printf(1,"S2");
#elif   ECBM_MCU    ==    0x120504
    uart_printf(1,"S4");
#elif   ECBM_MCU    ==    0x2405C2
    uart_printf(1,"S2A12");
#elif   ECBM_MCU    ==    0x2815C4
    uart_printf(1,"D4");
#elif   ECBM_MCU    ==    0x2805C4
    uart_printf(1,"S4A12");
#elif   ECBM_MCU    ==    0x3103A2
    uart_printf(1,"-16PIN/20PIN");
#elif   ECBM_MCU    ==    0x310201
    uart_printf(1,"-8PIN ");
#elif   ECBM_MCU    ==    0x3102A1
    uart_printf(1,"A-8PIN");
#elif   ECBM_MCU    ==    0x3103A1
    uart_printf(1,"T-20PIN");
#elif   ECBM_MCU    ==    0x3205A2
    uart_printf(1,"S2");
#elif   ECBM_MCU    ==    0x3205A4
    uart_printf(1,"S4");
#elif   ECBM_MCU    ==    0x4103A2
    uart_printf(1,"-20PIN");
#elif   ECBM_MCU    ==    0x4105A2
    uart_printf(1,"-32PIN");    
#elif   ECBM_MCU    ==    0x4305C2
    uart_printf(1,"S2");    
#elif   ECBM_MCU    ==    0x4305C4
    uart_printf(1,"S4");
#elif   ECBM_MCU    ==    0x4805C4
    uart_printf(1,"U");    
#elif   ECBM_MCU    ==    0x520502
    uart_printf(1,"S2");    
#elif   ECBM_MCU    ==    0x520504
    uart_printf(1,"S4");
#endif
    j=0;
    uart_printf(1,"\r\nChecking MCU ID");
    for(i=0;i<7;i++){
        uart_printf(1,".");
        if((REG_ID(i))==(MCUID[i])){
            j++;
        }
    }
    if(j!=7){
        uart_printf(1,"Error\r\nPlease check the setting of the MCU model\r\n");
    }else{
        uart_printf(1,"OK\r\nID    :");for(i=0;i<7;i++){uart_printf(1,"%02X",(u16)(MCUID[i]));}uart_printf(1,"\r\n");        //输出唯一ID号
        uart_printf(1,"DATA  :128\tByte\r\n");//DATA区固定是128Byte
        uart_printf(1,"IDATA :128\tByte\r\n");//IDATA区固定是128Byte
        uart_printf(1,"XDATA :%u\tByte\r\n",(u16)((ECBM_MCU&0x0F0000)>>16)*1024);//从配置文件中获取XDATA区大小
        uart_printf(1,"FLASH :%lu\tByte\r\n",(u32)ECBM_MCU_ROM_SIZE*1024);//从配置文件中获取FLASH区大小
        uart_printf(1,"SYSCLK:%lu\tHz\r\n",ECBM_SYSCLK_SETTING);//输出内部晶振值，在图形界面上设置
        uart_printf(1,"BGV   :%u\tmV\r\n",REG_BGV);//输出内部电压基准值，需要在STC-ISP上设置
        uart_printf(1,"ENDIAN:");
        if(*((char*)(&aaa))==0x12)uart_printf(1,"big\tendian\r\n");
        if(*((char*)(&aaa))==0x34)uart_printf(1,"little\tendian\r\n");
    }    
}
#endif
/*----------------------------------其他系统函数-----------------------------------*/
#define SYS_HSI_S 0 //内部高速时钟HSI(标准)
#define SYS_HSI_C 1 //内部高速时钟HSI(自定义)
#define SYS_LSI   2 //内部低速时钟LSI
#define SYS_LSE   3 //外部低速时钟LSI
#define SYS_HSE_A 4 //外部有源晶振
#define SYS_HSE_P 5 //外部无源晶振
void system_set_clock(u8 source){
    switch(source){
        case SYS_HSI_S:
        case SYS_HSI_C:{
            CLK_HSI_POWER_ON;   //使能HSI，即内部24M的IRC。
            CLK_SET_SOURCE_HSI; //切换到HSI。
            CLK_HSE_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_LSE_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_LSI_POWER_OFF;  //关闭其他时钟源，省电。
        }break;
        case SYS_LSI:{
            CLK_LSI_POWER_ON;   //使能LSI，即内部32K的IRC。
            CLK_SET_SOURCE_LSI; //切换到LSI。
            CLK_HSI_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_LSE_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_HSE_POWER_OFF;  //关闭其他时钟源，省电。
        }break;
        case SYS_LSE:{
            CLK_LSE_POWER_ON;   //使能LSE，即外部低速晶振。
            CLK_SET_SOURCE_LSE; //切换到LSE。
            CLK_LSI_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_HSI_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_HSE_POWER_OFF;  //关闭其他时钟源，省电。
        }break;
        case SYS_HSE_A:{
            CLK_HSE_A_POWER_ON; //使能HSE（有源晶振）。
            CLK_SET_SOURCE_HSE; //切换到HSE。
            CLK_HSI_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_LSE_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_LSI_POWER_OFF;  //关闭其他时钟源，省电。
        }break;
        case SYS_HSE_P:{
            CLK_HSE_P_POWER_ON; //使能HSE（无源晶振）。
            CLK_SET_SOURCE_HSE; //切换到HSE。
            CLK_HSI_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_LSE_POWER_OFF;  //关闭其他时钟源，省电。
            CLK_LSI_POWER_OFF;  //关闭其他时钟源，省电。
        }break;
    }
}
void system_set_div(u8 div){
    if(div==0){                 //排除掉0这个不稳定选项。
        CLK_SET_REG_CLKDIV(1);  //如果输入0的话就改成1。
    }else{
        CLK_SET_REG_CLKDIV(div);//如果不是0，就直接写入寄存器。
    }
}
/*-------------------------------------------------------
库函数系统初始化函数
-------------------------------------------------------*/
void system_init(void){
    EX_SFR_ENABLE;//打开额外的寄存器。
//---------------自动下载--------------//
#if ((ECBM_AUTO_DOWNLOAD_EN)&&(ECBM_UART_LIB_EN))//判断否需要开启自动下载。
    auto_download_en=1;         //打开自动下载使能
    auto_download_old_char=0;   //初始化串口相关变量
    auto_download_char_count=0; //初始化串口相关变量
    uart_init();
#endif
//-------------基本硬件设置------------//
#if (ECBM_POWER_LIB_EN)&&(ECBM_POWER_RST_CFG_EN)
    power_rstcfg_init();
#endif    
//-------------时钟输出设置------------//    
#if ECBM_SYSCLK_OUT_EN //判断是否需要开启时钟输出。
#   if ((ECBM_MCU&0xF00000)>0x200000)//检查是不是GH。
#       if ECBM_SYSLCK_OUT_PIN
            CLK_SET_OUT_TO_P16_GH;
#       else
            CLK_SET_OUT_TO_P54_GH;
#       endif
        CLK_OUT_SET_DIV_GH(ECBM_SYSCLK_OUT_SETTING_GH);
#   else
#       if ECBM_SYSLCK_OUT_PIN
            CLK_SET_OUT_TO_P16_FA;
#       else
            CLK_SET_OUT_TO_P54_FA;
#       endif
        CLK_OUT_SET_DIV_FA(ECBM_SYSCLK_OUT_SETTING_FA);
#   endif
#endif
//--------------设置确认---------------//
    EA_ENABLE;//打开总中断。
#if ((ECBM_MCU_CHECK_EN)&&(ECBM_UART_PRINTF_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_UART1_EN))
    delay_ms(500);
    system_check();
#endif
}
/*---------------------------------其他非系统函数---------------------------------*/
/**********************************str系列函数************************/#if ECBM_STRING_EN
/*-------------------------------------------------------
字符串查找函数。
-------------------------------------------------------*/
u16 str_find(char * dest,char * key){
    u16 key_count=0,key_first=0,count=0;
    while(*dest){    //判断目标字符串。
        if(key[key_count]==(*dest)){//假如关键词字符串当前位比对成功，
            key_count++;            //那么就比较下一位。
        }else if(key[0]==(*dest)){	//假如当前位没有对比成功，就看看是不是要从头开始对比。
			key_count=1;			//从头对比成功，说明再次找到了疑似的关键词，那么下次就从第二个开始对比。
        }else{                      //假如没有比对成功，
            key_count=0;            //那么就从头开始比对。
        }
		count++;    				//记录循环的次数，用于计算关键词出现的位置。
        dest++;                     //读取目标字符串的下一位。
        if(key[key_count]==0){      //如果关键词字符串比对完，
            return (count-key_count);//返回关键词字符串第一次出现的位置。
        } 
    }
    return 0xffff;//能运行到这一步，说明直到目标字符串结束都没有比对成功，返回-1。
}
/*-------------------------------------------------------
IO信息读取函数。
-------------------------------------------------------*/
u8 str_read_pin(char * str,u16 pos){
    u8  dat=0,offset,count; //从左往右依次是读取的信息、字符串偏移和字数统计。
    count=0;                //字数统计清零。
    for(offset=0;offset<10;offset++){//预留10个偏移量。
        if((str[pos+offset]>='0')&&(str[pos+offset]<='7')){//IO口的编号都是从0~7。
            count++;                            //在这个范围内，字数+1。
            if(count==1){                       //如果是第一个数，
                dat=(str[pos+offset]-'0')<<4;   //解析出来放到高4位。
            }
            if(count==2){                       //如果是第二个数，
                dat=(str[pos+offset]-'0')|dat;  //解析出来放到低4位。
                return dat;                     //返回该值。
            }
        }
        if((str[pos+offset]>='8')&&(str[pos+offset]<='9')){//如果是8和9，那么只增加字数，不写入值。
            count++;
        }
        if(str[pos+offset]==',')break;//遇到逗号就退出。
        if(str[pos+offset]==0)break;  //字符串结束也退出。
    }
    return dat;
}
/*-------------------------------------------------------
u16变量读取函数。
-------------------------------------------------------*/
u16 str_read_u16(char * str,u16 pos){
    u16 dat=0; //读取的信息。
    u8  offset;//字符串偏移。
    for(offset=0;offset<20;offset++){//预留20个字符的偏移。
        if((str[pos+offset]>='0')&&(str[pos+offset]<='9')){//数字都是从0~9。
            dat*=10;                  //变量增加一位，即原来是12，就变成120，空出的个数就拿来装新的数。
            dat+=str[pos+offset]-'0'; //将新的数加到个位上。
        }
        if(str[pos+offset]==',')break;//遇到逗号就退出。
        if(str[pos+offset]=='.')break;//遇到点号就退出。
        if(str[pos+offset]==0)break;  //字符串结束也退出。
    }
    return dat;
}
/*-------------------------------------------------------
字符串推出指令函数（带字符串长度参数版）。
-------------------------------------------------------*/
u8 str_push_len(u8 * dest,u16 dlen,u8 * key,u16 klen){
    u16 i,j=0,start=0,stop=0;
    for(i=0;i<dlen;i++){        //从头开始，直到指定的长度。
        if(dest[i]==key[j]){    //把当前的字符和关键词比较成功，
            j++;                //取关键词的下一个字。
            if(j==klen){        //当关键词全部比对完成的时候。
                stop=i;            //保存【结束位置】。
                break;            //退出循环。
            }
        }else{                    //如果当前的字符和关键词比较失败，
            j=0;                //下一次从头开始比对。
            start=i+1;            //更新【开始位置】为下一位（因为当前位失败了）。
        }
    }
    if(start<=stop){            //当比对成功的时候，【开始位置】肯定小于等于【结束位置】。
        for(i=start;i<stop;i++){//将从【开始位置】到【结束位置】之间的缓存全清零。
            dest[i]=0;
        }
        return 1;                //返回推出成功。
    }else{
        return 0;                //返回推出失败。
    }
}
/*****************************************************************************/#endif
