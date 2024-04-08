// #include "GSM_My.h"
// #include "variable.h"
// #include "charFunc.h"

// =======================0====1=====2====3====4====5====6====7====8====9===10===11===12===13===14===15
// char *CharKir[] = { "\0", "YO", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0",
//                                "A\0", "B\0",  "V\0", "G\0", "D\0", "E\0", "J\0", "Z\0", "I\0", "Y\0", "K\0", "L\0", "M\0", "N\0", "O\0", "P\0",
//                                "R\0", "S\0",  "T\0", "U\0", "F\0", "H\0", "C\0", "CH\0","SH\0","SH\0", "''\0", "Y\0","\'\0", "E\0", "YU\0","YA\0",
//                                "a\0", "b\0",  "v\0", "g\0", "d\0", "e\0", "j\0", "z\0", "i\0", "y\0", "k\0", "l\0", "m\0", "n\0", "o\0", "p\0",
//                                "r\0", "s\0",  "t\0", "u\0", "f\0", "h\0", "c\0", "ch\0","sh\0","ch\0", "''\0", "y\0", "\'\0","e\0", "yu\0","ya\0",
//                                "N'\0","yo\0" }; // " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
//


void GSM_Un::Transliterate(char* str, uint8_t Chr)
{
        // for (; *str != 0; str++)
        // {
            switch (Chr)
              {
                case 1: strcat(str, "Ye"); break;
                case 16: strcat(str, "A"); break;
                case 17: strcat(str, "B"); break;
                case 18: strcat(str, "V"); break;
                case 19: strcat(str, "G"); break;
                case 20: strcat(str, "D"); break;
                case 21: strcat(str, "E"); break;
                case 22: strcat(str, "Zh");break;
                case 23: strcat(str, "Z"); break;
                case 24: strcat(str, "I"); break;
                case 25: strcat(str, "Y"); break;
                case 26: strcat(str, "K"); break;
                case 27: strcat(str, "L"); break;
                case 28: strcat(str, "M"); break;
                case 29: strcat(str, "N"); break;
                case 30: strcat(str, "O"); break;
                case 31: strcat(str, "P"); break;
                case 32: strcat(str, "R"); break;
                case 33: strcat(str, "S"); break;
                case 34: strcat(str, "T"); break;
                case 35: strcat(str, "U"); break;
                case 36: strcat(str, "F"); break;
                case 37: strcat(str, "Ch"); break;
                case 38: strcat(str, "Z"); break;
                case 39: strcat(str, "Ch"); break;
                case 40: strcat(str, "Sh"); break;
                case 41: strcat(str, "Ch"); break;
                case 42: strcat(str, "''"); break;
                case 43: strcat(str, "Y"); break;
                case 44: strcat(str, "''"); break;
                case 45: strcat(str, "E"); break;
                case 46: strcat(str, "Yu"); break;
                case 47: strcat(str, "Ya"); break;
                case 48: strcat(str, "a"); break;
                case 49: strcat(str, "b"); break;
                case 50: strcat(str, "v"); break;
                case 51: strcat(str, "g"); break;
                case 52: strcat(str, "d"); break;
                case 53: strcat(str, "e"); break;

                case 54: strcat(str, "zh"); break;
                case 55: strcat(str, "z"); break;
                case 56: strcat(str, "i"); break;
                case 57: strcat(str, "y"); break;
                case 58: strcat(str, "k"); break;
                case 59: strcat(str, "l"); break;
                case 60: strcat(str, "m"); break;
                case 61: strcat(str, "n"); break;
                case 62: strcat(str, "o"); break;
                case 63: strcat(str, "p"); break;
                case 64: strcat(str, "r"); break;
                case 65: strcat(str, "s"); break;
                case 66: strcat(str, "t"); break;
                case 67: strcat(str, "u"); break;
                case 68: strcat(str, "f"); break;
                case 69: strcat(str, "ch"); break;
                case 70: strcat(str, "z"); break;
                case 71: strcat(str, "ch"); break;
                case 72: strcat(str, "sh"); break;
                case 73: strcat(str, "ch"); break;
                case 74: strcat(str, "''"); break;
                case 75: strcat(str, "y"); break;
                case 76: strcat(str, "''"); break;
                case 77: strcat(str, "e"); break;
                case 78: strcat(str, "yu"); break;
                case 79: strcat(str, "ya"); break;
                case 81: strcat(str, "ye"); break;

                // default: { char Temp[2] = { str[0], 0} ; strcat(&newStr[0], &Temp[0]); }
                }
        // }
}

uint8_t CharToInt(char S){
  static uint8_t values[] = {
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,  // 0-9
         0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // A-F
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // a-f
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    return values[S];
}

uint8_t getByte(char* Data){
  char Hi  = Data[0];
  char Low = Data[1];
  return CharToInt(Hi)*16 + CharToInt(Low);
}


// фунция запроса балланса
char* GSM_Un::Ballans(GSM_OPER P, int Asq){
  // если в буфере есть информация, вычитать для очистки
  _Debug -> println("Ballans Get");
  ClearBuferUart(5000);
  memset(Bufer, NULL, sizeof(Bufer));
  memset(Inc, NULL, sizeof(Inc));
  // DebugPrint("AT+CUSD=1,\"*100#\"");

  _Ser_GSM -> write("AT+CUSD=1,");
  _Ser_GSM -> write(P.BALL);
  _Ser_GSM -> write('\n');

  _Ser_GSM -> readBytesUntil('\r', Bufer, 500);
  // DebugPrint(Bufer);

  uint64_t timeOld = millis();
  while (strstr(Bufer, "+CUSD:") == NULL) {
    memset(Inc, NULL, sizeof(Inc));
    _Ser_GSM -> readBytesUntil('\r', Inc, 500);
    strcat(Bufer, Inc);
    // DebugPrint(Bufer);
    // delay(5);
    if ((millis() - timeOld) > 10000) return "Note Responce";
  }

  // DebugPrint(Inc);
  // _Debug -> println(Inc);
  // DebugPrint(Bufer);

  memset(Bufer, '\0', sizeof(Bufer));
  char *t = strchr(Inc, '\"');
  memmove(Bufer, strchr(Inc, '\"') + 1, strrchr(Inc, '\"') - strchr(Inc,'\"') - 1);
  // DebugPrint(Bufer);
  char Ball[500] = "";
  // UCS2ToString(Bufer, Ball);

  ConvertHEXLatToKir(Bufer);
  // memset(Bufer, '\0', sizeof(Bufer));
  clear_char(Service_info.Ballans_PDU);
  if (Asq == SUM){
    strcat(Service_info.Ballans_PDU, CharHexBufer);
    _Debug ->println(Service_info.Ballans_PDU);
    return Service_info.Ballans_PDU;
   }
  clear_char(Service_info.Ballans_SUM);
  getBallansToChar(CharHexBufer, Service_info.Ballans_PDU);
  _Debug -> println(Service_info.Ballans_SUM);
  return Service_info.Ballans_SUM;
}

char* GSM_Un::Ballans(int Asq){
  _ballans_start = true;
  // если в буфере есть информация, вычитать для очистки
  // ClearBuferUart(5000);
  // memset(Inc, NULL, sizeof(Inc));
  _Debug -> println("Ballans Get");
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;

  _Ser_GSM -> write("AT+CUSD=1,");
  _Ser_GSM -> write(_OPER_OUT -> BALL);
  _Ser_GSM -> write('\n');

  xQueueReceive(queue_ballans, &result1, 1000/portTICK_RATE_MS);
  // _Debug -> print("1 ballans result1= "), _Debug -> print(result1), _Debug -> println("#");

  time = millis();
  while((strstr(result1, "+CUSD:") == NULL) && ((millis() - time) < 10000)) {
    xQueueReceive(queue_ballans, &result2, 5000/portTICK_RATE_MS);
    // _Debug -> print("while ballans result2= "), _Debug -> print(result2), _Debug -> println("#");
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }
  // _Debug -> print("2 ballans result1= "), _Debug -> print(result1), _Debug -> println("#");
  _ballans_start = false;
  if (strstr(result1, "+CUSD:") == NULL) {
    _Debug -> println("Note Responce");
    return "Note Responce";
  }

  if (strstr(result1, "+CUSD: 2") != NULL) {
    _Debug -> println("Cancel Session");
    return "Cancel Session";
  }

  clear_char(result2);

  // _Debug -> println(result1);

  char *t = strchr(result1, '\"');
  memmove(result2, strchr(result1, '\"') + 1, strrchr(result1, '\"') - strchr(result1,'\"') - 1);
  char Ball[500] = "";
  // UCS2ToString(Bufer, Ball);

  ConvertHEXLatToKir(result2);
  // memset(Bufer, '\0', sizeof(Bufer));
  clear_char(Service_info.Ballans_PDU);
  if (Asq == PDU){
    strcat(Service_info.Ballans_PDU, CharHexBufer);
    _Debug ->println(Service_info.Ballans_PDU);
    return Service_info.Ballans_PDU;
   }
  clear_char(Service_info.Ballans_SUM);
  getBallansToChar(CharHexBufer, Service_info.Ballans_SUM);
  _Debug -> println(Service_info.Ballans_SUM);
  return Service_info.Ballans_SUM;
}

char* GSM_Un::Ballans_all(GSM_OPER P){
  _ballans_start = true;
  // если в буфере есть информация, вычитать для очистки
  // ClearBuferUart(5000);
  // memset(Inc, NULL, sizeof(Inc));
  _Debug -> println("Ballans Get");
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;

  _Debug -> print("Number USSD = "), _Debug -> println(P.BALL);

  _Ser_GSM -> write("AT+CUSD=1,");
  _Ser_GSM -> write(P.BALL);
  _Ser_GSM -> write('\n');

  xQueueReceive(queue_ballans, &result1, 1000/portTICK_RATE_MS);
  // _Debug -> print("1 ballans result1= "), _Debug -> print(result1), _Debug -> println("#");

  time = millis();
  while((strstr(result1, "+CUSD:") == NULL) && ((millis() - time) < 10000)) {
    xQueueReceive(queue_ballans, &result2, 5000/portTICK_RATE_MS);
    // _Debug -> print("while ballans result2= "), _Debug -> print(result2), _Debug -> println("#");
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }
  // _Debug -> print("2 ballans result1= "), _Debug -> print(result1), _Debug -> println("#");
  _ballans_start = false;
  if (strstr(result1, "+CUSD:") == NULL) {
    _Debug -> println("Note Responce");
    return "Note Responce";
  }

  if (strstr(result1, "+CUSD: 2") != NULL) {
    _Debug -> println("Cancel Session");
    return "Cancel Session";
  }

  clear_char(result2);

  // _Debug -> println(result1);

  char *t = strchr(result1, '\"');
  memmove(result2, strchr(result1, '\"') + 1, strrchr(result1, '\"') - strchr(result1,'\"') - 1);
  char Ball[500] = "";
  // UCS2ToString(Bufer, Ball);

  ConvertHEXLatToKir(result2);
  // memset(Bufer, '\0', sizeof(Bufer));
  clear_char(Service_info.Ballans_PDU);

  strcat(Service_info.Ballans_PDU, CharHexBufer);
  _Debug ->println(Service_info.Ballans_PDU);

  clear_char(Service_info.Ballans_SUM);
  getBallansToChar(CharHexBufer, Service_info.Ballans_SUM);
  _Debug -> println(Service_info.Ballans_SUM);
  return Service_info.Ballans_SUM;
}

bool GSM_Un::Network_check(){
  char result[500] = "";

  strcat(result, AT_as("AT+CREG?", "OK"));
  DebugPrint(result);
  int t = strstr(result, "+CREG:") - result + 9;

  _Debug -> write("\n");
  _Debug -> write(result[t]);
  _Debug -> write("\n");
  // DebugPrint(result[t]);

  if ((result[t] == '1') || (result[t] == '5')) return true;
  return false;
}

// функция включения GPRS
bool GSM_Un::GPRS(){

  char result[500] = "";

  // if (_flag_All_init){
    _Debug -> println(">>>>>>>>>> Settings GPRS param to module <<<<<<<<<<<<");

  AT_as("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"", "OK");

  clear_char(result);
  strcat(result, "AT+SAPBR=3,1, \"APN\",");
  strcat(result, oper_put.APN);
  _Debug -> print("result APN = "), _Debug -> println(result);
  AT_as(result);

  clear_char(result);
  strcat(result, "AT+SAPBR=3,1, \"USER\",");
  strcat(result, oper_put.user_gsm);
  _Debug -> print("result USER = "), _Debug -> println(result);
  AT_as(result);

  clear_char(result);
  strcat(result, "AT+SAPBR=3,1, \"PWD\",");
  strcat(result, oper_put.pwd);
  _Debug -> print("result PWD = "), _Debug -> println(result);
  AT_as(result);

  // AT_as( 3, "AT+SAPBR=3,1, \"APN\", \"next\"");
  // AT_as( 3, "AT+SAPBR=3,1, \"USER\",\"", _OPER_OUT -> USER, "\"");
  // AT_as( 3, "AT+SAPBR=3,1, \"USER\",,,");
  // AT_as( 3, "AT+SAPBR=3,1, \"PWD\",\"", _OPER_OUT -> PWD, "\"");
  // AT_as( 3, "AT+SAPBR=3,1, \"PWD\",,, \,");
  AT_as("AT+CGACT=1,1", "OK");
  AT_as("AT+SAPBR=4,1", "OK");
  // AT("AT+SAPBR=1,1", "OK")
  // }

  uint32_t Time_set = millis();

  while( (!Network_check()) && ((millis() - Time_set) <= 20000)) {
    _Debug -> println(">>>>>>>>>> Waiting Network <<<<<<<<<<<");
  }

  if (((millis() - Time_set) >= 20000)) {
    _Debug -> println(">>>>>>>>>> Stop Waiting Network <<<<<<<<<<<");
    AT_as("AT+CFUN=1,1");
    if (!_Reconnect_flag) {
      _Debug -> println(" Reconnect flag true in GPRS");
      // xSemaphoreGive(Reconnect_Sem);
      Reconnect_Task_flag = true;
    }
    return false;
  }



  if (GPRS_check()) return true;

  AT_as("AT+SAPBR=1,1", "OK");
  AT_as("AT+CLBSCFG=0,3");
  // strcat(result, AT("AT+SAPBR=1,1", "OK"));
  AT_as("AT+CGATT?", "OK");
  return true;
}

bool GSM_Un::Module_init(){
  _Debug -> println("Module init start");
  // AT_as("AT+CIPSRIP=3");
  // if (!digitalRead(_Pin_All_init)){
  if (1){
    _Debug -> println(">>>>>>>>>> Settings AT param to module <<<<<<<<<<<<");

    waitingUart(10000);
    // AT("AT");
    AT_as("AT+CFUN=1,1");
    waitingUart(10000);
    AT_as("ATE0", "OK");
    AT_as("AT+CLTS=1", "OK");
    AT_as("AT&W", "OK");

    AT_as("AT+CSCS=\"HEX\"");
    AT_as("AT+CSCS?");
    Ballans(SUM);
  }
  waitingUart(10000);
  _Debug -> println("Module init stop true");

  return true;
}

// функция включения проверки соединиения GPRS
bool GSM_Un::GPRS_check(){
  char result[500] = "";

  strcat(result, AT_as("AT+SAPBR=2,1", "OK"));
  DebugPrint(result);
  int t = strstr(result, "+SAPBR") - result + 10;

  _Debug -> write("\n");
  _Debug -> write(result[t]);
  _Debug -> write("\n");
  // DebugPrint(result[t]);

  if ((result[t]) == '1' || (result[t] == '0')) return true;
  return false;
}

// функция поднятия соединения TCP
bool GSM_Un::TCP_connect(){
  TCP_connect_flag = false;
  char result[500] = "";
  // if (_flag_All_init){
    _Debug -> println(">>>>>>>>>> Settings TCP/IP param to module <<<<<<<<<<<<");

    AT_as("AT+CIPSTATUS");
    AT_as("AT+CSTT=\"internet\"");
    AT_as("AT+CIPSTATUS");
    AT_as("AT+CIICR");
    AT_as("AT+CIPSTATUS");
    AT_as("AT+CIFSR");



  AT_as("AT+CIPSHUT", "SHUT OK");                          // зброс всех TCP соединений
  AT_as("AT+CIPMODE=0", "OK");                             // установка командного режима
  AT_as("AT+CIPMUX=0", "OK");                             // установка режима режима моносокета
  // AT("AT+CIPTKA=1,30,30,3", "OK");
  AT_as("AT+CIPQSEND=0", "OK");												// выбор режима пеердачи данных - с потверждением от принимающего или нет
  AT_as("AT+CIPHEAD=1", "OK");												// добавление IP в пакет ответа
  AT_as("AT+CIPSHOWTP=1", "OK");												// добавление IP в пакет ответа
	AT_as("AT+CIPSRIP=1", "OK");												// показывать удаленный IP и порт когда принимаются данные
	// AT_as("AT+CIPSRIP=1", "OK");												// показывать удаленный IP и порт когда принимаются данные
	AT_as("AT+CIPRXGET=1", "OK");												// Настройка ручного вывода данных.
	// AT_as("AT+CSTT=\"internet\", \"gdata\",\"gdata\"", "OK");
	// AT_as("AT+CIICR", "OK");
	// AT_as("AT+CIFSR;E0", "OK");
	// AT_as("AT+CDNSCFG=\"8.8.8.8\",\"8.8.4.4\"", "OK");
  // AT_as("AT+CIPSCONT", "OK");


// }

// AT_as("AT+CIPSGTXT=0", "OK");

// strcat(result, AT_as("AT+CIICR", "OK"));
// if (strstr(result, "ERROR") != NULL){
//   _flag_All_init = true;
//   TCP_connect();
// }


  // strcat(result, AT("AT+CIPSTART=\"TCP\",\"dev.rightech.io\", 1883", 3000));
  char line[200] = "AT+CIPSTART=\"TCP\",";
  strcat(line, "\"dev.rightech.io\",");
  strcat(line, "1883");

  strcat(result, AT_as(line, "ERROR", "CONNECT OK", "ALREADY CONNECT"));
  _Debug -> println(result);
  if ((strstr(result, "CONNECT") != NULL) || (strstr(result, "ALREADY CONNECT") != NULL)) {
    _Debug -> println("Connect to server");
    AT_as("AT+CIPTKA?", "OK");

    strcat(result, AT_as("AT+CIPSTATUS", "ERROR", "CONNECT OK", "ALREADY CONNECT"));
    if ((strstr(result, "CONNECT FAIL") != NULL)) return false;
    // AT_as("AT+CIPSTATUS");
    // _flag_All_init = false;
    TCP_connect_flag = true;
    _Debug -> println("TCP_connect_flag = true");
    return true;
  }

  if (strstr(result, "ERROR") != NULL){
    _Debug -> println("No connection to server");
    _data_start = false;
    // _Debug -> println(" Semaphore Reconnect_Sem Start");
    // xSemaphoreGive(Reconnect_Sem);
  }

  _flag_All_init = true;
  return false;
}

// функция восстановления соединения
bool GSM_Un::Reconnect(){
  // xSemaphoreTake(Reconnect_Sem, portMAX_DELAY);
  _Debug -> println(" Reconnect_Task_flag to false");
  Reconnect_Task_flag = false;
  _Reconnect_flag = true;
  _blink_connect = false;
  _Debug -> println("###############  RECONNECT #######################################################");
  waitingUart(10000);
  if (!GPRS()) {
    // waitingUart(10000);
    // AT("AT");
    // AT_as("AT+CFUN=1,1");
    // waitingUart(10000);
    AT_as("ATE0", "OK");
    AT_as("AT+CLTS=1", "OK");
    AT_as("AT&W", "OK");
    GPRS();
  }
  TCP_connect();
  if (MQTT_connect()) {
    _flag_mqtt_con = true;
    _Reconnect_flag = false;
    _blink_connect = true;
    return true;
  }
  return false;
}

void GSM_Un::CIPRXGET_handler_task(){
  xSemaphoreTake(CIPRXGET_hendler_start, portMAX_DELAY);
  _Debug -> println("CIPRXGET_handler_task GO");
  if (strstr(CIPRXGET_bufer, "D000")){
    _pingreq_flag = true;
    _Debug -> println("YES PING");
  }
  if (strstr(CIPRXGET_bufer, "20020000")){
    _mqttConnect_flag = true;
    _Debug -> println("YES Connect");
  }
  if (strstr(CIPRXGET_bufer, "40020010")){
    _mqttPublish_flag = true;
    _Debug -> println("YES Publish");
    return;
  }
  // getMQTTmessage(CIPRXGET_bufer);
  MQTT_parseMessage(getMQTTmessage(CIPRXGET_bufer));
  if (MqttMes.Head == 0x32){
    _Debug -> println("Yes command in CIPRXGET_handler_task");
    MQTT_pubback();
    MQTT_command_flag = true;
  }

}

char* GSM_Un::getDataCIPRXGET_task(){
  xSemaphoreTake(CIPRXGET_start, portMAX_DELAY);
  _Debug -> println("Start call CIPRXGET ");
  char result1[1000] = "";
  char result2[1000] = "";
  uint32_t time;
  // _Ser_GSM -> println("AT+CIPRXGET=4, 500");
  // AT("AT+CIPRXGET=3, 500", "OK");
  AT_as("AT+CIPRXGET=3, 500");
  // AT_as("AT+CIPRXGET=4, 500", "OK");

  time = millis();
   do {
     // xQueueReceive(queue_CIPRXGET, &result2, 1000);
     xQueueReceive(queue_CIPRXGET, &result2, 100/portTICK_RATE_MS);
     // _Debug -> print("result2 = "), _Debug -> println(result2);
     strcat(result1, result2);
     // _Debug -> print("result1 = "), _Debug -> println(result1);
     clear_char(result2);
     // vTaskDelay(500);
   } while((strstr(result1, "+CIPRXGET: 3,") == NULL) && ((millis() - time) < 2000));

   clear_char(CIPRXGET_bufer);
   strcat(CIPRXGET_bufer, result1);
   if ((strstr(CIPRXGET_bufer, "+CIPRXGET: 3,") != NULL) && (strstr(CIPRXGET_bufer, "OK") != NULL)){
     xSemaphoreGive(CIPRXGET_hendler_start);
   }

   _Debug -> print("CIPRXGET_bufer = "), _Debug -> print(CIPRXGET_bufer); _Debug -> println("#");

   // _Debug -> print("result1 +CIPRXGET = "), _Debug -> print(result1); _Debug -> println("#");

  _CIPRXGET_start = false;

  // _Debug -> println("End call CIPRXGET ");
  return("ok");
}

char* GSM_Un::getDataRX(){
  char result1[1000] = "";
  char result2[1000] = "";
  // запрашиваем данные которые еще не были прочитаны из gsm модуля
  strcat(result1, AT("AT+CIPRXGET=4", "+CIPRXGET: 4", 500));
  // DebugPrint(result1);


  if (strstr(result1, "+CMTI:") != NULL){
    strcat(result2, result1);
    SMS_getNumb_newMes(result2);
    flagNewMes = true;
    clear_char(result2);
  }

  if (strstr(result1, "+CIPRXGET: 4") != NULL){

    uint8_t count_char = strchr(strchr(result1, ','), '\r') - strchr(result1, ',') - 2;
    // _Debug -> println(count_char);
    memmove(result2, strchr(result1, ',') + 1, count_char);

    // _Debug -> print(">>");_Debug -> print(result2);_Debug -> println("<<");
    int count = atoi(result2);
    // sscanf(result2, "%d", count);
    // _Debug -> println(count);

    _Ser_GSM -> write("AT+CIPRXGET=3,"), _Ser_GSM -> write(result2), _Ser_GSM -> write('\n');
    _Ser_GSM -> setTimeout(100);
    _Ser_GSM -> readBytes(result1, 500);
    _Ser_GSM -> setTimeout(_TimeoutDefault);
    // _Debug -> println(result1);
    if (strstr(result1, "+CIPRXGET:") != NULL){
      memset(result2, NULL, sizeof(result2));
      char* t = strstr(result1, "+CIPRXGET:");
      t = strchr(t, '\n') + 1;

      memmove(result2, t, count*2);

      memset(Bufer, NULL, sizeof(Bufer));
      strcat(Bufer, result2);
    }
  }
_Debug -> println(Bufer);
return Bufer;
}

char* GSM_Un::getMQTTmessage(char* message){
  char result1[1000] = "";
  char result2[1000] = "";
  if (strstr(message, "+CIPRXGET:") != NULL){
    char* t = strstr(message, "+CIPRXGET: 3");
    memset(result2, NULL, sizeof(result2));
    strcat(result2, t);
    t = strstr(result2, "\n") + 1;
    memset(result1, NULL, sizeof(result1));
    strcat(result1, t);
    t = strstr(result1, "\n");
    memset(result2, NULL, sizeof(result2));
    memmove(result2, result1, t - result1 - 1);

    if (strstr(result2, "40020010") != NULL){
      memset(result1, NULL, sizeof(result1));
      strcpy(result1, result2 + 8);
    }

    _Debug -> print("MQTT message >>"), _Debug -> print(result1), _Debug -> println(" <<");
    memset(MQTT_MesBufer, NULL, sizeof(MQTT_MesBufer));
    strcat(MQTT_MesBufer, result1);
    return MQTT_MesBufer;
  }
  memset(MQTT_MesBufer, NULL, sizeof(MQTT_MesBufer));
  return MQTT_MesBufer;
}


char* GSM_Un::getDataRX(char* Test){
  char result1[1000] = "";
  char result2[1000] = "";
  memset(Bufer, NULL, sizeof(Bufer));

  strcat(result1, AT("AT+CIPRXGET=4", "+CIPRXGET: 4", 200));
  // DebugPrint(result1);
  if (strstr(result1, "+CMTI:") != NULL){
    strcat(result2, result1);
    SMS_getNumb_newMes(result2);
    flagNewMes = true;
    clear_char(result2);
  }

  if (strstr(result1, "+CIPRXGET: 4") != NULL){

    uint8_t count_char = strchr(strchr(result1, ','), '\r') - strchr(result1, ',') - 2;
    // _Debug -> println(count_char);
    memmove(result2, strchr(result1, ',') + 1, count_char);

    // _Debug -> print(">>");_Debug -> print(result2);_Debug -> println("<<");
    int count = atoi(result2);
    // sscanf(result2, "%d", count);
    _Debug -> println(count);
    if (count == 0) return Bufer;

    _Ser_GSM -> write("AT+CIPRXGET=3,"), _Ser_GSM -> write(result2), _Ser_GSM -> write('\n');
    _Ser_GSM -> setTimeout(100);
    _Ser_GSM -> readBytes(result1, 500);
    _Ser_GSM -> setTimeout(_TimeoutDefault);
    // _Debug -> println(result1);
    if (strstr(result1, "+CIPRXGET:") != NULL){
      memset(result2, NULL, sizeof(result2));
      char* t = strstr(result1, "+CIPRXGET:");
      t = strchr(t, '\n') + 1;

      memmove(result2, t, count*2);

      _Debug -> print("Data = "); _Debug -> println(result2);
      // _Debug -> print("count = "); _Debug -> println(count);
      // _Debug -> print("Datalen = "); _Debug -> println(strlen(result2)/2);
      // _Debug -> print("Test = "); _Debug -> println(strlen(Test)/2);

      if (count > strlen(Test)/2){
        memset(result1, NULL, sizeof(result1));
        // _Debug -> print((int)strstr(result2, Test)); _Debug -> print("    ");
        // _Debug -> println((int)result2);

        if ((int)strstr(result2, Test) == (int)result2){
          memmove(result1, result2 + strlen(Test), strlen(result2) - strlen(Test));
          _Debug -> print("Data = "); _Debug -> println(result1);
        }
        else{
          memmove(result1, result2, strlen(result2) - strlen(Test));
          _Debug -> print("Data = "); _Debug -> println(result1);
        }

        MQTT_parseMessage(result1);
        MQTT_pubback();
        hendlerCommand(1);
        memset(Bufer, NULL, sizeof(Bufer));
        strcat(Bufer, Test);
        return Bufer;
      }
      memset(Bufer, NULL, sizeof(Bufer));
      strcat(Bufer, result2);
      return Bufer;
    }
  }
return Bufer;
}

bool GSM_Un::chekDataRX(){
  char result[500] = "";
  char result2[500] = "";

  _Debug -> println("chekDataRX");
  _Ser_GSM -> setTimeout(100);
  _Ser_GSM -> println("AT+CIPRXGET=4");
  _Ser_GSM -> readBytes(result, 500);
  _Ser_GSM -> setTimeout(_TimeoutDefault);

  if (strstr(result, "+CMTI:") != NULL){
    _Debug -> println("New message");
    strcat(result2, result);
    SMS_getNumb_newMes(result);
    flagNewMes = true;
    clear_char(result2);
  }

  if(strstr(result, "+CIPRXGET: 4") != NULL){
    if (strstr(result, "+CIPRXGET: 4,0") != NULL){
      return false;
    }
    _Debug -> println("!!! Data In !!!!");
    // _Debug -> println(result);
    return true;
  }

  return false;
}

void GSM_Un::hendlerCommand(uint8_t sourseCommand){
  switch (sourseCommand) {
    case 1:
      _Debug -> print("PayloadText = ");_Debug -> println(MqttMes.PayloadText);
      if (strstr(MqttMes.PayloadText, "SMS DEL")!= NULL) {
        SMS_del_all();
      }
    break;
    case 2:
      if (strstr(SMStextFMes.PayLoadText, "STATUS") != NULL){
        SMS_send_textF(SMStextFMes.Number, "STATUS OK");
      }
      if (strstr(SMStextFMes.PayLoadText, "Smartgen") != NULL){
      if (strstr(SMStextFMes.PayLoadText, "STOP") != NULL){
          state_command_ModBus = true;
          coil_command_ModBus = 1;
          coil_state_ModBus = 255;
          SMS_send_textF(SMStextFMes.Number, "STOP OK");
        }
      }
    break;
  }
}


void GSM_Un::check_Uart_command(){
  char result1[1000] = "";
  char result2[1000] = "";
  if (_Ser_GSM -> available()){
    _Ser_GSM -> setTimeout(100);
    _Ser_GSM -> readBytes(result1, 1000);
    _Debug -> println(result1);
    _Ser_GSM -> setTimeout(_TimeoutDefault);
  }
  if (strstr(result1, "+CIPRXGET: 1") != NULL){
    _Debug -> println(" Hendler get data CIPRXGET");
    // _Ser_GSM -> setTimeout(2000);
    strcat(result2, getDataRX());
    MQTT_parseMessage(result2);
    if (MqttMes.Head == 0x32){
      _Debug -> println("Yes command in check_Uart_command");
      MQTT_pubback();
      hendlerCommand(1);
    }
  }
  if (strstr(result1, "+CMTI:") != NULL){
    _Debug -> println(" Have new messege NOW");
    strcat(result2, result1);
    SMS_getNumb_newMes(result2);
    SMS_read_textF(NumNewMes,0);
    hendlerCommand(2);
  }
  if (flagNewMes){
    _Debug -> println(" Have new messege");
    SMS_read_textF(NumNewMes,0);
    flagNewMes = false;
    hendlerCommand(2);
  }

}


void GSM_Un::MQTT_parseMessage(char* Message){
  _Debug -> print("Message = >>>>"), _Debug -> println(Message), _Debug -> print(" <<<<<<<");

  int len = strlen(Message);
  char twice[2];
  memmove(twice, Message, 2);
  MqttMes.Head = getByte(twice);
  _Debug -> print("Head = "), _Debug -> println(MqttMes.Head, HEX);
  if (MqttMes.Head == 0x32){
    _Debug -> println("Command come in");
    memmove(twice, Message  + 2, 2);
    MqttMes.RemL = getByte(twice);
    _Debug -> print("Remaining Length = "), _Debug -> println(MqttMes.RemL);
    memmove(twice, Message  + 2 + 2, 2);
    uint8_t Hi = getByte(twice);
    memmove(twice, Message  + 2 + 2 + 2, 2);
    uint8_t Low = getByte(twice);
    MqttMes.TopL = Hi | Low;
    _Debug -> print("Topic Length = "), _Debug -> println(MqttMes.TopL);
    char TopicHex[500] = "";
    memmove(TopicHex, Message  + 2 + 2 + 2 + 2, MqttMes.TopL*2);
    // _Debug -> print("Topic Hex = "), _Debug -> println(TopicHex);
    // char Topic[500] = "";
    // _Debug -> print("Message = "), _Debug -> println(Message);
    memset(MqttMes.Topic, NULL, sizeof(MqttMes.Topic));
    strcat(MqttMes.Topic, HexCharToChar(TopicHex));
    // _Debug -> print("Message = "), _Debug -> println(Message);
    // _Debug -> print("Topic Char = "), _Debug -> println(MqttMes.Topic);
    // _Debug -> print("Message = "), _Debug -> println(Message);
    memmove(twice, Message  + 2 + 2 + 2 + 2 + MqttMes.TopL*2, 2);
    // _Debug -> print("twice = "), _Debug -> println(twice);
    MqttMes.IdentifierHi = getByte(twice);
    memmove(twice, Message  + 2 + 2 + 2 + 2 + MqttMes.TopL*2 + 2, 2);
    MqttMes.IdentifierLow = getByte(twice);
    // _Debug -> print("Packet Identifie = "), _Debug -> print(MqttMes.IdentifierHi), _Debug -> println(MqttMes.IdentifierLow);
    char PayloadHex[500] = "";
    strcpy(PayloadHex, Message + 2 + 2 + 2 + 2 + MqttMes.TopL*2 + 2 + 2);
    // char Payload[500] = "";
    memset(MqttMes.Payload, NULL, sizeof(MqttMes.Payload));
    strcat(MqttMes.Payload, PayloadHex);
    memset(MqttMes.PayloadText, NULL, sizeof(MqttMes.PayloadText));
    strcat(MqttMes.PayloadText, HexCharToChar(PayloadHex));
    // _Debug -> print("Payload Char = "), _Debug -> println(MqttMes.Payload);



  }
}

void GSM_Un::checkCommand(){
  MQTT_parseMessage(getDataRX());
  if (MqttMes.Head == 0x32){
    MQTT_pubback();
  }
}

char* GSM_Un::HexCharToChar(char* Data){
  // char DataOut[500] = "";
  memset(CharHexBufer, NULL, sizeof(CharHexBufer));
  char twice[2];
  uint8_t Ch;
  int len = strlen(Data);
  for(int i = 0; i < len; i+=2){
    memmove(twice, Data + i, 2);
    Ch = getByte(twice);
    strcat_c(CharHexBufer, (char)Ch);
  }

  _Debug -> print("Char = "), _Debug -> println(CharHexBufer);
  return CharHexBufer;
}

char* GSM_Un::ConvertHEXLatToKir(char* Line){
  // char result[500] = "";
  memset(CharHexBufer, NULL, sizeof(CharHexBufer));
  _Debug -> print(">>>"), _Debug -> print(Line), _Debug -> println("<<<");
  uint8_t Ch;
  char tetra[4] = "";
  char twice1[2] = "";
  char twice2[2] = "";
  char *p;
  uint16_t len = strlen(Line);
  int EndLen;
  for (int i = 0; i < len; i+=4){
    memmove(tetra, Line + i, 4);
    memmove(twice1, tetra, 2);
    memmove(twice2, tetra + 2, 2);
    if (strstr(twice1, "04") != NULL){
      Ch = getByte(twice2);
      _Debug -> println(Ch);
      Transliterate(CharHexBufer, Ch);
      _Debug -> println(CharHexBufer);
    }
    else{
      Ch = getByte(twice2);
        strcat_c(CharHexBufer, (char)Ch);
    }
  }
_Debug -> print(">>ConvertHEXLatToKir>>>"), _Debug -> println(CharHexBufer);
return CharHexBufer;
}

char* GSM_Un::Get_CSQ(){
  char result1[500] = "";
  char result2[500] = "";
  uint8_t csq_num = 0;
  double csq_val;

  strcat(result1, AT_as("AT+CSQ"));
  // _Debug -> print(">>>"),  _Debug -> println(result1), _Debug -> print("<<<");
  strcat(result2, ShiftLine_FindChar(result1, ":"));
  // _Debug -> print(">>>"),  _Debug -> println(result2), _Debug -> print("<<<");
  clear_char(result1);
  FirstWordLineToChar(result2, result1, ',');
  // _Debug -> print(">>>"),  _Debug -> print(result1), _Debug -> println("<<<");
  csq_num = atoi(result1);
  // _Debug -> println(csq_num);
  csq_val = ((double)csq_num / 31) * 100;
  // _Debug -> println(csq_val);

  clear_char(Service_info.CSQ);
  itoa(csq_num, Service_info.CSQ, DEC);
  clear_char(Service_info.CSQ_VAL);
  itoa((int)csq_val, Service_info.CSQ_VAL, DEC);
  _Debug -> print("CSQ = "),  _Debug -> print(Service_info.CSQ), _Debug -> print("     CSQ_VAL = "),  _Debug -> println(Service_info.CSQ_VAL);
  return result1;
}

char* GSM_Un::Get_TempModuleGSM(){
  char result1[500] = "";
  char result2[500] = "";

  strcat(result1, AT_as("AT+CMTE?"));
  // _Debug -> print(">>>"),  _Debug -> println(result1), _Debug -> print("<<<");
  strcat(result2, ShiftLine_FindChar(result1, ","));
  // _Debug -> print(">>>"),  _Debug -> println(result2), _Debug -> print("<<<");
  clear_char(result1);
  FirstWordLineToChar(result2, result1, '\r');
  // _Debug -> print(">>>"),  _Debug -> print(result1), _Debug -> println("<<<");
  clear_char(Service_info.Temp_SIMMODULE);
  strcat(Service_info.Temp_SIMMODULE, result1);
  _Debug -> print("Temp_SIMMODULE = "),  _Debug -> println(Service_info.Temp_SIMMODULE);

  return result1;
}

char* GSM_Un::Get_OperInfo(){
  char result1[500] = "";
  char result2[500] = "";

  strcat(result1, AT_as("AT+COPS?"));
  // _Debug -> print(">>>"),  _Debug -> println(result1), _Debug -> print("<<<");
  strcat(result2, ShiftLine_FindChar(result1, '\"'));
  // _Debug -> print(">>>"),  _Debug -> println(result2), _Debug -> print("<<<");
  clear_char(result1);
  FirstWordLineToChar(result2, result1, '\"');
  // _Debug -> print(">>>"),  _Debug -> print(result1), _Debug -> println("<<<");
  clear_char(Service_info.OperInfo);
  strcat(Service_info.OperInfo, result1);
  _Debug -> print("OperInfo = "),  _Debug -> println(Service_info.OperInfo);

  return result1;
}
