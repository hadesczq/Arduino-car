#include <IRremote.h>  
#include <Servo.h>

//***********************蜂鸣器*************************
int Buzzer=8;
//***********************转向灯*************************
int LEDL=A1;
int LEDR=A2;
//***********************电机驱动引脚定义*************************
int MotorRight1=5;
int MotorRight2=6;
int MotorLeft1=10;
int MotorLeft2=11;
int counter=0;
const int irReceiverPin = 2; //红外线接收器 OUTPUT 接在 pin 2

char val; 
//***********************设定所收到的红外线信息IRcode*************************
long IRfront= 0x00FF629D;        //前进
long IRback=0x00FFA857;         //后退
long IRturnright=0x00FFC23D;    //右转
long IRturnleft= 0x00FF22DD;     //左转
long IRstop=0x00FF02FD;         //停止
long IRcny70=0x00FF6897;        //巡线模式
long IRAutorun=0x00FF9867;      //超声波避障模式
long IRturnsmallleft= 0x00FF22DD; 
//*************************红外巡线模块引脚定义************************************
const int SensorLeft = 7;     
const int SensorMiddle= 4 ;    
const int SensorRight = 3;     
int SL;   
int SM;   
int SR;    
IRrecv irrecv(irReceiverPin);  //定义红外线接收器的信号
decode_results results;       // 解码结果 decode_results 结构体 result 数组
//*************************超声波引脚定义******************************
int inputPin =13 ; //定义超声波接收引脚Echo
int outputPin =12; // 定义超声波发射引脚Trig
int Fspeedd = 0; // 前方距离
int Rspeedd = 0; // 右方距离
int Lspeedd = 0; // 左方距离
int directionn = 0; // 前=8 后=2 左=4 右=6 
Servo myservo; 
int delay_time = 250; // 转向后稳定时间
int Fgo = 8; //前进
int Rgo = 6; // 右转
int Lgo = 4; // 左转
int Bgo = 2; // 后退
//********************************************************************(SETUP)
void setup()
{  
  Serial.begin(9600);
  pinMode(LEDL,  OUTPUT);  
  pinMode(LEDR,  OUTPUT);  
  digitalWrite(LEDL,LOW);
  digitalWrite(LEDR,LOW);
  pinMode(MotorRight1, OUTPUT); 
  pinMode(MotorRight2, OUTPUT);  
  pinMode(MotorLeft1,  OUTPUT);  
  pinMode(MotorLeft2,  OUTPUT);  
  pinMode(Buzzer, OUTPUT); 
  digitalWrite(Buzzer,LOW);
  irrecv.enableIRIn();     // 红外接收解码
  pinMode(SensorLeft, INPUT); 
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT); 
  digitalWrite(2,HIGH);
  
  pinMode(inputPin, INPUT); 
  pinMode(outputPin, OUTPUT); 
  myservo.attach(9); // 舵机输出PWM引脚
  myservo.write(130);

 }
void Beep()
{
   digitalWrite(Buzzer,HIGH);
   delay(250);
   digitalWrite(Buzzer,LOW);
}
void LedL_on()
{
  digitalWrite(LEDL,HIGH);
}
void LedL_off()
{
  digitalWrite(LEDL,LOW);
}
void LedR_on()
{
  digitalWrite(LEDR,HIGH);
}
void LedR_off()
{
  digitalWrite(LEDR,LOW);
}
//******************************************************************(Void)
void turnR(int a) //右转 双轮
{ 
        LedR_on();
        digitalWrite(MotorRight1,LOW);
        digitalWrite(MotorRight2,HIGH);
        digitalWrite(MotorLeft1,LOW);
        digitalWrite(MotorLeft2,HIGH);
        delay(a * 100); 
        LedR_off();
        
}
void right(int b) //右转 单轮
{
       LedR_on();
       digitalWrite(MotorLeft1,LOW);
       digitalWrite(MotorLeft2,HIGH);
       digitalWrite(MotorRight1,LOW);
       digitalWrite(MotorRight2,LOW);
       delay(b * 100);
       LedR_off();
}

void left(int c) //左转 单轮
{
      LedL_on();
      digitalWrite(MotorRight1,HIGH);
      digitalWrite(MotorRight2,LOW);
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,LOW);
      delay(c * 100);
      LedL_off();
}
void back(int d) //后退
{
      digitalWrite(MotorRight1,HIGH);
      digitalWrite(MotorRight2,LOW);
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,HIGH);
      delay(d * 100);
}
void advance(int e) //前进
{
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,HIGH);
      digitalWrite(MotorLeft1,HIGH);
      digitalWrite(MotorLeft2,LOW);
      delay(e * 100);
} 
void stopp(int f) //停止
{
     digitalWrite(MotorRight1,LOW);
     digitalWrite(MotorRight2,LOW);
     digitalWrite(MotorLeft1,LOW);
     digitalWrite(MotorLeft2,LOW);
     delay(f * 100);
}
void turnL(int g) //左转 单轮
{       
        LedL_on();
        digitalWrite(MotorRight1,HIGH);
        digitalWrite(MotorRight2,LOW);
        digitalWrite(MotorLeft1,HIGH);
        digitalWrite(MotorLeft2,LOW);;
        delay(g * 100); 
        LedL_off
        ();
}
void detection() 
{ 
    int delay_time = 250; 
    ask_pin_F();

    if(Fspeedd <5) 
   {
      stopp(1); 
      back(2); 
   }
    if(Fspeedd < 10) 
   {
      stopp(1); 
      ask_pin_L(); 
      delay(delay_time); 
      ask_pin_R(); 
      delay(delay_time);

      if(Lspeedd > Rspeedd) 
     {
        directionn = Lgo; 
     }

      if(Lspeedd <= Rspeedd)
      {
        directionn = Rgo; 
      } 

      if (Lspeedd < 5 && Rspeedd < 5) 
     {
        directionn = Bgo; 
      } 
    }
    else 
   {
      directionn = Fgo; 
   }
}   
//*********************************************************************************
void ask_pin_F() 
{
myservo.write(130);
digitalWrite(outputPin, LOW);
delayMicroseconds(2);
digitalWrite(outputPin, HIGH);
delayMicroseconds(10);
digitalWrite(outputPin, LOW);
float Fdistance = pulseIn(inputPin, HIGH);
Fdistance= Fdistance/5.8/10; 
Serial.print("F distance:"); 
Serial.println(Fdistance); 
Fspeedd = Fdistance; 
} 
//********************************************************************************
void ask_pin_L() 
{
myservo.write(180);
Beep();
delay(delay_time);
digitalWrite(outputPin, LOW);
delayMicroseconds(2);
digitalWrite(outputPin, HIGH); 
delayMicroseconds(10);
digitalWrite(outputPin, LOW); 
float Ldistance = pulseIn(inputPin, HIGH); 
Ldistance= Ldistance/5.8/10; 
Serial.print("L distance:");
Serial.println(Ldistance);
Lspeedd = Ldistance; 
} 
//******************************************************************************
void ask_pin_R()
{
myservo.write(85);
Beep();
delay(delay_time);
digitalWrite(outputPin, LOW); 
delayMicroseconds(2);
digitalWrite(outputPin, HIGH); 
delayMicroseconds(10);
digitalWrite(outputPin, LOW);
float Rdistance = pulseIn(inputPin, HIGH); 
Rdistance= Rdistance/5.8/10; 
Serial.print("R distance:");
Serial.println(Rdistance);
Rspeedd = Rdistance; 
} 
//******************************************************************************(LOOP)
void loop() 
{
      SL = digitalRead(SensorLeft);
      SM = digitalRead(SensorMiddle);
      SR = digitalRead(SensorRight);
      Bluetooth();

//***************************************************************************正常遙控模式      
  if (irrecv.decode(&results)) 
    {   
      Beep();      
/***********************************************************************/
      if (results.value == IRfront)
       {
        advance(10);
       }
/***********************************************************************/ 
      if (results.value ==  IRback)
       {
        back(10);
       }
/***********************************************************************/
      if (results.value == IRturnright)
      {
        right(6); 
      }
/***********************************************************************/
     if (results.value == IRturnleft)
     {
       left(6); 
     }
/***********************************************************************/    
    if (results.value == IRstop)
   {
     digitalWrite(MotorRight1,LOW);
     digitalWrite(MotorRight2,LOW);
     digitalWrite(MotorLeft1,LOW);
     digitalWrite(MotorLeft2,LOW);
    }
//***********************************************************************巡线模式
    if (results.value == IRcny70)
   {                     
     while(IRcny70)
     {  
       SL = digitalRead(SensorLeft);
       SM = digitalRead(SensorMiddle);
       SR = digitalRead(SensorRight);
                   
       if (SM == HIGH)
       { 
          if (SL == LOW & SR == HIGH) 
          {  
            turnR(10);
//             digitalWrite(MotorRight1,LOW);
//             digitalWrite(MotorRight2,HIGH);
//             analogWrite(MotorLeft1,0);
//             analogWrite(MotorLeft2,80);
          } 
          else if (SR == LOW & SL == HIGH) 
          {  
            turnL(10);
//             analogWrite(MotorRight1,0);
//             analogWrite(MotorRight2,80);
//             digitalWrite(MotorLeft1,LOW);
//             digitalWrite(MotorLeft2,HIGH);
          }
         else  
          { 
            advance(10);
//             digitalWrite(MotorRight1,LOW);
//             digitalWrite(MotorRight2,HIGH);
//             digitalWrite(MotorLeft1,LOW);
//             digitalWrite(MotorLeft2,HIGH);
//             analogWrite(MotorLeft1,200);
//             analogWrite(MotorLeft2,200);
//             analogWrite(MotorRight1,200);
//             analogWrite(MotorRight2,200);
         }      
       } 
       else 
      {  
         if (SL == LOW & SR == HIGH)
        {  
          turnR(10);
//            digitalWrite(MotorRight1,LOW);
//            digitalWrite(MotorRight2,HIGH);
//            digitalWrite(MotorLeft1,LOW);
//            digitalWrite(MotorLeft2,LOW);
        }
         else if (SR == LOW & SL == HIGH) 
        {  
          turnL(10);
//           digitalWrite(MotorRight1,LOW);
//           digitalWrite(MotorRight2,LOW);
//           digitalWrite(MotorLeft1,LOW);
//           digitalWrite(MotorLeft2,HIGH);
        }
         else 
        {    
          advance(10);
//        digitalWrite(MotorRight1,HIGH);
//        digitalWrite(MotorRight2,LOW);
//        digitalWrite(MotorLeft1,HIGH);
//        digitalWrite(MotorLeft2,LOW);
        }
      }
       if (irrecv.decode(&results))
       {
             irrecv.resume(); 
                  Serial.println(results.value,HEX);
             if(results.value ==IRstop)
             { 
               digitalWrite(MotorRight1,HIGH);
               digitalWrite(MotorRight2,HIGH);
               digitalWrite(MotorLeft1,HIGH);
               digitalWrite(MotorLeft2,HIGH);
               break;
             }
       }
     }
      results.value=0;
   }
//***********************************************************************超声波避障模式
 if (results.value ==IRAutorun )
      {
           while(IRAutorun)
        {
            myservo.write(130);
            detection(); 
             if(directionn == 8) 
            { 
              if (irrecv.decode(&results))
           {
             irrecv.resume(); 
             Serial.println(results.value,HEX);
             if(results.value ==IRstop)
             { 
               digitalWrite(MotorRight1,LOW); 
               digitalWrite(MotorRight2,LOW);
               digitalWrite(MotorLeft1,LOW);
               digitalWrite(MotorLeft2,LOW);
               break;
             }
           }
                results.value=0;
                advance(1);
                Serial.print(" Advance "); 
                Serial.print(" "); 
            }
           if(directionn == 2) 
          {
            if (irrecv.decode(&results))
           {
             irrecv.resume(); 
             Serial.println(results.value,HEX);
             if(results.value ==IRstop)
             { 
               digitalWrite(MotorRight1,LOW); 
               digitalWrite(MotorRight2,LOW);
               digitalWrite(MotorLeft1,LOW);
               digitalWrite(MotorLeft2,LOW);
               break;
             }
           }
              results.value=0;
              back(8);
              turnL(3); 
              Serial.print(" Reverse "); 
          }
            if(directionn == 6) 
          {
           if (irrecv.decode(&results))
           {
              irrecv.resume(); 
              Serial.println(results.value,HEX);
             if(results.value ==IRstop)
             { 
               digitalWrite(MotorRight1,LOW); 
               digitalWrite(MotorRight2,LOW);
               digitalWrite(MotorLeft1,LOW);
               digitalWrite(MotorLeft2,LOW);
               break;
             }
           }
             results.value=0;
               back(1); 
               turnR(3);
               Serial.print(" Right ");
          }
            if(directionn == 4) 
          { 
             if (irrecv.decode(&results))
           {
             irrecv.resume(); 
             Serial.println(results.value,HEX);
             if(results.value ==IRstop)
             { 
               digitalWrite(MotorRight1,LOW); 
               digitalWrite(MotorRight2,LOW);
               digitalWrite(MotorLeft1,LOW);
               digitalWrite(MotorLeft2,LOW);
               break;
             }
           }
                results.value=0;
                back(1); 
                turnL(3); 
                Serial.print(" Left ");
           } 
            
             if (irrecv.decode(&results))
           {
             irrecv.resume(); 
             Serial.println(results.value,HEX);
             if(results.value ==IRstop)
             { 
               digitalWrite(MotorRight1,LOW); 
               digitalWrite(MotorRight2,LOW);
               digitalWrite(MotorLeft1,LOW);
               digitalWrite(MotorLeft2,LOW);
               break;
             }
           }
         }
               results.value=0;
       }

       
/***********************************************************************/    
     else
    {
           digitalWrite(MotorRight1,LOW);
           digitalWrite(MotorRight2,LOW);
           digitalWrite(MotorLeft1,LOW);
           digitalWrite(MotorLeft2,LOW);
     }
      

        irrecv.resume();    
   }  
}
/***********************************************************************/   
void Bluetooth()
{  if (Serial.available()) {
    val = Serial.read();
  }
    if (val == 'U') { // Forward
      advance(1);
    } else if (val == 'S') { // Stop Forward     
      stopp(1) ;
    } else if (val == 'D') { // Backward
      back(1); 
    }else if (val == 'R') { // Right
      turnR(1);
    } else if (val == 'L') { // Left
      turnL(1);
    }
}
    
    
