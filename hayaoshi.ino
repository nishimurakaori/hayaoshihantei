#include <Arduino.h>
/*#include "./audio_player.hpp"*/

#define BEATTIME 100 //音を出している時間(msec)
#define SPEAKER 3 //スピーカーの出力ピン番号

#define MARU_INPUT 4
#define BATSU_INPUT 5
#define RESET_INPUT 6

#define RESET_OUTPUT 2


#define MARU 0
#define BATSU 1
#define RESET 2

bool ring_buffer[3][5] = {false};
static const int MAX_RING_BUFFER = sizeof(ring_buffer[0]) / sizeof(ring_buffer[0][0]);
int ring_buffer_index[3];

/*
AudioPlayer *g_player;
byte g_playerInstance[sizeof(AudioPlayer)];
*/



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  
  pinMode(MARU_INPUT, INPUT_PULLUP);
  
  //pinMode(3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  ring_buffer_index[MARU] = 0;
  ring_buffer_index[BATSU] = 0;
  ring_buffer_index[RESET] = 0;

}

void PushBuffer(int button, bool v)
{
  
  ring_buffer[button][ring_buffer_index[button]] = v;
  ring_buffer_index[button] = (ring_buffer_index[button] + 1) % MAX_RING_BUFFER;

  for(int i = 0; i < MAX_RING_BUFFER; i++){
    Serial.print(ring_buffer[MARU][i]);
  }
  Serial.println();
}

bool IsPush(int button)
{
  bool result = true;
  for(int i = 0; i < MAX_RING_BUFFER; i++){
    if (ring_buffer[button][i] == false) {
      result = false;
      break;
    }
  }
  return result;
}


void loop() {

  // put your main code here, to run repeatedly:
//  const bool val = digitalRead(2) == HIGH;
  const bool val_maru = digitalRead(MARU_INPUT) == LOW;

  //Serial.println(val_maru);
  
  PushBuffer(MARU, val_maru);
 // const int is_push = IsPush() ? HIGH : LOW;
  int is_push[3];
  is_push[MARU] = IsPush(MARU) ? HIGH : LOW;
  
  //Serial.println(is_push[MARU]);
  
  if(is_push[MARU]){
//    digitalWrite(2, LOW);
    digitalWrite(LED_BUILTIN, LOW);
//    g_player->play();


    tone(SPEAKER,784,BEATTIME) ; // ソ
    delay(BEATTIME) ;
    tone(SPEAKER,659,BEATTIME) ; // ミ
    delay(BEATTIME) ;
    tone(SPEAKER,784,BEATTIME) ; // ソ
    delay(BEATTIME) ;
    tone(SPEAKER,659,BEATTIME) ; // ミ
    delay(BEATTIME) ;
    tone(SPEAKER,784,BEATTIME) ; // ソ
    delay(BEATTIME) ;
    tone(SPEAKER,659,500) ; // ミ
    delay(500) ;
 //   delay(300) ;

/*
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
 */
  }
  else {
  //  digitalWrite(2, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  delay(1);

}
