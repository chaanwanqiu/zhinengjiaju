#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;

#include "audio.h"
struct config_type
{
  int EEPROM_music_num;       //歌曲的数目
  int EEPROM_music_vol;       //歌曲的音量
};


int music2_Pin = 6;//按键控制引脚定义

boolean play_pause;
boolean play_change;//定义boolean型变量
int music_num = 1;    //歌曲序号


#include <Microduino_ColorLED.h> //引用彩灯

#define PIN 12   //led灯控制引脚
#define NUMPIXELS      2        //级联彩灯数量
#define  sensorPinh  SDA
#define  sensorPing  A0
int stateh, stateg;
ColorLED strip = ColorLED(NUMPIXELS, PIN); //将ColorLED类命名为strip，并定义彩灯数量和彩灯引脚号


#define servo_pin1 10
#define servo_pin2 8
#define servo_pin3 9

int angle = 0;


#include <ESP8266.h>

#ifdef ESP32
#error "This code is not recommended t························· o run on the ESP32 platform! Please check your Tools->Board setting."
#endif

/**
**CoreUSB UART Port: [Serial1] [D0,D1]
**Core+ UART Port: [Serial1] [D2,D3]
**/
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined (__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define EspSerial Serial1
#define UARTSPEED  115200
#endif

/**
**Core UART Port: [SoftSerial] [D2,D3]
**/
#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial1(2, 3); /* RX:D2, TX:D3 */

#define EspSerial mySerial1
#define UARTSPEED  9600
#endif

#define SSID        F("wang")
#define PASSWORD    F("wanganyi")
#define HOST_NAME   F("api.heclouds.com")
#define HOST_PORT   (80)
#define DEVICEID    "504601808" //OneNet上的设备ID
String apiKey = "imjcKhEeN09X9dxi6T1aqCmPltg=";
String jsonToSend;
String postString;



char shijian1[23] = {'0'}, shijian2[23] = {'0'};



static const byte  GETDATA[]  PROGMEM = {
  "GET https://api.heclouds.com/devices/504601808/datapoints?datastream_id=kongtiao&limit=1 HTTP/1.1\r\nHost:api.heclouds.com\r\napi-key:imjcKhEeN09X9dxi6T1aqCmPltg=\r\nConnection: close\r\n\r\n"
};

ESP8266 wifi(&EspSerial);

void setup(void)
{
  strip.begin();
  strip.setBrightness(60);       //设置彩灯亮度
  strip.show();
  pinMode(sensorPinh, INPUT);
  pinMode(sensorPing, INPUT);
  pinMode(servo_pin1, OUTPUT);
  pinMode(servo_pin2, OUTPUT);
  pinMode(servo_pin3, OUTPUT);
  //  myservo1.attach(servo_pin1);
  //  myservo2.attach(servo_pin2);
  //  myservo3.attach(servo_pin3);
  //  myservo1.detach();
  Serial.begin(9600);


  pinMode(music2_Pin, INPUT);


  audio_pause();

  audio_init(DEVICE_Flash, MODE_loopOne, 9);




  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.print(F("setup begin\r\n"));
  delay(100);




  WifiInit(EspSerial, UARTSPEED);

  Serial.print(F("FW Version:"));
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print(F("to station + softap ok\r\n"));
  } else {
    Serial.print(F("to station + softap err\r\n"));
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print(F("Join AP success\r\n"));

    Serial.print(F("IP:"));
    Serial.println( wifi.getLocalIP().c_str());
  } else {
    Serial.print(F("Join AP failure\r\n"));
  }

  if (wifi.disableMUX()) {
    Serial.print(F("single ok\r\n"));
  } else {
    Serial.print(F("single err\r\n"));
  }

  Serial.print(F("setup end\r\n"));
}

void loop(void)
{
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print(F("create tcp ok\r\n"));
  } else {
    Serial.print(F("create tcp err\r\n"));
  }

  //char *hello = "GET /testwifi/index.html HTTP/1.0\r\nHost: www.adafruit.com\r\nConnection: close\r\n\r\n";
  //wifi.send((const uint8_t*)hello, strlen(hello));  //直接发送

  wifi.sendFromFlash(GETDATA, sizeof(GETDATA)); //从Flash读取发送内容，节约内存
  char a = '0';
  uint8_t buffer[512] = {0};
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 20000);
  if (len > 0) {
    Serial.print(F("Received:["));
    for (uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print(F("]\r\n"));

    for (uint32_t i = 0; i < len - 12; i++) {
      if ((char)buffer[i] == 'v' && (char)buffer[i + 1] == 'a' && (char)buffer[i + 2] == 'l' && (char)buffer[i + 3] == 'u' && (char)buffer[i + 4] == 'e')
      {

        a = buffer[i + 8];
      }
    }

    for (uint32_t i = 0; i < len ; i++) {
      if ((char)buffer[i - 1] == '"' && (char)buffer[i] == 'a' && (char)buffer[i + 1] == 't' && (char)buffer[i + 2] == '"' && (char)buffer[i + 3] == ':')
      {
        for (int j = 0; j < 23; j++)
        { shijian1[j] = buffer[i + 5 + j];
          Serial.print((char)shijian1[j]);
        }
      }
    }
    int sum = 0;
    for (int j = 0; j < 22; j++)
    {
      if (shijian1[j] != shijian2[j])
        sum++;
    }
    if (sum == 0)
      a = '0';


    Serial.print(F("]\r\n"));
  }

  if (wifi.releaseTCP()) {
    Serial.print(F("release tcp ok\r\n"));
  } else {
    Serial.print(F("release tcp err\r\n"));
  }
  Serial.println(a);






  //控制空调
  if (a == '1')
  {
    angle = 180;
    myservo1.attach(servo_pin1);
    myservo1.write(angle);

    delay(1000);
    angle = 0;

    myservo1.write(angle);
    delay(1000);
    myservo1.detach();

  }
  //控制加湿器
  if (a == '2')
  {
    angle = 180;
    myservo2.attach(servo_pin2);
    myservo2.write(angle);
    delay(1000);
    angle = 0;
    myservo2.write(angle);
    delay(1000);
    myservo2.detach();

  }


  if (a == '3') //辅助开灯
  {
    stateh = digitalRead(sensorPinh);
    Serial.print("stateh:");
    Serial.println(stateh);
    stateg = analogRead(sensorPing);
    Serial.print("stateg:");
    Serial.println(stateg);
    if ((stateh == 1) && (stateg < 250))
    {
      strip.setPixelColor(0, strip.Color(255, 255, 255));
      strip.show();
      delay(1000);
    }
    else
    {
      strip.setPixelColor(0, strip.Color(0, 0, 0));//灭
      strip.show();
      delay(1000);
    }
  }


  if (a == '4') //手动开灯
  {
    strip.setPixelColor(0, strip.Color(255, 255, 255));
    strip.show();
    delay(1000);
  }
  if (a == '5') //手动关灯
  {
    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    delay(1000);
  }

  if (a == '6')//自动开窗
  {
    angle = 180;
    myservo3.attach(servo_pin3);
    myservo3.write(angle);
    delay(1000);
    myservo3.detach();

  }


  if (a == '7')//自动关窗
  {
    angle = 90;
    myservo3.attach(servo_pin3);
    myservo3.write(angle);
    delay(1000);
    myservo3.detach();

  }


  if (a == '8')
  {
    audio_play();
  }
  if (a == 'a')
  {
    audio_pause();
  }
  if (a == 'b')
  {
    music_num++;  //歌曲序号加
    if (music_num > 9)  //限制歌曲序号范围，如果歌曲序号大于9
    {
      music_num = 1; //歌曲序号返回1
    }
    audio_choose(music_num);
    audio_play();

  }
  delay(1000);

  for (int j = 0; j < 23; j++)
  { shijian2[j] = shijian1[j];
    Serial.print((char)shijian2[j]);
  }
}








