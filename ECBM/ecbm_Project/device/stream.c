#include "stream.h"//����ͷ�ļ�
#if ECBM_STREAM_EN//��鱾����û�б�ʹ��
/*--------------------------------------��������-----------------------------------*/
u8 xdata ecbm_stream_buf[ECBM_STREAM_SZIE];
u8 ecbm_stream_start =0;
u8 ecbm_stream_stop  =0;
u8 ecbm_stream_count =0;
u8 ecbm_stream_time  =0;
u8 ecbm_stream_status=0;
/*--------------------------------------������-----------------------------------*/
/*-------------------------------------------------------
������������������
-------------------------------------------------------*/
void ecbm_stream_main(void){
    //���봦���������
    if(ecbm_stream_status&ECBM_STREAM_TIME_OUT){//�����ǽ��ճ�ʱ״̬�����״̬�����Ѿ�����һ��ʱ��û���µ����ݹ����ˡ�
        if((ecbm_stream_count>0)&&(ecbm_stream_count<ECBM_STREAM_SZIE)){//�жϽ��յ������ݵ������Ƿ�Ϸ���
            ecbm_stream_status&=~ECBM_STREAM_TIME_OUT;  //��ʼ���������ˣ���������־λ��
            while(ecbm_stream_count){
                ecbm_stream_exe(ecbm_stream_buf[ecbm_stream_start]);
                ecbm_stream_start++;
                if(ecbm_stream_start>=ECBM_STREAM_SZIE){
                    ecbm_stream_start=0;
                }
                ecbm_stream_count--;
            }
            ecbm_stream_start=ecbm_stream_stop;
        }else{//������Ϸ��Ļ�����ִ������Ķ�����
            if(ecbm_stream_count>=ECBM_STREAM_SZIE){    //����ǽ��յ����ݳ����˶��е����̷�Χ��
                ecbm_stream_count=0;                    //���ǵ����ݿ����Ѿ�������ʧ������������Щ���ݡ�
            }
        }
    }
    if(ecbm_stream_status&ECBM_STREAM_UART_IDLE){
        ecbm_stream_status&=~ECBM_STREAM_UART_IDLE;  //��������־λ��
        #if ECBM_STREAM_FUR_EN
            es_fur_status=FUR_READY;
        #endif
        #if ECBM_STREAM_MODBUS_EN
            es_modbus_rtu_status=ES_MODBUS_RTU_READY;
        #endif
        #if ECBM_STREAM_ECP_EN
            es_ecp_status=ES_ECP_READY;
        #endif
        #if ECBM_STREAM_XMODEM_EN
            es_xmodem_status     =0; 
        #endif

    }
}
/*-------------------------------------------------------
������ȶԺ�����
-------------------------------------------------------*/
#if ECBM_STREAM_CMP_EN
void ecbm_stream_strcmp(u8 dat,u8 code * str,u8 * count){
    if(str[*count]==dat){    //�ж�һ�µ�ǰ�������ݺ͹ؼ��ֵ�ĳ���ַ��Ƿ�һ����
        (*count)++;          //һ���Ļ�������+1���´�ѭ���ͻ��ж���һ���ַ��ˡ�
    }else{                   //��һ���Ļ���
        *count=0;            //�������㡣�����ڱ���ѭ���У��������������ؼ��ֵ�һ�����ַ���
        if(str[*count]==dat){//��Ȼ���������ַ���Ҫ�ж����Ƿ��뵱ǰ�������ݷ��ϡ�
            (*count)++;      //���Ͼͼ���+1��
        }
    }
}
#endif
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��