//#include <Arduino.h>
#include "GSM_My.h"
#include <ModbusMaster.h>
#include "MODBUS/modbus_my.h"
#include <WiFi.h>
// #include "USSD.h"
#include "Timer/Timer.h"
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include <SPIFFS.h>
#include "My_piffs.h"
#include "My_WiFi_gen.h"
#include <FS.h>
#include "variable.h"


#include "oled/oled_sh1106.h"


char Bufer[500] = "";
char DataAll[1000] = "";

// инициализация аппаратного юарт для связи
HardwareSerial  GSM_uart(2);
// инициализация аппаратного юарт для модбаз
HardwareSerial  DGU_uart(1);
// SoftwareSerial GNSS_Serial(25, 26);

TimerGO BallansGet;
TimerGO GNSS;
TimerGO Publish;

// ***************** создание обьекта для модуля связи с указанием: ******************************
// - юарт через который идет связь с модулем
// - юарт через который идет отладка
// - названием опреатора (можно без этого параметра, но нужно будет вручную указать номер для баланса)
GSM_Un GSM(GSM_uart, Serial, "MEGAFON");
//  *****************************************************************************

// ********** создание обьекта для модбаз под наш контроллер: *******************
// - адрес слэйв
// - юарт через который идет связь с контроллером
// - юарт через который идет отладка
ModbusDGU Smartgen(1, DGU_uart, Serial);
//  *****************************************************************************

String bufer = "";
// данные для соединения с брокером на платформе MQTT
struct data_mqtt {
  char PROTOKOL[200] = "MQIsdp";
  char MQTT_ID[200] = "AKSA_1_energomir";
  char USER[200]    = "AKSA_1_energomir";
  char PASSWORD[200]= "qwerty116";
} mqtt;

#define latitude_state    "55.623221"
#define longtitude_state  "49.156243"

TaskHandle_t PingReqHandle;
TaskHandle_t BallansHandle;
bool connect_mqtt = false;

SemaphoreHandle_t Reconnect_Sem_task = xSemaphoreCreateBinary();
SemaphoreHandle_t fackt = xSemaphoreCreateBinary();
SemaphoreHandle_t mutex_v = xSemaphoreCreateMutex();
SemaphoreHandle_t mutex_collect = xSemaphoreCreateMutex();
// флаг который запускает процесс проверки команды и ее выпонения
// так что бы паблишь после команды не выпонялся одновременно с основным
// паблишем и сейфконнектом
bool Waiting_Command_flag = false;
bool Pablish_Ping_flag = false;

void read_settings();
// ============================= SETUP =================================
void setup() {

{
  Serial.begin(115200);
  Serial.println("Hello World");
  Serial.println("Привет МИР!");

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  // display.drawPixel(10, 10, WHITE);
  // display.display();
  // delay(2000);
  // display.clearDisplay();
  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(20,30);
  display.println("Hello, world!");
  // display.setTextColor(BLACK, WHITE); // 'inverted' text
  // display.println(3.141592);
  display.display();
    //================ WiFI ====================
    Serial.println("Start 1-WIFI");
    WIFIinit();
    if (SPIFFS.begin()) {
      Serial.println("FileServer is true");       // Инициализируем работу с файловой системой
    }

    File f = SPIFFS.open("/1.txt", "r");
    while(f.available()) {
        //Lets read line by line from the file
        //char kek = f.readStringUntil('\n');
        Serial.print(f.readString());
      }

  	f.close();

    read_settings();

    HTTP_on();
    // HTTP.begin();                                          // Инициализируем Web-сервер
    //
    // HTTP.on("/input-id", input_id);
    // HTTP.on("/input_gsm", input_gsm);
    // HTTP.on("/input_gsm_handle", input_gsm_handle);
    // HTTP.on("/input-locate", input_locate);
    // HTTP.on("/input-type", input_type);
    //
    // HTTP.onNotFound([](){                                 // Описываем действия при событии "Не найдено"
    // if(!handleFileRead(HTTP.uri()))                       // Если функция handleFileRead (описана ниже) возвращает значение false в ответ на поиск файла в файловой системе
    //     HTTP.send(404, "text/plain", "Not Found");       // возвращаем на запрос текстовое сообщение "File isn't found" с кодом 404 (не найдено)
    // });

    // HTTP.handleClient();                                // Обработчик HTTP-событий (отлавливает HTTP-запросы к устройству и обрабатывает их в соответствии с выше описанным алгоритмом)

    // =========================================


    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    GSM_uart.begin(57600, SERIAL_8N1, 16, 17);
    // GSM_uart.begin(19200, SERIAL_8N1, 16, 17);
    DGU_uart.begin(9600, SERIAL_8N1, 14, 12);
    // DGU_uart.begin(115200, SERIAL_8N1, 14, 12);
    // DGU_uart.begin(9600, SERIAL_8N1, 25, 26);


    CheckSpiffs();
    OpenFileRead("/test1.txt");
    createFile("/history.txt");

// ++++++++++++++++++++++++++++++++++++++++++
}
// xTaskCreatePinnedToCore(Task_Modebus, "Task_Modebus", 10000, NULL, 1, NULL,  1);

{
  // GSM.AT_as("AT+IPR=0","OK");
  // GSM_uart.end();
  // GSM_uart.begin(115200, SERIAL_8N1, 16, 17);
  // GSM.waitingUart(2000);
  // GSM.AT_as("AT&W","OK");


  // GSM.Ballans(PDU); // Запрос балланса PDU - весь текст из сообщения, SUM - только сумма
  // GSM.AT_as("AT+IPR=0","OK");
  // GSM.AT_as("AT&W","OK");
  // GSM.AT_as("AT+IPR?","OK");
}
// ++++++++++++++++++++++++++++++++++++++++++
  GSM_uart.setTimeout(300);
  DGU_uart.setTimeout(300);
    // Запуск задачи которая постоянно слушает порт связи GSM, парсит
    xTaskCreatePinnedToCore(HTTP_client_frtos, "HTTP_client_frtos", 10000, NULL, 1, NULL,  1);
    xTaskCreatePinnedToCore(listen_Uart, "listen_Uart", 10000, NULL, 4, NULL,  0);
    xTaskCreatePinnedToCore(check_ciprxget, "check_ciprxget", 10000, NULL, 4, NULL,  0);
    xTaskCreatePinnedToCore(CIPRXGET_handler_task, "CIPRXGET_handler_task", 10000, NULL, 4, NULL,  0);
    xTaskCreatePinnedToCore(_Reconnect, "Reconnect", 10000, NULL, 4, NULL,  0);
    // xTaskCreatePinnedToCore(_Ping_Req, "Ping_Req", 10000, NULL, 1, &PingReqHandle,  0);

    // ***** Временно отключаю block 1
    xTaskCreatePinnedToCore(GetModbusAll_frtos, "GetModbusAll_frtos", 10000, NULL, 4, NULL,  0);
    // xTaskCreatePinnedToCore(CollectDataTask, "CollectDataTask", 10000, NULL, 1, NULL,  0);
    // ****** block 1
    // запуск задачи которая постоянно ждет комманды от сервера по флагу

    xTaskCreatePinnedToCore(BlinkConnect, "BlinkConnect", 10000, NULL, 4, NULL,  0);

    xTaskCreatePinnedToCore(display_info, "display_info", 10000, NULL, 4, NULL,  0);

    xTaskCreatePinnedToCore(BallansTask, "BallansTask", 10000, NULL, 4, &BallansHandle,  0);

    GSM.AT_as("AT+CPIN?", "READY");

    GSM.Module_init();


    // GSM.GNSS_powerOn();
    // GSM.AT_as("AT+CPIN?");
    GSM.AT_as("AT+CSQ");




    // GSM.Ballans(SUM);
    // GSM.Ballans(PDU);
    bool flag_tcpConnect = false;
    if (GSM.GPRS()) {
      if (GSM.TCP_connect()) flag_tcpConnect = true;
      else {GSM.AT_as("AT+CFUN=1,1");
            // xSemaphoreGive(GSM.Reconnect_Sem);
            GSM.Reconnect();
            // flag_tcpConnect = true;
      }
    }


    // if (flag_tcpConnect){
    if (GSM.TCP_connect_flag){
        if (GSM.MQTT_connect()) {
          connect_mqtt = true;
          Serial.print("Yes connect in setup - "), Serial.println(connect_mqtt);

          GetModbusAll();
          GSM.MQTT_pingreq();
          GSM.MQTT_publish("station/controller/all_param_message", DataAll);
          xTaskCreatePinnedToCore(Waiting_Command, "Waiting_Command", 10000, NULL, 4, NULL,  0);
          xTaskCreatePinnedToCore(SafeConnect_frtos, "SafeConnect_frtos", 10000, NULL, 4, NULL,  0);
          xTaskCreatePinnedToCore(Publish_frtos, "Publish_frtos", 10000, NULL, 4, NULL,  0);
          xTaskCreatePinnedToCore(get_serviceInfo, "get_serviceInfo", 10000, NULL, 4, NULL,  0);

        } else{
          // xSemaphoreGive(GSM.Reconnect_Sem);
        }
    }


    // char BuferUartTask[1000] = "";
      Serial.print("GSM.object_station.status_locate = "); Serial.println(GSM.object_station.status_locate);
      if (strstr(GSM.object_station.status_locate, "fix") == NULL){
        xTaskCreatePinnedToCore(listen_GNSS, "listen_GNSS", 10000, NULL, 4, NULL,  1);
      }


    // xTaskCreatePinnedToCore(listen_GNSS, "listen_GNSS", 10000, NULL, 4, NULL,  1);


}
// ===================================================================================

void HTTP_client_frtos( void * parameter) {
  for(;;) {//infinite loop
    HTTP.handleClient();
    vTaskDelay( 1 );
  }
}


void debug_screen( void * parameter) {
  for(;;) {//infinite loop

    vTaskDelay( 120000 );
  }
}



void get_serviceInfo( void * parameter) {
  for(;;) {//infinite loop
    xSemaphoreTake(mutex_v, portMAX_DELAY);
    GSM.Get_CSQ();
    GSM.Get_TempModuleGSM();
    GSM.Get_OperInfo();
    GSM.Ballans_all(GSM.MEGAFON);
    xSemaphoreGive(mutex_v);
    vTaskDelay( 240000 );
  }
}

void screen_1(){
  display.clearDisplay();
  display.setCursor(0,5);
  display.setTextSize(0);
  display.print("T="), display.print(GSM.Service_info.Temp_SIMMODULE), display.print(" C");
  display.setCursor(70,5);
  display.print("GSM "), display.print(GSM.Service_info.CSQ_VAL), display.print(" %");
  display.setCursor(0,20);
  display.print(GSM.Service_info.OperInfo);
  display.setCursor(60 ,20);
  display.print(GSM.Service_info.Ballans_SUM), display.print(" rub");
  display.setCursor(0 ,30);
  display.print(GSM.GPS_DATA.latitude), display.print("  "), display.print(GSM.GPS_DATA.logitude);
  display.setCursor(0 ,40);
  display.print(GSM.SafeConnect.getTimeRemains());
  display.setCursor(0 ,50);
  display.print(GSM.Reconnect_Task_flag);


  display.display();
}

void display_info( void * parameter) {
  for(;;) {//infinite loop
    screen_1();
    vTaskDelay( 300 );
  }
}

void collectData(){
    memset(DataAll, NULL, sizeof(DataAll));
    strcat(DataAll, Smartgen._BuferModB_reg);
    strcat(DataAll, "@");
    strcat(DataAll, Smartgen._BuferModB_coils);
    strcat(DataAll, "@");
    strcat(DataAll, GSM.Service_info.Ballans_SUM);
    strcat(DataAll, "#");
    strcat(DataAll, GSM.Service_info.CSQ_VAL);
    strcat(DataAll, "#");
    strcat(DataAll, GSM.Service_info.Temp_SIMMODULE);
    strcat(DataAll, "@");
    strcat(DataAll, GSM.GPS_DATA.UTCdatetime);
    strcat(DataAll, "#");
    strcat(DataAll, GSM.GPS_DATA.latitude);
    strcat(DataAll, "#");
    strcat(DataAll, GSM.GPS_DATA.logitude);
    strcat(DataAll, "#");
    strcat(DataAll, GSM.GPS_DATA.satellitesinview);
    strcat(DataAll, "@");

    // Serial.print("DataAll = "), Serial.println(DataAll);
}

void GetModbusAll(){
  Smartgen.Read_register_to_Array(0, 124);
  Smartgen.reg_to_char("#", DEC, 50);
  Smartgen.reg_to_char_ZIP("#", HEX, 50);
  Smartgen.Read_coils_to_Array(0, 80);
  Smartgen.coils_to_char("#", HEX, 6);
  Smartgen.coils_to_char_ZIP("#", HEX, 6);

  // collectData();
}
// |11#14#ea60#3e8#ea60#64#ea60##94#|5#1e#|4#1#2#|3#2#|3#1#f##1#|2@3##818##1429#@
// |11#14#ea60#3e8#ea60#64#ea60##94#|5#1e#|4#1#2#|3#2#|3#1#f##1#|2@3##818##1429#@@


// функция хендлера которая постоянно слушает юар и пишит значения в глобальный массив
// и в зависимости отполученных данных запускает соответствующие процессы
void listen_Uart( void * parameter) {
  char BuferUartTask[1000] = "";
  for(;;) {//infinite loop
    GSM.GSM_listen_Uart();
    vTaskDelay( 1 );
  }
}

uint32_t GNNS_time = 10000;

void listen_GNSS( void * parameter) {
  for(;;) {
      xSemaphoreTake(mutex_v, portMAX_DELAY);
      Serial.println("GNSS listen start");
      GSM.GNSS_get_inf();
      GSM.GNSS_parse_to_struct();
      GNNS_time = 10000;
      if (atoi(GSM.GPS_DATA.satellitesinview) == 0){
        if(GSM.GNSS_get_CLBS()){
          GSM.GNSS_CLBS_parse_to_struct();
          GNNS_time = 120000;
        }
      }
      Serial.println("GNSS listen STOP");
      // GSM.GNSS_to_char();
      xSemaphoreGive(mutex_v);
      vTaskDelay(GNNS_time);

  }
}


// фунция хендлера которая запускается по вызову (симофор) и вычитывает данные (интернет)
// из модуля в глобальный массив
// и запускает в конце фнукцию которая проверяет данные на пример подтерждений комманд (паблишь, конннект и тд)
void check_ciprxget( void * parameter){
  for(;;){
    GSM.getDataCIPRXGET_task();
    vTaskDelay(1);
  }
}

void CIPRXGET_handler_task( void * parameter){
  for(;;){
    GSM.CIPRXGET_handler_task();
    vTaskDelay(1);
  }
}

void _Reconnect( void * parameter){
  for(;;){
    // vTaskSuspend(PingReqHandle);
    xSemaphoreTake(mutex_v, portMAX_DELAY);
    // xSemaphoreTake(mutex_v, 50);
    // if (xSemaphoreTake(GSM.Reconnect_Sem, portMAX_DELAY
    if (GSM.Reconnect_Task_flag){
      GSM.Reconnect();
    }
    // }
    // vTaskResume(PingReqHandle);
    xSemaphoreGive(mutex_v);
    vTaskDelay(10);
  }
}

void GetModbusAll_frtos( void * parameter){
  for(;;){
    GetModbusAll();
    // add_line_to_end_file(DataAll, "/history.txt");

    // if (Smartgen.check_coil(Auto_Mode)) Serial.println("Auto mode");
    // if (Smartgen.check_coil(Manual_Mode)) Serial.println("Manual mode");
    // if (Smartgen.check_coil(Stop_Mode)) Serial.println("Stop mode");
    // if (Smartgen.check_coil(Common_Alarm)) Serial.println("ALARM");
    // if (Smartgen.check_coil(Emergency_Stop)) Serial.println("Emergency_Stop");

    // check_file("/test1.txt");
    // collectData();
    // add_line_to_end_file(DataAll, "/history.txt");
    // OpenFileRead("/history.txt");

    vTaskDelay(10000);
  }
}

void CollectDataTask( void * parameter){
  for(;;){
    // if (Smartgen.check_coil(Auto_Mode)) Serial.println("Auto mode");
    // if (Smartgen.check_coil(Manual_Mode)) Serial.println("Manual mode");
    // if (Smartgen.check_coil(Stop_Mode)) Serial.println("Stop mode");
    // if (Smartgen.check_coil(Common_Alarm)) Serial.println("ALARM");
    // if (Smartgen.check_coil(Emergency_Stop)) Serial.println("Emergency_Stop");

    collectData();
    add_line_to_end_file(DataAll, "/history.txt");
    // OpenFileRead("/history.txt");
    vTaskDelay(10000);
  }
}

void BallansTask( void * parameter){
  for(;;){
    xSemaphoreTake(mutex_v, portMAX_DELAY);
    if (connect_mqtt){
      // vTaskSuspend(PingReqHandle);
      // GSM.Ballans(PDU); // Запрос балланса PDU - весь текст из сообщения, SUM - только сумма
      // vTaskDelay(30000);
      GSM.Ballans(SUM); // Запрос балланса PDU - весь текст из сообщения, SUM - только сумма
      GSM.Ballans(PDU); // Запрос балланса PDU - весь текст из сообщения, SUM - только сумма
      // vTaskResume(PingReqHandle);
    }
    xSemaphoreGive(mutex_v);
    vTaskDelay(3000000);
  }
}

void BlinkConnect( void * parameter){
  for(;;){
    if (GSM._blink_connect){
      digitalWrite(2, HIGH);
      vTaskDelay(100);
      digitalWrite(2, LOW);
      vTaskDelay(1000);
    }
    else{
      digitalWrite(2, HIGH);
      vTaskDelay(30);
      digitalWrite(2, LOW);
      vTaskDelay(300);
    }
  }
}

void _Ping_Req( void * parameter){
  for(;;){
    xSemaphoreTake(mutex_v, portMAX_DELAY);
    // vTaskSuspend(BallansHandle);
      if (connect_mqtt && !GSM._Reconnect_flag){
        Serial.print("Flag connect - "), Serial.println(connect_mqtt);
        if(!GSM.MQTT_pingreq()) {
            vTaskSuspend(NULL);
            Serial.println("Semaphore Reconnect_Sem Start in GPRS in _Ping_Req"); xSemaphoreGive(GSM.Reconnect_Sem);
        }
      }
    // vTaskResume(BallansHandle);
    xSemaphoreGive(mutex_v);
    vTaskDelay(20000);
  }
}

void Waiting_Command( void * parameter){
  for(;;){
        // if (Pablish_Ping_flag) return;
        xSemaphoreTake(mutex_v, portMAX_DELAY);

        // Serial.print("GSM.MQTT_command_flag = "), Serial.println(GSM.MQTT_command_flag);
        if (GSM.MQTT_command_flag){
          // Waiting_Command_flag = true;
          Serial.println("Yes command from server!!!");
          GSM.MQTT_command_flag = false;
          if (strstr(GSM.MqttMes.Topic, "base/relay/Command") != NULL){
            Serial.println("Topic is command!!!!");
            if (strstr(GSM.MqttMes.PayloadText, "manual") != NULL){
              Serial.println("Manual Mode");
              Smartgen.write_singlCoil( 4 ,1);
            }
            if (strstr(GSM.MqttMes.PayloadText, "auto") != NULL){
              Serial.println("Auto Mode");
              Smartgen.write_singlCoil( 3 ,1);
            }
            if (strstr(GSM.MqttMes.PayloadText, "stop") != NULL){
              Serial.println("Stop!!!");
              Smartgen.write_singlCoil( 1 ,1);
            }
            if (strstr(GSM.MqttMes.PayloadText, "start") != NULL){
              Serial.println("Start!!!!");
              // Smartgen.write_singlCoil( 0 ,1);
            }
            // GetModbusAll();

            Serial.println("Publish new data after command");
            GSM.MQTT_publish("station/controller/all_param_message", DataAll);
          }
          // Waiting_Command_flag = false;
        }

        xSemaphoreGive(mutex_v);
    vTaskDelay(1);
  }
}

void SafeConnect_frtos( void * parameter){
  for(;;){
    xSemaphoreTake(mutex_v, portMAX_DELAY);
    // if (Waiting_Command_flag) return;
    // Pablish_Ping_flag = true;
    // Serial.println("SafeConnect_frtose gone");
    // Serial.print("__Reconnect_flag = "), Serial.println(GSM._Reconnect_flag);
    // Serial.print("_blink_connect = "), Serial.println(GSM._blink_connect);
    GSM.MQTT_safeConnect();
    // if (!GSM.MQTT_safeConnect()){
    //   GSM.Reconnect_Task_flag = true;
    // }
    // vTaskSuspend(BallansHandle);

    // vTaskResume(BallansHandle);
    xSemaphoreGive(mutex_v);
    // Pablish_Ping_flag = false;
    vTaskDelay(1000);
  }
}

void Publish_frtos( void * parameter){
  for(;;){
    xSemaphoreTake(mutex_v, portMAX_DELAY);
    // if (Waiting_Command_flag) return;
    // Pablish_Ping_flag = true;

    vTaskDelay(200);
    collectData();
    // if( !GSM.MQTT_publishTimer("station/controller/all_param_message", DataAll, 30)) {
    if( !GSM.MQTT_publish("station/controller/all_param_message", DataAll)) {
      Serial.println(" No Publish and flag of Reconnect = true");
      GSM.Reconnect_Task_flag = true;
    }

    xSemaphoreGive(mutex_v);
    // Pablish_Ping_flag = false;
    vTaskDelay(60000);
  }
}

// GPS.start(60000);

void loop() {

  // if (BallansGet.Go()){
  //   GSM.Ballans(SUM);
  // }

  // GSM.MQTT_safeConnect();

  // GSM.MQTT_publishTimer("station/controller/all_param_message",
  // DataAll,
  // // "Kovali_azimut_20#213@0@0@214@0@214@499@0@0@0@0@0@0@0@0@0@0@42@3145@0@96@75@277@0@135@0@0@0@0@0@30@0@0@0@0@1@2@0@0@0@2@0@0@42@52@6@0@156@0@204@#40@0@800@2004@1402@#65.53@41@94@0.13#F@55.623221@49.156243@F@F#SMARTGEN",
  // 30);

  if (Serial.available()){           // Ожидаем прихода данных (ответа) от модема...
    GSM_uart.write(Serial.read());    // ...и выводим их в Serial
  }

}

void read_settings(){
  Serial.println("================= Read settings start =================");
  File f = SPIFFS.open("/1.txt", "r");
  while(f.available()) {
      Serial.print(f.readString());
    }
  f.close();

  char line1[100] = "";
  // char line2[100] = "";
  f = SPIFFS.open("/1.txt", "r");

  f.readBytesUntil('\n', line1, 100);
  save_parameter(GSM.mqtt.mqtt_id, line1);
  clear_char(line1);
  Serial.print("GSM.mqtt.mqtt_id = "), Serial.println(GSM.mqtt.mqtt_id);

  f.readBytesUntil('\n', line1, 100);
  save_parameter(GSM.mqtt.user, line1);
  clear_char(line1);

  f.readBytesUntil('\n', line1, 100);
  save_parameter(GSM.mqtt.password, line1);
  clear_char(line1);


        #define _BEELINE_APN  "internet.beeline.ru"
        #define _BEELINE_USER  "beeline"
        #define _BEELINE_PWD  "beeline"
        #define _BEELINE_BALL  "\"*100#\""
        //
        // oper MEGAFON;
        #define _MEGAFON_APN  "\"internet\""
        #define _MEGAFON_USER  "\"gdata\""
        #define _MEGAFON_PWD  "\"gdata\""
        #define _MEGAFON_BALL  "\"*100#\""

  f.readBytesUntil('\n', line1, 100);
  save_parameter(GSM.oper_put.gsm, line1);
  clear_char(line1);
  Serial.print("GSM.oper_put.gsm = "), Serial.println(GSM.oper_put.gsm);

  if (strstr(GSM.oper_put.gsm, "MEGAFON") != NULL){
    clear_char(GSM.oper_put.APN), strcat(GSM.oper_put.APN, _MEGAFON_APN);
    clear_char(GSM.oper_put.user_gsm), strcat(GSM.oper_put.user_gsm, _MEGAFON_USER);
    clear_char(GSM.oper_put.pwd), strcat(GSM.oper_put.pwd, _MEGAFON_PWD);
    clear_char(GSM.oper_put.ball), strcat(GSM.oper_put.ball, _MEGAFON_BALL);
    f.readBytesUntil('\n', line1, 100);
    f.readBytesUntil('\n', line1, 100);
    f.readBytesUntil('\n', line1, 100);
  }

  if (strstr(GSM.oper_put.gsm, "BEELINE") != NULL){
    clear_char(GSM.oper_put.APN), strcat(GSM.oper_put.APN, _BEELINE_APN);
    clear_char(GSM.oper_put.user_gsm), strcat(GSM.oper_put.user_gsm, _BEELINE_USER);
    clear_char(GSM.oper_put.pwd), strcat(GSM.oper_put.pwd, _BEELINE_PWD);
    clear_char(GSM.oper_put.ball), strcat(GSM.oper_put.ball, _BEELINE_BALL);
    f.readBytesUntil('\n', line1, 100);
    f.readBytesUntil('\n', line1, 100);
    f.readBytesUntil('\n', line1, 100);
  }

  if (strstr(GSM.oper_put.gsm, "OTHER") != NULL){
    f.readBytesUntil('\n', line1, 100);
    save_parameter(GSM.oper_put.APN, line1);
    clear_char(line1);
    Serial.print("GSM.oper_put.APN = "), Serial.println(GSM.oper_put.APN);

    f.readBytesUntil('\n', line1, 100);
    save_parameter(GSM.oper_put.user_gsm, line1);
    clear_char(line1);
    Serial.print("GSM.oper_put.user_gsm = "), Serial.println(GSM.oper_put.user_gsm);

    f.readBytesUntil('\n', line1, 100);
    save_parameter(GSM.oper_put.pwd, line1);
    clear_char(line1);
    Serial.print("GSM.oper_put.pwd = "), Serial.println(GSM.oper_put.pwd);
  }
  else{
    f.readBytesUntil('\n', line1, 100);
    f.readBytesUntil('\n', line1, 100);
    f.readBytesUntil('\n', line1, 100);
  }
// ----------------
    f.readBytesUntil('\n', line1, 100);
    save_parameter(GSM.object_station.status_locate, line1);
    clear_char(line1);
    Serial.print("GSM.object_station.status_locate = "), Serial.println(GSM.object_station.status_locate);

    f.readBytesUntil('\n', line1, 100);
    save_parameter(GSM.GPS_DATA.latitude, line1);
    clear_char(line1);
    Serial.print("GSM.GPS_DATA.latitude = "), Serial.println(GSM.GPS_DATA.latitude);

    f.readBytesUntil('\n', line1, 100);
    save_parameter(GSM.GPS_DATA.logitude, line1);
    clear_char(line1);
    Serial.print("GSM.GPS_DATA.logitude = "), Serial.println(GSM.GPS_DATA.logitude);
// -------------
    f.readBytesUntil('\n', line1, 100);
    save_parameter(GSM.object_station.type_controller, line1);
    clear_char(line1);
    Serial.print("GSM.object_station.type_controller = "), Serial.println(GSM.object_station.type_controller);

    f.readBytesUntil('\n', line1, 100);
    save_parameter(GSM.object_station.type_GSM, line1);
    clear_char(line1);
    Serial.print("GSM.object_station.type_GSM = "), Serial.println(GSM.object_station.type_GSM);



  Serial.println("+++++++++++++++++ Read settings stop +++++++++++++++++++");
}

void save_parameter(char* parameter, char* line){
  // Serial.print("line = "), Serial.println(line);
  ShiftLine_FindChar(line, '\"');
  // Serial.print("line = "), Serial.println(line);
  clear_char(parameter);
  FirstWordLineToChar(line, parameter, '\"');
  Serial.print("parameter = "), Serial.println(parameter);
}

char* ShiftLine_FindChar(char* Line, char ch){
  char *p;
  int EndLen;
  p = strchr(Line, ch) + 1;
  EndLen = strlen(Line) - (p - Line);
  memmove(Line, p, EndLen);
  Line[EndLen] = NULL;
  return Line;
}

char* FirstWordLineToChar(char* Line, char* word, char ch){
  char result[500] = "";
  strcat(result, Line);
  int EndLen = strchr(result, ch) - result;
  result[EndLen] = NULL;
  strcat(word, result);
  return word;
}

void clear_char(char* MassChar){
  memset(MassChar, NULL, sizeof(MassChar));
}

void check_settings(){
  if (strstr(GSM.object_station.status_locate, "fix") != NULL){

  }
}
