#include "ecbm_core.h"//统一加载核心头文件
#if ECBM_UART_LIB_EN  //检查本库有没有被使能
/*--------------------------------------变量定义-----------------------------------*/
#if ECBM_UART1_EN
bit uart1_busy;
    #if (ECBM_MCU == 0x310201)||(ECBM_MCU == 0x3102A1)
        u8 code uart1_io_map[3][2]={
            {D30,D31},
            {D32,D33},
            {D54,D55},
        };
    #else
        u8 code uart1_io_map[4][2]={
            {D30,D31},
            {D36,D37},
            {D16,D17},
            {D43,D44},
        };
    #endif
#endif
#if ECBM_UART2_EN
bit uart2_busy;
    #if    ((ECBM_MCU&0xF00000)<=0x200000)
        u8 code uart2_io_map[2][2]={
            {D10,D11},
            {D40,D42},
        };
    #else
        u8 code uart2_io_map[2][2]={
            {D10,D11},
            {D46,D47},
        };        
    #endif
#endif
#if ECBM_UART3_EN
bit uart3_busy;
u8 code uart3_io_map[2][2]={
    {D00,D01},
    {D50,D51},
};
#endif
#if ECBM_UART4_EN
bit uart4_busy;
u8 code uart4_io_map[2][2]={
    {D02,D03},
    {D52,D53},
};
#endif
/*------------------------------------资源冲突警告---------------------------------*/
//------------------------------------校验部分警告---------------------------------//
#if ECBM_UART1_EN    ==    1
#if            (ECBM_UART1_PARITY!=0)                    //若打开了校验，
    #if        ((ECBM_UART1_SCON_CONFIG&0x80)!=0x80)    //但是没有设置成9位数据。
    #error    若想开启串口1的校验功能，请把工作模式设置为9位！
    #endif
#else                                                //若没有打开校验或者多机通信，
    #if        ((ECBM_UART1_SCON_CONFIG&0x80)==0x80)&&((ECBM_UART1_SCON_CONFIG&0x20)==0)    //却设置成了9位数据。
    #warning    串口1当前没有开启校验或者多机通信功能，请留意一下工作模式是否一定设置为9位。
    #endif
#endif
#endif

#if ECBM_UART2_EN    ==    1
#if            (ECBM_UART2_PARITY!=0)                    //若打开了校验，
    #if        ((ECBM_UART2_S2CON_CONFIG&0x80)!=0x80)    //但是没有设置成9位数据。
    #error    若想开启串口2的校验功能，请把工作模式设置为9位！
    #endif
#else                                                //若没有打开校验或者多机通信，
    #if        ((ECBM_UART2_S2CON_CONFIG&0x80)==0x80)&&((ECBM_UART2_S2CON_CONFIG&0x20)==0)    //却设置成了9位数据。
    #warning    串口2当前没有开启校验或者多机通信功能，请留意一下工作模式是否一定设置为9位。
    #endif
#endif
#endif

#if ECBM_UART3_EN    ==    1
#if            (ECBM_UART3_PARITY!=0)                    //若打开了校验，
    #if        ((ECBM_UART3_S3CON_CONFIG&0x80)!=0x80)    //但是没有设置成9位数据。
    #error    若想开启串口3的校验功能，请把工作模式设置为9位！
    #endif
#else                                                //若没有打开校验或者多机通信，
    #if        ((ECBM_UART3_S3CON_CONFIG&0x80)==0x80)&&((ECBM_UART3_S3CON_CONFIG&0x20)==0)    //却设置成了9位数据。
    #warning    串口3当前没有开启校验或者多机通信功能，请留意一下工作模式是否一定设置为9位。
    #endif
#endif
#endif

#if ECBM_UART4_EN    ==    1
#if            (ECBM_UART4_PARITY!=0)                    //若打开了校验，
    #if        ((ECBM_UART4_S4CON_CONFIG&0x80)!=0x80)    //但是没有设置成9位数据。
    #error    若想开启串口4的校验功能，请把工作模式设置为9位！
    #endif
#else                                                //若没有打开校验或者多机通信，
    #if        ((ECBM_UART4_S4CON_CONFIG&0x80)==0x80)&&((ECBM_UART4_S4CON_CONFIG&0x20)==0)    //却设置成了9位数据。
    #warning    串口4当前没有开启校验或者多机通信功能，请留意一下工作模式是否一定设置为9位。
    #endif
#endif
#endif
//----------------------------------多机通信部分警告-------------------------------//
#if    (ECBM_UART1_SCON_CONFIG&0x20)&&((ECBM_UART1_SCON_CONFIG&0x80)==0)
#error 若开启串口1的多机通信功能，请把工作模式设置为9位！
#endif
#if    (ECBM_UART2_S2CON_CONFIG&0x20)&&((ECBM_UART2_S2CON_CONFIG&0x80)==0)
#error 若开启串口2的多机通信功能，请把工作模式设置为9位！
#endif
#if    (ECBM_UART3_S3CON_CONFIG&0x20)&&((ECBM_UART3_S3CON_CONFIG&0x80)==0)
#error 若开启串口3的多机通信功能，请把工作模式设置为9位！
#endif
#if    (ECBM_UART4_S4CON_CONFIG&0x20)&&((ECBM_UART4_S4CON_CONFIG&0x80)==0)
#error 若开启串口4的多机通信功能，请把工作模式设置为9位！
#endif
//------------------------------------串口数量警告---------------------------------//
#if    (ECBM_UART2_EN == 1)&&((ECBM_MCU&0x00000F)<0x000002)
#error 当前单片机型号不支持串口2，请更换型号或者关闭串口2。
#endif
#if    (ECBM_UART3_EN == 1)&&((ECBM_MCU&0x00000F)<0x000003)
#error 当前单片机型号不支持串口3，请更换型号或者关闭串口3。
#endif
#if    (ECBM_UART4_EN == 1)&&((ECBM_MCU&0x00000F)<0x000004)
#error 当前单片机型号不支持串口4，请更换型号或者关闭串口4。
#endif
//----------------------------------和定时器冲突警告-------------------------------//
#if    (ECBM_UART1_EN == 1)&&((ECBM_UART1_AUXR_CONFIG&0x01) == 0x01)&&(ECBM_UART2_EN == 1)
#if    ECBM_UART1_BAUD_RATE != ECBM_UART2_BAUD_RATE
#error 串口1和串口2的波特率产生器（定时器2）冲突。请更换串口1的波特率产生器或者将串口1和串口2的波特率调成一致。
#endif
#endif
#if    (ECBM_UART1_EN == 1)&&((ECBM_UART1_AUXR_CONFIG&0x01) == 0x01)&&(ECBM_UART3_EN == 1)&&((ECBM_UART3_S3CON_CONFIG&0x40)==0x00)
#if    ECBM_UART1_BAUD_RATE != ECBM_UART3_BAUD_RATE
#error 串口1和串口3的波特率产生器（定时器2）冲突。请更换串口1或串口3的波特率产生器或者将串口1和串口3的波特率调成一致。
#endif
#endif
#if    (ECBM_UART1_EN == 1)&&((ECBM_UART1_AUXR_CONFIG&0x01) == 0x01)&&(ECBM_UART4_EN == 1)&&((ECBM_UART4_S4CON_CONFIG&0x40)==0x00)
#if    ECBM_UART1_BAUD_RATE != ECBM_UART4_BAUD_RATE
#error 串口1和串口4的波特率产生器（定时器2）冲突。请更换串口1或串口4的波特率产生器或者将串口1和串口4的波特率调成一致。
#endif
#endif
#if    (ECBM_UART2_EN == 1)&&(ECBM_UART3_EN == 1)&&((ECBM_UART3_S3CON_CONFIG&0x40)==0x00)
#if    ECBM_UART2_BAUD_RATE != ECBM_UART3_BAUD_RATE
#error 串口2和串口3的波特率产生器（定时器2）冲突。请更换串口3的波特率产生器或者将串口2和串口3的波特率调成一致。
#endif
#endif
#if    (ECBM_UART2_EN == 1)&&(ECBM_UART4_EN == 1)&&((ECBM_UART4_S4CON_CONFIG&0x40)==0x00)
#if    ECBM_UART2_BAUD_RATE != ECBM_UART4_BAUD_RATE
#error 串口2和串口4的波特率产生器（定时器2）冲突。请更换串口4的波特率产生器或者将串口2和串口4的波特率调成一致。
#endif
#endif
#if    (ECBM_UART3_EN == 1)&&((ECBM_UART3_S3CON_CONFIG&0x40)==0x00)&&(ECBM_UART4_EN == 1)&&((ECBM_UART4_S4CON_CONFIG&0x40)==0x00)
#if    ECBM_UART3_BAUD_RATE != ECBM_UART4_BAUD_RATE
#error 串口3和串口4的波特率产生器（定时器2）冲突。请更换串口3或串口4的波特率产生器或者将串口3和串口4的波特率调成一致。
#endif
#endif



#if     (ECBM_STREAM_EN == 1)
#   if  (ECBM_STREAM_UART == 1)&&(ECBM_UART1_EN == 0)
#       error  串口1的使能没有打开，不能把STREAM安装到串口1！
#   endif
#   if (ECBM_STREAM_UART == 2)&&(ECBM_UART2_EN == 0)
#       error  串口2的使能没有打开，不能把STREAM安装到串口2！
#   endif
#   if (ECBM_STREAM_UART == 3)&&(ECBM_UART3_EN == 0)
#       error  串口3的使能没有打开，不能把STREAM安装到串口3！
#   endif
#   if (ECBM_STREAM_UART == 4)&&(ECBM_UART4_EN == 0)
#       error  串口4的使能没有打开，不能把STREAM安装到串口4！
#   endif
#endif


/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
串口初始化函数。
-------------------------------------------------------*/
void uart_init(void){
#if ECBM_UART1_EN == 1    //当串口1功能使能的时候。
    UART1_SET_REG_SCON  (ECBM_UART1_SCON_CONFIG);   //写入SCON配置，包含工作模式、接收使能、多机通信的选项。
    UART1_SET_REG_PCON  (ECBM_UART1_PCON_CONFIG);   //写入PCON配置，包含波特率加倍。
    UART1_SET_REG_AUXR  (ECBM_UART1_AUXR_CONFIG);   //写入AUXR配置，包含加倍控制、波特率发生器选择。
    uart_set_io         (1,ECBM_UART1_IO);          //写入IO选择控制位。
    uart_set_baud       (1,ECBM_UART1_BAUD_RATE);   //设置波特率。
    #if (ECBM_UART1_SCON_CONFIG&0x20)               //如果打开了多机通信功能，
    UART1_SET_REG_SADDR (ECBM_UART1_SADDR_CONFIG);  //写入从机地址。
    UART1_SET_REG_SADEN (ECBM_UART1_SADEN_CONFIG);  //写入从机地址使能位。
    #endif
    #if (ECBM_UART1_AUXR_CONFIG&0x01) == 0            //如果选择了定时器1，
    TIMER1_SET_MODE_1T;     //设定定时器1为1T模式，
    TIMER1_SET_REG_TMOD(0); //设定定时器1为16位自动重装方式，目前这样设置已经能满足常用的波特率了。
    TIMER1_IT_DISABLE;      //禁止定时器1中断。
    TIMER1_POWER_ON;        //启动定时器1。
    #else                   //如果选择了定时器2，
    TIMER2_SET_MODE_1T;     //设定定时器2为1T模式。
    TIMER2_IT_DISABLE;      //禁止定时器2中断。
    TIMER2_POWER_ON;        //启动定时器2。
    #endif
    uart1_busy=0;           //串口1忙标志位清0。
    UART1_IT_ENABLE;        //打开串口1中断。
#endif

#if ECBM_UART2_EN == 1   //当串口2功能使能的时候。
    UART2_SET_REG_S2CON (ECBM_UART2_S2CON_CONFIG);  //写入S2CON配置,包含了通信位数、接收允许、多机通信。
    uart_set_io         (2,ECBM_UART2_IO);          //写入IO选择控制位。
    uart_set_baud       (2,ECBM_UART2_BAUD_RATE);   //设置波特率。
    TIMER2_SET_MODE_1T; //定时器2时钟为Fosc,即1T。
    TIMER2_IT_DISABLE;  //禁止定时器2中断。
    TIMER2_POWER_ON;    //启动定时器2。
    uart2_busy=0;       //串口2忙标志位清0。
    UART2_IT_ENABLE;    //打开串口2中断。
#endif
    
#if ECBM_UART3_EN == 1   //当串口3功能使能的时候。
    UART3_SET_REG_S3CON (ECBM_UART3_S3CON_CONFIG);  //写入S3CON配置,包含了通信位数、接收允许、多机通信、波特率产生器选择。
    uart_set_io         (3,ECBM_UART3_IO);          //写入IO选择控制位。
    uart_set_baud       (3,ECBM_UART3_BAUD_RATE);   //设置波特率。
    #if (ECBM_UART3_S3CON_CONFIG&0x40)==0
    TIMER2_SET_MODE_1T; //定时器2时钟为Fosc,即1T。
    TIMER2_IT_DISABLE;  //禁止定时器2中断。
    TIMER2_POWER_ON;    //启动定时器2。
    #else
    TIMER3_SET_MODE_1T; //定时器3时钟为Fosc,即1T。
    TIMER3_IT_DISABLE;  //禁止定时器3中断。
    TIMER3_POWER_ON;    //启动定时器3。
    #endif
    uart3_busy=0;       //串口3忙标志位清0。
    UART3_IT_ENABLE;    //打开串口3中断。
#endif
    
#if ECBM_UART4_EN == 1   //当串口4功能使能的时候。
    UART4_SET_REG_S4CON (ECBM_UART4_S4CON_CONFIG);  //写入S4CON配置,包含了通信位数、接收允许、多机通信、波特率产生器选择。
    uart_set_io         (4,ECBM_UART4_IO);          //写入IO选择控制位。
    uart_set_baud       (4,ECBM_UART4_BAUD_RATE);   //设置波特率。
    #if (ECBM_UART4_S4CON_CONFIG&0x40)==0
    TIMER2_SET_MODE_1T; //定时器2时钟为Fosc,即1T。
    TIMER2_IT_DISABLE;  //禁止定时器2中断。
    TIMER2_POWER_ON;    //启动定时器2。
    #else
    TIMER4_SET_MODE_1T; //定时器4时钟为Fosc,即1T。
    TIMER4_IT_DISABLE;  //禁止定时器4中断。
    TIMER4_POWER_ON;    //启动定时器4。
    #endif
    uart4_busy=0;       //串口4忙标志位清0。
    UART4_IT_ENABLE;    //打开串口4中断。
#endif

#if ECBM_STREAM_EN == 1
    #if     ECBM_STREAM_TIMER == 0
        TIMER0_SET_MODE_12T;
        TIMER0_SET_REG_HL(65536-(u16)(10000.0f*((float)ECBM_SYSCLK_SETTING/12.0f/1000000.0f)));
        TIMER0_SET_MODE_TIMER;
        TIMER0_IT_ENABLE;
        TIMER0_POWER_ON;
    #elif   ECBM_STREAM_TIMER == 1
        TIMER1_SET_MODE_12T;
        TIMER1_SET_REG_HL(65536-(u16)(10.0f*((float)ECBM_SYSCLK_SETTING/12.0f/1000.0f)));
        TIMER1_SET_MODE_TIMER;
        TIMER1_IT_ENABLE;
        TIMER1_POWER_ON;
    #elif   ECBM_STREAM_TIMER == 2
        TIMER2_SET_MODE_12T;
        TIMER2_SET_REG_HL(65536-(u16)(10.0f*((float)ECBM_SYSCLK_SETTING/12.0f/1000.0f)));
        TIMER2_SET_MODE_TIMER;
        TIMER2_IT_ENABLE;
        TIMER2_POWER_ON;
    #elif   ECBM_STREAM_TIMER == 3
        TIMER3_SET_MODE_12T;
        TIMER3_SET_REG_HL(65536-(u16)(10.0f*((float)ECBM_SYSCLK_SETTING/12.0f/1000.0f)));
        TIMER3_SET_MODE_TIMER;
        TIMER3_IT_ENABLE;
        TIMER3_POWER_ON;
    #elif   ECBM_STREAM_TIMER == 4
        TIMER4_SET_MODE_12T;
        TIMER4_SET_REG_HL(65536-(u16)(10.0f*((float)ECBM_SYSCLK_SETTING/12.0f/1000.0f)));
        TIMER4_SET_MODE_TIMER;
        TIMER4_IT_ENABLE;
        TIMER4_POWER_ON;
    #endif
#endif
}
/*-------------------------------------------------------
串口输出IO设置函数。
-------------------------------------------------------*/
void uart_set_io(u8 id,u8 io){
    switch(id){
        #if ECBM_UART1_EN
        case 1:{
            UART1_SET_PIN(io);
            gpio_mode(uart1_io_map[io>>6][0],GPIO_IN);
            gpio_mode(uart1_io_map[io>>6][1],GPIO_OUT);
        }break;
        #endif
        #if ECBM_UART2_EN
        case 2:{
            UART2_SET_PIN(io);
            gpio_mode(uart2_io_map[io][0],GPIO_IN);
            gpio_mode(uart2_io_map[io][1],GPIO_OUT);
        }break;
        #endif
        #if ECBM_UART3_EN
        case 3:{
            UART3_SET_PIN(io);
            gpio_mode(uart3_io_map[io>>1][0],GPIO_IN);
            gpio_mode(uart3_io_map[io>>1][1],GPIO_OUT);
        }break;
        #endif
        #if ECBM_UART4_EN
        case 4:{
            UART4_SET_PIN(io);
            gpio_mode(uart4_io_map[io>>2][0],GPIO_IN);
            gpio_mode(uart4_io_map[io>>2][1],GPIO_OUT);
        }break;
        #endif
    }
}
/*-------------------------------------------------------
串口波特率设置函数。
-------------------------------------------------------*/
void uart_set_baud(u8 id,u32 baud){
    u16 res;
    res=(u16)(65536-(u16)(ECBM_SYSCLK_SETTING/4/baud));//通过波特率设置定时器初值。
    switch(id){
        #if ECBM_UART1_EN == 1       //当串口1功能使能的时候。
        case 1:{
            #if (ECBM_UART1_AUXR_CONFIG&0x01) == 0//如果选择了定时器1，
            TIMER1_SET_REG_HL(res); //设定定时初值。
            #else               //如果选择了定时器2，
            TIMER2_SET_REG_HL(res); //设定定时初值。
            #endif
        }break;
        #endif
        #if ECBM_UART2_EN == 1   //当串口2功能使能的时候。
        case 2:{
            TIMER2_SET_REG_HL(res);    //设定定时初值。
        }break;
        #endif
        #if ECBM_UART3_EN == 1   //当串口3功能使能的时候。
        case 3:{
            #if (ECBM_UART3_S3CON_CONFIG&0x40)==0
            TIMER2_SET_REG_HL(res); //设定定时初值。
            #else
            TIMER3_SET_REG_HL(res);    //设定定时初值。
            #endif
        }break;
        #endif
        #if ECBM_UART4_EN == 1   //当串口4功能使能的时候。
        case 4:{
            #if (ECBM_UART4_S4CON_CONFIG&0x40)==0
            TIMER2_SET_REG_HL(res);    //设定定时初值。
            #else
            TIMER4_SET_REG_HL(res);    //设定定时初值。
            #endif
        }break;
        #endif
    }
}
/*-------------------------------------------------------
串口单个字节发送函数。
-------------------------------------------------------*/
void uart_char(u8 id,u8 ch){
    switch(id){
        #if ECBM_UART1_EN
        case 1:{
            #if   ECBM_UART1_PARITY == 1
            IF_ODD(ch){
                UART1_SET_TXD_BYTE9_0;
            }else{
                UART1_SET_TXD_BYTE9_1;
            }
            #elif ECBM_UART1_PARITY == 2
            IF_ODD(ch){
                UART1_SET_TXD_BYTE9_1;
            }else{
                UART1_SET_TXD_BYTE9_0;
            }
            #elif ECBM_UART1_PARITY == 3
            UART1_SET_TXD_BYTE9_1;
            #elif ECBM_UART1_PARITY == 4
            UART1_SET_TXD_BYTE9_0;
            #endif
            UART1_SET_REG_SBUF(ch);
            uart1_busy=1;
            while(uart1_busy);
        }break;
        #endif
        #if ECBM_UART2_EN
        case 2:{
            #if   ECBM_UART2_PARITY == 1
            IF_ODD(ch){
                UART2_SET_TXD_BYTE9_0;
            }else{
                UART2_SET_TXD_BYTE9_1;
            }
            #elif ECBM_UART2_PARITY == 2
            IF_ODD(ch){
                UART2_SET_TXD_BYTE9_1;
            }else{
                UART2_SET_TXD_BYTE9_0;
            }    
            #elif ECBM_UART2_PARITY == 3
            UART2_SET_TXD_BYTE9_1;
            #elif ECBM_UART2_PARITY == 4
            UART2_SET_TXD_BYTE9_0;
            #endif
            UART2_SET_REG_S2BUF(ch);
            uart2_busy=1;
            while(uart2_busy);
        }break;
        #endif
        #if ECBM_UART3_EN
        case 3:{
            #if   ECBM_UART3_PARITY == 1
            IF_ODD(ch){
                UART3_SET_TXD_BYTE9_0;
            }else{
                UART3_SET_TXD_BYTE9_1;
            }
            #elif ECBM_UART3_PARITY == 2
            IF_ODD(ch){
                UART3_SET_TXD_BYTE9_1;
            }else{
                UART3_SET_TXD_BYTE9_0;
            }    
            #elif ECBM_UART3_PARITY == 3
            UART3_SET_TXD_BYTE9_1;
            #elif ECBM_UART3_PARITY == 4
            UART3_SET_TXD_BYTE9_0;
            #endif
            UART3_SET_REG_S3BUF(ch);
            uart3_busy=1;
            while(uart3_busy);
        }break;
        #endif
        #if ECBM_UART4_EN
        case 4:{
            #if   ECBM_UART4_PARITY == 1
            IF_ODD(ch){
                UART4_SET_TXD_BYTE9_0;
            }else{
                UART4_SET_TXD_BYTE9_1;
            }
            #elif ECBM_UART4_PARITY == 2
            IF_ODD(ch){
                UART4_SET_TXD_BYTE9_1;
            }else{
                UART4_SET_TXD_BYTE9_0;
            }    
            #elif ECBM_UART4_PARITY == 3
            UART4_SET_TXD_BYTE9_1;
            #elif ECBM_UART4_PARITY == 4
            UART4_SET_TXD_BYTE9_0;
            #endif
            UART4_SET_REG_S4BUF(ch);
            uart4_busy=1;
            while(uart4_busy);
        }break;
        #endif
    }    
}
/*-------------------------------------------------------
9位模式下的字符发送函数。
-------------------------------------------------------*/
void uart_char_9(u8 id,u8 ch,u8 bit9){
    switch(id){
        #if ECBM_UART1_EN
        case 1:{
            if(bit9){
                UART1_SET_TXD_BYTE9_1;
            }else{
                UART1_SET_TXD_BYTE9_0;
            }
            UART1_SET_REG_SBUF(ch);
            uart1_busy=1;
            while(uart1_busy);
        }break;
        #endif
        #if ECBM_UART2_EN
        case 2:{
            if(bit9){
                UART2_SET_TXD_BYTE9_1;
            }else{
                UART2_SET_TXD_BYTE9_0;
            }
            UART2_SET_REG_S2BUF(ch);
            uart2_busy=1;
            while(uart2_busy);
        }break;
        #endif
        #if ECBM_UART3_EN
        case 3:{
            if(bit9){
                UART3_SET_TXD_BYTE9_1;
            }else{
                UART3_SET_TXD_BYTE9_0;
            }
            UART3_SET_REG_S3BUF(ch);
            uart3_busy=1;
            while(uart3_busy);
        }break;
        #endif
        #if ECBM_UART4_EN
        case 4:{
            if(bit9){
                UART4_SET_TXD_BYTE9_1;
            }else{
                UART4_SET_TXD_BYTE9_0;
            }
            UART4_SET_REG_S4BUF(ch);
            uart4_busy=1;
            while(uart4_busy);
        }break;
        #endif
    }
}
/*-------------------------------------------------------
串口字符串发送函数。
-------------------------------------------------------*/
void uart_string(u8 id,u8 * str){
    while(*str){
        uart_char(id,*str++);
    }    
}
/*-------------------------------------------------------
串口打印函数。
-------------------------------------------------------*/
#if    ECBM_UART_PRINTF_EN    ==    1
void uart_printf(u8 id,const char * str,...){
    char xdata buf[ECBM_UART_PRINTF_BUF_MAX];
    va_list vp;
    va_start(vp, str);
    
    vsprintf(buf,str,vp);
    va_end(vp);
    uart_string(id,buf);
}
#endif
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。