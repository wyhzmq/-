#include "soft_rtc.h"   //加载头文件。
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
获取天数最大值函数。
-------------------------------------------------------*/
sr_u8 soft_rtc_get_day_max(sr_u16 year,sr_u8 month){
    if((month==4)||(month==6)||(month==9)||(month==11)){//4.6.9.11这几个月的时候，
        return 30;//一个月30天。
    }else if(month==2){//2月份比较特殊。
        if(((year%4==0)&&(year%100!=0))||(year%400==0)){//先判断当前是平年还是闰年。
            return 29;//闰年一个月29天。
        }else{
            return 28;//平年一个月28天。
        }
    }else{
        return 31;//其他月份都是一个月31天。
    }
}
/*-------------------------------------------------------
跑时函数。
-------------------------------------------------------*/
void soft_rtc_run(void){
    sr_u8 day_max;
    soft_rtc_second++;      //秒+1。
    if(soft_rtc_second>=60){//到了60秒，
        soft_rtc_second=0;  //秒清零。
        soft_rtc_minute++;  //分+1。
        if(soft_rtc_minute>=60){//到了60分。
            soft_rtc_minute=0;//分清零。
            soft_rtc_hour++;    //时+1。
            if(soft_rtc_hour>=24){//到了24时。
                soft_rtc_hour=0;//时清零。
                soft_rtc_day++;//天+1。
                day_max=soft_rtc_get_day_max(soft_rtc_year,soft_rtc_month);//获取当年当月的最大天数。
                if(soft_rtc_day>day_max){//天数大于一个月最大天数时，
                    soft_rtc_day=1;//天恢复。
                    soft_rtc_month++;//月份+1。
                    if(soft_rtc_month>12){//超过12个月的话，
                        soft_rtc_month=1;//月恢复
                        soft_rtc_year++;//年份+1。
                    }
                }
            }
        }
    }
}
/*-------------------------------------------------------
设置日期函数。
-------------------------------------------------------*/
sr_u8 soft_rtc_set_date(sr_u16 year,sr_u8 month,sr_u8 day){
    sr_u8 day_max;
    soft_rtc_year=year;
    if((month>=1)&&(month<=12)){
        soft_rtc_month=month;
    }else{
        return SOFTRTC_MON_ERR;
    }
    day_max=soft_rtc_get_day_max(soft_rtc_year,soft_rtc_month);//获取当年当月的最大天数。
    if((day>=1)&&(day<=day_max)){
        soft_rtc_day=day;
    }else{
        return SOFTRTC_DAY_ERR;
    }
    return SOFTRTC_OK;
}
/*-------------------------------------------------------
设置时间函数。
-------------------------------------------------------*/
sr_u8 soft_rtc_set_time(sr_u8 hour,sr_u8 minute,sr_u8 second){
    if(hour  <24){soft_rtc_hour  =hour;  }else{return SOFTRTC_HOUR_ERR;}
    if(minute<60){soft_rtc_minute=minute;}else{return SOFTRTC_MIN_ERR; }
    if(second<60){soft_rtc_second=second;}else{return SOFTRTC_SEC_ERR; }
    return SOFTRTC_OK;
}