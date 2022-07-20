#ifndef _ECBM_SOFT_RTC_H_//头文件防止重加载必备，先看看有没有定义过这个，定义说明已经加载过一次了。
#define _ECBM_SOFT_RTC_H_//没定义说明是首次加载，那么往下执行。并且定义这个宏定义，防止下一次被加载。
/*-------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2021 奈特

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

免责说明：
    本软件库以MIT开源协议免费向大众提供。作者只保证原始版本是由作者在维护修BUG，
其他通过网络传播的版本也许被二次修改过，由此出现的BUG与作者无关。而当您使用原始
版本出现BUG时，请联系作者解决。
                            **************************
                            * 联系方式：进群778916610 *
                            **************************
------------------------------------------------------------------------------------*/
/*---------------------------------------宏定义------------------------------------*/
#define sr_u16 unsigned int
#define sr_u8  unsigned char
#define SOFTRTC_OK       0//操作OK
#define SOFTRTC_MON_ERR  1//月设置错误
#define SOFTRTC_DAY_ERR  2//日设置错误
#define SOFTRTC_HOUR_ERR 3//小时设置错误
#define SOFTRTC_MIN_ERR  4//分钟设置错误
#define SOFTRTC_SEC_ERR  5//秒钟设置错误
/*--------------------------------------变量定义-----------------------------------*/
sr_u16 soft_rtc_year;   //年
sr_u8  soft_rtc_month;  //月
sr_u8  soft_rtc_day;    //日
sr_u8  soft_rtc_hour;   //时
sr_u8  soft_rtc_minute; //分
sr_u8  soft_rtc_second; //秒
/*--------------------------------------函数定义-----------------------------------*/
/*-------------------------------------------------------
函数名：soft_rtc_get_day_max
描  述：获取天数最大值函数。
输  入：无
输  出：无
返回值：
    当前年份和当前月份的最大天数值。
创建者：奈特
调用例程：无
创建日期：2021-8-31
修改记录：
-------------------------------------------------------*/
extern sr_u8 soft_rtc_get_day_max(sr_u16 year,sr_u8 month);
/*-------------------------------------------------------
函数名：soft_rtc_run
描  述：跑时函数。每一秒运行一次即可。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-8-31
修改记录：
-------------------------------------------------------*/
extern void soft_rtc_run(void);
/*-------------------------------------------------------
函数名：soft_rtc_set_date
描  述：设置日期函数。
输  入：
    year    年份
    month   月份
    day     日期
输  出：无
返回值：
    0   设置正确
    1   月份设置错误
    2   日期设置错误
创建者：奈特
调用例程：无
创建日期：2021-8-31
修改记录：
-------------------------------------------------------*/
extern sr_u8 soft_rtc_set_date(sr_u16 year,sr_u8 month,sr_u8 day);
/*-------------------------------------------------------
函数名：soft_rtc_set_time
描  述：设置时间函数。
输  入：
    hour    时
    minute  分
    second  秒
输  出：无
返回值：
    0   设置正确
    3   时设置错误
    4   分设置错误
    5   秒设置错误
创建者：奈特
调用例程：无
创建日期：2021-8-31
修改记录：
-------------------------------------------------------*/
extern sr_u8 soft_rtc_set_time(sr_u8 hour,sr_u8 minute,sr_u8 second);
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。