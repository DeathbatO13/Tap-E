// Importacion de la libreria para manejo de los servomotores
#include <Servo.h>
// Creacion de variables con los pines a los que corresponden
#define in1 7
#define in2 6
#define in3 5
#define in4 4
#define enA 3
#define enB 2
#define trigPin 13
#define echoPin 12
// Creaccion de los objetos servo
Servo servoBase;
Servo servoBrazo1;
Servo servoBrazo2;
Servo servoGarra;
// Configuracion de pines (Entradas, Salidas, y Pines de los Servos)
void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoBase.attach(11);
  servoBrazo1.attach(10);
  servoBrazo2.attach(9);
  servoGarra.attach(8);
}
// Funcion para hacer que Tap-E avance
void avanzar(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}
// Funcion para hacer que Tap-E gire a la derecha
void derecha(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}
// Funcion para que Tap-E se detenga
void parar(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
/* Funcion para dinamizar la memoria y no meter tantos ciclos for dentro de
la funcion recoger, basicamente le pasamos el servo que queremos mover, los grados
de referencia (inicio, fin) y la velocidad*/
void moverServo(Servo &servo, int inicio, int fin, int velocidad) {
  int paso = (inicio < fin) ? 1 : -1;
  for (int pos = inicio; pos != fin + paso; pos += paso) {
    servo.write(pos);
    delay(velocidad);
  }
}
/* Funcion recoger, en esta funcion se juntan todos los movimientos de los servos, para
hacer todo el movimiento de la garra entera*/
void recoger() {
  moverServo(servoBase, 170, 0, 12);
  delay(1000);
  
  for(int posi = 90; posi >= 0; posi--){
    servoBrazo1.write(posi);
    servoBrazo2.write(180-posi);
    delay(12);
  }
  delay(1000); 
  
  moverServo(servoGarra, 0, 45, 12);
  delay(1000); 
  
  for(int posi = 0; posi <= 90; posi++){
    servoBrazo1.write(posi);
    servoBrazo2.write(180-posi);
    delay(12);
  }
  delay(1000); 
  
  moverServo(servoBase, 0, 170, 12);
  delay(1000); 

  moverServo(servoGarra, 45, 0, 12);
  delay(1000); 
}
/* Funcion para andar, en esta funcion tambien hacemos la medicion de la distancia,
liberando un poco de memoria, y cuando la medicion sea menor a 40cm hace el giro a 
la derecha*/
void evadir(){
  float distancia, duracion;

  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH);

  distancia = duracion * 0.034 / 2;

  if(distancia <= 40){
    derecha();
  }else {
    avanzar();
  }
}
// Loop, ciclo principal donde se ejecuta el programa
void loop() {
  /*Ciclo for con 100 iteraciones, cada una de duracion de 100 ms, para una duracion
  total de 10 seg, en estos segundos solo va a avanzar y ezquivar (el delay, no solo sirve
  para que despues de las 100 iteraciones se completen 100 segundos, sino que tambien
  es la frecuencia de muestreo, es decir cada 100 ms hace la medicion de distancia y 
  la comparacion para saber si gira o no)*/
  for(int i = 0; i <= 100; i++){
    evadir();
    delay(100);
  }
  // Luego de los 10 segundos Tap-E se detiene y hace el movimiento de la garra
  parar();
  recoger();
  delay(1000);
}