#include <Servo.h>

// 左边油门（上下运动）/方向 （水平旋转） ，右边副翼（左右俯冲）/升降 （前后俯冲）
#define YOUMEN 2
#define FANGXIANG 3
#define FUYI 4
#define SHENGJIANG 5

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

int time;
int time2 ;
long lastReceiveTime = 0;
void setup() {
  //初始化servo
  YOUMEN_SERVO.attach(YOUMEN);
  FANGXIANG_SERVO.attach(FANGXIANG);
  FUYI_SERVO.attach(FUYI);
  SHENGJIANG_SERVO.attach(SHENGJIANG);

  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  time = micros(); //记录当前微秒，每次loop执行不足TOTAL_CHANNEL_TIME的话，就delay剩下的时间

  //间隔上次有信号的时间小于2s，就挂掉
  if(time - lastReceiveTime >1000*1000*2){
    youmen_v = 0;
  }
  youmen();
  fangxiang();
  fuyi();
  shengjiang();
  if(Serial.available()>0)
  {
    lastReceiveTime = time;
      char c=Serial.read();
      if(c=='a'||c=='b'||c=='c'||c=='d'){
        String str = Serial.readStringUntil('\n');
        str.trim();
        int v = str.toInt();

        if(c=='a'){
          youmen_v = v;
        }else if(c=='b'){
          fangxiang_v = v;
        }else if(c=='c'){
          fuyi_v = v;
        }else if(c=='d'){
          shengjiang_v = v;
        }
      }
      else if(c=='s'){
        Serial.readStringUntil('\n');
        lastReceiveTime = time;
      }else {
        while(Serial.available())
          Serial.read();
      }
  }
  time2 = micros() - time;
  
  if(time2 < TOTAL_CHANNEL_TIME){
    delayMicroseconds(TOTAL_CHANNEL_TIME - time2);
  }else{
//    Serial.println("超过20ms了");
  }
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



