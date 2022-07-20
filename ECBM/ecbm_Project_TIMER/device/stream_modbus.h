#ifndef _ECBM_STREAM_MODBUS_H_//头文件防止重加载必备，先看看有没有定义过这个，定义说明已经加载过一次了。
#define _ECBM_STREAM_MODBUS_H_//没定义说明是首次加载，那么往下执行。并且定义这个宏定义，防止下一次被加载。
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
//modbus-rtu的版本。此版本隶属于stream库。
#define ES_MODBUS_RTU_VERSION "V1.2"
//<q>[01]读线圈
//<i>如果和线圈有关的指令都没有被使能，那么线圈读写相关的函数和缓存都将被优化掉。
#define ES_MODBUS_RTU_CMD01_EN 1
//<q>[05]写单个线圈
//<i>如果和线圈有关的指令都没有被使能，那么线圈读写相关的函数和缓存都将被优化掉。
#define ES_MODBUS_RTU_CMD05_EN 1
//<q>[03]读寄存器
//<i>如果和寄存器有关的指令都没有被使能，那么线圈读写相关的函数和缓存都将被优化掉。
#define ES_MODBUS_RTU_CMD03_EN 1
//<q>[06]写单个寄存器
//<i>如果和寄存器有关的指令都没有被使能，那么线圈读写相关的函数和缓存都将被优化掉。
#define ES_MODBUS_RTU_CMD06_EN 1
//<e>[10]写多个寄存器
//<i>如果和寄存器有关的指令都没有被使能，那么线圈读写相关的函数和缓存都将被优化掉。
#define ES_MODBUS_RTU_CMD10_EN 1
//<o>寄存器写入缓存总数
//<i>单位是字节（8位），由于CRC的存在，在多字节写入的时候，不能立刻把数据存入，需要用一个缓存存起来，待CRC验证完毕之后才能一起写入。
#define ES_MODBUS_RTU_BUF_SIZE  10
//</e>
//<q>[02]读离散量输入
//<i>如果和IO系统有关的指令都没有被使能，那么IO相关的函数和缓存都将被优化掉。
#define ES_MODBUS_RTU_CMD02_EN 1
//<q>[04]读输入寄存器
//<i>如果和IO系统有关的指令都没有被使能，那么IO相关的函数和缓存都将被优化掉。
#define ES_MODBUS_RTU_CMD04_EN 1
//<q>CRC错误回调函数
//<i>如果通信中出现了CRC错误，那么就会调用这个回调函数。如果不对其进行处理，可以不使能这个选项。
#define ES_MODBUS_RTU_CRC_ERR_EN 0
//以下是合并各个分散的宏定义的总结定义：
#define ES_MODBUS_RTU_CMD_BIT_EN  (ES_MODBUS_RTU_CMD01_EN+ES_MODBUS_RTU_CMD05_EN)
#define ES_MODBUS_RTU_CMD_REG_EN  (ES_MODBUS_RTU_CMD03_EN+ES_MODBUS_RTU_CMD06_EN+ES_MODBUS_RTU_CMD10_EN)
#define ES_MODBUS_RTU_CMD_IO_EN   (ES_MODBUS_RTU_CMD02_EN+ES_MODBUS_RTU_CMD04_EN)
#define ES_MODBUS_RTU_CMD_ALL_EN  (ES_MODBUS_RTU_CMD_BIT_EN+ES_MODBUS_RTU_CMD_REG_EN+ES_MODBUS_RTU_CMD_IO_EN)
//<<< end of configuration section >>>
//-----------------以上是图形设置界面，可在Configuration Wizard界面设置-----------------
/*---------------------------------------头文件------------------------------------*/
#include "ecbm_core.h"    //ECBM库的头文件，里面已经包含了STC8的头文件。
/*------------------------------------状态机宏定义---------------------------------*/
#define ES_MODBUS_RTU_READY           0   //就绪态，此时可以接受一帧modbus数据。
#define ES_MODBUS_RTU_WAIT            1   //等待态，当发生错误之后，在此等待当前数据帧结束。
#define ES_MODBUS_RTU_FUN_NUM         2   //读取功能码，在此读取功能码。
#define ES_MODBUS_RTU_ADDRH           3   //读取地址高8位。
#define ES_MODBUS_RTU_ADDRL           4   //读取地址低8位。
#define ES_MODBUS_RTU_DATA_COUNTH     5   //读取数据或者个数的高8位。
#define ES_MODBUS_RTU_DATA_COUNTL     6   //读取数据或者个数的低8位。
#define ES_MODBUS_RTU_COUNT_ERR       7   //读取个数错误。
#define ES_MODBUS_RTU_CRCH            8   //读取CRC的高8位。
#define ES_MODBUS_RTU_CRCL            9   //读取CRC的低8位。
#define ES_MODBUS_RTU_DO              10  //处理态，在该状态下处理数据。
#define ES_MODBUS_RTU_DATAH           11  //读取地址高8位。
#define ES_MODBUS_RTU_DATAL           12  //读取地址低8位。
#define ES_MODBUS_RTU_BYTE_COUNT      13  //读取字节数量。
/*--------------------------------------变量定义-----------------------------------*/
extern u8  es_modbus_rtu_status      ; //状态机使用的变量。
extern u8  es_modbus_rtu_broadcast_en; //广播模式。
extern u8  es_modbus_rtu_fun_code    ; //功能码。
extern u8  es_modbus_rtu_fun_err_num ; //异常码。
extern u16 es_modbus_rtu_address     ; //数据地址。
extern u16 es_modbus_rtu_data_count  ; //数据/个数。
extern u16 es_modbus_rtu_uart_crc    ; //CRC计算缓存。
extern u16 es_modbus_rtu_crc_buf     ; //CRC缓存。
extern u8  es_modbus_rtu_cmd_count   ; //指令缓存计数。
extern u16 es_modbus_rtu_cmd_buf[ES_MODBUS_RTU_BUF_SIZE];//指令缓存。
/*--------------------------------------程序定义-----------------------------------*/
/*------------------需要用户定义的函数------------------*/
/*-------------------------------------------------------
函数名：es_modbus_cmd_read_io_bit
描  述：读取离散输入寄存器函数，功能码02H会用到。
输  入：
    addr    主机传来的地址信息。
输  出：
    dat     该地址对应的离散输入寄存器的数据，只有0和1两种可能。
返回值：无
创建者：奈特
参考例程：
    void es_modbus_cmd_read_io_bit(u16 addr,u8 * dat){
        if(addr==0x0000){//当主机要读地址0的时候，
            if(P00){//例程中，这个地址对应着P0.0的状态。
                *dat=1;//是高电平就返回1。
            }else{
                *dat=0;//是低电平就返回0。
            }
        }
    }
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_cmd_read_io_bit(u16 addr,u8 * dat);
/*-------------------------------------------------------
函数名：es_modbus_cmd_read_io_reg
描  述：读取离散输入寄存器函数，功能码04H会用到。
输  入：
    addr    主机传来的地址信息。
输  出：
    dat     该地址对应的输入寄存器的数据。
返回值：无
创建者：奈特
参考例程：
    void es_modbus_cmd_read_io_reg(u16 addr,u16 * dat){
        if(addr==0x0000){//当主机要读地址0的时候，
            *dat=(u16)P0;//例程中，这个地址对应着P0的状态。
        }
    }
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_cmd_read_io_reg(u16 addr,u16 * dat);
/*-------------------------------------------------------
函数名：es_modbus_cmd_write_bit
描  述：写单个线圈寄存器函数，功能码05H会用到。
输  入：
    addr    主机传来的地址信息。
    dat     要写入该地址的数据。
输  出：无
返回值：无
创建者：奈特
参考例程：
    void es_modbus_cmd_write_bit(u16 addr,u8 dat){
        if(addr==0x0000){//当主机要写地址0的线圈时候，
            if(dat){//例程中，这个地址对应着变量test的D0位。
                test|=0x0001;//如果写入的是1，就令D0位变成1。
            }else{
                test&=0xFFFE;//如果写入的是0，就令D0位变成0。
            }
        }
    }
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_cmd_write_bit(u16 addr,u8 dat);
/*-------------------------------------------------------
函数名：es_modbus_cmd_read_bit
描  述：读单个线圈寄存器函数，功能码01H会用到。
输  入：
    addr    主机传来的地址信息。
输  出：
    dat     该地址对应的线圈寄存器的数据。
返回值：无
创建者：奈特
参考例程：
    void es_modbus_cmd_read_bit(u16 addr,u8 * dat){
        if(addr==0x0000){//当主机要读地址0的时候，
            if(test&0x0001){//例程中，这个地址对应着test变量的D0位。
                *dat=1;//D0位为1就返回1。
            }else{
                *dat=0;//D0位为0就返回0。
            }
        }
    }
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_cmd_read_bit(u16 addr,u8 * dat);
/*-------------------------------------------------------
函数名：es_modbus_cmd_write_reg
描  述：写单个保持寄存器函数，功能码06H和10H会用到。
输  入：
    addr    主机传来的地址信息。
    dat     要写入该地址的数据。
输  出：无
返回值：无
创建者：奈特
参考例程：
    void es_modbus_cmd_write_reg(u16 addr,u16 dat){
        reg[addr]=dat;//例程中的数组reg代表了所有保持寄存器。
    }
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_cmd_write_reg(u16 addr,u16 dat);
/*-------------------------------------------------------
函数名：es_modbus_cmd_read_reg
描  述：读单个保持寄存器函数，功能码03H会用到。
输  入：
    addr    主机传来的地址信息。
输  出：
    dat     该地址对应的保持寄存器的数据。
返回值：无
创建者：奈特
参考例程：
    void es_modbus_cmd_read_reg(u16 addr,u16 * dat){
        *dat=reg[addr];//例程中的数组reg代表了所有保持寄存器。
    }
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_cmd_read_reg(u16 addr,u16 * dat);
/*-------------------------------------------------------
函数名：es_modbus_rtu_crc_err_callback
描  述：CRC出错回调函数，当modbus通讯的CRC校验出错时调用。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：
    void es_modbus_rtu_crc_err_callback(void){
        //可以通知主机重发，也可以什么都不做。
    }
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_crc_err_callback(void);
/*-------------------------------------------------------
函数名：es_modbus_rtu_get_id
描  述：获取本机ID函数，modbus通讯中会调用，要返回本机的ID号。
输  入：无
输  出：无
返回值：
    本机的ID值。
创建者：奈特
参考例程：
    u8 es_modbus_rtu_get_id(void){
        return 1;//可以为一个常数，也可以是一个变量。但是范围必须在1~247之间。
    }
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern u8 es_modbus_rtu_get_id(void);
/*----------------------系统函数-----------------------*/
/*-------------------------------------------------------
函数名：es_modbus_rtu_crc16
描  述：CRC校验函数。
输  入：
    buf     当前需要进行CRC校验的数据。
    crc     当前的CRC值。
输  出：
    crc     经过计算后得到的新CRC值。
返回值：无
创建者：奈特
参考例程：无
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_crc16(u8 buf,u16 * crc);
/*-------------------------------------------------------
函数名：es_modbus_rtu_err_num
描  述：modbus返回错误码函数。
输  入：
    fun_num     当前的功能码。
    err_num     需要报错的错误码。
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_err_num(u8 fun_num,u8 err_num);
/*-------------------------------------------------------
函数名：es_modbus_rtu_cmd_0x01
描  述：01号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x01(void);
/*-------------------------------------------------------
函数名：es_modbus_rtu_cmd_0x02
描  述：02号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x02(void);
/*-------------------------------------------------------
函数名：es_modbus_rtu_cmd_0x03
描  述：03号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x03(void);
/*-------------------------------------------------------
函数名：es_modbus_rtu_cmd_0x04
描  述：04号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x04(void);
/*-------------------------------------------------------
函数名：es_modbus_rtu_cmd_0x05
描  述：05号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x05(void);
/*-------------------------------------------------------
函数名：es_modbus_rtu_cmd_0x06
描  述：06号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x06(void);
/*-------------------------------------------------------
函数名：es_modbus_rtu_cmd_0x10
描  述：16号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
参考例程：无
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_cmd_0x10(void);
/*-------------------------------------------------------
函数名：es_modbus_rtu_exe
描  述：modbus_rtu解析执行函数，放进stream框架里运行。
输  入：
    dat     和stream框架对接的参数。
输  出：无
返回值：无
创建者：奈特
参考例程：
    void ecbm_stream_exe(u8 dat){
        es_modbus_rtu_exe(dat);
    }
创建日期：2021-10-28
修改记录：
-------------------------------------------------------*/
extern void es_modbus_rtu_exe(u8 dat);
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。