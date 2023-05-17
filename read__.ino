//RF24_config 파일에 spi_speed 8000000으로 수정
#include <SPI.h>
#include <Servo.h>
#include <nRF24L01.h>
#include <RF24.h>
int right_1 = 7;
int right_2 = 4;
int left_1 = 0;
int left_2 = 1;
int LPWM=3;
int LENA=2;
int RPWM=6;
int RENA=5;

Servo servo;
RF24 radio(8,10); // SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN 선언.
const byte address[6] = "13131"; //주소값을 5가지 문자열로 변경할 수 있으며, 송신기과 수신기가 동일한 주소로 해야됨.
void Readdata(int receiveDataPacket[], uint8_t readBuf[]);
void move_right();
void move_left();
void move_foward();
void move_backward();

void setup() {
//Serial.begin(115200);
radio.begin();
radio.openReadingPipe(0, address);
radio.setPALevel(RF24_PA_MIN); //전원공급에 관한 파워레벨을 설정합니다. 모듈 사이가 가까우면 최소로 설정합니다.
servo.attach(2);
pinMode(right_1, OUTPUT);
pinMode(right_2, OUTPUT);
pinMode(left_1, OUTPUT);
pinMode(left_2, OUTPUT);
pinMode(LENA,OUTPUT);
pinMode(LPWM,OUTPUT);
pinMode(RENA,OUTPUT);
pinMode(RPWM,OUTPUT);
//거리가 가까운 순으로 RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX 등으로 설정할 수 있습니다.
//높은 레벨(거리가 먼 경우)은 작동하는 동안 안정적인 전압을 가지도록 GND와 3.3V에 바이패스 커패시터 사용을 권장함
radio.startListening(); //모듈을 수신기로 설정
}
unsigned long current = 0;
unsigned long before = 0;
uint8_t readBuf[4*8];
int receiveDataPacket[8] = {0,};
int state = 0;

void loop() {
digitalWrite(LENA,LOW);
digitalWrite(LPWM,HIGH);
digitalWrite(RENA,LOW);
digitalWrite(RPWM,HIGH);
current = millis();
if (radio.available()) {
radio.read(&readBuf, sizeof(readBuf));
Readdata(receiveDataPacket, readBuf);
//100밀리초마다 출력
//if(current - before > 100)
//{
//for(int i = 0; i < 8; i++)
//{
//Serial.print(receiveDataPacket[i]);
//Serial.print("\t");
//}
//Serial.println(" ");
//before = current;
//}
}
//Serial.println("don't work");
int foward_backward_sign = receiveDataPacket[0];//map(int(receiveDataPacket[3]), 0, 1023, -2,2);
int right_left_sign = receiveDataPacket[1];//map(int(receiveDataPacket[2]), 0, 1023, -2,2);
// int angle = map(receiveDataPacket[1], 0, 1023, 15, 90);
// servo.write(angle);

if(foward_backward_sign < 300)
  move_backward();
else if(foward_backward_sign > 600)
  move_foward();
  
else if(right_left_sign < 300)
  move_left();
else if(right_left_sign > 600)
  move_right();
  
else
  move_stop();
}



void move_foward()
{
digitalWrite(right_1, LOW);
digitalWrite(right_2, HIGH);
digitalWrite(left_1, LOW);
digitalWrite(left_2, HIGH);
}
void move_left()
{
digitalWrite(right_1, HIGH);
digitalWrite(right_2, LOW);
digitalWrite(left_1, LOW);
digitalWrite(left_2, HIGH);
}
void move_right()
{
digitalWrite(right_1, LOW);
digitalWrite(right_2, HIGH);
digitalWrite(left_1, HIGH);
digitalWrite(left_2, LOW);
}
void move_backward()
{
digitalWrite(right_1, HIGH);
digitalWrite(right_2, LOW);
digitalWrite(left_1, HIGH);
digitalWrite(left_2, LOW);
}
void move_stop()
{
digitalWrite(right_1, LOW);
digitalWrite(right_2, LOW);
digitalWrite(left_1, LOW);
digitalWrite(left_2, LOW);
}
void Readdata(int receiveDataPacket[], uint8_t readBuf[])
{
int data[8] = {0,};
data[0] += readBuf[0];
data[0] += readBuf[1] << 8;
data[0] += readBuf[2] << 16;
data[0] += readBuf[3] << 24;
data[1] += readBuf[4];
data[1] += readBuf[5] << 8;
data[1] += readBuf[6] << 16;
data[1] += readBuf[7] << 24;
data[2] += readBuf[8];
data[2] += readBuf[9] << 8;
data[2] += readBuf[10] << 16;
data[2] += readBuf[11] << 24;
data[3] += readBuf[12];
data[3] += readBuf[13] << 8;
data[3] += readBuf[14] << 16;
data[3] += readBuf[15] << 24;
data[4] += readBuf[16];
data[4] += readBuf[17] << 8;
data[4] += readBuf[18] << 16;
data[4] += readBuf[19] << 24;
data[5] += readBuf[20];
data[5] += readBuf[21] << 8;
data[5] += readBuf[22] << 16;
data[5] += readBuf[23] << 24;
data[6] += readBuf[24];
data[6] += readBuf[25] << 8;
data[6] += readBuf[26] << 16;
data[6] += readBuf[27] << 24;
data[7] += readBuf[28];
data[7] += readBuf[29] << 8;
data[7] += readBuf[30] << 16;
data[7] += readBuf[31] << 24;
for(int i = 0; i < 8; i++)
receiveDataPacket[i] = data[i];
}
