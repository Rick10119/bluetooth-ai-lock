#include "msp430.h"

unsigned int i,j;       //��������i��j
unsigned int k;
unsigned int Time;   //ȫ��ʱ���������
unsigned char Key_Num;//��������

 int flagkaimen;                    //���ű�־λ
 int flagguanmen;                    //�����ű�־λ
 int flaglanya;                     //0����ģʽ,1����ģʽ��2����ģʽ
 int flagfasong;                    //���ͱ�־λ 1ʧ�� 2�ɹ� 3���� 4��û��0����
 int flagpipei;                     //ƥ���־λ 0����¼����1��ʼƥ��
 int flaganjian;
 int flagmen;
 int keyval;   //���̰�����־
 int shuru[8]; //���ڴ�ż��̵�����
 int shurunum;  //���ڼǰ��µ���




