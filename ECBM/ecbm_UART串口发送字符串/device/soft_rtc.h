#ifndef _ECBM_SOFT_RTC_H_//ͷ�ļ���ֹ�ؼ��رر����ȿ�����û�ж�������������˵���Ѿ����ع�һ���ˡ�
#define _ECBM_SOFT_RTC_H_//û����˵�����״μ��أ���ô����ִ�С����Ҷ�������궨�壬��ֹ��һ�α����ء�
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
/*---------------------------------------�궨��------------------------------------*/
#define sr_u16 unsigned int
#define sr_u8  unsigned char
#define SOFTRTC_OK       0//����OK
#define SOFTRTC_MON_ERR  1//�����ô���
#define SOFTRTC_DAY_ERR  2//�����ô���
#define SOFTRTC_HOUR_ERR 3//Сʱ���ô���
#define SOFTRTC_MIN_ERR  4//�������ô���
#define SOFTRTC_SEC_ERR  5//�������ô���
/*--------------------------------------��������-----------------------------------*/
sr_u16 soft_rtc_year;   //��
sr_u8  soft_rtc_month;  //��
sr_u8  soft_rtc_day;    //��
sr_u8  soft_rtc_hour;   //ʱ
sr_u8  soft_rtc_minute; //��
sr_u8  soft_rtc_second; //��
/*--------------------------------------��������-----------------------------------*/
/*-------------------------------------------------------
��������soft_rtc_get_day_max
��  ������ȡ�������ֵ������
��  �룺��
��  ������
����ֵ��
    ��ǰ��ݺ͵�ǰ�·ݵ��������ֵ��
�����ߣ�����
�������̣���
�������ڣ�2021-8-31
�޸ļ�¼��
-------------------------------------------------------*/
extern sr_u8 soft_rtc_get_day_max(sr_u16 year,sr_u8 month);
/*-------------------------------------------------------
��������soft_rtc_run
��  ������ʱ������ÿһ������һ�μ��ɡ�
��  �룺��
��  ������
����ֵ����
�����ߣ�����
�������̣���
�������ڣ�2021-8-31
�޸ļ�¼��
-------------------------------------------------------*/
extern void soft_rtc_run(void);
/*-------------------------------------------------------
��������soft_rtc_set_date
��  �����������ں�����
��  �룺
    year    ���
    month   �·�
    day     ����
��  ������
����ֵ��
    0   ������ȷ
    1   �·����ô���
    2   �������ô���
�����ߣ�����
�������̣���
�������ڣ�2021-8-31
�޸ļ�¼��
-------------------------------------------------------*/
extern sr_u8 soft_rtc_set_date(sr_u16 year,sr_u8 month,sr_u8 day);
/*-------------------------------------------------------
��������soft_rtc_set_time
��  ��������ʱ�亯����
��  �룺
    hour    ʱ
    minute  ��
    second  ��
��  ������
����ֵ��
    0   ������ȷ
    3   ʱ���ô���
    4   �����ô���
    5   �����ô���
�����ߣ�����
�������̣���
�������ڣ�2021-8-31
�޸ļ�¼��
-------------------------------------------------------*/
extern sr_u8 soft_rtc_set_time(sr_u8 hour,sr_u8 minute,sr_u8 second);
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��