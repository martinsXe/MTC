#include <math.h>

const double A = 1.25552582E-03;
const double B = 2.13537683E-04;
const double C = 1.69097407E-07;

const double R = 9748;
//const double R = 10000;
const double Vi = 1023;

const int sensor0 = A0;
const int sensor1 = A1;
const int sensor2 = A2;
const int sensor3 = A3;
const int sensor4 = A4;

double T[5] = {0,0,0,0,0};

void setup() {

  Serial.begin(9600);
}
void loop() {

  T[0] = temperatura(analogRead(sensor0));
  T[1] = temperatura(analogRead(sensor1));
  T[2] = temperatura(analogRead(sensor2));
  T[3] = temperatura(analogRead(sensor3));
  T[4] = temperatura(analogRead(sensor4));

  Serial.println(T[0],1);

  delay(10);
  }

  double temperatura(double V0) {
    double R0 = 0;
    double T = 0;
    R0 = R*(Vi-V0)/V0;
    T = 1/(A + B * log(R0) + C * pow((log(R0)),3))-273.15;
    return T;
    }
