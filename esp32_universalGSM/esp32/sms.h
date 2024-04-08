
void GSM_Un::SMS_pdu_list(uint8_t stat, uint8_t mode){
  char _s[10] = "";
  itoa(stat, _s, DEC);
  char _m[10] = "";
  itoa(mode, _m, DEC);
  // AT(4, "AT+CMGL=", _s, ",", _m);
  char com[200] = "AT+CMGL=";
  strcat(com, _s);
  strcat(com, ",");
  strcat(com, _m);
  AT(com, 5000);
}

void GSM_Un::SMS_pdu_list(char* stat, uint8_t mode){
  // char _s[10] = "";
  // itoa(stat, _s, DEC);
  char _m[10] = "";
  itoa(mode, _m, DEC);
  // AT(4, "AT+CMGL=", _s, ",", _m);
  char com[200] = "AT+CMGL=";
  strcat(com, stat);
  strcat(com, ",");
  strcat(com, _m);
  AT(com, 5000);
}


void GSM_Un::SMS_pdu_list(uint8_t stat){

}

bool GSM_Un::SMS_read_textF(uint16_t num, uint8_t mode){
  char result[1000] = "";
  char word[1000] = "";
  char numChar[10] = "";
  char modeChar[10] = "";
  itoa(num, numChar, DEC);
  itoa(mode, modeChar, DEC);
  strcat(result, AT(4, "AT+CMGR=", numChar, ",", modeChar));
  if (strstr(result, "+CMGR:") != 0){
    ShiftLine_FindChar(result, '\"');
    // _Debug -> print(">>"), _Debug -> print(result), _Debug -> println("<<");
    FirstWordLineToChar(result, word, '\"');
    clear_char(SMStextFMes.state);
    strcat(SMStextFMes.state, word);
    _Debug -> print(">>"), _Debug -> print(word), _Debug -> println("<<");
    ShiftLine_FindChar(result, '\"', 2);
    // ShiftLine_FindChar(result, '\"');
    clear_char(word);
    FirstWordLineToChar(result, word, '\"');
    clear_char(SMStextFMes.Number);
    strcat(SMStextFMes.Number, word);
    _Debug -> print(">>"), _Debug -> print(word), _Debug -> println("<<");
    ShiftLine_FindChar(result, '\"', 4);
    clear_char(word);
    FirstWordLineToChar(result, word, '\"');
    clear_char(SMStextFMes.DateTime);
    strcat(SMStextFMes.DateTime, word);
    _Debug -> print(">>"), _Debug -> print(word), _Debug -> println("<<");
    ShiftLine_FindChar(result, '\n');
    clear_char(word);
    FirstWordLineToChar(result, word, "OK");
    clear_char(SMStextFMes.PayLoad);
    strcat(SMStextFMes.PayLoad, word);
    clear_char(SMStextFMes.PayLoadText);
    _Debug -> print(">>"), _Debug -> print(word), _Debug -> println("<<");
    if ((!isalpha(SMStextFMes.PayLoad[0]) && !ispunct(SMStextFMes.PayLoad[0])) or
          (!isalpha(SMStextFMes.PayLoad[1]) && !ispunct(SMStextFMes.PayLoad[1]))){
            _Debug -> println("Is not simbol");
            strcat(SMStextFMes.PayLoadText, ConvertHEXLatToKir(SMStextFMes.PayLoad));
            _Debug -> println(SMStextFMes.PayLoadText);

          }
          else{
            _Debug -> println("Is simbol");
            // clear_char(SMStextFMes.PayLoadText);
            strcat(SMStextFMes.PayLoadText, SMStextFMes.PayLoad);
            _Debug -> println(SMStextFMes.PayLoadText);
          }
    return true;
  }
  return false;
}

void GSM_Un::SMS_del_all(){
  AT("AT+CMGD=1,4", "OK");
}

void GSM_Un::SMS_send_textF(char* Number, char* Text){
  AT(5, "AT+CMGS=\"", Number, "\"", "\r", Text);
  _Ser_GSM -> print((char)26);

  uint64_t timeOld = millis();
  char result1[500] = "";
  char result2[500] = "";
  _Ser_GSM -> setTimeout(50);
  _Ser_GSM -> readBytes(result1, 500);

  while ((strstr(result1, "+CMGS") == NULL) && ((millis() - timeOld) < 10000)){
    _Ser_GSM -> readBytes(result2, 500);
    strcat(result1, result2);
    memset(result2, NULL, sizeof(result2));
  }
  _Debug -> println(result1);

}

void GSM_Un::SMS_getNumb_newMes(char* Line){
  char NumMesCh[10] = "";
  ShiftLine_FindChar(Line, '+');
  ShiftLine_FindChar(Line, ',');
  FirstWordLineToChar(Line, NumMesCh, '\r');
  NumNewMes = atoi(NumMesCh);
}
