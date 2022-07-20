#ifndef _ECBM_STREAM_H_//头文件防止重加载必备，先看看有没有定义过这个，定义说明已经加载过一次了。
#define _ECBM_STREAM_H_//没定义说明是首次加载，那么往下执行。并且定义这个宏定义，防止下一次被加载。
/*-------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2022 奈特

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
                            * 若1群满人：进群927297508*
                            **************************
------------------------------------------------------------------------------------*/
//-----------------以下是图形设置界面，可在Configuration Wizard界面设置-----------------
//<<< Use Configuration Wizard in Context Menu >>>
#define ECBM_STREAM_VERSION "V1.3"
//<o>队列缓存大小
//<i>单位“字节”。
#define ECBM_STREAM_SZIE     135
//<o>数据帧间隔时间
//<10-2500:10>
//<i>单位mS。默认定时器10mS中断一次,因此这个时间是10的倍数。
//<i>从接收到最后一个数据开始计算，超过这个时间没有再次接受到数据时，认为对方已经传送完一个数据帧。
#define ECBM_STREAM_TIME_MS  20
#define ECBM_STREAM_TIME_MAX (ECBM_STREAM_TIME_MS/10)
//<o>串口空闲时间
//<10-2500:10>
//<i>单位mS。默认定时器10mS中断一次,因此这个时间是10的倍数。
//<i>从接收到最后一个数据开始计算，超过这个时间没有再次接收到数据时，认为对方已经发送完全部数据，串口恢复到空闲状态。
//<i>该值应该比数据帧间隔时间大。
#define ECBM_STREAM_IDLE_MS  80
#define ECBM_STREAM_IDLE_MAX (ECBM_STREAM_IDLE_MS/10)
//<h>组件使能
//<q>比较组件
//<i>就是对接收到的字符串和目标字符串进行比较，当缓冲区存在目标字符串的时候，可以触发某些动作。
#define ECBM_STREAM_CMP_EN 0
//<q>FUR组件
//<i>这是ECBM自主研发的快速(Fast)串口(Uart)访问寄存器(Reg)组件。
//<i>基于ASCII码的明文通信，协议通俗易懂，不仅可以快速读写寄存器，还能对其进行运算。
#define ECBM_STREAM_FUR_EN 0
//<q>MODBUS组件
//<i>通用的MODBUS协议RTU版本，目前集成了[01][05][03][06][10][02][04]共7个指令。
//<i>这个组件也是用于读写寄存器的。
#define ECBM_STREAM_MODBUS_EN 0
//<q>X-MODEM组件
//<i>通用的X-MODEM协议，采用了每包128字节和校验和的版本。
//<i>这个组件用于传输大量数据或者文件。
#define ECBM_STREAM_XMODEM_EN 0
//<q>ECP组件
//<i>这是ECBM自主研发的ECBM通信(Communication)协议(Protocol)组件。
//<i>这个组件可以以高质量传输一些重要的、少量的数据。
//<i>不过在单片机没有其他任务的时候也可以全速跑ECP来传输大量数据。
#define ECBM_STREAM_ECP_EN 1
//</h>
//<<< end of configuration section >>>
//-----------------以上是图形设置界面，可在Configuration Wizard界面设置-----------------
/*---------------------------------------头文件------------------------------------*/
#include "ecbm_core.h"    //ECBM库的头文件，里面已经包含了STC8的头文件。
/*---------------------------------------宏定义------------------------------------*/
#define ECBM_STREAM_TIME_EN   0x01  //计时使能。
#define ECBM_STREAM_TIME_OUT  0x02  //定时器超时标志。
#define ECBM_STREAM_UART_IDLE 0x04  //串口空闲标志。
/*--------------------------------------变量定义-----------------------------------*/
extern u8 xdata ecbm_stream_buf[ECBM_STREAM_SZIE];  //stream的接收缓存。
extern u8 ecbm_stream_start;                  //读缓存时候的开始地址。
extern u8 ecbm_stream_stop;                   //读缓存时候的结束地址。
extern u8 ecbm_stream_count;                  //接收到的数据数量。
extern u8 ecbm_stream_time;                   //定时器计时变量。
extern u8 ecbm_stream_status;                 //steam状态。
/*--------------------------------------函数定义-----------------------------------*/
///////////////////////////////////需要用户定义的函数////////////////////////////////
/*-------------------------------------------------------
函数名：ecbm_stream_exe
描  述：流处理函数，可根据需要添加。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-24
修改记录：
-------------------------------------------------------*/
extern void ecbm_stream_exe(u8 dat);
///////////////////////////////////需要用户移植的函数////////////////////////////////
/*-------------------------------------------------------
函数名：ECBM_STREAM_IN
描  述：数据接收函数，由于只有一处调用，为了快速响应做成了宏定义。
输  入：
    dat     接收到的数据
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-24
修改记录：
2021-11-11：针对串口空闲的判断做了修改。
-------------------------------------------------------*/
#define ECBM_STREAM_IN(dat) do{\
    ecbm_stream_time=0;                     /*重置计时值*/\
    ecbm_stream_status=ECBM_STREAM_TIME_EN; /*激活定时器并清除标志位*/\
    ecbm_stream_buf[ecbm_stream_stop++]=dat;/*接收数据到缓存同时队尾指针增加*/\
    ecbm_stream_count++;                    /*数据计数增加*/\
    if(ecbm_stream_stop>=ECBM_STREAM_SZIE){ /*如果队尾超过队列最大值*/\
        ecbm_stream_stop=0;                 /*就切换到队列最前*/\
    }\
}while(0)
/*-------------------------------------------------------
函数名：ECBM_STREAM_TIME_RUN
描  述：时间运行函数，用于提供流处理的时间判断功能。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-24
修改记录：
2021-11-11：新增了串口空闲的判断。
-------------------------------------------------------*/    
#define ECBM_STREAM_TIME_RUN()   do{\
    if(ecbm_stream_status&ECBM_STREAM_TIME_EN){       /*处于运行状态时*/\
        ecbm_stream_time++;                           /*每次定时器中断加一次*/\
        if(ecbm_stream_time>ECBM_STREAM_TIME_MAX){    /*超过了间隔时间最大值时*/\
            ecbm_stream_status|=ECBM_STREAM_TIME_OUT; /*变成超时状态*/\
        }\
        if(ecbm_stream_time>ECBM_STREAM_IDLE_MAX){    /*超过了空闲时间最大值时*/\
            ecbm_stream_status|=ECBM_STREAM_UART_IDLE;/*变成空闲状态*/\
            ecbm_stream_status&=~ECBM_STREAM_TIME_EN; /*空闲时关闭计时*/\
        }\
    }\
}while(0)
/*-------------------------------------------------------
函数名：ecbm_stream_main
描  述：流处理主函数函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-24
修改记录：
2021-11-11：针对串口空闲的判断做了修改。
-------------------------------------------------------*/
extern void ecbm_stream_main(void);
/*-------------------------------------------------------
函数名：ecbm_stream_cmp
描  述：流处理比对函数。
输  入：
    dat     和ecbm_stream_exe对接的接口。
    str     需要比对的字符串。
输  出：
    count   比对的计数值，当该值和字符串长度相等时，表示比对成功。
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-10-21
修改记录：
-------------------------------------------------------*/
#if ECBM_STREAM_CMP_EN
extern void ecbm_stream_strcmp(u8 dat,u8 code * str,u8 * count);
#endif
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。