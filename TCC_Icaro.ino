/*
   Criado por Ícaro da Silva Misquita em 2016
   Discente de Engenharia Agrícola e Ambiental
   Sobre orientação dos docentes: Wagner Dias de Souza
                                            Marcus Vinicius Morais de Oliveira
   Universidade Federal Rural do Rio de Janeiro (UFRRJ)
   Departamento de Engenharia
   Instituto de Tecnologia (IT)
     
  Este programa tem como função obter e guardar dados dos sensores de temperatura LM35 (de temperatura), DHT 11 (de umidade) e o LDR (de luminosidade) e sua posterior  gravação em um cartão SD.

     O circuito
   Sensores LM35 conectados às portas analógicas A0 à A6
 * * Alimentados pela porta VIN

   Sensor LDR conectado a portas A12
   Sensores DHT11 conectados às portas digitais 2 à 6

    Cartão SD
 * * Porta 50 pino MISO
 * * Porta 51 pino MOSI
 * * Porta 52 pino SCK
 * * Porta 53 pino CS
 * * Alimentados pela porta 5V

   Todos ligados ao pino terra GND

      
*/

// Definição de variáveis globais

int tm0;
int tm1;
int tm2;
int tm3;     // Definição de variáveis que tratarão as leituras dos sensores LM35
int tm4;
int tm5;
int tm6;
int tempPin0 = 0;
int tempPin1 = 1;
int tempPin2 = 2;
int tempPin3 = 3;          // Definição das portas analógicas usadas pelo sensor LM35
int tempPin4 = 4;
int tempPin5 = 5;
int tempPin6 = 6;
unsigned long segundo;
unsigned long minuto;        // Definição de variáveis do contador de tempo
unsigned long hora;
unsigned long ts;
#include <DHT.h>             // Inclusão da biblioteca do DHT11
DHT dht1(2, DHT11);
DHT dht2(3, DHT11);
DHT dht3(4, DHT11);    // Definição das portas digitais e o tipo do de sensor DHT11
DHT dht4(5, DHT11);         // DHT dht1 (porta digital, tipo de sensor DHT)
DHT dht5(6, DHT11);
double h[5];                // Conversão da variável inteira int para uma variável double
double t[5];                // Operação necessária para que os sensores possam demonstrar medidas fracionárias
String S;                   // Definição da variável tipo String, nela serão armazenados os dados temporariamente antes deles serem transferidos ao SD
#include <SPI.h>
#include <SD.h>             // Inclusão da biblioteca do cartão SD
const int chipSelect = 53;  // Definição do pino de comunicação do SD com o Arduino
int id = 1;
File dataFile;              // Criação da variável datafile, que será a variável de escrita no SD
int LDR;                    // Definição da variável que tratará as leituras do LDR
int LDRPin = 12;            // Definição do pino analógico do LDR

void setup() {           // Etapa de setup, nesta são inicializados os sensores e definida a velocidade de operação do Arduino
  Serial.begin (9600);   // Definição da velocidade
  dht1.begin();
  dht2.begin();
  dht3.begin();         // Inicialização dos sensores DHT11
  dht4.begin();
  dht5.begin();
  Serial.println("Iniciando cartao SD...");  // Teste do módulo do cartão SD
  delay(5000);
  if (!SD.begin(53)) {
    Serial.println("Falha na inicializacao!");
    setup();
  }
  else {
    dataFile = SD.open("datalog.txt", FILE_WRITE);    // Caso o módulo esteja funcionando corretamente cria-se um arquivo .txt onde as leituras serão escritas
    if (dataFile) {
      Serial.println("Arquivo criado com sucesso.");
      Serial.println("Inicializacao concluida.");
      Serial.print("ID Timestamp ");
      dataFile.print("ID Timestamp ");
      for (int i = 1; i < 6; i++) {
        S = "Sensor_";
        Serial.print(S);
        dataFile.print(S);
        S = i;
        Serial.print(S);                                   // Etapa onde será realizada a impressão do cabeçalho do sensor de umidade,
        dataFile.print(S);                                 // para organizar os dados em uma tabela
        S = "_Humidity ";
        Serial.print(S);
        dataFile.print(S);
      }
      for (int i = 6; i < 12; i++)
      {
        String S = "Sensor_";
        Serial.print(S);
        dataFile.print(S);
        S = i;
        Serial.print(S);                                  // Etapa onde a o cabeçalho do sensor de temperatura será impresso no programa
        dataFile.print(S);                                // Organizando os dados em uma tabela lógica
        S = "_Temp ";
        Serial.print(S);
        dataFile.print(S);
      }
      for (int i = 12; i < 14; i++)
      {
        String S = "Sensor_";
        Serial.print(S);
        dataFile.print(S);
        S = i;
        Serial.print(S);                                  // Etapa onde a o cabeçalho do sensor de luminosidade será impresso no programa
        dataFile.print(S);
        S = "_LDR";
        Serial.print(S);
        dataFile.print(S);
      }
      Serial.print("\n");
      dataFile.println("");
      dataFile.close();
    }
    else {
      Serial.println("Nao foi possivel abrir o arquivo");       // Caso o módulo do SD não for encontrado o programa imprime esta frase ao usuário
      setup();                                                  // e retorna a etapa de Setup, até o SD for encontrado o programa repetirá estes passos
    }
  }
}
void loop() {                                                 // Neste ponto a rotina do programa será escrita, a rotina se repetirá enquanto o Arduino estiver ligado
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    h[0] = dht1.readHumidity();
    h[1] = dht2.readHumidity();
    h[2] = dht3.readHumidity();                              // Etapa de gravação dos dados de umidade no SD
    h[3] = dht4.readHumidity();
    h[4] = dht5.readHumidity();
    Serial.print(id);
    dataFile.print(id);
    Serial.print(" ");
    dataFile.print(" ");
    ts = millis() / 1000;
    segundo = ts % 60;
    minuto = ts / 60;
    minuto = minuto % 60;
    hora = ts / 3600;
    Serial.print(hora);
    Serial.print(":");
    Serial.print(minuto);
    Serial.print(":");
    Serial.print(segundo);                                // Etapa de gravação do tempo no cartão SD
    dataFile.print(hora);
    dataFile.print(":");
    dataFile.print(minuto);
    dataFile.print(":");
    dataFile.print(segundo);

    Serial.print(" ");
    dataFile.print(" ");

    for (int i = 0; i < 5; i++) {        // Etapa de gravação dos dados de temperatura no SD
      Serial.print(h[i]);
      dataFile.print(h[i]);
      Serial.print(" ");
      dataFile.print(" ");
    }
    tm0 = analogRead(tempPin0);
    float milivolts0 = (tm0 / 1024.0) * 5000;    // Conversão das leituras do LM35 em graus Celsius
    float celsius0 = (milivolts0 / 10);
    Serial.print(celsius0);
    Serial.print(" ");
    dataFile.print(celsius0);
    dataFile.print(" ");

    tm1 = analogRead(tempPin1);
    float milivolts1 = (tm1 / 1024.0) * 5000;
    float celsius1 = (milivolts1 / 10);
    Serial.print(celsius1);
    Serial.print(" ");
    dataFile.print(celsius1);
    dataFile.print(" ");

    tm2 = analogRead(tempPin2);
    float milivolts2 = (tm2 / 1024.0) * 5000;
    float celsius2 = (milivolts2 / 10);
    Serial.print(celsius2);
    Serial.print(" ");
    dataFile.print(celsius2);
    dataFile.print(" ");

    tm3 = analogRead(tempPin3);
    float milivolts3 = (tm3 / 1024.0) * 5000;
    float celsius3 = (milivolts3 / 10);
    Serial.print(celsius3);
    Serial.print(" ");
    dataFile.print(celsius3);
    dataFile.print(" ");

    tm4 = analogRead(tempPin4);
    float milivolts4 = (tm4 / 1024.0) * 5000;
    float celsius4 = (milivolts4 / 10);
    Serial.print(celsius4);
    Serial.print(" ");
    dataFile.print(celsius4);
    dataFile.print(" ");

    tm5 = analogRead(tempPin5);
    float milivolts5 = (tm5 / 1024.0) * 5000;
    float celsius5 = (milivolts5 / 10);
    Serial.print(celsius5);
    Serial.print(" ");
    dataFile.print(celsius5);
    dataFile.print(" ");

    tm6 = analogRead(tempPin6);
    float milivolts6 = (tm6 / 1024.0) * 5000;
    float celsius6 = (milivolts6 / 10);
    Serial.print(celsius6);
    dataFile.print(celsius6);
    dataFile.print(" ");


    LDR = analogRead(LDRPin);                                  //Etapa de conversão da leitura do LDR em LUX
    float milivoltsLDR = (LDR / 1024.0);
    Serial.println(milivoltsLDR);
    dataFile.println(milivoltsLDR);


    id++;
  }

  else {
    Serial.println("Nao foi possivel abrir o arquivo");
    return;
  }
  dataFile.close();
  delay (3000);                       // Definição do intervalo entre as leituras em milisegundos
}

