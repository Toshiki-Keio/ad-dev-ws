/*******************************
  モータドライバ　動作モード
  　　|FIN |RIN | OUT1 | OUT2 | 動作
  ①  | L  | L  | OPEN | OPEN | スタンバイ
  ②  | H  | L  | High | Low  | OUT1→OUT2
  ③  | L  | H  | Low  | High | OUT2→OUT1
  ④  | H  | H  | High | High | ブレーキ

  ②⇔④ を交互に行い前進の速度調整　(②が多い:高速,　④が多い:低速) 0が最速　120以上は駆動力不足
  ③⇔④ を交互に行い後退の速度調整　(③が多い:高速,　④が多い:低速)
 *******************************/

// モータドライバに信号を送るArduinoのピン番号を格納する定数
#define RP 9    //定数RPを9に置き換える
#define RN 10   //定数RNを10に置き換える
#define LP 11   //定数LPを11に置き換える
#define LN 13   //定数LNを13に置き換える

// センサー読み取り値格納用変数
int s1, s2, s3, s4, s5, s6;

// setup()内のプログラムは最初に一回のみ実行される
// 初期設定を記述
void setup() {
	// ArduinoのA0～A5番ピンを入力に設定
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(A4, INPUT);
	pinMode(A5, INPUT);

	// Arduinoの9,10,11,13番ピンを出力に設定
	pinMode(RP, OUTPUT);
	pinMode(RN, OUTPUT);
	pinMode(LP, OUTPUT);
	pinMode(LN, OUTPUT);
}

// loop()内のプログラムは繰り返し実行される
void loop() {
	// センサーの読み取り値を変数に格納
	s1 = digitalRead(A0);
	s2 = digitalRead(A1);
	s3 = digitalRead(A2);
	s4 = digitalRead(A3);
	s5 = digitalRead(A4);
	s6 = digitalRead(A5);

  Serial.print(s1);
  Serial.print(",");
  Serial.print(s2);
  Serial.print(",");
  Serial.print(s3);
  Serial.print(",");
  Serial.print(s4);
  Serial.print(",");
  Serial.print(s5);
  Serial.print(",");
  Serial.print(s6);
  Serial.println(); // 改行でデータの終了を示す
	delay(100);

	// /************************
	//   センサ基板小
	//  ************************/
	// // それぞれの場合ごとにモータドライバへ送るPWM信号を設定//ライン外→0を示す（反射がないと光る。光っている状態であればそこを追従するかんじでかけばよい。反射がない→黒線上→光る→0）
	// if (s3 == 0 || s4 ==0) {
	// 	digitalWrite(RP, HIGH);//
	// 	digitalWrite(LP, HIGH);
	// 	analogWrite(RN, 120);
	// 	analogWrite(LN, 1200);//正面に進む
	// } else if (s5 == 0) {
	// 	digitalWrite(RP, HIGH);
	// 	digitalWrite(LP, HIGH);
	// 	analogWrite(RN, 120);
	// 	analogWrite(LN, 100);
  // } else if (s2 == 0) {
	// 	digitalWrite(RP, HIGH);
	// 	digitalWrite(LP, HIGH);
	// 	analogWrite(RN, 100);
	// 	analogWrite(LN, 120);
	// } else if (s6 == 0) {
	// 	digitalWrite(RP, HIGH);
	// 	digitalWrite(LP, HIGH);
	// 	analogWrite(RN, 120);
	// 	analogWrite(LN, 80);
	// } else if (s1 == 0) {
	// 	digitalWrite(RP, HIGH);
	// 	digitalWrite(LP, HIGH);
	// 	analogWrite(RN, 80);
	// 	analogWrite(LN, 120);//ここまででストレートな道を進むコードが完成

  //   //左折
  // }else if(s1==s2==0){ 
  //   digitalWrite(RP, HIGH);
  //   digitalWrite(LP, LOW);
  //   analogWrite(RN, 120);
  //   analogWrite(LN, 50);
    
  // }else if(s2==s3==0){ 
  //   digitalWrite(RP, HIGH);
  //   digitalWrite(LP, LOW);
  //   analogWrite(RN, 120);
  //   analogWrite(LN, 50);

  //   //右折
  // }else if(s4==s5==0){ 
  //   digitalWrite(RP, LOW);
  //   digitalWrite(LP, HIGH);
  //   analogWrite(RN, 50);
  //   analogWrite(LN, 120);
    
  // }else if(s5==s6==0){ 
  //   digitalWrite(RP, LOW);
  //   digitalWrite(LP, HIGH);
  //   analogWrite(RN, 50);
  //   analogWrite(LN, 120);
    
  // } else {
	// 	digitalWrite(RP, HIGH);
	// 	digitalWrite(LP, HIGH);
	// 	digitalWrite(RN, HIGH);
	// 	digitalWrite(LN , HIGH);
	// }

	/************************
	  センサ基板大
	 ************************/
	//	if (s3 == 0) {
	//		digitalWrite(RP, HIGH);
	//		digitalWrite(LP, HIGH);
	//		analogWrite(RN, 50);
	//		analogWrite(LN, 50);
	//	} else if (s4 == 0) {
	//		digitalWrite(RP, HIGH);
	//		digitalWrite(LP, HIGH);
	//		analogWrite(RN, 100);
	//		analogWrite(LN, 120);
	//	} else if (s2 == 0) {
	//		digitalWrite(RP, HIGH);
	//		digitalWrite(LP, HIGH);
	//		analogWrite(RN, 100);
	//		analogWrite(LN, 120);
	//	} else if (s1 == 0) {
	//		digitalWrite(RP, HIGH);
	//		digitalWrite(LP, HIGH);
	//		analogWrite(RN, 80);
	//		analogWrite(LN, 120);
	//	} else if (s5 == 0) {
	//		digitalWrite(RP, HIGH);
	//		digitalWrite(LP, HIGH);
	//		analogWrite(RN, 120);
	//		analogWrite(LN, 80);
	//	} else if (s6 == 0) {
	//		digitalWrite(RN, HIGH);
	//		digitalWrite(LN, HIGH);
	//		analogWrite(RP, 50);
	//		analogWrite(LP, 50);
  //  } else {
	//		digitalWrite(RP, HIGH);
	//		digitalWrite(LP, HIGH);
	//		digitalWrite(RN, HIGH);
	//		digitalWrite(LN , HIGH);
	//	}


	// 100 ms（ミリ秒）の間、プログラムの実行を止める
}
