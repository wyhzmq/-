#ifndef _ECBM_STREAM_ECP_H_//头文件防止重加载必备，先看看有没有定义过这个，定义说明已经加载过一次了。
#define _ECBM_STREAM_ECP_H_//没定义说明是首次加载，那么往下执行。并且定义这个宏定义，防止下一次被加载。
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
//ep的版本。此版本隶属于stream库。
#define ES_ECP_VERSION "V1.0"
//<o>数据缓存大小
//<1-200>
//<i>该缓存在读取指令和写入指令里都用得到，所以在内存足够的情况下，设置得越大越好。
#define ES_ECP_DATA_BUF_MAX 32
//<q>主机使能
//<i>若仅仅是拿来当从机，那么主机部分代码就可以不要了。省出一点空间。
#define ES_ECP_MASTER_EN 0
//<<< end of configuration section >>>
//-----------------以上是图形设置界面，可在Configuration Wizard界面设置-----------------
/*---------------------------------------头文件------------------------------------*/
#include "hal_config.h"
/*------------------------------------状态机宏定义---------------------------------*/
#define ES_ECP_READY             0   //等帧头。
#define ES_ECP_GET_DATA_LEN      1   //读取数据长度。
#define ES_ECP_CHECK_DATA_LEN    2   //检查数据长度。
#define ES_ECP_GET_TARGET_ID     3   //读取目标ID。
#define ES_ECP_GET_SOURCE_ID     4   //读取源头ID。
#define ES_ECP_GET_OPERATION     5   //读取操作码。
#define ES_ECP_GET_ADDR_31_24    6   //读取地址31~24。
#define ES_ECP_GET_ADDR_23_16    7   //读取地址23~16。
#define ES_ECP_GET_ADDR_15_8     8   //读取地址15~8。
#define ES_ECP_GET_ADDR_7_0      9   //读取地址7~0。
#define ES_ECP_GET_DATA          10  //读取数据。
#define ES_ECP_GET_CRC_H         11  //读取CRC高位。
#define ES_ECP_GET_CRC_L         12  //读取CRC低位。
#define ES_ECP_END               13  //等帧尾。
/*--------------------------------------变量定义-----------------------------------*/
extern u8  es_ecp_status;        //状态机变量。
extern u8  es_ecp_data_len;      //用于存放参数、数据的长度。
extern u8  es_ecp_count;         //用于统计实际接收的参数、数据长度。
extern u8  es_ecp_source_id;     //源头ID，代表该帧由这个ID的器件发出。
extern u8  es_ecp_target_id;     //目标ID，代表该帧应该由这个ID的器件接收。
extern u8  es_ecp_operation;     //操作码缓存。
extern u16 es_ecp_addr16_ex;     //16位扩展地址缓存。
extern u16 es_ecp_addr16;        //16位地址缓存。
extern u16 es_ecp_crc;           //用于计算接收数据的CRC。
extern u16 es_ecp_crc_buf;       //用于存放数据帧里的CRC。
extern u8  es_ecp_data_buf[ES_ECP_DATA_BUF_MAX];//用于读写操作的缓存。
/*--------------------------------------程序定义-----------------------------------*/
/*------------------需要用户定义的函数------------------*/
/*-------------------------------------------------------
函数名：es_ecp_get_id
描  述：获取本机的ID函数。
输  入：无
输  出：无
返回值：
    本设备的ID。
创建者：奈特
参考例程：
    u8 es_ecp_get_id(void){
        return 1;
    }
创建日期：2022-05-27
修改记录：
-------------------------------------------------------*/
extern u8 es_ecp_get_id(void);
/*-------------------------------------------------------
函数名：es_ecp_write
描  述：ECP的写入函数。
输  入：
    addr    写入的地址。
    buf     写入数据的缓存。
    len     写入的数据量。
输  出：无  
返回值：无
创建者：奈特
参考例程：
    void es_ecp_write(u16 addr,u8 * buf,u8 len){
        u8 i;
        for(i=0;i<len;i++){
            es_ecp_test[i]=buf[i];
        }
    }
创建日期：2022-05-27
修改记录：
-------------------------------------------------------*/
extern void es_ecp_write(u16 addr,u8 * buf,u8 len);
/*-------------------------------------------------------
函数名：es_ecp_read
描  述：ECP的读取函数。
输  入：
    addr    读取的地址。
    buf     读取数据的缓存。
    len     读取的数据量。
输  出：无  
返回值：无
创建者：奈特
参考例程：
    void es_ecp_read(u16 addr,u8 * buf,u8 len){
        u8 i;
        for(i=0;i<len;i++){
            buf[i]=es_ecp_test[i];
        }
    }
创建日期：2022-05-27
修改记录：
-------------------------------------------------------*/
extern void es_ecp_read(u16 addr,u8 * buf,u8 len);
/*-------------------------------------------------------
函数名：es_ecp_read_callback
描  述：ECP的读取回调函数，当作为主机发送读取指令之后，收到从机返回数据的时候，执行本函数。
输  入：
    addr    读取的地址。
    buf     读取数据的缓存。
    len     读取的数据量。
输  出：无  
返回值：无
创建者：奈特
参考例程：
    void es_ecp_read_callback(u16 addr,u8 * buf,u8 len){
        if(addr==0x0000){
            oled_show(0,0,"%s",buf);
        }
    }
创建日期：2022-05-30
修改记录：
-------------------------------------------------------*/
extern void es_ecp_read_callback(u16 addr,u8 * buf,u8 len);
/*----------------------系统函数-----------------------*/
/*-------------------------------------------------------
函数名：es_ecp_crc16
描  述：CRC校验函数。
输  入：
    crc     当前的CRC值。
    buf     当前需要进行CRC校验的数据。
输  出：无  
返回值：
    经过计算后得到的新CRC值。
创建者：奈特
参考例程：无
创建日期：2022-05-27
修改记录：
-------------------------------------------------------*/
extern u16 es_ecp_crc16(u16 crc,u8 buf);
/*-------------------------------------------------------
函数名：es_ecp_cmd02
描  述：02指令处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2022-05-27
修改记录：
-------------------------------------------------------*/
extern void es_ecp_cmd02(void);
/*-------------------------------------------------------
函数名：es_ecp_cmd04
描  述：04指令处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2022-05-27
修改记录：
-------------------------------------------------------*/
extern void es_ecp_cmd04(void);
/*-------------------------------------------------------
函数名：es_ecp_cmd06
描  述：06指令处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2022-05-31
修改记录：
-------------------------------------------------------*/
extern void es_ecp_cmd06(void);
/*-------------------------------------------------------
函数名：es_ecp_cmd08
描  述：08指令处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2022-05-31
修改记录：
-------------------------------------------------------*/
extern void es_ecp_cmd08(void);
/*-------------------------------------------------------
函数名：es_ecp_master_write
描  述：ECP主机写函数，向一个从机写入一串数据。
输  入：
    id      从机的ID。
    addr    要写入的首地址。
    buf     要写入的数据。
    len     要写入数据的长度。
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2022-05-30
修改记录：
-------------------------------------------------------*/
extern void es_ecp_master_write(u8 id,u16 addr,u8 * buf,u8 len);
/*-------------------------------------------------------
函数名：es_ecp_master_read
描  述：ECP主机读函数，向一个从机发送读数据请求，收到从机的数据时会调用回调函数。
输  入：
    id      从机的ID。
    addr    要读取的首地址。
    len     要读取数据的长度。
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2022-05-30
修改记录：
-------------------------------------------------------*/
extern void es_ecp_master_read(u8 id,u16 addr,u8 len);
/*-------------------------------------------------------
函数名：es_ecp_exe
描  述：ECP解析执行函数，放进stream框架里运行。
输  入：
    dat     和stream框架对接的参数。
输  出：无
返回值：无
创建者：奈特
参考例程：
    void ecbm_stream_exe(u8 dat){
        es_ecp_exe(dat);
    }
创建日期：2022-05-27
修改记录：
-------------------------------------------------------*/
extern void es_ecp_exe(u8 dat);
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。