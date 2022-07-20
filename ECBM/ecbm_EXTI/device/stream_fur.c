#include "stream_fur.h"//����ͷ�ļ�
#if (ECBM_STREAM_EN)&&(ECBM_STREAM_FUR_EN)//��鱾����û�б�ʹ��
/*--------------------------------------��������-----------------------------------*/
u8  es_fur_status =0;//FUR����״̬����
u16 es_fur_addr   =0;//FUR��ַ��
u16 es_fur_dat16  =0;//FUR���ݣ�16λ����
u8  es_fur_id     =0;//FUR��ID��ʱ������
u8  es_fur_dat8   =0;//FUR���ݣ�8λ����
u8  es_fur_operate=0;//FUR��������
u8  es_fur_temp8  =0;//FUR��ʱ������8λ����
/*--------------------------------------������-----------------------------------*/
/*-------------------------------------------------------
FUR���ú�����
-------------------------------------------------------*/
void es_fur_reset(void){
    es_fur_status =FUR_GET_ADDR;   //һ�㶼��Ҫ���յ�ʱ������ã��������ú󵽽��յ�ַ״̬��
    es_fur_addr   =0;              //FUR��ַ���㡣
    es_fur_dat16  =0;              //FUR���ݣ�16λ�����㡣
    es_fur_id     =0;              //FUR��ID��ʱ�������㡣
    es_fur_dat8   =0;              //FUR���ݣ�8λ�����㡣
    es_fur_operate=0;              //FUR���������㡣
    es_fur_temp8  =0;              //FUR��ʱ������8λ�����㡣
}
/*-------------------------------------------------------
FUR�������ݺ�������10���Ƶĸ�ʽ���͡�
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
FUR�������ݺ�������16���Ƶĸ�ʽ���͡�
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
FUR����ִ�к�����
-------------------------------------------------------*/
void es_fur_exe(u8 dat){
    u16 temp16,mask;
    u8  operate;
    switch(es_fur_status){
        case FUR_READY:{    //����״̬��
            //ɶҲ������
        }break;
        case FUR_GET_ADDR:{ //���յ�ַ״̬��
            if((dat>='0')&&(dat<='9')){    //����յ�����0~9��
                es_fur_addr*=10;           //�ճ�һλ��
                es_fur_addr+=(dat-'0');    //���ַ�ת�������ַ���ճ�����һλ�ϡ�
            }else if(dat=='@'){            //��Ҫ�ǽ��յ�@��˵����ID���ݡ�
                es_fur_status=FUR_GET_ID;  //��ת������ID״̬��
            }else if((dat==']')||(dat==')')){//����յ�]����)��˵����ַ�Ѿ�������ϡ�
                es_fur_status=FUR_GET_OP;  //��ת�����ղ���״̬��
            }else if((dat=='i')||(dat=='I')){//����յ���Сд��i�����ߴ�д��I��
                es_fur_status=FUR_CMD_ID;  //˵�������ǲ�ID��ָ���ת����ID״̬��
            }else{                         //������յ������ַ���˵�����ճ����ˡ�
                es_fur_status=FUR_READY;   //�ص�����״̬��
            }
        }break;
        case FUR_CMD_ID:{   //��ID״̬��
            if((dat=='d')||(dat=='D')){    //�����״̬�£�ֻ�ж��ǲ���ID�����Ǿ�����ȥ��
                es_fur_operate|=FUR_FBID;  //��λ��ѯID��
            }else if(dat==']'){            //����յ�]��˵��ָ���Ѿ�������ϡ�
                es_fur_status=FUR_GET_OP;  //��ת�����ղ���״̬��
            }else{                         //������յ������ַ���˵�����ճ����ˡ�
                es_fur_status=FUR_READY;   //�ص�����״̬��
            }
        }break;
        case FUR_GET_ID:{   //����ID״̬��
            if((dat>='0')&&(dat<='9')){    //����յ�����0~9��
                es_fur_id*=10;             //�ճ�һλ��
                es_fur_id+=(dat-'0');      //���ַ�ת�������ַ���ճ�����һλ�ϡ�
            }else if(dat==']'){            //����յ�]��˵��ID�Ѿ�������ϡ�
                es_fur_status=FUR_GET_OP;  //��ת�����ղ���״̬��
            }else{                         //������յ������ַ���˵�����ճ����ˡ�
                es_fur_status=FUR_READY;   //�ص�����״̬��
            }
        }break;
        case FUR_GET_OP:{   //���ղ�����״̬��
            if(dat=='+'){                      //����յ�+�ţ�
                es_fur_operate|=FUR_ADD;       //ִ�мӲ�����
                es_fur_status  =FUR_GET_OP_EX; //������չ����״̬��
            }else if(dat=='-'){                //����յ�-�ţ�
                es_fur_operate|=FUR_DEC;       //ִ�м�������
                es_fur_status  =FUR_GET_OP_EX; //������չ����״̬��
            }else if(dat=='*'){                //����յ�*�ţ�
                es_fur_operate|=FUR_MUL;       //ִ�г˲�����
                es_fur_status  =FUR_GET_OP_EX; //������չ����״̬��
            }else if(dat=='/'){                //����յ�/�ţ�
                es_fur_operate|=FUR_DIV;       //ִ�г�������
                es_fur_status  =FUR_GET_OP_EX; //������չ����״̬��
            }else if(dat=='&'){                //����յ�&�ţ�
                es_fur_operate|=FUR_AND;       //ִ���������
                es_fur_status  =FUR_GET_OP_EX; //������չ����״̬��
            }else if(dat=='|'){                //����յ�|�ţ�
                es_fur_operate|=FUR_OR;        //ִ�л������
                es_fur_status  =FUR_GET_OP_EX; //������չ����״̬��
            }else if(dat=='^'){                //����յ�^�ţ�
                es_fur_operate|=FUR_XOR;       //ִ����������
                es_fur_status  =FUR_GET_OP_EX; //������չ����״̬��
            }else if(dat=='.'){                //����յ�.�ţ�
                es_fur_operate|=FUR_BIT;       //ִ��λ������
                es_fur_status  =FUR_GET_OP_EX; //������չ����״̬��
            }else if(dat=='='){                //����յ�=�ţ�
                es_fur_operate|=FUR_EQU;       //ִ�и�ֵ������
                es_fur_status  =FUR_GET_DATA;  //������������״̬��ʮ���ƣ���
            }else if(dat=='x'){                //����������յ�x��������ʮ�����ơ�
                es_fur_operate|=FUR_HEX;       //��λ��Ӧ�ı�־λ��������Ҫ��ת������״̬��
            }else if(dat=='?'){                //����յ�?�ţ�
                es_fur_operate|=FUR_READ;      //ִ�ж�ȡ������
                es_fur_status  =FUR_WAIT_END;  //�����ȴ�����̬��
            }else{                             //������յ������ַ���˵�����ճ����ˡ�
                es_fur_status=FUR_READY;       //�ص�����״̬��
            }
        }break;
        case FUR_GET_OP_EX:{//������չ����״̬��Ŀǰ���ǽ���λ������λ��ŵģ���
            if((dat>='0')&&(dat<='9')){        //����յ�����0~9��
                es_fur_dat8*=10;               //�ճ�һλ��
                es_fur_dat8+=(dat-'0');        //���ַ�ת�������ַ���ճ�����һλ�ϡ�
            }else if(dat=='='){                //����յ�=�ţ�
                es_fur_dat8&=0x0F;             //���Ƹò������ܳ���15��Ȼ�������������
                es_fur_status=FUR_GET_DATA;    //������������״̬��ʮ���ƣ���
            }else{                             //������յ������ַ���˵�����ճ����ˡ�
                es_fur_status=FUR_READY;       //�ص�����״̬��
            }
        }break;
        case FUR_GET_DATA:{ //��������״̬��ʮ���ƣ���
            if((dat>='0')&&(dat<='9')){        //����յ�����0~9��
                es_fur_dat16*=10;              //�ճ�һλ��
                es_fur_dat16+=(dat-'0');       //���ַ�ת�������ַ���ճ�����һλ�ϡ�
            }else if(dat==';'){                //����յ���������
                es_fur_status=FUR_END_DO;      //��������̬��
            }else if((dat=='x')||(dat=='X')){  //����յ�����x��˵������Ҫ�յ�16��������
                es_fur_dat16=0;                //���16λ���ݱ�����
                es_fur_operate|=FUR_HEX;       //������ͨ����16���Ʊ�ʾ��
                es_fur_status=FUR_GET_DATA16;  //������������״̬��ʮ�����ƣ���
            }else{                             //������յ������ַ���˵�����ճ����ˡ�
                es_fur_status=FUR_READY;       //�ص�����״̬��
            }
        }break;
        case FUR_GET_DATA16:{//��������״̬��ʮ�����ƣ���
            if((dat>='0')&&(dat<='9')){        //����յ�����0~9��
                es_fur_dat16*=16;              //�ճ�4bit��
                es_fur_dat16+=(dat-'0');       //���ַ�ת�������ַ���ճ���λ�ϡ�
            }else if((dat>='a')&&(dat<='f')){  //����յ�����Сд����ĸ��
                es_fur_dat16*=16;         
                es_fur_dat16+=(dat-'a'+10);    //������һ������ת���ַ���
            }else if((dat>='A')&&(dat<='F')){  //����յ����Ǵ�д����ĸ��
                es_fur_dat16*=16;
                es_fur_dat16+=(dat-'A'+10);    //������һ������ת���ַ���
            }else if(dat==';'){                //����յ���������
                es_fur_status=FUR_END_DO;      //��������̬��
            }else{                             //������յ������ַ���˵�����ճ����ˡ�
                es_fur_status=FUR_READY;       //�ص�����״̬��
            }
        }break;
        case FUR_WAIT_END:{ //�ȴ�������״̬��
            if(dat==';'){                      //����յ���������
                es_fur_status=FUR_END_DO;      //������̬��
            }
        }break;
    }
    if(es_fur_status==FUR_END_DO){     //���ڽ���̬��ʱ�򣬿�ʼ����ָ�
        operate=es_fur_operate&0x0F;
        if(operate==FUR_FBID){//��ID�ǲ���Ҫ���ID�ģ��������ж������
            #if ECBM_STREAM_FUR_UART_SEND_EN
                uart_char(ECBM_STREAM_UART,'i');
                uart_char(ECBM_STREAM_UART,'d');
                uart_char(ECBM_STREAM_UART,'=');
                es_fur_send_num_10((u16)es_fur_get_id());
                uart_char(ECBM_STREAM_UART,';');
                uart_char(ECBM_STREAM_UART,'\r');
                uart_char(ECBM_STREAM_UART,'\n');
            #endif
        }else{//���˲�ѯIDָ���⣬ʣ�µ�ָ���Ҫ��ID���бȽϡ�
            if( (es_fur_id==0)||//����ǹ㲥��
                (es_fur_id==es_fur_get_id())){//����ID��ƥ���ϡ�
                temp16=es_fur_read_reg(es_fur_addr);
                if(es_fur_operate&FUR_WRITE){   //�����֡���������������ģ�
                    switch(operate){            //����ָ��������������صļĴ�����
                        case FUR_READ://���Ĵ�����
                            //ɶ����������
                        break;
                        case FUR_ADD://�Ĵ�������һ������
                            temp16+=es_fur_dat16;
                        break;
                        case FUR_DEC://�Ĵ�����ȥһ������
                            temp16-=es_fur_dat16;
                        break;
                        case FUR_MUL://�Ĵ�������һ������
                            temp16*=es_fur_dat16;
                        break;
                        case FUR_DIV://�Ĵ�������һ������
                            temp16/=es_fur_dat16;
                        break;
                        case FUR_AND://�Ĵ�������һ������
                            temp16&=es_fur_dat16;
                        break;
                        case FUR_OR://�Ĵ�������һ������
                            temp16|=es_fur_dat16;
                        break;
                        case FUR_XOR://�Ĵ��������һ������
                            temp16^=es_fur_dat16;
                        break;
                        case FUR_BIT://�Ĵ���λ��ֵ��
                            mask=1<<es_fur_dat8;
                            if(es_fur_dat16){
                                temp16|=mask;
                            }else{
                                temp16&=~mask;
                            }
                        break;
                        case FUR_EQU://�Ĵ�����ֵ��
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
                }else{//�����֡�����Ǵӻ����صģ�
                    #if ECBM_STREAM_FUR_MATER_EN
                        es_fur_master_receive_callback(es_fur_addr,es_fur_dat16);//ִ�дӻ����ջص���
                    #endif
                }
            }
        }
        es_fur_status=FUR_READY;        //������ϣ�������״̬��
    }
    if(dat=='['){                       //�κ�ʱ������յ��˿�ʼ���[��
        es_fur_reset();                 //�͵�������fur��
        es_fur_operate|=FUR_WRITE;      //�ٴ���д���־��
    }else if(dat=='('){                 //������յ����Ǵӻ��������ݱ��(��
        es_fur_reset();                 //��ֻ����fur��
    }
}
/*-------------------------------------------------------
FUR�������ͺ�����
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
FUR������ȡ������
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
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��