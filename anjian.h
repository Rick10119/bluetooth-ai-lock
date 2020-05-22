#include "define.h"
#include "msp430.h"

void saomiao();//键盘扫描函数声明
void anjian();//按键模块函数声明
void delay4();
#define ROW P2OUT  //矩阵键盘的行宏定义
#define COL P2IN   //矩阵键盘的列宏定义
int DPYOUT;    //数码管输出口宏定义
unsigned char seg[16]={1,2,3,4,4,5,6,7,7,8,9,10,0,14,15,16};


void delay4()
{
    int i3=0;
    do i3++;
     while(i3<3000);
}

//*********************键盘扫描*****************************
unsigned char keyscan()
{
   delay4();
   unsigned char key=0;
   ROW=0x0f;
   if((COL&0x0f)!=0x0f)
   {

       ROW=0x7f;
       if((COL & 0x0f)== 0x0f)
         {ROW=0xbf;
         if((COL & 0x0f)== 0x0f)
         {ROW=0xdf;
          if((COL & 0x0f)== 0x0f)
          {ROW=0xef;
           if((COL & 0x0f)== 0x0f)
             key=17;
           else key=((ROW&0xf0)|(COL&0x0f));
          }
           else key=((ROW&0xf0)|(COL&0x0f));
         }
          else key=((ROW&0xf0)|(COL&0x0f));

     }
      else key=((ROW&0xf0)|(COL&0x0f));
   }
   delay4();
   return key;
}

//*********************对应数字*****************************
void saomiao()
{
    switch(keyscan())
         {
         case 0x77:DPYOUT=seg[0];break;
         case 0x7b:DPYOUT=seg[1];break;
         case 0x7d:DPYOUT=seg[2];break;
         case 0x7e:DPYOUT=seg[3];break;
         case 0xb7:DPYOUT=seg[4];break;
         case 0xbb:DPYOUT=seg[5];break;
         case 0xbd:DPYOUT=seg[6];break;
         case 0xbe:DPYOUT=seg[7];break;
         case 0xd7:DPYOUT=seg[8];break;
         case 0xdb:DPYOUT=seg[9];break;
         case 0xdd:DPYOUT=seg[10];break;
         case 0xde:DPYOUT=seg[11];break;
         case 0xe7:DPYOUT=seg[12];break;
         case 0xeb:DPYOUT=seg[13];break;
         case 0xed:DPYOUT=seg[14];break;
         case 0xee:DPYOUT=seg[15];break;

         }
    keyval=DPYOUT;
}

//********************中断子程，判断*****************************
#pragma  vector=PORT2_VECTOR             //P2向量中断
__interrupt  void port_ISR2()
{

  Time = 0; //开始倒计时
  saomiao();
  P2OUT &= ~BIT0;//蜂鸣器响

  if(keyval==15)       //进入识别模式或者确认
   {
      k=1;
      if(shurunum>0)flagpipei=1;      //开始匹配
      shuru[0]=10;
      shuru[1]=10;
   }
  if(keyval==14)       //进入求助模式
  {
      k=2;
      shuru[0]=13;
      shuru[1]=13;
      TA1CCTL0|=BIT1;//输入结束
  }
  if(k==1&&keyval<14)
  {

      if(shurunum<6)shuru[shurunum+2]=keyval;
      shurunum++;

  }

  //结束，设置
  keyval=17;
  P2IE=0x00;
  _EINT();
  while(Time<1);
  P2OUT  =  0x0F;      //设置上拉电阻接电平
  P2IFG=0;
  P2IE=0x0E;
}


