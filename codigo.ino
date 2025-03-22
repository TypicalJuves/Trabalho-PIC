#include <AFMotor.h>
#include <Servo.h>
#include <HCSR04.h>

// ----- Motor Definitions -----
AF_DCMotor motorLeft(3);  // Left Motor
AF_DCMotor motorRight(4); // Right Motor

// ----- Servo e Sensor Ultrassônico -----
Servo sensorServo;
UltraSonicDistanceSensor distanceSensor(11, 12); // Trigger, Echo

// ----- Constantes -----
#define TURN_DURATION 650         // Aumentado para 90° 
#define REVERSE_DURATION 300      // Tempo de ré
#define OBSTACLE_THRESHOLD 30.0   
#define OPERATION_TIME 60000      
#define FORWARD_AFTER_TURN 400    // Movimento após curva

// ----- Registro de Movimentos -----
const int MAX_MOVES = 100;
unsigned long moveDurations[MAX_MOVES];
char turnDirections[MAX_MOVES];
int moveCount = 0;
unsigned long lastMoveTime = 0;

int speedVal = 200;

// ----- Funções de Movimento -----
void moveForward() {
  motorLeft.setSpeed(speedVal);
  motorRight.setSpeed(speedVal);
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
}

void moveBackward() {
  motorLeft.setSpeed(speedVal);
  motorRight.setSpeed(speedVal);
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
}

void turnLeft() {
  motorLeft.setSpeed(speedVal);
  motorRight.setSpeed(speedVal);
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
  delay(TURN_DURATION);
  stopMotors();
}

void turnRight() {
  motorLeft.setSpeed(speedVal);
  motorRight.setSpeed(speedVal);
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
  delay(TURN_DURATION);
  stopMotors();
}

void stopMotors() {
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

// ----- Funções do Sensor -----
float measureDistance() {
  return distanceSensor.measureDistanceCm();
}

void decideTurn() {
  // Dá ré antes de virar
  moveBackward();
  delay(REVERSE_DURATION);
  stopMotors();
  
  // Verifica direções
  float distRight, distLeft;
  
  sensorServo.write(180); // Nova direita
  delay(500);
  distRight = measureDistance();
  
  sensorServo.write(0);   // Nova esquerda
  delay(500);
  distLeft = measureDistance();
  
  sensorServo.write(90);
  delay(250);

  // Registra movimento
  unsigned long now = millis();
  moveDurations[moveCount] = now - lastMoveTime;
  
  // Toma decisão
  if (distRight > distLeft && distRight > OBSTACLE_THRESHOLD) {
    turnRight();
    turnDirections[moveCount] = 'R';
  } else if (distLeft > OBSTACLE_THRESHOLD) {
    turnLeft();
    turnDirections[moveCount] = 'L';
  } else {
    turnAround();
    turnDirections[moveCount] = 'B';
  }
  
  // Movimento pós-curva
  moveForward();
  delay(FORWARD_AFTER_TURN);
  stopMotors();
  
  moveCount++;
  lastMoveTime = millis();
}

void turnAround() {
  turnRight();
  turnRight();
}

void retracePath() {
  stopMotors();
  delay(500);
  turnAround();
  
  for (int i = moveCount - 1; i >= 0; i--) {
    moveForward();
    delay(moveDurations[i]);
    stopMotors();
    delay(250);
    
    if (i > 0) {
      if (turnDirections[i - 1] == 'L') turnRight();
      else if (turnDirections[i - 1] == 'R') turnLeft();
      else if (turnDirections[i - 1] == 'B') turnAround();
    }
  }
  stopMotors();
}

void setup() {
  Serial.begin(9600);
  sensorServo.attach(10);
  sensorServo.write(90);
  lastMoveTime = millis();
}

void loop() {
  unsigned long now = millis();
  if (now < OPERATION_TIME) {
    float distAhead = measureDistance();
    
    if (distAhead > 0 && distAhead < OBSTACLE_THRESHOLD) {
      stopMotors();
      decideTurn();
    } else {
      moveForward();
    }
  } else {
    moveDurations[moveCount] = now - lastMoveTime;
    moveCount++;
    retracePath();
    while (true) stopMotors();
  }
}
