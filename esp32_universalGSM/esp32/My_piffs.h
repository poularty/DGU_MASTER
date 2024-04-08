 #include <SPIFFS.h>

void CheckSpiffs(){
   if(!SPIFFS.begin(true)){
       Serial.println("An Error has occurred while mounting SPIFFS");
       return;
   }
}

bool createFile(char* NameFile){
  File file = SPIFFS.open(NameFile, "w");
    if(!file){
      Serial.println("Failed to open file for reading");
      return false;
    }
  file.close();
  return true;
}

bool OpenFileRead(char* NameFile){
  File file = SPIFFS.open(NameFile, "r");
    if(!file){
      Serial.println("Failed to open file for reading");
      return false;
    }
  Serial.println(">>> Start file:");
  while (file.available()) { Serial.write(file.read());}
  Serial.println("<<< end file");
  file.close();
  return true;
}

bool check_file(char* NameFile){
  char result[200] = "";
  File File = SPIFFS.open(NameFile, "r");
  if(!File){
    Serial.println("Failed to open file for reading");
    return false;
  }
  if(File.available()){
    File.readBytes(result, 200);
    Serial.println("Read from file:");
  }
  Serial.println(result);
  File.close();
  if (strlen(result) > 2) {
    Serial.println("File not empty");
    return true;
  }
  return false;
}

void add_line_to_start_file(char* line, char* NameFile){
  File File2 = SPIFFS.open("/clone.txt", "w+");
  if (!File2) {Serial.println("Failed to open file"); return;}
  File2.println(line);
  File File1 = SPIFFS.open("/test1.txt", "r");
  if (!File1) {Serial.println("Failed to open file for reading"); return;}
  while (File1.available()) { File2.write(File1.read());}
  File1.close();
  File2.close();
  File1 = SPIFFS.open("/test1.txt", "w+");
  if (!File1) {Serial.println("Failed to open file"); return;}
  File2 = SPIFFS.open("/clone.txt", "r");
  if (!File2) {Serial.println("Failed to open file for reading"); return;}
  while (File2.available()) {File1.write(File2.read());}
  File1.close();
  File2.close();
}

void add_line_to_end_file(char* line, char* NameFile){
  File File = SPIFFS.open(NameFile, "a");
  if (!File) {Serial.println("Failed to open file"); return;}
  File.println(line);
  File.close();
}

void read_line_from_start_file(char* NameFile){
  File File1 = SPIFFS.open(NameFile);
  if (!File1){ Serial.println("Failed to open file for reading"); return;}
}
