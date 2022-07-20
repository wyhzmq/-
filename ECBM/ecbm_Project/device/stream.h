#ifndef _ECBM_STREAM_H_//ͷ�ļ���ֹ�ؼ��رر����ȿ�����û�ж�������������˵���Ѿ����ع�һ���ˡ�
#define _ECBM_STREAM_H_//û����˵�����״μ��أ���ô����ִ�С����Ҷ�������궨�壬��ֹ��һ�α����ء�
/*-------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2022 ����

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
    ���������MIT��ԴЭ�����������ṩ������ֻ��֤ԭʼ�汾����������ά����BUG��
����ͨ�����紫���İ汾Ҳ�������޸Ĺ����ɴ˳��ֵ�BUG�������޹ء�������ʹ��ԭʼ
�汾����BUGʱ������ϵ���߽����
                            **************************
                            * ��ϵ��ʽ����Ⱥ778916610 *
                            * ��1Ⱥ���ˣ���Ⱥ927297508*
                            **************************
------------------------------------------------------------------------------------*/
//-----------------������ͼ�����ý��棬����Configuration Wizard��������-----------------
//<<< Use Configuration Wizard in Context Menu >>>
#define ECBM_STREAM_VERSION "V1.3"
//<o>���л����С
//<i>��λ���ֽڡ���
#define ECBM_STREAM_SZIE     135
//<o>����֡���ʱ��
//<10-2500:10>
//<i>��λmS��Ĭ�϶�ʱ��10mS�ж�һ��,������ʱ����10�ı�����
//<i>�ӽ��յ����һ�����ݿ�ʼ���㣬�������ʱ��û���ٴν��ܵ�����ʱ����Ϊ�Է��Ѿ�������һ������֡��
#define ECBM_STREAM_TIME_MS  20
#define ECBM_STREAM_TIME_MAX (ECBM_STREAM_TIME_MS/10)
//<o>���ڿ���ʱ��
//<10-2500:10>
//<i>��λmS��Ĭ�϶�ʱ��10mS�ж�һ��,������ʱ����10�ı�����
//<i>�ӽ��յ����һ�����ݿ�ʼ���㣬�������ʱ��û���ٴν��յ�����ʱ����Ϊ�Է��Ѿ�������ȫ�����ݣ����ڻָ�������״̬��
//<i>��ֵӦ�ñ�����֡���ʱ���
#define ECBM_STREAM_IDLE_MS  80
#define ECBM_STREAM_IDLE_MAX (ECBM_STREAM_IDLE_MS/10)
//<h>���ʹ��
//<q>�Ƚ����
//<i>���ǶԽ��յ����ַ�����Ŀ���ַ������бȽϣ�������������Ŀ���ַ�����ʱ�򣬿��Դ���ĳЩ������
#define ECBM_STREAM_CMP_EN 0
//<q>FUR���
//<i>����ECBM�����з��Ŀ���(Fast)����(Uart)���ʼĴ���(Reg)�����
//<i>����ASCII�������ͨ�ţ�Э��ͨ���׶����������Կ��ٶ�д�Ĵ��������ܶ���������㡣
#define ECBM_STREAM_FUR_EN 0
//<q>MODBUS���
//<i>ͨ�õ�MODBUSЭ��RTU�汾��Ŀǰ������[01][05][03][06][10][02][04]��7��ָ�
//<i>������Ҳ�����ڶ�д�Ĵ����ġ�
#define ECBM_STREAM_MODBUS_EN 0
//<q>X-MODEM���
//<i>ͨ�õ�X-MODEMЭ�飬������ÿ��128�ֽں�У��͵İ汾��
//<i>���������ڴ���������ݻ����ļ���
#define ECBM_STREAM_XMODEM_EN 0
//<q>ECP���
//<i>����ECBM�����з���ECBMͨ��(Communication)Э��(Protocol)�����
//<i>�����������Ը���������һЩ��Ҫ�ġ����������ݡ�
//<i>�����ڵ�Ƭ��û�����������ʱ��Ҳ����ȫ����ECP������������ݡ�
#define ECBM_STREAM_ECP_EN 1
//</h>
//<<< end of configuration section >>>
//-----------------������ͼ�����ý��棬����Configuration Wizard��������-----------------
/*---------------------------------------ͷ�ļ�------------------------------------*/
#include "ecbm_core.h"    //ECBM���ͷ�ļ��������Ѿ�������STC8��ͷ�ļ���
/*---------------------------------------�궨��------------------------------------*/
#define ECBM_STREAM_TIME_EN   0x01  //��ʱʹ�ܡ�
#define ECBM_STREAM_TIME_OUT  0x02  //��ʱ����ʱ��־��
#define ECBM_STREAM_UART_IDLE 0x04  //���ڿ��б�־��
/*--------------------------------------��������-----------------------------------*/
extern u8 xdata ecbm_stream_buf[ECBM_STREAM_SZIE];  //stream�Ľ��ջ��档
extern u8 ecbm_stream_start;                  //������ʱ��Ŀ�ʼ��ַ��
extern u8 ecbm_stream_stop;                   //������ʱ��Ľ�����ַ��
extern u8 ecbm_stream_count;                  //���յ�������������
extern u8 ecbm_stream_time;                   //��ʱ����ʱ������
extern u8 ecbm_stream_status;                 //steam״̬��
/*--------------------------------------��������-----------------------------------*/
///////////////////////////////////��Ҫ�û�����ĺ���////////////////////////////////
/*-------------------------------------------------------
��������ecbm_stream_exe
��  ���������������ɸ�����Ҫ��ӡ�
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2021-03-24
�޸ļ�¼��
-------------------------------------------------------*/
extern void ecbm_stream_exe(u8 dat);
///////////////////////////////////��Ҫ�û���ֲ�ĺ���////////////////////////////////
/*-------------------------------------------------------
��������ECBM_STREAM_IN
��  �������ݽ��պ���������ֻ��һ�����ã�Ϊ�˿�����Ӧ�����˺궨�塣
��  �룺
    dat     ���յ�������
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2021-03-24
�޸ļ�¼��
2021-11-11����Դ��ڿ��е��ж������޸ġ�
-------------------------------------------------------*/
#define ECBM_STREAM_IN(dat) do{\
    ecbm_stream_time=0;                     /*���ü�ʱֵ*/\
    ecbm_stream_status=ECBM_STREAM_TIME_EN; /*���ʱ���������־λ*/\
    ecbm_stream_buf[ecbm_stream_stop++]=dat;/*�������ݵ�����ͬʱ��βָ������*/\
    ecbm_stream_count++;                    /*���ݼ�������*/\
    if(ecbm_stream_stop>=ECBM_STREAM_SZIE){ /*�����β�����������ֵ*/\
        ecbm_stream_stop=0;                 /*���л���������ǰ*/\
    }\
}while(0)
/*-------------------------------------------------------
��������ECBM_STREAM_TIME_RUN
��  ����ʱ�����к����������ṩ�������ʱ���жϹ��ܡ�
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2021-03-24
�޸ļ�¼��
2021-11-11�������˴��ڿ��е��жϡ�
-------------------------------------------------------*/    
#define ECBM_STREAM_TIME_RUN()   do{\
    if(ecbm_stream_status&ECBM_STREAM_TIME_EN){       /*��������״̬ʱ*/\
        ecbm_stream_time++;                           /*ÿ�ζ�ʱ���жϼ�һ��*/\
        if(ecbm_stream_time>ECBM_STREAM_TIME_MAX){    /*�����˼��ʱ�����ֵʱ*/\
            ecbm_stream_status|=ECBM_STREAM_TIME_OUT; /*��ɳ�ʱ״̬*/\
        }\
        if(ecbm_stream_time>ECBM_STREAM_IDLE_MAX){    /*�����˿���ʱ�����ֵʱ*/\
            ecbm_stream_status|=ECBM_STREAM_UART_IDLE;/*��ɿ���״̬*/\
            ecbm_stream_status&=~ECBM_STREAM_TIME_EN; /*����ʱ�رռ�ʱ*/\
        }\
    }\
}while(0)
/*-------------------------------------------------------
��������ecbm_stream_main
��  ����������������������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2021-03-24
�޸ļ�¼��
2021-11-11����Դ��ڿ��е��ж������޸ġ�
-------------------------------------------------------*/
extern void ecbm_stream_main(void);
/*-------------------------------------------------------
��������ecbm_stream_cmp
��  ����������ȶԺ�����
��  �룺
    dat     ��ecbm_stream_exe�ԽӵĽӿڡ�
    str     ��Ҫ�ȶԵ��ַ�����
��  ����
    count   �ȶԵļ���ֵ������ֵ���ַ����������ʱ����ʾ�ȶԳɹ���
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2021-10-21
�޸ļ�¼��
-------------------------------------------------------*/
#if ECBM_STREAM_CMP_EN
extern void ecbm_stream_strcmp(u8 dat,u8 code * str,u8 * count);
#endif
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��