 #include <FS.h>
 // #include <SPIFFS.h>
 // #include <WiFi.h>
 #include <WebServer.h>

 IPAddress apIP(192, 168, 5, 1);

 const byte relay = 4;                                                   // Пин подключения сигнального контакта реле
 const char *ssid = "SweetHome";                                             // Название генерируемой точки доступа
 const char *password = "27061984"; // Для хранения пароля сети
 const char *ssidAP = "WiFi";   // SSID AP точки доступа
 const char *passwordAP = "27061984"; // пароль точки доступа

 WebServer HTTP(80);                                              // Определяем объект и порт сервера для работы с HTTP
 // FtpServer ftpSrv;                                                       // Определяем объект для работы с модулем по FTP (для отладки HTML)

 void WIFIinit();
 bool StartAPMode();
 void input_id();
 void input_gsm();
 void input_gsm_handle();
 void input_locate();
 void input_type();
 void input_typeGSM();
 void input_resetGSM();

 bool handleFileRead(String path);

 void reconfig (char file_config, int num_line, char set_line);
 String Send_HTML_config();


// Инициализируем Web-сервер
void HTTP_on(){
  HTTP.begin();                                          // Инициализируем Web-сервер

  HTTP.on("/input-id", input_id);
  HTTP.on("/input_gsm", input_gsm);
  HTTP.on("/input_gsm_handle", input_gsm_handle);
  HTTP.on("/input-locate", input_locate);
  HTTP.on("/input-type", input_type);
  HTTP.on("/input-typeGSM", input_typeGSM);
  HTTP.on("/input-resetGSM", input_resetGSM);

  HTTP.onNotFound([](){                                 // Описываем действия при событии "Не найдено"
  if(!handleFileRead(HTTP.uri()))                       // Если функция handleFileRead (описана ниже) возвращает значение false в ответ на поиск файла в файловой системе
      HTTP.send(404, "text/plain", "Not Found");       // возвращаем на запрос текстовое сообщение "File isn't found" с кодом 404 (не найдено)
  });
}


 void reconfig(char* file_config, int num_line, char* set_line) {			// функция изменения файла конфигурации


 	char buf[500] = {};													// буфер для хранения всего файла
 	char s[50] = {};													// буфер для хранения одной строки

 	File f = SPIFFS.open(file_config, "r");								// открываем файл для чтения

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
  // просто прочитываем файл, в постоянном варианте стоит убрать
  // while(f.available()) {
  //   Serial.print(f.readString());
  // }
  // f.close();
  //
  // f = SPIFFS.open(file_config, "r");								// открываем файл для чтения

  for (int i = 0; i <= num_line - 1; i++){
 		int l = f.readBytesUntil('\n', s, 100);							// считываем по строчно
 		strncat( buf, s, l);
 		buf[strlen(buf)] = '\n';											// добавляем строки в основной буфер
 	}


  char line[100] = "";
  f.readBytesUntil('\n', line, 100);
  // Serial.print("line = "), Serial.println(line);
  int EndLine = strchr(line, '\"') - line + 1;
  // Serial.print("EndLine = "), Serial.println(EndLine);

  // line[EndLine] = NULL;
  char line2[100] = "";
  memmove(line2, line, EndLine);
  strcat(line2, set_line);
  strcat(line2, "\";");
  line2[strlen(line2)] = '\n';
  // Serial.print("line2 = "), Serial.println(line2);

 	strcat(buf, line2);												// заменяем строку нужным параметром
 	// buf[strlen(buf)] = '\n';											// добавляем конец строки
 	// f.readBytesUntil('\n', line, 100);

  memset(s, 50, NULL);
 	while(f.available()){												// считываем файл до конца в буфер
 		int l = f.readBytesUntil('\n', s, 100);
 		strncat( buf, s, l);
 		buf[strlen(buf)] = '\n';
 	}

 	f.close();

 	f = SPIFFS.open(file_config, "w");										// записывем буфер в файл
 	f.print(buf);
 	f.close();

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
  // просто прочитываем файл, в постоянном варианте стоит убрать
  f = SPIFFS.open(file_config, "r");								// открываем файл для чтения
  while(f.available()) {
    Serial.print(f.readString());
  }
  f.close();


 }

 char buf_var[100] = "";

 char* args_to_arr(String args_input){
   strcpy(buf_var, args_input.c_str());
   return buf_var;
 }

 char* arrarg_to_arg(char* arr, char* separ){
   char* buf_args[10];
   char *istr;
   istr = strtok(arr, separ);
   int n = 0;
     while (istr != NULL){
       istr = strtok(NULL, separ);
       buf_args[n] = istr;
       Serial.println(buf_args[n]);
       n++;
     }
   //Serial.println(buf_args);
   return(*buf_args);
   }

 void input_id() {
     // HTTP.send(200, "text/plain", "OK");
     Serial.print(HTTP.argName(0)), Serial.print(" = "), Serial.println(HTTP.arg(0));
     Serial.print(HTTP.argName(1)), Serial.print(" = "), Serial.println(HTTP.arg(1));
     Serial.print(HTTP.argName(2)), Serial.print(" = "), Serial.println(HTTP.arg(2));

     reconfig("/1.txt", 0, args_to_arr(HTTP.arg(0)));
     reconfig("/1.txt", 1, args_to_arr(HTTP.arg(1)));
     reconfig("/1.txt", 2, args_to_arr(HTTP.arg(2)));

     handleFileRead("/");
     delay(2000);
     ESP.restart();
 }

 void input_gsm() {
    Serial.print(HTTP.argName(0)), Serial.print(" = "), Serial.println(HTTP.arg(0));

    char line_in[20] = "";
    strcat(line_in, args_to_arr(HTTP.arg(0)));
    char line_out[20] = "";
    char C_upper;
    for (int i = 0; i < strlen(line_in); i++){
      C_upper = toupper(line_in[i]);
      line_out[i] = C_upper;
    }
    reconfig("/1.txt", 3, line_out);

    handleFileRead("/");
    delay(2000);
    ESP.restart();
 }

 void input_gsm_handle() {
   // HTTP.send(200, "text/plain", "OK");

   Serial.print(HTTP.argName(0)), Serial.print(" = "), Serial.println(HTTP.arg(0));
   Serial.print(HTTP.argName(1)), Serial.print(" = "), Serial.println(HTTP.arg(1));
   Serial.print(HTTP.argName(2)), Serial.print(" = "), Serial.println(HTTP.arg(2));

   reconfig("/1.txt", 4, args_to_arr(HTTP.arg(0)));
   reconfig("/1.txt", 5, args_to_arr(HTTP.arg(1)));
   reconfig("/1.txt", 6, args_to_arr(HTTP.arg(2)));

   handleFileRead("/");
 }

 void input_locate() {
   Serial.print(HTTP.argName(0)), Serial.print(" = "), Serial.println(HTTP.arg(0));
   Serial.print(HTTP.argName(1)), Serial.print(" = "), Serial.println(HTTP.arg(1));
   Serial.print(HTTP.argName(2)), Serial.print(" = "), Serial.println(HTTP.arg(2));

   reconfig("/1.txt", 7, args_to_arr(HTTP.arg(0)));
   reconfig("/1.txt", 8, args_to_arr(HTTP.arg(1)));
   reconfig("/1.txt", 9, args_to_arr(HTTP.arg(2)));

   handleFileRead("/");
   // ESP.restart();
 }

 void input_type() {
   Serial.print(HTTP.argName(0)), Serial.print(" = "), Serial.println(HTTP.arg(0));

   reconfig("/1.txt", 10, args_to_arr(HTTP.arg(0)));

   handleFileRead("/");
   ESP.restart();
 }

 void input_typeGSM() {
   Serial.print(HTTP.argName(0)), Serial.print(" = "), Serial.println(HTTP.arg(0));

   reconfig("/1.txt", 11, args_to_arr(HTTP.arg(0)));

   handleFileRead("/");
 }

 void input_resetGSM() {
   Serial.print(HTTP.argName(0)), Serial.print(" = "), Serial.println(HTTP.arg(0));

   reconfig("/1.txt", 12, args_to_arr(HTTP.arg(0)));

   handleFileRead(HTTP.uri());
   ESP.restart();
 }

 String relay_switch() {                                                 // Функция переключения реле
   byte state;
   if (digitalRead(relay))                                               // Если на пине реле высокий уровень
     state = 0;                                                          //  то запоминаем, что его надо поменять на низкий
   else                                                                  // иначе
     state = 1;                                                          //  запоминаем, что надо поменять на высокий
   digitalWrite(relay, state);                                           // меняем значение на пине подключения реле
   return String(state);                                                 // возвращаем результат, преобразовав число в строку
 }

 String relay_status() {                                                 // Функция для определения текущего статуса реле
   byte state;
   if (digitalRead(relay))                                               // Если на пине реле высокий уровень
     state = 1;                                                          //  то запоминаем его как единицу
   else                                                                  // иначе
     state = 0;                                                          //  запоминаем его как ноль
   return String(state);                                                 // возвращаем результат, преобразовав число в строку
 }

 String getContentType(String filename){                                 // Функция, возвращающая необходимый заголовок типа содержимого в зависимости от расширения файла
   if (filename.endsWith(".html")) return "text/html";                   // Если файл заканчивается на ".html", то возвращаем заголовок "text/html" и завершаем выполнение функции
   else if (filename.endsWith(".css")) return "text/css";                // Если файл заканчивается на ".css", то возвращаем заголовок "text/css" и завершаем выполнение функции
   else if (filename.endsWith(".js")) return "application/javascript";   // Если файл заканчивается на ".js", то возвращаем заголовок "application/javascript" и завершаем выполнение функции
   else if (filename.endsWith(".png")) return "image/png";               // Если файл заканчивается на ".png", то возвращаем заголовок "image/png" и завершаем выполнение функции
   else if (filename.endsWith(".jpg")) return "image/jpeg";              // Если файл заканчивается на ".jpg", то возвращаем заголовок "image/jpg" и завершаем выполнение функции
   else if (filename.endsWith(".gif")) return "image/gif";               // Если файл заканчивается на ".gif", то возвращаем заголовок "image/gif" и завершаем выполнение функции
   else if (filename.endsWith(".ico")) return "image/x-icon";            // Если файл заканчивается на ".ico", то возвращаем заголовок "image/x-icon" и завершаем выполнение функции
   return "text/plain";                                                  // Если ни один из типов файла не совпал, то считаем что содержимое файла текстовое, отдаем соответствующий заголовок и завершаем выполнение функции
 }

 bool handleFileRead(String path){                                       // Функция работы с файловой системой
   if(path.endsWith("/")) path += "index.html";                          // Если устройство вызывается по корневому адресу, то должен вызываться файл index.html (добавляем его в конец адреса)
   String contentType = getContentType(path);                            // С помощью функции getContentType (описана ниже) определяем по типу файла (в адресе обращения) какой заголовок необходимо возвращать по его вызову
   if(SPIFFS.exists(path)){                                              // Если в файловой системе существует файл по адресу обращения
     File file = SPIFFS.open(path, "r");                                 //  Открываем файл для чтения
     size_t sent = HTTP.streamFile(file, contentType);                   //  Выводим содержимое файла по HTTP, указывая заголовок типа содержимого contentType
     file.close();                                                       //  Закрываем файл
     return true;                                                        //  Завершаем выполнение функции, возвращая результатом ее исполнения true (истина)
   }
   return false;                                                         // Завершаем выполнение функции, возвращая результатом ее исполнения false (если не обработалось предыдущее условие)
 }



 void WIFIinit() {
   // Попытка подключения к точке доступа
   WiFi.mode(WIFI_STA);
   byte tries = 11;
   WiFi.begin(ssid, password);
   while (--tries && WiFi.status() != WL_CONNECTED)
   {
     Serial.print(".");
     delay(1000);
   }
   if (WiFi.status() != WL_CONNECTED)
   {
     // Если не удалось подключиться запускаем в режиме AP
     Serial.println("");
     Serial.println("WiFi up AP");
     StartAPMode();
   }
   else {
     Serial.println("");
     Serial.println("WiFi connected");
     Serial.println("IP address: ");
     Serial.println(WiFi.localIP());
   }
 }

 bool StartAPMode() {
   WiFi.disconnect();
   WiFi.mode(WIFI_AP);
   WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
   WiFi.softAP(ssidAP, passwordAP);
   return true;
 }
