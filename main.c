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

    init();//初始化
//****************************************************
//主循环：
//****************************************************
  while(1)
  {   

    zhuangtai();//确认智能锁状态
    shibie();//扫描键盘读数
    if(flagkaimen==1&&flaglanya!=2)kaimen();//执行开关控制
    if(flagguanmen)guanmen();//自动关门
    fasong();//向手机发送信号

  }
}
