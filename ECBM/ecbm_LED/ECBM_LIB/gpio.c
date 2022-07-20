#include "ecbm_core.h"//ͳһ���غ���ͷ�ļ�
u8 code ecbm_pin_mask[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
u8 data ecbm_port,ecbm_pin;
/*--------------------------------------������-----------------------------------*/
/*�������۵�ר��************************IO����ģ��******************************/#if 1
/*-------------------------------------------------------
IO�������������ú�����
-------------------------------------------------------*/
#if ECBM_GPIO_UPPULL_EN
void gpio_uppull(u8 pin,u8 en){
    /*---�����￪ʼ�������ڽ��IO�ڱ�š�---*/
    if(pin==Dxx)goto gpio_uppull_end;
    ecbm_port=pin&0xf0;
    ecbm_pin =ecbm_pin_mask[pin&0x0f];
    if((pin&0x0f)>7){
        return;
    }
    /*-------����������������ɡ�-------*/
    if(en){//�����ʹ�ܣ��򽫶�Ӧ��IO�����������衣
        switch(ecbm_port){
            #if ECBM_GPIO0_EN
            case 0x00:P0PU|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO1_EN
            case 0x10:P1PU|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO2_EN
            case 0x20:P2PU|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO3_EN
            case 0x30:P3PU|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO4_EN
            case 0x40:P4PU|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO5_EN
            case 0x50:P5PU|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO6_EN
            case 0x60:P6PU|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO7_EN
            case 0x70:P7PU|=ecbm_pin;break;
            #endif
            default:return;break;
        }
    }else{//�����ʧ�ܣ��򽫶�Ӧ��IOȡ���������衣
        switch(ecbm_port){
            #if ECBM_GPIO0_EN
            case 0x00:P0PU&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO1_EN
            case 0x10:P1PU&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO2_EN
            case 0x20:P2PU&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO3_EN
            case 0x30:P3PU&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO4_EN
            case 0x40:P4PU&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO5_EN
            case 0x50:P5PU&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO6_EN
            case 0x60:P6PU&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO7_EN
            case 0x70:P7PU&=~ecbm_pin;break;
            #endif
            default:return;break;
        }
    }
    gpio_uppull_end:;
}
#endif
#if ECBM_GPIO_UPPULL_EX_EN
void gpio_uppull_ex(u8 port,u8 pin,u8 en){
    if(en){//�����ʹ�ܣ��򽫶�Ӧ��IO�����������衣
        switch(port){
            #if ECBM_GPIO0_EN
            case 0x00:P0PU|=pin;break;
            #endif
            #if ECBM_GPIO1_EN
            case 0x10:P1PU|=pin;break;
            #endif
            #if ECBM_GPIO2_EN
            case 0x20:P2PU|=pin;break;
            #endif
            #if ECBM_GPIO3_EN
            case 0x30:P3PU|=pin;break;
            #endif
            #if ECBM_GPIO4_EN
            case 0x40:P4PU|=pin;break;
            #endif
            #if ECBM_GPIO5_EN
            case 0x50:P5PU|=pin;break;
            #endif
            #if ECBM_GPIO6_EN
            case 0x60:P6PU|=pin;break;
            #endif
            #if ECBM_GPIO7_EN
            case 0x70:P7PU|=pin;break;
            #endif
            default:return;break;
        }
    }else{//�����ʧ�ܣ��򽫶�Ӧ��IOȡ���������衣
        switch(port){
            #if ECBM_GPIO0_EN
            case 0x00:P0PU&=~pin;break;
            #endif
            #if ECBM_GPIO1_EN
            case 0x10:P1PU&=~pin;break;
            #endif
            #if ECBM_GPIO2_EN
            case 0x20:P2PU&=~pin;break;
            #endif
            #if ECBM_GPIO3_EN
            case 0x30:P3PU&=~pin;break;
            #endif
            #if ECBM_GPIO4_EN
            case 0x40:P4PU&=~pin;break;
            #endif
            #if ECBM_GPIO5_EN
            case 0x50:P5PU&=~pin;break;
            #endif
            #if ECBM_GPIO6_EN
            case 0x60:P6PU&=~pin;break;
            #endif
            #if ECBM_GPIO7_EN
            case 0x70:P7PU&=~pin;break;
            #endif
            default:return;break;
        }
    }
}
#endif
/*-------------------------------------------------------
����IO�ڹ���ģʽ������
-------------------------------------------------------*/
#if ECBM_GPIO_MODE_EN
void gpio_mode(u8 pin,u8 mode){
    /*---�����￪ʼ�������ڽ��IO�ڱ�š�---*/
    if(pin==Dxx)goto gpio_mode_end;
    ecbm_port=pin&0xf0;
    ecbm_pin=ecbm_pin_mask[pin&0x0f];
    if((pin&0x0f)>7){
        return;
    }
    switch(ecbm_port){
        #if ECBM_GPIO0_EN
        case 0x00:ecbm_port=GPIO_P0;break;
        #endif
        #if ECBM_GPIO1_EN
        case 0x10:ecbm_port=GPIO_P1;break;
        #endif
        #if ECBM_GPIO2_EN
        case 0x20:ecbm_port=GPIO_P2;break;
        #endif
        #if ECBM_GPIO3_EN
        case 0x30:ecbm_port=GPIO_P3;break;
        #endif
        #if ECBM_GPIO4_EN
        case 0x40:ecbm_port=GPIO_P4;break;
        #endif
        #if ECBM_GPIO5_EN
        case 0x50:ecbm_port=GPIO_P5;break;
        #endif
        #if ECBM_GPIO6_EN
        case 0x60:ecbm_port=GPIO_P6;break;
        #endif
        #if ECBM_GPIO7_EN
        case 0x70:ecbm_port=GPIO_P7;break;
        #endif
        default:return;break;
    }
    /*-------����������������ɡ�-------*/
    if(mode>3){
        return;
    }    
    #if ECBM_GPIO0_EN
    if(ecbm_port==GPIO_P0){//��������������趨��ͬ��IO���ã���ͬ��
        if(mode==GPIO_PU){P0M1&=~ecbm_pin;P0M0&=~ecbm_pin;}
        if(mode==GPIO_HZ){P0M1|= ecbm_pin;P0M0&=~ecbm_pin;}
        if(mode==GPIO_OD){P0M1|= ecbm_pin;P0M0|= ecbm_pin;}
        if(mode==GPIO_PP){P0M1&=~ecbm_pin;P0M0|= ecbm_pin;}
    }
    #endif
    #if ECBM_GPIO1_EN
    if(ecbm_port==GPIO_P1){
        if(mode==GPIO_PU){P1M1&=~ecbm_pin;P1M0&=~ecbm_pin;}
        if(mode==GPIO_HZ){P1M1|= ecbm_pin;P1M0&=~ecbm_pin;}
        if(mode==GPIO_OD){P1M1|= ecbm_pin;P1M0|= ecbm_pin;}
        if(mode==GPIO_PP){P1M1&=~ecbm_pin;P1M0|= ecbm_pin;}
    }
    #endif
    #if ECBM_GPIO2_EN
    if(ecbm_port==GPIO_P2){
        if(mode==GPIO_PU){P2M1&=~ecbm_pin;P2M0&=~ecbm_pin;}
        if(mode==GPIO_HZ){P2M1|= ecbm_pin;P2M0&=~ecbm_pin;}
        if(mode==GPIO_OD){P2M1|= ecbm_pin;P2M0|= ecbm_pin;}
        if(mode==GPIO_PP){P2M1&=~ecbm_pin;P2M0|= ecbm_pin;}
    }    
    #endif
    #if ECBM_GPIO3_EN
    if(ecbm_port==GPIO_P3){
        if(mode==GPIO_PU){P3M1&=~ecbm_pin;P3M0&=~ecbm_pin;}
        if(mode==GPIO_HZ){P3M1|= ecbm_pin;P3M0&=~ecbm_pin;}
        if(mode==GPIO_OD){P3M1|= ecbm_pin;P3M0|= ecbm_pin;}
        if(mode==GPIO_PP){P3M1&=~ecbm_pin;P3M0|= ecbm_pin;}
    }
    #endif
    #if ECBM_GPIO4_EN
    if(ecbm_port==GPIO_P4){
        if(mode==GPIO_PU){P4M1&=~ecbm_pin;P4M0&=~ecbm_pin;}
        if(mode==GPIO_HZ){P4M1|= ecbm_pin;P4M0&=~ecbm_pin;}
        if(mode==GPIO_OD){P4M1|= ecbm_pin;P4M0|= ecbm_pin;}
        if(mode==GPIO_PP){P4M1&=~ecbm_pin;P4M0|= ecbm_pin;}
    }
    #endif
    #if ECBM_GPIO5_EN
    if(ecbm_port==GPIO_P5){
        if(mode==GPIO_PU){P5M1&=~ecbm_pin;P5M0&=~ecbm_pin;}
        if(mode==GPIO_HZ){P5M1|= ecbm_pin;P5M0&=~ecbm_pin;}
        if(mode==GPIO_OD){P5M1|= ecbm_pin;P5M0|= ecbm_pin;}
        if(mode==GPIO_PP){P5M1&=~ecbm_pin;P5M0|= ecbm_pin;}
    }    
    #endif
    #if ECBM_GPIO6_EN
    if(ecbm_port==GPIO_P6){
        if(mode==GPIO_PU){P6M1&=~ecbm_pin;P6M0&=~ecbm_pin;}
        if(mode==GPIO_HZ){P6M1|= ecbm_pin;P6M0&=~ecbm_pin;}
        if(mode==GPIO_OD){P6M1|= ecbm_pin;P6M0|= ecbm_pin;}
        if(mode==GPIO_PP){P6M1&=~ecbm_pin;P6M0|= ecbm_pin;}
    }
    #endif
    #if ECBM_GPIO7_EN
    if(ecbm_port==GPIO_P7){
        if(mode==GPIO_PU){P7M1&=~ecbm_pin;P7M0&=~ecbm_pin;}
        if(mode==GPIO_HZ){P7M1|= ecbm_pin;P7M0&=~ecbm_pin;}
        if(mode==GPIO_OD){P7M1|= ecbm_pin;P7M0|= ecbm_pin;}
        if(mode==GPIO_PP){P7M1&=~ecbm_pin;P7M0|= ecbm_pin;}
    }    
    #endif
    gpio_mode_end:;
}
#endif
#if ECBM_GPIO_MODE_EX_EN
void gpio_mode_ex(u8 port,u8 pin,u8 mode){
    if(mode>3){
        return;
    }    
    #if ECBM_GPIO0_EN
    if(port==GPIO_P0){//��������������趨��ͬ��IO���ã���ͬ��
        if(mode==GPIO_PU){P0M1&=~pin;P0M0&=~pin;}
        if(mode==GPIO_HZ){P0M1|= pin;P0M0&=~pin;}
        if(mode==GPIO_OD){P0M1|= pin;P0M0|= pin;}
        if(mode==GPIO_PP){P0M1&=~pin;P0M0|= pin;}
    }
    #endif
    #if ECBM_GPIO1_EN
    if(port==GPIO_P1){
        if(mode==GPIO_PU){P1M1&=~pin;P1M0&=~pin;}
        if(mode==GPIO_HZ){P1M1|= pin;P1M0&=~pin;}
        if(mode==GPIO_OD){P1M1|= pin;P1M0|= pin;}
        if(mode==GPIO_PP){P1M1&=~pin;P1M0|= pin;}
    }
    #endif
    #if ECBM_GPIO2_EN
    if(port==GPIO_P2){
        if(mode==GPIO_PU){P2M1&=~pin;P2M0&=~pin;}
        if(mode==GPIO_HZ){P2M1|= pin;P2M0&=~pin;}
        if(mode==GPIO_OD){P2M1|= pin;P2M0|= pin;}
        if(mode==GPIO_PP){P2M1&=~pin;P2M0|= pin;}
    }    
    #endif
    #if ECBM_GPIO3_EN
    if(port==GPIO_P3){
        if(mode==GPIO_PU){P3M1&=~pin;P3M0&=~pin;}
        if(mode==GPIO_HZ){P3M1|= pin;P3M0&=~pin;}
        if(mode==GPIO_OD){P3M1|= pin;P3M0|= pin;}
        if(mode==GPIO_PP){P3M1&=~pin;P3M0|= pin;}
    }
    #endif
    #if ECBM_GPIO4_EN
    if(port==GPIO_P4){
        if(mode==GPIO_PU){P4M1&=~pin;P4M0&=~pin;}
        if(mode==GPIO_HZ){P4M1|= pin;P4M0&=~pin;}
        if(mode==GPIO_OD){P4M1|= pin;P4M0|= pin;}
        if(mode==GPIO_PP){P4M1&=~pin;P4M0|= pin;}
    }
    #endif
    #if ECBM_GPIO5_EN
    if(port==GPIO_P5){
        if(mode==GPIO_PU){P5M1&=~pin;P5M0&=~pin;}
        if(mode==GPIO_HZ){P5M1|= pin;P5M0&=~pin;}
        if(mode==GPIO_OD){P5M1|= pin;P5M0|= pin;}
        if(mode==GPIO_PP){P5M1&=~pin;P5M0|= pin;}
    }    
    #endif
    #if ECBM_GPIO6_EN
    if(port==GPIO_P6){
        if(mode==GPIO_PU){P6M1&=~pin;P6M0&=~pin;}
        if(mode==GPIO_HZ){P6M1|= pin;P6M0&=~pin;}
        if(mode==GPIO_OD){P6M1|= pin;P6M0|= pin;}
        if(mode==GPIO_PP){P6M1&=~pin;P6M0|= pin;}
    }
    #endif
    #if ECBM_GPIO7_EN
    if(port==GPIO_P7){
        if(mode==GPIO_PU){P7M1&=~pin;P7M0&=~pin;}
        if(mode==GPIO_HZ){P7M1|= pin;P7M0&=~pin;}
        if(mode==GPIO_OD){P7M1|= pin;P7M0|= pin;}
        if(mode==GPIO_PP){P7M1&=~pin;P7M0|= pin;}
    }    
    #endif
}
#endif
/*-------------------------------------------------------
����IO�ڹ����ٶȺ�����
-------------------------------------------------------*/
#if    ECBM_GPIO_SPEED_EN == 1
#if ((ECBM_MCU&0xF00000)>0x200000)//����ǲ���GH��
void gpio_speed(u8 pin,u8 speed){
    /*---�����￪ʼ�������ڽ��IO�ڱ�š�---*/
    if(pin==Dxx)goto gpio_speed_end;
    ecbm_port=pin&0xf0;
    ecbm_pin=ecbm_pin_mask[pin&0x0f];
    if((pin&0x0f)>7){
        return;  
    }
    switch(ecbm_port){
        #if ECBM_GPIO0_EN
        case 0x00:ecbm_port=GPIO_P0;break;
        #endif
        #if ECBM_GPIO1_EN
        case 0x10:ecbm_port=GPIO_P1;break;
        #endif
        #if ECBM_GPIO2_EN
        case 0x20:ecbm_port=GPIO_P2;break;
        #endif
        #if ECBM_GPIO3_EN
        case 0x30:ecbm_port=GPIO_P3;break;
        #endif
        #if ECBM_GPIO4_EN
        case 0x40:ecbm_port=GPIO_P4;break;
        #endif
        #if ECBM_GPIO5_EN
        case 0x50:ecbm_port=GPIO_P5;break;
        #endif
        #if ECBM_GPIO6_EN
        case 0x60:ecbm_port=GPIO_P6;break;
        #endif
        #if ECBM_GPIO7_EN
        case 0x70:ecbm_port=GPIO_P7;break;
        #endif
        default:return;break;
    }
    /*-------����������������ɡ�-------*/
    if(speed==GPIO_SLOW){
        switch(ecbm_port){
            #if ECBM_GPIO0_EN
            case GPIO_P0:{P0SR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO1_EN
            case GPIO_P1:{P1SR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO2_EN
            case GPIO_P2:{P2SR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO3_EN
            case GPIO_P3:{P3SR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO4_EN
            case GPIO_P4:{P4SR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO5_EN
            case GPIO_P5:{P5SR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO6_EN
            case GPIO_P6:{P6SR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO7_EN
            case GPIO_P7:{P7SR|=ecbm_pin;}break;
            #endif
        }
    }else{
        switch(ecbm_port){
            #if ECBM_GPIO0_EN
            case GPIO_P0:{P0SR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO1_EN
            case GPIO_P1:{P1SR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO2_EN
            case GPIO_P2:{P2SR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO3_EN
            case GPIO_P3:{P3SR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO4_EN
            case GPIO_P4:{P4SR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO5_EN
            case GPIO_P5:{P5SR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO6_EN
            case GPIO_P6:{P6SR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO7_EN
            case GPIO_P7:{P7SR&=~ecbm_pin;}break;
            #endif
        }        
    }
    gpio_speed_end:;
}
#endif
#endif
/*-------------------------------------------------------
����IO����������������
-------------------------------------------------------*/
#if    ECBM_GPIO_CURRENT_EN == 1
#if ((ECBM_MCU&0xF00000)>0x200000)//����ǲ���GH��
void gpio_current(u8 pin,u8 current){
    /*---�����￪ʼ�������ڽ��IO�ڱ�š�---*/
    if(pin==Dxx)goto gpio_current_end;
    ecbm_port=pin&0xf0;
    ecbm_pin=ecbm_pin_mask[pin&0x0f];
    if((pin&0x0f)>7){
        return;
    }
    switch(ecbm_port){
        #if ECBM_GPIO0_EN
        case 0x00:ecbm_port=GPIO_P0;break;
        #endif
        #if ECBM_GPIO1_EN
        case 0x10:ecbm_port=GPIO_P1;break;
        #endif
        #if ECBM_GPIO2_EN
        case 0x20:ecbm_port=GPIO_P2;break;
        #endif
        #if ECBM_GPIO3_EN
        case 0x30:ecbm_port=GPIO_P3;break;
        #endif
        #if ECBM_GPIO4_EN
        case 0x40:ecbm_port=GPIO_P4;break;
        #endif
        #if ECBM_GPIO5_EN
        case 0x50:ecbm_port=GPIO_P5;break;
        #endif
        #if ECBM_GPIO6_EN
        case 0x60:ecbm_port=GPIO_P6;break;
        #endif
        #if ECBM_GPIO7_EN
        case 0x70:ecbm_port=GPIO_P7;break;
        #endif
        default:return;break;
    }
    /*-------����������������ɡ�-------*/
    if(current==GPIO_GEN){
        switch(ecbm_port){
            #if ECBM_GPIO0_EN
            case GPIO_P0:{P0DR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO1_EN
            case GPIO_P1:{P1DR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO2_EN
            case GPIO_P2:{P2DR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO3_EN
            case GPIO_P3:{P3DR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO4_EN
            case GPIO_P4:{P4DR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO5_EN
            case GPIO_P5:{P5DR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO6_EN
            case GPIO_P6:{P6DR|=ecbm_pin;}break;
            #endif
            #if ECBM_GPIO7_EN
            case GPIO_P7:{P7DR|=ecbm_pin;}break;
            #endif
        }
    }else{
        switch(ecbm_port){
            #if ECBM_GPIO0_EN
            case GPIO_P0:{P0DR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO1_EN
            case GPIO_P1:{P1DR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO2_EN
            case GPIO_P2:{P2DR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO3_EN
            case GPIO_P3:{P3DR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO4_EN
            case GPIO_P4:{P4DR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO5_EN
            case GPIO_P5:{P5DR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO6_EN
            case GPIO_P6:{P6DR&=~ecbm_pin;}break;
            #endif
            #if ECBM_GPIO7_EN
            case GPIO_P7:{P7DR&=~ecbm_pin;}break;
            #endif
        }        
    }
    gpio_current_end:;
}
#endif
#endif
/*�������۵�ר��**************************************************************/#endif
/*�������۵�ר��**********************��ͨIO����ģ��****************************/#if 1
/*-------------------------------------------------------
P��д�뺯����ֱ��д��8λ���ݵ�ĳ��P���ϡ�
-------------------------------------------------------*/
#if ECBM_GPIO_WRITE_EN
void gpio_write(u8 port,u8 dat){
    switch(port){//ͨ���ж�P�ڱ�Ž��벻ͬ�ķ�֧��
        #if ECBM_GPIO0_EN
        case GPIO_P0:P0=dat;break;//�����ݷ��͵���Ӧ��P�ڣ���ͬ��
        #endif
        #if ECBM_GPIO1_EN
        case GPIO_P1:P1=dat;break;
        #endif
        #if ECBM_GPIO2_EN
        case GPIO_P2:P2=dat;break;
        #endif
        #if ECBM_GPIO3_EN
        case GPIO_P3:P3=dat;break;
        #endif
        #if ECBM_GPIO4_EN
        case GPIO_P4:P4=dat;break;
        #endif
        #if ECBM_GPIO5_EN
        case GPIO_P5:P5=dat;break;
        #endif
        #if ECBM_GPIO6_EN
        case GPIO_P6:P6=dat;break;
        #endif
        #if ECBM_GPIO7_EN
        case GPIO_P7:P7=dat;break;
        #endif
        case GPIO_Px:break;
        default:return;break;
    }
}
#endif
/*-------------------------------------------------------
P�ڶ���������������P�ڵ�ֵһ���Զ���(����)��
-------------------------------------------------------*/
#if ECBM_GPIO_READ_EN
u8 gpio_read(u8 port){
    switch(port){//ͨ���ж�P�ڱ�Ž��벻ͬ�ķ�֧��
        #if ECBM_GPIO0_EN
        case GPIO_P0:return P0;break;//����ӦP�ڵ�ֵ���أ���ͬ��
        #endif
        #if ECBM_GPIO1_EN
        case GPIO_P1:return P1;break;
        #endif
        #if ECBM_GPIO2_EN
        case GPIO_P2:return P2;break;
        #endif
        #if ECBM_GPIO3_EN
        case GPIO_P3:return P3;break;
        #endif
        #if ECBM_GPIO4_EN
        case GPIO_P4:return P4;break;
        #endif
        #if ECBM_GPIO5_EN
        case GPIO_P5:return P5;break;
        #endif
        #if ECBM_GPIO6_EN
        case GPIO_P6:return P6;break;
        #endif
        #if ECBM_GPIO7_EN
        case GPIO_P7:return P7;break;
        #endif
		default:
        case GPIO_Px:return 0xff;break;
    }
}
#endif
/*-------------------------------------------------------
IO�����������
-------------------------------------------------------*/
#if ECBM_GPIO_OUT_EN
void gpio_out(u8 pin,u8 value){
    /*---�����￪ʼ�������ڽ��IO�ڱ�š�---*/
    if(pin==Dxx)goto gpio_out_end;
    ecbm_port=pin&0xf0;
    ecbm_pin =ecbm_pin_mask[pin&0x0f];
    if((pin&0x0f)>7){
        return;
    }
    /*-------����������������ɡ�-------*/
    if(value){//�û�����ʵ������ߵ�ƽ���ٶȻ��һЩ��
        switch(ecbm_port){
            #if ECBM_GPIO0_EN
            case 0x00:P0|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO1_EN
            case 0x10:P1|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO2_EN
            case 0x20:P2|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO3_EN
            case 0x30:P3|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO4_EN
            case 0x40:P4|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO5_EN
            case 0x50:P5|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO6_EN
            case 0x60:P6|=ecbm_pin;break;
            #endif
            #if ECBM_GPIO7_EN
            case 0x70:P7|=ecbm_pin;break;
            #endif
            default:return;break;
        }
    }else{//��������ʵ������͵�ƽ���ٶȻ��һЩ��
        switch(ecbm_port){
            #if ECBM_GPIO0_EN
            case 0x00:P0&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO1_EN
            case 0x10:P1&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO2_EN
            case 0x20:P2&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO3_EN
            case 0x30:P3&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO4_EN
            case 0x40:P4&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO5_EN
            case 0x50:P5&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO6_EN
            case 0x60:P6&=~ecbm_pin;break;
            #endif
            #if ECBM_GPIO7_EN
            case 0x70:P7&=~ecbm_pin;break;
            #endif
            default:return;break;
        }        
    }
    gpio_out_end:;
}
#endif
/*-------------------------------------------------------
IO�����뺯����
-------------------------------------------------------*/
#if ECBM_GPIO_IN_EN
u8  gpio_in(u8 pin){
    u8 data value;
    /*---�����￪ʼ�������ڽ��IO�ڱ�š�---*/
    if(pin==Dxx)return 0;
    ecbm_port=pin&0xf0;
    ecbm_pin =ecbm_pin_mask[pin&0x0f];
    if((pin&0x0f)>7){
        return 1; 
    }
    /*-------����������������ɡ�-------*/
    switch(ecbm_port){//ֱ�Ӷ�ȡ����P�ڵ�����
        #if ECBM_GPIO0_EN
        case 0x00:value=P0;break;
        #endif
        #if ECBM_GPIO1_EN
        case 0x10:value=P1;break;
        #endif
        #if ECBM_GPIO2_EN
        case 0x20:value=P2;break;
        #endif
        #if ECBM_GPIO3_EN
        case 0x30:value=P3;break;
        #endif
        #if ECBM_GPIO4_EN
        case 0x40:value=P4;break;
        #endif
        #if ECBM_GPIO5_EN
        case 0x50:value=P5;break;
        #endif
        #if ECBM_GPIO6_EN
        case 0x60:value=P6;break;
        #endif
        #if ECBM_GPIO7_EN
        case 0x70:value=P7;break;
        #endif
        default:break;
    }
    if(value&ecbm_pin)return 1;//ͨ������������ȡĳһλ�ĵ�ƽ״̬��
    else return 0;
}
#endif
/*-------------------------------------------------------
IO�ڵ�ƽ��ת������
-------------------------------------------------------*/
#if ECBM_GPIO_TOGGLE_EN
void gpio_toggle(u8 pin){
    /*---�����￪ʼ�������ڽ��IO�ڱ�š�---*/
    if(pin==Dxx)goto gpio_toggle_end;
    ecbm_port=pin&0xf0;
    ecbm_pin =ecbm_pin_mask[pin&0x0f];
    if((pin&0x0f)>7){
        return; 
    }
    /*-------����������������ɡ�-------*/
    switch(ecbm_port){//���������ֱ�ӷ�ת��Ӧ��IO�ڡ�
        #if ECBM_GPIO0_EN
        case 0x00:P0^=ecbm_pin;break;
        #endif
        #if ECBM_GPIO1_EN
        case 0x10:P1^=ecbm_pin;break;
        #endif
        #if ECBM_GPIO2_EN
        case 0x20:P2^=ecbm_pin;break;
        #endif
        #if ECBM_GPIO3_EN
        case 0x30:P3^=ecbm_pin;break;
        #endif
        #if ECBM_GPIO4_EN
        case 0x40:P4^=ecbm_pin;break;
        #endif
        #if ECBM_GPIO5_EN
        case 0x50:P5^=ecbm_pin;break;
        #endif
        #if ECBM_GPIO6_EN
        case 0x60:P6^=ecbm_pin;break;
        #endif
        #if ECBM_GPIO7_EN
        case 0x70:P7^=ecbm_pin;break;
        #endif
        default:return;break;
    }
    gpio_toggle_end:;
}
#endif
/*�������۵�ר��**************************************************************/#endif
/*�������۵�ר��**********************����IO����ģ��****************************/#if 1
/*-------------------------------------------------------
IO�ڵ�ƽ���ٷ�ת������
-------------------------------------------------------*/
#if ECBM_GPIO_TOGGLE_FAST_EN
void gpio_toggle_fast(u8 port,u8 pin){
    switch(port){//������ķ�ת��������������������IO�����Ĵ��룬ʵ���Ƕδ���ǳ���ʱ��
        #if ECBM_GPIO0_EN
        case GPIO_P0:P0^=pin;break;
        #endif
        #if ECBM_GPIO1_EN
        case GPIO_P1:P1^=pin;break;
        #endif
        #if ECBM_GPIO2_EN
        case GPIO_P2:P2^=pin;break;
        #endif
        #if ECBM_GPIO3_EN
        case GPIO_P3:P3^=pin;break;
        #endif
        #if ECBM_GPIO4_EN
        case GPIO_P4:P4^=pin;break;
        #endif
        #if ECBM_GPIO5_EN
        case GPIO_P5:P5^=pin;break;
        #endif
        #if ECBM_GPIO6_EN
        case GPIO_P6:P6^=pin;break;
        #endif
        #if ECBM_GPIO7_EN
        case GPIO_P7:P7^=pin;break;
        #endif
        case GPIO_Px:break;
    }
}
#endif
/*-------------------------------------------------------
IO�ڵ�ƽ�������������
-------------------------------------------------------*/
#if ECBM_GPIO_OUT_FAST_EN
void gpio_out_fast   (u8 port,u8 pin,u8 val){
    if(val){//������������������������������IO�����Ĵ��룬ʵ���Ƕδ���ǳ���ʱ��
        switch(port){
            #if ECBM_GPIO0_EN
            case GPIO_P0:P0|=pin;break;
            #endif
            #if ECBM_GPIO1_EN
            case GPIO_P1:P1|=pin;break;
            #endif
            #if ECBM_GPIO2_EN
            case GPIO_P2:P2|=pin;break;
            #endif
            #if ECBM_GPIO3_EN
            case GPIO_P3:P3|=pin;break;
            #endif
            #if ECBM_GPIO4_EN
            case GPIO_P4:P4|=pin;break;
            #endif
            #if ECBM_GPIO5_EN
            case GPIO_P5:P5|=pin;break;
            #endif
            #if ECBM_GPIO6_EN
            case GPIO_P6:P6|=pin;break;
            #endif
            #if ECBM_GPIO7_EN
            case GPIO_P7:P7|=pin;break;
            #endif
            case GPIO_Px:break;
        } 
    }else{
        switch(port){
            #if ECBM_GPIO0_EN
            case GPIO_P0:P0&=~pin;break;
            #endif
            #if ECBM_GPIO1_EN
            case GPIO_P1:P1&=~pin;break;
            #endif
            #if ECBM_GPIO2_EN
            case GPIO_P2:P2&=~pin;break;
            #endif
            #if ECBM_GPIO3_EN
            case GPIO_P3:P3&=~pin;break;
            #endif
            #if ECBM_GPIO4_EN
            case GPIO_P4:P4&=~pin;break;
            #endif
            #if ECBM_GPIO5_EN
            case GPIO_P5:P5&=~pin;break;
            #endif
            #if ECBM_GPIO6_EN
            case GPIO_P6:P6&=~pin;break;
            #endif
            #if ECBM_GPIO7_EN
            case GPIO_P7:P7&=~pin;break;
            #endif
            case GPIO_Px:break;
        } 
    }
}
#endif
/*-------------------------------------------------------
IO�ڵ�ƽ�������뺯����
-------------------------------------------------------*/
#if ECBM_GPIO_IN_FAST_EN
u8  gpio_in_fast    (u8 port,u8 pin){
    u8 val;
    switch(port){//����������뺯������������������IO�����Ĵ��룬ʵ���Ƕδ���ǳ���ʱ��
        #if ECBM_GPIO0_EN
        case GPIO_P0:val=P0;break;
        #endif
        #if ECBM_GPIO1_EN
        case GPIO_P1:val=P1;break;
        #endif
        #if ECBM_GPIO2_EN
        case GPIO_P2:val=P2;break;
        #endif
        #if ECBM_GPIO3_EN
        case GPIO_P3:val=P3;break;
        #endif
        #if ECBM_GPIO4_EN
        case GPIO_P4:val=P4;break;
        #endif
        #if ECBM_GPIO5_EN
        case GPIO_P5:val=P5;break;
        #endif
        #if ECBM_GPIO6_EN
        case GPIO_P6:val=P6;break;
        #endif
        #if ECBM_GPIO7_EN
        case GPIO_P7:val=P7;break;
        #endif
        case GPIO_Px:return 1;break;
    } 
    if(val&pin)return 1;
    else return 0;
}
#endif
/*�������۵�ר��**************************************************************/
#endif  //���������#ifndef��ϳ�һ������Ρ�
        //��һ������Ϊ��β��