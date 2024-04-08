// #include <SPIFFS.h>
// #include "./My_piffs.h"
// #define BEELINE  "\"*102#\""
// #define MEGAFON  "\"*100#\""
// #define TELE2     "\"*105#\""

// #define _MEG     struct megafon



#define PDU 0
#define SUM 1

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

typedef struct {
  char APN[200];
  char USER[200];
  char PWD[200];
  char BALL[200];
} GSM_OPER;

GSM_OPER *_OPER_OUT;

GSM_OPER MEGAFON = {
  _MEGAFON_APN,
  _MEGAFON_USER,
  _MEGAFON_PWD,
  _MEGAFON_BALL
};

GSM_OPER BEELINE = {
  _BEELINE_APN,
  _BEELINE_USER,
  _BEELINE_PWD,
  _BEELINE_BALL
};

struct {
  char mqtt_id[100] = "";
  char user[100] = "";
  char password[100] = "";
  char gsm[100] = "";
  char APN[100] = "";
  char user_gsm[100] = "";
  char pwd[100] = "";
  char Lat[100] = "";
  char Lon[100] = "";
  char type[100] = "";

} Settings_main;
