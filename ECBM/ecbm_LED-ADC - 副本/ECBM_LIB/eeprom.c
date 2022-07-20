#include "ecbm_core.h"//统一加载核心头文件
#if ECBM_EEPROM_LIB_EN//检查本库有没有被使能
/*---------------------------------------宏定义------------------------------------*/
#if     ECBM_SYSCLK_SETTING == 5529600UL//根据系统时钟来选择系数。
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
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
eeprom关闭函数。
-------------------------------------------------------*/
void eeprom_off(void){
    IAP_SET_REG_CONTR(0);       //关闭IAP功能
    IAP_CMD_NOP;                //清除命令寄存器
    IAP_TRIG_CLS;               //清除触发寄存器
    IAP_SET_REG_ADDR_H8(0xff);  //将地址设置到非IAP区域
    IAP_SET_REG_ADDR_L8(0xff);  //将地址设置到非IAP区域
}
/*-------------------------------------------------------
eeprom初始化函数。
-------------------------------------------------------*/
void eeprom_init(void){
#if  (((ECBM_MCU&0xF00000) > 0x200000)||(ECBM_MCU == 0x2815C4))
    IAP_TPS=ECBM_SYSCLK_SETTING/1000000;
#endif
    eeprom_off();
}
/*-------------------------------------------------------
eeprom擦除函数。
-------------------------------------------------------*/
void eeprom_erase(u16 addr){
    IAP_SET_REG_CONTR(ECBM_EEPROM_WAIT_TIME|IAP_EN);//使能IAP
    IAP_CMD_ERASE;              //设置IAP擦除命令
    IAP_SET_REG_ADDR_HL(addr);  //设置IAP地址
    IAP_TRIG_ON;                //触发命令
    _nop_();                    //稍稍等待一下
    eeprom_off();               //关闭IAP功能
}
/*-------------------------------------------------------
eeprom写函数。
-------------------------------------------------------*/
void eeprom_write(u16 addr,u8 dat){
    IAP_SET_REG_CONTR(ECBM_EEPROM_WAIT_TIME|IAP_EN);//使能IAP
    IAP_CMD_WRITE;              //设置IAP写命令
    IAP_SET_REG_ADDR_HL(addr);  //设置IAP地址
    IAP_SET_REG_DATA(dat);      //写IAP数据
    IAP_TRIG_ON;                //触发命令
    _nop_();                    //稍稍等待一下
    eeprom_off();               //关闭IAP功能
}
/*-------------------------------------------------------
eeprom读函数。
-------------------------------------------------------*/
u8 eeprom_read(u16 addr){
    u8 dat;
    IAP_SET_REG_CONTR(ECBM_EEPROM_WAIT_TIME|IAP_EN);  //使能IAP
    IAP_CMD_READ;                           //设置IAP读命令
    IAP_SET_REG_ADDR_HL(addr);              //设置IAP地址
    IAP_TRIG_ON;                            //触发命令
    _nop_();                                //稍稍等待一下
    dat=IAP_GET_REG_DATA;                   //读IAP数据
    eeprom_off();                           //关闭IAP功能
    return dat;
}
#if ECBM_EEPROM_EX_EN
/*-------------------------------------------------------
eeprom读函数延伸版(extension)。
-------------------------------------------------------*/
void eeprom_read_ex(u16 addr,u8 * dat,u16 num){
    u16 i;
    for(i=0;i<num;i++){
        dat[i]=eeprom_read(addr+i);
    }
}
/*-------------------------------------------------------
eeprom写函数延伸版(extension)。
-------------------------------------------------------*/
u8 xdata eeprom_buf[512];//用于整合数据的缓存
void eeprom_write_ex(u16 addr,u8 * dat,u16 num){
    u16 num_yu;         //剩余要写的数据的数量。
    u16 area;           //操作扇区。
    u16 area_addr_yu;   //扇区余下的地址数量。
    u16 area_start_addr;//扇区开始地址。
    u16 area_stop_addr; //扇区结束地址。
    u16 addr_offset;    //地址偏移。
    u16 dat_offset=0;   //数据偏移。
    u16 address;        //操作地址。
    u16 i;              //临时变量。
    address=addr;       //将地址参数赋值给操作地址。
    num_yu=num;         //将参数数量赋值为剩余数量。
    do{
        area=address>>9;                    //获取扇区。
        area_start_addr=(area<<9);          //获取扇区开始的地址。
        area_stop_addr=(area<<9)+512;       //获取扇区末尾的地址。
        area_addr_yu=area_stop_addr-address;//末尾地址减操作地址，得到地址剩余数量。
        if(num_yu<=area_addr_yu){           //如果要写的数少于地址剩余数量，说明不用跨扇区。
            for(i=0;i<512;i++){             //将原来的数据读出来。
                eeprom_buf[i]=eeprom_read(area_start_addr+i);
            }
            eeprom_erase(area_start_addr);      //清空扇区。
            addr_offset=address-area_start_addr;//获取地址偏移。
            for(i=0;i<num_yu;i++){              //修改数据。
                eeprom_buf[addr_offset+i]=dat[dat_offset+i];
            }
            for(i=0;i<512;i++){                 //将数据写回去。
                eeprom_write(area_start_addr+i,eeprom_buf[i]);
            }
            break;                              //写完就跳出循环。
        }else{                                  //如果要写的数多于地址剩余量。
            for(i=0;i<512;i++){                 //将原来的数据读出来。
                eeprom_buf[i]=eeprom_read(area_start_addr+i);
            }
            eeprom_erase(area_start_addr);      //清空扇区。
            addr_offset=address-area_start_addr;//获取地址偏移。
            for(i=0;i<area_addr_yu;i++){        //修改数据。
                eeprom_buf[addr_offset+i]=dat[dat_offset+i];
            }
            for(i=0;i<512;i++){                 //将数据写回去。
                eeprom_write(area_start_addr+i,eeprom_buf[i]);
            }
            address+=area_addr_yu;              //写了多少，地址就加多少。
            num_yu -=area_addr_yu;              //剩余数量就要减多少。
            dat_offset+=area_addr_yu;           //缓存的偏移就加多少。
        }
    }while(1);
}
#endif
#if ECBM_EEPROM_EDS_EN
/*-------------------------------------------------------
eds检查函数。
-------------------------------------------------------*/
u8 eds_check(u16 addr){
    u8 dat,_dat;
    dat=eeprom_read(addr+0);//读出第一个字节的信息，
    if(dat!='E')return  EDS_ERR_NULL;//第一个字节不是E,说明不是EDS。
    dat=eeprom_read(addr+1);//第一个字节正确的话，读出第二个字节的信息。
    if(dat!='D')return  EDS_ERR_NULL;//看是不是D,不是D说明不是EDS。
    dat=eeprom_read(addr+2);//第二个字节正确的话，读出第三个字节的信息。
    if(dat!='S')return  EDS_ERR_NULL;//看是不是S,不是S说明不是EDS。
    dat =eeprom_read(addr+3);//读出ID，
    _dat=eeprom_read(addr+4);//还有ID反码。
    if((dat==(~_dat))&&(dat==(u8)(addr/512))){//ID格式也正确的话，这就是一个合格的EDS。
        return EDS_OK;      //返回OK。
    }
    return EDS_ERR_ID;      //走到这里，说明是最后的ID验证不通过，返回ID错误。
}
/*-------------------------------------------------------
eds擦除函数。
-------------------------------------------------------*/
void eds_erase(u8 sector_start,u8 sector_szie){
    u8 i;
    for(i=0;i<sector_szie;i++){ //初始化的时候，就要擦除用到的扇区了。
        eeprom_erase((u16)(sector_start+i)*512);//计算地址，并擦除该地址。
    }
}
/*-------------------------------------------------------
eds初始化函数。
-------------------------------------------------------*/
u8 eds_init(u8 sector_start,u8 sector_szie,u16 pack_len){
    u16 addr;
    u8 id;
    if(sector_start>128)return EDS_ERR_SECTOR; //限制扇区不要超过128，即地址不超过128*512=65536。
    if(sector_szie >128)return EDS_ERR_SECTOR; //限制数量不要超过128，即总数不超过128*512=65536。
    if(sector_szie ==0 )return EDS_ERR_SECTOR; //扇区数量也不能是0。
    addr=sector_start*512;      //获取开始地址。
    if(eds_check(addr)!=EDS_OK){//检查该地址是否有EDS。
        eds_erase(sector_start,sector_szie);//没有就擦除。
        eeprom_write(addr+0,'E');   //写入标识符。
        eeprom_write(addr+1,'D');
        eeprom_write(addr+2,'S');
        eeprom_write(addr+3, id);   //写入管理ID。
        eeprom_write(addr+4,~id);   //写入ID的反码。
        eeprom_write(addr+5,sector_szie);//写入管理的扇区数量。
        eeprom_write(addr+6,(u8)(pack_len>>8));//写入包的长度。
        eeprom_write(addr+7,(u8)(pack_len   ));
        return EDS_DATA_VOID;       //重置了之后，此时EDS内无数据。
    }
    return EDS_OK;
}
/*-------------------------------------------------------
eds写函数。
-------------------------------------------------------*/
u8 eds_write(u8 sector_start,u8 * buf){
    u16 start_addr,limit_addr,data_len,count,write_addr;
    u8  read_buf[8],res,i;
    start_addr=(u16)(sector_start)*512; //计算出开始地址。
    res=eds_check(start_addr);          //检查EDS。
    if(res!=EDS_OK){                    //如果不正常，
        return res;                     //返回错误码。
    }                                   //正常就往下走。
    for(i=0;i<8;i++){                   //要读信息区出来。
        read_buf[i]=eeprom_read(start_addr+(u16)(i));
    }
    limit_addr=start_addr+(u16)(read_buf[5])*512;//合成限制地址。
    data_len=(u16)(read_buf[6])*256+(u16)(read_buf[7]);//合成包长度。
    count=0;//统计值清零。
    for(i=8;i<64;i++){//读标记区的数据。
        res=eeprom_read(start_addr+(u16)(i));//读一个字节。
        //break只能中断一层语句，所以不能用switch。
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
    write_addr=start_addr+64+count*data_len;//拼接出写入地址。
    if((write_addr>=limit_addr)||((limit_addr-write_addr)<data_len)){  
    //如果写入地址超过限制了，或者剩余的空间不够写。
        eds_erase(read_buf[3],read_buf[5]); //清除片区。
        for(i=0;i<8;i++){                   //还原信息区。
            eeprom_write(start_addr+i,read_buf[i]);
        }
        eeprom_write(start_addr+8,0x7F);    //打上第一个数据的标记。
        write_addr=start_addr+64;           //重置写入地址。
    }
    for(count=0;count<data_len;count++){    //写入数据。
        eeprom_write(write_addr+count,buf[count]);
    }
    return EDS_OK;  //写入成功。
}
/*-------------------------------------------------------
eds读函数。
-------------------------------------------------------*/
u8 eds_read(u8 sector_start,u8 * buf){
    u16 start_addr,limit_addr,data_len,count,read_addr;
    u8  read_buf[8],res,i;
    start_addr=(u16)(sector_start)*512; //计算出开始地址。
    res=eds_check(start_addr);          //检查EDS。
    if(res!=EDS_OK){                    //如果不正常，
        return res;                     //返回错误码。
    }                                   //正常就往下走。
    for(i=0;i<8;i++){                   //要读信息区出来。
        read_buf[i]=eeprom_read(start_addr+(u16)(i));
    }
    limit_addr=start_addr+(u16)(read_buf[5])*512;//合成限制地址。
    data_len=(u16)(read_buf[6])*256+(u16)(read_buf[7]);//合成包长度。
    count=0;//统计值清零。
    for(i=8;i<64;i++){//读标记区的数据。
        res=eeprom_read(start_addr+(u16)(i));//读一个字节。
        //break只能中断一层语句，所以不能用switch。
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
    if(count==0)return EDS_DATA_VOID;//经过了上面的循环之后，如果统计值还是0，就说明没有数据。
    read_addr=start_addr+64+(count-1)*data_len;//拼接出读取地址。
    for(count=0;count<data_len;count++){//读出数据。
        buf[count]=eeprom_read(read_addr+count);
    }
    return EDS_OK;  //读取成功。
}
#endif 
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。