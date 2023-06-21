#include <Servo.h>                     //舵机库
#include <SoftwareSerial.h>            //软串口库
// A4（扩展板上SDA）为RX，接语音识别模块的TXD
// A5（扩展板上SCL）为TX，接语音识别模块的RXD
SoftwareSerial softSerial(A4, A5);//定义软串口，避免与主串口冲突

Servo myservo1;                        //定义舵机1
Servo myservo2;                        //定义舵机2
Servo myservo3;                        //定义舵机3
Servo myservo4;                        //定义舵机4

int val;

//定义舵机管脚
int ms1 = 4;                            //可回收垃圾-舵机1
int ms2 = 5;                            //厨余垃圾-舵机2
int ms3 = 6;                           //有害垃圾-舵机3
int ms4 = 7;                           //其他垃圾-舵机4

void setup() {
  // 初始化串口
  Serial.begin(9600);
  softSerial.begin(9600);

  // 初始化舵机，复位
  myservo1.attach(ms1);
  myservo2.attach(ms2);
  myservo3.attach(ms3);
  myservo4.attach(ms4);
  myservo1.write(90);
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(90);
  delay(200);
  //释放,以解决多个舵机抖动
  myservo1.detach();
  myservo2.detach();
  myservo3.detach();
  myservo4.detach();

  Serial.println("初始化完成，请开始使用。");
}

//可回收垃圾桶盖开关
void khslj()
{
  ServoAction(1);//开盖，合盖动作
}

//厨余垃圾桶盖开关
void cylj()
{
  ServoAction(2);//开盖，合盖动作
}

//有害垃圾桶盖开关
void yhlj()
{
  ServoAction(3);//开盖，合盖动作
}

//其他垃圾桶盖开关
void qtlj()
{
  ServoAction(4);//开盖，合盖动作
}



//开盖，合盖动作函数
void ServoAction(int servo_num)
{
  switch (servo_num) {
    case 1:
      myservo1.attach(ms1);
      myservo1.write(90);
      delay(100);
      //打开盖  舵机打开转向角度
      for (int jiao = 90; jiao > 0; jiao = jiao - 1)
      {
        myservo1.write(jiao);
        delay(5);
      }
      //延时2秒
      delay(2000);
      Serial.println("可回收垃圾桶");
      Serial.println("开");

      //合上盖 舵机合上转向角度
      myservo1.write(90);
      delay(500);
      Serial.println("合ok");

      //释放,以解决多个舵机抖动
      myservo1.detach();
      break;
    case 2:
      myservo2.attach(ms2);
      myservo2.write(90);
      delay(100);
      //打开盖  舵机打开转向角度
      for (int jiao = 90; jiao > 0; jiao = jiao - 1)
      {
        myservo2.write(jiao);
        delay(5);
      }
      //延时2秒
      delay(2000);
      Serial.println("厨余垃圾桶");
      Serial.println("开");

      //合上盖 舵机合上转向角度
      myservo2.write(90);
      delay(500);
      Serial.println("合ok");

      //释放,以解决多个舵机抖动
      myservo2.detach();
      break;
    case 3:
      myservo3.attach(ms3);
      myservo3.write(90);
      delay(100);
      //打开盖  舵机打开转向角度
      for (int jiao = 90; jiao > 0; jiao = jiao - 1)
      {
        myservo3.write(jiao);
        delay(5);
      }
      //延时2秒
      delay(2000);
      Serial.println("有害垃圾桶");
      Serial.println("开");

      //合上盖 舵机合上转向角度
      myservo3.write(90);
      delay(500);
      Serial.println("合ok");

      //释放,以解决多个舵机抖动
      myservo3.detach();
      break;
    case 4:
      myservo4.attach(ms4);
      myservo4.write(90);
      delay(100);
      //打开盖  舵机打开转向角度
      for (int jiao = 90; jiao > 0; jiao = jiao - 1)
      {
        myservo4.write(jiao);
        delay(5);
      }
      //延时2秒
      delay(2000);
      Serial.println("其他垃圾桶");
      Serial.println("开");

      //合上盖 舵机合上转向角度
      myservo4.write(90);
      delay(500);
      Serial.println("合ok");

      //释放,以解决多个舵机抖动
      myservo4.detach();
      break;
    default: break;
  }
}


//把十进制转换为十六进制

char  buffer [2];
char  * inttohex( int  aa)
{
  sprintf (buffer, "%x" , aa);
  return  (buffer);
}


void loop()
{

  if (softSerial.available() > 0)
  {
    val = softSerial.read();//从软串口获得数据

    //从串口读取语音识别模块的数据，语音识别设置是发送十六进制数据，
    //arduino通过串口读出的数据的是十进制数，以下是对应关系。
    //十进制16对应十六进制是10,  唤醒语
    //十进制17对应十六进制是11,  可回收垃圾
    //十进制18对应十六进制是12,  厨余垃圾
    //十进制19对应十六进制是13,  有害垃圾
    //十进制20对应十六进制是14,  其他垃圾


    if (val == 16)
    {
      Serial.println("-----------------------------------");
      Serial.print("口令唤醒：");
      Serial.println(inttohex(val));//从主串口输出语音模块十六进制数据，便于查看
    }

    if (val == 17)
    {
      Serial.print("分类：");
      Serial.println(inttohex(val));//从主串口输出语音模块十六进制数据，便于查看
      delay(1500);
      khslj();//调用可回收垃圾桶盖开关
    }


    if (val == 18)
    {
      Serial.print("分类：");
      Serial.println(inttohex(val));//从主串口输出语音模块十六进制数据，便于查看
      delay(1500);
      cylj();//调用厨余垃圾桶盖开关
    }


    if (val == 19)
    {
      Serial.print("分类：");
      Serial.println(inttohex(val));//从主串口输出语音模块十六进制数据，便于查看
      delay(1500);
      yhlj();//调用有害垃圾桶盖开关
    }


    if (val == 20)
    {
      Serial.print("分类：");
      Serial.println(inttohex(val));//从主串口输出语音模块十六进制数据，便于查看
      delay(1500);
      qtlj();//调用其他垃圾桶盖开关
    }

  }

}
