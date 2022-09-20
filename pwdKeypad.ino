#include <LiquidCrystal.h>
#include <Keypad.h>

// 定义LCD的引脚
// LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
// 定义键盘map，考虑运算符的按键
const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {' ', '0', '=', '+'} // 用空格表示ON/C按键
};
byte rowPins[rows] = {3, 2, A5, A4};
byte colPins[cols] = {A3, A2, A1, A0};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

String inputKey = "";
// REPLACE YOUR STUDENT ID HERE.
String pwd = "0000"; // my password


void setup() {
  pinMode(11, OUTPUT); // IO11, PB3, PIN11，控制绿灯
  pinMode(10, OUTPUT); // IO10, PB2, PIN10，控制红灯
  pinMode(12, OUTPUT); // IO12, PB4, PIN12，继电器和黄灯
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(12, LOW);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (!key){
    return;
  }
  Serial.println(key);
  lcd.clear(); // 每次输入就刷新一下吧
  if (key == ' '){
    // 题目没要求的，这个IF删了也行
    inputKey = "";
    return;
  }
  inputKey += key;
  lcd.print(String(inputKey));
  if (inputKey.length() == 4){
    Serial.println(String(inputKey));
    Serial.println(pwd);
    inputKey.trim();
    Serial.println(inputKey == pwd);
    if (inputKey == pwd){
      // 密码正确
      lcd.setCursor(0, 1);
      lcd.print("OPEN");
      Serial.println("OPEN");
      digitalWrite(11, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(12, HIGH);
    }
    else {
      // 密码错误
      lcd.setCursor(0,1);
      lcd.print("INVALID");
      Serial.println("INVALID");
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(12, LOW);
    }
    inputKey = "";
  }
}
