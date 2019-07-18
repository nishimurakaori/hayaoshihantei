#include <Arduino.h>
/*#include "./audio_player.hpp"*/

#define BEATTIME 100 //音を出している時間(msec)
#define SPEAKER 3 //スピーカーの出力ピン番号


bool ring_buffer[5] = {false};
static const int MAX_RING_BUFFER = sizeof(ring_buffer) / sizeof(ring_buffer[0]);
int ring_buffer_index;

/*
AudioPlayer *g_player;
byte g_playerInstance[sizeof(AudioPlayer)];
*/

static const int MARU = 1;
static const int BATSU = 2;
static const int RESET = 0;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  
  pinMode(2, INPUT_PULLUP);
  //pinMode(3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  ring_buffer_index = 0;

}

void PushBuffer(bool v)
{
  ring_buffer[ring_buffer_index] = v;
  ring_buffer_index = (ring_buffer_index + 1) % MAX_RING_BUFFER;
}

bool IsPush()
{
  bool result = true;
  for(int i = 0; i < MAX_RING_BUFFER; i++){
    if (ring_buffer[i] == false) {
      result = false;
      break;
    }
  }
  return result;
}


void loop() {

  // put your main code here, to run repeatedly:
//  const bool val = digitalRead(2) == HIGH;
  const bool val = digitalRead(2) == LOW;

  Serial.println(val);
  
  PushBuffer(val);
  const int is_push = IsPush() ? HIGH : LOW;

//  Serial.println(val);
 // Serial.println((int)IsPush);
  
  if(is_push){
//    digitalWrite(2, LOW);
    digitalWrite(LED_BUILTIN, LOW);
//    g_player->play();

/*
    tone(SPEAKER,392,BEATTIME) ; // ソ
    delay(BEATTIME) ;
    tone(SPEAKER,330,BEATTIME) ; // ミ
    delay(BEATTIME) ;
    tone(SPEAKER,392,BEATTIME) ; // ソ
    delay(BEATTIME) ;
    tone(SPEAKER,330,BEATTIME) ; // ミ
    delay(BEATTIME) ;
    tone(SPEAKER,392,BEATTIME) ; // ソ
    delay(BEATTIME) ;
    tone(SPEAKER,330,500) ; // ミ
    delay(500) ;
 //   delay(300) ;
*/
    tone(SPEAKER,659,BEATTIME) ; // ミ
    delay(BEATTIME) ;
    tone(SPEAKER,523,BEATTIME) ; // ド
    delay(BEATTIME) ;
    tone(SPEAKER,659,BEATTIME) ; // ミ
    delay(BEATTIME) ;
    tone(SPEAKER,523,BEATTIME) ; // ド
    delay(BEATTIME) ;
    tone(SPEAKER,659,BEATTIME) ; // ミ
    delay(BEATTIME) ;
    tone(SPEAKER,523,500) ; // ド
    delay(500) ;
 
  }
  else {
  //  digitalWrite(2, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  delay(1);

}
