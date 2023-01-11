/* Robotic Arm Controller Code
   Using Bluetooth Module */

#include <SoftwareSerial.h>
#include <Servo.h>
int datainput;
int base_num = 180;
int elbow_num = 60;
int hand_num = 50;
int grip_num = 140;
int speeddelay = 10;
bool servo_motors_Flag = false;
bool Base_servo_0_to_180_Flag = false;
bool Base_servo_180_to_0_Flag = false;
bool Grip_servo_50_to_140_Flag = false;
bool Grip_servo_140_to_0_Flag = false;
bool Hand_servo_5_to_50_Flag = false;
bool Hand_servo_50_to_5_Flag = false;
bool elbow_servo_0_to_100_Flag = false;
bool elbow_servo_100_to_0_Flag = false;
int Base[50], Grip[50], Hand[50], Elbow[50];
int index = 0;

Servo Base_servo;
Servo Grip_servo;
Servo Hand_servo;
Servo Elbow_servo;
SoftwareSerial Bluetoothmod(0, 1);

void setup() {
  Base_servo.attach(10);
  Grip_servo.attach(8);
  Hand_servo.attach(7);
  Elbow_servo.attach(5);
  Serial.begin(9600);
  Bluetoothmod.begin(9600);
  Base_servo.write(180);
  Grip_servo.write(140);
  Hand_servo.write(50);
  Elbow_servo.write(60); 
}

void loop() {
  if (Bluetoothmod.available() > 0) {
    datainput = Bluetoothmod.read();
    Serial.println(datainput);

    if (datainput == 'l') {
      speeddelay = 25;
    }
    if (datainput == 'm') {
      speeddelay = 10;
    }
    if (datainput == 'h') {
      speeddelay = 2;
    }

    if (datainput == 'S') {
      servo_motors_Flag = true;
      Base_servo_0_to_180_Flag = false;
      Base_servo_180_to_0_Flag = false;
      Grip_servo_50_to_140_Flag = false;
      Grip_servo_140_to_0_Flag = false;
      Hand_servo_5_to_50_Flag = false;
      Hand_servo_50_to_5_Flag = false;
      elbow_servo_0_to_100_Flag = false;
      elbow_servo_100_to_0_Flag = false;
      base_num = base_num;
      elbow_num = elbow_num;
      hand_num = hand_num;
      grip_num = grip_num;
    }

    if (datainput == 'L') {
      Base_servo_0_to_180_Flag = true;
      Base_servo.write(base_num);
    }

    if (datainput == 'R') {
      Base_servo_180_to_0_Flag = true;
      Base_servo.write(base_num);
    }

    if (datainput == 'C') {
      Grip_servo_50_to_140_Flag = true;
      Grip_servo.write(grip_num);
    }

    if (datainput == 'O') {
      Grip_servo_140_to_0_Flag = true;
      Grip_servo.write(grip_num);
    }

    if (datainput == 'D') {
      Hand_servo_5_to_50_Flag = true;
      Hand_servo.write(hand_num);
    }

    if (datainput == 'U') {
      Hand_servo_50_to_5_Flag = true;
      Hand_servo.write(hand_num);
    }

    if (datainput == 'F') {
      elbow_servo_0_to_100_Flag = true;
      Elbow_servo.write(elbow_num);
    }

    if (datainput == 'B') {
      elbow_servo_100_to_0_Flag = true;
      Elbow_servo.write(elbow_num);
    }

    if (datainput == 's') {
      Base[index] = base_num;
      Grip[index] = grip_num;
      Hand[index] = hand_num;
      Elbow[index] = elbow_num;
      index++;
    }

    if (datainput == 'x') {
      runservo();
    }

    if (datainput == 'y') {
      reset();
    }
  }

  if (Base_servo_180_to_0_Flag == true) {
    base_num++;
    if (base_num > 180) {
      base_num = 180;
    }
    Base_servo.write(base_num);
    delay(speeddelay);
  }

  if (Base_servo_0_to_180_Flag == true) {
    base_num--;
    if (base_num < 0) {
      base_num = 0;
    }
    Base_servo.write(base_num);
    delay(speeddelay);
  }

  if (Grip_servo_140_to_0_Flag == true) {
    grip_num--;
    if (grip_num < 50) {
      grip_num = 50;
    }
    Grip_servo.write(grip_num);
    delay(speeddelay);
  }

  if (Grip_servo_50_to_140_Flag == true) {
    grip_num++;
    if (grip_num > 140) {
      grip_num = 140;
    }
    Grip_servo.write(grip_num);
    delay(speeddelay);
  }

  if (Hand_servo_50_to_5_Flag == true) {
    hand_num--;
    if (hand_num < 5) {
      hand_num = 5;
    }
    Hand_servo.write(hand_num);
    delay(speeddelay);
  }

  if (Hand_servo_5_to_50_Flag == true) {
    hand_num++;
    if (hand_num > 50) {
      hand_num = 50;
    }
    Hand_servo.write(hand_num);
    delay(speeddelay);
  }

  if (elbow_servo_100_to_0_Flag == true) {
    elbow_num++;
    if (elbow_num > 100) {
      elbow_num = 100;
    }
    Elbow_servo.write(elbow_num);
    delay(speeddelay);
  }

  if (elbow_servo_0_to_100_Flag == true) {
    elbow_num--;
    if (elbow_num < 0) {
      elbow_num = 0;
    }
    Elbow_servo.write(elbow_num);
    delay(speeddelay);
  }
}

void runservo() {

  if (datainput == 'l') {
    speeddelay = 25;
  }
  if (datainput == 'm') {
    speeddelay = 10;
  }
  if (datainput == 'h') {
    speeddelay = 2;
  }

  while (datainput != 'y') {
    for (int i = 0; i <= index - 2; i++) {
      if (Bluetoothmod.available() > 0) {
        datainput = Bluetoothmod.read();
        if (datainput == 'z') {
          while (datainput != 'x') {
            if (Bluetoothmod.available() > 0) {
              datainput = Bluetoothmod.read();
              if (datainput == 'y') {
                break;
              }
            }
          }
        }
      }

      if (Base[i] == Base[i + 1]) {
      }
      if (Base[i] > Base[i + 1]) {
        for (int j = Base[i]; j >= Base[i + 1]; j--) {
          Base_servo.write(j);
          delay(speeddelay);
        }
      }
      if (Base[i] < Base[i + 1]) {
        for (int j = Base[i]; j <= Base[i + 1]; j++) {
          Base_servo.write(j);
          delay(speeddelay);
        }
      }


      if (Grip[i] == Grip[i + 1]) {
      }
      if (Grip[i] > Grip[i + 1]) {
        for (int j = Grip[i]; j >= Grip[i + 1]; j--) {
          Grip_servo.write(j);
          delay(speeddelay);
        }
      }
      if (Grip[i] < Grip[i + 1]) {
        for (int j = Grip[i]; j <= Grip[i + 1]; j++) {
          Grip_servo.write(j);
          delay(speeddelay);
        }
      }


      if (Hand[i] == Hand[i + 1]) {
      }
      if (Hand[i] > Hand[i + 1]) {
        for (int j = Hand[i]; j >= Hand[i + 1]; j--) {
          Hand_servo.write(j);
          delay(speeddelay);
        }
      }
      if (Hand[i] < Hand[i + 1]) {
        for (int j = Hand[i]; j <= Hand[i + 1]; j++) {
          Hand_servo.write(j);
          delay(speeddelay);
        }
      }


      if (Elbow[i] == Elbow[i + 1]) {
      }
      if (Elbow[i] > Elbow[i + 1]) {
        for (int j = Elbow[i]; j >= Elbow[i + 1]; j--) {
          Elbow_servo.write(j);
          delay(speeddelay);
        }
      }
      if (Elbow[i] < Elbow[i + 1]) {
        for (int j = Elbow[i]; j <= Elbow[i + 1]; j++) {
          Elbow_servo.write(j);
          delay(speeddelay);
        }
      }
    }
  }
}
void reset() {

  for (int i = index - 1; i > 0; i--) {

    if (Base[i] == Base[i - 1]) {
    }
    if (Base[i] > Base[i - 1]) {
      for (int j = Base[i]; j >= Base[i - 1]; j--) {
        Base_servo.write(j);
        delay(speeddelay);
      }
    }
    if (Base[i] < Base[i - 1]) {
      for (int j = Base[i]; j <= Base[i - 1]; j++) {
        Base_servo.write(j);
        delay(speeddelay);
      }
    }


    if (Grip[i] == Grip[i - 1]) {
    }
    if (Grip[i] < Grip[i - 1]) {
      for (int j = Grip[i]; j <= Grip[i - 1]; j++) {
        Grip_servo.write(j);
        delay(speeddelay);
      }
    }
    if (Grip[i] > Grip[i - 1]) {
      for (int j = Grip[i]; j >= Grip[i - 1]; j--) {
        Grip_servo.write(j);
        delay(speeddelay);
      }
    }


    if (Hand[i] == Hand[i - 1]) {
    }
    if (Hand[i] > Hand[i - 1]) {
      for (int j = Hand[i]; j >= Hand[i - 1]; j--) {
        Hand_servo.write(j);
        delay(speeddelay);
      }
    }
    if (Hand[i] < Hand[i - 1]) {
      for (int j = Hand[i]; j <= Hand[i - 1]; j++) {
        Hand_servo.write(j);
        delay(speeddelay);
      }
    }


    if (Elbow[i] == Elbow[i - 1]) {
    }
    if (Elbow[i] > Elbow[i - 1]) {
      for (int j = Elbow[i]; j >= Elbow[i - 1]; j--) {
        Elbow_servo.write(j);
        delay(speeddelay);
      }
    }
    if (Elbow[i] < Elbow[i - 1]) {
      for (int j = Elbow[i]; j <= Elbow[i - 1]; j++) {
        Elbow_servo.write(j);
        delay(speeddelay);
      }
    }
  }

  memset(Base, Base[0], sizeof(Base));
  memset(Grip, Grip[0], sizeof(Grip));
  memset(Hand, Hand[0], sizeof(Hand));
  memset(Elbow, Elbow[0], sizeof(Elbow));
}
