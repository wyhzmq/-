#include "stream_ecp.h"//加载头文件
#if (ECBM_STREAM_EN)&&(ECBM_STREAM_ECP_EN)//检查本库有没有被使能
/*--------------------------------------变量定义-----------------------------------*/
u8  es_ecp_status   =0; //状态机变量。
u8  es_ecp_data_len =0; //用于存放参数、数据的长度。
u8  es_ecp_count    =0; //用于统计实际接收的参数、数据长度。
u8  es_ecp_source_id=0; //源头ID，代表该帧由这个ID的器件发出。
u8  es_ecp_target_id=0; //目标ID，代表该帧应该由这个ID的器件接收。
u8  es_ecp_operation=0; //操作码缓存。
u16 es_ecp_addr16_ex=0; //16位扩展地址缓存。
u16 es_ecp_addr16   =0; //16位地址缓存。
u16 es_ecp_crc      =0; //用于计算接收数据的CRC。
u16 es_ecp_crc_buf  =0; //用于存放数据帧里的CRC。
u8  es_ecp_data_buf[ES_ECP_DATA_BUF_MAX];//用于读写操作的缓存。
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
CRC校验函数。
-------------------------------------------------------*/
u16 es_ecp_crc16(u16 crc,u8 buf){
    u8 j;
    u16 crc_buf;
    crc_buf=crc^buf;                    //当前数据异或CRC低字节，在C51里可以直接处理。
    for(j=0;j<8;j++){                   //计算每个字节的每一位。
        if(crc_buf&0x01){               //判断右移前最低位是否为1。
            crc_buf=(crc_buf>>1)^0xA001;//如果为1则右移并异或表达式。
        }else{
            crc_buf>>=1;                //否则直接右移一位。
        }           
    }
    return crc_buf;
}
/*-------------------------------------------------------
通用回复函数。
-------------------------------------------------------*/
void es_ecp_cmd_back(u8 cmd){
    u16 crc;
    if(es_ecp_source_id){//如果对方是广播，就不要回复了。
        crc=es_ecp_crc16(0xffff,0xEC);
        crc=es_ecp_crc16(crc,0x00);
        crc=es_ecp_crc16(crc,0xFF);
        crc=es_ecp_crc16(crc,es_ecp_source_id);
        crc=es_ecp_crc16(crc,es_ecp_get_id()); 
        crc=es_ecp_crc16(crc,cmd);
        crc=es_ecp_crc16(crc,(u8)(es_ecp_addr16_ex>>8));
        crc=es_ecp_crc16(crc,(u8)(es_ecp_addr16_ex   ));
        crc=es_ecp_crc16(crc,(u8)(es_ecp_addr16>>8));
        crc=es_ecp_crc16(crc,(u8)(es_ecp_addr16   ));
    
        ecbm_stream_out(0xEC);//帧头。
        ecbm_stream_out(0x00);//长度。
        ecbm_stream_out(0xFF);//长度反码。
        ecbm_stream_out(es_ecp_source_id);//谁发过来的，返还给谁。
        ecbm_stream_out(es_ecp_get_id()); //带上本机的ID。
        ecbm_stream_out(cmd);  //回执。
        ecbm_stream_out((u8)(es_ecp_addr16_ex>>8));//地址高位。
        ecbm_stream_out((u8)(es_ecp_addr16_ex   ));//地址低位。
        ecbm_stream_out((u8)(es_ecp_addr16>>8));//地址高位。
        ecbm_stream_out((u8)(es_ecp_addr16   ));//地址低位。
        ecbm_stream_out((u8)(crc>>8)); 
        ecbm_stream_out((u8)(crc));
        ecbm_stream_out(0xBE);  //帧尾。
    }
}
/*-------------------------------------------------------
02指令处理函数。
-------------------------------------------------------*/
void es_ecp_cmd02(void){
    u8 count,arg_len;
    u16 crc;
    arg_len=es_ecp_data_buf[0];
    es_ecp_read(es_ecp_addr16,es_ecp_data_buf,arg_len);
    if(es_ecp_source_id){//如果对方是广播，就不要回复了。
        crc=es_ecp_crc16(0xffff,0xEC);
        crc=es_ecp_crc16(crc, arg_len);
        crc=es_ecp_crc16(crc,~arg_len);
        crc=es_ecp_crc16(crc,es_ecp_source_id);
        crc=es_ecp_crc16(crc,es_ecp_get_id()); 
        crc=es_ecp_crc16(crc,0x03);
        crc=es_ecp_crc16(crc,(u8)(es_ecp_addr16_ex>>8));
        crc=es_ecp_crc16(crc,(u8)(es_ecp_addr16_ex   ));
        crc=es_ecp_crc16(crc,(u8)(es_ecp_addr16>>8));
        crc=es_ecp_crc16(crc,(u8)(es_ecp_addr16   ));
        for(count=0;count<arg_len;count++){
            crc=es_ecp_crc16(crc,es_ecp_data_buf[count]);
        }

        ecbm_stream_out(0xEC);  //帧头。
        ecbm_stream_out( arg_len); //长度。
        ecbm_stream_out(~arg_len);//长度反码。
        ecbm_stream_out(es_ecp_source_id);//谁发过来的，返还给谁。
        ecbm_stream_out(es_ecp_get_id()); //带上本机的ID。
        ecbm_stream_out(0x03);  //回执。
        ecbm_stream_out((u8)(es_ecp_addr16_ex>>8));//地址高位。
        ecbm_stream_out((u8)(es_ecp_addr16_ex   ));//地址低位。
        ecbm_stream_out((u8)(es_ecp_addr16>>8));//地址高位。
        ecbm_stream_out((u8)(es_ecp_addr16   ));//地址低位。
        for(count=0;count<arg_len;count++){
            ecbm_stream_out(es_ecp_data_buf[count]);//发送数据。
        }
        ecbm_stream_out((u8)(crc>>8)); 
        ecbm_stream_out((u8)(crc));
        ecbm_stream_out(0xBE);  //帧尾。
    }
}
/*-------------------------------------------------------
04指令处理函数。
-------------------------------------------------------*/
void es_ecp_cmd04(void){
    es_ecp_write(es_ecp_addr16,es_ecp_data_buf,es_ecp_data_len);
    es_ecp_cmd_back(0x05);
}
/*-------------------------------------------------------
06指令处理函数。
-------------------------------------------------------*/
void es_ecp_cmd06(void){
    u8 buf[ES_ECP_DATA_BUF_MAX],i;
    es_ecp_read(es_ecp_addr16,buf,es_ecp_data_len);
    for(i=0;i<es_ecp_data_len;i++){
        buf[i]|=es_ecp_data_buf[i];
    }
    es_ecp_write(es_ecp_addr16,buf,es_ecp_data_len);
    es_ecp_cmd_back(0x07);
}
/*-------------------------------------------------------
08指令处理函数。
-------------------------------------------------------*/
void es_ecp_cmd08(void){
    u8 buf[ES_ECP_DATA_BUF_MAX],i;
    es_ecp_read(es_ecp_addr16,buf,es_ecp_data_len);
    for(i=0;i<es_ecp_data_len;i++){
        buf[i]&=es_ecp_data_buf[i];
    }
    es_ecp_write(es_ecp_addr16,buf,es_ecp_data_len);
    es_ecp_cmd_back(0x09);
}
/*-------------------------------------------------------
ECP主机写函数。
-------------------------------------------------------*/
#if ES_ECP_MASTER_EN
void es_ecp_master_write(u8 id,u16 addr,u8 * buf,u8 len){
    u8 count;
    u16 crc;
    crc=es_ecp_crc16(0xffff,0xEC);
    crc=es_ecp_crc16(crc, len);
    crc=es_ecp_crc16(crc,~len);
    crc=es_ecp_crc16(crc,id);
    crc=es_ecp_crc16(crc,es_ecp_get_id()); 
    crc=es_ecp_crc16(crc,0x04);
    crc=es_ecp_crc16(crc,0x00);
    crc=es_ecp_crc16(crc,0x00);
    crc=es_ecp_crc16(crc,(u8)(addr>>8));
    crc=es_ecp_crc16(crc,(u8)(addr   ));
    for(count=0;count<len;count++){
        crc=es_ecp_crc16(crc,buf[count]);
    }
    ecbm_stream_out(0xEC);  //帧头。
    ecbm_stream_out( len); //长度。
    ecbm_stream_out(~len);//长度反码。
    ecbm_stream_out(id);//
    ecbm_stream_out(es_ecp_get_id()); //带上本机的ID。
    ecbm_stream_out(0x04);  //
    ecbm_stream_out(0x00);//地址高位。
    ecbm_stream_out(0x00);//地址低位。
    ecbm_stream_out((u8)(addr>>8));//地址高位。
    ecbm_stream_out((u8)(addr   ));//地址低位。
    for(count=0;count<len;count++){
        ecbm_stream_out(buf[count]);//发送数据。
    }
    ecbm_stream_out((u8)(crc>>8)); 
    ecbm_stream_out((u8)(crc));
    ecbm_stream_out(0xBE);  //帧尾。
}
#endif
/*-------------------------------------------------------
ECP主机读函数。
-------------------------------------------------------*/
#if ES_ECP_MASTER_EN
void es_ecp_master_read(u8 id,u16 addr,u8 len){
    u16 crc;
    crc=es_ecp_crc16(0xffff,0xEC);
    crc=es_ecp_crc16(crc,0x01);
    crc=es_ecp_crc16(crc,0xFE);
    crc=es_ecp_crc16(crc,id);
    crc=es_ecp_crc16(crc,es_ecp_get_id()); 
    crc=es_ecp_crc16(crc,0x02);
    crc=es_ecp_crc16(crc,0x00);
    crc=es_ecp_crc16(crc,0x00);
    crc=es_ecp_crc16(crc,(u8)(addr>>8));
    crc=es_ecp_crc16(crc,(u8)(addr   ));
    crc=es_ecp_crc16(crc,len);
    
    ecbm_stream_out(0xEC);  //帧头。
    ecbm_stream_out(0x01); //长度。
    ecbm_stream_out(0xFE);//长度反码。
    ecbm_stream_out(id);//
    ecbm_stream_out(es_ecp_get_id()); //带上本机的ID。
    ecbm_stream_out(0x02);  //
    ecbm_stream_out(0x00);//地址高位。
    ecbm_stream_out(0x00);//地址低位。
    ecbm_stream_out((u8)(addr>>8));//地址高位。
    ecbm_stream_out((u8)(addr   ));//地址低位。
    ecbm_stream_out(len);//发送数据。
    ecbm_stream_out((u8)(crc>>8)); 
    ecbm_stream_out((u8)(crc));
    ecbm_stream_out(0xBE);  //帧尾。
}
#endif
/*-------------------------------------------------------
ECP解析执行函数。
-------------------------------------------------------*/
void es_ecp_exe(u8 dat){
    switch(es_ecp_status){
        case ES_ECP_READY:{                             //准备状态。
            if(dat==0xEC){                              //读取到帧头的时候，
                es_ecp_status=ES_ECP_GET_DATA_LEN;      //去读取数据帧长度。
                es_ecp_crc=es_ecp_crc16(0xffff,0xEC);   //重置CRC，计算帧头的CRC。
            }
        }break;
        case ES_ECP_GET_DATA_LEN:{                  //读取数据帧长度状态。
            es_ecp_data_len=dat;                    //读取数据帧长度。
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//计算数据帧长度的CRC。
            es_ecp_status=ES_ECP_CHECK_DATA_LEN;    //去确认数据帧长度。
        }break;
        case ES_ECP_CHECK_DATA_LEN:{                        //确认数据帧长度状态。
            if(es_ecp_data_len==(~dat)){                    //放反码的用途之一就是可以用来加强识别帧头。
                es_ecp_status=ES_ECP_GET_TARGET_ID;         //确认正确之后，去获取目标ID。
                es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);    //计算数据帧长度反码的CRC。
            }else{                                          //如果不是长度的反码，说明这不是一个合法的帧头。
                if(es_ecp_data_len==0xEC){                  //回溯一下，是不是一个多余0xEC干扰了。
                    es_ecp_status=ES_ECP_CHECK_DATA_LEN;    //是的话，本字节就应该是数据帧长度了，那么下一步就是到确认数据帧长度状态。
                    es_ecp_data_len=dat;                    //把数据帧长度存好。
                    es_ecp_crc=es_ecp_crc16(0xffff,0xEC);   //重置CRC，计算帧头的CRC。
                    es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//计算数据帧长度的CRC。
                }else{                                      //不是的话，那就再看看是不是这几步判断的时候来了0xEC信号。
                    if(dat==0xEC){                          //最后一次判断帧头了。
                        es_ecp_status=ES_ECP_GET_DATA_LEN;  //是的话，需要重新读取一遍数据帧长度。
                        es_ecp_crc=es_ecp_crc16(0xffff,0xEC);//重置CRC，计算帧头的CRC。
                    }else{                                  //到这里还不是的话，说明接收到的完全是干扰。
                        es_ecp_status=ES_ECP_READY;         //回到准备状态。
                    }//注意事项：
                }   //之所以在这里要判断那么多，是因为在传输过程中普通数据里也会出现0xEC的，就是说别一遇到0xEC就认为是帧头，要连着长度和长度反码综合判断。
            }       //虽然钻牛角尖而言，普通数据出现合法帧头（0xEC，长度，长度反码）的概率也不是0，但判断3个字节误判的概率是远远低于只判断1个字节的。
        }break;
        case ES_ECP_GET_TARGET_ID:{                 //读取目标ID状态。
            es_ecp_target_id=dat;                   //读取目标ID。
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//计算目标ID的CRC。
            es_ecp_status=ES_ECP_GET_SOURCE_ID;     //去读取发送方ID。
        }break;
        case ES_ECP_GET_SOURCE_ID:{                 //读取发送方ID状态。
            es_ecp_source_id=dat;                   //读取发送方ID。
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//计算发送方ID的CRC。
            es_ecp_status=ES_ECP_GET_OPERATION;     //去读取操作码。
        }break;
        case ES_ECP_GET_OPERATION:{                 //读取操作码状态。
            es_ecp_operation=dat;                   //保存操作码。
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//计算操作码的CRC。
            es_ecp_status=ES_ECP_GET_ADDR_31_24;    //去读取地址。
        }break;
        case ES_ECP_GET_ADDR_31_24:{                //读取地址31~24位状态。
            es_ecp_addr16_ex=(u16)dat;              //保存地址高位。
            es_ecp_status=ES_ECP_GET_ADDR_23_16;    //这个地址是给32位单片机的预留，51单片机有另外的含义。
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,0x00);//预留的也要计算0x00的CRC。
        }break;
        case ES_ECP_GET_ADDR_23_16:{                //读取地址23~16位状态。
            es_ecp_addr16_ex<<=8;                   //把上一次的地址，
            es_ecp_addr16_ex+=(u16)dat;             //和这一次的地址合并在一起。
            es_ecp_status=ES_ECP_GET_ADDR_15_8;     //这个地址是给32位单片机的预留，51单片机有另外的含义。
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,0x00);//预留的也要计算0x00的CRC。
        }break;
        case ES_ECP_GET_ADDR_15_8:{                 //读取地址15~8位状态。
            es_ecp_addr16=(u16)dat;                 //保存地址高位。
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//计算地址高位的CRC。
            es_ecp_status=ES_ECP_GET_ADDR_7_0;      //去读取地址低位。
        }break;
        case ES_ECP_GET_ADDR_7_0:{                  //读取地址7~0位状态。
            es_ecp_addr16<<=8;                      //把上一次的地址，
            es_ecp_addr16+=(u16)dat;                //和这一次的地址合并在一起。
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//计算地址低位的CRC。
            if(es_ecp_data_len){                    //如果数据长度存在，
                es_ecp_status=ES_ECP_GET_DATA;      //就到读取数据状态。
                es_ecp_count=0;                     //清零数据计数变量。 
            }else{                                  //数据长度为0的话，
                es_ecp_status=ES_ECP_GET_CRC_H;     //就去读取CRC。
            }
        }break;
        case ES_ECP_GET_DATA:{                      //读取参数、数据状态。
            es_ecp_data_buf[es_ecp_count++]=dat;    //将参数、数据存入缓存，然后计数+1。
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//计算数据的CRC。
            if(es_ecp_count>=es_ecp_data_len){      //当计数达到目标时，
                es_ecp_status=ES_ECP_GET_CRC_H;     //就去读取CRC。
            }
        }break;
        case ES_ECP_GET_CRC_H:{                 //读取CRC高位状态。
            es_ecp_crc_buf=(u16)dat;            //组装CRC。
            es_ecp_status=ES_ECP_GET_CRC_L;     //到下一步。
        }break;
        case ES_ECP_GET_CRC_L:{                 //读取CRC低位状态。
            es_ecp_crc_buf<<=8;                 //组装CRC。
            es_ecp_crc_buf+=(u16)dat;
            es_ecp_status=ES_ECP_END;           //到判断帧尾阶段了。
        }break;
        case ES_ECP_END:{                       //判断帧尾状态。
            es_ecp_status=ES_ECP_READY;         //不管是不是帧尾，都可以回到准备状态了。
            if((dat==0xBE)&&(es_ecp_crc_buf==es_ecp_crc)){                    //但是检测到合法的CRC和帧尾时才能执行帧内动作。
                if((es_ecp_target_id==es_ecp_get_id())||(es_ecp_target_id==0)){//确认本帧数据是发往本机的，亦或者是广播。
                    switch(es_ecp_operation){//根据操作码来执行相应动作。
                        case 0x00:es_ecp_cmd_back(0x01);break;//查询。
                        case 0x02:es_ecp_cmd02();break;//读取。
                        case 0x04:es_ecp_cmd04();break;//写入。
                        case 0x06:es_ecp_cmd06();break;//置位。
                        case 0x08:es_ecp_cmd08();break;//复位。
                        case 0x01:break;
                        case 0x03:es_ecp_read_callback(es_ecp_addr16,es_ecp_data_buf,es_ecp_data_len);break;
                        case 0x05:break;
                        case 0x07:break;
                        case 0x09:break;
                    }
                }
            }
        }break;
    }
}
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。