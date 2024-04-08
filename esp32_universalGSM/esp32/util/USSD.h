// void UCS2ToString(char *s, char * _Bufer);
// unsigned char HexSymbolToChar(char c);
// // float getFloatFromString(String str);
// void strcat_c (char *str, char c);
// void getBallansToChar(char *str, char * InChar);
// void trim(char *s);

// enum OperType {MTS, BEELINE, MEGAFON, TELE2};

void GSM_Un::UCS2ToString(char *s, char * _Bufer) {                       // Функция декодирования UCS2 строки
  char result[500] = "";
  unsigned char c[5] = "";                            // Массив для хранения результата
  for (int i = 0; i < strlen(s) - 3; i += 4) {       // Перебираем по 4 символа кодировки
    unsigned long code = (((unsigned int)HexSymbolToChar(s[i])) << 12) +    // Получаем UNICODE-код символа из HEX представления
                         (((unsigned int)HexSymbolToChar(s[i + 1])) << 8) +
                         (((unsigned int)HexSymbolToChar(s[i + 2])) << 4) +
                         ((unsigned int)HexSymbolToChar(s[i + 3]));
    if (code <= 0x7F) {                               // Теперь в соответствии с количеством байт формируем символ
      c[0] = (char)code;
      c[1] = 0;                                       // Не забываем про завершающий ноль
    } else if (code <= 0x7FF) {
      c[0] = (char)(0xC0 | (code >> 6));
      c[1] = (char)(0x80 | (code & 0x3F));
      c[2] = 0;
    } else if (code <= 0xFFFF) {
      c[0] = (char)(0xE0 | (code >> 12));
      c[1] = (char)(0x80 | ((code >> 6) & 0x3F));
      c[2] = (char)(0x80 | (code & 0x3F));
      c[3] = 0;
    } else if (code <= 0x1FFFFF) {
      c[0] = (char)(0xE0 | (code >> 18));
      c[1] = (char)(0xE0 | ((code >> 12) & 0x3F));
      c[2] = (char)(0x80 | ((code >> 6) & 0x3F));
      c[3] = (char)(0x80 | (code & 0x3F));
      c[4] = 0;

		}
		// Serial.print(">>>>> *c =  "); Serial.println((char*)c);
		strcat(result, (char*)c);
		//result += String((char*)c);                       // Добавляем полученный символ к результату
    //result += String((char)*c);                       // Добавляем полученный символ к результату
  }
	// Serial.print(">>>>> UCS2ToString = "); Serial.println(result);
	// Debug.print(">>>>> UCS2ToString = "); Debug.println(result);
  strcat(_Bufer,result);
  // _Debug -> print("UCS2ToString>>"), _Debug -> print(_Bufer), _Debug -> println("<<UCS2ToString");
  // return result;
}

unsigned char GSM_Un::HexSymbolToChar(char c) {
  if      ((c >= 0x30) && (c <= 0x39)) return (c - 0x30);
  else if ((c >= 'A') && (c <= 'F'))   return (c - 'A' + 10);
  else                                 return (0);
}

// float getFloatFromString(String str) {            // Функция извлечения цифр из сообщения - для парсинга баланса из USSD-запроса
//   bool   flag     = false;
//   String result   = "";
//   str.replace(",", ".");                          // Если в качестве разделителя десятичных используется запятая - меняем её на точку.
//   for (int i = 0; i < str.length(); i++) {
//     if (isDigit(str[i]) || (str[i] == (char)46 && flag)) {        // Если начинается группа цифр (при этом, на точку без цифр не обращаем внимания),
//       if (result == "" && i > 0 && (String)str[i - 1] == "-") {   // Нельзя забывать, что баланс может быть отрицательным
//         result += "-";                            // Добавляем знак в начале
//       }
//       result += str[i];                           // начинаем собирать их вместе
//       if (!flag) flag = true;                     // Выставляем флаг, который указывает на то, что сборка числа началась.
//     }
//     else  {                                       // Если цифры закончились и флаг говорит о том, что сборка уже была,
//       if (str[i] != (char)32) {                   // Если порядок числа отделен пробелом - игнорируем его, иначе...
//         if (flag) break;                          // ...считаем, что все.
//       }
//     }
//   }
//   return result.toFloat();                        // Возвращаем полученное число.
// }

void GSM_Un::strcat_c (char *str, char c){
    for (;*str;str++); // note the terminating semicolon here.
    *str++ = c;
    *str++ = NULL;
  }

void GSM_Un::getBallansToChar(char *str, char * InChar) {            // Функция извлечения цифр из сообщения - для парсинга баланса из USSD-запроса
	//Debug.println(str);
  bool   flag     = false;
  char result[10] = "";
  char com[10] = "";
	// Debug.print(">>>>> str = "); Debug.println(str);
	// Serial.print(">>>>> str = "); Serial.println(str);
	int t = strspn(str, ",");
	while (t != 0) {
		str[t] = '.';
		t = strspn(str, ",");
	}
	// Debug.print(">>>>> str = "); Debug.println(str);
	// Serial.print(">>>>> str = "); Serial.println(str);



  for (int i = 0; i < strlen(str); i++) {
    if (isdigit(str[i]) || (str[i] == (char)46 && flag)) {        // Если начинается группа цифр (при этом, на точку без цифр не обращаем внимания),
      if ((strcmp(result, "") == 0) && i > 0 && str[i - 1] == (char)45) {   // Нельзя забывать, что баланс может быть отрицательным
        strcat(result, "-");                            // Добавляем знак в начале
      }
			strcat_c(result, str[i]);
			// Debug.print(">>>>> res = "); Debug.println(result);

			if (!flag) flag = true;                     // Выставляем флаг, который указывает на то, что сборка числа началась.
    }
    else  {                                       // Если цифры закончились и флаг говорит о том, что сборка уже была,
      if (str[i] != (char)32) {                   // Если порядок числа отделен пробелом - игнорируем его, иначе...
        if (flag) break;                          // ...считаем, что все.
      }
    }
  }
	//Debug.print(">>>>> "); Debug.println(result);
	// Serial.print(">>>>> "); Serial.println(result);
	dtostrf(atof(result), 7, 2, com);

	trim(com);
  // _Debug -> print(">>COM>>"), _Debug -> println(com);

  // strcat(InChar, com);
  clear_char(InChar);
  // memcpy(InChar, com, strlen(com));
  strcat(InChar, com);
  // _Debug -> print(">>getBallansToChar>>"), _Debug -> println(InChar);
  // Serial.print(">>>>> "); Serial.println(InChar);
}

void GSM_Un::trim(char *s) {
     // удаляем пробелы и табы с начала строки:
     int i=0,j;
     while((s[i]==' ')||(s[i]=='\t')) {
         i++;
     }
     if(i>0) {
        for(j=0; j < strlen(s); j++) {
           s[j]=s[j+i];
        }
        s[j]='\0';
     }

     // удаляем пробелы и табы с конца строки:
     i=strlen(s)-1;
     while((s[i]==' ')||(s[i]=='\t'))
     {
          i--;
     }
     if(i < (strlen(s)-1))
     {
          s[i+1]='\0';
     }
}

// // #ifdef BEELINE
// // #define USSD_Ballans  "*102#"
// #define USSD_Ballans  "*102#"
// // #endif
// // #ifdef MEGAFON
// #define USSD_Ballans  "*100#"
// #endif
// #ifdef TELE2
// #define USSD_Ballans  "*105#"
// #endif


// #define MTS  "*105#"
