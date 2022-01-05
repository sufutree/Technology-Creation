#include <Unistep2.h>

Unistep2 stepper1(5, 6, 7, 8, 0, 1500);// IN1, IN2, IN3, IN4, 總step數, 每步的延遲(in micros)
Unistep2 stepper2(9, 10, 11, 12, 0, 1500); // IN1, IN2, IN3, IN4, 總step數, 每步的延遲(in micros)
int down_or_top = 0;
int mode = 0;

int buttonpush1;//按鈕按下紀錄
int buttonpush2;
int buttonpush3;

int buttonpin1 = 2 ; //黃色
int buttonpin2 = 3 ; //綠色
int buttonpin3 = 4 ; //mode按鈕

void setup() {

  Serial.begin(9600);//開啟序列埠
  pinMode( buttonpin1 , INPUT);//按鈕腳位模式為輸入
  pinMode( buttonpin2 , INPUT);
  pinMode( buttonpin3 , INPUT);
  digitalWrite(buttonpin1, HIGH);//開啟上拉電阻
  digitalWrite(buttonpin2, HIGH);
  digitalWrite(buttonpin3, HIGH);
}

void loop() {
  stepper1.run();  //步進機啟動
  stepper2.run();
  buttonpush1 = digitalRead (buttonpin1);//讀取按鈕資訊
  buttonpush2 = digitalRead (buttonpin2);
  buttonpush3 = digitalRead (buttonpin3);
  if (buttonpush3 == 0)
  {
    mode = 0;
  }
  else {
    mode = 1;
  }

  if (buttonpush1 == 0  && mode == 0) //黃色校正
  {
    stepper1.move(50);
    stepper2.move(50);
  }

  if (buttonpush2 == 0 && mode == 0) //綠色校正
  {
    stepper1.move(-50);
    stepper2.move(-50);
  }
  if (buttonpush1 == 0 && down_or_top == 0 && mode == 1) //下降
  {
    stepper1.moveTo(6000);
    stepper2.moveTo(6000);
    down_or_top = 1;
  }
  if (buttonpush2 == 0 && down_or_top == 1 && mode == 1) //上升
  {
    stepper1.moveTo(0);
    stepper2.moveTo(0);
    down_or_top = 0;
  }
}
