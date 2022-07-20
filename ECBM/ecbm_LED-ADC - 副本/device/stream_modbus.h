#ifndef _ECBM_STREAM_MODBUS_H_//ͷ�ļ���ֹ�ؼ��رر����ȿ�����û�ж�������������˵���Ѿ����ع�һ���ˡ�
#define _ECBM_STREAM_MODBUS_H_//û����˵�����״μ��أ���ô����ִ�С����Ҷ�������궨�壬��ֹ��һ�α����ء�
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
//modbus-rtu�İ汾���˰汾������stream�⡣
#define ES_MODBUS_RTU_VERSION "V1.2"
//<q>[01]����Ȧ
//<i>�������Ȧ�йص�ָ�û�б�ʹ�ܣ���ô��Ȧ��д��صĺ����ͻ��涼�����Ż�����
#define ES_MODBUS_RTU_CMD01_EN 1
//<q>[05]д������Ȧ
//<i>�������Ȧ�йص�ָ�û�б�ʹ�ܣ���ô��Ȧ��д��صĺ����ͻ��涼�����Ż�����
#define ES_MODBUS_RTU_CMD05_EN 1
//<q>[03]���Ĵ���
//<i>����ͼĴ����йص�ָ�û�б�ʹ�ܣ���ô��Ȧ��д��صĺ����ͻ��涼�����Ż�����
#define ES_MODBUS_RTU_CMD03_EN 1
//<q>[06]д�����Ĵ���
//<i>����ͼĴ����йص�ָ�û�б�ʹ�ܣ���ô��Ȧ��д��صĺ����ͻ��涼�����Ż�����
#define ES_MODBUS_RTU_CMD06_EN 1
//<e>[10]д����Ĵ���
//<i>����ͼĴ����йص�ָ�û�б�ʹ�ܣ���ô��Ȧ��д��صĺ����ͻ��涼�����Ż�����
#define ES_MODBUS_RTU_CMD10_EN 1
//<o>�Ĵ���д�뻺������
//<i>��λ���ֽڣ�8λ��������CRC�Ĵ��ڣ��ڶ��ֽ�д���ʱ�򣬲������̰����ݴ��룬��Ҫ��һ���������������CRC��֤���֮�����һ��д�롣
#define ES_MODBUS_RTU_BUF_SIZE  10
//</e>
//<q>[02]����ɢ������
//<i>�����IOϵͳ�йص�ָ�û�б�ʹ�ܣ���ôIO��صĺ����ͻ��涼�����Ż�����
#define ES_MODBUS_RTU_CMD02_EN 1
//<q>[04]������Ĵ���
//<i>�����IOϵͳ�йص�ָ�û�б�ʹ�ܣ���ôIO��صĺ����ͻ��涼�����Ż�����
#define ES_MODBUS_RTU_CMD04_EN 1
//<q>CRC����ص�����
//<i>���ͨ���г�����CRC������ô�ͻ��������ص������������������д������Բ�ʹ�����ѡ�
#define ES_MODBUS_RTU_CRC_ERR_EN 0
//�����Ǻϲ�������ɢ�ĺ궨����ܽᶨ�壺
#define ES_MODBUS_RTU_CMD_BIT_EN  (ES_MODBUS_RTU_CMD01_EN+ES_MODBUS_RTU_CMD05_EN)
#define ES_MODBUS_RTU_CMD_REG_EN  (ES_MODBUS_RTU_CMD03_EN+ES_MODBUS_RTU_CMD06_EN+ES_MODBUS_RTU_CMD10_EN)
#define ES_MODBUS_RTU_CMD_IO_EN   (ES_MODBUS_RTU_CMD02_EN+ES_MODBUS_RTU_CMD04_EN)
#define ES_MODBUS_RTU_CMD_ALL_EN  (ES_MODBUS_RTU_CMD_BIT_EN+ES_MODBUS_RTU_CMD_REG_EN+ES_MODBUS_RTU_CMD_IO_EN)
//<<< end of configuration section >>>
//-----------------������ͼ�����ý��棬����Configuration Wizard��������-----------------
/*---------------------------------------ͷ�ļ�------------------------------------*/
#include "ecbm_core.h"    //ECBM���ͷ�ļ��������Ѿ�������STC8��ͷ�ļ���
/*------------------------------------״̬���궨��---------------------------------*/
#define ES_MODBUS_RTU_READY           0   //����̬����ʱ���Խ���һ֡modbus���ݡ�
#define ES_MODBUS_RTU_WAIT            1   //�ȴ�̬������������֮���ڴ˵ȴ���ǰ����֡������
#define ES_MODBUS_RTU_FUN_NUM         2   //��ȡ�����룬�ڴ˶�ȡ�����롣
#define ES_MODBUS_RTU_ADDRH           3   //��ȡ��ַ��8λ��
#define ES_MODBUS_RTU_ADDRL           4   //��ȡ��ַ��8λ��
#define ES_MODBUS_RTU_DATA_COUNTH     5   //��ȡ���ݻ��߸����ĸ�8λ��
#define ES_MODBUS_RTU_DATA_COUNTL     6   //��ȡ���ݻ��߸����ĵ�8λ��
#define ES_MODBUS_RTU_COUNT_ERR       7   //��ȡ��������
#define ES_MODBUS_RTU_CRCH            8   //��ȡCRC�ĸ�8λ��
#define ES_MODBUS_RTU_CRCL            9   //��ȡCRC�ĵ�8λ��
#define ES_MODBUS_RTU_DO              10  //����̬���ڸ�״̬�´������ݡ�
#define ES_MODBUS_RTU_DATAH           11  //��ȡ��ַ��8λ��
#define ES_MODBUS_RTU_DATAL           12  //��ȡ��ַ��8λ��
#define ES_MODBUS_RTU_BYTE_COUNT      13  //��ȡ�ֽ�������
/*--------------------------------------��������-----------------------------------*/
extern u8  es_modbus_rtu_status      ; //״̬��ʹ�õı�����
extern u8  es_modbus_rtu_broadcast_en; //�㲥ģʽ��
extern u8  es_modbus_rtu_fun_code    ; //�����롣
extern u8  es_modbus_rtu_fun_err_num ; //�쳣�롣
extern u16 es_modbus_rtu_address     ; //���ݵ�ַ��
extern u16 es_modbus_rtu_data_count  ; //����/������
extern u16 es_modbus_rtu_uart_crc    ; //CRC���㻺�档
extern u16 es_modbus_rtu_crc_buf     ; //CRC���档
extern u8  es_modbus_rtu_cmd_count   ; //ָ��������
extern u16 es_modbus_rtu_cmd_buf[ES_MODBUS_RTU_BUF_SIZE];//ָ��档
/*--------------------------------------������-----------------------------------*/
/*------------------��Ҫ�û�����ĺ���------------------*/
/*-------------------------------------------------------
��������es_modbus_cmd_read_io_bit
��  ������ȡ��ɢ����Ĵ���������������02H���õ���
��  �룺
    addr    ���������ĵ�ַ��Ϣ��
��  ����
    dat     �õ�ַ��Ӧ����ɢ����Ĵ��������ݣ�ֻ��0��1���ֿ��ܡ�
����ֵ����
�����ߣ�����
�ο����̣�
    void es_modbus_cmd_read_io_bit(u16 addr,u8 * dat){
        if(addr==0x0000){//������Ҫ����ַ0��ʱ��
            if(P00){//�����У������ַ��Ӧ��P0.0��״̬��
                *dat=1;//�Ǹߵ�ƽ�ͷ���1��
            }else{
                *dat=0;//�ǵ͵�ƽ�ͷ���0��
            }
        }
    }
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_cmd_read_io_bit(u16 addr,u8 * dat);
/*-------------------------------------------------------
��������es_modbus_cmd_read_io_reg
��  ������ȡ��ɢ����Ĵ���������������04H���õ���
��  �룺
    addr    ���������ĵ�ַ��Ϣ��
��  ����
    dat     �õ�ַ��Ӧ������Ĵ��������ݡ�
����ֵ����
�����ߣ�����
�ο����̣�
    void es_modbus_cmd_read_io_reg(u16 addr,u16 * dat){
        if(addr==0x0000){//������Ҫ����ַ0��ʱ��
            *dat=(u16)P0;//�����У������ַ��Ӧ��P0��״̬��
        }
    }
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_cmd_read_io_reg(u16 addr,u16 * dat);
/*-------------------------------------------------------
��������es_modbus_cmd_write_bit
��  ����д������Ȧ�Ĵ���������������05H���õ���
��  �룺
    addr    ���������ĵ�ַ��Ϣ��
    dat     Ҫд��õ�ַ�����ݡ�
��  ������
����ֵ����
�����ߣ�����
�ο����̣�
    void es_modbus_cmd_write_bit(u16 addr,u8 dat){
        if(addr==0x0000){//������Ҫд��ַ0����Ȧʱ��
            if(dat){//�����У������ַ��Ӧ�ű���test��D0λ��
                test|=0x0001;//���д�����1������D0λ���1��
            }else{
                test&=0xFFFE;//���д�����0������D0λ���0��
            }
        }
    }
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_cmd_write_bit(u16 addr,u8 dat);
/*-------------------------------------------------------
��������es_modbus_cmd_read_bit
��  ������������Ȧ�Ĵ���������������01H���õ���
��  �룺
    addr    ���������ĵ�ַ��Ϣ��
��  ����
    dat     �õ�ַ��Ӧ����Ȧ�Ĵ��������ݡ�
����ֵ����
�����ߣ�����
�ο����̣�
    void es_modbus_cmd_read_bit(u16 addr,u8 * dat){
        if(addr==0x0000){//������Ҫ����ַ0��ʱ��
            if(test&0x0001){//�����У������ַ��Ӧ��test������D0λ��
                *dat=1;//D0λΪ1�ͷ���1��
            }else{
                *dat=0;//D0λΪ0�ͷ���0��
            }
        }
    }
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_cmd_read_bit(u16 addr,u8 * dat);
/*-------------------------------------------------------
��������es_modbus_cmd_write_reg
��  ����д�������ּĴ���������������06H��10H���õ���
��  �룺
    addr    ���������ĵ�ַ��Ϣ��
    dat     Ҫд��õ�ַ�����ݡ�
��  ������
����ֵ����
�����ߣ�����
�ο����̣�
    void es_modbus_cmd_write_reg(u16 addr,u16 dat){
        reg[addr]=dat;//�����е�����reg���������б��ּĴ�����
    }
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_cmd_write_reg(u16 addr,u16 dat);
/*-------------------------------------------------------
��������es_modbus_cmd_read_reg
��  �������������ּĴ���������������03H���õ���
��  �룺
    addr    ���������ĵ�ַ��Ϣ��
��  ����
    dat     �õ�ַ��Ӧ�ı��ּĴ��������ݡ�
����ֵ����
�����ߣ�����
�ο����̣�
    void es_modbus_cmd_read_reg(u16 addr,u16 * dat){
        *dat=reg[addr];//�����е�����reg���������б��ּĴ�����
    }
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_cmd_read_reg(u16 addr,u16 * dat);
/*-------------------------------------------------------
��������es_modbus_rtu_crc_err_callback
��  ����CRC����ص���������modbusͨѶ��CRCУ�����ʱ���á�
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣�
    void es_modbus_rtu_crc_err_callback(void){
        //����֪ͨ�����ط���Ҳ����ʲô��������
    }
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_crc_err_callback(void);
/*-------------------------------------------------------
��������es_modbus_rtu_get_id
��  ������ȡ����ID������modbusͨѶ�л���ã�Ҫ���ر�����ID�š�
��  �룺��
��  ������
����ֵ��
    ������IDֵ��
�����ߣ�����
�ο����̣�
    u8 es_modbus_rtu_get_id(void){
        return 1;//����Ϊһ��������Ҳ������һ�����������Ƿ�Χ������1~247֮�䡣
    }
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern u8 es_modbus_rtu_get_id(void);
/*----------------------ϵͳ����-----------------------*/
/*-------------------------------------------------------
��������es_modbus_rtu_crc16
��  ����CRCУ�麯����
��  �룺
    buf     ��ǰ��Ҫ����CRCУ������ݡ�
    crc     ��ǰ��CRCֵ��
��  ����
    crc     ���������õ�����CRCֵ��
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_crc16(u8 buf,u16 * crc);
/*-------------------------------------------------------
��������es_modbus_rtu_err_num
��  ����modbus���ش����뺯����
��  �룺
    fun_num     ��ǰ�Ĺ����롣
    err_num     ��Ҫ����Ĵ����롣
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_err_num(u8 fun_num,u8 err_num);
/*-------------------------------------------------------
��������es_modbus_rtu_cmd_0x01
��  ����01�Ź����봦������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x01(void);
/*-------------------------------------------------------
��������es_modbus_rtu_cmd_0x02
��  ����02�Ź����봦������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x02(void);
/*-------------------------------------------------------
��������es_modbus_rtu_cmd_0x03
��  ����03�Ź����봦������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x03(void);
/*-------------------------------------------------------
��������es_modbus_rtu_cmd_0x04
��  ����04�Ź����봦������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x04(void);
/*-------------------------------------------------------
��������es_modbus_rtu_cmd_0x05
��  ����05�Ź����봦������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x05(void);
/*-------------------------------------------------------
��������es_modbus_rtu_cmd_0x06
��  ����06�Ź����봦������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x06(void);
/*-------------------------------------------------------
��������es_modbus_rtu_cmd_0x10
��  ����16�Ź����봦������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x10(void);
/*-------------------------------------------------------
��������es_modbus_rtu_exe
��  ����modbus_rtu����ִ�к������Ž�stream��������С�
��  �룺
    dat     ��stream��ܶԽӵĲ�����
��  ������
����ֵ����
�����ߣ�����
�ο����̣�
    void ecbm_stream_exe(u8 dat){
        es_modbus_rtu_exe(dat);
    }
�������ڣ�2021-10-28
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_modbus_rtu_exe(u8 dat);
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��