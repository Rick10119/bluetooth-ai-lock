#include "msp430.h"
#include "string.h"
#include "define.h"
#include "initialize.h"
#include "lanya.h"
#include "anjian.h"
#include "shibie.h"
#include "kaimen.h"

void main( void )
{

    init();//��ʼ��
//****************************************************
//��ѭ����
//****************************************************
  while(1)
  {   

    zhuangtai();//ȷ��������״̬
    shibie();//ɨ����̶���
    if(flagkaimen==1&&flaglanya!=2)kaimen();//ִ�п��ؿ���
    if(flagguanmen)guanmen();//�Զ�����
    fasong();//���ֻ������ź�

  }
}
