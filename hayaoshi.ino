bool ring_buffer[5] = {false};
static const int MAX_RING_BUFFER = sizeof(ring_buffer) / sizeof(ring_buffer[0]);
int ring_buffer_index;

static const int MARU = 0;
static const int BATSU = 0;
static const int RESET = 0;


void setup() {
  // put your setup code here, to run once:
//Serial.begin(9600);
  
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
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
  const bool val = digitalRead(3) == HIGH;
  PushBuffer(val);
  const int is_push = IsPush() ? HIGH : LOW;

//  Serial.println(val);
  
  if(is_push){
    digitalWrite(2, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    digitalWrite(2, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  delay(1);

}
