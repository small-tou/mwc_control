#include <Servo.h>

// 左边油门（上下运动）/方向 （水平旋转） ，右边副翼（左右俯冲）/升降 （前后俯冲）
#define YOUMEN 2;
#define FANGXIANG 3;
#define FUYI 4;
#define SHENGJIANG 5;

#define MIN_PWM 1000
#define MAX_PWM 2000

#define ONE_CHANNEL_TIME 2500 //一个通道给的占空时间
#define TOTAL_CHANNEL_TIME 20000 //定义频率

Servo YOUMEN_SERVO;
Servo FANGXIANG_SERVO;
Servo FUYI_SERVO;
Servo SHENGJIANG_SERVO;
//记录每个通道的值，会一直使用，可以用蓝牙修改
int youmen_v = 0;
int fangxiang_v = 0;
int fuyi_v = 0;
int shengjiang_v = 0;

int time ;

void setup() {
  //初始化servo
  YOUMEN_SERVO.attach(YOUMEN);
  FANGXIANG_SERVO.attach(FANGXIANG);
  FUYI_SERVO.attach(FUYI);
  SHENGJIANG_SERVO.attach(SHENGJIANG);
}

void loop() {
  // put your main code here, to run repeatedly:
  time = micros(); //记录当前微秒，每次loop执行不足TOTAL_CHANNEL_TIME的话，就delay剩下的时间
  youmen();
  fangxiang();
  fuyi();
  shengjiang();
  
}
/**
 * value 从0 - 100
 */
void youmen(){
  int v = map(youmen_v, 0, 100, MIN_PWM, MAX_PWM); 
  YOUMEN_SERVO.writeMicroseconds(v);
  delayMicroseconds(ONE_CHANNEL_TIME-v);
}
void fangxiang(){
  int v = map(fangxiang_v, 0, 100, MIN_PWM, MAX_PWM); 
  FANGXIANG_SERVO.writeMicroseconds(v);
  delayMicroseconds(ONE_CHANNEL_TIME-v);
}
void fuyi(){
  int v = map(fuyi_v, 0, 100, MIN_PWM, MAX_PWM); 
  FUYI_SERVO.writeMicroseconds(v);
  delayMicroseconds(ONE_CHANNEL_TIME-v);
}
void shengjiang(){
  int v = map(shengjiang_v, 0, 100, MIN_PWM, MAX_PWM); 
  SHENGJIANG_SERVO.writeMicroseconds(v);
  delayMicroseconds(ONE_CHANNEL_TIME-v);
}



