#include "stream_ecp.h"//����ͷ�ļ�
#if (ECBM_STREAM_EN)&&(ECBM_STREAM_ECP_EN)//��鱾����û�б�ʹ��
/*--------------------------------------��������-----------------------------------*/
u8  es_ecp_status   =0; //״̬��������
u8  es_ecp_data_len =0; //���ڴ�Ų��������ݵĳ��ȡ�
u8  es_ecp_count    =0; //����ͳ��ʵ�ʽ��յĲ��������ݳ��ȡ�
u8  es_ecp_source_id=0; //ԴͷID�������֡�����ID������������
u8  es_ecp_target_id=0; //Ŀ��ID�������֡Ӧ�������ID���������ա�
u8  es_ecp_operation=0; //�����뻺�档
u16 es_ecp_addr16_ex=0; //16λ��չ��ַ���档
u16 es_ecp_addr16   =0; //16λ��ַ���档
u16 es_ecp_crc      =0; //���ڼ���������ݵ�CRC��
u16 es_ecp_crc_buf  =0; //���ڴ������֡���CRC��
u8  es_ecp_data_buf[ES_ECP_DATA_BUF_MAX];//���ڶ�д�����Ļ��档
/*--------------------------------------������-----------------------------------*/
/*-------------------------------------------------------
CRCУ�麯����
-------------------------------------------------------*/
u16 es_ecp_crc16(u16 crc,u8 buf){
    u8 j;
    u16 crc_buf;
    crc_buf=crc^buf;                    //��ǰ�������CRC���ֽڣ���C51�����ֱ�Ӵ���
    for(j=0;j<8;j++){                   //����ÿ���ֽڵ�ÿһλ��
        if(crc_buf&0x01){               //�ж�����ǰ���λ�Ƿ�Ϊ1��
            crc_buf=(crc_buf>>1)^0xA001;//���Ϊ1�����Ʋ������ʽ��
        }else{
            crc_buf>>=1;                //����ֱ������һλ��
        }           
    }
    return crc_buf;
}
/*-------------------------------------------------------
ͨ�ûظ�������
-------------------------------------------------------*/
void es_ecp_cmd_back(u8 cmd){
    u16 crc;
    if(es_ecp_source_id){//����Է��ǹ㲥���Ͳ�Ҫ�ظ��ˡ�
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
    
        ecbm_stream_out(0xEC);//֡ͷ��
        ecbm_stream_out(0x00);//���ȡ�
        ecbm_stream_out(0xFF);//���ȷ��롣
        ecbm_stream_out(es_ecp_source_id);//˭�������ģ�������˭��
        ecbm_stream_out(es_ecp_get_id()); //���ϱ�����ID��
        ecbm_stream_out(cmd);  //��ִ��
        ecbm_stream_out((u8)(es_ecp_addr16_ex>>8));//��ַ��λ��
        ecbm_stream_out((u8)(es_ecp_addr16_ex   ));//��ַ��λ��
        ecbm_stream_out((u8)(es_ecp_addr16>>8));//��ַ��λ��
        ecbm_stream_out((u8)(es_ecp_addr16   ));//��ַ��λ��
        ecbm_stream_out((u8)(crc>>8)); 
        ecbm_stream_out((u8)(crc));
        ecbm_stream_out(0xBE);  //֡β��
    }
}
/*-------------------------------------------------------
02ָ�������
-------------------------------------------------------*/
void es_ecp_cmd02(void){
    u8 count,arg_len;
    u16 crc;
    arg_len=es_ecp_data_buf[0];
    es_ecp_read(es_ecp_addr16,es_ecp_data_buf,arg_len);
    if(es_ecp_source_id){//����Է��ǹ㲥���Ͳ�Ҫ�ظ��ˡ�
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

        ecbm_stream_out(0xEC);  //֡ͷ��
        ecbm_stream_out( arg_len); //���ȡ�
        ecbm_stream_out(~arg_len);//���ȷ��롣
        ecbm_stream_out(es_ecp_source_id);//˭�������ģ�������˭��
        ecbm_stream_out(es_ecp_get_id()); //���ϱ�����ID��
        ecbm_stream_out(0x03);  //��ִ��
        ecbm_stream_out((u8)(es_ecp_addr16_ex>>8));//��ַ��λ��
        ecbm_stream_out((u8)(es_ecp_addr16_ex   ));//��ַ��λ��
        ecbm_stream_out((u8)(es_ecp_addr16>>8));//��ַ��λ��
        ecbm_stream_out((u8)(es_ecp_addr16   ));//��ַ��λ��
        for(count=0;count<arg_len;count++){
            ecbm_stream_out(es_ecp_data_buf[count]);//�������ݡ�
        }
        ecbm_stream_out((u8)(crc>>8)); 
        ecbm_stream_out((u8)(crc));
        ecbm_stream_out(0xBE);  //֡β��
    }
}
/*-------------------------------------------------------
04ָ�������
-------------------------------------------------------*/
void es_ecp_cmd04(void){
    es_ecp_write(es_ecp_addr16,es_ecp_data_buf,es_ecp_data_len);
    es_ecp_cmd_back(0x05);
}
/*-------------------------------------------------------
06ָ�������
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
08ָ�������
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
ECP����д������
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
    ecbm_stream_out(0xEC);  //֡ͷ��
    ecbm_stream_out( len); //���ȡ�
    ecbm_stream_out(~len);//���ȷ��롣
    ecbm_stream_out(id);//
    ecbm_stream_out(es_ecp_get_id()); //���ϱ�����ID��
    ecbm_stream_out(0x04);  //
    ecbm_stream_out(0x00);//��ַ��λ��
    ecbm_stream_out(0x00);//��ַ��λ��
    ecbm_stream_out((u8)(addr>>8));//��ַ��λ��
    ecbm_stream_out((u8)(addr   ));//��ַ��λ��
    for(count=0;count<len;count++){
        ecbm_stream_out(buf[count]);//�������ݡ�
    }
    ecbm_stream_out((u8)(crc>>8)); 
    ecbm_stream_out((u8)(crc));
    ecbm_stream_out(0xBE);  //֡β��
}
#endif
/*-------------------------------------------------------
ECP������������
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
    
    ecbm_stream_out(0xEC);  //֡ͷ��
    ecbm_stream_out(0x01); //���ȡ�
    ecbm_stream_out(0xFE);//���ȷ��롣
    ecbm_stream_out(id);//
    ecbm_stream_out(es_ecp_get_id()); //���ϱ�����ID��
    ecbm_stream_out(0x02);  //
    ecbm_stream_out(0x00);//��ַ��λ��
    ecbm_stream_out(0x00);//��ַ��λ��
    ecbm_stream_out((u8)(addr>>8));//��ַ��λ��
    ecbm_stream_out((u8)(addr   ));//��ַ��λ��
    ecbm_stream_out(len);//�������ݡ�
    ecbm_stream_out((u8)(crc>>8)); 
    ecbm_stream_out((u8)(crc));
    ecbm_stream_out(0xBE);  //֡β��
}
#endif
/*-------------------------------------------------------
ECP����ִ�к�����
-------------------------------------------------------*/
void es_ecp_exe(u8 dat){
    switch(es_ecp_status){
        case ES_ECP_READY:{                             //׼��״̬��
            if(dat==0xEC){                              //��ȡ��֡ͷ��ʱ��
                es_ecp_status=ES_ECP_GET_DATA_LEN;      //ȥ��ȡ����֡���ȡ�
                es_ecp_crc=es_ecp_crc16(0xffff,0xEC);   //����CRC������֡ͷ��CRC��
            }
        }break;
        case ES_ECP_GET_DATA_LEN:{                  //��ȡ����֡����״̬��
            es_ecp_data_len=dat;                    //��ȡ����֡���ȡ�
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//��������֡���ȵ�CRC��
            es_ecp_status=ES_ECP_CHECK_DATA_LEN;    //ȥȷ������֡���ȡ�
        }break;
        case ES_ECP_CHECK_DATA_LEN:{                        //ȷ������֡����״̬��
            if(es_ecp_data_len==(~dat)){                    //�ŷ������;֮һ���ǿ���������ǿʶ��֡ͷ��
                es_ecp_status=ES_ECP_GET_TARGET_ID;         //ȷ����ȷ֮��ȥ��ȡĿ��ID��
                es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);    //��������֡���ȷ����CRC��
            }else{                                          //������ǳ��ȵķ��룬˵���ⲻ��һ���Ϸ���֡ͷ��
                if(es_ecp_data_len==0xEC){                  //����һ�£��ǲ���һ������0xEC�����ˡ�
                    es_ecp_status=ES_ECP_CHECK_DATA_LEN;    //�ǵĻ������ֽھ�Ӧ��������֡�����ˣ���ô��һ�����ǵ�ȷ������֡����״̬��
                    es_ecp_data_len=dat;                    //������֡���ȴ�á�
                    es_ecp_crc=es_ecp_crc16(0xffff,0xEC);   //����CRC������֡ͷ��CRC��
                    es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//��������֡���ȵ�CRC��
                }else{                                      //���ǵĻ����Ǿ��ٿ����ǲ����⼸���жϵ�ʱ������0xEC�źš�
                    if(dat==0xEC){                          //���һ���ж�֡ͷ�ˡ�
                        es_ecp_status=ES_ECP_GET_DATA_LEN;  //�ǵĻ�����Ҫ���¶�ȡһ������֡���ȡ�
                        es_ecp_crc=es_ecp_crc16(0xffff,0xEC);//����CRC������֡ͷ��CRC��
                    }else{                                  //�����ﻹ���ǵĻ���˵�����յ�����ȫ�Ǹ��š�
                        es_ecp_status=ES_ECP_READY;         //�ص�׼��״̬��
                    }//ע�����
                }   //֮����������Ҫ�ж���ô�࣬����Ϊ�ڴ����������ͨ������Ҳ�����0xEC�ģ�����˵��һ����0xEC����Ϊ��֡ͷ��Ҫ���ų��Ⱥͳ��ȷ����ۺ��жϡ�
            }       //��Ȼ��ţ�Ǽ���ԣ���ͨ���ݳ��ֺϷ�֡ͷ��0xEC�����ȣ����ȷ��룩�ĸ���Ҳ����0�����ж�3���ֽ����еĸ�����ԶԶ����ֻ�ж�1���ֽڵġ�
        }break;
        case ES_ECP_GET_TARGET_ID:{                 //��ȡĿ��ID״̬��
            es_ecp_target_id=dat;                   //��ȡĿ��ID��
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//����Ŀ��ID��CRC��
            es_ecp_status=ES_ECP_GET_SOURCE_ID;     //ȥ��ȡ���ͷ�ID��
        }break;
        case ES_ECP_GET_SOURCE_ID:{                 //��ȡ���ͷ�ID״̬��
            es_ecp_source_id=dat;                   //��ȡ���ͷ�ID��
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//���㷢�ͷ�ID��CRC��
            es_ecp_status=ES_ECP_GET_OPERATION;     //ȥ��ȡ�����롣
        }break;
        case ES_ECP_GET_OPERATION:{                 //��ȡ������״̬��
            es_ecp_operation=dat;                   //��������롣
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//����������CRC��
            es_ecp_status=ES_ECP_GET_ADDR_31_24;    //ȥ��ȡ��ַ��
        }break;
        case ES_ECP_GET_ADDR_31_24:{                //��ȡ��ַ31~24λ״̬��
            es_ecp_addr16_ex=(u16)dat;              //�����ַ��λ��
            es_ecp_status=ES_ECP_GET_ADDR_23_16;    //�����ַ�Ǹ�32λ��Ƭ����Ԥ����51��Ƭ��������ĺ��塣
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,0x00);//Ԥ����ҲҪ����0x00��CRC��
        }break;
        case ES_ECP_GET_ADDR_23_16:{                //��ȡ��ַ23~16λ״̬��
            es_ecp_addr16_ex<<=8;                   //����һ�εĵ�ַ��
            es_ecp_addr16_ex+=(u16)dat;             //����һ�εĵ�ַ�ϲ���һ��
            es_ecp_status=ES_ECP_GET_ADDR_15_8;     //�����ַ�Ǹ�32λ��Ƭ����Ԥ����51��Ƭ��������ĺ��塣
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,0x00);//Ԥ����ҲҪ����0x00��CRC��
        }break;
        case ES_ECP_GET_ADDR_15_8:{                 //��ȡ��ַ15~8λ״̬��
            es_ecp_addr16=(u16)dat;                 //�����ַ��λ��
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//�����ַ��λ��CRC��
            es_ecp_status=ES_ECP_GET_ADDR_7_0;      //ȥ��ȡ��ַ��λ��
        }break;
        case ES_ECP_GET_ADDR_7_0:{                  //��ȡ��ַ7~0λ״̬��
            es_ecp_addr16<<=8;                      //����һ�εĵ�ַ��
            es_ecp_addr16+=(u16)dat;                //����һ�εĵ�ַ�ϲ���һ��
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//�����ַ��λ��CRC��
            if(es_ecp_data_len){                    //������ݳ��ȴ��ڣ�
                es_ecp_status=ES_ECP_GET_DATA;      //�͵���ȡ����״̬��
                es_ecp_count=0;                     //�������ݼ��������� 
            }else{                                  //���ݳ���Ϊ0�Ļ���
                es_ecp_status=ES_ECP_GET_CRC_H;     //��ȥ��ȡCRC��
            }
        }break;
        case ES_ECP_GET_DATA:{                      //��ȡ����������״̬��
            es_ecp_data_buf[es_ecp_count++]=dat;    //�����������ݴ��뻺�棬Ȼ�����+1��
            es_ecp_crc=es_ecp_crc16(es_ecp_crc,dat);//�������ݵ�CRC��
            if(es_ecp_count>=es_ecp_data_len){      //�������ﵽĿ��ʱ��
                es_ecp_status=ES_ECP_GET_CRC_H;     //��ȥ��ȡCRC��
            }
        }break;
        case ES_ECP_GET_CRC_H:{                 //��ȡCRC��λ״̬��
            es_ecp_crc_buf=(u16)dat;            //��װCRC��
            es_ecp_status=ES_ECP_GET_CRC_L;     //����һ����
        }break;
        case ES_ECP_GET_CRC_L:{                 //��ȡCRC��λ״̬��
            es_ecp_crc_buf<<=8;                 //��װCRC��
            es_ecp_crc_buf+=(u16)dat;
            es_ecp_status=ES_ECP_END;           //���ж�֡β�׶��ˡ�
        }break;
        case ES_ECP_END:{                       //�ж�֡β״̬��
            es_ecp_status=ES_ECP_READY;         //�����ǲ���֡β�������Իص�׼��״̬�ˡ�
            if((dat==0xBE)&&(es_ecp_crc_buf==es_ecp_crc)){                    //���Ǽ�⵽�Ϸ���CRC��֡βʱ����ִ��֡�ڶ�����
                if((es_ecp_target_id==es_ecp_get_id())||(es_ecp_target_id==0)){//ȷ�ϱ�֡�����Ƿ��������ģ�������ǹ㲥��
                    switch(es_ecp_operation){//���ݲ�������ִ����Ӧ������
                        case 0x00:es_ecp_cmd_back(0x01);break;//��ѯ��
                        case 0x02:es_ecp_cmd02();break;//��ȡ��
                        case 0x04:es_ecp_cmd04();break;//д�롣
                        case 0x06:es_ecp_cmd06();break;//��λ��
                        case 0x08:es_ecp_cmd08();break;//��λ��
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
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��