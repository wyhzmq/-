#include "ecbm_core.h"//ͳһ���غ���ͷ�ļ�
#if ECBM_UART_LIB_EN  //��鱾����û�б�ʹ��
/*--------------------------------------��������-----------------------------------*/
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
/*------------------------------------��Դ��ͻ����---------------------------------*/
//------------------------------------У�鲿�־���---------------------------------//
#if ECBM_UART1_EN    ==    1
#if            (ECBM_UART1_PARITY!=0)                    //������У�飬
    #if        ((ECBM_UART1_SCON_CONFIG&0x80)!=0x80)    //����û�����ó�9λ���ݡ�
    #error    ���뿪������1��У�鹦�ܣ���ѹ���ģʽ����Ϊ9λ��
    #endif
#else                                                //��û�д�У����߶��ͨ�ţ�
    #if        ((ECBM_UART1_SCON_CONFIG&0x80)==0x80)&&((ECBM_UART1_SCON_CONFIG&0x20)==0)    //ȴ���ó���9λ���ݡ�
    #warning    ����1��ǰû�п���У����߶��ͨ�Ź��ܣ�������һ�¹���ģʽ�Ƿ�һ������Ϊ9λ��
    #endif
#endif
#endif

#if ECBM_UART2_EN    ==    1
#if            (ECBM_UART2_PARITY!=0)                    //������У�飬
    #if        ((ECBM_UART2_S2CON_CONFIG&0x80)!=0x80)    //����û�����ó�9λ���ݡ�
    #error    ���뿪������2��У�鹦�ܣ���ѹ���ģʽ����Ϊ9λ��
    #endif
#else                                                //��û�д�У����߶��ͨ�ţ�
    #if        ((ECBM_UART2_S2CON_CONFIG&0x80)==0x80)&&((ECBM_UART2_S2CON_CONFIG&0x20)==0)    //ȴ���ó���9λ���ݡ�
    #warning    ����2��ǰû�п���У����߶��ͨ�Ź��ܣ�������һ�¹���ģʽ�Ƿ�һ������Ϊ9λ��
    #endif
#endif
#endif

#if ECBM_UART3_EN    ==    1
#if            (ECBM_UART3_PARITY!=0)                    //������У�飬
    #if        ((ECBM_UART3_S3CON_CONFIG&0x80)!=0x80)    //����û�����ó�9λ���ݡ�
    #error    ���뿪������3��У�鹦�ܣ���ѹ���ģʽ����Ϊ9λ��
    #endif
#else                                                //��û�д�У����߶��ͨ�ţ�
    #if        ((ECBM_UART3_S3CON_CONFIG&0x80)==0x80)&&((ECBM_UART3_S3CON_CONFIG&0x20)==0)    //ȴ���ó���9λ���ݡ�
    #warning    ����3��ǰû�п���У����߶��ͨ�Ź��ܣ�������һ�¹���ģʽ�Ƿ�һ������Ϊ9λ��
    #endif
#endif
#endif

#if ECBM_UART4_EN    ==    1
#if            (ECBM_UART4_PARITY!=0)                    //������У�飬
    #if        ((ECBM_UART4_S4CON_CONFIG&0x80)!=0x80)    //����û�����ó�9λ���ݡ�
    #error    ���뿪������4��У�鹦�ܣ���ѹ���ģʽ����Ϊ9λ��
    #endif
#else                                                //��û�д�У����߶��ͨ�ţ�
    #if        ((ECBM_UART4_S4CON_CONFIG&0x80)==0x80)&&((ECBM_UART4_S4CON_CONFIG&0x20)==0)    //ȴ���ó���9λ���ݡ�
    #warning    ����4��ǰû�п���У����߶��ͨ�Ź��ܣ�������һ�¹���ģʽ�Ƿ�һ������Ϊ9λ��
    #endif
#endif
#endif
//----------------------------------���ͨ�Ų��־���-------------------------------//
#if    (ECBM_UART1_SCON_CONFIG&0x20)&&((ECBM_UART1_SCON_CONFIG&0x80)==0)
#error ����������1�Ķ��ͨ�Ź��ܣ���ѹ���ģʽ����Ϊ9λ��
#endif
#if    (ECBM_UART2_S2CON_CONFIG&0x20)&&((ECBM_UART2_S2CON_CONFIG&0x80)==0)
#error ����������2�Ķ��ͨ�Ź��ܣ���ѹ���ģʽ����Ϊ9λ��
#endif
#if    (ECBM_UART3_S3CON_CONFIG&0x20)&&((ECBM_UART3_S3CON_CONFIG&0x80)==0)
#error ����������3�Ķ��ͨ�Ź��ܣ���ѹ���ģʽ����Ϊ9λ��
#endif
#if    (ECBM_UART4_S4CON_CONFIG&0x20)&&((ECBM_UART4_S4CON_CONFIG&0x80)==0)
#error ����������4�Ķ��ͨ�Ź��ܣ���ѹ���ģʽ����Ϊ9λ��
#endif
//------------------------------------������������---------------------------------//
#if    (ECBM_UART2_EN == 1)&&((ECBM_MCU&0x00000F)<0x000002)
#error ��ǰ��Ƭ���ͺŲ�֧�ִ���2��������ͺŻ��߹رմ���2��
#endif
#if    (ECBM_UART3_EN == 1)&&((ECBM_MCU&0x00000F)<0x000003)
#error ��ǰ��Ƭ���ͺŲ�֧�ִ���3��������ͺŻ��߹رմ���3��
#endif
#if    (ECBM_UART4_EN == 1)&&((ECBM_MCU&0x00000F)<0x000004)
#error ��ǰ��Ƭ���ͺŲ�֧�ִ���4��������ͺŻ��߹رմ���4��
#endif
//----------------------------------�Ͷ�ʱ����ͻ����-------------------------------//
#if    (ECBM_UART1_EN == 1)&&((ECBM_UART1_AUXR_CONFIG&0x01) == 0x01)&&(ECBM_UART2_EN == 1)
#if    ECBM_UART1_BAUD_RATE != ECBM_UART2_BAUD_RATE
#error ����1�ʹ���2�Ĳ����ʲ���������ʱ��2����ͻ�����������1�Ĳ����ʲ��������߽�����1�ʹ���2�Ĳ����ʵ���һ�¡�
#endif
#endif
#if    (ECBM_UART1_EN == 1)&&((ECBM_UART1_AUXR_CONFIG&0x01) == 0x01)&&(ECBM_UART3_EN == 1)&&((ECBM_UART3_S3CON_CONFIG&0x40)==0x00)
#if    ECBM_UART1_BAUD_RATE != ECBM_UART3_BAUD_RATE
#error ����1�ʹ���3�Ĳ����ʲ���������ʱ��2����ͻ�����������1�򴮿�3�Ĳ����ʲ��������߽�����1�ʹ���3�Ĳ����ʵ���һ�¡�
#endif
#endif
#if    (ECBM_UART1_EN == 1)&&((ECBM_UART1_AUXR_CONFIG&0x01) == 0x01)&&(ECBM_UART4_EN == 1)&&((ECBM_UART4_S4CON_CONFIG&0x40)==0x00)
#if    ECBM_UART1_BAUD_RATE != ECBM_UART4_BAUD_RATE
#error ����1�ʹ���4�Ĳ����ʲ���������ʱ��2����ͻ�����������1�򴮿�4�Ĳ����ʲ��������߽�����1�ʹ���4�Ĳ����ʵ���һ�¡�
#endif
#endif
#if    (ECBM_UART2_EN == 1)&&(ECBM_UART3_EN == 1)&&((ECBM_UART3_S3CON_CONFIG&0x40)==0x00)
#if    ECBM_UART2_BAUD_RATE != ECBM_UART3_BAUD_RATE
#error ����2�ʹ���3�Ĳ����ʲ���������ʱ��2����ͻ�����������3�Ĳ����ʲ��������߽�����2�ʹ���3�Ĳ����ʵ���һ�¡�
#endif
#endif
#if    (ECBM_UART2_EN == 1)&&(ECBM_UART4_EN == 1)&&((ECBM_UART4_S4CON_CONFIG&0x40)==0x00)
#if    ECBM_UART2_BAUD_RATE != ECBM_UART4_BAUD_RATE
#error ����2�ʹ���4�Ĳ����ʲ���������ʱ��2����ͻ�����������4�Ĳ����ʲ��������߽�����2�ʹ���4�Ĳ����ʵ���һ�¡�
#endif
#endif
#if    (ECBM_UART3_EN == 1)&&((ECBM_UART3_S3CON_CONFIG&0x40)==0x00)&&(ECBM_UART4_EN == 1)&&((ECBM_UART4_S4CON_CONFIG&0x40)==0x00)
#if    ECBM_UART3_BAUD_RATE != ECBM_UART4_BAUD_RATE
#error ����3�ʹ���4�Ĳ����ʲ���������ʱ��2����ͻ�����������3�򴮿�4�Ĳ����ʲ��������߽�����3�ʹ���4�Ĳ����ʵ���һ�¡�
#endif
#endif



#if     (ECBM_STREAM_EN == 1)
#   if  (ECBM_STREAM_UART == 1)&&(ECBM_UART1_EN == 0)
#       error  ����1��ʹ��û�д򿪣����ܰ�STREAM��װ������1��
#   endif
#   if (ECBM_STREAM_UART == 2)&&(ECBM_UART2_EN == 0)
#       error  ����2��ʹ��û�д򿪣����ܰ�STREAM��װ������2��
#   endif
#   if (ECBM_STREAM_UART == 3)&&(ECBM_UART3_EN == 0)
#       error  ����3��ʹ��û�д򿪣����ܰ�STREAM��װ������3��
#   endif
#   if (ECBM_STREAM_UART == 4)&&(ECBM_UART4_EN == 0)
#       error  ����4��ʹ��û�д򿪣����ܰ�STREAM��װ������4��
#   endif
#endif


/*--------------------------------------������-----------------------------------*/
/*-------------------------------------------------------
���ڳ�ʼ��������
-------------------------------------------------------*/
void uart_init(void){
#if ECBM_UART1_EN == 1    //������1����ʹ�ܵ�ʱ��
    UART1_SET_REG_SCON  (ECBM_UART1_SCON_CONFIG);   //д��SCON���ã���������ģʽ������ʹ�ܡ����ͨ�ŵ�ѡ�
    UART1_SET_REG_PCON  (ECBM_UART1_PCON_CONFIG);   //д��PCON���ã����������ʼӱ���
    UART1_SET_REG_AUXR  (ECBM_UART1_AUXR_CONFIG);   //д��AUXR���ã������ӱ����ơ������ʷ�����ѡ��
    uart_set_io         (1,ECBM_UART1_IO);          //д��IOѡ�����λ��
    uart_set_baud       (1,ECBM_UART1_BAUD_RATE);   //���ò����ʡ�
    #if (ECBM_UART1_SCON_CONFIG&0x20)               //������˶��ͨ�Ź��ܣ�
    UART1_SET_REG_SADDR (ECBM_UART1_SADDR_CONFIG);  //д��ӻ���ַ��
    UART1_SET_REG_SADEN (ECBM_UART1_SADEN_CONFIG);  //д��ӻ���ַʹ��λ��
    #endif
    #if (ECBM_UART1_AUXR_CONFIG&0x01) == 0            //���ѡ���˶�ʱ��1��
    TIMER1_SET_MODE_1T;     //�趨��ʱ��1Ϊ1Tģʽ��
    TIMER1_SET_REG_TMOD(0); //�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ��Ŀǰ���������Ѿ������㳣�õĲ������ˡ�
    TIMER1_IT_DISABLE;      //��ֹ��ʱ��1�жϡ�
    TIMER1_POWER_ON;        //������ʱ��1��
    #else                   //���ѡ���˶�ʱ��2��
    TIMER2_SET_MODE_1T;     //�趨��ʱ��2Ϊ1Tģʽ��
    TIMER2_IT_DISABLE;      //��ֹ��ʱ��2�жϡ�
    TIMER2_POWER_ON;        //������ʱ��2��
    #endif
    uart1_busy=0;           //����1æ��־λ��0��
    UART1_IT_ENABLE;        //�򿪴���1�жϡ�
#endif

#if ECBM_UART2_EN == 1   //������2����ʹ�ܵ�ʱ��
    UART2_SET_REG_S2CON (ECBM_UART2_S2CON_CONFIG);  //д��S2CON����,������ͨ��λ���������������ͨ�š�
    uart_set_io         (2,ECBM_UART2_IO);          //д��IOѡ�����λ��
    uart_set_baud       (2,ECBM_UART2_BAUD_RATE);   //���ò����ʡ�
    TIMER2_SET_MODE_1T; //��ʱ��2ʱ��ΪFosc,��1T��
    TIMER2_IT_DISABLE;  //��ֹ��ʱ��2�жϡ�
    TIMER2_POWER_ON;    //������ʱ��2��
    uart2_busy=0;       //����2æ��־λ��0��
    UART2_IT_ENABLE;    //�򿪴���2�жϡ�
#endif
    
#if ECBM_UART3_EN == 1   //������3����ʹ�ܵ�ʱ��
    UART3_SET_REG_S3CON (ECBM_UART3_S3CON_CONFIG);  //д��S3CON����,������ͨ��λ���������������ͨ�š������ʲ�����ѡ��
    uart_set_io         (3,ECBM_UART3_IO);          //д��IOѡ�����λ��
    uart_set_baud       (3,ECBM_UART3_BAUD_RATE);   //���ò����ʡ�
    #if (ECBM_UART3_S3CON_CONFIG&0x40)==0
    TIMER2_SET_MODE_1T; //��ʱ��2ʱ��ΪFosc,��1T��
    TIMER2_IT_DISABLE;  //��ֹ��ʱ��2�жϡ�
    TIMER2_POWER_ON;    //������ʱ��2��
    #else
    TIMER3_SET_MODE_1T; //��ʱ��3ʱ��ΪFosc,��1T��
    TIMER3_IT_DISABLE;  //��ֹ��ʱ��3�жϡ�
    TIMER3_POWER_ON;    //������ʱ��3��
    #endif
    uart3_busy=0;       //����3æ��־λ��0��
    UART3_IT_ENABLE;    //�򿪴���3�жϡ�
#endif
    
#if ECBM_UART4_EN == 1   //������4����ʹ�ܵ�ʱ��
    UART4_SET_REG_S4CON (ECBM_UART4_S4CON_CONFIG);  //д��S4CON����,������ͨ��λ���������������ͨ�š������ʲ�����ѡ��
    uart_set_io         (4,ECBM_UART4_IO);          //д��IOѡ�����λ��
    uart_set_baud       (4,ECBM_UART4_BAUD_RATE);   //���ò����ʡ�
    #if (ECBM_UART4_S4CON_CONFIG&0x40)==0
    TIMER2_SET_MODE_1T; //��ʱ��2ʱ��ΪFosc,��1T��
    TIMER2_IT_DISABLE;  //��ֹ��ʱ��2�жϡ�
    TIMER2_POWER_ON;    //������ʱ��2��
    #else
    TIMER4_SET_MODE_1T; //��ʱ��4ʱ��ΪFosc,��1T��
    TIMER4_IT_DISABLE;  //��ֹ��ʱ��4�жϡ�
    TIMER4_POWER_ON;    //������ʱ��4��
    #endif
    uart4_busy=0;       //����4æ��־λ��0��
    UART4_IT_ENABLE;    //�򿪴���4�жϡ�
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
�������IO���ú�����
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
���ڲ��������ú�����
-------------------------------------------------------*/
void uart_set_baud(u8 id,u32 baud){
    u16 res;
    res=(u16)(65536-(u16)(ECBM_SYSCLK_SETTING/4/baud));//ͨ�����������ö�ʱ����ֵ��
    switch(id){
        #if ECBM_UART1_EN == 1       //������1����ʹ�ܵ�ʱ��
        case 1:{
            #if (ECBM_UART1_AUXR_CONFIG&0x01) == 0//���ѡ���˶�ʱ��1��
            TIMER1_SET_REG_HL(res); //�趨��ʱ��ֵ��
            #else               //���ѡ���˶�ʱ��2��
            TIMER2_SET_REG_HL(res); //�趨��ʱ��ֵ��
            #endif
        }break;
        #endif
        #if ECBM_UART2_EN == 1   //������2����ʹ�ܵ�ʱ��
        case 2:{
            TIMER2_SET_REG_HL(res);    //�趨��ʱ��ֵ��
        }break;
        #endif
        #if ECBM_UART3_EN == 1   //������3����ʹ�ܵ�ʱ��
        case 3:{
            #if (ECBM_UART3_S3CON_CONFIG&0x40)==0
            TIMER2_SET_REG_HL(res); //�趨��ʱ��ֵ��
            #else
            TIMER3_SET_REG_HL(res);    //�趨��ʱ��ֵ��
            #endif
        }break;
        #endif
        #if ECBM_UART4_EN == 1   //������4����ʹ�ܵ�ʱ��
        case 4:{
            #if (ECBM_UART4_S4CON_CONFIG&0x40)==0
            TIMER2_SET_REG_HL(res);    //�趨��ʱ��ֵ��
            #else
            TIMER4_SET_REG_HL(res);    //�趨��ʱ��ֵ��
            #endif
        }break;
        #endif
    }
}
/*-------------------------------------------------------
���ڵ����ֽڷ��ͺ�����
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
9λģʽ�µ��ַ����ͺ�����
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
�����ַ������ͺ�����
-------------------------------------------------------*/
void uart_string(u8 id,u8 * str){
    while(*str){
        uart_char(id,*str++);
    }    
}
/*-------------------------------------------------------
���ڴ�ӡ������
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
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��