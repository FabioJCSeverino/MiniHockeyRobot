#include "BluetoothSerial.h"
#define VEL_ALTA 255
#define VEL_BAIXA 175
#define VEL_CURVA 200

//Bluetooh
#define BT_NAME "PS_Germ_Grupo_1"

BluetoothSerial SerialBT;

//Motores
const int enA = 34;
const int in1 = 32;
const int in2 = 35;

const int enB = 27;
const int in3 = 25;
const int in4 = 26;

char comando;
int vel;

void setup() {
  Serial.begin(115200);
  
  // Bluetooh
  SerialBT.begin(BT_NAME);

  //Motores
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  parar();
  velocidade(VEL_BAIXA);
}

void loop() {
  if (SerialBT.available()) {
    comando = SerialBT.read();
    Serial.print("Recebido: ");
    Serial.println(comando);

    switch (comando) {
      case 'F': // Frente
        frente();
        break;
      case 'B': //Tras
        tras();
        break;
      case 'L': //Esq
        esquerda();
        break;
      case 'R': //Dir
        direita();
        break;
      case 'S': //Parar
        parar();
        break;
      case 'X': //Velocidade Alta
        velocidade(VEL_ALTA);
        break;
      case 'x': //Velocidade Baixa
        velocidade(VEL_BAIXA);
        break;
      default:
        break;
    }
  }
}

void velocidade(int v){
  Serial.print("Velocidade: ");
  Serial.println(v);
  vel = v;
}

void frente() {
  Serial.println("FRENTE");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, vel);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, vel);
}

void tras() {
  Serial.println("TRAS");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, vel);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, vel);
}

void esquerda() {
  Serial.println("ESQUERDA");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, VEL_CURVA);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, VEL_CURVA);
}

void direita() {
  Serial.println("DIREITA");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, VEL_CURVA);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, VEL_CURVA);
}

void parar() {
  Serial.println("PARADO");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
}
