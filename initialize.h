#include "define.h"
#include "msp430.h"

void USCIA0_init(); //蓝牙设置初始化函数声明
//void LD3320_init(); //LD3320设置初始化函数声明
void TAO_init();    //定时器设置初始化函数声明
void GPIO_init();   //GPIO设置初始化函数声明
void init();        //总初始化函数声明




void init()
{
     WDTCTL = WDTPW + WDTHOLD;     //关闭看门狗
     GPIO_init();   //GPIO设置初始化函数
     USCIA0_init(); //蓝牙设置初始化函数
    // LD3320_init(); //LD3320设置初始化函数
     TAO_init();    //定时器设置初始化函数

     //标志位的初始化
     flagkaimen=0;                    //开门标志位
     flaglanya=0;                     //0按键模式,1开门模式，2锁死模式
     flagfasong=0;                    //发送标志位 1失败 2成功 3求助 0不发
     flagpipei=0;                     //匹配标志位 0继续录音；1开始匹配
     flagguanmen=1;                     //关门标志位
     flagmen=0;                         //们的状态 1为开，0为关
     j=0;       //计数变量i、j
     i=0;
     Time=0;   //全局时间计数变量
     Key_Num=0;//键盘输入

     IE2 |= UCA0RXIE;      //接收中断位打开
     _EINT();                //中断总控位打开
}

void USCIA0_init()                  //蓝牙设置初始化函数
{

        UCA0CTL1|= UCSWRST;         //置软件复位位swrst为1
        P1SEL |= BIT1+BIT2;         //置P1.1、P1.2为串行接口收、发引脚功能
        P1SEL2 |= BIT1+BIT2;        //
        UCA0CTL1|=UCSSEL_2+UCRXEIE; //波特率时钟选择MCLK，不论对错均收
        UCA0BR0 = 104;              //波特率9600
        UCA0BR1 = 0;
        UCA0MCTL=UCBRF_0+UCBRS_1;
        UCA0CTL1 &=~UCSWRST;        //置软件复位位swrst为0，串口设置完毕
}

/*
void LD3320_init()                  //LD3320设置初始化函数
{
  UCA1CTL1 |= UCSWRST;          //swrst=1
  P3SEL |= BIT6+BIT7;
  P3SEL2 |= BIT6+BIT7;          //P1.1和P1.2引脚功能设置
  UCA1CTL1 |= UCSSEL_2+UCRXEIE;     //时钟源选 SMCLK 默认约 1MHz
  UCA1BR1 = 0;              //高八位 0
  UCA1BR0 = 104;            //低八位为 104
  UCA1MCTL = UCBRS_1;           //由上述计算出 0.167*8 近似为 1
  UCA1CTL1 &=~UCSWRST ;         //swrst=0
}*/

void TAO_init()                     //定时器设置初始化函数
{
  TA0CTL|=ID_3+TACLR+TASSEL_2+MC_1;     //设置TA0计时，选用DCO时钟源1MHz
  TA0CCR0=63875;                        //TA比较控制寄存器0值为1.022M/8-1=125000
  TA1CTL|=ID_3+TACLR+TASSEL_2+MC_1;     //设置TA1计时，选用DCO时钟源1MHz
  TA1CCR0=63875;                        //TA比较控制寄存器0值为1.022M/8-1=31937
}

void GPIO_init()                    //GPIO设置初始化函数
{
    //设置键盘P2初始化
       P2SEL  =  0;
       P2SEL2 =  0;
       P2DIR |=  0XF1 ;  //将P2.0~2.3定义为输入，将P2.4~P2.7定义为输出
       P2IES |=  0X0F ;  //下降沿触发
       P2IFG  =  0X00 ;  //初始清空中断标志位
       P2REN  =  0x0E;     //输入设置上拉电阻
       P2OUT  =  0x0F;      //设置上拉电阻接电平



  P1SEL&=~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7);     //设置1.3-1.7
  P1SEL2&=~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7);
  P1OUT=0x01;
  P1DIR|= BIT3+BIT4+BIT5+BIT6+BIT7;
  P1REN = 0x01;  //开关

}


