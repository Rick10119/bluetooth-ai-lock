#include "msp430.h"

unsigned int i,j;       //计数变量i、j
unsigned int k;
unsigned int Time;   //全局时间计数变量
unsigned char Key_Num;//键盘输入

 int flagkaimen;                    //开门标志位
 int flagguanmen;                    //关门门标志位
 int flaglanya;                     //0按键模式,1开门模式，2锁死模式
 int flagfasong;                    //发送标志位 1失败 2成功 3求助 4门没关0不发
 int flagpipei;                     //匹配标志位 0继续录音；1开始匹配
 int flaganjian;
 int flagmen;
 int keyval;   //键盘按键标志
 int shuru[8]; //用于存放键盘的输入
 int shurunum;  //用于记按下的数




