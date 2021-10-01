#include <LiquidCrystal.h>

LiquidCrystal lcd(22,11,5,25,3,29);

int hora = 12;
int minuto = 0;
int ht = hora;
int mt = minuto;
int ha = 0;
int ma = 0;
const int btch = 12;
const int btcm = 13;
const int btsh = 8;
const int btsa = 37;
int changeH = 0;
int changeM = 0;
int establecerHora = 0;
int establecerAlarma = 0;
const int num[] = {5,3,2,1,1}; 

const int L1R = 7;
const int L1G = 4;
const int L1B = 2;

const int L2R = 53;
const int L2G = 52;
const int L2B = 51;

const int L3R = 50;
const int L3G = 49;
const int L3B = 48;

const int L4R = 47;
const int L4G = 46;
const int L4B = 45;

const int L5R = 44;
const int L5G = 43;
const int L5B = 41;

const int pinBuzzer = 9;
  
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(btch, INPUT);
  pinMode(btcm, INPUT);
  pinMode(btsh, INPUT);
  pinMode(btsa, INPUT);
  
  pinMode(L1R, OUTPUT);
  pinMode(L1G, OUTPUT);
  pinMode(L1B, OUTPUT);
  pinMode(L2R, OUTPUT);
  pinMode(L2G, OUTPUT);
  pinMode(L2B, OUTPUT);
  pinMode(L3R, OUTPUT);
  pinMode(L3G, OUTPUT);
  pinMode(L3B, OUTPUT);
  pinMode(L4R, OUTPUT);
  pinMode(L4G, OUTPUT);
  pinMode(L4B, OUTPUT);
  pinMode(L5R, OUTPUT);
  pinMode(L5G, OUTPUT);
  pinMode(L5B, OUTPUT);

  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  establecerHora = 0;
  changeH = digitalRead(btch);
  changeM = digitalRead(btcm);
  establecerHora = digitalRead(btsh);
  establecerAlarma = digitalRead(btsa);

  if(changeH == 1 || changeM == 1 || establecerHora == 1 || establecerAlarma == 1){
    cambiarHora(changeH, changeM, establecerHora, establecerAlarma);
    delay(500);
  }
  if(ha == hora && ma == minuto){
    alarma();
  }
  reloj();
}

void reloj(){
  minuto = minuto + 2;
  if(minuto > 60){
    minuto = 0;
    hora = hora + 1;
    if(hora>12){
      hora = 1;
    }
  }
  show();
  fibonachi(hora, minuto);
  delay(1000);
  apagarleds();
  lcd.clear();
}

void cambiarHora(int changeH, int changeM, int establecerHora, int  establecerAlarma ){

  if(changeH == 1){
    ht = ht +1;
    if(ht > 12){
      ht = 1;
    }
  }
  if(changeM == 1){
    mt = mt + 2;
    if(mt > 60){
      ht = ht +1;
      mt = 0;
      if(ht > 12){
        ht = 1;
      }
    }
  }
  if(establecerHora == 1){
    hora = ht;
    minuto = mt;
  }
  if(establecerAlarma == 1){
    ha = ht;
    ma = mt;
    lcd.setCursor(3,1);
    lcd.print("Alarma ON");
  }
  lcd.setCursor(0,1);
  lcd.print(ht);
  lcd.setCursor(3,1);
  lcd.print(mt);
}

void fibonachi(int h, int m){ //h = horas, m = minutos
  int x = m / 5;
  int suma = 0;
  boolean minu[5];
  boolean horas[5];
  
  for(int i = 0; i<5; i++){ //para rellenar el array dependiendo si la suma es menor igual al numero o mayor y de esta manera ver que "casillas" utilizar
    suma = suma + num[i];
    if(suma <= x){
      minu[i] = true;
    }else{
      minu[i] = false;
      suma = suma - num[i];
    }
  }

  suma = 0;
  for(int j = 0; j<5; j++){
    suma = suma + num[j];
    if(suma <= h){
      horas[j] = true;
    }else{
      horas[j] = false;
      suma = suma - num[j];
    }
  }
  ledMinutos(horas, minu);
}

void ledMinutos(boolean minu[], boolean horas[]){
  char color[5]; 
  
  for(int i = 0; i <5; i++){
      if(minu[i] == true && horas[i] == true){
        color[i] = 'A';
      }else if(minu[i] == true && horas[i] == false){
        color[i] ='R';
      }
      else if(minu[i] == false && horas[i] == true){
        color[i] = 'V';
      }else if(minu[i] == false && horas[i] == false){
        color[i] = 'N';
      }
    }
  encenderLed(color);    
}


void show(){
  lcd.setCursor(0,0);
  lcd.print((String)+ hora + " : "+minuto);
}

void alarma(){
  tone(pinBuzzer, 740);
  delay(500);
  noTone(pinBuzzer);
}

void encenderLed(char color[]){
  if(color[0] == 'A' ){
    digitalWrite(L1B, HIGH);
  }
  if(color[0] == 'V'){
    digitalWrite(L1G, HIGH);
  }
  if(color[0] == 'R'){
    digitalWrite(L1R, HIGH);
  }if(color[0] == 'N'){
    digitalWrite(L1B, LOW);
    digitalWrite(L1G, LOW);
    digitalWrite(L1R, LOW);
  }
  
  if(color[1] == 'A' ){
    digitalWrite(L2B, HIGH);
  }
  if(color[1] == 'V'){
    digitalWrite(L2G, HIGH);
  }
  if(color[1] == 'R'){
    digitalWrite(L2R, HIGH);
  }if(color[1] == 'N'){
    digitalWrite(L2B, LOW);
    digitalWrite(L2G, LOW);
    digitalWrite(L2R, LOW);
  }

  if(color[2] == 'A' ){
   digitalWrite(L3B, HIGH);
  }
  if(color[2] == 'V'){
    digitalWrite(L3G, HIGH);
  }
  if(color[2] == 'R'){
    digitalWrite(L3R, HIGH);
  }if(color[2] == 'N'){
    digitalWrite(L3B, LOW);
    digitalWrite(L3G, LOW);
    digitalWrite(L3R, LOW);
  }

  if(color[3] == 'A' ){
    digitalWrite(L4B, HIGH);
  }
  if(color[3] == 'V'){
    digitalWrite(L4G, HIGH);
  }
  if(color[3] == 'R'){
    digitalWrite(L4R, HIGH);
  }if(color[3] == 'N'){
    digitalWrite(L4B, LOW);
    digitalWrite(L4G, LOW);
    digitalWrite(L4R, LOW);
  }

  if(color[4] == 'A' ){
    digitalWrite(L5B, HIGH);
  }
  if(color[4] == 'V'){
    digitalWrite(L5G, HIGH);
  }
  if(color[4] == 'R'){
    digitalWrite(L5R, HIGH);
  }if(color[4] == 'N'){
    digitalWrite(L5B, LOW);
    digitalWrite(L5G, LOW);
    digitalWrite(L5R, LOW);
  }
}

void apagarleds(){
  digitalWrite(L5B, LOW);
  digitalWrite(L5G, LOW);
  digitalWrite(L5R, LOW);
  digitalWrite(L4B, LOW);
  digitalWrite(L4G, LOW);
  digitalWrite(L4R, LOW);
  digitalWrite(L3B, LOW);
  digitalWrite(L3G, LOW);
  digitalWrite(L3R, LOW);
  digitalWrite(L2B, LOW);
  digitalWrite(L2G, LOW);
  digitalWrite(L2R, LOW);
  digitalWrite(L1B, LOW);
  digitalWrite(L1G, LOW);
  digitalWrite(L1R, LOW);
}
