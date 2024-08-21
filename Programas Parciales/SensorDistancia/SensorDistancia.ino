// Definimos los pines de conexión
#define echoPin 12
#define trigPin 13


void setup() {  
  // Inicializamos los pines como salidas
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  float distancia, duracion;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH);

  distancia = duracion * 0.034 / 2;

  Serial.print("Diatancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(1000);
}