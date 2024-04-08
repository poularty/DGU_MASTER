#include "GSM_My.h"
#include "util/USSD.h"
#include "service.h"
#include "util/charFunc.h"
#include "mqtt.h"
#include "gnss.h"
#include "sms.h"
#include <bitset>

// #include "util/variable.h"

#include <HardwareSerial.h>
#include <SoftwareSerial.h>

 // = {
//   .bal = "\"*102#\"",
//   .APN = "internet.beeline.ru"
// };


// конструктор класса
GSM_Un::GSM_Un(Stream &Ser_GSM, Stream &Debug) {
  _Ser_GSM = &Ser_GSM;
  _Debug = &Debug;
  pinMode(23, INPUT_PULLUP);
  if (!digitalRead(_Pin_All_init)) _flag_All_init = true;
  SafeConnect.start((KEEP_ALIVE * 1000)/2);
  TimePublish.start(PUBLISH_TIMER * 1000);


  _Ser_GSM  -> write("ATE0");             // отключаем дублирование команд
  _Ser_GSM  -> write('\n');
}
// -------------------------------------------------------------------------------

/*
// void GSM_Un::StartUartRead(){
//   xTaskCreate(this->ReadUartGSM, "ReadUartGSM", 10000, NULL, 1, NULL);
// }
//
//
// void GSM_Un::ReadUartGSM(void * parameter){
//   ((GSM_Un*)parameter) -> _ReadUartGSM();
// }
//
// void GSM_Un::_ReadUartGSM() {
//   char BuferUartTask[1000] = "";
//   for(;;) {//infinite loop
//
//     if (_Ser_GSM ->available()){           // Ожидаем прихода данных (ответа) от модема...
//       memset(BuferUartTask, NULL, sizeof(BuferUartTask));
//       _Ser_GSM -> readBytes(BuferUartTask, 1000);    // ...и выводим их в Serial
//       _Debug -> println(BuferUartTask);
//     }
//
//     vTaskDelay(50);
//   }
// }
*/


// конструктор класса
GSM_Un::GSM_Un(Stream &Ser_GSM, Stream &Debug, char* _Oper) {
  _Ser_GSM = &Ser_GSM;
  _Debug = &Debug;
  pinMode(23, INPUT_PULLUP);
  if (!digitalRead(_Pin_All_init)) _flag_All_init = true;
  SafeConnect.start((KEEP_ALIVE * 1000)/2);
  // SafeConnect.start((KEEP_ALIVE * 1000)/ 2);
  TimePublish.start(PUBLISH_TIMER * 1000);

  if (strstr(_Oper, "MEGAFON") != NULL){
    _OPER_OUT = &MEGAFON;
  }
  if (strstr(_Oper, "BEELINE") != NULL){
    _OPER_OUT = &BEELINE;
  }
  // xTaskCreatePinnedToCore(this->ReadUartGSM, "ReadUartGSM", 10000, NULL, 1, NULL,  0);

  _Ser_GSM  -> write("ATE0");             // отключаем дублирование команд
  _Ser_GSM  -> write('\n');
}
// -------------------------------------------------------------------------------

void GSM_Un::GSM_listen_Uart(){
  char BuferUartTask[1000] = "";

  // _Debug -> print("1");

  if (_Ser_GSM -> available()){           // Ожидаем прихода данных (ответа) от модема...
    memset(BuferUartTask, NULL, sizeof(BuferUartTask));
    _Ser_GSM -> readBytes(BuferUartTask, 1000);    // ...и выводим их в Serial

    // =============================================================================================
    _Debug -> print("Listen uart = "), _Debug -> println(BuferUartTask);
    // =============================================================================================

    // vTaskDelay(100);

    // _Debug -> print("2");
    if (_data_start){
      _Debug -> println("Start data");
      xQueueSend(queue_bufer, &BuferUartTask, 100/portTICK_RATE_MS);
      // _Debug -> print("3");
    }
    if (strstr(BuferUartTask, "+CIPRXGET: 1") != 0) {
      _Debug -> println("Yes CIPRXGET");
      _CIPRXGET_start = true;
      xSemaphoreGive(CIPRXGET_start);
      // xQueueSend(queue_CIPRXGET, &BuferUartTask, 100/portTICK_RATE_MS);
      // _Debug -> print("4");
    }
    if (_CIPRXGET_start) {
      xQueueSend(queue_CIPRXGET, &BuferUartTask, 100/portTICK_RATE_MS);
      // _Debug -> print("5");
    }

    if (_ballans_start) {
      xQueueSend(queue_ballans, &BuferUartTask, 100/portTICK_RATE_MS);
      // _Debug -> print("5");
    }

    if (strstr(BuferUartTask, "CLOSED") != NULL){
      _data_start = false;
      // _Debug -> println(" Semaphore Reconnect_Sem Start in GSM_listen_Uart");xSemaphoreGive(Reconnect_Sem);
      _Debug -> println("Reconnect flag true in GSM_listen_Uart");
      Reconnect_Task_flag = true;
    }

  }
}


void GSM_Un::DebugPrint(char* Line){
  _Debug   -> write('\n');
  _Debug   -> write(">>");
  _Debug   -> write(Line);
}

void GSM_Un::ClearBuferUart(int Timeout){
  char _in[1000] = "";
  uint64_t timeOld = millis();
  while((timeOld - millis()) < Timeout){
    _Ser_GSM -> readBytes(_in, 1000);
    memset(_in, NULL, sizeof(_in));
  }
}

void GSM_Un::ChekBuferGSMIn(){
  if (_Ser_GSM -> available()){

  }
}

// функция проверки подключения к модулю через команду АТ
char* GSM_Un::waitingUart(uint64_t Timeout){
  char result[500] = "";
  uint64_t timeOld = millis();
  while (strstr(result, "OK") == NULL && (millis() - timeOld) < Timeout){
    strcat(result, AT_as("AT"));
    // DebugPrint(result);
  }
  return result;
}
// фунция отправки команд модулю
char* GSM_Un::AT(char* Command){

  // если в буфере есть информация, вычитать для очистки
  ClearBuferUart(500);
  memset(Bufer, NULL, sizeof(Bufer));

  _Debug   -> write(">>");
  _Debug   -> write(Command);


  _Ser_GSM -> write(Command);
  _Ser_GSM -> write('\n');
  _Ser_GSM -> readBytes(Bufer, 1000);

  // uint64_t timeOld = millis();
  // int i = 0;
  // while( _Ser_GSM -> available()){
  //
  //   Bufer[i] = _Ser_GSM -> read();
  //   if ((millis() - timeOld > _TimeoutResponce)) break;
  // }

  _Debug   -> write('\n');
  _Debug   -> write("<<");
  _Debug   -> write(Bufer);

  return Bufer;
}

char* GSM_Un::AT_as(char* Command){
  _data_start = true;
  // delay(20);
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;
    // если в буфере есть информация, вычитать для очистки
  // ClearBuferUart(500);
  _Ser_GSM -> println(Command);
  // vTaskDelay(1000);
  xQueueReceive(queue_bufer, &result1, 1000/portTICK_RATE_MS);

  _Debug   -> print(">>AS>> ");
  _Debug   -> println(Command);


  // _Debug -> print("result1 = "), _Debug -> println(result1);
 time = millis();
  while((strstr(result1, "OK") == NULL) && ((millis() - time) < 2000)) {
    xQueueReceive(queue_bufer, &result2, 1000/portTICK_RATE_MS);
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }
  memset(Bufer, NULL, sizeof(Bufer));
  strcat(Bufer, result1);
  _data_start = false;
  return Bufer;
}

char* GSM_Un::AT_as(char* Command, int Wait){
  _data_start = true;
  delay(20);
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;
    // если в буфере есть информация, вычитать для очистки
  // ClearBuferUart(500);

  _Debug   -> print(">>AS>> ");
  _Debug   -> println(Command);

  _Ser_GSM -> println(Command);

  xQueueReceive(queue_bufer, &result1, 1000/portTICK_RATE_MS);
  // _Debug -> print("result1 = "), _Debug -> println(result1);
 time = millis();
  while((strstr(result1, "OK") == NULL) && ((millis() - time) < (Wait*1000))) {
    xQueueReceive(queue_bufer, &result2, 1000/portTICK_RATE_MS);
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }
  memset(Bufer, NULL, sizeof(Bufer));
  strcat(Bufer, result1);
  _data_start = false;
  return Bufer;
}

// фунция отправки команд модулю с контролем ответа
char* GSM_Un::AT(char* Command, char* Responce){
  // если в буфере есть информация, вычитать для очистки
  ClearBuferUart(500);

  memset(Bufer, NULL, sizeof(Bufer));
  memset(Inc, NULL, sizeof(Inc));

  DebugPrint(Command);


  _Ser_GSM -> write(Command);
  _Ser_GSM -> write('\n');
  int i = 0;

  // _Ser_GSM -> readBytesUntil('\r', Bufer, 200);
  // Bufer[0] = '';
  uint64_t timeOld = millis();
  while (strstr(Bufer, Responce) == NULL) {
    memset(Inc, '\0', sizeof(Inc));
    _Ser_GSM -> readBytesUntil('\r', Inc, 200);
    strcat(Bufer, Inc);
    // delay(5);
    if ((millis() - timeOld > _TimeoutResponce)) return "Note Responce";
  }
  memset(Inc, '\0', sizeof(Inc));
  _Ser_GSM -> readBytes(Inc, 200);
  strcat(Bufer, Inc);

  DebugPrint(Bufer);

  return Bufer;
}

char* GSM_Un::AT_as(char* Command, char* Responce){
  _data_start = true;
  delay(20);
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;
    // если в буфере есть информация, вычитать для очистки
  ClearBuferUart(500);
  memset(Bufer, NULL, sizeof(Bufer));

  _Debug   -> print(">>AS>> ");
  _Debug   -> println(Command);

  _Ser_GSM -> println(Command);

  xQueueReceive(queue_bufer, &result1, 1000/portTICK_RATE_MS);
  // _Debug -> print("result1 = "), _Debug -> println(result1);
 time = millis();
  while((strstr(result1, Responce) == NULL) && ((millis() - time) < 2000)) {
    xQueueReceive(queue_bufer, &result2, 1000/portTICK_RATE_MS);
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }
  memset(Bufer, NULL, sizeof(Bufer));
  strcat(Bufer, result1);
  _data_start = false;
  return Bufer;
}

char* GSM_Un::AT_as(char* Command, char* Responce1, char* Responce2){
  _data_start = true;
  delay(20);
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;
    // если в буфере есть информация, вычитать для очистки
  ClearBuferUart(500);
  memset(Bufer, NULL, sizeof(Bufer));

  _Debug   -> print(">>AS>> ");
  _Debug   -> println(Command);

  _Ser_GSM -> println(Command);

  xQueueReceive(queue_bufer, &result1, 1000/portTICK_RATE_MS);
  // _Debug -> print("result1 = "), _Debug -> println(result1);
 time = millis();
  while((strstr(result1, Responce1) == NULL) && (strstr(result1, Responce2) == NULL) && ((millis() - time) < 2000)) {
    xQueueReceive(queue_bufer, &result2, 1000/portTICK_RATE_MS);
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }
  memset(Bufer, NULL, sizeof(Bufer));
  strcat(Bufer, result1);
  _data_start = false;
  return Bufer;
}

char* GSM_Un::AT_as(char* Command, char* Responce1, char* Responce2, char* Responce3){
  _data_start = true;
  delay(20);
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;
    // если в буфере есть информация, вычитать для очистки
  ClearBuferUart(500);
  memset(Bufer, NULL, sizeof(Bufer));

  _Debug   -> print(">>AS>> ");
  _Debug   -> println(Command);

  _Ser_GSM -> println(Command);

  xQueueReceive(queue_bufer, &result1, 3000/portTICK_RATE_MS);
  // _Debug -> print("result1 = "), _Debug -> println(result1);
 time = millis();
  while((strstr(result1, Responce1) == NULL) &&
   (strstr(result1, Responce2) == NULL) &&
    (strstr(result1, Responce3) == NULL) &&
     ((millis() - time) < 10000)) {
    xQueueReceive(queue_bufer, &result2, 2000/portTICK_RATE_MS);
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }
  memset(Bufer, NULL, sizeof(Bufer));
  strcat(Bufer, result1);
  _data_start = false;
  _Debug -> print("#"), _Debug -> print(Bufer), _Debug -> println("#");
  return Bufer;
}

char* GSM_Un::AT_as(char* Command, char* Responce1, char* Responce2, char* Responce3, char* Responce4){
  _data_start = true;
  delay(20);
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;
    // если в буфере есть информация, вычитать для очистки
  ClearBuferUart(500);
  memset(Bufer, NULL, sizeof(Bufer));

  _Debug   -> print(">>AS>> ");
  _Debug   -> println(Command);

  _Ser_GSM -> println(Command);

  xQueueReceive(queue_bufer, &result1, 3000/portTICK_RATE_MS);
  // _Debug -> print("result1 = "), _Debug -> println(result1);
 time = millis();
  while((strstr(result1, Responce1) == NULL) &&
   (strstr(result1, Responce2) == NULL) &&
    (strstr(result1, Responce3) == NULL) &&
     (strstr(result1, Responce4) == NULL) &&
     ((millis() - time) < 10000)) {
    xQueueReceive(queue_bufer, &result2, 2000/portTICK_RATE_MS);
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }
  memset(Bufer, NULL, sizeof(Bufer));
  strcat(Bufer, result1);
  _data_start = false;
  _Debug -> print("#"), _Debug -> print(Bufer), _Debug -> println("#");
  return Bufer;
}

char* GSM_Un::AT(int n, ... ){
  char result[200] = "";
  va_list vl;
  va_start (vl, n);
  for (int i = 0; i < n; i++){
    strcat(result, va_arg(vl, char*));
  }
  va_end(vl);

  AT(result);

  return Bufer;
}

char* GSM_Un::AT_as(int n, ... ){
  char result[200] = "";
  va_list vl;
  va_start (vl, n);
  for (int i = 0; i < n; i++){
    strcat(result, va_arg(vl, char*));
  }
  va_end(vl);

  AT_as(result);

  return Bufer;
}

// фунция отправки команд модулю с контролем ответа и номером ответа
char* GSM_Un::AT(char* Command, char* Responce, byte num){
  // если в буфере есть информация, вычитать для очистки
  ClearBuferUart(500);
  memset(Bufer, NULL, sizeof(Bufer));
  memset(Inc, NULL, sizeof(Bufer));

  DebugPrint(Command);


  _Ser_GSM -> write(Command);
  _Ser_GSM -> write('\n');
  // int i = 0;

  // _Ser_GSM -> readBytesUntil('\r', Bufer, 200);
  // Bufer[0] = '';

  for ( int i = 0; i < num; i++) {
    memset(Bufer, NULL, sizeof(Bufer));
    uint64_t timeOld = millis();
      while (strstr(Bufer, Responce) == NULL) {
        memset(Inc, '\0', sizeof(Bufer));
        _Ser_GSM -> readBytesUntil('\r', Inc, 200);
        strcat(Bufer, Inc);
        // delay(5);
        if ((millis() - timeOld > _TimeoutResponce)) return "Note Responce";
      }

  }

  memset(Inc, '\0', sizeof(Inc));
  _Ser_GSM -> readBytes(Inc, 200);
  strcat(Bufer, Inc);

  DebugPrint(Bufer);

  return Bufer;
}
// фунция отправки команд модулю с установкой таймаута чтения буфера uart
char* GSM_Un::AT(char* Command, int Timeout){
  // если в буфере есть информация, вычитать для очистки
  ClearBuferUart(500);
  memset(Bufer, NULL, sizeof(Bufer));
  _Ser_GSM -> setTimeout(Timeout);

  DebugPrint(Command);


  _Ser_GSM -> write(Command);
  _Ser_GSM -> write('\n');
  _Ser_GSM -> readBytes(Bufer, 1000);

  DebugPrint(Bufer);

  _Ser_GSM -> setTimeout(_TimeoutDefault);

  return Bufer;
}
// -------------------------------------------------------------------------------
char* GSM_Un::AT(char* Command, char* Responce, int Timeout){
  // если в буфере есть информация, вычитать для очистки
  ClearBuferUart(500);

  memset(Bufer, NULL, sizeof(Bufer));
  memset(Inc, NULL, sizeof(Inc));

  DebugPrint(Command);

  _Ser_GSM -> setTimeout(Timeout);
  _Ser_GSM -> write(Command);
  _Ser_GSM -> write('\n');
  int i = 0;

  // _Ser_GSM -> readBytesUntil('\r', Bufer, 200);
  // Bufer[0] = '';
  uint64_t timeOld = millis();
  while (strstr(Bufer, Responce) == NULL) {
    memset(Inc, '\0', sizeof(Inc));
    _Ser_GSM -> readBytesUntil('\r', Inc, 200);
    strcat(Bufer, Inc);
    // delay(5);
    if ((millis() - timeOld > _TimeoutResponce)) {
      _Ser_GSM -> setTimeout(_TimeoutDefault);
      return "Note Responce";
    }
  }
  memset(Inc, '\0', sizeof(Inc));
  // _Ser_GSM -> readBytes(Inc, 200);
  _Ser_GSM -> readBytesUntil('\r', Inc, 200);
  strcat(Bufer, Inc);

  DebugPrint(Bufer);
  _Ser_GSM -> setTimeout(_TimeoutDefault);
  return Bufer;
}
