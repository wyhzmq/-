#include "soft_rtc.h"   //����ͷ�ļ���
/*--------------------------------------������-----------------------------------*/
/*-------------------------------------------------------
��ȡ�������ֵ������
-------------------------------------------------------*/
sr_u8 soft_rtc_get_day_max(sr_u16 year,sr_u8 month){
    if((month==4)||(month==6)||(month==9)||(month==11)){//4.6.9.11�⼸���µ�ʱ��
        return 30;//һ����30�졣
    }else if(month==2){//2�·ݱȽ����⡣
        if(((year%4==0)&&(year%100!=0))||(year%400==0)){//���жϵ�ǰ��ƽ�껹�����ꡣ
            return 29;//����һ����29�졣
        }else{
            return 28;//ƽ��һ����28�졣
        }
    }else{
        return 31;//�����·ݶ���һ����31�졣
    }
}
/*-------------------------------------------------------
��ʱ������
-------------------------------------------------------*/
void soft_rtc_run(void){
    sr_u8 day_max;
    soft_rtc_second++;      //��+1��
    if(soft_rtc_second>=60){//����60�룬
        soft_rtc_second=0;  //�����㡣
        soft_rtc_minute++;  //��+1��
        if(soft_rtc_minute>=60){//����60�֡�
            soft_rtc_minute=0;//�����㡣
            soft_rtc_hour++;    //ʱ+1��
            if(soft_rtc_hour>=24){//����24ʱ��
                soft_rtc_hour=0;//ʱ���㡣
                soft_rtc_day++;//��+1��
                day_max=soft_rtc_get_day_max(soft_rtc_year,soft_rtc_month);//��ȡ���굱�µ����������
                if(soft_rtc_day>day_max){//��������һ�����������ʱ��
                    soft_rtc_day=1;//��ָ���
                    soft_rtc_month++;//�·�+1��
                    if(soft_rtc_month>12){//����12���µĻ���
                        soft_rtc_month=1;//�»ָ�
                        soft_rtc_year++;//���+1��
                    }
                }
            }
        }
    }
}
/*-------------------------------------------------------
�������ں�����
-------------------------------------------------------*/
sr_u8 soft_rtc_set_date(sr_u16 year,sr_u8 month,sr_u8 day){
    sr_u8 day_max;
    soft_rtc_year=year;
    if((month>=1)&&(month<=12)){
        soft_rtc_month=month;
    }else{
        return SOFTRTC_MON_ERR;
    }
    day_max=soft_rtc_get_day_max(soft_rtc_year,soft_rtc_month);//��ȡ���굱�µ����������
    if((day>=1)&&(day<=day_max)){
        soft_rtc_day=day;
    }else{
        return SOFTRTC_DAY_ERR;
    }
    return SOFTRTC_OK;
}
/*-------------------------------------------------------
����ʱ�亯����
-------------------------------------------------------*/
sr_u8 soft_rtc_set_time(sr_u8 hour,sr_u8 minute,sr_u8 second){
    if(hour  <24){soft_rtc_hour  =hour;  }else{return SOFTRTC_HOUR_ERR;}
    if(minute<60){soft_rtc_minute=minute;}else{return SOFTRTC_MIN_ERR; }
    if(second<60){soft_rtc_second=second;}else{return SOFTRTC_SEC_ERR; }
    return SOFTRTC_OK;
}