#include "define.h"
#include "msp430.h"

void zhuangtai();     //状态识别函数声明
void fasong();        //发送模块函数声明
void clear();         //清空message

char bufferzhuangtai; //定义接收状态缓存
char snd_end=0;       //定义完成事件标志
char message[50];     //定义待发送的信息

unsigned char message1[50]=" Someone has tried to open but failed!\r\n\n";//消息1字符串
unsigned char message2[50]=" Your door has been opened!\r\n\n";//消息2字符串
unsigned char message3[50]=" Someone is asking for help!\r\n\n";//消息3字符串
unsigned char message4[50]=" Your door is not closed!\r\n\n";//消息4字符串
unsigned char message5[50]=" Your door is closed!\r\n\n";//消息4字符串

void zhuangtai()
{
    if(flaglanya==1)//直接开门模式
       {
         flagkaimen=1;
         flaganjian=0;
       }
       else if(flaglanya==2) //锁死模式
       {
         flagkaimen=0;
         flaganjian=0;
       }
       else if(flaglanya==0) //按键模式
       {
         flagkaimen=0;
         flaganjian=1;
       }
       else if(flaglanya==3) //关门模式
       {
         flagkaimen=0;
         flaganjian=1;
         flagguanmen=1;
       }
}

void fasong()
{
    //根据标志选择发送信息
   if(flagkaimen==1)flagfasong=2;
   else if(flagkaimen==0&&k==1)flagfasong=1;
   else if(k==2)flagfasong=3;
   else if(flagmen)flagfasong=4;
   else if(flagguanmen)flagfasong=5;
   else flagfasong=0;

   //从发送缓冲器发送一个字符
   for(j=0;j<50;j++)
   {
       if(flagfasong==1) message[j]=message1[j];
       if(flagfasong==2) message[j]=message2[j];
       if(flagfasong==3) message[j]=message3[j];
       if(flagfasong==4) message[j]=message4[j];
       if(flagfasong==5) message[j]=message5[j];
   }
   j=0;

   //开始发送
   if(flagfasong)
       {
       IE2 |= UCA0TXIE;
       while(snd_end==0);//等待发送完毕
        snd_end=0;
       }

   //清零信号
   if(flagfasong&&flaglanya!=2)
       {
       flaglanya=0;
       flagkaimen=0;
       flagguanmen=0;
       }

   k=0;//清零发送标志位
   j=0;
   flagfasong=0;
   clear();
}




void clear()
{
   for (i=0;i<50;i++) message[i]=0;
   i=0;
}


//************中断子程********************
//*******************************************************


#pragma vector = USCIAB0RX_VECTOR         //蓝牙接收中断
__interrupt void USCI0RX_isr()
{
    bufferzhuangtai=UCA0RXBUF;     //读接收缓冲器保存一个字符

    if(bufferzhuangtai=='0')         //按键模式
    {
      flaglanya=0;
    }
    else if(bufferzhuangtai=='1')        //直接开门
    {
      flaglanya=1;
    }
    else if(bufferzhuangtai=='2')       //锁死模式
    {
      flaglanya=2;
    }
    else if(bufferzhuangtai=='3')       //锁死模式
       {
         flaglanya=3;
       }
}

#pragma vector=USCIAB0TX_VECTOR       //蓝牙发送中断
__interrupt void USCI0TX_isr()
{
    UCA0TXBUF = message[j];
    j++;
    if(message[j+1]=='\0')
        {
        IE2 &= ~UCA0TXIE;
        snd_end=1;
        }
}
