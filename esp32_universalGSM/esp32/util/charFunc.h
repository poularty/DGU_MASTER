// находит в строке искомый символ и сдвигает строку влево до этого символа (после него)
char* GSM_Un::ShiftLine_FindChar(char* Line, char ch){
  char *p;
  int EndLen;
  p = strchr(Line, ch) + 1;
  EndLen = strlen(Line) - (p - Line);
  memmove(Line, p, EndLen);
  Line[EndLen] = NULL;
  return Line;
}

// находит в строке Н-ое вхождение искомыго символа и сдвигает строку влево до этого символа (после него)
char* GSM_Un::ShiftLine_FindChar(char* Line, char ch, int num){
  char *p;
  int EndLen;
  p = strchr(Line, ch) + 1;

  for (int i = 0; i < (num - 1); i++){
    p = strchr(p, ch) + 1;
  }

  EndLen = strlen(Line) - (p - Line);

  memmove(Line, p, EndLen);
  Line[EndLen] = NULL;
  return Line;

}

char* GSM_Un::ShiftLine_FindChar(char* Line, char* Fword){
  char *p;
  int EndLen;
  p = strstr(Line, Fword) + 1;
  EndLen = strlen(Line) - (p - Line);
  memmove(Line, p, EndLen);
  Line[EndLen] = NULL;
  return Line;
}

void GSM_Un::ShiftLine_FindChar(char* Line, char* Fword, int num){
  for (int i = 0; i < num; i++){
    ShiftLine_FindChar(Line, Fword);
  }
}

char* GSM_Un::FirstWordLineToChar(char* Line, char* word, char ch){
  char result[500] = "";
  strcat(result, Line);
  int EndLen = strchr(result, ch) - result;
  result[EndLen] = NULL;
  strcat(word, result);
  return word;
}

char* GSM_Un::FirstWordLineToChar(char* Line, char* word, char* Fword){
  char result[500] = "";
  strcat(result, Line);
  int EndLen = strstr(result, Fword) - result;
  result[EndLen] = NULL;
  strcat(word, result);
  return word;
}



void GSM_Un::clear_char(char* MassChar){
  memset(MassChar, NULL, sizeof(MassChar));
}
