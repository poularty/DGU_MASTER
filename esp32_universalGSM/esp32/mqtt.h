#include "GSM_My.h"
#include <HardwareSerial.h>
#include <SoftwareSerial.h>




// #define MQTT_ID			"AKSA_1"
// #define MQTT_ID			"Test_esp32_sim868"
#define MQTT_ID			mqtt.mqtt_id
//#define MQTT_ID			"GENSET_TEST_2"
// #define	USER			"poul"
#define	USER			mqtt.user
// #define	PASSWORD		"1808"
#define	PASSWORD		mqtt.password
#define	PROTOKOL		"MQIsdp"
#define KEEP_ALIVE  60
#define PUBLISH_TIMER  60
// #define	PROTOKOL		"MQTT"

// функция отправки байтов длины сообщения
// для функций паблишь и коннект
void GSM_Un::print_len_data (int x) {
  int encodedByte = 0;
  do {
    encodedByte = x % 128;
    x = x / 128;
    // if there are more data to encode, set the top bit of this byte
    if ( x > 0 ){
      encodedByte = encodedByte | 128;
    }
            _Ser_GSM -> write(encodedByte);
        }while ( x > 0 );
}

// функция соединения с брокером
#define CONNACK_OK "20020000"
bool GSM_Un::MQTT_connect(){
  _mqttConnect_flag = false;
  _blink_connect = false;
  _Debug -> println(">>>>>>>>>>>>>>> Connect to broker >>>>>>  MQTT_connect()  ");
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;

  _Debug -> print("MQTT_ID = "), _Debug -> println(MQTT_ID);
  _Debug -> print("USER = "), _Debug -> println(USER);
  _Debug -> print("PASSWORD = "), _Debug -> println(PASSWORD);

  _Debug -> print("MQTT_ID = "), _Debug -> println(mqtt.mqtt_id);
  _Debug -> print("USER = "), _Debug -> println(mqtt.user);
  _Debug -> print("PASSWORD = "), _Debug -> println(mqtt.password);

  _Debug -> println("Start packet");
  _Ser_GSM -> write("AT+CIPSEND"); _Ser_GSM -> write("\n");
  delay(10);
  _data_start = true;
  _Ser_GSM -> write(0x10); 																// фиксированный заголовок о коннекте
	_Ser_GSM -> write(strlen(PROTOKOL)+strlen(MQTT_ID)+strlen(USER)+strlen(PASSWORD) + 12); 	// оставшаяся длина
  delay(100);
  _Ser_GSM -> write((byte)0x00); 																// 1 бит длины протокола
	_Ser_GSM -> write(strlen(PROTOKOL)); 													// 2 бит длины протокола
	_Ser_GSM -> write(PROTOKOL);   															// тип протокола
	//SIM800.write(0x03), SIM800.write(0xC2),SIM800.write((byte)0),SIM800.write(0x3C); 	// 0х03 - версия протокола(00000011),
	_Ser_GSM -> write(0x03);  																// 0х03 - версия протокола(00000011),
	_Ser_GSM -> write(0xC2);																	// флаги коннекта
	// _Ser_GSM -> write(0xC2);																	// флаги коннекта
	// _Ser_GSM -> write(0);																// 1 бит keepAlive
	_Ser_GSM -> write((byte)0x00);																// 1 бит keepAlive
	//SIM800.write(0x46); 																// 2 бит keepAlive
	// _Ser_GSM -> write(60); 																// 2 бит keepAlive
	// _Ser_GSM -> write((byte)60); 																// 2 бит keepAlive
  _Ser_GSM -> write((byte)KEEP_ALIVE); 																// 2 бит keepAlive
	// _Ser_GSM -> write(array, 2); 																// 2 бит keepAlive
	_Ser_GSM -> write((byte)0x00), _Ser_GSM -> write(strlen(MQTT_ID)),    _Ser_GSM -> write(MQTT_ID);
	_Ser_GSM -> write((byte)0x00), _Ser_GSM -> write(strlen(USER)),       _Ser_GSM -> write(USER);
	_Ser_GSM -> write((byte)0x00), _Ser_GSM -> write(strlen(PASSWORD)),   _Ser_GSM -> write(PASSWORD);
	_Ser_GSM -> write(0x1A);
  _Debug -> println("Stop packet");




  xQueueReceive(queue_bufer, &result1, 1000/portTICK_RATE_MS);
  // _Debug -> print("result1 = "), _Debug -> println(result1);
 time = millis();
  while((strstr(result1, "SEND OK") == NULL) && ((millis() - time) < 10000)) {
    xQueueReceive(queue_bufer, &result2, 1000/portTICK_RATE_MS);
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }

  // _Debug -> print("result1 Connect= "), _Debug -> println(result1);
  _data_start = false;

  time = millis();
   while(!_mqttConnect_flag && ((millis() - time) < 10000)) {}
   if (_mqttConnect_flag){
     _Debug -> println(" Yes Connect");
     SafeConnect.resetGo();
     _blink_connect = true;
     return true;
   }
   return false;

}

// функция публикации сообщения на брокер
#define PUBBACK_OK "40020010"
bool GSM_Un::MQTT_publish(char* topic, char* message){
  _mqttPublish_flag = false;
  _Debug -> println(">> Publish data <<<");
  _Debug -> println(topic);
  _Debug -> println(message);
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;

  _Ser_GSM -> write("AT+CIPSEND"); _Ser_GSM -> write("\n");
  delay(10);
  _data_start = true;
  _Ser_GSM -> write(0x32);
	print_len_data(strlen(topic)+strlen(message) + 4);
	_Ser_GSM -> write((byte)0);
	_Ser_GSM -> write(strlen(topic));
	_Ser_GSM -> write(topic); // топик
	_Ser_GSM -> write((byte)0);
	_Ser_GSM -> write(0x10);
	_Ser_GSM -> write(message);
	_Ser_GSM -> write(0x1A);

  xQueueReceive(queue_bufer, &result1, 1000/portTICK_RATE_MS);
  // _Debug -> print("result1 = "), _Debug -> println(result1);
 time = millis();
  while((strstr(result1, "SEND OK") == NULL) && ((millis() - time) < 9000)) {
    xQueueReceive(queue_bufer, &result2, 1000/portTICK_RATE_MS);
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }

  // _Debug -> print("result1 Publish= "), _Debug -> println(result1);
  _data_start = false;

  time = millis();
   while(!_mqttPublish_flag && ((millis() - time) < 10000)) {}
   if (_mqttPublish_flag){
     _Debug -> println(" Yes Publish");
     SafeConnect.resetGo();
     return true;
   }
   else {
     // _Debug -> println(" Semaphore Reconnect_Sem Start in MQTT_publish");
     // xSemaphoreGive(Reconnect_Sem);
     return false;
   }

}

#define PUBBACK_OK "40020010"
bool GSM_Un::MQTT_pubback(){
  _Debug -> println(">> Publish pubback <<<");
  char result1[500] = "";
  char result2[500] = "";


  _Ser_GSM -> write("AT+CIPSEND"); _Ser_GSM -> write("\n");
  _Ser_GSM -> setTimeout(200);
  _Ser_GSM -> readBytes(result1, 500);
  _Ser_GSM -> setTimeout(_TimeoutDefault);
  _Debug -> println(result1);
  _Debug -> println("Sending packet");

  _Ser_GSM -> write((byte)0b01000000);
	_Ser_GSM -> write((byte)0b00000010);
	_Ser_GSM -> write((byte)MqttMes.IdentifierHi);
	_Ser_GSM -> write((byte)MqttMes.IdentifierLow);
	_Ser_GSM -> write(0x1A);
  _Debug -> println("stop transmit paket");

  _Ser_GSM -> setTimeout(50);
  _Ser_GSM -> readBytes(result1, 500);


  // if (strstr(result1, "ERROR") != NULL) {
  //   _Debug ->println(result1);
  //   _flag_mqtt_con = false;
  //   return false;
  // }

  uint64_t timeOld = millis();
  while ((strstr(result1, "SEND OK") == NULL) && ((millis() - timeOld) < 10000)){
    // _Debug -> println("Waiting SEND OK");
    _Ser_GSM -> readBytes(result2, 500);
    strcat(result1, result2);
    memset(result2, NULL, sizeof(result2));
    // _Debug -> println(result2);
  }
  _Ser_GSM -> setTimeout(_TimeoutDefault);

  if (strstr(result1, "SEND OK") != NULL){
        _Debug -> println("SEND OK");
        _flag_mqtt_con = true;
        SafeConnect.resetGo();
        return true;
      }


  _flag_mqtt_con = false;

  return false;
}

// функция публикации сообщения на брокер с таймером в секундах
#define PUBBACK_OK "40020010"
bool GSM_Un::MQTT_publishTimer(char* topic, char* message, uint8_t timer){
  // TimePublish.setTime(timer * 1000);

  if (!TimePublish.Go()) {
    // _flag_mqtt_con = false;
    return false;
  }

  MQTT_publish(topic, message);

  // if (!MQTT_publish(topic, message)) {
  // if (!_mqttPublish_flag) {
  //   // _Debug -> println(" Semaphore Reconnect_Sem Start in MQTT_publishTimer");
  //   // xSemaphoreGive(Reconnect_Sem);
  // }

}

bool GSM_Un::MQTT_subscribe(char* topic){
  _Debug -> println(">> Subscribe on topic <<<");
  char result1[500] = "";
  char result2[500] = "";

  _Ser_GSM -> write("AT+CIPSEND"); _Ser_GSM -> write("\n");
  _Ser_GSM -> setTimeout(200);
  _Ser_GSM -> readBytes(result1, 500);
  _Ser_GSM -> setTimeout(_TimeoutDefault);

  _Ser_GSM -> write(0x82);                                                // команда отправки subscribe
  _Ser_GSM -> write(strlen(topic)+5);                                     // длина оставшегося сообщения
  _Ser_GSM -> write((byte)0);                                             // первый байт пакета идентификатора
  _Ser_GSM -> write(0x01);                                                // идентификатор равный 1
  _Ser_GSM -> write((byte)0);                                             // превый байт длины топика
  _Ser_GSM -> write(strlen(topic));                                  // второй байт длины топика
  _Ser_GSM -> write(topic);                                          // топик подписки
  _Ser_GSM -> write((byte)0);                                         // QOS = 0
  _Ser_GSM -> write(0x1A);

  _Ser_GSM -> readBytes(result1, 500);
  if (strstr(result1, "ERROR")) {
    _Debug ->println(result1);
    _flag_mqtt_con = false;
    return false;
  }

  uint64_t timeOld = millis();
  while ((strstr(result1, "SEND OK") == NULL) && ((millis() - timeOld) < 10000)){
    _Ser_GSM -> readBytes(result2, 500);
    strcat(result1, result2);
    memset(result2, NULL, sizeof(result2));
  }

  if (strstr(result1, "SEND OK") != NULL){
      if (strstr(getDataRX(), PUBBACK_OK) != NULL) {
        _Debug -> println("======= PUBLISH OK =========");
        _flag_mqtt_con = true;
        SafeConnect.resetGo();
        return true;
      }
    }

  _flag_mqtt_con = false;
  return false;
}

bool GSM_Un::MQTT_UNsubscribe(char* topic){
  _Debug -> println(">> UNsubscribe on topic <<<");
  char result1[500] = "";
  char result2[500] = "";

  _Ser_GSM -> write("AT+CIPSEND"); _Ser_GSM -> write("\n");
  _Ser_GSM -> setTimeout(200);
  _Ser_GSM -> readBytes(result1, 500);
  _Ser_GSM -> setTimeout(_TimeoutDefault);

  _Ser_GSM -> write((byte)0b10100010);                                                // команда отправки subscribe
  _Ser_GSM -> write(strlen(topic)+5);                                     // длина оставшегося сообщения
  _Ser_GSM -> write((byte)0);                                             // первый байт пакета идентификатора
  _Ser_GSM -> write(0x01);                                                // идентификатор равный 1
  _Ser_GSM -> write((byte)0);                                             // превый байт длины топика
  _Ser_GSM -> write(strlen(topic));                                  // второй байт длины топика
  _Ser_GSM -> write(topic);                                          // топик подписки
  _Ser_GSM -> write((byte)0);                                         // QOS = 0
  _Ser_GSM -> write(0x1A);

  _Ser_GSM -> readBytes(result1, 500);
  if (strstr(result1, "ERROR")) {
    _Debug ->println(result1);
    _flag_mqtt_con = false;
    return false;
  }

  uint64_t timeOld = millis();
  while ((strstr(result1, "SEND OK") == NULL) && ((millis() - timeOld) < 10000)){
    _Ser_GSM -> readBytes(result2, 500);
    strcat(result1, result2);
    memset(result2, NULL, sizeof(result2));
  }

  if (strstr(result1, "SEND OK") != NULL){
      if (strstr(getDataRX(), PUBBACK_OK) != NULL) {
        _Debug -> println("======= PUBLISH OK =========");
        _flag_mqtt_con = true;
        SafeConnect.resetGo();
        return true;
      }
    }

  _flag_mqtt_con = false;
  return false;
}

// функция отправки брокеру сообщения для поддержания связи
#define PINGresp_OK "D000"
bool GSM_Un::MQTT_pingreq(){
  _pingreq_flag = false;
  _data_start = true;
  // delay(200);
  _Debug -> println(">>>> ping to broker <<<<<");
  char result1[500] = "";
  char result2[500] = "";
  uint32_t time;


  _Ser_GSM -> write("AT+CIPSEND"); _Ser_GSM -> write("\n");
  delay(100);
  _Ser_GSM -> write((byte)0xC0);
  _Ser_GSM -> write((byte)0x00);
  _Ser_GSM -> write((byte)0x1A);
  _Debug -> println("End data");

  xQueueReceive(queue_bufer, &result1, 1000/portTICK_RATE_MS);
  // _Debug -> print("result1 = "), _Debug -> println(result1);
  time = millis();
  while((strstr(result1, "SEND OK") == NULL) && (strstr(result1, "ERROR") == NULL) && ((millis() - time) < 2000)) {
    xQueueReceive(queue_bufer, &result2, 1000/portTICK_RATE_MS);
    // _Debug -> print("result2 = "), _Debug -> println(result2);
    strcat(result1, result2);
    clear_char(result2);
  }

  if (strstr(result1, "ERROR") != NULL){
    _Debug -> println(result1);
    _data_start = false;
    // _Debug -> println(" Semaphore Reconnect_Sem Start in MQTT_pingreq"); xSemaphoreGive(Reconnect_Sem
    return false;
  }

  // _Debug -> print("result1 = "), _Debug -> println(result1);
  _data_start = false;

  time = millis();
   while(!_pingreq_flag && ((millis() - time) < 20000)) {}
   if (_pingreq_flag){
     _pingreq_flag = false;
     return true;
   }
   _blink_connect = false;
   return false;

}


bool GSM_Un::MQTT_safeConnect(){
  // if (!_Reconnect_flag && !_flag_mqtt_con){
  if (!_Reconnect_flag && _blink_connect){
    // _Debug -> println("No reconnect");
    if ( SafeConnect.Go()) {
    // if (0) {
      // _Debug -> print("Timer safeconnect = "), _Debug -> println(SafeConnect.getTimeRemains());
      // _Debug -> print("Timer set = "), _Debug -> println(SafeConnect.return_Tset());
      // _Debug -> println("Timer SafeConnect Gone");

      if ( !MQTT_pingreq()) {
        _Debug -> println("No ping");
        _blink_connect = false;
        Reconnect_Task_flag = true;
        // Reconnect();
        // if ( !_Reconnect_flag) _Debug -> println(" Semaphore Reconnect_Sem Start in MQTT_safeConnect");
        // xSemaphoreGive(Reconnect_Sem);
        return false;
      }
    _blink_connect = true;
    // SafeConnect.resetGo();
    return true;
    }

    return false;
  }
  // _blink_connect = false;
  return false;
}
