#include "ArduinoSTL.h" 
#include "vector"
#include "iostream"
#include "string"
#include "queue"
#include "sensor.h"

#define rep(i,n) for(short int i = 0;i <(short int)n;i++)
#define sint short int

using namespace std;

#define length 20 //地図の縦の長さ
#define width 10 //地図の横の長さ
#define det_dis 10 //障害物の幅(排除する円領域の半径)
char cur_x = length/2, cur_y = width/2;//初期の現在地，これはどうしよう
char tg_x = 0,tg_y = 0;//移動目標値
char field_map[length][width];//障害物記録用の地図
const sint dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};
bool seen[length][width];
queue<sint> que;
//↑経路探索に使う奴ら

//map 0:障害物なし,1:未探査,2:障害物あり 

void set_map(float r,float theta){
    sint x = cur_x + r*sin(theta), y = cur_y + r*cos(theta);
    // cout << x << ' ' << y << endl;
    rep(i,length){
        rep(j,width){
            if(field_map[i][j] == 2)continue;
            if((i-x)*(i-x) + (j-y)*(j-y) < 10) field_map[i][j] = 2;
            else if((cur_x-i)*(cur_x-i) + (cur_y-j)*(cur_y-j) < det_dis*det_dis && field_map[i][j] != 2)field_map[i][j] = 0;
        }
    }
}
sint bfs(){
    while (!que.empty()){
        sint xy = que.front();
        // cout << xy << ' ';
        que.pop();
        sint x = xy/100,y = xy%100;
        seen[x][y] = true;
        rep(dir,4){
            sint xd = x + dx[dir], yd = y + dy[dir];
            if(xd < 0 || xd >= length || yd < 0 || yd >= width)continue;
            if(field_map[xd][yd] == 2)continue;
            if(seen[xd][yd])continue;
            que.push(100*xd+yd);
            seen[xd][yd] = true;
            if(field_map[xd][yd] == 1){
                return xd*100+yd;
            }
        }
    }
    return 9999;
}

float move_dis(sint cur,sint goal){
    if(goal == 9999)return 0;
    else{
        float cx = cur/100,cy = cur%100;
        float gx = goal/100,gy = goal%100;
        float r = sqrt((cx-gx)*(cx-gx)+(cy-gy)*(cy-gy));
        return r;
    }
}
float move_deg(sint cur,sint goal){
    if(goal == 9999)return 0;
    else{
        float cx = cur/100,cy = cur%100;
        float gx = goal/100,gy = goal%100;
        float r = sqrt((cx-gx)*(cx-gx)+(cy-gy)*(cy-gy));
        float t = (cx-gx)/(cy-gy);
        cout << t << endl;
        float theta = atan(t);
        return theta;
    }
}

void scan(){
    float r1 = 10.0,r2 = 10.0, theta1 = 30.0, theta2 = 30.0;//超音波センサから取得した値が入る
    sint div = 15;
    delay(100);
    sint init_div = dummy_qmc();
    rep(i,180/div){
        delay(100);
        sint cur_div = dummy_qmc();
        Serial.print(i);
        Serial.println(" times search");
        delay(1000);
        div = init_div + 15*(i+1) - cur_div;
        Serial.println(div);
        right_rotate(div);//回転
        digitalWrite(WHITE, HIGH);//計算&計測を始めたらLEDを点灯
        delay(1000);
        r1 = dis1();//前の超音波センサから値を取得
        Serial.println(r1);
        set_map(r1,i*div);
        r2 = dis2();//後ろの超音波センサから値を取得
        Serial.println(r2);
        set_map(r2,i*div+180);
        digitalWrite(WHITE, LOW);//計算終了後LED消灯
    }
    que.push(100*cur_x+cur_y);
    cout << bfs() << endl;
    rep(i,length){//経路探査用地図の中身を見る
        rep(j,width)Serial.print(seen[i][j]);
    }
    rep(i,length){//障害物記録用地図の中身を見る
        rep(j,width)Serial.print(field_map[i][j]);
    }
    sint cur = cur_x*100+cur_y;
    right_rotate(move_deg(cur,find()));
    myservo.write(0);   
    straight(move_dis(cur,find()));
}

sint find(){//次の移動場所を返す関数
   rep(i,length-10){
       rep(j,width-10){
           bool b = true;
           rep(k,10){
               if(!b)break;
               rep(l,10){
                   if(field_map[i+k][j+l] != 0){
                       b = false;
                       break;
                   }
               }
           }
           if(b)return (i+5)*100+(j+5);
       }
   }
   return (rand()%20)*100+rand()%20;//移動したい場所が見つからない場合はランダムで生成
}

void setup() {
  Serial.begin(9600);
  setup_sensors();
  Serial.println("complete setup sensors");
}

void loop() {
  digitalWrite(BLUE, HIGH);
  myservo.write(0);     //プーリー下げる
//   straight(10);         //直進
//   digitalWrite(WHITE, LOW);
//   digitalWrite(WHITE, HIGH);
  delay(1000);
  digitalWrite(BLUE, LOW);
  myservo.write(70);    //プーリー上げる
  delay(1000);
  Serial.println("start search");
  scan();
//   digitalWrite(WHITE, LOW);
//   int time = millis();
//   Serial.println(time);
//   delay(1000);
//   sint goal = find();
//   int time2 = millis();
//   digitalWrite(WHITE, HIGH);
//   Serial.println(goal);
//   delay(1000);
//   digitalWrite(WHITE, LOW);
//   Serial.println(time2);
//   Serial.println(dis1());
// ↑色々試したやつら
}
