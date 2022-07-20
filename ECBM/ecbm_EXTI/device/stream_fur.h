#ifndef _ECBM_STREAM_FUR_H_//ͷ�ļ���ֹ�ؼ��رر����ȿ�����û�ж�������������˵���Ѿ����ع�һ���ˡ�
#define _ECBM_STREAM_FUR_H_//û����˵�����״μ��أ���ô����ִ�С����Ҷ�������궨�壬��ֹ��һ�α����ء�
/*-------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2021 ����

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
                            **************************
------------------------------------------------------------------------------------*/
//-----------------������ͼ�����ý��棬����Configuration Wizard��������-----------------
//<<< Use Configuration Wizard in Context Menu >>>
#define ECBM_STREAM_FUR_VERSION "V1.2"
//<q>���ڻظ�ʹ��
//<i>FUR��Ȼ�ǻ��ڴ��ڵ�Ӧ�ã��������ݵķ�������������������ʽ��
//<i>�����ð���OLED����ʾ���ݡ� ֱ�ӹ۲�������ת�Ƕȵȡ���ʱ�ѻظ�����ȡ�������Խ�ʡһЩ�ռ䡣
#define ECBM_STREAM_FUR_UART_SEND_EN 1
//<q>����ʹ��
//<i>FUR�����֮������������Դ������ֺ͵�Ƭ���ı��ͨ�ţ���������Ҳ֧�ֵ�Ƭ���͵�Ƭ����ͨ�š�
//<i>�������Ҫ����������ܣ�����ȡ���Խ�ʡ�ռ䡣
#define ECBM_STREAM_FUR_MATER_EN 0
//<<< end of configuration section >>>
//-----------------������ͼ�����ý��棬����Configuration Wizard��������-----------------
/*---------------------------------------ͷ�ļ�------------------------------------*/
#include "ecbm_core.h"    //ECBM���ͷ�ļ��������Ѿ�������STC8��ͷ�ļ���
/*---------------------------------------�궨��------------------------------------*/
/*------------------��������------------------*/
#define FUR_READ    0x00//���Ĵ�����
#define FUR_ADD     0x01//�Ĵ�������һ������
#define FUR_DEC     0x02//�Ĵ�����ȥһ������
#define FUR_MUL     0x03//�Ĵ�������һ������
#define FUR_DIV     0x04//�Ĵ�������һ������
#define FUR_AND     0x05//�Ĵ�������һ������
#define FUR_OR      0x06//�Ĵ�������һ������
#define FUR_XOR     0x07//�Ĵ��������һ������
#define FUR_BIT     0x08//�Ĵ���λ��ֵ��
#define FUR_EQU     0x09//�Ĵ�����ֵ��
#define FUR_FBID    0x0A//����ID���������ָ���ǲ�ѯID�õġ�
/*------------------��־λ����----------------*/
#define FUR_WRITE   0x80//д��ʹ�ܣ�������������Ҫд���Ĵ�����
#define FUR_HEX     0x40//16����ʹ�ܣ�������������Ҫ��16���Ʊ�ʾ��
/*------------------״̬����----------------*/
#define FUR_READY       0//����̬��ɶҲ������
#define FUR_GET_ADDR    1//���յ�ַ״̬��
#define FUR_GET_ID      2//����ID״̬��
#define FUR_GET_OP      3//���ղ�����״̬��
#define FUR_GET_OP_EX   4//���ղ�����״̬��
#define FUR_GET_DATA    5//��������״̬��
#define FUR_GET_DATA16  6//����16��������״̬��
#define FUR_CMD_ID      7//ȷ��ID�Ĳ��֡�
#define FUR_WAIT_END    8//�ȴ�������״̬��
#define FUR_END_DO      9//Э�������ָ���״̬��
/*--------------------------------------��������-----------------------------------*/
extern u8  es_fur_status ;//FUR����״̬����
extern u16 es_fur_addr   ;//FUR��ַ��
extern u16 es_fur_dat16  ;//FUR���ݣ�16λ����
extern u8  es_fur_id     ;//FUR��ID��ʱ������
extern u8  es_fur_dat8   ;//FUR���ݣ�8λ����
extern u8  es_fur_operate;//FUR��������
extern u8  es_fur_temp8  ;//FUR��ʱ������8λ����
/*--------------------------------------������-----------------------------------*/
/*------------------��Ҫ�û�����ĺ���------------------*/
/*-------------------------------------------------------
��������es_fur_reset
��  ����FUR��ȡID���������������Ҫ���ر�����ID�š�
��  �룺��
��  ������
����ֵ��
    ������ID�š�
�����ߣ�����
�ο����̣�
    u8 es_fur_get_id(void){
        return 1;
    }
�������ڣ�2021-10-25
�޸ļ�¼��
-------------------------------------------------------*/
extern u8 es_fur_get_id(void);
/*-------------------------------------------------------
��������es_fur_read_reg
��  ����FUR��ȡ�Ĵ���������
��  �룺
    addr    Ҫ��ȡ���ݵļĴ����ĵ�ַ��
��  ������
����ֵ��
    �õ�ַ��Ӧ�ļĴ��������ݡ�
�����ߣ�����
�ο����̣�
    u16 es_fur_read_reg(u16 addr){
        return reg[addr];
    }
�������ڣ�2021-10-25
�޸ļ�¼��
2022-03-21������Ϊes_fur_read_reg��
-------------------------------------------------------*/
extern u16 es_fur_read_reg(u16 addr);
/*-------------------------------------------------------
��������es_fur_write_reg
��  ����FURд��Ĵ���������
��  �룺
    addr    Ҫд�����ݵļĴ����ĵ�ַ��
    dat     Ҫд������ݡ�
��  ������
����ֵ����
�����ߣ�����
�ο����̣�
    void es_fur_write_reg(u16 addr,u16 dat){
        reg[addr]=dat;
    }
�������ڣ�2021-10-25
�޸ļ�¼��
2022-03-21������Ϊes_fur_write_reg��
-------------------------------------------------------*/
extern void es_fur_write_reg(u16 addr,u16 dat);
/*-------------------------------------------------------
��������es_fur_master_receive_callback
��  ����FUR�������ջص���������������Ϊ��������ָ����ӻ�֮�󣬴ӻ���������ʱ����ñ�������
��  �룺
    addr    �ӻ����صļĴ�����ַ�����������жϴӻ������Ƿ���ȷ�������������ֲ�ͬ������
    dat     �ӻ��ĸõ�ַ�����ݡ�
��  ������
����ֵ����
�����ߣ�����
�ο����̣�
    //����ӻ�ģ���15�żĴ��������ģ����������¶ȡ�
    //����ص�����
    void es_fur_master_receive_callback(u16 addr,u16 dat){
        if(addr==15){//���ӻ����ص�������15�żĴ���ʱ��
            oled_printf(&oled,0,0,"temp=%d",dat);//��OLED�ϴ�ӡ���¶���Ϣ��
        }
    }
    //��main��ִ�ж�ȡ���������ˡ�
    void main(){
        ...//��������
        while(1){
            if(temp_flag){//���˸����¶ȵ�ʱ���ˣ�
                temp_flag=0;//�������־λ��
                es_fur_master_read(15,0);//��ӻ����Ͷ�ȡ15�ŵ�ָ��յ��ظ���ʱ���ִ�лص�������
            }
        }
    }

�������ڣ�2021-10-25
�޸ļ�¼��
-------------------------------------------------------*/
#if ECBM_STREAM_FUR_MATER_EN == 1
extern void es_fur_master_receive_callback(u16 addr,u16 dat);
#endif
/*-----------------------ϵͳ����-----------------------*/
/*-------------------------------------------------------
��������es_fur_reset
��  ����FUR���ú�������FUR����Ĳ���ȫ�����á�
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-25
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_fur_reset(void);
/*-------------------------------------------------------
��������es_fur_send_num_10
��  ����FUR�������ݺ�������10���Ƶĸ�ʽ���͡�
��  �룺
    num     Ҫ���͵����ݡ�
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-25
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_fur_send_num_10(u16 num);
/*-------------------------------------------------------
��������es_fur_send_num_16
��  ����FUR�������ݺ�������16���Ƶĸ�ʽ���͡�
��  �룺
    num     Ҫ���͵����ݡ�
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-25
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_fur_send_num_16(u16 num);
/*-------------------------------------------------------
��������es_fur_exe
��  ����FUR����ִ�к������Ž�stream��������С�
��  �룺
    dat     ��stream��ܶԽӵĲ�����
��  ������
����ֵ����
�����ߣ�����
�ο����̣�
    void ecbm_stream_exe(u8 dat){
        es_fur_exe(dat);
    }
�������ڣ�2021-10-25
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_fur_exe(u8 dat);
/*-------------------------------------------------------
��������es_fur_master_send
��  ����FUR�������ͺ�����������һ��֧��FUR���豸����һ�����ݡ�
��  �룺
    addr    Ҫ���͵�Ŀ��Ĵ�����ַ��
    id      Ŀ���豸��ID��
    dat     Ҫ���͵����ݡ�
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-25
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_fur_master_send(u16 addr,u8 id,u16 dat);
/*-------------------------------------------------------
��������es_fur_master_read
��  ����FUR������ȡ���������ڶ�ȡһ��֧��FUR���豸�����ݡ�
��  �룺
    addr    Ҫ��ȡ��Ŀ��Ĵ�����ַ��
    id      Ŀ���豸��ID��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-25
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_fur_master_read(u16 addr,u8 id);
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��