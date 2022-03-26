#define rep(i,n) for (int i = 0;i < (int)n;i++)
#define echoPin1 A0 //前方
#define echoPin2 A1 //後方
#define trigPin A2
double duration1 = 0;
double distance1 = 0;
double duration2 = 0;
double distance2 = 0;
float res_distance1 = 0;
float res_distance2 = 0;


void set_ult_snc(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
}
float dis1(){
  rep(i,6) {
        rep(j,100) {
            digitalWrite(trigPin, LOW);
            digitalWrite(echoPin1, LOW);
            delayMicroseconds(1);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            duration1 = pulseIn(echoPin1, HIGH);
            res_distance1 += duration1 * 0.000001 * 34000 / 2;
        }
        digitalWrite(trigPin, LOW);
        digitalWrite(echoPin1, LOW);
        res_distance1 = res_distance1 * 0.01;//１００個の平均を取る
    }
    return res_distance1;
}
float dis2(){
  rep(i,6) {
        rep(j,100) {
            digitalWrite(trigPin, LOW);
            digitalWrite(echoPin2, LOW);
            delayMicroseconds(1);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            duration2 = pulseIn(echoPin2, HIGH);
            res_distance2 += duration2 * 0.000001 * 34000 / 2;
        }
        digitalWrite(trigPin, LOW);
        digitalWrite(echoPin2, LOW);
        res_distance2 = res_distance2 * 0.01;//１００個の平均を取る
    }
    return res_distance2;
}