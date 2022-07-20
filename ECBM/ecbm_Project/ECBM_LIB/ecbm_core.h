#ifndef _ECBM_CORE_H_//ͷ�ļ���ֹ�ؼ��رر����ȿ�����û�ж�������������˵���Ѿ����ع�һ���ˡ�
#define _ECBM_CORE_H_//û����˵�����״μ��أ���ô����ִ�С����Ҷ�������궨�壬��ֹ��һ�α����ء�
/*-------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2020 ����

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

����˵����
    ����������MIT��ԴЭ�����������ṩ������ֻ��֤ԭʼ�汾����������ά����BUG��
����ͨ�����紫���İ汾Ҳ���������޸Ĺ����ɴ˳��ֵ�BUG�������޹ء�������ʹ��ԭʼ
�汾����BUGʱ������ϵ���߽����
                            **************************
                            * ��ϵ��ʽ����Ⱥ778916610 *
                            ************************** 
------------------------------------------------------------------------------------*/
//-----------------������ͼ�����ý��棬����Configuration Wizard��������-----------------
//<<< Use Configuration Wizard in Context Menu >>>
//Frame Version Number ��ܰ汾��
#define ECBM_FVN 3
//Release Version Number �����汾��
//�������ؼ����ļ�����ʱ���ð汾�ż�һ��
#define ECBM_RVN 2
//BUG Version Number �����汾��
//ÿ�η���������ʱ����ֻ���޸�BUG���ð汾�ż�һ��
#define ECBM_BVN 0
//<h>��Ƭ��ϵͳ����
//<i>�ÿ��ڵ�ѡ���л����ѡ�����ϸ�Ķ��˽��˽����ѡ��
//<o>ϵͳʱ��Ƶ��ѡ��
//<i>���嵥Ƭ�����е�ʱ��Ƶ�ʣ���λHz����
//<5529600UL=>5.5296M <6000000UL=>6.000M <11059200UL=>11.0592M <12000000UL=>12.000M <18432000UL=>18.432M  
//<20000000UL=>20.000M <22118400UL=>22.1184M <24000000UL=>24.000M <27000000UL=>27.000M
//<30000000UL=>30.000M <33000000UL=>33.000M <33177600UL=>33.1776M <35000000UL=>35.000M 
//<36864000UL=>36.864M <40000000UL=>40.000M <44236800UL=>44.2368M <45000000UL=>45.000M 
#define ECBM_SYSCLK_SETTING 35000000L
//<e>ϵͳʱ�����
//<i>�������ʱ��Ƶ�����������������裬�������ڼ���ڲ��Ĺ���Ƶ�ʡ�
#define ECBM_SYSCLK_OUT_EN 0
//<o>�������
//<0=>�����P54 <1=>�����P16
#define ECBM_SYSLCK_OUT_PIN 0
//<o.4..7>STC8F��STC8A���������Ƶ
//<i>����������ͺ�ѡ���������÷�Ƶ��ѡ��ֻ����Чһ����
//< 1=>SYSCLK/ 1  < 2=>SYSCLK/ 2 < 4=>SYSCLK/ 4 
//< 6=>SYSCLK/ 8  < 8=>SYSCLK/16 <10=>SYSCLK/32 
//<12=>SYSCLK/64  <14=>SYSCLK/128
#define ECBM_SYSCLK_OUT_SETTING_FA 0x18
//<o>STC8G��STC8H���������Ƶ
//<1-127>
//<i>����������ͺ�ѡ���������÷�Ƶ��ѡ��ֻ����Чһ����
//<i>����پ��Ƿ�Ƶ���٣�������6������SYSCLK/6��
#define ECBM_SYSCLK_OUT_SETTING_GH 1
//</e>
//</h>
//<h>����Ż��Ͳ��Թ���
//<i>��������8K������С��Ƭ�����߸�С�ĵ�Ƭ����ʹ�ñ����ʱ��������Ѷ���ĺ����Ż�����
//<q>��Ƭ�����ü��
//<i>��ѡ��ѡ����Զ�����system_check������Ȼ���ڵ��Զ˵Ĵ������ֿ�����Ƭ����һЩ��Ϣ��
//<i>ֻҪ�ܿ�����������Ϣ�������˵����������û�����ȷ��
#define ECBM_MCU_CHECK_EN  0 
//<q>strϵ��
//<i>��ϵ�к�����Ҫ��Ϊ�˴��ַ����л�ȡ���õ���Ϣ��ĳЩ�����ʹ�õ���������Ϊ��չ���ܣ���ʵ��������Ŀ��ʱ������Ż�����
#define ECBM_STRING_EN 1
//</h>
//<h>��Ƭ��������ѡ��
//<i>��Щ���Ա�Ŀ�����������ע�⿴˵�����֡��ڹ�ѡĳ���ʱ����ͬ�����Ŀ�һ��ѡ��
//<q>POWER��
//<i>�ÿ��ṩ�˹���STC8�ĵ�Դ����λ�����Ź���ز���������
#define ECBM_POWER_LIB_EN 1
//<e>UART��
//<i>�ÿ��ṩ�˹���STC8��Ӳ��UART��ز���������
#define ECBM_UART_LIB_EN 1
//<q>�Զ����ع���
//<i>��ѡ��ѡ�����ʹ���Զ����ع��ܡ���������ʹ���˴���1�����Ե�ȷ������1��ʹ��״̬�����������ӳ�䵽P30��P31��
//<i>�����Զ����ع��ܺ�uart_int�����ͻ���system_init�ﱻ���ã��������ֶ�����uart_int�����ˡ�
#define ECBM_AUTO_DOWNLOAD_EN  1
//</e>
//<q>EXTI��
//<i>�ÿ��ṩ�˹���STC8���ⲿ�ж���ز���������
#define ECBM_EXTI_LIB_EN 0
//<q>TIMER��
//<i>�ÿ��ṩ�˹���STC8��Ӳ��TIMER��ز���������
#define ECBM_TIMER_LIB_EN 0
//<q>EEPROM��
//<i>�ÿ��ṩ�˹���STC8ʹ������FLASHģ���EEPROM��ز���������
#define ECBM_EEPROM_LIB_EN 0
//<q>SPI��
//<i>�ÿ��ṩ�˹���STC8��Ӳ��SPI��ز���������
#define ECBM_SPI_LIB_EN 0
//<q>SOFT_SPI��
//<i>�ÿ��ṩ�˹���STC8����GPIO�������SPI��ز���������
#define ECBM_SOFTSPI_LIB_EN 0
//<q>IIC��
//<i>�ÿ��ṩ�˹���STC8��Ӳ��IIC��ز���������
#define ECBM_IIC_LIB_EN 0
//<q>SOFT_IIC��
//<i>�ÿ��ṩ�˹���STC8����GPIO�������IIC��ز���������
#define ECBM_SOFTIIC_LIB_EN 0
//<q>ADC��
//<i>�ÿ��ṩ�˹���STC8��Ӳ��ADC��ز���������
#define ECBM_ADC_LIB_EN 0
//<q>CMP��
//<i>�ÿ��ṩ�˹���STC8��Ӳ��CMP��ز���������
#define ECBM_CMP_LIB_EN 0
//<q>MDU16��
//<i>�ÿ��ṩ�˹���STC8G��Ӳ���˳�����ز���������
#define ECBM_MDU16_LIB_EN 0
//<q>PCA��
//<i>�ÿ��ṩ�˹���STC8A��Ӳ��PCA��ز���������
#define ECBM_PCA_LIB_EN 0
//<q>PWM��
//<i>�ÿ��ṩ�˹���STC8��Ӳ��PWM��ز���������
#define ECBM_PWM_LIB_EN 0
//<q>LCM��
//<i>�ÿ��ṩ�˹���STC8��Ӳ��LCM��ز���������
#define ECBM_LCM_LIB_EN 0
//<q>LED��
//<i>�ÿ��ṩ�˹���STC8��Ӳ��LED��ز���������
#define ECBM_LED_LIB_EN 0
//</h>
//<<< end of configuration section >>>
//-----------------������ͼ�����ý��棬����Configuration Wizard��������-----------------
/*------------------------------------ͷ�ļ�����------------------------------------*/
#include "ecbm_reg.h"    //��Ƭ���Ĵ�����ͷ�ļ���
#include "intrins.h"    //��Ƭ��C����ʹ�û��ָ���ͷ�ļ���
#include "STDARG.H"     //���������֧�ֵ�ͷ�ļ���    
#include "stdio.h"      //sprintf��غ���֧�ֵ�ͷ�ļ���
/*------------------------------------ͨ�������趨----------------------------------*/
sbit    LED       =P5^5;     //ͨ��ECBM�İ��Ӷ����һ��LED����LED���õ͵�ƽ������
#define LED_ON    LED=0;     //����LED��
#define LED_OFF   LED=1;     //�ر�LED��
#define LED_BLINK LED=!LED;  //��LED��˸��
/*------------------------------------���ù����趨----------------------------------*/
//���¼�����������idata������ʱ����б����ǵķ��գ����鱣��idata����Ҫʹ�ã���ʹ��xdata����
#define REG_BGV   read_idata_u16(0xEF)//Ƭ��1.3V��ѹ��ʵ��ֵ��
#define REG_ID(x) read_idata_u8 (0xF1+x)//��Ƭ����ΨһID�롣

#define io2port(n) (n)>>4           //ȡ�������ڵ�P�ڣ����Ÿ�ʽ�����0xXX�ĸ�ʽ��
#define io2pin(n)  0x01<<((n)&0x0f) //ȡ�������ڵ�PIN�����Ÿ�ʽ�����0xXX�ĸ�ʽ��
/*-----------------------------------�⺯������-----------------------------------*/
#include "gpio.h"
#include "power.h"
#include "uart.h"
#include "exti.h"
#include "timer.h"
#include "eeprom.h"
#include "spi.h"
#include "soft_spi.h"
#include "iic.h"
#include "soft_iic.h"
#include "adc.h"
#include "cmp.h"
#include "mdu16.h"
#include "pca.h"
#include "lcm.h"
#include "pwm.h"
#include "led.h"
#include "nvic.h"
#include "stream.h"
#include "stream_fur.h"
#include "stream_modbus.h"
#include "stream_xmodem.h"
/*--------------------------------------������-----------------------------------*/
/*-------------------------------------------------------
��������delay_ms
��  �������뼶��ʱ����
��  �룺��Ҫ��ʱ�ĺ�������������1~65535��
��  ������
����ֵ����
�����ߣ�����
�������̣�
    delay_ms(500);//��ʱ500����
�������ڣ�2019-10-8
�޸ļ�¼��
2020-06-02:�޸�����ʱ0ms�����ʱ65535ms��BUG��
2022-02-06:�ӱ���������ʱ�ĳɺ궨�������ʱ��
-------------------------------------------------------*/
extern void delay_ms(u16 ms);
/*-------------------------------------------------------
��������delay_us
��  ����΢�뼶��ʱ����
��  �룺��Ҫ��ʱ�Ľ�����������΢����������ͨ��delay_set_us�����������΢���Ӧ�Ľ�������
��  ������
����ֵ����
�����ߣ�����
�������̣�
    us_val=delay_set_us(20);//�����20us��Ӧ�Ľ�������
    ...//�����޹صĴ��롣
    delay_us(us_val);//��ʱ20us��
    ...//�����޹صĴ��롣
�������ڣ�2019-10-8
�޸ļ�¼��
2020-1-3��ȥ����us_code.h�ļ�
2022-02-06:�ӱ���������ʱ�ĳɺ궨�������ʱ��
-------------------------------------------------------*/
extern void delay_us(u16 us);
/*-------------------------------------------------------
��������delay_set_us
��  ����΢�뼶��ʱת�����������ڰ�΢����ת���ɶ�Ӧ��������
��  �룺������ʱ��΢������
��  ������
����ֵ����΢������Ӧ�Ľ�������
�����ߣ�����
�������̣�
    us_val=delay_set_us(20);//�����20us��Ӧ�Ľ�������
    ...//�����޹صĴ��롣
    delay_us(us_val);//��ʱ20us��
    ...//�����޹صĴ��롣
�������ڣ�2019-10-8
�޸ļ�¼��
-------------------------------------------------------*/
extern u16  delay_set_us(u16 us);
/***********************************���ڵ���ģ��***************/#if ((ECBM_AUTO_DOWNLOAD_EN)&&(ECBM_UART_LIB_EN))
extern bit auto_download_en;            //�Զ����ص�ʹ��
extern u8 data auto_download_old_char;  //������һ�ν��յ�����
extern u8 data auto_download_char_count;//��ͬ���ݼ���
/*-------------------------------------------------------
��������system_uart_reset
��  �����Զ�����������������õ������жϵĽ��ղ��־���ʵ���Զ����ء�
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2019-10-8
�޸ļ�¼��
2022-2-9�������˴��룬���������سɹ��ʡ�
-------------------------------------------------------*/
extern void system_uart_reset();
/****************************************************************************/#endif
/*-------------------------------------------------------
��������system_check
��  ����ϵͳ��⺯�������򴮿ڷ��͵�Ƭ����һЩ������Ϣ��
    �����յĵ���Ϣ˵���⺯�������������������һ�㲻���á�
    ��ͼ�ν����п����Ż�����������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�������̣�
    system_check();//���͵�Ƭ����Ϣ�����ڡ�
�������ڣ�2019-10-8
�޸ļ�¼��
2020-01-02�������˼�����Ŀ��
-------------------------------------------------------*/
#if ((ECBM_MCU_CHECK_EN)&&(ECBM_UART_PRINTF_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_UART1_EN))
extern void system_check();
#endif
/*----------------------------------����ϵͳ����-----------------------------------*/
/*-------------------------------------------------------
��������system_init
��  ����ECBM�⺯���ĳ�ʼ���������������еĺ�����
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�������̣�
    void main(){
        system_init();//��ʼ�������⺯����
        while(1){  
        }    
    }
�������ڣ�2019-10-8
�޸ļ�¼��
2020-1-3���¼����Զ��жϾ���Ĺ��ܡ�
2022-2-6��ȡ�����Զ��жϾ���Ĺ��ܡ�
-------------------------------------------------------*/
extern void system_init(void);
/********************************strϵ�к���************************/#if ECBM_STRING_EN
/*-------------------------------------------------------
��������str_find
��  �����ַ������Һ��������ڲ���һ���ַ����Ƿ�����һ���ַ����ڡ�
��  �룺
    dest    ��Ҫ���ҵ�Ŀ���ַ�����
    key     ��Ҫ���ҵ��ַ���������
��  ������
����ֵ���ַ���������Ŀ���ַ�����λ�ã���0��ʼ���㡣�����-1��˵��Ŀ���ַ���û�и�������
�����ߣ�����
�������̣�
    str_find("0123456789","4",i);//��"0123456789"�в���"4"���ڵ�λ�á�
�������ڣ�2019-10-9
�޸ļ�¼��
2022-2-6���޸����ظ��ַ����Ҳ�����bug��
-------------------------------------------------------*/
extern u16 str_find(char * dest,char * key);
/*-------------------------------------------------------
��������str_read_pin
��  ����IO��Ϣ��ȡ���������ڶ�ȡ�ַ�����Ŀ��λ�õ�IO��Ϣ��
��  �룺
    str     ����IO��Ϣ���ַ�����
    pos     IO��Ϣ��λ�ã�ͨ������������ַ����ڵĶ��IO��Ϣ��
��  ������
����ֵ���ڸ�λ�õ�IO��Ϣ��
�����ߣ�����
�������̣�
    str_read_pin("SCL=D13,SDA=D14",11);//��ȡ���±�11��ʼ��IO��Ϣ�����᷵��0x14��
�������ڣ�2019-10-9
�޸ļ�¼��
-------------------------------------------------------*/
extern u8 str_read_pin(char * str,u16 pos);
/*-------------------------------------------------------
��������str_read_u16
��  ����u16������ȡ���������ڶ�ȡ�ַ�����Ŀ��λ�õ�u16����ֵ��
��  �룺
    str     ������ֵ���ַ�����
    pos     ��ֵ��λ�ã�ͨ������������ַ����ڵĶ����ֵ��
��  ������
����ֵ���ڸ�λ�õ���ֵ��U16���ͣ���0~65535��
�����ߣ�����
�������̣�
    str_read_u16("SCL=D13,w=128",9);//��ȡ���±�8��ʼ����ֵ�����᷵��128��
�������ڣ�2019-10-9
�޸ļ�¼��
2020-02-17��������һ��ֹͣ�����������������ҲҪֹͣ��
-------------------------------------------------------*/
extern u16 str_read_u16(char * str,u16 pos);
/*-------------------------------------------------------
��������str_push_len
��  �����ַ����Ƴ�ָ��������ַ������Ȳ����棩�����ڰ�ָ�������е�ָ���ؼ����Ƴ��û��档
        Ϊ�˷�ֹǰ������������ɸ��ţ����硰LEDLED_ON_OFF�����Ƴ���LED_ON����ʣ�µĲ��ֻ�������ɡ�LED_OFF������
        �����Ƴ��ؼ���֮��ֻ��ѹؼ�������λ�����㣬����������β���ݣ�����LEDLED_ON_OFF�����Ƴ���LED_ON����ʣ�¡�LED      _OFF������
��  �룺
    dest    Ŀ���ַ������档
    dlen    Ŀ���ַ�������ĳ��ȡ�
    key     ��Ҫ�Ƴ��Ĺؼ��ʡ�
    klen    �ؼ��ʵĳ��ȡ�
��  ������
����ֵ��
    0   �Ƴ�ʧ�ܣ�������Ŀ�껺����û�иùؼ��ʡ�
    1   �Ƴ��ɹ���
�����ߣ�����
�������̣���
�������ڣ�2020-02-17
�޸ļ�¼��
-------------------------------------------------------*/
extern u8 str_push_len(u8 * dest,u16 dlen,u8 * key,u16 klen);
/**************************************************************************/#endif
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��