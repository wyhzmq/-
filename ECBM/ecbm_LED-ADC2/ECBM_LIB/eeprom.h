#ifndef _ECBM_EEPROM_H_//ͷ�ļ���ֹ�ؼ��رر����ȿ�����û�ж�������������˵���Ѿ����ع�һ���ˡ�
#define _ECBM_EEPROM_H_//û����˵�����״μ��أ���ô����ִ�С����Ҷ�������궨�壬��ֹ��һ�α����ء�
/*-------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2019 ����

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
//<q>����EEPROM���캯����
//<i>���캯����ռ��512�ֽڵ�XDATA�ռ䣬�ռ���ŵ�ʱ����Բ����š�
//<i>���ŵĻ�����ͨ������512�ֽڵĻ��棬ʹ������eeprom����ֱ��д�����ֽڣ����Ҳ����ֶ�������
#define ECBM_EEPROM_EX_EN 0
//<q>Eeprom-Data-System���
//<i>����һ��רΪflash�����eeprom��������ݹ���ϵͳ��ģ��ƽ����ĸ��ʹ��flash�ռ�����flash������
//<i>ͬʱ��ʵ������eeprom��Ч������д�뺯������ֱ��д�룬����Ҫ������
#define ECBM_EEPROM_EDS_EN 0
//<<< end of configuration section >>>
/*---------------------------------------ͷ�ļ�------------------------------------*/
#include "ecbm_core.h"    //ECBM���ͷ�ļ��������Ѿ�������STC8��ͷ�ļ���
/*--------------------------------------��������-----------------------------------*/
extern u8 xdata eeprom_buf[512];
/*--------------------------------------������-----------------------------------*/
/*-------------------------------------------------------
��������eeprom_init
��  ����eeprom��ʼ��������
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2020-04-29
�޸ļ�¼��
2020-04-29�������˶�STC8Gϵ�е�֧�֡�
2021-06-10�������˶�STC8A8K64D4��֧�֡�
-------------------------------------------------------*/
extern void eeprom_init(void);
/*-------------------------------------------------------
��������eeprom_erase
��  ����eeprom����������stc��eeprom������flash��������ģ�������д֮ǰҪ������
        ͬʱ��Ϊһ��������512�ֽڣ�����������һ���ֽڣ��ͻ��ͬһ����������511�ֽ�һ�������
        �úú�ע��������⣬�ö�дflash��˼ά��ʹ�����eeprom��
��  �룺
    addr    Ҫ�����ĵ�ַ��������õ�ַ���ڵ�����������ȫ�����ݡ�
��  ������
����ֵ����
�����ߣ�����
�������̣�
    ...//�����޹صĴ��롣
    eeprom_erase(30);//������ַ30�����ݣ���������30�ǵ�0����������0~511������Ҳ��һ������������
    ...//�����޹صĴ��롣
�������ڣ�2019-10-12
�޸ļ�¼��
2020-04-29�������˶�STC8Gϵ�е�֧�֡�
2020-11-10��ɾ���˶Ե�ַ�ռ���жϡ�
-------------------------------------------------------*/
extern void eeprom_erase(u16 addr);
/*-------------------------------------------------------
��������eeprom_write
��  ����eepromд������
��  �룺
    addr    Ҫд����ֵ�ĵ�ַ
    dat     Ҫд�����ֵ����Χ��u8�ͣ���0~255��
��  ������
����ֵ����
�����ߣ�����
�������̣�
    ...//�����޹صĴ��롣
    eeprom_write(123,15);//����ֵ15д�뵽��ַ123��ȥ��
    ...//�����޹صĴ��롣
�������ڣ�2019-10-12
�޸ļ�¼��
2020-04-29�������˶�STC8Gϵ�е�֧�֡�
2020-11-10��ɾ���˶Ե�ַ�ռ���жϡ�
-------------------------------------------------------*/
extern void eeprom_write(u16 addr,u8 dat);
/*-------------------------------------------------------
��������eeprom_read
��  ����eeprom��������
��  �룺
    addr    Ҫ��ȡ�ĵ�ַ
��  ������
����ֵ��
    �õ�ַ���ֵ
�����ߣ�����
�������̣�
    ...//�����޹صĴ��롣
    val=eeprom_read(56);//��ȡ��ַ56��ֵ���������val��
    ...//�����޹صĴ��롣
�������ڣ�2019-10-12
�޸ļ�¼��
2020-04-29�������˶�STC8Gϵ�е�֧�֡�
2020-11-10��ɾ���˶Ե�ַ�ռ���жϡ�
-------------------------------------------------------*/
extern u8 eeprom_read(u16 addr);
/*-------------------------------------------------------
��������eeprom_read_ex
��  ����eeprom�����������(extension)��
��  �룺
    addr    ��ʼ��ַ
    dat     Ҫ�������ݵĻ���
    num     Ҫ�������ݵ�����
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2020-04-29
�޸ļ�¼��
-------------------------------------------------------*/
extern void eeprom_read_ex(u16 addr,u8 * dat,u16 num);
/*-------------------------------------------------------
��������eeprom_write_ex
��  ����eepromд���������(extension)��
��  �룺
    addr    ��ʼ��ַ
    dat     Ҫд�����ݵĻ���
    num     Ҫд�����ݵ�����
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2020-04-29
�޸ļ�¼��
-------------------------------------------------------*/
extern void eeprom_write_ex(u16 addr,u8 * dat,u16 num);
/*-------------------------------------------------------
��������eds_check
��  ����eds��麯����
��  �룺
    addr    ��ʼ��ַ��
��  ������
����ֵ��
    EDS_OK          EDS���ж�������
    EDS_ERR_NULL    �Ҳ���EDS��
    EDS_ERR_ID      EDS�е�ID����
�����ߣ�����
�������̣���
�������ڣ�2022-04-21
�޸ļ�¼��
-------------------------------------------------------*/
#define EDS_OK              0   //EDS���ж�������
#define EDS_ERR_NULL        1   //�Ҳ���EDS��
#define EDS_ERR_ID          2   //EDS�е�ID����
#define EDS_ERR_SECTOR      3   //EDS��ʼ��ʱ����û���öԡ�
#define EDS_DATA_VOID       4   //EDS��û�����ݡ�
extern u8 eds_check(u16 addr);
/*-------------------------------------------------------
��������eds_erase
��  ����eds����������
��  �룺
    sector_start    ��ʼ������
    sector_szie     ��������/�ܴ�С��
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2022-04-21
�޸ļ�¼��
-------------------------------------------------------*/
extern void eds_erase(u8 sector_start,u8 sector_szie);
/*-------------------------------------------------------
��������eds_init
��  ����eds��ʼ��������
��  �룺
    sector_start    ��ʼ������
    sector_szie     ��������/�ܴ�С��
    pack_len        ���ݰ���С��
��  ������
����ֵ��
    EDS_OK          EDS���ж�������
    EDS_ERR_SECTOR  EDS��ʼ��ʱ����û���öԡ�
    EDS_DATA_VOID   EDS��û�����ݡ�
�����ߣ�����
�������̣���
�������ڣ�2022-04-21
�޸ļ�¼��
-------------------------------------------------------*/
extern u8 eds_init(u8 sector_start,u8 sector_szie,u16 pack_len);
/*-------------------------------------------------------
��������eds_write
��  ����edsд������
��  �룺
    sector_start    ��ʼ������
    buf             Ҫд������ݰ���
��  ������
����ֵ��
    EDS_OK          EDS���ж�������
    EDS_ERR_NULL    �Ҳ���EDS��
    EDS_ERR_ID      EDS�е�ID����
    EDS_DATA_VOID   EDS��û�����ݡ�
�����ߣ�����
�������̣���
�������ڣ�2022-04-21
�޸ļ�¼��
-------------------------------------------------------*/
extern u8 eds_write(u8 sector_start,u8 * buf);
/*-------------------------------------------------------
��������eds_read
��  ����eds��������
��  �룺
    sector_start    ��ʼ������
��  ����
    buf             ��ȡ�������ݰ���
����ֵ��
    EDS_OK          EDS���ж�������
    EDS_ERR_NULL    �Ҳ���EDS��
    EDS_ERR_ID      EDS�е�ID����
    EDS_DATA_VOID   EDS��û�����ݡ�
�����ߣ�����
�������̣���
�������ڣ�2022-04-21
�޸ļ�¼��
-------------------------------------------------------*/
extern u8 eds_read(u8 sector_start,u8 * buf);
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��