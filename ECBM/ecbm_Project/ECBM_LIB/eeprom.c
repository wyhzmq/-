#include "ecbm_core.h"//ͳһ���غ���ͷ�ļ�
#if ECBM_EEPROM_LIB_EN//��鱾����û�б�ʹ��
/*---------------------------------------�궨��------------------------------------*/
#if     ECBM_SYSCLK_SETTING == 5529600UL//����ϵͳʱ����ѡ��ϵ����
    #define ECBM_EEPROM_WAIT_TIME   4
#elif   ECBM_SYSCLK_SETTING == 6000000UL
    #define ECBM_EEPROM_WAIT_TIME   4
#elif   ECBM_SYSCLK_SETTING == 11059200UL
    #define ECBM_EEPROM_WAIT_TIME   3
#elif   ECBM_SYSCLK_SETTING == 12000000UL
    #define ECBM_EEPROM_WAIT_TIME   3
#elif   ECBM_SYSCLK_SETTING == 18432000UL
    #define ECBM_EEPROM_WAIT_TIME   2
#elif   ECBM_SYSCLK_SETTING == 20000000UL
    #define ECBM_EEPROM_WAIT_TIME   2
#elif   ECBM_SYSCLK_SETTING == 22118400UL
    #define ECBM_EEPROM_WAIT_TIME   2
#elif   ECBM_SYSCLK_SETTING == 24000000UL
    #define ECBM_EEPROM_WAIT_TIME   1
#elif   ECBM_SYSCLK_SETTING == 27000000UL
    #define ECBM_EEPROM_WAIT_TIME   1
#elif   ECBM_SYSCLK_SETTING == 30000000UL
    #define ECBM_EEPROM_WAIT_TIME   0
#elif   ECBM_SYSCLK_SETTING == 33000000UL
    #define ECBM_EEPROM_WAIT_TIME   0
#elif   ECBM_SYSCLK_SETTING == 33177600UL
    #define ECBM_EEPROM_WAIT_TIME   0
#elif   ECBM_SYSCLK_SETTING == 35000000UL
    #define ECBM_EEPROM_WAIT_TIME   0
#elif   ECBM_SYSCLK_SETTING == 36864000UL
    #define ECBM_EEPROM_WAIT_TIME   0
#elif   ECBM_SYSCLK_SETTING == 40000000UL
    #define ECBM_EEPROM_WAIT_TIME   0
#elif   ECBM_SYSCLK_SETTING == 44236800UL
    #define ECBM_EEPROM_WAIT_TIME   0
#elif   ECBM_SYSCLK_SETTING == 45000000UL
    #define ECBM_EEPROM_WAIT_TIME   0
#endif
/*--------------------------------------������-----------------------------------*/
/*-------------------------------------------------------
eeprom�رպ�����
-------------------------------------------------------*/
void eeprom_off(void){
    IAP_SET_REG_CONTR(0);       //�ر�IAP����
    IAP_CMD_NOP;                //�������Ĵ���
    IAP_TRIG_CLS;               //��������Ĵ���
    IAP_SET_REG_ADDR_H8(0xff);  //����ַ���õ���IAP����
    IAP_SET_REG_ADDR_L8(0xff);  //����ַ���õ���IAP����
}
/*-------------------------------------------------------
eeprom��ʼ��������
-------------------------------------------------------*/
void eeprom_init(void){
#if  (((ECBM_MCU&0xF00000) > 0x200000)||(ECBM_MCU == 0x2815C4))
    IAP_TPS=ECBM_SYSCLK_SETTING/1000000;
#endif
    eeprom_off();
}
/*-------------------------------------------------------
eeprom����������
-------------------------------------------------------*/
void eeprom_erase(u16 addr){
    IAP_SET_REG_CONTR(ECBM_EEPROM_WAIT_TIME|IAP_EN);//ʹ��IAP
    IAP_CMD_ERASE;              //����IAP��������
    IAP_SET_REG_ADDR_HL(addr);  //����IAP��ַ
    IAP_TRIG_ON;                //��������
    _nop_();                    //���Եȴ�һ��
    eeprom_off();               //�ر�IAP����
}
/*-------------------------------------------------------
eepromд������
-------------------------------------------------------*/
void eeprom_write(u16 addr,u8 dat){
    IAP_SET_REG_CONTR(ECBM_EEPROM_WAIT_TIME|IAP_EN);//ʹ��IAP
    IAP_CMD_WRITE;              //����IAPд����
    IAP_SET_REG_ADDR_HL(addr);  //����IAP��ַ
    IAP_SET_REG_DATA(dat);      //дIAP����
    IAP_TRIG_ON;                //��������
    _nop_();                    //���Եȴ�һ��
    eeprom_off();               //�ر�IAP����
}
/*-------------------------------------------------------
eeprom��������
-------------------------------------------------------*/
u8 eeprom_read(u16 addr){
    u8 dat;
    IAP_SET_REG_CONTR(ECBM_EEPROM_WAIT_TIME|IAP_EN);  //ʹ��IAP
    IAP_CMD_READ;                           //����IAP������
    IAP_SET_REG_ADDR_HL(addr);              //����IAP��ַ
    IAP_TRIG_ON;                            //��������
    _nop_();                                //���Եȴ�һ��
    dat=IAP_GET_REG_DATA;                   //��IAP����
    eeprom_off();                           //�ر�IAP����
    return dat;
}
#if ECBM_EEPROM_EX_EN
/*-------------------------------------------------------
eeprom�����������(extension)��
-------------------------------------------------------*/
void eeprom_read_ex(u16 addr,u8 * dat,u16 num){
    u16 i;
    for(i=0;i<num;i++){
        dat[i]=eeprom_read(addr+i);
    }
}
/*-------------------------------------------------------
eepromд���������(extension)��
-------------------------------------------------------*/
u8 xdata eeprom_buf[512];//�����������ݵĻ���
void eeprom_write_ex(u16 addr,u8 * dat,u16 num){
    u16 num_yu;         //ʣ��Ҫд�����ݵ�������
    u16 area;           //����������
    u16 area_addr_yu;   //�������µĵ�ַ������
    u16 area_start_addr;//������ʼ��ַ��
    u16 area_stop_addr; //����������ַ��
    u16 addr_offset;    //��ַƫ�ơ�
    u16 dat_offset=0;   //����ƫ�ơ�
    u16 address;        //������ַ��
    u16 i;              //��ʱ������
    address=addr;       //����ַ������ֵ��������ַ��
    num_yu=num;         //������������ֵΪʣ��������
    do{
        area=address>>9;                    //��ȡ������
        area_start_addr=(area<<9);          //��ȡ������ʼ�ĵ�ַ��
        area_stop_addr=(area<<9)+512;       //��ȡ����ĩβ�ĵ�ַ��
        area_addr_yu=area_stop_addr-address;//ĩβ��ַ��������ַ���õ���ַʣ��������
        if(num_yu<=area_addr_yu){           //���Ҫд�������ڵ�ַʣ��������˵�����ÿ�������
            for(i=0;i<512;i++){             //��ԭ�������ݶ�������
                eeprom_buf[i]=eeprom_read(area_start_addr+i);
            }
            eeprom_erase(area_start_addr);      //���������
            addr_offset=address-area_start_addr;//��ȡ��ַƫ�ơ�
            for(i=0;i<num_yu;i++){              //�޸����ݡ�
                eeprom_buf[addr_offset+i]=dat[dat_offset+i];
            }
            for(i=0;i<512;i++){                 //������д��ȥ��
                eeprom_write(area_start_addr+i,eeprom_buf[i]);
            }
            break;                              //д�������ѭ����
        }else{                                  //���Ҫд�������ڵ�ַʣ������
            for(i=0;i<512;i++){                 //��ԭ�������ݶ�������
                eeprom_buf[i]=eeprom_read(area_start_addr+i);
            }
            eeprom_erase(area_start_addr);      //���������
            addr_offset=address-area_start_addr;//��ȡ��ַƫ�ơ�
            for(i=0;i<area_addr_yu;i++){        //�޸����ݡ�
                eeprom_buf[addr_offset+i]=dat[dat_offset+i];
            }
            for(i=0;i<512;i++){                 //������д��ȥ��
                eeprom_write(area_start_addr+i,eeprom_buf[i]);
            }
            address+=area_addr_yu;              //д�˶��٣���ַ�ͼӶ��١�
            num_yu -=area_addr_yu;              //ʣ��������Ҫ�����١�
            dat_offset+=area_addr_yu;           //�����ƫ�ƾͼӶ��١�
        }
    }while(1);
}
#endif
#if ECBM_EEPROM_EDS_EN
/*-------------------------------------------------------
eds��麯����
-------------------------------------------------------*/
u8 eds_check(u16 addr){
    u8 dat,_dat;
    dat=eeprom_read(addr+0);//������һ���ֽڵ���Ϣ��
    if(dat!='E')return  EDS_ERR_NULL;//��һ���ֽڲ���E,˵������EDS��
    dat=eeprom_read(addr+1);//��һ���ֽ���ȷ�Ļ��������ڶ����ֽڵ���Ϣ��
    if(dat!='D')return  EDS_ERR_NULL;//���ǲ���D,����D˵������EDS��
    dat=eeprom_read(addr+2);//�ڶ����ֽ���ȷ�Ļ��������������ֽڵ���Ϣ��
    if(dat!='S')return  EDS_ERR_NULL;//���ǲ���S,����S˵������EDS��
    dat =eeprom_read(addr+3);//����ID��
    _dat=eeprom_read(addr+4);//����ID���롣
    if((dat==(~_dat))&&(dat==(u8)(addr/512))){//ID��ʽҲ��ȷ�Ļ��������һ���ϸ��EDS��
        return EDS_OK;      //����OK��
    }
    return EDS_ERR_ID;      //�ߵ����˵��������ID��֤��ͨ��������ID����
}
/*-------------------------------------------------------
eds����������
-------------------------------------------------------*/
void eds_erase(u8 sector_start,u8 sector_szie){
    u8 i;
    for(i=0;i<sector_szie;i++){ //��ʼ����ʱ�򣬾�Ҫ�����õ��������ˡ�
        eeprom_erase((u16)(sector_start+i)*512);//�����ַ���������õ�ַ��
    }
}
/*-------------------------------------------------------
eds��ʼ��������
-------------------------------------------------------*/
u8 eds_init(u8 sector_start,u8 sector_szie,u16 pack_len){
    u16 addr;
    u8 id;
    if(sector_start>128)return EDS_ERR_SECTOR; //����������Ҫ����128������ַ������128*512=65536��
    if(sector_szie >128)return EDS_ERR_SECTOR; //����������Ҫ����128��������������128*512=65536��
    if(sector_szie ==0 )return EDS_ERR_SECTOR; //��������Ҳ������0��
    addr=sector_start*512;      //��ȡ��ʼ��ַ��
    if(eds_check(addr)!=EDS_OK){//���õ�ַ�Ƿ���EDS��
        eds_erase(sector_start,sector_szie);//û�оͲ�����
        eeprom_write(addr+0,'E');   //д���ʶ����
        eeprom_write(addr+1,'D');
        eeprom_write(addr+2,'S');
        eeprom_write(addr+3, id);   //д�����ID��
        eeprom_write(addr+4,~id);   //д��ID�ķ��롣
        eeprom_write(addr+5,sector_szie);//д�����������������
        eeprom_write(addr+6,(u8)(pack_len>>8));//д����ĳ��ȡ�
        eeprom_write(addr+7,(u8)(pack_len   ));
        return EDS_DATA_VOID;       //������֮�󣬴�ʱEDS�������ݡ�
    }
    return EDS_OK;
}
/*-------------------------------------------------------
edsд������
-------------------------------------------------------*/
u8 eds_write(u8 sector_start,u8 * buf){
    u16 start_addr,limit_addr,data_len,count,write_addr;
    u8  read_buf[8],res,i;
    start_addr=(u16)(sector_start)*512; //�������ʼ��ַ��
    res=eds_check(start_addr);          //���EDS��
    if(res!=EDS_OK){                    //�����������
        return res;                     //���ش����롣
    }                                   //�����������ߡ�
    for(i=0;i<8;i++){                   //Ҫ����Ϣ��������
        read_buf[i]=eeprom_read(start_addr+(u16)(i));
    }
    limit_addr=start_addr+(u16)(read_buf[5])*512;//�ϳ����Ƶ�ַ��
    data_len=(u16)(read_buf[6])*256+(u16)(read_buf[7]);//�ϳɰ����ȡ�
    count=0;//ͳ��ֵ���㡣
    for(i=8;i<64;i++){//������������ݡ�
        res=eeprom_read(start_addr+(u16)(i));//��һ���ֽڡ�
        //breakֻ���ж�һ����䣬���Բ�����switch��
        if(res==0xFF){count+=0;eeprom_write(start_addr+(u16)(i),0x7F);break;}
        if(res==0x7F){count+=1;eeprom_write(start_addr+(u16)(i),0x3F);break;}
        if(res==0x3F){count+=2;eeprom_write(start_addr+(u16)(i),0x1F);break;}
        if(res==0x1F){count+=3;eeprom_write(start_addr+(u16)(i),0x0F);break;}
        if(res==0x0F){count+=4;eeprom_write(start_addr+(u16)(i),0x07);break;}
        if(res==0x07){count+=5;eeprom_write(start_addr+(u16)(i),0x03);break;}
        if(res==0x03){count+=6;eeprom_write(start_addr+(u16)(i),0x01);break;}
        if(res==0x01){count+=7;eeprom_write(start_addr+(u16)(i),0x00);break;}
        if(res==0x00){count+=8;}
    }
    write_addr=start_addr+64+count*data_len;//ƴ�ӳ�д���ַ��
    if((write_addr>=limit_addr)||((limit_addr-write_addr)<data_len)){  
    //���д���ַ���������ˣ�����ʣ��Ŀռ䲻��д��
        eds_erase(read_buf[3],read_buf[5]); //���Ƭ����
        for(i=0;i<8;i++){                   //��ԭ��Ϣ����
            eeprom_write(start_addr+i,read_buf[i]);
        }
        eeprom_write(start_addr+8,0x7F);    //���ϵ�һ�����ݵı�ǡ�
        write_addr=start_addr+64;           //����д���ַ��
    }
    for(count=0;count<data_len;count++){    //д�����ݡ�
        eeprom_write(write_addr+count,buf[count]);
    }
    return EDS_OK;  //д��ɹ���
}
/*-------------------------------------------------------
eds��������
-------------------------------------------------------*/
u8 eds_read(u8 sector_start,u8 * buf){
    u16 start_addr,limit_addr,data_len,count,read_addr;
    u8  read_buf[8],res,i;
    start_addr=(u16)(sector_start)*512; //�������ʼ��ַ��
    res=eds_check(start_addr);          //���EDS��
    if(res!=EDS_OK){                    //�����������
        return res;                     //���ش����롣
    }                                   //�����������ߡ�
    for(i=0;i<8;i++){                   //Ҫ����Ϣ��������
        read_buf[i]=eeprom_read(start_addr+(u16)(i));
    }
    limit_addr=start_addr+(u16)(read_buf[5])*512;//�ϳ����Ƶ�ַ��
    data_len=(u16)(read_buf[6])*256+(u16)(read_buf[7]);//�ϳɰ����ȡ�
    count=0;//ͳ��ֵ���㡣
    for(i=8;i<64;i++){//������������ݡ�
        res=eeprom_read(start_addr+(u16)(i));//��һ���ֽڡ�
        //breakֻ���ж�һ����䣬���Բ�����switch��
        if(res==0xFF){count+=0;break;}
        if(res==0x7F){count+=1;break;}
        if(res==0x3F){count+=2;break;}
        if(res==0x1F){count+=3;break;}
        if(res==0x0F){count+=4;break;}
        if(res==0x07){count+=5;break;}
        if(res==0x03){count+=6;break;}
        if(res==0x01){count+=7;break;}
        if(res==0x00){count+=8;}
    }
    if(count==0)return EDS_DATA_VOID;//�����������ѭ��֮�����ͳ��ֵ����0����˵��û�����ݡ�
    read_addr=start_addr+64+(count-1)*data_len;//ƴ�ӳ���ȡ��ַ��
    for(count=0;count<data_len;count++){//�������ݡ�
        buf[count]=eeprom_read(read_addr+count);
    }
    return EDS_OK;  //��ȡ�ɹ���
}
#endif 
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��