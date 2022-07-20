#include "ecbm_core.h"//统一加载核心头文件
#if ECBM_CMP_LIB_EN   //检查本库有没有被使能
/*------------------------------------资源冲突警告---------------------------------*/
#if (ECBM_MCU == 0x110301)||(ECBM_MCU == 0x310201)||(ECBM_MCU == 0x3102A1)
#error 该型号没有比较器！
#endif
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
比较器初始化函数。
-------------------------------------------------------*/
void cmp_init(void){
    CMP_SET_REG_CMPCR2(ECBM_CMP_CMPCR2);//写入比较器前端控制信息。
    CMP_SET_REG_CMPCR1(ECBM_CMP_CMPCR1);//写入比较器后端控制信息。
    CMP_SET_REG_CMPEXCFG(ECBM_CMP_EXCFG);//写入比较器扩展配置信息。
    #if ECBM_CMP_INIT_ON                //如果设定了初始化开启，
    CMP_POWER_ON;                       //就开启比较器。
    #endif
}
/*-------------------------------------------------------
比较器读取结果函数。
-------------------------------------------------------*/
u8 cmp_read(void){
    if(CMP_GET_RESULT){//判断结果寄存器，
        return 1;      //有结果就返回1，
    }else{
        return 0;      //否则返回0。
    }
}
/*-------------------------------------------------------
比较器开启函数。
-------------------------------------------------------*/
void cmp_start(void){
    CMP_POWER_ON;
}
/*-------------------------------------------------------
比较器关闭函数。
-------------------------------------------------------*/
void cmp_stop(void){
    CMP_POWER_OFF;
}
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。