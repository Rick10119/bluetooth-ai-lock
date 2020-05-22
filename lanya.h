#include "define.h"
#include "msp430.h"

void zhuangtai();     //״̬ʶ��������
void fasong();        //����ģ�麯������
void clear();         //���message

char bufferzhuangtai; //�������״̬����
char snd_end=0;       //��������¼���־
char message[50];     //��������͵���Ϣ

unsigned char message1[50]=" Someone has tried to open but failed!\r\n\n";//��Ϣ1�ַ���
unsigned char message2[50]=" Your door has been opened!\r\n\n";//��Ϣ2�ַ���
unsigned char message3[50]=" Someone is asking for help!\r\n\n";//��Ϣ3�ַ���
unsigned char message4[50]=" Your door is not closed!\r\n\n";//��Ϣ4�ַ���
unsigned char message5[50]=" Your door is closed!\r\n\n";//��Ϣ4�ַ���

void zhuangtai()
{
    if(flaglanya==1)//ֱ�ӿ���ģʽ
       {
         flagkaimen=1;
         flaganjian=0;
       }
       else if(flaglanya==2) //����ģʽ
       {
         flagkaimen=0;
         flaganjian=0;
       }
       else if(flaglanya==0) //����ģʽ
       {
         flagkaimen=0;
         flaganjian=1;
       }
       else if(flaglanya==3) //����ģʽ
       {
         flagkaimen=0;
         flaganjian=1;
         flagguanmen=1;
       }
}

void fasong()
{
    //���ݱ�־ѡ������Ϣ
   if(flagkaimen==1)flagfasong=2;
   else if(flagkaimen==0&&k==1)flagfasong=1;
   else if(k==2)flagfasong=3;
   else if(flagmen)flagfasong=4;
   else if(flagguanmen)flagfasong=5;
   else flagfasong=0;

   //�ӷ��ͻ���������һ���ַ�
   for(j=0;j<50;j++)
   {
       if(flagfasong==1) message[j]=message1[j];
       if(flagfasong==2) message[j]=message2[j];
       if(flagfasong==3) message[j]=message3[j];
       if(flagfasong==4) message[j]=message4[j];
       if(flagfasong==5) message[j]=message5[j];
   }
   j=0;

   //��ʼ����
   if(flagfasong)
       {
       IE2 |= UCA0TXIE;
       while(snd_end==0);//�ȴ��������
        snd_end=0;
       }

   //�����ź�
   if(flagfasong&&flaglanya!=2)
       {
       flaglanya=0;
       flagkaimen=0;
       flagguanmen=0;
       }

   k=0;//���㷢�ͱ�־λ
   j=0;
   flagfasong=0;
   clear();
}




void clear()
{
   for (i=0;i<50;i++) message[i]=0;
   i=0;
}


//************�ж��ӳ�********************
//*******************************************************


#pragma vector = USCIAB0RX_VECTOR         //���������ж�
__interrupt void USCI0RX_isr()
{
    bufferzhuangtai=UCA0RXBUF;     //�����ջ���������һ���ַ�

    if(bufferzhuangtai=='0')         //����ģʽ
    {
      flaglanya=0;
    }
    else if(bufferzhuangtai=='1')        //ֱ�ӿ���
    {
      flaglanya=1;
    }
    else if(bufferzhuangtai=='2')       //����ģʽ
    {
      flaglanya=2;
    }
    else if(bufferzhuangtai=='3')       //����ģʽ
       {
         flaglanya=3;
       }
}

#pragma vector=USCIAB0TX_VECTOR       //���������ж�
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
