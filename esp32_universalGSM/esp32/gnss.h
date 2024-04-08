// включение функции GNSS
bool GSM_Un::GNSS_powerOn(){
  char result[200] = "";
  strcat(result, AT("AT+CGNSPWR=1"));
  if (strstr(result, "OK") != NULL) return true;
  return false;
}

// выключение функции GNSS
bool GSM_Un::GNSS_powerOff(){
  char result[200] = "";
  strcat(result, AT("AT+CGNSPWR=0"));
  if (strstr(result, "OK") != NULL) return true;
  return false;
}

// Получение координат
void GSM_Un::GNSS_get_inf(){
  char result[500] = "";
  // strcat(result, AT_as("AT+CGNSINF", "OK"));
  strcat(result, AT_as("AT+CGNSINF", "OK"));
  // _Debug -> print("Result GNSS_inf = "), _Debug -> println(result);
  clear_char(_GNSS_Bufer);
  strcat(_GNSS_Bufer, result);
}

// Получение координат от через сервер от стовых вышек
bool GSM_Un::GNSS_get_CLBS(){
  char result[500] = "";
  // strcat(result, AT_as("AT+CGNSINF", "OK"));
  // AT_as("AT+SAPBR=2,1");
  // AT_as("AT+CLBSCFG=0,3");
  clear_char(result);
  strcat(result, AT_as("AT+CLBS=4,1", 20));

  if (strstr(result, "+CLBS") == NULL){
    return false;
  }

  clear_char(_GNSS_Bufer);
  strcat(_GNSS_Bufer, result);
  _Debug -> print("GNSS bufer = "), _Debug -> println(_GNSS_Bufer);

  return true;
}

void GSM_Un::GNSS_CLBS_parse_to_struct(){
  char result1[500] = "";
  char result2[500] = "";
  memset( &GPS_DATA, NULL , sizeof(struct GGPS_DATA));

  strcat(result1, ShiftLine_FindChar(_GNSS_Bufer, ','));
  // clear_char(GPS_DATA.logitude);
  FirstWordLineToChar(result1, GPS_DATA.logitude, ',');

  strcat(result2, ShiftLine_FindChar(result1, ','));
  // clear_char(GPS_DATA.latitude);
  FirstWordLineToChar(result2, GPS_DATA.latitude, ',');

  clear_char(result1);
  // clear_char(GPS_DATA.UTCdatetime);
  // _Debug -> print("result2 = "), _Debug -> print(result2);
  strcat(result1, ShiftLine_FindChar(result2, ',', 2));
  // _Debug -> print("result1 = "), _Debug -> print(result1);
  FirstWordLineToChar(result1, GPS_DATA.UTCdatetime, '\r');

  strcat(GPS_DATA.satellitesinview, "GSM");

  _Debug -> print("lat = "), _Debug -> print(GPS_DATA.latitude), _Debug -> print("   long = "), _Debug -> print(GPS_DATA.logitude);
  _Debug -> print("  time = "), _Debug -> println(GPS_DATA.UTCdatetime);

}

void GSM_Un::GNSS_parse_to_struct(){
  int counter = 0;
    char tmp[150] = {0};
    char *lptr = NULL;
    char *localptr = NULL;

    lptr=strstr(_GNSS_Bufer,"+CGNSINF");
    if(lptr==NULL)return;
    else lptr+=10;

    while(*lptr!='\0')
    {
        if(*lptr==','&&*(lptr+1)==',')
        {
            tmp[counter]=*lptr;
            counter++;
            tmp[counter]='0';
        }
        else if(*lptr=='\r'&&*(lptr+1)=='\n'&&counter<148)
        {
            tmp[counter]   = '0';
            tmp[counter+1] = ',';
            tmp[counter+2] = 0;
            break;
        }
        else
            tmp[counter]=*lptr;

        lptr++;
        counter++;

        //avoid array out of range
        if(counter>=148)return;
    }
    //Clear struct data
    memset( &GPS_DATA, NULL, sizeof(struct GGPS_DATA));

    localptr = strtok(tmp,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.GNSSrunstatus,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.Fixstatus,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.UTCdatetime,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.latitude,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.logitude,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.altitude,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.speedOTG,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.course,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.fixmode,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.Reserved1,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.HDOP,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.PDOP,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.VDOP,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.Reserved2,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.satellitesinview,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.GNSSsatellitesused,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.GLONASSsatellitesused,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.Reserved3,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.CN0max,localptr);

    localptr = strtok(NULL,",");if(localptr == NULL) return;
    strcpy(GPS_DATA.HPA,localptr);

    localptr = strtok(NULL,"\r\n");if(localptr == NULL) return;
    strcpy(GPS_DATA.VPA,localptr);

}

void GSM_Un::GNSS_to_char(){
  uint32_t num;
  char word[20] = "";
  clear_char(GNSS_bufer);
  strcat(GNSS_bufer, GPS_DATA.Fixstatus);
  strcat(GNSS_bufer, "#");
  FirstWordLineToChar(GPS_DATA.UTCdatetime, word, '.');
  num = atoi(word + 6);
  clear_char(word);
  itoa(num, word, HEX);
  strcat(GNSS_bufer, word);
  strcat(GNSS_bufer, "#");
  clear_char(word);
  FirstWordLineToChar(GPS_DATA.latitude, word, '.');
  num = atoi(word);
  clear_char(word);
  itoa(num, word, HEX);
  strcat(GNSS_bufer, word);
  strcat(GNSS_bufer, "#");
  clear_char(word);
  strcat(word, strstr(GPS_DATA.latitude, ".") + 1);
  num = atoi(word);
  clear_char(word);
  itoa(num, word, HEX);
  strcat(GNSS_bufer, word);
  strcat(GNSS_bufer, "#");
  clear_char(word);
  FirstWordLineToChar(GPS_DATA.logitude, word, '.');
  num = atoi(word);
  clear_char(word);
  itoa(num, word, HEX);
  strcat(GNSS_bufer, word);
  strcat(GNSS_bufer, "#");
  clear_char(word);
  strcat(word, strstr(GPS_DATA.logitude, ".") + 1);
  num = atoi(word);
  clear_char(word);
  itoa(num, word, HEX);
  strcat(GNSS_bufer, word);
  strcat(GNSS_bufer, "#");
  clear_char(word);
  FirstWordLineToChar(GPS_DATA.altitude, word, '.');
  num = atoi(word);
  clear_char(word);
  itoa(num, word, HEX);
  strcat(GNSS_bufer, word);
  strcat(GNSS_bufer, "#");
  clear_char(word);
  strcat(word, GPS_DATA.GNSSsatellitesused);
  num = atoi(word);
  clear_char(word);
  itoa(num, word, HEX);
  strcat(GNSS_bufer, word);
  strcat(GNSS_bufer, "#");
  clear_char(word);

  _Debug -> println(GNSS_bufer);

}




// +CGNSINF: 1,1,20230523175936.000,55.725556,49.150234,73.049,0.00,315.9,2,,0.8,1.1,0.8,,12,11,11,,43,, OK

// 1,                   GNSS run status 		-- 			0-1
// 1,                   Fix status 			-- 		        0-1
// 20230523175936.000,  UTC date & Time   		yyyyMMddhh
                                                  					// mmss.sss
                                                  					// 			yyyy: [1980,2039]
                                                  					// 			MM : [1,12]
                                                  					// 			dd: [1,31]
                                                  					// 			hh: [0,23]
                                                  					// 			mm: [0,59]
// 55.725556,           Latitude 	        	±dd.dddddd 		[-90.000000,90.000000]
// 49.150234,           Longitude 			±ddd.dddddd 	        [-180.000000,180.000000]
// 73.049,              MSL Altitude 			meters
// 0.00,                Speed Over Ground 		Km/hour 		[0,999.99]
// 315.9,               Course Over Ground 		degrees 		[0,360.00]
// 2,                   Fix Mode 		        -- 			0,1,2
// ,                    Reserved1
// 0.8,                 HDOP				-- 			[0,99.9]
// 1.1,                 PDOP 				-- 			[0,99.9]
// 0.8,                 VDOP 				-- 			[0,99.9]
// ,                    Reserved2
// 12,                  GPS Satellites in View -- 				[0,99]
// 11,                  GNSS Satellites Used -- 				[0,99]
// 11,                  GLONASS Satellites in View -- 		                [0,99]
// ,                    Reserved3
// 43,                  C/N0 max 		        dBHz 			[0,55]
// ,                    HPA[2] 			        meters 			[0,9999.9]
//                      VPA[2] 			        meters 			[0,9999.9]

 // OK
