#include "stream_modbus.h"//����ͷ�ļ�
#if (ECBM_STREAM_EN)&&(ECBM_STREAM_MODBUS_EN)//��鱾����û�б�ʹ��
/*--------------------------------------��������-----------------------------------*/
u8  es_modbus_rtu_status      =0; //״̬��ʹ�õı�����
u8  es_modbus_rtu_broadcast_en=0; //�㲥ģʽ��
u8  es_modbus_rtu_fun_code    =0; //�����롣
u8  es_modbus_rtu_fun_err_num =0; //�쳣�롣
u16 es_modbus_rtu_address     =0; //���ݵ�ַ��
u16 es_modbus_rtu_data_count  =0; //����/������
u16 es_modbus_rtu_uart_crc    =0; //CRC���㻺�档
u16 es_modbus_rtu_crc_buf     =0; //CRC���档
u8  es_modbus_rtu_cmd_count   =0; //ָ��������
#if ES_MODBUS_RTU_CMD10_EN
u16 es_modbus_rtu_cmd_buf[ES_MODBUS_RTU_BUF_SIZE];//ָ��档
#endif
/*--------------------------------------������-----------------------------------*/
void es_modbus_rtu_crc16(u8 buf,u16 * crc){
    u8 j;
    u16 crc_buf;
    crc_buf=*crc;
    crc_buf^=buf;                       //��ǰ�������CRC���ֽڣ���C51�����ֱ�Ӵ�����
    for(j=0;j<8;j++){                   //����ÿ���ֽڵ�ÿһλ��
        if(crc_buf&0x01){               //�ж�����ǰ���λ�Ƿ�Ϊ1��
            crc_buf=(crc_buf>>1)^0xA001;//���Ϊ1�����Ʋ�������ʽ��
        }else{
            crc_buf>>=1;                //����ֱ������һλ��
        }           
    }
    *crc=crc_buf;
}
void es_modbus_rtu_err_num(u8 fun_num,u8 err_num){
    u8  id;
    u16 crc=0xFFFF;
    if(es_modbus_rtu_broadcast_en){     //ֻ�в��ǹ㲥֡��ʱ����ܻظ���
        id=es_modbus_rtu_get_id();      //��ȡ����ID��
        es_modbus_rtu_crc16(id          ,&crc); //����CRC����ͬ��
        es_modbus_rtu_crc16(0x80+fun_num,&crc);
        es_modbus_rtu_crc16(err_num     ,&crc);
        uart_char(ECBM_STREAM_UART,id);            //���͵�ַ��
        uart_char(ECBM_STREAM_UART,0x80+fun_num);  //����0x80+������ظ���
        uart_char(ECBM_STREAM_UART,err_num);       //�쳣�롣
        uart_char(ECBM_STREAM_UART,(u8)(crc));   //����CRC��
        uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
    }
}
/*-------------------------------------------------------
1�Ź����봦��������
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD01_EN
void es_modbus_rtu_cmd_0x01(void){
    u8 temp8,t1,c1,i,j,qw,id;
    u16 crc=0xFFFF;
    id=es_modbus_rtu_get_id();      //��ȡ����ID��
    if((es_modbus_rtu_data_count>=1)&&(es_modbus_rtu_data_count<=0x07D0)){          //��ȡ�ĸ���Ҫ��1�����ϣ��ҵ�ַ���ܴ���2000��
        if(((u32)es_modbus_rtu_data_count+(u32)es_modbus_rtu_address)<=65536UL){//�жϵ�ַ+������û�г��ޡ�
            if(es_modbus_rtu_broadcast_en){             //����ǹ㲥֡����ô�㲻�ܻظ���
                t1=(u8)(es_modbus_rtu_data_count/8);  //ͳ��Ҫ��ȡ�������ܴչ����ٸ��ֽڡ�
                if(es_modbus_rtu_data_count%8)t1++;     //ʣ�µĲ���8λ������ҲҪһ���ֽ������䡣
                es_modbus_rtu_crc16(id  ,&crc);  //����CRC����ͬ��
                es_modbus_rtu_crc16(0x01,&crc);
                es_modbus_rtu_crc16(t1  ,&crc);
                uart_char(ECBM_STREAM_UART,id);    //���͵�ַ��
                uart_char(ECBM_STREAM_UART,0x01);  //���͹�����ظ���
                uart_char(ECBM_STREAM_UART,t1);    //�������ݳ��ȡ�
                for(i=0;i<t1;i++){                          //����ʼλ�ÿ�ʼ��װ���ݡ�
                    temp8=0;                                //���������
                    if(es_modbus_rtu_data_count>=8){        //���ʣ��Ҫ�������ݶ���8�����ء�
                        c1=8;                               //��ô����ѭ���ȶ�8�������ݡ�
                    }else{                                  //����
                        c1=(u8)es_modbus_rtu_data_count;  //���ж��ٶ����١�
                    }
                    for(j=0;j<c1;j++){      
                        es_modbus_cmd_read_bit(es_modbus_rtu_address++,&qw);//����ַ�͵���ȡ�����У���ȡ��Ӧ�ı���ֵ��
                        if(qw)temp8|=(1<<j);                //��װ���ݡ�
                    }
                    es_modbus_rtu_crc16(temp8,&crc);        //����CRC��
                    uart_char(ECBM_STREAM_UART,temp8);                 //������װ�õ����ݡ�
                    es_modbus_rtu_data_count-=(u16)c1;    //����ʣ��Ҫ�������ݸ�����
                }
                uart_char(ECBM_STREAM_UART,(u8)(crc));               //����CRC
                uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
            }
        }else{                                  //�����ַ+��������65536��
            es_modbus_rtu_fun_err_num=0x02;     //��¼�쳣��02��
            es_modbus_rtu_err_num(0x01,es_modbus_rtu_fun_err_num);//���ʹ����롣
        }
    }else{                                  //������������ͳ���2000�ˡ�
        es_modbus_rtu_fun_err_num=0x03;     //��¼�쳣��03��
        es_modbus_rtu_err_num(0x01,es_modbus_rtu_fun_err_num);//���ʹ����롣
    }
}
#endif
/*-------------------------------------------------------
2�Ź����봦��������
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD02_EN
void es_modbus_rtu_cmd_0x02(void){
    u8 temp8,t1,c1,i,j,qw,id;
    u16 crc=0xFFFF;
    id=es_modbus_rtu_get_id();      //��ȡ����ID��
    if((es_modbus_rtu_data_count>=1)&&(es_modbus_rtu_data_count<=0x07D0)){              //��ȡ�ĸ���Ҫ��1�����ϣ��ҵ�ַ���ܴ���2000��
        if(((u32)es_modbus_rtu_data_count+(u32)es_modbus_rtu_address)<=65536UL){    //�жϵ�ַ+������û�г��ޡ�
                if(es_modbus_rtu_broadcast_en){             //����ǹ㲥֡����ô�㲻�ܻظ���
                    t1=(u8)(es_modbus_rtu_data_count/8);  //ͳ��Ҫ��ȡ�������ܴչ����ٸ��ֽڡ�
                    if(es_modbus_rtu_data_count%8)t1++;     //ʣ�µĲ���8λ������ҲҪһ���ֽ������䡣
                    es_modbus_rtu_crc16(id  ,&crc);         //����CRC����ͬ��
                    es_modbus_rtu_crc16(0x02,&crc);
                    es_modbus_rtu_crc16(t1  ,&crc);
                    uart_char(ECBM_STREAM_UART,id);                    //���͵�ַ��
                    uart_char(ECBM_STREAM_UART,0x02);                  //���͹�����ظ���
                    uart_char(ECBM_STREAM_UART,t1);                    //�������ݳ��ȡ�
                    for(i=0;i<t1;i++){                      //����ʼλ�ÿ�ʼ��װ���ݡ�
                        temp8=0;                            //���������
                        if(es_modbus_rtu_data_count>=8){    //���ʣ��Ҫ�������ݶ���8�����ء�
                            c1=8;                           //��ô����ѭ���ȶ�8�������ݡ�
                        }else{                              //����
                            c1=(u8)es_modbus_rtu_data_count;  //���ж��ٶ����١�
                        }
                        for(j=0;j<c1;j++){      
                            es_modbus_cmd_read_io_bit(es_modbus_rtu_address++,&qw);//����ַ�͵���ȡ�����У���ȡ��Ӧ�ı���ֵ��
                            if(qw)temp8|=(1<<j);                     //��װ���ݡ�
                        }
                        es_modbus_rtu_crc16(temp8,&crc);        //����CRC��
                        uart_char(ECBM_STREAM_UART,temp8);                 //������װ�õ����ݡ�
                        es_modbus_rtu_data_count-=(u16)c1;    //����ʣ��Ҫ�������ݸ�����
                    }
                    uart_char(ECBM_STREAM_UART,(u8)(crc));               //����CRC��
                    uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
                }
        }else{                                  //�����ַ+��������2000��
            es_modbus_rtu_fun_err_num=0x02;     //��¼�쳣��02��
            es_modbus_rtu_err_num(0x02,es_modbus_rtu_fun_err_num);//���ʹ����롣
        }
    }else{                                  //������������ͳ���65536�ˡ�
        es_modbus_rtu_fun_err_num=0x03;     //��¼�쳣��03��
        es_modbus_rtu_err_num(0x02,es_modbus_rtu_fun_err_num);//���ʹ����롣
    }
}
#endif
/*-------------------------------------------------------
3�Ź����봦��������
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD03_EN
void es_modbus_rtu_cmd_0x03(void){
    u8 id;
    u16 temp16,i,crc=0xffff;
    id=es_modbus_rtu_get_id();      //��ȡ����ID��
    if((es_modbus_rtu_data_count>=1)&&(es_modbus_rtu_data_count<=0x007D)){          //��ȡ�ĸ���Ҫ��1�����ϣ��ҵ�ַ���ܴ���125��
        if(((u32)es_modbus_rtu_data_count+(u32)es_modbus_rtu_address)<65536UL){ //�жϵ�ַ+������û�г��ޡ�
            if(es_modbus_rtu_broadcast_en){
                es_modbus_rtu_crc16(id  ,&crc);  //����CRC����ͬ��
                es_modbus_rtu_crc16(0x03,&crc);
                es_modbus_rtu_crc16(es_modbus_rtu_data_count*2,&crc);
                uart_char(ECBM_STREAM_UART,id);            //���͵�ַ��
                uart_char(ECBM_STREAM_UART,0x03);          //���͹�����ظ���
                uart_char(ECBM_STREAM_UART,es_modbus_rtu_data_count*2);//���ͻظ��ֽ�����
                for(i=0;i<es_modbus_rtu_data_count;i++){
                    es_modbus_cmd_read_reg(es_modbus_rtu_address+i,&temp16);//�ӼĴ��������������ȡ������
                    es_modbus_rtu_crc16((u8)(temp16>>8),&crc);            //����CRC����ͬ��
                    es_modbus_rtu_crc16((u8)(temp16),&crc);
                    uart_char(ECBM_STREAM_UART,(u8)(temp16>>8)); //�������ݡ�
                    uart_char(ECBM_STREAM_UART,(u8)(temp16));
                }
                uart_char(ECBM_STREAM_UART,(u8)(crc));//����CRC��
                uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
            }
        }else{
            es_modbus_rtu_fun_err_num=0x02; //��¼�쳣��02��
            es_modbus_rtu_err_num(0x03,es_modbus_rtu_fun_err_num);//���ʹ����롣
        }
    }else{                              //������������ͳ���125�ˡ�
        es_modbus_rtu_fun_err_num=0x03; //��¼�쳣��03��    
        es_modbus_rtu_err_num(0x03,es_modbus_rtu_fun_err_num);//���ʹ����롣
    }
}
#endif
/*-------------------------------------------------------
4�Ź����봦��������
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD04_EN
void es_modbus_rtu_cmd_0x04(void){
    u8 id;
    u16 temp16,i,crc=0xffff;
    id=es_modbus_rtu_get_id();      //��ȡ����ID��
    if((es_modbus_rtu_data_count>=1)&&(es_modbus_rtu_data_count<=0x007D)){          //��ȡ�ĸ���Ҫ��1�����ϣ��ҵ�ַ���ܴ���125��
        if(((u32)es_modbus_rtu_data_count+(u32)es_modbus_rtu_address)<65536UL){ //�жϵ�ַ+������û�г��ޡ�
            if(es_modbus_rtu_broadcast_en){
                es_modbus_rtu_crc16(id  ,&crc);     //����CRC����ͬ��
                es_modbus_rtu_crc16(0x04,&crc);
                es_modbus_rtu_crc16(es_modbus_rtu_data_count*2,&crc);
                uart_char(ECBM_STREAM_UART,id);                //���͵�ַ��
                uart_char(ECBM_STREAM_UART,0x04);              //���͹�����ظ���
                uart_char(ECBM_STREAM_UART,es_modbus_rtu_data_count*2);//���ͻظ��ֽ�����
                for(i=0;i<es_modbus_rtu_data_count;i++){
                    es_modbus_cmd_read_io_reg(es_modbus_rtu_address+i,&temp16);//�ӼĴ��������������ȡ������
                    es_modbus_rtu_crc16((u8)(temp16>>8),&crc); //����CRC����ͬ��
                    es_modbus_rtu_crc16((u8)(temp16),&crc);
                    uart_char(ECBM_STREAM_UART,(u8)(temp16>>8));//�������ݡ�
                    uart_char(ECBM_STREAM_UART,(u8)(temp16));
                }
                uart_char(ECBM_STREAM_UART,(u8)(crc));//����CRC��
                uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
            }
        }else{
            es_modbus_rtu_fun_err_num=0x02; //��¼�쳣��02��
            es_modbus_rtu_err_num(0x04,es_modbus_rtu_fun_err_num);//���ʹ����롣
        }
    }else{                              //������������ͳ���125�ˡ�
        es_modbus_rtu_fun_err_num=0x03; //��¼�쳣��03��    
        es_modbus_rtu_err_num(0x04,es_modbus_rtu_fun_err_num);//���ʹ����롣
    }
}
#endif
/*-------------------------------------------------------
5�Ź����봦��������
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD05_EN
void es_modbus_rtu_cmd_0x05(void){
    u8 id;
    u16 crc=0xffff;
    id=es_modbus_rtu_get_id();      //��ȡ����ID��
    if((es_modbus_rtu_data_count==0x0000)||(es_modbus_rtu_data_count==0xFF00)){//�ж����ֵ�Ƿ�Ϸ���
        es_modbus_cmd_write_bit(es_modbus_rtu_address,(u8)(es_modbus_rtu_data_count>>8));
        if(es_modbus_rtu_broadcast_en){
            es_modbus_rtu_crc16(id  ,&crc);                  //����CRC����ͬ��
            es_modbus_rtu_crc16(0x05,&crc);
            es_modbus_rtu_crc16((u8)(es_modbus_rtu_address>>8)   ,&crc);
            es_modbus_rtu_crc16((u8)(es_modbus_rtu_address)      ,&crc);
            es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count>>8),&crc);
            es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count)   ,&crc);
            uart_char(ECBM_STREAM_UART,id);               //���͵�ַ��
            uart_char(ECBM_STREAM_UART,0x05);                             //���͹�����ظ���
            uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address>>8)); //���͵�ַ�ظ���
            uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address));
            uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count>>8));//���ͼ����ظ���
            uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count));
            uart_char(ECBM_STREAM_UART,(u8)(crc));        //����CRC��
            uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
        }    
    }else{                              //������Ϸ���
        es_modbus_rtu_fun_err_num=0x03; //��¼�쳣��03��    
        es_modbus_rtu_err_num(0x05,es_modbus_rtu_fun_err_num);//���ʹ����롣
    }
}
#endif
/*-------------------------------------------------------
6�Ź����봦��������
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD06_EN
void es_modbus_rtu_cmd_0x06(void){
    u8 id;
    u16 crc=0xffff;
    id=es_modbus_rtu_get_id();      //��ȡ����ID��
    es_modbus_cmd_write_reg(es_modbus_rtu_address,es_modbus_rtu_data_count);//������д��Ĵ�����
    if(es_modbus_rtu_broadcast_en){
        es_modbus_rtu_crc16(id  ,&crc);          //����CRC����ͬ��
        es_modbus_rtu_crc16(0x06,&crc);
        es_modbus_rtu_crc16((u8)(es_modbus_rtu_address>>8),&crc);
        es_modbus_rtu_crc16((u8)(es_modbus_rtu_address),&crc);
        es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count>>8),&crc);
        es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count),&crc);
        uart_char(ECBM_STREAM_UART,id);        //���͵�ַ��
        uart_char(ECBM_STREAM_UART,0x06);      //���͹�����ظ���
        uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address>>8));//���͵�ַ��
        uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address));
        uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count>>8));//���͸�����
        uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count));
        uart_char(ECBM_STREAM_UART,(u8)(crc));//����CRC��
        uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
    }    
}
#endif
/*-------------------------------------------------------
16�Ź����봦��������
-------------------------------------------------------*/
#if ES_MODBUS_RTU_CMD10_EN
void es_modbus_rtu_cmd_0x10(void){
    u8 i,id;
    u16 crc=0xffff;
    id=es_modbus_rtu_get_id();      //��ȡ����ID��
    if((es_modbus_rtu_data_count>=0x0001)&&(es_modbus_rtu_data_count<=0x007B)){             //��������ݸ����÷���Ҫ��
        if(((u32)es_modbus_rtu_address+(u32)es_modbus_rtu_data_count)<65536UL){             //��ַ���ܳ���65536��
            for(i=0;i<es_modbus_rtu_cmd_count;i++){   
                es_modbus_cmd_write_reg(es_modbus_rtu_address+i,es_modbus_rtu_cmd_buf[i]);  //������д��Ĵ�����
            }
            if(es_modbus_rtu_broadcast_en){
                    es_modbus_rtu_crc16(id,&crc);          //����CRC����ͬ��
                    es_modbus_rtu_crc16(0x10,&crc);
                    es_modbus_rtu_crc16((u8)(es_modbus_rtu_address>>8)   ,&crc);
                    es_modbus_rtu_crc16((u8)(es_modbus_rtu_address)      ,&crc);
                    es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count>>8),&crc);
                    es_modbus_rtu_crc16((u8)(es_modbus_rtu_data_count)   ,&crc);
                    uart_char(ECBM_STREAM_UART,id);                    //���͵�ַ��
                    uart_char(ECBM_STREAM_UART,0x10);                  //���͹�����ظ���
                    uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address>>8));//���͵�ַ��
                    uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_address));
                    uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count>>8));//���͸�����
                    uart_char(ECBM_STREAM_UART,(u8)(es_modbus_rtu_data_count));
                    uart_char(ECBM_STREAM_UART,(u8)(crc));           //����CRC��
                    uart_char(ECBM_STREAM_UART,(u8)(crc>>8));
            }   
        }else{
            es_modbus_rtu_fun_err_num=0x02;               //��¼�쳣��02��
            es_modbus_rtu_err_num(0x10,es_modbus_rtu_fun_err_num);//���ʹ����롣
        }
    }else{                                                  //������Ϸ���
        es_modbus_rtu_fun_err_num=0x03;                   //��¼�쳣��03��    
        es_modbus_rtu_err_num(0x10,es_modbus_rtu_fun_err_num);//���ʹ����롣
    }
}
#endif
/*-------------------------------------------------------
modbus_rtu����ִ�к�����
-------------------------------------------------------*/
void es_modbus_rtu_exe(u8 dat){
    switch(es_modbus_rtu_status){
        case ES_MODBUS_RTU_READY:{          //�������ȴ��������ݡ�
            if((dat==es_modbus_rtu_get_id())||(dat==0)){      //����յ���ID�ͱ�����ƥ�䡣
                es_modbus_rtu_status      =ES_MODBUS_RTU_FUN_NUM;//�л���������ʶ��
                es_modbus_rtu_broadcast_en=dat;     //д��ͨ��ģʽ��Ϊ�˼򻯴��룬����ֱ�Ӹ�ֵ��
                es_modbus_rtu_fun_code    =0;       //���㹦���뻺�档
                es_modbus_rtu_fun_err_num =0;       //�����쳣�뻺�档
                es_modbus_rtu_uart_crc    =0xffff;  //����CRC��ֵ��
                es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//����CRC��
            }
        }break;
        case ES_MODBUS_RTU_FUN_NUM:{        //���ڽ��չ����롣
            es_modbus_rtu_fun_code=dat;
            if(es_modbus_rtu_fun_code>127){     //�жϹ������Ƿ�Ϸ���
                es_modbus_rtu_fun_err_num=0x01; //�쳣��01�� 
                es_modbus_rtu_err_num(es_modbus_rtu_fun_code,es_modbus_rtu_fun_err_num);//���ʹ����롣
                es_modbus_rtu_status=ES_MODBUS_RTU_READY;
            }else{                              //����Ϸ���
                switch(es_modbus_rtu_fun_code){ //�ж��ǲ��Ǳ���֧�ֵĹ����롣
                    #if ES_MODBUS_RTU_CMD01_EN
                        case 0x01://����Ȧ
                    #endif
                    #if ES_MODBUS_RTU_CMD02_EN
                        case 0x02://����ɢ������
                    #endif
                    #if ES_MODBUS_RTU_CMD05_EN
                        case 0x05://д������Ȧ
                    #endif
                    #if ES_MODBUS_RTU_CMD04_EN
                        case 0x04://������Ĵ���
                    #endif
                    #if ES_MODBUS_RTU_CMD03_EN
                        case 0x03://������Ĵ���
                    #endif
                    #if ES_MODBUS_RTU_CMD06_EN
                        case 0x06://д�����Ĵ���
                    #endif
                    #if ES_MODBUS_RTU_CMD10_EN
                        case 0x10://д����Ĵ���
                    #endif
                    #if ES_MODBUS_RTU_CMD_ALL_EN
                        {
                            es_modbus_rtu_status=ES_MODBUS_RTU_ADDRH;           //����Ǵ��ڵĹ����룬�Ϳ��ǿ�ʼ���������ˡ�
                            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);
                        }break;//֧�ֵĹ�����ͷ��ر�����
                    #endif
                    default:{
                        es_modbus_rtu_fun_err_num=0x01;                       //�쳣��01��
                        es_modbus_rtu_err_num(es_modbus_rtu_fun_code,es_modbus_rtu_fun_err_num);//���ʹ����롣
                        es_modbus_rtu_status=ES_MODBUS_RTU_READY;
                    }break;//��֧�ֵĹ�����ͷ���0x80+�����롣
                }
            }
        }break;
        case ES_MODBUS_RTU_ADDRH:{                        //���յ�ַ�ĸ�8λ��
            es_modbus_rtu_address=(u16)dat<<8;            //��װ��ַ��
            es_modbus_rtu_status=ES_MODBUS_RTU_ADDRL;   //����һ����
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);
        }break;
        case ES_MODBUS_RTU_ADDRL:{                        //���յ�ַ�ĵ�8λ��
            es_modbus_rtu_address+=(u16)dat;              //��װ��ַ��
            es_modbus_rtu_status=ES_MODBUS_RTU_DATA_COUNTH;//����һ����
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//����CRC��
        }break;
        case ES_MODBUS_RTU_DATA_COUNTH:{                  //��������/�����ĸ�8λ��
            es_modbus_rtu_data_count=(u16)dat<<8;         //��װ����/������
            es_modbus_rtu_status=ES_MODBUS_RTU_DATA_COUNTL;//����һ����
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//����CRC��
        }break;
        case ES_MODBUS_RTU_DATA_COUNTL:{                  //��������/�����ĵ�8λ��
            es_modbus_rtu_data_count+=(u16)dat;           //��װ����/������
            if(es_modbus_rtu_fun_code==0x10){
                es_modbus_rtu_cmd_count=0;
                es_modbus_rtu_status=ES_MODBUS_RTU_BYTE_COUNT;//���ֽڶ�ȡ��
            }else{
                es_modbus_rtu_status=ES_MODBUS_RTU_CRCL;//��CRC��
            }
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//����CRC��
        }break;
        case ES_MODBUS_RTU_CRCL:{                         //����CRC�ĵ�8λ��
            es_modbus_rtu_crc_buf=(u16)dat;               //���CRC��
            es_modbus_rtu_status=ES_MODBUS_RTU_CRCH;    //����һ����
        }break;
        case ES_MODBUS_RTU_CRCH:{                         //����CRC�ĸ�8λ��
            es_modbus_rtu_crc_buf+=(u16)dat<<8;           //���CRC��
            if(es_modbus_rtu_crc_buf==es_modbus_rtu_uart_crc){//�жϽ��յ�CRC�ͼ����CRC�Ƿ���ȡ�
                #if ES_MODBUS_RTU_CMD_ALL_EN
                    switch(es_modbus_rtu_fun_code){//���ݹ�������ѡ���Ӧ�Ķ�����
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
            }else{                                          //����
                #if ES_MODBUS_RTU_CRC_ERR_EN
                es_modbus_rtu_crc_err_callback();//������CRC������档
                #endif
                es_modbus_rtu_status=ES_MODBUS_RTU_READY;
            }
        }break;
        #if ES_MODBUS_RTU_CMD10_EN
        case ES_MODBUS_RTU_BYTE_COUNT:{                   //���������ֽ�����
            es_modbus_rtu_cmd_count=dat;
            if((es_modbus_rtu_cmd_count==0)||(es_modbus_rtu_cmd_count!=(u8)(es_modbus_rtu_data_count*2))){//����������ϡ�
                es_modbus_rtu_fun_err_num=0x03;           //�ֽ����Բ��ϣ��쳣��03��
                es_modbus_rtu_err_num(es_modbus_rtu_fun_code,es_modbus_rtu_fun_err_num);//���ʹ����롣
                es_modbus_rtu_status=ES_MODBUS_RTU_READY;
            }else{
                es_modbus_rtu_cmd_count=0;                    //���øñ�����
                es_modbus_rtu_status=ES_MODBUS_RTU_DATAH;//������Ӧ�Ĵ������档
                es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//����CRC��
            }
        }break;
        case ES_MODBUS_RTU_DATAH:{
            es_modbus_rtu_cmd_buf[es_modbus_rtu_cmd_count]=((u16)dat)<<8;
            es_modbus_rtu_status=ES_MODBUS_RTU_DATAL;   //����8λ��
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//����CRC��
        }break;
        case ES_MODBUS_RTU_DATAL:{
            es_modbus_rtu_cmd_buf[es_modbus_rtu_cmd_count]+=((u16)dat);
            es_modbus_rtu_cmd_count++;
            if(es_modbus_rtu_cmd_count==(u8)es_modbus_rtu_data_count){
                es_modbus_rtu_status=ES_MODBUS_RTU_CRCL;//��CRC��
            }else{
                es_modbus_rtu_status=ES_MODBUS_RTU_DATAH;//����һ�����ݵĸ�8λ��
            }
            es_modbus_rtu_crc16(dat,&es_modbus_rtu_uart_crc);//����CRC��
        }break;
        #endif
    }
}
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��