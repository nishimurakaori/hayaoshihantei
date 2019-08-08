#include <Arduino.h>

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


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  
  pinMode(MARU_INPUT, INPUT_PULLUP);
  pinMode(BATSU_INPUT, INPUT_PULLUP);
  pinMode(RESET_INPUT, INPUT_PULLUP);
  
  pinMode(RESET_OUTPUT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  ring_buffer_index[MARU] = 0;
  ring_buffer_index[BATSU] = 0;
  ring_buffer_index[RESET] = 0;
}

void PushBuffer(int button, bool v)
{
  ring_buffer[button][ring_buffer_index[button]] = v;
  ring_buffer_index[button] = (ring_buffer_index[button] + 1) % MAX_RING_BUFFER;

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
  const bool val_maru = digitalRead(MARU_INPUT) == LOW;
  const bool val_batsu = digitalRead(BATSU_INPUT) == LOW;
  const bool val_reset = digitalRead(RESET_INPUT) == LOW;

  //Serial.println(val_batsu);
  
  PushBuffer(MARU, val_maru);
  PushBuffer(BATSU, val_batsu);
  PushBuffer(RESET, val_reset);
  int is_push[3];
  is_push[MARU] = IsPush(MARU) ? HIGH : LOW;
  is_push[BATSU] = IsPush(BATSU) ? HIGH : LOW;
  is_push[RESET] = IsPush(RESET) ? HIGH : LOW;
  
  //Serial.println(is_push[BATSU]);
  
  if(is_push[MARU]){
    digitalWrite(RESET_OUTPUT, HIGH);
    digitalWrite(LED_BUILTIN, LOW);

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
  }
  
  else if (is_push[BATSU]){
    digitalWrite(RESET_OUTPUT, HIGH);
    tone(SPEAKER,277,200) ; // ド＃
    delay(200) ;

  }
  else if (is_push[RESET]){
    digitalWrite(RESET_OUTPUT, HIGH);
  }

  else {
    digitalWrite(RESET_OUTPUT, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  delay(1);

}
