#include "ecbm_core.h"//ͳһ���غ���ͷ�ļ�
/*--------------------------------------��������-----------------------------------*/
/*-------------------------------------------------------
�������ȼ�������
-------------------------------------------------------*/
void nvic_set_priority(void){
#if ((ECBM_EXTI0_EN)&&(ECBM_EXTI_LIB_EN))
    #if      ECBM_NVIC_EXTI0_PRIORITY == 0
        EXTI0_SET_IT_PRIORITY_0;
    #elif    ECBM_NVIC_EXTI0_PRIORITY == 1
        EXTI0_SET_IT_PRIORITY_1;
    #elif    ECBM_NVIC_EXTI0_PRIORITY == 2
        EXTI0_SET_IT_PRIORITY_2;
    #elif    ECBM_NVIC_EXTI0_PRIORITY == 3
        EXTI0_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_TIMER0_IT_EN)&&(ECBM_TIMER_LIB_EN))
    #if     ECBM_NVIC_TIMER0_PRIORITY == 0
        TIMER0_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_TIMER0_PRIORITY == 1
        TIMER0_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_TIMER0_PRIORITY == 2
        TIMER0_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_TIMER0_PRIORITY == 3
        TIMER0_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_EXTI1_EN)&&(ECBM_EXTI_LIB_EN))
    #if      ECBM_NVIC_EXTI1_PRIORITY == 0
        EXTI1_SET_IT_PRIORITY_0;
    #elif    ECBM_NVIC_EXTI1_PRIORITY == 1
        EXTI1_SET_IT_PRIORITY_1;
    #elif    ECBM_NVIC_EXTI1_PRIORITY == 2
        EXTI1_SET_IT_PRIORITY_2;
    #elif    ECBM_NVIC_EXTI1_PRIORITY == 3
        EXTI1_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_TIMER1_IT_EN)&&(ECBM_TIMER_LIB_EN))
    #if     ECBM_NVIC_TIMER1_PRIORITY == 0
        TIMER1_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_TIMER1_PRIORITY == 1
        TIMER1_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_TIMER1_PRIORITY == 2
        TIMER1_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_TIMER1_PRIORITY == 3
        TIMER1_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_UART1_EN)&&(ECBM_UART_LIB_EN))
    #if     ECBM_NVIC_UART1_PRIORITY == 0
        UART1_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_UART1_PRIORITY == 1
        UART1_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_UART1_PRIORITY == 2
        UART1_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_UART1_PRIORITY == 3
        UART1_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_ADC_IT_EN)&&(ECBM_ADC_LIB_EN))
    #if     ECBM_NVIC_ADC_PRIORITY == 0
        ADC_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_ADC_PRIORITY == 1
        ADC_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_ADC_PRIORITY == 2
        ADC_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_ADC_PRIORITY == 3
        ADC_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_POWER_RST_CFG_EN)&&(ECBM_POWER_LIB_EN))
    #if     ECBM_NVIC_LVD_PRIORITY == 0
        LVD_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_LVD_PRIORITY == 1
        LVD_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_LVD_PRIORITY == 2
        LVD_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_LVD_PRIORITY == 3
        LVD_SET_IT_PRIORITY_3;
    #endif
#endif

#if ECBM_PCA_LIB_EN
    #if     ECBM_NVIC_PCA_PRIORITY == 0

    #elif   ECBM_NVIC_PCA_PRIORITY == 1

    #elif   ECBM_NVIC_PCA_PRIORITY == 2

    #elif   ECBM_NVIC_PCA_PRIORITY == 3

    #endif
#endif

#if ((ECBM_UART2_EN)&&(ECBM_UART_LIB_EN))
    #if     ECBM_NVIC_UART2_PRIORITY == 0
        UART2_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_UART2_PRIORITY == 1
        UART2_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_UART2_PRIORITY == 2
        UART2_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_UART2_PRIORITY == 3
        UART2_SET_IT_PRIORITY_3;
    #endif
#endif

#if (ECBM_SPI_IT_EN)&&(ECBM_SPI_LIB_EN)
    #if     ECBM_NVIC_SPI_PRIORITY == 0
        SPI_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_SPI_PRIORITY == 1
        SPI_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_SPI_PRIORITY == 2
        SPI_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_SPI_PRIORITY == 3
        SPI_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_EXTI4_EN)&&(ECBM_EXTI_LIB_EN))
    #if     ECBM_NVIC_EXTI4_PRIORITY == 0
        EXTI4_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_EXTI4_PRIORITY == 1
        EXTI4_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_EXTI4_PRIORITY == 2
        EXTI4_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_EXTI4_PRIORITY == 3
        EXTI4_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_UART3_EN)&&(ECBM_UART_LIB_EN))
    #if     ECBM_NVIC_UART3_PRIORITY == 0
        UART3_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_UART3_PRIORITY == 1
        UART3_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_UART3_PRIORITY == 2
        UART3_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_UART3_PRIORITY == 3
        UART3_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_UART4_EN)&&(ECBM_UART_LIB_EN))
    #if     ECBM_NVIC_UART4_PRIORITY == 0
        UART4_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_UART4_PRIORITY == 1
        UART4_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_UART4_PRIORITY == 2
        UART4_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_UART4_PRIORITY == 3
        UART4_SET_IT_PRIORITY_3;
    #endif
#endif

#if ((ECBM_CMP_CMPCR1&0x30)&&(ECBM_CMP_LIB_EN))
    #if     ECBM_NVIC_CMP_PRIORITY == 0
        CMP_SET_IT_PRIORITY_0;
    #elif   ECBM_NVIC_CMP_PRIORITY == 1
        CMP_SET_IT_PRIORITY_1;
    #elif   ECBM_NVIC_CMP_PRIORITY == 2
        CMP_SET_IT_PRIORITY_2;
    #elif   ECBM_NVIC_CMP_PRIORITY == 3
        CMP_SET_IT_PRIORITY_3;
    #endif
#endif
}
/*-------------------------------------------------------
�ⲿ�ж�0�жϷ������
-------------------------------------------------------*/
#if ((ECBM_EXTI0_EN)&&(ECBM_EXTI_LIB_EN))
void nvic_exti0_function(void)interrupt 0{
    exti0_it_callback();
}
#endif
/*-------------------------------------------------------
��ʱ��0�жϷ������
-------------------------------------------------------*/
#if ((ECBM_TIMER0_IT_EN)&&(ECBM_TIMER_LIB_EN))||((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 0))
void nvic_timer0_function(void)interrupt 1{
    #if ((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 0))
    ECBM_STREAM_TIME_RUN();
    #endif
    #if ((ECBM_TIMER0_IT_EN)&&(ECBM_TIMER_LIB_EN))
    timer0_it_callback();
    #endif
}
#endif
/*-------------------------------------------------------
�ⲿ�ж�1�жϷ������
-------------------------------------------------------*/
#if ((ECBM_EXTI1_EN)&&(ECBM_EXTI_LIB_EN))
void nvic_exti1_function(void)interrupt 2{
    exti1_it_callback();
}
#endif
/*-------------------------------------------------------
��ʱ��1�жϷ������
-------------------------------------------------------*/
#if ((ECBM_TIMER1_IT_EN)&&(ECBM_TIMER_LIB_EN))||((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 1))
void nvic_timer1_function(void)interrupt 3{
    #if ((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 1))
    ECBM_STREAM_TIME_RUN();
    #endif
    #if ((ECBM_TIMER1_IT_EN)&&(ECBM_TIMER_LIB_EN))
    timer1_it_callback();
    #endif
}
#endif
/*-------------------------------------------------------
����1�жϷ������
-------------------------------------------------------*/
#if ((ECBM_UART1_EN)&&(ECBM_UART_LIB_EN))
extern bit uart1_busy;//����1����æ��־λ��
void nvic_uart1_function(void)interrupt 4{
    if(UART1_GET_RI_FLAG){//����1�����жϡ�
        UART1_CLR_RI_FLAG;//�������1���ձ�־��
        #if ECBM_UART1_RECEIVE_CALLBACK_EN
        uart1_receive_callback();
        #endif
        #if ECBM_AUTO_DOWNLOAD_EN
        system_uart_reset();//ʵ���Զ����ع��ܡ�
        #endif
        #if (ECBM_STREAM_EN == 1)&&(ECBM_STREAM_UART == 1)
        ECBM_STREAM_IN(SBUF);
        #endif
    }
    if(UART1_GET_TI_FLAG){//����1�����жϡ�
        UART1_CLR_TI_FLAG;//�������1���ͱ�־��
        uart1_busy=0;//֪ͨ����3���ͺ�����
        #if ECBM_UART1_SEND_CALLBACK_EN
        uart1_send_callback();
        #endif
    }
}
#endif
/*-------------------------------------------------------
ADC�жϴ�������
-------------------------------------------------------*/
#if ((ECBM_ADC_IT_EN)&&(ECBM_ADC_LIB_EN))
void nvic_adc_function(void)interrupt 5{
    ADC_CLS_IT_FLAG;
    adc_it_callback();
}
#endif
/*-------------------------------------------------------
��ѹ����жϴ�������
-------------------------------------------------------*/
#if ((ECBM_POWER_RST_CFG_EN)&&(ECBM_POWER_LIB_EN))
void nvic_lvd_function(void)interrupt 6{
    LVD_CLS_IT_FLAG;
    lvd_it_callback();
}
#endif
/*-------------------------------------------------------
PCA�ĸ����жϴ�������
-------------------------------------------------------*/
#if ECBM_PCA_LIB_EN
void nvic_pca_function(void)interrupt 7{
    if(PCA_GET_IT_FLAG){
        PCA_CLS_IT_FLAG;
        #if ECBM_PCA_CALLBACK_EN
            pca_timer_callback();
        #endif
    }
    #if ECBM_PCA0_EN
    if(PCA0_GET_IT_FLAG){
        PCA0_CLS_IT_FLAG;
        #if ECBM_PCA0_TIMER_AUTO_EN
            if(pca_mode_0>=6){
                PCA_SET_REG_CCAP0HL(pca_timer_count_0);
                pca_timer_count_0+=pca_timer_add_0;//880ns
            }
        #endif
        #if ECBM_PCA0_CALLBACK_EN
            pca0_callback();
        #endif
    }
    #endif
    #if ECBM_PCA1_EN
    if(PCA1_GET_IT_FLAG){
        PCA1_CLS_IT_FLAG;
        #if ECBM_PCA1_TIMER_AUTO_EN
            if(pca_mode_1>=6){
                PCA_SET_REG_CCAP1HL(pca_timer_count_1);
                pca_timer_count_1+=pca_timer_add_1;//880ns
            }
        #endif
        #if ECBM_PCA1_CALLBACK_EN
            pca1_callback();
        #endif
    }
    #endif
    #if ECBM_PCA2_EN
    if(PCA2_GET_IT_FLAG){
        PCA2_CLS_IT_FLAG;
        #if ECBM_PCA2_TIMER_AUTO_EN
            if(pca_mode_2>=6){
                PCA_SET_REG_CCAP2HL(pca_timer_count_2);
                pca_timer_count_2+=pca_timer_add_2;//880ns
            }
        #endif
        #if ECBM_PCA2_CALLBACK_EN
            pca2_callback();
        #endif
    }
    #endif
    #if ECBM_PCA3_EN
    if(PCA3_GET_IT_FLAG){
        PCA3_CLS_IT_FLAG;
        #if ECBM_PCA3_TIMER_AUTO_EN
            if(pca_mode_3>=6){
                PCA_SET_REG_CCAP3HL(pca_timer_count_3);
                pca_timer_count_3+=pca_timer_add_3;//880ns
            }
        #endif
        #if ECBM_PCA3_CALLBACK_EN
            pca3_callback();
        #endif
    }
    #endif
}
#endif
/*-------------------------------------------------------
����2�жϷ������
-------------------------------------------------------*/
#if ((ECBM_UART2_EN)&&(ECBM_UART_LIB_EN))
extern bit uart2_busy;//����2����æ��־λ��
void nvic_uart2_function(void)interrupt 8{
    if(UART2_GET_RI_FLAG){  //����2�����жϡ�
        UART2_CLR_RI_FLAG; //�������2���ձ�־��
        #if ECBM_UART2_RECEIVE_CALLBACK_EN
        uart2_receive_callback();
        #endif
        #if (ECBM_STREAM_EN == 1)&&(ECBM_STREAM_UART == 2)
        ECBM_STREAM_IN(S2BUF);
        #endif
    }
    if(UART2_GET_TI_FLAG){  //����2�����жϡ�
        UART2_CLR_TI_FLAG; //�������2���ͱ�־��
        uart2_busy=0;//֪ͨ����2���ͺ�����
        #if ECBM_UART2_SEND_CALLBACK_EN
        uart2_send_callback();
        #endif
    }
}
#endif
/*-------------------------------------------------------
SPI�жϷ������
-------------------------------------------------------*/
#if (ECBM_SPI_IT_EN)&&(ECBM_SPI_LIB_EN)
void nvic_spi_function(void)interrupt 9{
    spi_it_callback();
}
#endif
/*-------------------------------------------------------
�ⲿ�ж�2�жϷ������
-------------------------------------------------------*/
#if ((ECBM_EXTI2_EN)&&(ECBM_EXTI_LIB_EN))
void nvic_exti2_function(void)interrupt 10{
    exti2_it_callback();
}
#endif
/*-------------------------------------------------------
�ⲿ�ж�3�жϷ������
-------------------------------------------------------*/
#if ((ECBM_EXTI3_EN)&&(ECBM_EXTI_LIB_EN))
void nvic_exti3_function(void)interrupt 11{
    exti3_it_callback();
}
#endif
/*-------------------------------------------------------
��ʱ��2�жϷ������
-------------------------------------------------------*/
#if ((ECBM_TIMER2_IT_EN)&&(ECBM_TIMER_LIB_EN))||((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 2))
void nvic_timer2_function(void)interrupt 12{
    #if ((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 2))
    ECBM_STREAM_TIME_RUN();
    #endif
    #if ((ECBM_TIMER2_IT_EN)&&(ECBM_TIMER_LIB_EN))
    timer2_it_callback();
    #endif
}
#endif
/*-------------------------------------------------------
�ⲿ�ж�4�жϷ������
-------------------------------------------------------*/
#if ((ECBM_EXTI4_EN)&&(ECBM_EXTI_LIB_EN))
void nvic_exti4_function(void)interrupt 16{
    exti4_it_callback();
}
#endif
/*-------------------------------------------------------
����3�жϷ������
-------------------------------------------------------*/
#if ((ECBM_UART3_EN)&&(ECBM_UART_LIB_EN))
extern bit uart3_busy;//����3����æ��־λ��
void nvic_uart3_function(void)interrupt 17{
    if(UART3_GET_RI_FLAG){  //����3�����жϡ�
        UART3_CLR_RI_FLAG; //�������3���ձ�־��
        #if ECBM_UART3_RECEIVE_CALLBACK_EN
        uart3_receive_callback();
        #endif
        #if (ECBM_STREAM_EN == 1)&&(ECBM_STREAM_UART == 3)
        ECBM_STREAM_IN(S3BUF);
        #endif
    }
    if(UART3_GET_TI_FLAG){  //����3�����жϡ�
        UART3_CLR_TI_FLAG; //�������3���ͱ�־��
        uart3_busy=0;//֪ͨ����3���ͺ�����
        #if ECBM_UART3_SEND_CALLBACK_EN
        uart3_send_callback();
        #endif
    }
}
#endif
/*-------------------------------------------------------
����4�жϷ������
-------------------------------------------------------*/
#if ((ECBM_UART4_EN)&&(ECBM_UART_LIB_EN))
extern bit uart4_busy;//����4����æ��־λ��
void nvic_uart4_function(void)interrupt 18{
    if(UART4_GET_RI_FLAG){  //����4�����жϡ�
        UART4_CLR_RI_FLAG; //�������4���ձ�־��
        #if ECBM_UART4_RECEIVE_CALLBACK_EN
        uart4_receive_callback();
        #endif
        #if (ECBM_STREAM_EN == 1)&&(ECBM_STREAM_UART == 4)
        ECBM_STREAM_IN(S4BUF);
        #endif
    }
    if(UART4_GET_TI_FLAG){  //����4�����жϡ�
        UART4_CLR_TI_FLAG; //�������4���ͱ�־��
        uart4_busy=0;//֪ͨ����4���ͺ�����
        #if ECBM_UART4_SEND_CALLBACK_EN
        uart4_send_callback();
        #endif
    }
}
#endif
/*-------------------------------------------------------
��ʱ��3�жϷ������
-------------------------------------------------------*/
#if ((ECBM_TIMER3_IT_EN)&&(ECBM_TIMER_LIB_EN))||((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 3))
void nvic_timer3_function(void)interrupt 19{
    #if ((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 3))
    ECBM_STREAM_TIME_RUN();
    #endif
    #if ((ECBM_TIMER3_IT_EN)&&(ECBM_TIMER_LIB_EN))
    timer3_it_callback();
    #endif
}
#endif
/*-------------------------------------------------------
��ʱ��4�жϷ������
-------------------------------------------------------*/
#if ((ECBM_TIMER4_IT_EN)&&(ECBM_TIMER_LIB_EN))||((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 4))
void nvic_timer4_function(void)interrupt 20{
    #if ((ECBM_STREAM_EN)&&(ECBM_UART_LIB_EN)&&(ECBM_STREAM_TIMER == 4))
    ECBM_STREAM_TIME_RUN();
    #endif
    #if ((ECBM_TIMER4_IT_EN)&&(ECBM_TIMER_LIB_EN))
    timer4_it_callback();
    #endif
}
#endif
/*-------------------------------------------------------
�Ƚ����жϷ������
-------------------------------------------------------*/
#if ((ECBM_CMP_CMPCR1&0x30)&&(ECBM_CMP_LIB_EN))
void nvic_cmp_function(void)interrupt 21{
    //cmp_it_callback();
}
#endif
/*
void nvic_pwm0_function(void)interrupt 22{
    pwm0_it_callback();
}
void nvic_pwm0fd_function(void)interrupt 23{
    pwm0fdit_callback();
}*/
/*-------------------------------------------------------
IIC�жϷ������
-------------------------------------------------------*/
#if (ECBM_IIC_LIB_EN)
extern bit iic_master_busy; 
void nvic_iic_function(void)interrupt 24{
    if(IIC_GET_M_IT_FLAG){//�����������ж�ʱ��
        IIC_CLS_M_IT_FLAG;//�������жϱ�־��
        iic_master_busy=0;//֪ͨIIC�ĺ��������Լ�������ִ�С�
    }
//    iic_it_callback();
}
#endif
/*
void nvic_usb_function(void)interrupt 25{
    usb_it_callback();
}
void nvic_pwma_function(void)interrupt 26{
    pwma_it_callback();
}
void nvic_pwmb_function(void)interrupt 27{
    pwmb_it_callback();
}
void nvic_pwm1_function(void)interrupt 28{
    pwm1_it_callback();
}
void nvic_pwm2_function(void)interrupt 29{
    pwm2_it_callback();
}
void nvic_pwm3_function(void)interrupt 30{
    pwm3_it_callback();
}
void nvic_pwm4_function(void)interrupt 31{
    pwm4_it_callback();
}
*/

