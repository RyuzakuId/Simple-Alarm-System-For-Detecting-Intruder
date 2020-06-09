// Inisiasi Variabel Global yang dibutuhkan
int trigPin = 3;
int echoPin = 4;
int speakerPin = 5;
int ledPin = 10;

float jarak = 0;
bool penyusup = false;
float lebarPintu = 60; //Dalam cm

void setup() {
  // Memulai komunikasi serial
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  jarak = getDistance();

  // Cek Apakah ada intruder masuk
  if(jarak < lebarPintu)
    penyusup = true;

  if(penyusup){
    Serial.print("INTRUDER ALERT!!!!!!!!\n");
    // bunyikan buzzer
    beep();
    
    // kedipkan led
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
    delay(10);
  }else {
    Serial.print(jarak, 2);
    Serial.print(" cm\n");
    digitalWrite(ledPin, LOW);
  }

  delay(50);
}

void beep(){
  tone(speakerPin, 490, 150);
  delay(50);
  tone(speakerPin, 131, 300);
  delay(50);
}

float getDistance(){
  float echoTime;
  float hasil;

  // Mengirim sinyal pulsa ultrasonik yang lamanya 10ms
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mengirim sinyal pulsa ultrasonik yang lamanya 10ms
  echoTime = pulseIn(echoPin, HIGH);

  hasil = echoTime / 58.26; // kecepatan suara 58.26

  return hasil;
}
