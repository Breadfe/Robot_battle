#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN를 선언.
// set nRF24L01 at SPI bus by declare CE, CSN pin
RF24 radio(8,10);
//주소값을 5가지 문자열로 변경할 수 있으며, 송신기와 수신기가 동일한 주소로 해야됨.
// can set address in 5 length char, reciever and transmitter need to have same address
const byte address[6] = "13131";                                                                    
uint8_t sendBuf[4*8];
int r1 = A0;
int l1 = A1;
int r2 = A2;
int l2 = A3;
void makeSendbuf(float receiveDataPacket[], uint8_t sendBuf[]);
void setup() {
// put your setup code here, to run once:
//NRF24L01
radio.begin();
radio.openWritingPipe(address); //이전에 설정한 5글자 문자열인 데이터를 보낼 수신의 주소를 설정
radio.setPALevel(RF24_PA_MIN); //전원공급에 관한 파워레벨을 설정합니다. 모듈 사이가 가까우면 최소로 설정합니다.
radio.stopListening(); //모듈을 송신기로 설정
pinMode(r1, INPUT);
pinMode(l1, INPUT);
pinMode(r2, INPUT);
pinMode(l2, INPUT);
//Serial.begin(115200);
}
void loop() {
//NRF24L01 sending
int a = analogRead(r1);
int b = analogRead(l1);
int c = analogRead(r2);
int d = analogRead(l2);
int receiveDataPacket[8] = {a,b,c,d,0,0,0,0};//변수 최대 8개 전송가능(아두이노 성능에
//float receiveDataPacket[8] = {1,2,3,4,2,1,1,1};
makeSendbuf(receiveDataPacket, sendBuf);
radio.write(&sendBuf, sizeof(sendBuf));
//arduino 성능에 따라 delay조작
//delay(100);
// Serial.print(receiveDataPacket[0]);
// Serial.print("\t");
// Serial.print(receiveDataPacket[1]);
// Serial.print("\t");
// Serial.print(receiveDataPacket[2]);
// Serial.print("\t");
// Serial.println(receiveDataPacket[3]);
}
void makeSendbuf(int receiveDataPacket[], uint8_t sendBuf[])
{
sendBuf[0] = int(receiveDataPacket[0]) & 0xFF;
sendBuf[1] = (int(receiveDataPacket[0]) >> 8) & 0xFF;
sendBuf[2] = (int(receiveDataPacket[0]) >> 16) & 0xFF;
sendBuf[3] = (int(receiveDataPacket[0]) >> 24) & 0xFF;
sendBuf[4] = int(receiveDataPacket[1]) & 0xFF;
sendBuf[5] = (int(receiveDataPacket[1]) >> 8) & 0xFF;
sendBuf[6] = (int(receiveDataPacket[1]) >> 16) & 0xFF;
sendBuf[7] = (int(receiveDataPacket[1]) >> 24) & 0xFF;
sendBuf[8] = int(receiveDataPacket[2]) & 0xFF;
sendBuf[9] = (int(receiveDataPacket[2]) >> 8) & 0xFF;
sendBuf[10] = (int(receiveDataPacket[2]) >> 16) & 0xFF;
sendBuf[11] = (int(receiveDataPacket[2]) >> 24) & 0xFF;
sendBuf[12] = int(receiveDataPacket[3]) & 0xFF;
sendBuf[13] = (int(receiveDataPacket[3]) >> 8) & 0xFF;
sendBuf[14] = (int(receiveDataPacket[3]) >> 16) & 0xFF;
sendBuf[15] = (int(receiveDataPacket[3]) >> 24) & 0xFF;
sendBuf[16] = int(receiveDataPacket[4]) & 0xFF;
sendBuf[17] = (int(receiveDataPacket[4]) >> 8) & 0xFF;
sendBuf[18] = (int(receiveDataPacket[4]) >> 16) & 0xFF;
sendBuf[19] = (int(receiveDataPacket[4]) >> 24) & 0xFF;
sendBuf[20] = int(receiveDataPacket[5]) & 0xFF;
sendBuf[21] = (int(receiveDataPacket[5]) >> 8) & 0xFF;
sendBuf[22] = (int(receiveDataPacket[5]) >> 16) & 0xFF;
sendBuf[23] = (int(receiveDataPacket[5]) >> 24) & 0xFF;
sendBuf[24] = int(receiveDataPacket[6]) & 0xFF;
sendBuf[25] = (int(receiveDataPacket[6]) >> 8) & 0xFF;
sendBuf[26] = (int(receiveDataPacket[6]) >> 16) & 0xFF;
sendBuf[27] = (int(receiveDataPacket[6]) >> 24) & 0xFF;
sendBuf[28] = int(receiveDataPacket[7]) & 0xFF;
sendBuf[29] = (int(receiveDataPacket[7]) >> 8) & 0xFF;
sendBuf[30] = (int(receiveDataPacket[7]) >> 16) & 0xFF;
sendBuf[31] = (int(receiveDataPacket[7]) >> 24) & 0xFF;
}
