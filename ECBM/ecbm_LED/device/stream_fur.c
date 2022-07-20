#include "stream_fur.h"//加载头文件
#if (ECBM_STREAM_EN)&&(ECBM_STREAM_FUR_EN)//检查本库有没有被使能
/*--------------------------------------变量定义-----------------------------------*/
u8  es_fur_status =0;//FUR接收状态机。
u16 es_fur_addr   =0;//FUR地址。
u16 es_fur_dat16  =0;//FUR数据（16位）。
u8  es_fur_id     =0;//FUR的ID临时变量。
u8  es_fur_dat8   =0;//FUR数据（8位）。
u8  es_fur_operate=0;//FUR操作数。
u8  es_fur_temp8  =0;//FUR临时变量（8位）。
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
FUR重置函数。
-------------------------------------------------------*/
void es_fur_reset(void){
    es_fur_status =FUR_GET_ADDR;   //一般都是要接收的时候才重置，所以重置后到接收地址状态，
    es_fur_addr   =0;              //FUR地址清零。
    es_fur_dat16  =0;              //FUR数据（16位）清零。
    es_fur_id     =0;              //FUR的ID临时变量清零。
    es_fur_dat8   =0;              //FUR数据（8位）清零。
    es_fur_operate=0;              //FUR操作数清零。
    es_fur_temp8  =0;              //FUR临时变量（8位）清零。
}
/*-------------------------------------------------------
FUR发送数据函数，以10进制的格式发送。
-------------------------------------------------------*/
void es_fur_send_num_10(u16 num){
    u8 a,b,c,d,e;
    a=num       /10000;
    b=num%10000/1000;
    c=num%1000/100;
    d=num%100/10;
    e=num%10/1;
    if(a)uart_char(ECBM_STREAM_UART,a+'0');
    if(a|b)uart_char(ECBM_STREAM_UART,b+'0');
    if(a|b|c)uart_char(ECBM_STREAM_UART,c+'0');
    if(a|b|c|d)uart_char(ECBM_STREAM_UART,d+'0');
    uart_char(ECBM_STREAM_UART,e+'0');
}
/*-------------------------------------------------------
FUR发送数据函数，以16进制的格式发送。
-------------------------------------------------------*/
void es_fur_send_num_16(u16 num){
    u8 i;
    u16 temp16;
    temp16=num;
    for(i=0;i<4;i++){
        if((temp16&0xF000)<0xA000){
            uart_char(ECBM_STREAM_UART,'0'+(temp16&0xF000)>>12);
        }else{
            uart_char(ECBM_STREAM_UART,'A'+((temp16&0xF000)>>12)-10);
        }
        temp16<<=4;
    }
}
/*-------------------------------------------------------
FUR解析执行函数。
-------------------------------------------------------*/
void es_fur_exe(u8 dat){
    u16 temp16,mask;
    u8  operate;
    switch(es_fur_status){
        case FUR_READY:{    //就绪状态。
            //啥也不做。
        }break;
        case FUR_GET_ADDR:{ //接收地址状态。
            if((dat>='0')&&(dat<='9')){    //如果收到的是0~9，
                es_fur_addr*=10;           //空出一位，
                es_fur_addr+=(dat-'0');    //把字符转换成数字放入空出的那一位上。
            }else if(dat=='@'){            //但要是接收到@，说明有ID数据。
                es_fur_status=FUR_GET_ID;  //跳转到接收ID状态。
            }else if((dat==']')||(dat==')')){//如果收到]或者)，说明地址已经接收完毕。
                es_fur_status=FUR_GET_OP;  //跳转到接收操作状态。
            }else if((dat=='i')||(dat=='I')){//如果收到了小写的i，或者大写的I。
                es_fur_status=FUR_CMD_ID;  //说明可能是查ID的指令，跳转到查ID状态。
            }else{                         //如果是收到其他字符，说明接收出错了。
                es_fur_status=FUR_READY;   //回到就绪状态。
            }
        }break;
        case FUR_CMD_ID:{   //查ID状态。
            if((dat=='d')||(dat=='D')){    //在这个状态下，只判断是不是ID，不是就跳出去。
                es_fur_operate|=FUR_FBID;  //置位查询ID。
            }else if(dat==']'){            //如果收到]，说明指令已经接收完毕。
                es_fur_status=FUR_GET_OP;  //跳转到接收操作状态。
            }else{                         //如果是收到其他字符，说明接收出错了。
                es_fur_status=FUR_READY;   //回到就绪状态。
            }
        }break;
        case FUR_GET_ID:{   //接收ID状态。
            if((dat>='0')&&(dat<='9')){    //如果收到的是0~9，
                es_fur_id*=10;             //空出一位，
                es_fur_id+=(dat-'0');      //把字符转换成数字放入空出的那一位上。
            }else if(dat==']'){            //如果收到]，说明ID已经接收完毕。
                es_fur_status=FUR_GET_OP;  //跳转到接收操作状态。
            }else{                         //如果是收到其他字符，说明接收出错了。
                es_fur_status=FUR_READY;   //回到就绪状态。
            }
        }break;
        case FUR_GET_OP:{   //接收操作数状态。
            if(dat=='+'){                      //如果收到+号，
                es_fur_operate|=FUR_ADD;       //执行加操作。
                es_fur_status  =FUR_GET_OP_EX; //跳到扩展操作状态。
            }else if(dat=='-'){                //如果收到-号，
                es_fur_operate|=FUR_DEC;       //执行减操作。
                es_fur_status  =FUR_GET_OP_EX; //跳到扩展操作状态。
            }else if(dat=='*'){                //如果收到*号，
                es_fur_operate|=FUR_MUL;       //执行乘操作。
                es_fur_status  =FUR_GET_OP_EX; //跳到扩展操作状态。
            }else if(dat=='/'){                //如果收到/号，
                es_fur_operate|=FUR_DIV;       //执行除操作。
                es_fur_status  =FUR_GET_OP_EX; //跳到扩展操作状态。
            }else if(dat=='&'){                //如果收到&号，
                es_fur_operate|=FUR_AND;       //执行与操作。
                es_fur_status  =FUR_GET_OP_EX; //跳到扩展操作状态。
            }else if(dat=='|'){                //如果收到|号，
                es_fur_operate|=FUR_OR;        //执行或操作。
                es_fur_status  =FUR_GET_OP_EX; //跳到扩展操作状态。
            }else if(dat=='^'){                //如果收到^号，
                es_fur_operate|=FUR_XOR;       //执行异或操作。
                es_fur_status  =FUR_GET_OP_EX; //跳到扩展操作状态。
            }else if(dat=='.'){                //如果收到.号，
                es_fur_operate|=FUR_BIT;       //执行位操作。
                es_fur_status  =FUR_GET_OP_EX; //跳到扩展操作状态。
            }else if(dat=='='){                //如果收到=号，
                es_fur_operate|=FUR_EQU;       //执行赋值操作。
                es_fur_status  =FUR_GET_DATA;  //跳到接收数据状态（十进制）。
            }else if(dat=='x'){                //如果在这里收到x，代表是十六进制。
                es_fur_operate|=FUR_HEX;       //置位对应的标志位，但不需要跳转到其他状态。
            }else if(dat=='?'){                //如果收到?号，
                es_fur_operate|=FUR_READ;      //执行读取操作。
                es_fur_status  =FUR_WAIT_END;  //跳到等待结束态。
            }else{                             //如果是收到其他字符，说明接收出错了。
                es_fur_status=FUR_READY;       //回到就绪状态。
            }
        }break;
        case FUR_GET_OP_EX:{//接收扩展操作状态（目前就是接收位操作的位编号的）。
            if((dat>='0')&&(dat<='9')){        //如果收到的是0~9，
                es_fur_dat8*=10;               //空出一位，
                es_fur_dat8+=(dat-'0');        //把字符转换成数字放入空出的那一位上。
            }else if(dat=='='){                //如果收到=号，
                es_fur_dat8&=0x0F;             //限制该参数不能超过15，然后给操作变量。
                es_fur_status=FUR_GET_DATA;    //跳到接收数据状态（十进制）。
            }else{                             //如果是收到其他字符，说明接收出错了。
                es_fur_status=FUR_READY;       //回到就绪状态。
            }
        }break;
        case FUR_GET_DATA:{ //接收数据状态（十进制）。
            if((dat>='0')&&(dat<='9')){        //如果收到的是0~9，
                es_fur_dat16*=10;              //空出一位，
                es_fur_dat16+=(dat-'0');       //把字符转换成数字放入空出的那一位上。
            }else if(dat==';'){                //如果收到结束符，
                es_fur_status=FUR_END_DO;      //跳到结束态。
            }else if((dat=='x')||(dat=='X')){  //如果收到的是x，说明可能要收到16进制数。
                es_fur_dat16=0;                //清除16位数据变量。
                es_fur_operate|=FUR_HEX;       //标记这次通信以16进制表示。
                es_fur_status=FUR_GET_DATA16;  //跳到接收数据状态（十六进制）。
            }else{                             //如果是收到其他字符，说明接收出错了。
                es_fur_status=FUR_READY;       //回到就绪状态。
            }
        }break;
        case FUR_GET_DATA16:{//接收数据状态（十六进制）。
            if((dat>='0')&&(dat<='9')){        //如果收到的是0~9，
                es_fur_dat16*=16;              //空出4bit，
                es_fur_dat16+=(dat-'0');       //把字符转换成数字放入空出的位上。
            }else if((dat>='a')&&(dat<='f')){  //如果收到的是小写的字母，
                es_fur_dat16*=16;         
                es_fur_dat16+=(dat-'a'+10);    //和上面一样都是转化字符。
            }else if((dat>='A')&&(dat<='F')){  //如果收到的是大写的字母，
                es_fur_dat16*=16;
                es_fur_dat16+=(dat-'A'+10);    //和上面一样都是转化字符。
            }else if(dat==';'){                //如果收到结束符，
                es_fur_status=FUR_END_DO;      //跳到结束态。
            }else{                             //如果是收到其他字符，说明接收出错了。
                es_fur_status=FUR_READY;       //回到就绪状态。
            }
        }break;
        case FUR_WAIT_END:{ //等待结束符状态。
            if(dat==';'){                      //如果收到结束符，
                es_fur_status=FUR_END_DO;      //到结束态。
            }
        }break;
    }
    if(es_fur_status==FUR_END_DO){     //处于结束态的时候，开始处理指令。
        operate=es_fur_operate&0x0F;
        if(operate==FUR_FBID){//读ID是不需要检查ID的，所以先判断这个。
            #if ECBM_STREAM_FUR_UART_SEND_EN
                uart_char(ECBM_STREAM_UART,'i');
                uart_char(ECBM_STREAM_UART,'d');
                uart_char(ECBM_STREAM_UART,'=');
                es_fur_send_num_10((u16)es_fur_get_id());
                uart_char(ECBM_STREAM_UART,';');
                uart_char(ECBM_STREAM_UART,'\r');
                uart_char(ECBM_STREAM_UART,'\n');
            #endif
        }else{//除了查询ID指令外，剩下的指令都需要对ID进行比较。
            if( (es_fur_id==0)||//如果是广播，
                (es_fur_id==es_fur_get_id())){//或者ID能匹配上。
                temp16=es_fur_read_reg(es_fur_addr);
                if(es_fur_operate&FUR_WRITE){   //如果这帧数据是主机发来的，
                    switch(operate){            //根据指令操作，操作本地的寄存器。
                        case FUR_READ://读寄存器。
                            //啥都不用做。
                        break;
                        case FUR_ADD://寄存器加上一个数。
                            temp16+=es_fur_dat16;
                        break;
                        case FUR_DEC://寄存器减去一个数。
                            temp16-=es_fur_dat16;
                        break;
                        case FUR_MUL://寄存器乘以一个数。
                            temp16*=es_fur_dat16;
                        break;
                        case FUR_DIV://寄存器除以一个数。
                            temp16/=es_fur_dat16;
                        break;
                        case FUR_AND://寄存器与上一个数。
                            temp16&=es_fur_dat16;
                        break;
                        case FUR_OR://寄存器或上一个数。
                            temp16|=es_fur_dat16;
                        break;
                        case FUR_XOR://寄存器异或上一个数。
                            temp16^=es_fur_dat16;
                        break;
                        case FUR_BIT://寄存器位赋值。
                            mask=1<<es_fur_dat8;
                            if(es_fur_dat16){
                                temp16|=mask;
                            }else{
                                temp16&=~mask;
                            }
                        break;
                        case FUR_EQU://寄存器赋值。
                            temp16=es_fur_dat16;
                        break;
                    }
                    es_fur_write_reg(es_fur_addr,temp16);
                    #if ECBM_STREAM_FUR_UART_SEND_EN
                        uart_char(ECBM_STREAM_UART,'(');
                        es_fur_send_num_10(es_fur_addr);
                        uart_char(ECBM_STREAM_UART,')');
                        uart_char(ECBM_STREAM_UART,'=');
                        if(es_fur_operate&FUR_HEX){
                            uart_char(ECBM_STREAM_UART,'0');
                            uart_char(ECBM_STREAM_UART,'x');
                            es_fur_send_num_16(temp16);
                        }else{
                            es_fur_send_num_10(temp16);
                        }
                        uart_char(ECBM_STREAM_UART,';');
                        uart_char(ECBM_STREAM_UART,'\r');
                        uart_char(ECBM_STREAM_UART,'\n');
                    #endif
                }else{//如果这帧数据是从机返回的，
                    #if ECBM_STREAM_FUR_MATER_EN
                        es_fur_master_receive_callback(es_fur_addr,es_fur_dat16);//执行从机接收回调。
                    #endif
                }
            }
        }
        es_fur_status=FUR_READY;        //处理完毕，到就绪状态。
    }
    if(dat=='['){                       //任何时候如果收到了开始标记[，
        es_fur_reset();                 //就得先重置fur，
        es_fur_operate|=FUR_WRITE;      //再打上写入标志。
    }else if(dat=='('){                 //如果接收到得是从机返回数据标记(，
        es_fur_reset();                 //就只重置fur。
    }
}
/*-------------------------------------------------------
FUR主机发送函数。
-------------------------------------------------------*/
#if ECBM_STREAM_FUR_MATER_EN
void es_fur_master_send(u16 addr,u8 id,u16 dat){
    uart_char(ECBM_STREAM_UART,'[');
    es_fur_send_num_10(addr);
    if(id){
        uart_char(ECBM_STREAM_UART,'@');
        es_fur_send_num_10(id);
    }
    uart_char(ECBM_STREAM_UART,']');
    uart_char(ECBM_STREAM_UART,'=');
    es_fur_send_num_10(dat);
    uart_char(ECBM_STREAM_UART,';');
    uart_char(ECBM_STREAM_UART,'\r');
    uart_char(ECBM_STREAM_UART,'\n');
}
#endif
/*-------------------------------------------------------
FUR主机读取函数。
-------------------------------------------------------*/
#if ECBM_STREAM_FUR_MATER_EN
void es_fur_master_read(u16 addr,u8 id){
    uart_char(ECBM_STREAM_UART,'[');
    es_fur_send_num_10(addr);
    if(id){
        uart_char(ECBM_STREAM_UART,'@');
        es_fur_send_num_10(id);
    }
    uart_char(ECBM_STREAM_UART,']');
    uart_char(ECBM_STREAM_UART,'?');
    uart_char(ECBM_STREAM_UART,';');
    uart_char(ECBM_STREAM_UART,'\r');
    uart_char(ECBM_STREAM_UART,'\n');
}
#endif
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。