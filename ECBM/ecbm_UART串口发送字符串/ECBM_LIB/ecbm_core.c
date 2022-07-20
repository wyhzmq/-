#include "ecbm_core.h"
/*------------------------------------��Դ��ͻ����---------------------------------*/
#if ECBM_AUTO_DOWNLOAD_EN
#   if ECBM_UART_LIB_EN == 0
#       warning �򴮿ڿ�δʹ��,�Զ����ع���ʧЧ!
#   endif
#   if ECBM_UART1_EN == 0
#       error �Զ����ع����򴮿�1δʹ�ܶ�����ʧ��,��ǰ��uart.hʹ�ܴ���1!
#   endif
#   if ECBM_UART1_IO != 0
#       error �Զ����ع�����Ҫ����1ӳ�䵽P30��P31,��ǰ��uart.h�޸Ĵ���1�����IO!
#   endif
#endif
/*-----------------------------------��ѡģ���趨----------------------------------*/
union{
    u32 num32;
    u16 num16[2];
    u8  num8[4];
}fast_cout;
/*-------------------------------------------------------
���뼶��ʱ����
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
΢�뼶��ʱ���������ģ�
-------------------------------------------------------*/
void delay_us(u16 us){
    u16 i;
    i=us;
	do{}while(--i);
}
/*-------------------------------------------------------
΢�뼶��ʱ�����Ľ��ļ��㺯��
-------------------------------------------------------*/
u16 delay_set_us(u16 us){
//��ʽ����������ʱ��̫������ֳ�����������������������������ʱ����ֵ����������ĺ������á�
    fast_cout.num32=((u32)(ECBM_SYSCLK_SETTING/10000)*(u32)(us))*131;
    return fast_cout.num16[0]>>1;
}
/************************************���ڵ���ģ��***************/#if ((ECBM_AUTO_DOWNLOAD_EN)&&(ECBM_UART_LIB_EN))
/*-------------------------------------------------------
�Զ���������ı��� 
-------------------------------------------------------*/
bit auto_download_en;            //�Զ����ص�ʹ��
u8 data auto_download_old_char;  //������һ�ν��յ�����
u8 data auto_download_char_count;//��ͬ���ݼ���
/*-------------------------------------------------------
�������жϺ���
-------------------------------------------------------*/
void system_uart_reset(){
    if(auto_download_old_char!=UART1_GET_REG_SBUF){ //�ж��ظ��ַ�������ַ����ظ�
        auto_download_old_char=UART1_GET_REG_SBUF;  //�͸���oldchar
        auto_download_char_count=0;                 //����������
    }else{                                          //����ַ��ظ�
        if(auto_download_en)auto_download_char_count++;//���ظ�������+1
    }
    if(auto_download_char_count>=233){              //���յ�233���ظ�����ʱ
        EA_DISABLE;                                 //�Ͽ������ж�
        while(1)POWER_RESET;                        //һֱ��������
    }
}
/****************************************************************************/#endif
/*-------------------------------------------------------
ϵͳ��麯��
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
    uart_printf(1,"ECBM V%bu.%bu.%bu on %s",ECBM_FVN,ECBM_RVN,ECBM_BVN,ECBM_MCU_NAME);//����汾�ź͵�Ƭ���ͺ�
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
        uart_printf(1,"OK\r\nID    :");for(i=0;i<7;i++){uart_printf(1,"%02X",(u16)(MCUID[i]));}uart_printf(1,"\r\n");        //���ΨһID��
        uart_printf(1,"DATA  :128\tByte\r\n");//DATA���̶���128Byte
        uart_printf(1,"IDATA :128\tByte\r\n");//IDATA���̶���128Byte
        uart_printf(1,"XDATA :%u\tByte\r\n",(u16)((ECBM_MCU&0x0F0000)>>16)*1024);//�������ļ��л�ȡXDATA����С
        uart_printf(1,"FLASH :%lu\tByte\r\n",(u32)ECBM_MCU_ROM_SIZE*1024);//�������ļ��л�ȡFLASH����С
        uart_printf(1,"SYSCLK:%lu\tHz\r\n",ECBM_SYSCLK_SETTING);//����ڲ�����ֵ����ͼ�ν���������
        uart_printf(1,"BGV   :%u\tmV\r\n",REG_BGV);//����ڲ���ѹ��׼ֵ����Ҫ��STC-ISP������
        uart_printf(1,"ENDIAN:");
        if(*((char*)(&aaa))==0x12)uart_printf(1,"big\tendian\r\n");
        if(*((char*)(&aaa))==0x34)uart_printf(1,"little\tendian\r\n");
    }    
}
#endif
/*----------------------------------����ϵͳ����-----------------------------------*/
#define SYS_HSI_S 0 //�ڲ�����ʱ��HSI(��׼)
#define SYS_HSI_C 1 //�ڲ�����ʱ��HSI(�Զ���)
#define SYS_LSI   2 //�ڲ�����ʱ��LSI
#define SYS_LSE   3 //�ⲿ����ʱ��LSI
#define SYS_HSE_A 4 //�ⲿ��Դ����
#define SYS_HSE_P 5 //�ⲿ��Դ����
void system_set_clock(u8 source){
    switch(source){
        case SYS_HSI_S:
        case SYS_HSI_C:{
            CLK_HSI_POWER_ON;   //ʹ��HSI�����ڲ�24M��IRC��
            CLK_SET_SOURCE_HSI; //�л���HSI��
            CLK_HSE_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_LSE_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_LSI_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
        }break;
        case SYS_LSI:{
            CLK_LSI_POWER_ON;   //ʹ��LSI�����ڲ�32K��IRC��
            CLK_SET_SOURCE_LSI; //�л���LSI��
            CLK_HSI_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_LSE_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_HSE_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
        }break;
        case SYS_LSE:{
            CLK_LSE_POWER_ON;   //ʹ��LSE�����ⲿ���پ���
            CLK_SET_SOURCE_LSE; //�л���LSE��
            CLK_LSI_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_HSI_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_HSE_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
        }break;
        case SYS_HSE_A:{
            CLK_HSE_A_POWER_ON; //ʹ��HSE����Դ���񣩡�
            CLK_SET_SOURCE_HSE; //�л���HSE��
            CLK_HSI_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_LSE_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_LSI_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
        }break;
        case SYS_HSE_P:{
            CLK_HSE_P_POWER_ON; //ʹ��HSE����Դ���񣩡�
            CLK_SET_SOURCE_HSE; //�л���HSE��
            CLK_HSI_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_LSE_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
            CLK_LSI_POWER_OFF;  //�ر�����ʱ��Դ��ʡ�硣
        }break;
    }
}
void system_set_div(u8 div){
    if(div==0){                 //�ų���0������ȶ�ѡ�
        CLK_SET_REG_CLKDIV(1);  //�������0�Ļ��͸ĳ�1��
    }else{
        CLK_SET_REG_CLKDIV(div);//�������0����ֱ��д��Ĵ�����
    }
}
/*-------------------------------------------------------
�⺯��ϵͳ��ʼ������
-------------------------------------------------------*/
void system_init(void){
    EX_SFR_ENABLE;//�򿪶���ļĴ�����
//---------------�Զ�����--------------//
#if ((ECBM_AUTO_DOWNLOAD_EN)&&(ECBM_UART_LIB_EN))//�жϷ���Ҫ�����Զ����ء�
    auto_download_en=1;         //���Զ�����ʹ��
    auto_download_old_char=0;   //��ʼ��������ر���
    auto_download_char_count=0; //��ʼ��������ر���
    uart_init();
#endif
//-------------����Ӳ������------------//
#if (ECBM_POWER_LIB_EN)&&(ECBM_POWER_RST_CFG_EN)
    power_rstcfg_init();
#endif    
//-------------ʱ���������------------//    
#if ECBM_SYSCLK_OUT_EN //�ж��Ƿ���Ҫ����ʱ�������
#   if ((ECBM_MCU&0xF00000)>0x200000)//����ǲ���GH��
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
//--------------����ȷ��---------------//
    EA_ENABLE;//�����жϡ�
#if ((ECBM_MCU_CHECK_EN)&&(ECBM_UART_PRINTF_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_UART1_EN))
    delay_ms(500);
    system_check();
#endif
}
/*---------------------------------������ϵͳ����---------------------------------*/
/**********************************strϵ�к���************************/#if ECBM_STRING_EN
/*-------------------------------------------------------
�ַ������Һ�����
-------------------------------------------------------*/
u16 str_find(char * dest,char * key){
    u16 key_count=0,key_first=0,count=0;
    while(*dest){    //�ж�Ŀ���ַ�����
        if(key[key_count]==(*dest)){//����ؼ����ַ�����ǰλ�ȶԳɹ���
            key_count++;            //��ô�ͱȽ���һλ��
        }else if(key[0]==(*dest)){	//���統ǰλû�жԱȳɹ����Ϳ����ǲ���Ҫ��ͷ��ʼ�Աȡ�
			key_count=1;			//��ͷ�Աȳɹ���˵���ٴ��ҵ������ƵĹؼ��ʣ���ô�´ξʹӵڶ�����ʼ�Աȡ�
        }else{                      //����û�бȶԳɹ���
            key_count=0;            //��ô�ʹ�ͷ��ʼ�ȶԡ�
        }
		count++;    				//��¼ѭ���Ĵ��������ڼ���ؼ��ʳ��ֵ�λ�á�
        dest++;                     //��ȡĿ���ַ�������һλ��
        if(key[key_count]==0){      //����ؼ����ַ����ȶ��꣬
            return (count-key_count);//���عؼ����ַ�����һ�γ��ֵ�λ�á�
        } 
    }
    return 0xffff;//�����е���һ����˵��ֱ��Ŀ���ַ���������û�бȶԳɹ�������-1��
}
/*-------------------------------------------------------
IO��Ϣ��ȡ������
-------------------------------------------------------*/
u8 str_read_pin(char * str,u16 pos){
    u8  dat=0,offset,count; //�������������Ƕ�ȡ����Ϣ���ַ���ƫ�ƺ�����ͳ�ơ�
    count=0;                //����ͳ�����㡣
    for(offset=0;offset<10;offset++){//Ԥ��10��ƫ������
        if((str[pos+offset]>='0')&&(str[pos+offset]<='7')){//IO�ڵı�Ŷ��Ǵ�0~7��
            count++;                            //�������Χ�ڣ�����+1��
            if(count==1){                       //����ǵ�һ������
                dat=(str[pos+offset]-'0')<<4;   //���������ŵ���4λ��
            }
            if(count==2){                       //����ǵڶ�������
                dat=(str[pos+offset]-'0')|dat;  //���������ŵ���4λ��
                return dat;                     //���ظ�ֵ��
            }
        }
        if((str[pos+offset]>='8')&&(str[pos+offset]<='9')){//�����8��9����ôֻ������������д��ֵ��
            count++;
        }
        if(str[pos+offset]==',')break;//�������ž��˳���
        if(str[pos+offset]==0)break;  //�ַ�������Ҳ�˳���
    }
    return dat;
}
/*-------------------------------------------------------
u16������ȡ������
-------------------------------------------------------*/
u16 str_read_u16(char * str,u16 pos){
    u16 dat=0; //��ȡ����Ϣ��
    u8  offset;//�ַ���ƫ�ơ�
    for(offset=0;offset<20;offset++){//Ԥ��20���ַ���ƫ�ơ�
        if((str[pos+offset]>='0')&&(str[pos+offset]<='9')){//���ֶ��Ǵ�0~9��
            dat*=10;                  //��������һλ����ԭ����12���ͱ��120���ճ��ĸ���������װ�µ�����
            dat+=str[pos+offset]-'0'; //���µ����ӵ���λ�ϡ�
        }
        if(str[pos+offset]==',')break;//�������ž��˳���
        if(str[pos+offset]=='.')break;//������ž��˳���
        if(str[pos+offset]==0)break;  //�ַ�������Ҳ�˳���
    }
    return dat;
}
/*-------------------------------------------------------
�ַ����Ƴ�ָ��������ַ������Ȳ����棩��
-------------------------------------------------------*/
u8 str_push_len(u8 * dest,u16 dlen,u8 * key,u16 klen){
    u16 i,j=0,start=0,stop=0;
    for(i=0;i<dlen;i++){        //��ͷ��ʼ��ֱ��ָ���ĳ��ȡ�
        if(dest[i]==key[j]){    //�ѵ�ǰ���ַ��͹ؼ��ʱȽϳɹ���
            j++;                //ȡ�ؼ��ʵ���һ���֡�
            if(j==klen){        //���ؼ���ȫ���ȶ���ɵ�ʱ��
                stop=i;            //���桾����λ�á���
                break;            //�˳�ѭ����
            }
        }else{                    //�����ǰ���ַ��͹ؼ��ʱȽ�ʧ�ܣ�
            j=0;                //��һ�δ�ͷ��ʼ�ȶԡ�
            start=i+1;            //���¡���ʼλ�á�Ϊ��һλ����Ϊ��ǰλʧ���ˣ���
        }
    }
    if(start<=stop){            //���ȶԳɹ���ʱ�򣬡���ʼλ�á��϶�С�ڵ��ڡ�����λ�á���
        for(i=start;i<stop;i++){//���ӡ���ʼλ�á���������λ�á�֮��Ļ���ȫ���㡣
            dest[i]=0;
        }
        return 1;                //�����Ƴ��ɹ���
    }else{
        return 0;                //�����Ƴ�ʧ�ܡ�
    }
}
/*****************************************************************************/#endif
