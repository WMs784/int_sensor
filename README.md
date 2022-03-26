# arduino_uno

## Pin Number
echoPin1 = A0　前方距離センサ
echoPin2 = A1　後方距離センサ
trigPin = A2　距離センサ
LED = A3　
PWMa = A4　モータaのPWM
PWMb = A3　モータbのPWM
motor11 = 2  
motor12 = 3
SD_ChipSelectPin = 4; SDカードのチップセレクト
motor22 = 5
motor21 = 6
pinA = 7　ロータリーエンコーダーのCLK
pinB = 8　ロータリーエンコーダーのDT
SV_PIN = 9　サーボモータ
SD…11,12,13　SDカード

## Memo
- 旋回があまり上手くできない(磁気センサの応答性の問題？)
- 角度-179~180で扱う mod_theta()を利用
- 角位置センサは不使用
