#ifndef _ECBM_STREAM_ECP_H_//ͷ�ļ���ֹ�ؼ��رر����ȿ�����û�ж�������������˵���Ѿ����ع�һ���ˡ�
#define _ECBM_STREAM_ECP_H_//û����˵�����״μ��أ���ô����ִ�С����Ҷ�������궨�壬��ֹ��һ�α����ء�
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
//ep�İ汾���˰汾������stream�⡣
#define ES_ECP_VERSION "V1.0"
//<o>���ݻ����С
//<1-200>
//<i>�û����ڶ�ȡָ���д��ָ���ﶼ�õõ����������ڴ��㹻������£����õ�Խ��Խ�á�
#define ES_ECP_DATA_BUF_MAX 32
//<q>����ʹ��
//<i>���������������ӻ�����ô�������ִ���Ϳ��Բ�Ҫ�ˡ�ʡ��һ��ռ䡣
#define ES_ECP_MASTER_EN 0
//<<< end of configuration section >>>
//-----------------������ͼ�����ý��棬����Configuration Wizard��������-----------------
/*---------------------------------------ͷ�ļ�------------------------------------*/
#include "hal_config.h"
/*------------------------------------״̬���궨��---------------------------------*/
#define ES_ECP_READY             0   //��֡ͷ��
#define ES_ECP_GET_DATA_LEN      1   //��ȡ���ݳ��ȡ�
#define ES_ECP_CHECK_DATA_LEN    2   //������ݳ��ȡ�
#define ES_ECP_GET_TARGET_ID     3   //��ȡĿ��ID��
#define ES_ECP_GET_SOURCE_ID     4   //��ȡԴͷID��
#define ES_ECP_GET_OPERATION     5   //��ȡ�����롣
#define ES_ECP_GET_ADDR_31_24    6   //��ȡ��ַ31~24��
#define ES_ECP_GET_ADDR_23_16    7   //��ȡ��ַ23~16��
#define ES_ECP_GET_ADDR_15_8     8   //��ȡ��ַ15~8��
#define ES_ECP_GET_ADDR_7_0      9   //��ȡ��ַ7~0��
#define ES_ECP_GET_DATA          10  //��ȡ���ݡ�
#define ES_ECP_GET_CRC_H         11  //��ȡCRC��λ��
#define ES_ECP_GET_CRC_L         12  //��ȡCRC��λ��
#define ES_ECP_END               13  //��֡β��
/*--------------------------------------��������-----------------------------------*/
extern u8  es_ecp_status;        //״̬��������
extern u8  es_ecp_data_len;      //���ڴ�Ų��������ݵĳ��ȡ�
extern u8  es_ecp_count;         //����ͳ��ʵ�ʽ��յĲ��������ݳ��ȡ�
extern u8  es_ecp_source_id;     //ԴͷID�������֡�����ID������������
extern u8  es_ecp_target_id;     //Ŀ��ID�������֡Ӧ�������ID���������ա�
extern u8  es_ecp_operation;     //�����뻺�档
extern u16 es_ecp_addr16_ex;     //16λ��չ��ַ���档
extern u16 es_ecp_addr16;        //16λ��ַ���档
extern u16 es_ecp_crc;           //���ڼ���������ݵ�CRC��
extern u16 es_ecp_crc_buf;       //���ڴ������֡���CRC��
extern u8  es_ecp_data_buf[ES_ECP_DATA_BUF_MAX];//���ڶ�д�����Ļ��档
/*--------------------------------------������-----------------------------------*/
/*------------------��Ҫ�û�����ĺ���------------------*/
/*-------------------------------------------------------
��������es_ecp_get_id
��  ������ȡ������ID������
��  �룺��
��  ������
����ֵ��
    ���豸��ID��
�����ߣ�����
�ο����̣�
    u8 es_ecp_get_id(void){
        return 1;
    }
�������ڣ�2022-05-27
�޸ļ�¼��
-------------------------------------------------------*/
extern u8 es_ecp_get_id(void);
/*-------------------------------------------------------
��������es_ecp_write
��  ����ECP��д�뺯����
��  �룺
    addr    д��ĵ�ַ��
    buf     д�����ݵĻ��档
    len     д�����������
��  ������  
����ֵ����
�����ߣ�����
�ο����̣�
    void es_ecp_write(u16 addr,u8 * buf,u8 len){
        u8 i;
        for(i=0;i<len;i++){
            es_ecp_test[i]=buf[i];
        }
    }
�������ڣ�2022-05-27
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_write(u16 addr,u8 * buf,u8 len);
/*-------------------------------------------------------
��������es_ecp_read
��  ����ECP�Ķ�ȡ������
��  �룺
    addr    ��ȡ�ĵ�ַ��
    buf     ��ȡ���ݵĻ��档
    len     ��ȡ����������
��  ������  
����ֵ����
�����ߣ�����
�ο����̣�
    void es_ecp_read(u16 addr,u8 * buf,u8 len){
        u8 i;
        for(i=0;i<len;i++){
            buf[i]=es_ecp_test[i];
        }
    }
�������ڣ�2022-05-27
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_read(u16 addr,u8 * buf,u8 len);
/*-------------------------------------------------------
��������es_ecp_read_callback
��  ����ECP�Ķ�ȡ�ص�����������Ϊ�������Ͷ�ȡָ��֮���յ��ӻ��������ݵ�ʱ��ִ�б�������
��  �룺
    addr    ��ȡ�ĵ�ַ��
    buf     ��ȡ���ݵĻ��档
    len     ��ȡ����������
��  ������  
����ֵ����
�����ߣ�����
�ο����̣�
    void es_ecp_read_callback(u16 addr,u8 * buf,u8 len){
        if(addr==0x0000){
            oled_show(0,0,"%s",buf);
        }
    }
�������ڣ�2022-05-30
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_read_callback(u16 addr,u8 * buf,u8 len);
/*----------------------ϵͳ����-----------------------*/
/*-------------------------------------------------------
��������es_ecp_crc16
��  ����CRCУ�麯����
��  �룺
    crc     ��ǰ��CRCֵ��
    buf     ��ǰ��Ҫ����CRCУ������ݡ�
��  ������  
����ֵ��
    ���������õ�����CRCֵ��
�����ߣ�����
�ο����̣���
�������ڣ�2022-05-27
�޸ļ�¼��
-------------------------------------------------------*/
extern u16 es_ecp_crc16(u16 crc,u8 buf);
/*-------------------------------------------------------
��������es_ecp_cmd02
��  ����02ָ�������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2022-05-27
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_cmd02(void);
/*-------------------------------------------------------
��������es_ecp_cmd04
��  ����04ָ�������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2022-05-27
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_cmd04(void);
/*-------------------------------------------------------
��������es_ecp_cmd06
��  ����06ָ�������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2022-05-31
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_cmd06(void);
/*-------------------------------------------------------
��������es_ecp_cmd08
��  ����08ָ�������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2022-05-31
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_cmd08(void);
/*-------------------------------------------------------
��������es_ecp_master_write
��  ����ECP����д��������һ���ӻ�д��һ�����ݡ�
��  �룺
    id      �ӻ���ID��
    addr    Ҫд����׵�ַ��
    buf     Ҫд������ݡ�
    len     Ҫд�����ݵĳ��ȡ�
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2022-05-30
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_master_write(u8 id,u16 addr,u8 * buf,u8 len);
/*-------------------------------------------------------
��������es_ecp_master_read
��  ����ECP��������������һ���ӻ����Ͷ����������յ��ӻ�������ʱ����ûص�������
��  �룺
    id      �ӻ���ID��
    addr    Ҫ��ȡ���׵�ַ��
    len     Ҫ��ȡ���ݵĳ��ȡ�
��  ������
����ֵ����
�����ߣ�����
�ο����̣���
�������ڣ�2022-05-30
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_master_read(u8 id,u16 addr,u8 len);
/*-------------------------------------------------------
��������es_ecp_exe
��  ����ECP����ִ�к������Ž�stream��������С�
��  �룺
    dat     ��stream��ܶԽӵĲ�����
��  ������
����ֵ����
�����ߣ�����
�ο����̣�
    void ecbm_stream_exe(u8 dat){
        es_ecp_exe(dat);
    }
�������ڣ�2022-05-27
�޸ļ�¼��
-------------------------------------------------------*/
extern void es_ecp_exe(u8 dat);
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��