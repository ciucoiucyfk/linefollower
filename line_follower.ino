#define s1 2
#define s2 3
#define s3 4
#define s4 5
#define s5 6


#define p1 A0
#define p2 A1 
#define p3 A2

int sensorPins[] = {s1, s2, s3, s4, s5};
int sensorValues[5];


#define lspeed 11 
#define l1 12
#define l2 13


#define rspeed 10 
#define r1 8
#define r2 9 


double Kp = 0; 
double Ki = 0; 
double Kd = 0; 


double error = 0;
double lastError = 0;
double integral = 0;
double derivative = 0;
double correction; 


int baseSpeed = 150;
int maxSpeed = 255; 


int lastKnownPosition = 0; 

void setup() {
  
  for (int pin : sensorPins) {
    pinMode(pin, INPUT);
  }

  
  pinMode(lspeed, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(rspeed, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);

  
  digitalWrite(l1, HIGH);
  digitalWrite(l2, LOW);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);

  Kp = analogRead(p1);
  Kd = analogRead(p2);
  Ki = analogRead(p3);

  
  Serial.begin(9600);
}


void loop() {
  
  error = calculateError();  
  correction = calculatePID(error);  
  Motors(correction);
  
  lastError = error;

}


double calculateError() {
  int sensorSum = 0;
  long weightedSum = 0;

  
  for (int i = 0; i < 5; i++) {
    sensorValues[i] = 1 - digitalRead(sensorPins[i]);
  } 

  weightedSum += (long)sensorValues[0] * -4;
  weightedSum += (long)sensorValues[1] * -2;
  weightedSum += (long)sensorValues[2] * 0;
  weightedSum += (long)sensorValues[3] * 2;
  weightedSum += (long)sensorValues[4] * 4;

  sensorSum = sensorValues[0] + sensorValues[1] + sensorValues[2] + sensorValues[3] + sensorValues[4];

  
  if (sensorSum == 0) {    
    if (lastKnownPosition > 0) {
      return 4; 
    } else {
      return -4;
    }
  }

  
  double position = (double)weightedSum / sensorSum;
  
  
  lastKnownPosition = position; 

  return position;
}


double calculatePID(double error) {
  // P (Proportional)
  double P = Kp * error;

  // I (Integral)
  integral += error;
  // --- Integral Windup Prevention ---
  // Clamp the integral to a reasonable range
  if (integral > 100) integral = 100;
  if (integral < -100) integral = -100;
  
  double I = Ki * integral;

  // D (Derivative)
  derivative = error - lastError;
  double D = Kd * derivative;

  // Total Correction
  return P + I + D;
}


void Motors(double correction) {  
  int leftSpeed = constrain(baseSpeed + correction,0,255);
  int rightSpeed = constrain(baseSpeed - correction,0,255);

 
  analogWrite(lspeed, leftSpeed);
  analogWrite(rspeed, rightSpeed);


}

