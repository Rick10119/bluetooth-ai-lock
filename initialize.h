#include "define.h"
#include "msp430.h"

void USCIA0_init(); //�������ó�ʼ����������
//void LD3320_init(); //LD3320���ó�ʼ����������
void TAO_init();    //��ʱ�����ó�ʼ����������
void GPIO_init();   //GPIO���ó�ʼ����������
void init();        //�ܳ�ʼ����������




void init()
{
     WDTCTL = WDTPW + WDTHOLD;     //�رտ��Ź�
     GPIO_init();   //GPIO���ó�ʼ������
     USCIA0_init(); //�������ó�ʼ������
    // LD3320_init(); //LD3320���ó�ʼ������
     TAO_init();    //��ʱ�����ó�ʼ������

     //��־λ�ĳ�ʼ��
     flagkaimen=0;                    //���ű�־λ
     flaglanya=0;                     //0����ģʽ,1����ģʽ��2����ģʽ
     flagfasong=0;                    //���ͱ�־λ 1ʧ�� 2�ɹ� 3���� 0����
     flagpipei=0;                     //ƥ���־λ 0����¼����1��ʼƥ��
     flagguanmen=1;                     //���ű�־λ
     flagmen=0;                         //�ǵ�״̬ 1Ϊ����0Ϊ��
     j=0;       //��������i��j
     i=0;
     Time=0;   //ȫ��ʱ���������
     Key_Num=0;//��������

     IE2 |= UCA0RXIE;      //�����ж�λ��
     _EINT();                //�ж��ܿ�λ��
}

void USCIA0_init()                  //�������ó�ʼ������
{

        UCA0CTL1|= UCSWRST;         //�������λλswrstΪ1
        P1SEL |= BIT1+BIT2;         //��P1.1��P1.2Ϊ���нӿ��ա������Ź���
        P1SEL2 |= BIT1+BIT2;        //
        UCA0CTL1|=UCSSEL_2+UCRXEIE; //������ʱ��ѡ��MCLK�����۶Դ����
        UCA0BR0 = 104;              //������9600
        UCA0BR1 = 0;
        UCA0MCTL=UCBRF_0+UCBRS_1;
        UCA0CTL1 &=~UCSWRST;        //�������λλswrstΪ0�������������
}

/*
void LD3320_init()                  //LD3320���ó�ʼ������
{
  UCA1CTL1 |= UCSWRST;          //swrst=1
  P3SEL |= BIT6+BIT7;
  P3SEL2 |= BIT6+BIT7;          //P1.1��P1.2���Ź�������
  UCA1CTL1 |= UCSSEL_2+UCRXEIE;     //ʱ��Դѡ SMCLK Ĭ��Լ 1MHz
  UCA1BR1 = 0;              //�߰�λ 0
  UCA1BR0 = 104;            //�Ͱ�λΪ 104
  UCA1MCTL = UCBRS_1;           //����������� 0.167*8 ����Ϊ 1
  UCA1CTL1 &=~UCSWRST ;         //swrst=0
}*/

void TAO_init()                     //��ʱ�����ó�ʼ������
{
  TA0CTL|=ID_3+TACLR+TASSEL_2+MC_1;     //����TA0��ʱ��ѡ��DCOʱ��Դ1MHz
  TA0CCR0=63875;                        //TA�ȽϿ��ƼĴ���0ֵΪ1.022M/8-1=125000
  TA1CTL|=ID_3+TACLR+TASSEL_2+MC_1;     //����TA1��ʱ��ѡ��DCOʱ��Դ1MHz
  TA1CCR0=63875;                        //TA�ȽϿ��ƼĴ���0ֵΪ1.022M/8-1=31937
}

void GPIO_init()                    //GPIO���ó�ʼ������
{
    //���ü���P2��ʼ��
       P2SEL  =  0;
       P2SEL2 =  0;
       P2DIR |=  0XF1 ;  //��P2.0~2.3����Ϊ���룬��P2.4~P2.7����Ϊ���
       P2IES |=  0X0F ;  //�½��ش���
       P2IFG  =  0X00 ;  //��ʼ����жϱ�־λ
       P2REN  =  0x0E;     //����������������
       P2OUT  =  0x0F;      //������������ӵ�ƽ



  P1SEL&=~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7);     //����1.3-1.7
  P1SEL2&=~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7);
  P1OUT=0x01;
  P1DIR|= BIT3+BIT4+BIT5+BIT6+BIT7;
  P1REN = 0x01;  //����

}


