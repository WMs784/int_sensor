// #define motor11 3
// #define motor12 4
// #define motor21 5
// #define motor22 6

// void set_dcm(){
//   pinMode(motor11, OUTPUT);
//   pinMode(motor12, OUTPUT);
//   pinMode(motor21, OUTPUT);
//   pinMode(motor22, OUTPUT);
// }
#define motor11 2
#define motor12 3
#define motor21 6
#define motor22 5
#define PWMa A4
#define PWMb A3
#define pinA 7
#define pinB 8
// #define echoPin1 = A0; //前方
// #define echoPin2 = A1; //後方
// #define trigPin = A2;
// double duration1 = 0;
// double distance1 = 0;
// double duration2 = 0;
// double distance2 = 0;

// void setup_ultrasonic() {
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin1, INPUT);
//   pinMode(echoPin2, INPUT);
// }

// float ultrasonic1() {
//    for ( int j = 0; j < 100; j++) {
//       digitalWrite(trigPin, LOW);
//       digitalWrite(echoPin1, LOW);
//       delayMicroseconds(1);
//       digitalWrite(trigPin, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(trigPin, LOW);
//       duration1 = pulseIn(echoPin1, HIGH);
//       distance1 += duration1 * 0.000001 * 34000 / 2;
//     }
//     digitalWrite(trigPin, LOW);
//     digitalWrite(echoPin1, LOW);
//     distance1 = distance1 * 0.01;
//     return distance1;
// }

// float ultrasonic2() {
//    for ( int j = 0; j < 100; j++) {
//       digitalWrite(trigPin, LOW);
//       digitalWrite(echoPin2, LOW);
//       delayMicroseconds(1);
//       digitalWrite(trigPin, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(trigPin, LOW);
//       duration1 = pulseIn(echoPin2, HIGH);
//       distance1 += duration1 * 0.000001 * 34000 / 2;
//     }
//     digitalWrite(trigPin, LOW);
//     digitalWrite(echoPin2, LOW);
//     distance2 = distance2 * 0.01;
//     return distance2;
// }
void setup_motor() {
  pinMode(motor11, OUTPUT);
  pinMode(motor12, OUTPUT);
  pinMode(motor21, OUTPUT);
  pinMode(motor22, OUTPUT);
  pinMode(PWMa, OUTPUT);
  pinMode(PWMb, OUTPUT);
  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
}

void straight( int l ) {
  int encoderPosCount = 0;
  int pinALast = digitalRead(pinA);
  int aVal;
  digitalWrite(motor11, LOW);
  digitalWrite(motor22, LOW);
  digitalWrite(motor12, HIGH);
  digitalWrite(motor21, HIGH);
  analogWrite( PWMb, 249 );
  analogWrite( PWMa, 254 );

  while (-encoderPosCount < l * 40 / 15.707) {
    // if (ultrasonic1() < 10) {
      aVal = digitalRead(pinA);
      if (aVal != pinALast) {
        //回ってたらピンAの値が変わるためエンコーダーの値を増やす
        if (digitalRead(pinB) != aVal) {
          //ピンBで前進後退を判断
          encoderPosCount ++;
        }
        else {
          encoderPosCount--;
        }
      }
      pinALast = aVal;
    // }
    // else{
    //   Serial.print("error");
    // }
  }
  digitalWrite(motor12, LOW);
  digitalWrite(motor21, LOW);
}

// void setup(){
// Serial.begin( 9600 );
// setup_ultrasonic();
// setup_motor();
// }

// void loop(){
//   straight( 1 );
//   Serial.print("前方");
//   Serial.println(ultrasonic1());
//   Serial.print("後方");
//   Serial.println(ultrasonic2());
// }