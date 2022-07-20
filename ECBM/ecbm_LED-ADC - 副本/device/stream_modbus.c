#include "stream_modbus.h"//加载头文件
#if (ECBM_STREAM_EN)&&(ECBM_STREAM_MODBUS_EN)//检查本库有没有被使能
/*--------------------------------------变量定义-----------------------------------*/
u8  es_modbus_rtu_status      =0; //状态机使用的变量。
u8  es_modbus_rtu_broadcast_en=0; //广播模式。
u8  es_modbus_rtu_fun_code    =0; //功能码。
u8  es_modbus_rtu_fun_err_num =0; //异常码。
u16 es_modbus_rtu_address     =0; //数据地址。
u16 es_modbus_rtu_data_count  =0; //数据/个数。
u16 es_modbus_rtu_uart_crc    =0; //CRC计算缓存。
u16 es_modbus_rtu_crc_buf     =0; //CRC缓存。
u8  es_modbus_rtu_cmd_count   =0; //指令缓存计数。
#if ES_MODBUS_RTU_CMD10_EN
u16 es_modbus_rtu_cmd_buf[ES_MODBUS_RTU_BUF_SIZE];//指令缓存。
#endif
/*--------------------------------------程序定义-----------------------------------*/
void es_modbus_rtu_crc16(u8 buf,u16 * crc){
    u8 j;
    u16 crc_buf;
    crc_buf=*crc;
    crc_buf^=buf;                       //当前数据异或CRC低字节，在C51里可以直接处理。
    for(j=0;j<8;j++){                   //计算每个字节的每一位。
        if(crc_buf&0x01){               //判断右移前最低位是否为1。
            crc_buf=(crc_buf>>1)^0xA001;//如果为1则右移并异或表达式。
        }else{
            crc_buf>>=1;                //否则直接右移一位。
        }           
    }
    *crc=crc_buf;
}
void es_modbus_rtu_err_num(u8 fun_num,u8 err_num){
    u8  id;
    u16 crc=0xFFFF;
    if(es_modbus_rtu_broadcast_en){     //只有不是广播帧的时候才能回复。
        id=es_modbus_rtu_get_id();      //读取本机ID。
        es_modbus_rtu_crc16(id          ,&crc); //计算CRC，下同。
        es_modbus_rtu_crc16(0x80+fun_num,&crc);
        es_modbus_rtu_crc16(err_num     ,&crc);
        uart_char(ECBM_STREAM_UART,id);            //发送地址。
        uart_char(ECBM_STREAM_UART,0x80+fun_num);  //发送0x80+功能码回复。
        uart_char(ECBM_STREAM_UART,err_num);       //异常码。
        uart_char(ECBM_STREAM_UART,(u8)(crc));   //发送CRC。
        uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
    }
}
/*-------------------------------------------------------
1号功能码处理函数。
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD01_EN
void es_modbus_rtu_cmd_0x01(void){
    u8 temp8,t1,c1,i,j,qw,id;
    u16 crc=0xFFFF;
    id=es_modbus_rtu_get_id();      //读取本机ID。
    if((es_modbus_rtu_data_count>=1)&&(es_modbus_rtu_data_count<=0x07D0)){          //读取的个数要在1个以上，且地址不能大于2000。
        if(((u32)es_modbus_rtu_data_count+(u32)es_modbus_rtu_address)<=65536UL){//判断地址+个数有没有超限。
            if(es_modbus_rtu_broadcast_en){             //如果是广播帧，那么便不能回复。
                t1=(u8)(es_modbus_rtu_data_count/8);  //统计要读取的数据能凑够多少个字节。
                if(es_modbus_rtu_data_count%8)t1++;     //剩下的不足8位的数据也要一个字节来传输。
                es_modbus_rtu_crc16(id  ,&crc);  //计算CRC，下同。
                es_modbus_rtu_crc16(0x01,&crc);
                es_modbus_rtu_crc16(t1  ,&crc);
                uart_char(ECBM_STREAM_UART,id);    //发送地址。
                uart_char(ECBM_STREAM_UART,0x01);  //发送功能码回复。
                uart_char(ECBM_STREAM_UART,t1);    //发送数据长度。
                for(i=0;i<t1;i++){                          //从起始位置开始组装数据。
                    temp8=0;                                //清零变量。
                    if(es_modbus_rtu_data_count>=8){        //如果剩余要读的数据多于8个比特。
                        c1=8;                               //那么本轮循环先读8比特数据。
                    }else{                                  //否则，
                        c1=(u8)es_modbus_rtu_data_count;  //就有多少读多少。
                    }
                    for(j=0;j<c1;j++){      
                        es_modbus_cmd_read_bit(es_modbus_rtu_address++,&qw);//将地址送到读取函数中，获取对应的比特值。
                        if(qw)temp8|=(1<<j);                //组装数据。
                    }
                    es_modbus_rtu_crc16(temp8,&crc);        //计算CRC。
                    uart_char(ECBM_STREAM_UART,temp8);                 //发送组装好的数据。
                    es_modbus_rtu_data_count-=(u16)c1;    //计算剩下要读的数据个数。
                }
                uart_char(ECBM_STREAM_UART,(u8)(crc));               //发送CRC
                uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
            }
        }else{                                  //如果地址+个数超过65536。
            es_modbus_rtu_fun_err_num=0x02;     //记录异常码02。
            es_modbus_rtu_err_num(0x01,es_modbus_rtu_fun_err_num);//发送错误码。
        }
    }else{                                  //如果个数本身就超过2000了。
        es_modbus_rtu_fun_err_num=0x03;     //记录异常码03。
        es_modbus_rtu_err_num(0x01,es_modbus_rtu_fun_err_num);//发送错误码。
    }
}
#endif
/*-------------------------------------------------------
2号功能码处理函数。
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD02_EN
void es_modbus_rtu_cmd_0x02(void){
    u8 temp8,t1,c1,i,j,qw,id;
    u16 crc=0xFFFF;
    id=es_modbus_rtu_get_id();      //读取本机ID。
    if((es_modbus_rtu_data_count>=1)&&(es_modbus_rtu_data_count<=0x07D0)){              //读取的个数要在1个以上，且地址不能大于2000。
        if(((u32)es_modbus_rtu_data_count+(u32)es_modbus_rtu_address)<=65536UL){    //判断地址+个数有没有超限。
                if(es_modbus_rtu_broadcast_en){             //如果是广播帧，那么便不能回复。
                    t1=(u8)(es_modbus_rtu_data_count/8);  //统计要读取的数据能凑够多少个字节。
                    if(es_modbus_rtu_data_count%8)t1++;     //剩下的不足8位的数据也要一个字节来传输。
                    es_modbus_rtu_crc16(id  ,&crc);         //计算CRC，下同。
                    es_modbus_rtu_crc16(0x02,&crc);
                    es_modbus_rtu_crc16(t1  ,&crc);
                    uart_char(ECBM_STREAM_UART,id);                    //发送地址。
                    uart_char(ECBM_STREAM_UART,0x02);                  //发送功能码回复。
                    uart_char(ECBM_STREAM_UART,t1);                    //发送数据长度。
                    for(i=0;i<t1;i++){                      //从起始位置开始组装数据。
                        temp8=0;                            //清零变量。
                        if(es_modbus_rtu_data_count>=8){    //如果剩余要读的数据多于8个比特。
                            c1=8;                           //那么本轮循环先读8比特数据。
                        }else{                              //否则，
                            c1=(u8)es_modbus_rtu_data_count;  //就有多少读多少。
                        }
                        for(j=0;j<c1;j++){      
                            es_modbus_cmd_read_io_bit(es_modbus_rtu_address++,&qw);//将地址送到读取函数中，获取对应的比特值。
                            if(qw)temp8|=(1<<j);                     //组装数据。
                        }
                        es_modbus_rtu_crc16(temp8,&crc);        //计算CRC。
                        uart_char(ECBM_STREAM_UART,temp8);                 //发送组装好的数据。
                        es_modbus_rtu_data_count-=(u16)c1;    //计算剩下要读的数据个数。
                    }
                    uart_char(ECBM_STREAM_UART,(u8)(crc));               //发送CRC。
                    uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
                }
        }else{                                  //如果地址+个数超过2000。
            es_modbus_rtu_fun_err_num=0x02;     //记录异常码02。
            es_modbus_rtu_err_num(0x02,es_modbus_rtu_fun_err_num);//发送错误码。
        }
    }else{                                  //如果个数本身就超过65536了。
        es_modbus_rtu_fun_err_num=0x03;     //记录异常码03。
        es_modbus_rtu_err_num(0x02,es_modbus_rtu_fun_err_num);//发送错误码。
    }
}
#endif
/*-------------------------------------------------------
3号功能码处理函数。
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD03_EN
void es_modbus_rtu_cmd_0x03(void){
    u8 id;
    u16 temp16,i,crc=0xffff;
    id=es_modbus_rtu_get_id();      //读取本机ID。
    if((es_modbus_rtu_data_count>=1)&&(es_modbus_rtu_data_count<=0x007D)){          //读取的个数要在1个以上，且地址不能大于125。
        if(((u32)es_modbus_rtu_data_count+(u32)es_modbus_rtu_address)<65536UL){ //判断地址+个数有没有超限。
            if(es_modbus_rtu_broadcast_en){
                es_modbus_rtu_crc16(id  ,&crc);  //计算CRC，下同。
                es_modbus_rtu_crc16(0x03,&crc);
                es_modbus_rtu_crc16(es_modbus_rtu_data_count*2,&crc);
                uart_char(ECBM_STREAM_UART,id);            //发送地址。
                uart_char(ECBM_STREAM_UART,0x03);          //发送功能码回复。
                uart_char(ECBM_STREAM_UART,es_modbus_rtu_data_count*2);//发送回复字节数。
                for(i=0;i<es_modbus_rtu_data_count;i++){
                    es_modbus_cmd_read_reg(es_modbus_rtu_address+i,&temp16);//从寄存器变量里把数据取出来。
                    es_modbus_rtu_crc16((u8)(temp16>>8),&crc);            //计算CRC，下同。
                    es_modbus_rtu_crc16((u8)(temp16),&crc);
                    uart_char(ECBM_STREAM_UART,(u8)(temp16>>8)); //发送数据。
                    uart_char(ECBM_STREAM_UART,(u8)(temp16));
                }
                uart_char(ECBM_STREAM_UART,(u8)(crc));//发送CRC。
                uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
            }
        }else{
            es_modbus_rtu_fun_err_num=0x02; //记录异常码02。
            es_modbus_rtu_err_num(0x03,es_modbus_rtu_fun_err_num);//发送错误码。
        }
    }else{                              //如果个数本身就超过125了。
        es_modbus_rtu_fun_err_num=0x03; //记录异常码03。    
        es_modbus_rtu_err_num(0x03,es_modbus_rtu_fun_err_num);//发送错误码。
    }
}
#endif
/*-------------------------------------------------------
4号功能码处理函数。
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD04_EN
void es_modbus_rtu_cmd_0x04(void){
    u8 id;
    u16 temp16,i,crc=0xffff;
    id=es_modbus_rtu_get_id();      //读取本机ID。
    if((es_modbus_rtu_data_count>=1)&&(es_modbus_rtu_data_count<=0x007D)){          //读取的个数要在1个以上，且地址不能大于125。
        if(((u32)es_modbus_rtu_data_count+(u32)es_modbus_rtu_address)<65536UL){ //判断地址+个数有没有超限。
            if(es_modbus_rtu_broadcast_en){
                es_modbus_rtu_crc16(id  ,&crc);     //计算CRC，下同。
                es_modbus_rtu_crc16(0x04,&crc);
                es_modbus_rtu_crc16(es_modbus_rtu_data_count*2,&crc);
                uart_char(ECBM_STREAM_UART,id);                //发送地址。
                uart_char(ECBM_STREAM_UART,0x04);              //发送功能码回复。
                uart_char(ECBM_STREAM_UART,es_modbus_rtu_data_count*2);//发送回复字节数。
                for(i=0;i<es_modbus_rtu_data_count;i++){
                    es_modbus_cmd_read_io_reg(es_modbus_rtu_address+i,&temp16);//从寄存器变量里把数据取出来。
                    es_modbus_rtu_crc16((u8)(temp16>>8),&crc); //计算CRC，下同。
                    es_modbus_rtu_crc16((u8)(temp16),&crc);
                    uart_char(ECBM_STREAM_UART,(u8)(temp16>>8));//发送数据。
                    uart_char(ECBM_STREAM_UART,(u8)(temp16));
                }
                uart_char(ECBM_STREAM_UART,(u8)(crc));//发送CRC。
                uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
            }
        }else{
            es_modbus_rtu_fun_err_num=0x02; //记录异常码02。
            es_modbus_rtu_err_num(0x04,es_modbus_rtu_fun_err_num);//发送错误码。
        }
    }else{                              //如果个数本身就超过125了。
        es_modbus_rtu_fun_err_num=0x03; //记录异常码03。    
        es_modbus_rtu_err_num(0x04,es_modbus_rtu_fun_err_num);//发送错误码。
    }
}
#endif
/*-------------------------------------------------------
5号功能码处理函数。
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD05_EN
void es_modbus_rtu_cmd_0x05(void){
    u8 id;
    u16 crc=0xffff;
    id=es_modbus_rtu_get_id();      //读取本机ID。
    if((es_modbus_rtu_data_count==0x0000)||(es_modbus_rtu_data_count==0xFF00)){//判断输出值是否合法。
        es_modbus_cmd_write_bit(es_modbus_rtu_address,(u8)(es_modbus_rtu_data_count>>8));
        if(es_modbus_rtu_broadcast_en){
            es_modbus_rtu_crc16(id  ,&crc);                  //计算CRC，下同。
            es_modbus_rtu_crc16(0x05,&crc);
            es_modbus_rtu_crc16((u8)(es_modbus_rtu_address>>8)   ,&crc);
            es_modbus_rtu_crc16((u8)(es_modbus_rtu_address)      ,&crc);
            es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count>>8),&crc);
            es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count)   ,&crc);
            uart_char(ECBM_STREAM_UART,id);               //发送地址。
            uart_char(ECBM_STREAM_UART,0x05);                             //发送功能码回复。
            uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address>>8)); //发送地址回复。
            uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address));
            uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count>>8));//发送计数回复。
            uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count));
            uart_char(ECBM_STREAM_UART,(u8)(crc));        //发送CRC。
            uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
        }    
    }else{                              //如果不合法。
        es_modbus_rtu_fun_err_num=0x03; //记录异常码03。    
        es_modbus_rtu_err_num(0x05,es_modbus_rtu_fun_err_num);//发送错误码。
    }
}
#endif
/*-------------------------------------------------------
6号功能码处理函数。
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD06_EN
void es_modbus_rtu_cmd_0x06(void){
    u8 id;
    u16 crc=0xffff;
    id=es_modbus_rtu_get_id();      //读取本机ID。
    es_modbus_cmd_write_reg(es_modbus_rtu_address,es_modbus_rtu_data_count);//把数据写入寄存器。
    if(es_modbus_rtu_broadcast_en){
        es_modbus_rtu_crc16(id  ,&crc);          //计算CRC，下同。
        es_modbus_rtu_crc16(0x06,&crc);
        es_modbus_rtu_crc16((u8)(es_modbus_rtu_address>>8),&crc);
        es_modbus_rtu_crc16((u8)(es_modbus_rtu_address),&crc);
        es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count>>8),&crc);
        es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count),&crc);
        uart_char(ECBM_STREAM_UART,id);        //发送地址。
        uart_char(ECBM_STREAM_UART,0x06);      //发送功能码回复。
        uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address>>8));//发送地址。
        uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address));
        uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count>>8));//发送个数。
        uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count));
        uart_char(ECBM_STREAM_UART,(u8)(crc));//发送CRC。
        uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
    }    
}
#endif
/*-------------------------------------------------------
16号功能码处理函数。
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD10_EN
void es_modbus_rtu_cmd_0x10(void){
    u8 i,id;
    u16 crc=0xffff;
    id=es_modbus_rtu_get_id();      //读取本机ID。
    if((es_modbus_rtu_data_count>=0x0001)&&(es_modbus_rtu_data_count<=0x007B)){             //输入的数据个数得符合要求。
        if(((u32)es_modbus_rtu_address+(u32)es_modbus_rtu_data_count)<65536UL){             //地址不能超过65536。
            for(i=0;i<es_modbus_rtu_cmd_count;i++){   
                es_modbus_cmd_write_reg(es_modbus_rtu_address+i,es_modbus_rtu_cmd_buf[i]);  //把数据写入寄存器。
            }
            if(es_modbus_rtu_broadcast_en){
                    es_modbus_rtu_crc16(id,&crc);          //计算CRC，下同。
                    es_modbus_rtu_crc16(0x10,&crc);
                    es_modbus_rtu_crc16((u8)(es_modbus_rtu_address>>8)   ,&crc);
                    es_modbus_rtu_crc16((u8)(es_modbus_rtu_address)      ,&crc);
                    es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count>>8),&crc);
                    es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count)   ,&crc);
                    uart_char(ECBM_STREAM_UART,id);                    //发送地址。
                    uart_char(ECBM_STREAM_UART,0x10);                  //发送功能码回复。
                    uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address>>8));//发送地址。
                    uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address));
                    uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count>>8));//发送个数。
                    uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count));
                    uart_char(ECBM_STREAM_UART,(u8)(crc));           //发送CRC。
                    uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
            }   
        }else{
            es_modbus_rtu_fun_err_num=0x02;               //记录异常码02。
            es_modbus_rtu_err_num(0x10,es_modbus_rtu_fun_err_num);//发送错误码。
        }
    }else{                                                  //如果不合法。
        es_modbus_rtu_fun_err_num=0x03;                   //记录异常码03。    
        es_modbus_rtu_err_num(0x10,es_modbus_rtu_fun_err_num);//发送错误码。
    }
}
#endif
/*-------------------------------------------------------
modbus_rtu解析执行函数。
-------------------------------------------------------*/
void es_modbus_rtu_exe(u8 dat){
    switch(es_modbus_rtu_status){
        case ES_MODBUS_RTU_READY:{          //就绪，等待接收数据。
            if((dat==es_modbus_rtu_get_id())||(dat==0)){      //如果收到的ID和本机的匹配。
                es_modbus_rtu_status      =ES_MODBUS_RTU_FUN_NUM;//切换到功能码识别
                es_modbus_rtu_broadcast_en=dat;     //写入通信模式，为了简化代码，采用直接赋值。
                es_modbus_rtu_fun_code    =0;       //清零功能码缓存。
                es_modbus_rtu_fun_err_num =0;       //清零异常码缓存。
                es_modbus_rtu_uart_crc    =0xffff;  //重置CRC初值。
                es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//计算CRC。
            }
        }break;
        case ES_MODBUS_RTU_FUN_NUM:{        //正在接收功能码。
            es_modbus_rtu_fun_code=dat;
            if(es_modbus_rtu_fun_code>127){     //判断功能码是否合法，
                es_modbus_rtu_fun_err_num=0x01; //异常码01。 
                es_modbus_rtu_err_num(es_modbus_rtu_fun_code,es_modbus_rtu_fun_err_num);//发送错误码。
                es_modbus_rtu_status=ES_MODBUS_RTU_READY;
            }else{                              //如果合法，
                switch(es_modbus_rtu_fun_code){ //判断是不是本机支持的功能码。
                    #if ES_MODBUS_RTU_CMD01_EN
                        case 0x01://读线圈
                    #endif
                    #if ES_MODBUS_RTU_CMD02_EN
                        case 0x02://读离散量输入
                    #endif
                    #if ES_MODBUS_RTU_CMD05_EN
                        case 0x05://写单个线圈
                    #endif
                    #if ES_MODBUS_RTU_CMD04_EN
                        case 0x04://读输入寄存器
                    #endif
                    #if ES_MODBUS_RTU_CMD03_EN
                        case 0x03://读多个寄存器
                    #endif
                    #if ES_MODBUS_RTU_CMD06_EN
                        case 0x06://写单个寄存器
                    #endif
                    #if ES_MODBUS_RTU_CMD10_EN
                        case 0x10://写多个寄存器
                    #endif
                    #if ES_MODBUS_RTU_CMD_ALL_EN
                        {
                            es_modbus_rtu_status=ES_MODBUS_RTU_ADDRH;           //如果是存在的功能码，就考虑开始接收数据了。
                            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);
                        }break;//支持的功能码就返回本身。
                    #endif
                    default:{
                        es_modbus_rtu_fun_err_num=0x01;                       //异常码01。
                        es_modbus_rtu_err_num(es_modbus_rtu_fun_code,es_modbus_rtu_fun_err_num);//发送错误码。
                        es_modbus_rtu_status=ES_MODBUS_RTU_READY;
                    }break;//不支持的功能码就返回0x80+功能码。
                }
            }
        }break;
        case ES_MODBUS_RTU_ADDRH:{                        //接收地址的高8位。
            es_modbus_rtu_address=(u16)dat<<8;            //组装地址。
            es_modbus_rtu_status=ES_MODBUS_RTU_ADDRL;   //到下一步。
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);
        }break;
        case ES_MODBUS_RTU_ADDRL:{                        //接收地址的低8位。
            es_modbus_rtu_address+=(u16)dat;              //组装地址。
            es_modbus_rtu_status=ES_MODBUS_RTU_DATA_COUNTH;//到下一步。
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//计算CRC。
        }break;
        case ES_MODBUS_RTU_DATA_COUNTH:{                  //接收数据/个数的高8位。
            es_modbus_rtu_data_count=(u16)dat<<8;         //组装数据/个数。
            es_modbus_rtu_status=ES_MODBUS_RTU_DATA_COUNTL;//到下一步。
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//计算CRC。
        }break;
        case ES_MODBUS_RTU_DATA_COUNTL:{                  //接收数据/个数的低8位。
            es_modbus_rtu_data_count+=(u16)dat;           //组装数据/个数。
            if(es_modbus_rtu_fun_code==0x10){
                es_modbus_rtu_cmd_count=0;
                es_modbus_rtu_status=ES_MODBUS_RTU_BYTE_COUNT;//到字节读取。
            }else{
                es_modbus_rtu_status=ES_MODBUS_RTU_CRCL;//到CRC。
            }
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//计算CRC。
        }break;
        case ES_MODBUS_RTU_CRCL:{                         //接收CRC的低8位。
            es_modbus_rtu_crc_buf=(u16)dat;               //组合CRC。
            es_modbus_rtu_status=ES_MODBUS_RTU_CRCH;    //到下一步。
        }break;
        case ES_MODBUS_RTU_CRCH:{                         //接收CRC的高8位。
            es_modbus_rtu_crc_buf+=(u16)dat<<8;           //组合CRC。
            if(es_modbus_rtu_crc_buf==es_modbus_rtu_uart_crc){//判断接收的CRC和计算的CRC是否相等。
                #if ES_MODBUS_RTU_CMD_ALL_EN
                    switch(es_modbus_rtu_fun_code){//根据功能码来选择对应的动作。
                    #if ES_MODBUS_RTU_CMD01_EN
                        case 0x01:es_modbus_rtu_cmd_0x01();break;
                    #endif
                    #if ES_MODBUS_RTU_CMD02_EN
                        case 0x02:es_modbus_rtu_cmd_0x02();break;
                    #endif
                    #if ES_MODBUS_RTU_CMD03_EN
                        case 0x03:es_modbus_rtu_cmd_0x03();break;
                    #endif
                    #if ES_MODBUS_RTU_CMD04_EN
                        case 0x04:es_modbus_rtu_cmd_0x04();break;
                    #endif
                    #if ES_MODBUS_RTU_CMD05_EN
                        case 0x05:es_modbus_rtu_cmd_0x05();break;
                    #endif
                    #if ES_MODBUS_RTU_CMD06_EN
                        case 0x06:es_modbus_rtu_cmd_0x06();break;
                    #endif
                    #if ES_MODBUS_RTU_CMD10_EN
                        case 0x10:es_modbus_rtu_cmd_0x10();break;
                    #endif
                    }
                #endif
                es_modbus_rtu_status=ES_MODBUS_RTU_READY; 
            }else{                                          //否则，
                #if ES_MODBUS_RTU_CRC_ERR_EN
                es_modbus_rtu_crc_err_callback();//就跳到CRC错误界面。
                #endif
                es_modbus_rtu_status=ES_MODBUS_RTU_READY;
            }
        }break;
        #if ES_MODBUS_RTU_CMD10_EN
        case ES_MODBUS_RTU_BYTE_COUNT:{                   //接收数据字节数。
            es_modbus_rtu_cmd_count=dat;
            if((es_modbus_rtu_cmd_count==0)||(es_modbus_rtu_cmd_count!=(u8)(es_modbus_rtu_data_count*2))){//如果数量不合。
                es_modbus_rtu_fun_err_num=0x03;           //字节数对不上，异常码03。
                es_modbus_rtu_err_num(es_modbus_rtu_fun_code,es_modbus_rtu_fun_err_num);//发送错误码。
                es_modbus_rtu_status=ES_MODBUS_RTU_READY;
            }else{
                es_modbus_rtu_cmd_count=0;                    //复用该变量。
                es_modbus_rtu_status=ES_MODBUS_RTU_DATAH;//调到对应的处理界面。
                es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//计算CRC。
            }
        }break;
        case ES_MODBUS_RTU_DATAH:{
            es_modbus_rtu_cmd_buf[es_modbus_rtu_cmd_count]=((u16)dat)<<8;
            es_modbus_rtu_status=ES_MODBUS_RTU_DATAL;   //到低8位。
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//计算CRC。
        }break;
        case ES_MODBUS_RTU_DATAL:{
            es_modbus_rtu_cmd_buf[es_modbus_rtu_cmd_count]+=((u16)dat);
            es_modbus_rtu_cmd_count++;
            if(es_modbus_rtu_cmd_count==(u8)es_modbus_rtu_data_count){
                es_modbus_rtu_status=ES_MODBUS_RTU_CRCL;//到CRC。
            }else{
                es_modbus_rtu_status=ES_MODBUS_RTU_DATAH;//到下一个数据的高8位。
            }
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//计算CRC。
        }break;
        #endif
    }
}
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。