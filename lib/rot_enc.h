#define pinA 7
#define pinB 8
int encoderPosCount = 0;
int pinALast;
int aVal;
boolean bCW;

void set_rot_enc(){
  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
  pinALast = digitalRead(pinA);
  Serial.println("set rot");
}