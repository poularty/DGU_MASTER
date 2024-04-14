#ifndef GSM_My_h
#define GSM_My_h

#include <HardwareSerial.h>
#include <SoftwareSerial.h>

#include <Arduino.h>
#include <stdarg.h>
#include <typeinfo>
// #include "USSD.h"
// #include "gnss.h"

#include "Timer/Timer.h"
// #include "mqtt.h"
// #include "oper.h"
// #include "util/USSD.h"
// #include "util/somefunc.h"

class GSM_Un {



  // TimerGO SafeConnect;
  // TimerGO TimePublish;


  // GSM_OPER BEELINE{
  //   _BEELINE_APN,
  //   _BEELINE_USER,
  //   _BEELINE_PWD,
  //   _BEELINE_BALL
  // };


  // typedef struct GSM_OPER MEGAFON;

  public:

    TimerGO SafeConnect;
    TimerGO TimePublish;

    struct {
      char mqtt_id[100] = "";
      char user[100] = "";
      char password[100] = "";
    } mqtt;

    // typedef struct GSM_OPER;
    #include "variable.h"

    struct {
      char gsm[100] = "";
      char APN[100] = "";
      char user_gsm[100] = "";
      char pwd[100] = "";
      char ball[100] = "";
    } oper_put;

    // bool object_station;

    struct{
      char status_locate[20];
      char type_controller[20];
      char type_GSM[20];
      char reset_GSM[20];
    } object_station;

    bool flag_all_GSM_init = false;

    // #include "util/variable.h"
    // typedef struct {
    //   char APN[200];
    //   char USER[200];
    //   char PWD[200];
    //   char BALL[200];
    // } GSM_OPER;
//================ IN GSM_My.cpp ==========================================
    GSM_Un(Stream &Ser_GSM, Stream &Debug);
    GSM_Un(Stream &Ser_GSM, Stream &Debug, char* _Oper);
    // static void ReadUartGSM(void * parameter);
    // void _ReadUartGSM();
    // void StartUartRead();
    void GSM_listen_Uart();

    typedef struct Listen_Bufer{
      uint8_t message[256];
    } Listen_Bufer;
    QueueHandle_t queue_bufer = xQueueCreate(1, sizeof(Listen_Bufer));
    QueueHandle_t queue_CIPRXGET = xQueueCreate(1, sizeof(Listen_Bufer));
    QueueHandle_t queue_ballans = xQueueCreate(1, sizeof(Listen_Bufer));
    Listen_Bufer payload;
    SemaphoreHandle_t CIPRXGET_start = xSemaphoreCreateBinary();
    bool _data_start = false;
    bool _CIPRXGET_start = false;

    // memset(payload.message, 0, 256);
    // memcpy(payload.message, "Example text", strlen(str));
    //

    char* AT(char* Command);
    char* AT_as(char* Command);
    char* AT_as(char* Command, int Wait);
    char* AT(char* Command, char* Responce);
    char* AT_as(char* Command, char* Responce);
    char* AT_as(char* Command, char* Responce1, char* Responce2);
    char* AT_as(char* Command, char* Responce1, char* Responce2, char* Responce3);
    char* AT_as(char* Command, char* Responce1, char* Responce2, char* Responce3, char* Responce4);
    char* AT(int n, ... );
    char* AT_as(int n, ... );
    char* AT(char* Command, char* Responce, byte num);
    char* AT(char* Command, int Timeout);
    char* AT(char* Command, char* Responce, int Timeout);
    char* waitingUart(uint64_t Timeout);
    void ChekBuferGSMIn();
// ========================================================================

//================ IN service.h ==========================================
    char* Ballans(GSM_OPER, int Asq);
    char* Ballans(int Asq);
    char* Ballans_all(GSM_OPER P);
    bool _ballans_start = false;
    bool Network_check();
    bool Module_init();
    bool GPRS();
    bool GPRS_check();
    bool TCP_connect();
    bool TCP_connect_flag = false;
    bool Reconnect();
    bool _Reconnect_flag = false;
    SemaphoreHandle_t Reconnect_Sem = xSemaphoreCreateBinary();
    char* getMQTTmessage(char* message);
    bool chekDataRX();
    void hendlerCommand(uint8_t);
    void check_Uart_command();
    void CIPRXGET_handler_task();
    SemaphoreHandle_t CIPRXGET_hendler_start = xSemaphoreCreateBinary();
    char* getDataCIPRXGET_task();
    char CIPRXGET_bufer[1000] = "";
    char* getDataRX();
    char* getDataRX(char* Test);
    void checkCommand();
    char* HexCharToChar(char* Data);
    char* ConvertHEXLatToKir(char* Line);
    void Transliterate(char* str, uint8_t Chr);

    struct {
      char CSQ[100] = "";
      char CSQ_VAL[100] = "";
      char Temp_SIMMODULE[100] = "";
      char OperInfo[100] = "";
      char Date_SIMMODULE[100] = "";
      char Time_SIMMODULE[100] = "";
      char Ballans_PDU[500] = "";
      char Ballans_SUM[500] = "";

    } Service_info;

    char* Get_CSQ();
    char* Get_TempModuleGSM();
    char* Get_OperInfo();

    bool Reconnect_Task_flag = false;
// ========================================================================

    char Bufer[1000] = "";
    char CharHexBufer[1000] = "";
    char Inc[500]   = "";
    char MQTT_MesBufer[1000] = "";

    struct {
      uint8_t Head;
      uint8_t RemL;
      uint16_t TopL;
      char Topic[500] = "";
      uint8_t IdentifierHi;
      uint8_t IdentifierLow;
      char Payload[500] = "";
      char PayloadText[500] = "";
    } MqttMes;

    bool MQTT_command_flag = false;

    // uint8_t sourseCommand;


//================ IN MQTT.h ==========================================
    bool MQTT_connect();
    bool _mqttConnect_flag = false;
    bool MQTT_publish(char* topic, char* message);
    bool _mqttPublish_flag = false;
    bool MQTT_pubback();
    bool MQTT_publishTimer(char* topic, char* message, uint8_t timer);
    bool MQTT_subscribe(char* topic);
    bool MQTT_UNsubscribe(char* topic);
    bool MQTT_pingreq();
    bool _pingreq_flag = false;
    bool MQTT_safeConnect();
    bool _blink_connect = false;
    uint32_t _TimeSafeConnect;
    uint32_t _TimePublish;
// ========================================================================

//================ gnss.h ==========================================
    bool GNSS_powerOn();
    bool GNSS_powerOff();
    void GNSS_get_inf();
    bool GNSS_get_CLBS();
    void GNSS_CLBS_parse_to_struct();
    char _GNSS_Bufer[1000] = "";
    void GNSS_parse_to_struct();
    struct GGPS_DATA {
    // struct {
        char GNSSrunstatus[2];//GNSS run status:0 = GNSS off and 1 = GNSS on
        char Fixstatus[2];//Fix status:0 = Not fixed positon and 1 = Fixed positon
        char UTCdatetime[19];//UTC date & Time
        char latitude[11];//Latitude
        char logitude[12];//Longitude
        char altitude[9];//MSL Altitude
        char speedOTG[7];//Speed Over Ground
        char course[7];//Course Over Ground
        char fixmode[2];//Fix Mode
        char Reserved1[2];//Reserved1
        char HDOP[5];//HDOP
        char PDOP[5];//PDOP
        char VDOP[5];//VDOP
        char Reserved2[2];//Reserved2
        char satellitesinview[3];//GPS Satellites in View
        char GNSSsatellitesused[3];//GNSS Satellites Used
        char GLONASSsatellitesused[3];//GLONASS Satellites in View
        char Reserved3[2];//Reserved3
        char CN0max[3];//C/N0 max
        char HPA[7];//HPA
        char VPA[7];//VPA
    }; struct GGPS_DATA GPS_DATA;
    // } GPS_DATA;
    void GNSS_to_char();
    char GNSS_bufer[200] = "";



// ========================================================================

//================ sms.h ==========================================
    void SMS_pdu_list(uint8_t stat, uint8_t mode);
    void SMS_pdu_list(char* stat, uint8_t mode);
    void SMS_pdu_list(uint8_t stat);
    bool SMS_read_textF(uint16_t num, uint8_t mode);
    struct {
      char state[20] = "";
      char Number[20] = "";
      char DateTime[50] = "";
      char PayLoad[500] = "";
      char PayLoadText[500] = "";
    } SMStextFMes;
    void SMS_del_all();
    void SMS_send_textF(char* Number, char* Text);
    void SMS_getNumb_newMes(char* Line);

    uint8_t NumNewMes;
    bool flagNewMes = false;



// ======= for modbus =====================================================
bool state_command_ModBus = false;
uint16_t coil_command_ModBus;
uint16_t coil_state_ModBus;
uint16_t regist_command_ModBus;
uint16_t regist_value_ModBus;

// ========================================================================

Stream* _Ser_GSM;
Stream* _Debug;

  private:

    uint8_t _Pin_All_init = 23;
    bool _flag_All_init = false;


    bool _flag_mqtt_con = true;

    // Stream* _Ser_GSM;
    // Stream* _Debug;
    uint16_t _TimeoutDefault = 1000;
    uint16_t _TimeoutResponce = 10000;

    void DebugPrint(char* Line);
    void ClearBuferUart(int Timeout);
    void print_len_data (int x);
    void MQTT_parseMessage(char* Message);
    char _Message[1000] = "";

    // ==============================================
    // USSD.h
    void UCS2ToString(char *s, char * _Bufer);
    unsigned char HexSymbolToChar(char c);
    // float getFloatFromString(String str);
    void strcat_c (char *str, char c);
    void getBallansToChar(char *str, char * InChar);
    void trim(char *s);
    // ==============================================
    // charFunc.h
    char* ShiftLine_FindChar(char* Line, char ch);
    char* ShiftLine_FindChar(char* Line, char ch, int num);
    char* ShiftLine_FindChar(char* Line, char* Fword);
    void ShiftLine_FindChar(char* Line, char* Fword, int num);
    char* FirstWordLineToChar(char* Line, char* word, char ch);
    char* FirstWordLineToChar(char* Line, char* word, char* Fword);
    void clear_char(char* MassChar);

    struct oper {
      char* bal;
      char* APN;
    };




};

#endif
