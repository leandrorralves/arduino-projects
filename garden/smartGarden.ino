//Carrega a biblioteca do RTC DS1307
#include <DS1307.h>

int moistureSensorPin = A0; // Variable addressed to the analog pin A0 which Will receive the signal from the sensor
int moistureSensorValue = 0; // variable that will store the value from  moistureSensorPin
int minSensorValue = 800;

int relayPin = 8;

//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino
DS1307 rtc(A4, A5);
String relayOnHour = "17:01:00";
String timeNow = "";

void setup() {
  // put your setup code here, to run once:
  //Aciona o relogio
  rtc.halt(false);

  //ATENCAO: As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  //rtc.setDOW(WEDNESDAY);      //Define o dia da semana
  //rtc.setTime(16, 15, 0);     //Define o horario
  //rtc.setDate(30, 11, 2016);   //Define o dia, mes e ano

  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);

  Serial.begin(9600); // set the baud rate serial with 9600
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  moistureSensorValue = analogRead(moistureSensorPin); // Reads the value from the sensor and store in moistureSensorValue                                                                                                                         delay(1000);

  // Prints on the serial the value stored in moistureSensorValue
  Serial.print("moistureSensor = " );
  Serial.println(moistureSensorValue);

  //Mostra as informações no Serial Monitor
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));

  timeNow = rtc.getTimeStr();
  
  if (timeNow.equals(relayOnHour)) {
    if (moistureSensorValue < minSensorValue) {
      digitalWrite(relayPin, HIGH); // Rele ligado
      //Serial.print("rele ligado");
    }
    else {
      digitalWrite(relayPin, LOW); // Rele desligado
      //Serial.print("rele desligado");
    }
  }

  //Tempo de espera de 1 segundo entre uma leitura e outra
  delay(1000);
}
