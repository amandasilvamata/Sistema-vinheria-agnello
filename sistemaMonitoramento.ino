// Integrantes:
// Amanda Silva da Mata 
// Beatriz Mantovani
// Gustavo Ducatti
// Laura Sampaio


#include <DHT.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte tempchar1[8] = {
  B00001,
  B00010,
  B00010,
  B00010,
  B00011,
  B00011,
  B00011,
};
byte tempchar2[8] = {
  B10110,
  B01000,
  B01110,
  B01000,
  B11110,
  B11000,
  B11000,
};
byte tempchar4[8] = {
  B11000,
  B11100,
  B11100,
  B11100,
  B11100,
  B11000,
  B00000,
};
byte tempchar3[8] = {
  B00011,
  B00111,
  B00111,
  B00111,
  B00111,
  B00011,
  B00000,
};

byte umchar1[8] = {
  B00001,
  B00011,
  B00011,
  B00011,
  B00111,
  B00111,
  B00111,
};
byte umchar2[8] = {
  B10000,
  B11000,
  B11000,
  B11000,
  B11100,
  B11100,
  B11100,
};
byte umchar4[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11100,
  B11000,
  B00000,
};
byte umchar3[8] = {
  B01111,
  B01111,
  B01111,
  B01111,
  B00111,
  B00011,
  B00000,
};


#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int ldrPin = A0;
int ledVerde = 8;
int ledAmarelo = 9;
int ledVermelho = 10;
int buzzer = 11;

String temperaturaLinha1;
String temperaturaLinha2;

String umidadeLinha1;
String umidadeLinha2;

String luzLinha1;
String luzLinha2;


void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
 
  dht.begin();
  Serial.begin(9600);
}

//zerar luzes e buzzer
void zerar(){
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(buzzer, LOW);
}

//escrever no display

void mostrarTemperatura(){
  lcd.clear();

  lcd.createChar(1,tempchar1);
  lcd.createChar(3,tempchar2);
  lcd.createChar(2,tempchar3);
  lcd.createChar(4,tempchar4);
  lcd.setCursor(14,0);
  lcd.write(1);
  lcd.setCursor(14,1);
  lcd.write(2);
  lcd.setCursor(15,0);
  lcd.write(3);
  lcd.setCursor(15,1);
  lcd.write(4);
  lcd.setCursor(16,0);
  lcd.print(temperaturaLinha1);
  lcd.setCursor(16, 1); 
  lcd.print(temperaturaLinha2);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(100);
  }
}

void mostrarUmidade(){
  lcd.clear();
  
  lcd.createChar(1,umchar1);
  lcd.createChar(3,umchar2);
  lcd.createChar(2,umchar3);
  lcd.createChar(4,umchar4);
  lcd.setCursor(14,0);
  lcd.write(1);
  lcd.setCursor(14,1);
  lcd.write(2);
  lcd.setCursor(15,0);
  lcd.write(3);
  lcd.setCursor(15,1);
  lcd.write(4);
  lcd.setCursor(16,0);
  lcd.print(umidadeLinha1);
  lcd.setCursor(16, 1); 
  lcd.print(umidadeLinha2);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(100);
  }
}

void mostrarLuz(){
  lcd.clear();
  
  lcd.setCursor(16,0);
  lcd.print(luzLinha1);
  lcd.setCursor(16, 1); 
  lcd.print(luzLinha2);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(100);
  }
}

//Fazer medias

float mediaUmidade(){

  float umidade = 0;

  for(int i=0; i<5; i++){
    float novaUm = dht.readHumidity();
    umidade += novaUm;
    delay(300);
  }

  umidade = umidade/5;
  return umidade;

}

float mediaTemperatura(){

  float temperatura = 0;

  for(int i=0; i<5; i++){
    float novaTem = dht.readTemperature();
    temperatura += novaTem;
    delay(300);
  }

  temperatura = temperatura/5;
  return temperatura;

}

float mediaLuz(){

  float luz = 0;

  for(int i=0; i<5; i++){
    float novaLuz = analogRead(ldrPin);
    luz += novaLuz;
    delay(300);
  }

  luz = luz/5;
  return luz;

}


void loop() {

  float temperatura = mediaTemperatura();
  float umidade = mediaUmidade();
  float luz = mediaLuz();

  String temperaturaStatus;
  String umidadeStatus;
  String luzStatus;

  //TEMPERATURA
  
  if(temperatura>=10 && temperatura<=15){
    temperaturaStatus = "OK";
    zerar();

  }else if(temperatura>15){
    temperaturaStatus = "ALTA";
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, HIGH);

  }else{
    temperaturaStatus = "BAIXA";
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, HIGH);
    
  }

  temperaturaLinha1 = "Temp. " + temperaturaStatus;
  temperaturaLinha2 = "Valor = " + String(temperatura);
  mostrarTemperatura();
  delay(1000);


  //UMIDADE
  
  if(umidade>=50 && umidade<=70){
    umidadeStatus = "OK";
    zerar();

  }else if(umidade>70){
    umidadeStatus = "ALTA";
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);

  }else{
    umidadeStatus = "BAIXA";
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
    
  }

  umidadeLinha1 = "Umidade " + umidadeStatus;
  umidadeLinha2 = "Um. = " + String(umidade) + "%";
  mostrarUmidade();
  delay(1000);


  //LUZ

  if (luz > 900) {
    luzStatus = "PERFEITA";
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);
 
  } else if (luz > 850) {
    luzStatus = "MEIA LUZ";
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);
 
  } else if (luz >= 0) {
    luzStatus = "MUITO CLARO";
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
 
  }

  luzLinha1 = luzStatus;
  luzLinha2 = "Luz = " + String(luz);
  mostrarLuz();
  delay(1000);


}
