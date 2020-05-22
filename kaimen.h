#include"define.h"
#include "msp430.h"

void kaimen();//����ģ�麯������
void guanmen();//���ź���
void delay1(unsigned int a);       //��ʱ��������
unsigned int flagwait=0;  //�ȴ���־

//***************���Ž�***************************
void kaimen()
{
      flagguanmen=0;
      P1OUT|=BIT3;
      delay1(0xffff);//open


   //��ʼ��ʱ
   TA1CCTL0|=CCIE;        //��ʱ����ʼ��ʱ
   while(flagwait==0);
   flagwait=0;

}

//***************������******************************
void guanmen()
{

    P1OUT|=BIT4;
    delay1(0xffff);//open
    TA1CCTL0|=CCIE;        //��ʱ����ʼ��ʱ
       while(flagwait==0);
    flagwait=0;

}

void delay1(unsigned int a)                        //��ʱ������������
{
    unsigned int i2;
    for (i2=0;i2<a;i2++);
}

//***************��ʱ��******************************
#pragma vector=TIMER1_A0_VECTOR                 //��ʱ���ж�
__interrupt void timer0_B0_ISR()
{
    Time++;             //�������
    if(Time>=5)P1OUT&=~(BIT3+BIT4);//stop
    if(Time==10)         //����10�ж����Ƿ����
              {
                Time=0;
                flagwait=1;      //���ٵȴ�
                 TA1CCTL0 &= ~CCIE;  //������ʱ
                if(P1IN & BIT0)
                    {
                      flagmen=0;//���Ѿ�����
                    }
              }
}
