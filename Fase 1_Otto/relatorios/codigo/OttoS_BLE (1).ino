/*  
*                        
*    ______________      ____                                _____    _  _     _
*   |   __     __  |    / __ \ _________ _________   ____   |  __ \  | | \\   //  
*   |  |__|   |__| |   | |  | |___   ___ ___   ___  / __ \  | |  | | | |  \\ //  
*   |_    _________|   | |  | |   | |       | |    | |  | | | |  | | | |   | |
*   | \__/         |   | |__| |   | |       | |    | |__| | | |__| | | |   | |
*   |              |    \____/    |_|       |_|     \____/  |_____/  |_|   |_|
*   |_    _________|
*     \__/            
*
*    This Sketch was created to control Otto Starter with the Offical Web Bluetooth Controller for Otto DIY Robots.
*    For any question about this script you can contact us at education@ottodiy.com
*    By: Iván R. Artiles
*/

#include <Otto.h>
#include <EEPROM.h>

#define LEFTLEG 2
#define RIGHTLEG 3
#define LEFTFOOT 4
#define RIGHTFOOT 5
#define TRIG 8
#define ECHO 9
#define BLE_TX 11
#define BLE_RX 12
#define BUZZER 13

#if defined(ARDUINO_ARCH_ESP32)
  #include "BluetoothSerial.h"
  String device_name = "Otto BT Esp32";
  BluetoothSerial bluetooth;
#else
  #include <SoftwareSerial.h>
  String device_name = "Otto BT";
  SoftwareSerial bluetooth(BLE_TX, BLE_RX);
#endif

int move_speed[] = {3000, 2000, 1000, 750, 500, 250};
int n = 2;
int ultrasound_threeshold = 15;
String command = "";

int v;
int ch;
int i;
int positions[] = {90, 90, 90, 90};
int8_t trims[4] = {0,0,0,0};
unsigned long sync_time = 0;

bool calibration = false;
  
Otto Ottobot;

// ================== VALSA (Rede de Petri) ==================
// Notas musicais do Danubio Azul
#define NOTE_C4  262
#define NOTE_E4  330
#define NOTE_G4  392
#define NOTE_C5  523

// Estados da Rede de Petri (Lugares)
enum EstadosPetri {
  P_INICIO,
  P_RITMO_1,      // Tempo 1: Forte (passo inicial)
  P_RITMO_2_3,    // Tempos 2 e 3: Fracos (ajuste/fechamento)
  P_GIRO
};

EstadosPetri estadoAtual = P_INICIO;
bool direcaoDireita = true;   // Controla o lado da danca (espelho)
int contadorPassos = 0;

// ================== CORRIDA DE OBSTACULOS ==================
#define DISTANCIA_LIMITE 20   // cm: abaixo disso, o robo desvia

// ================== ROBO INSPETOR DE DUTOS ==================
#define DISTANCIA_LIVRE_MIN  20.0  // Acima de 20cm: caminho livre
#define DISTANCIA_BOTAO_MAX  5.0   // Menor que 5cm: aciona o Botao Virtual
#define TEMPO_HOLD_BOTAO_MS  1500  // 1.5s com a mao proxima para alternar estado

enum EstadoInspecao {
  PAUSADO,
  INSPECAO_ATIVA,
  BLOQUEADO_AGUARDANDO_RESGATE
};

EstadoInspecao estadoInspecao = PAUSADO;
unsigned long passosAvancados = 0;   // profundidade percorrida no duto
unsigned long tempoInicioGesto = 0;
bool maoDetectada = false;

long ultrasound_distance() {
   long duration, distance;
   digitalWrite(TRIG,LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG, LOW);
   duration = pulseIn(ECHO, HIGH);
   distance = duration/58;
   return distance;
}

void setup() {
  Serial.begin(9600);
  Ottobot.init(LEFTLEG, RIGHTLEG, LEFTFOOT, RIGHTFOOT, true, BUZZER);
  pinMode(TRIG, OUTPUT); 
  pinMode(ECHO, INPUT);

#if defined(ARDUINO_ARCH_ESP32)
  bluetooth.begin(device_name);
  //bluetooth.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
#else
  bluetooth.begin(9600);
  bluetooth.print("AT+NAME" + device_name);
#endif
  
  Ottobot.home();
  v = 0;
}

void loop() {
  checkBluetooth();//if something is coming at us
  if (command == "forward") {
    Forward();
  }
  else if (command == "backward") {
    Backward();
  }
  else if (command == "right") {
    Right();
  }
  else if (command == "left") {
    Left();
  }
  else if (command == "avoidance") {
    Avoidance();
  }
  else if (command == "force") {
    UseForce();
  }
  else if (command == "waltz") {
    Waltz();
  }
  else if (command == "race") {
    Race();
  }
  else if (command == "inspect") {
    Inspector();
  }
}

void checkBluetooth() {
  char charBuffer[20];//most we would ever see
  
  if (bluetooth.available() > 0) {
    int numberOfBytesReceived = bluetooth.readBytesUntil('\n', charBuffer, 19);
    charBuffer[numberOfBytesReceived] = NULL;
    Serial.print("Received: ");
    Serial.println(charBuffer);
    
    n = charBuffer[numberOfBytesReceived-1]-'0';
    
    if (strstr(charBuffer, "forward") == &charBuffer[0]) {
      command = "forward";
    }   
    else if (strstr(charBuffer, "backward") == &charBuffer[0]) {
      command = "backward";
    }
    else if (strstr(charBuffer, "right") == &charBuffer[0]) {
      command = "right";
    }
    else if (strstr(charBuffer, "left") == &charBuffer[0]) {
      command = "left";
    }
    else if (strstr(charBuffer, "stop") == &charBuffer[0]) {
      command = "stop";
      Stop();
    }
    else if (strstr(charBuffer, "ultrasound") == &charBuffer[0]) {
      Stop();
      bluetooth.print(ultrasound_distance());
    }
    else if (strstr(charBuffer, "avoidance") == &charBuffer[0]) {
      command = "avoidance";
    }
    else if (strstr(charBuffer, "force") == &charBuffer[0]) {
      command = "force";
    }
    else if (strstr(charBuffer, "happy") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoSuperHappy);
    }
    else if (strstr(charBuffer, "victory") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoVictory);
    }
    else if (strstr(charBuffer, "sad") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoSad);
    }
    else if (strstr(charBuffer, "sleeping") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoSleeping);
    }
    else if (strstr(charBuffer, "confused") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoConfused);
    }
    else if (strstr(charBuffer, "fail") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoFail);
    }
    else if (strstr(charBuffer, "fart") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoFart);
    }
    else if (strstr(charBuffer, "love") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoLove);
    }
    else if (strstr(charBuffer, "angry") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoAngry);
    }
    else if (strstr(charBuffer, "magic") == &charBuffer[0]) {
      command = "";
      Ottobot.playGesture(OttoMagic);
    }
    // "waltz_stop" precisa vir ANTES de "waltz" (a comparacao e por prefixo)
    else if (strstr(charBuffer, "waltz_stop") == &charBuffer[0]) {
      command = "";
      noTone(BUZZER);
      Stop();
    }
    else if (strstr(charBuffer, "waltz") == &charBuffer[0]) {
      estadoAtual = P_INICIO;     // sempre comeca a valsa do zero
      contadorPassos = 0;
      direcaoDireita = true;
      command = "waltz";
    }
    // "race_stop" / "inspect_stop" precisam vir ANTES de "race" / "inspect"
    else if (strstr(charBuffer, "race_stop") == &charBuffer[0]) {
      command = "";
      Stop();
    }
    else if (strstr(charBuffer, "race") == &charBuffer[0]) {
      command = "race";
    }
    else if (strstr(charBuffer, "inspect_stop") == &charBuffer[0]) {
      command = "";
      noTone(BUZZER);
      estadoInspecao = PAUSADO;
      Stop();
    }
    else if (strstr(charBuffer, "inspect") == &charBuffer[0]) {
      estadoInspecao = INSPECAO_ATIVA;   // sempre comeca uma inspecao nova
      passosAvancados = 0;
      maoDetectada = false;
      command = "inspect";
      Serial.println(F("[SISTEMA] Inspecao ATIVADA via Bluetooth."));
    }
    else if (strstr(charBuffer, "C") == &charBuffer[0]) {
      
      if (calibration == false) {
        Ottobot._moveServos(10, positions);
        calibration = true;
        delay(50);
      } 
      command = "calibration";
      Calibration(charBuffer);
    }
    else if (strstr(charBuffer, "walk_test") == &charBuffer[0]) {
      command = "";
      Ottobot.walk(3, 1000, FORWARD);
    }
    else if (strstr(charBuffer, "save_calibration") == &charBuffer[0]) {
      command = "";
      readChar('s');
    }
  }
}

void Forward() {
  Ottobot.walk(1, move_speed[n], FORWARD);
}

void Backward() {
  Ottobot.walk(1, move_speed[n], BACKWARD);
}

void Right() {
  Ottobot.walk(1, move_speed[n], RIGHT);
}

void Left() {
  Ottobot.walk(1, move_speed[n], LEFT);
}

void Stop() {
  Ottobot.home();
}

void Avoidance() {
  if (ultrasound_distance() <= ultrasound_threeshold) {
    Ottobot.playGesture(OttoConfused);
    for (int count=0 ; count<2 ; count++) {
      Ottobot.walk(1,move_speed[n],-1); // BACKWARD
    }
    for (int count=0 ; count<4 ; count++) {
      Ottobot.turn(1,move_speed[n],1); // LEFT
    }
  }
  Ottobot.walk(1,move_speed[n],1); // FORWARD
}

void UseForce() {
  if (ultrasound_distance() <= ultrasound_threeshold) {
      Ottobot.walk(1,move_speed[n],-1); // BACKWARD
    }
    if ((ultrasound_distance() > 10) && ( ultrasound_distance() < 15)) {
      Ottobot.home();
    }
    if ((ultrasound_distance() > 15) && ( ultrasound_distance() < 30)) {
      Ottobot.walk(1,move_speed[n],1); // FORWARD
    }
    if (ultrasound_distance() > 30) {
      Ottobot.home();
    }  
}

// Move os 4 servos de uma vez: {perna esq, perna dir, pe esq, pe dir}
void waltzPose(int yl, int yr, int rl, int rr, int time_ms) {
  int target[4] = {yl, yr, rl, rr};
  Ottobot._moveServos(time_ms, target);
}

// Espera "ms" milissegundos sem travar o Bluetooth.
// Retorna false se chegou outro comando (ex.: parar valsa) e a danca deve parar.
bool waltzWait(unsigned long ms) {
  unsigned long end_time = millis() + ms;
  while (millis() < end_time) {
    checkBluetooth();
    if (command != "waltz") {
      return false;
    }
  }
  return true;
}

// Executa UM passo da maquina de estados da valsa a cada chamada do loop()
void Waltz() {
  switch (estadoAtual) {

    case P_INICIO:
      // Transicao: T_Cantar_Nota (nota de introducao do compasso)
      tone(BUZZER, NOTE_C4, 300);
      if (!waltzWait(350)) return;
      estadoAtual = P_RITMO_1;
      break;

    case P_RITMO_1:
      // Tempo 1: passo largo e forte para o lado ativo
      tone(BUZZER, NOTE_E4, 300);
      if (direcaoDireita) {
        waltzPose(90, 90, 90, 120, 200);   // Inclina pe direito
        waltzPose(90, 110, 90, 120, 200);  // Avanca perna direita
      } else {
        waltzPose(90, 90, 60, 90, 200);    // Inclina pe esquerdo
        waltzPose(70, 90, 60, 90, 200);    // Avanca perna esquerda
      }
      if (!waltzWait(400)) return;
      estadoAtual = P_RITMO_2_3;
      break;

    case P_RITMO_2_3:
      // Tempos 2 e 3: dois toques rapidos para fechar a base
      tone(BUZZER, NOTE_G4, 200);
      if (!waltzWait(250)) return;
      tone(BUZZER, NOTE_G4, 200);
      if (!waltzWait(250)) return;

      Ottobot.home();                      // Junta os pes (alinha o corpo)
      if (!waltzWait(300)) return;

      contadorPassos++;
      if (contadorPassos >= 2) {           // Completou 2 passos para o lado?
        contadorPassos = 0;
        estadoAtual = P_GIRO;
      } else {
        estadoAtual = P_INICIO;
      }
      break;

    case P_GIRO:
      // Transicao: T_Executa_Giro (nota aguda e rotacao)
      tone(BUZZER, NOTE_C5, 500);
      if (direcaoDireita) {
        waltzPose(90, 120, 90, 90, 200);    // Gira no sentido horario
        waltzPose(120, 120, 90, 90, 200);
      } else {
        waltzPose(90, 60, 90, 90, 200);     // Gira no sentido anti-horario
        waltzPose(60, 60, 90, 90, 200);
      }
      if (!waltzWait(600)) return;

      Ottobot.home();                       // Volta a postura reta
      if (!waltzWait(400)) return;

      direcaoDireita = !direcaoDireita;     // Efeito espelho
      estadoAtual = P_INICIO;
      break;
  }
}

// ================== CORRIDA DE OBSTACULOS ==================
// Leitura unica do HC-SR04. Retorna cm (999 = sem eco)
float lerUltrassomUmaVez() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracao = pulseIn(ECHO, HIGH, 60000);   // timeout de 60ms (~10m)
  if (duracao == 0) return 999.0;
  return (float)duracao / 58.0;
}

// Faz 3 leituras espacadas de 50ms (o HC-SR04 precisa de ~50-60ms entre disparos,
// senao o eco anterior gera leituras falsas) e devolve a MEDIANA, que descarta
// leituras erradas isoladas tanto para menos quanto para mais.
float medirDistancia() {
  float v[3];
  for (int k = 0; k < 3; k++) {
    v[k] = lerUltrassomUmaVez();
    delay(50);
  }
  // ordena as 3 leituras e pega a do meio
  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 2 - x; y++) {
      if (v[y] > v[y + 1]) { float t = v[y]; v[y] = v[y + 1]; v[y + 1] = t; }
    }
  }
  return v[1];
}

// Executa UM ciclo da corrida a cada chamada do loop()
void Race() {
  // Leitura rapida (sem pausa de ~150ms entre passos). So confirma com uma 2a
  // leitura quando parece haver obstaculo, para evitar falso alarme.
  float distancia = lerUltrassomUmaVez();
  if (distancia <= DISTANCIA_LIMITE) {
    delay(50);
    float confirmacao = lerUltrassomUmaVez();
    if (confirmacao > distancia) distancia = confirmacao;
  }
  Serial.print(F("[CORRIDA] distancia: "));
  Serial.println(distancia);

  if (distancia > DISTANCIA_LIMITE) {
    Ottobot.walk(1, 400, FORWARD);          // passo rapido (corrida)
  } else {
    Ottobot.home();                         // 1. para
    Ottobot.sing(S_cuddly);                 // 2. alerta sonoro
    Ottobot.walk(2, 800, BACKWARD);         // 3. 2 passos para tras
    Ottobot.turn(3, 800, RIGHT);            // 4. gira a direita
    Ottobot.home();
  }
}

// ================== ROBO INSPETOR DE DUTOS ==================
// Alterna INSPECAO_ATIVA <-> PAUSADO se a mao ficar < 5cm por 1.5s
void verificarBotaoVirtual(float distanciaAtual) {
  if (distanciaAtual > 0.0 && distanciaAtual <= DISTANCIA_BOTAO_MAX) {
    if (!maoDetectada) {
      maoDetectada = true;
      tempoInicioGesto = millis();
    } else if (millis() - tempoInicioGesto >= TEMPO_HOLD_BOTAO_MS) {
      if (estadoInspecao == INSPECAO_ATIVA) {
        estadoInspecao = PAUSADO;
        Ottobot.home();
        Serial.println(F("[SISTEMA] Inspecao PAUSADA via Botao Virtual."));
        tone(BUZZER, 440, 300);
      } else {
        estadoInspecao = INSPECAO_ATIVA;
        Serial.println(F("[SISTEMA] Inspecao ATIVADA via Botao Virtual."));
        tone(BUZZER, 880, 150); delay(200); tone(BUZZER, 1760, 150);
      }

      // Aguarda a mao sair (sem travar o Bluetooth)
      while (medirDistancia() <= DISTANCIA_BOTAO_MAX) {
        checkBluetooth();
        if (command != "inspect") break;
        delay(100);
      }
      maoDetectada = false;
    }
  } else {
    maoDetectada = false;
  }
}

// Executa UM ciclo da maquina de estados do inspetor a cada chamada do loop()
void Inspector() {
  float distancia = medirDistancia();
  Serial.print(F("[INSPETOR] distancia: "));
  Serial.println(distancia);

  if (estadoInspecao != BLOQUEADO_AGUARDANDO_RESGATE) {
    verificarBotaoVirtual(distancia);
  }

  switch (estadoInspecao) {

    case PAUSADO:
      delay(100);
      break;

    case INSPECAO_ATIVA:
      if (distancia > DISTANCIA_LIVRE_MIN) {
        tone(BUZZER, 1000, 50);
        Ottobot.walk(1, 800, FORWARD);
        passosAvancados++;
        Serial.print(F("Progresso da Inspecao - Profundidade acumulada: "));
        Serial.print(passosAvancados);
        Serial.println(F(" passo(s)"));
      }
      else if (distancia > DISTANCIA_BOTAO_MAX && distancia <= DISTANCIA_LIVRE_MIN) {
        Serial.println(F("--------------------------------------------------"));
        Serial.print(F("BLOQUEIO DETECTADO no passo "));
        Serial.print(passosAvancados);
        Serial.println(F("! Iniciando protocolo de resgate..."));
        Serial.println(F("--------------------------------------------------"));

        Ottobot.sing(S_sad);
        Ottobot.walk(1, 800, BACKWARD);   // recuo de seguranca
        Ottobot.detachServos();           // libera os servos para resgate manual
        estadoInspecao = BLOQUEADO_AGUARDANDO_RESGATE;
      }
      break;

    case BLOQUEADO_AGUARDANDO_RESGATE:
      tone(BUZZER, 500, 150);
      delay(150);
      tone(BUZZER, 300, 150);
      delay(700);

      // Operador pode destravar com o botao virtual (mao < 5cm por 1.5s)
      if (medirDistancia() <= DISTANCIA_BOTAO_MAX) {
        verificarBotaoVirtual(medirDistancia());
      }
      break;
  }
}

void Settings(String ts_ultrasound) {
  ultrasound_threeshold = ts_ultrasound.toInt();
}

void Calibration(String c) {
  if (sync_time < millis()) {
      sync_time = millis() + 50;
      for (int k = 1; k < c.length(); k++) {
        readChar((c[k]));
      }
  } 
}

void readChar(char ch) {
  switch (ch) {
  case '0'...'9':
    v = (v * 10 + ch) - 48;
    break;
   case 'a':
    trims[0] = v-90;
    setTrims();
    v = 0;
    break;
   case 'b':
    trims[1] = v-90;
    setTrims();
    v = 0;
    break;
   case 'c':
    trims[2] = v-90;
    setTrims();
    v = 0;
    break;
   case 'd':
    trims[3] = v-90;
    setTrims();
    v = 0;
    break;
   case 's':
    for (i=0 ; i<=3 ; i=i+1) {
      EEPROM.write(i,trims[i]);
    }
    delay(500);
    Ottobot.sing(S_superHappy);
    Ottobot.crusaito(1, 1000, 25, -1);
    Ottobot.crusaito(1, 1000, 25, 1);
    Ottobot.sing(S_happy_short);
    break;
  }
}

void setTrims() {
  Ottobot.setTrims(trims[0],trims[1],trims[2],trims[3]);
  Ottobot._moveServos(10, positions); 
}
