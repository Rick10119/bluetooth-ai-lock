#include"define.h"
#include "msp430.h"

void kaimen();//开门模块函数声明
void guanmen();//关门函数
void delay1(unsigned int a);       //延时函数声明
unsigned int flagwait=0;  //等待标志

//***************打开门禁***************************
void kaimen()
{
      flagguanmen=0;
      P1OUT|=BIT3;
      delay1(0xffff);//open


   //开始计时
   TA1CCTL0|=CCIE;        //定时器开始计时
   while(flagwait==0);
   flagwait=0;

}

//***************关上锁******************************
void guanmen()
{

    P1OUT|=BIT4;
    delay1(0xffff);//open
    TA1CCTL0|=CCIE;        //定时器开始计时
       while(flagwait==0);
    flagwait=0;

}

void delay1(unsigned int a)                        //延时按键防抖函数
{
    unsigned int i2;
    for (i2=0;i2<a;i2++);
}

//***************定时器******************************
#pragma vector=TIMER1_A0_VECTOR                 //定时器中断
__interrupt void timer0_B0_ISR()
{
    Time++;             //半秒计数
    if(Time>=5)P1OUT&=~(BIT3+BIT4);//stop
    if(Time==10)         //经过10判断门是否关上
              {
                Time=0;
                flagwait=1;      //不再等待
                 TA1CCTL0 &= ~CCIE;  //结束计时
                if(P1IN & BIT0)
                    {
                      flagmen=0;//门已经关上
                    }
              }
}
