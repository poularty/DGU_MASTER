#ifndef modbus_my_h
#define modbus_my_h

#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include <ModbusMaster.h>
#include <Arduino.h>
#include <bitset>
#include "smartgen.h"

class ModbusDGU {

  ModbusMaster DGU;

public:
  ModbusDGU(int ModbusAdress, Stream &Ser_DGU, Stream &Debug){
    _Ser_DGU = &Ser_DGU;
    _Debug = &Debug;
    _ModbusAdress = ModbusAdress;
    DGU.begin(_ModbusAdress, *_Ser_DGU);
    // DGU.ku8MaxBufferSize = 128;
  }

// чтение регистра по указанному адресу на заданую гдубину
  void Read_register(int Register, int Quanty){
    uint8_t j, result;
  	uint16_t data[Quanty];
    char char_data[50] = "";

    result = DGU.readHoldingRegisters(Register, Quanty);
      if (result == DGU.ku8MBSuccess) {
        for ( int i = 0; i < Quanty; i++){
          data[i] = DGU.getResponseBuffer(i);
          itoa(data[i], char_data, 10);
          _Debug -> print(i + Register), _Debug -> print(" "), _Debug -> println(char_data);
          memset(char_data, NULL, sizeof(char_data));
			}
      _Debug -> println();
    }
  }

// чтение регистров по указанному адресу на заданую глубину
// и сохранение данных в глобальный массив _RegisterArray[i]
  void Read_register_to_Array(int Register, int Quanty){
    uint8_t j, result;
    char char_data[50] = "";

    result = DGU.readHoldingRegisters(Register, Quanty);
      if (result == DGU.ku8MBSuccess) {
        for ( int i = 0; i < Quanty; i++){
          _RegisterArray[i] = DGU.getResponseBuffer(i);
          itoa(_RegisterArray[i], char_data, 10);
          // _Debug -> print(i + Register), _Debug -> print(" "), _Debug -> println(char_data);
          // memset(char_data, NULL, sizeof(char_data));
      }
      // _Debug -> println();
    }
  }

  // чтение коилс по указанному адресу на заданую глубину
  // и сохранение данных в глобальный массив _CoilsArray[i]
  void Read_coils_to_Array(int Coil, int Quanty){
    uint16_t result;
    char char_data[50] = "";

    DGU.clearResponseBuffer();
    memset(_CoilsArray, NULL, sizeof(_CoilsArray));

    result = DGU.readCoils(Coil, Quanty);
      if (result == DGU.ku8MBSuccess) {
        for ( int i = 0; i < 6; i++){
          _CoilsArray[i] = DGU.getResponseBuffer(i);
          itoa(_CoilsArray[i], char_data, BIN);
          // _Debug -> print(i), _Debug -> print(" "), _Debug -> println(char_data);
          // memset(char_data, NULL, sizeof(char_data));
      }
      // uint16_t n = _CoilsArray[0];
      // _Debug -> print("Bit = "), _Debug -> println((n >> 8) & 1u);
      // _Debug -> print("Bit = "), _Debug -> println((n >> 2) & 1u);
      // _Debug -> print("Bit = "), _Debug -> println((n >> 3) & 1u);
    }
  }


  // возвращает значение конкретного коилс в диавпазоне (0-81 (или больше))
   // в формате 0 или 1 (bool)
  bool check_coil(uint16_t coil){
    uint8_t num_byte = coil/16;
    uint8_t num_bit  = coil - num_byte*16;
    bool state = (_CoilsArray[num_byte] >> num_bit) & 1u;
    return state;
  }

  // проверка конкретного коилс в диавпазоне (0-81 (или больше))
   // и возвращает его значение bool
  bool check_coil_change(uint16_t coil){
    uint8_t num_byte = coil/16;
    uint8_t num_bit  = coil - num_byte*16;
    bool state = (_CoilsArray[num_byte] >> num_bit) & 1u;

    // _Debug -> print(coil); _Debug -> print(" = ");
    // _Debug -> print(state);
    bool state_last = (_CoilsArray_last[num_byte] >> num_bit) & 1u;
    // _Debug -> println(state_last);
    if (state != state_last) return true;
    return false;
  }

  bool check_coils_change(){
    uint8_t num_byte;
    uint8_t num_bit;
    for (int i = 0; i < 80; i++){
      num_byte = i/16;
      num_bit  = i - num_byte*16;
      bool state = (_CoilsArray[num_byte] >> num_bit) & 1u;
      bool state_last = (_CoilsArray_last[num_byte] >> num_bit) & 1u;
      if (state != state_last) return true;
    }
    return false;
  }

  bool check_coil_changeSet(uint16_t coil){
    if (check_coil_change(coil) && check_coil(coil)) {
      return true;
    }
    return false;
  }

  void write_singlCoil(uint16_t Coil, bool state){
    uint16_t result;
    result = DGU.writeSingleCoil(Coil, state);
    // _Debug -> println(DGU.getResponseBuffer(0));
    // _Debug -> println(DGU.getResponseBuffer(1));
  }

  // конверптиование данных регистров из глобального массива _RegisterArray
  // в (строку) глобальный char массив _BuferModB_reg с разделителем Ch (# )
  void reg_to_char(char* Ch, int calc, int count){
    char result[1000] = "";
    char word[50] = "";
    for ( int i = 0; i < count; i++){
      itoa( _RegisterArray[i], word, calc);
      strcat(result, word);
      // if (i = count - 1) { continue;}
      strcat(result, Ch);
      memset(word, NULL, sizeof(word));
    }
    _Debug -> println(result);
    _Debug -> println(strlen(result));
    memset(_BuferModB_reg, NULL, sizeof(_BuferModB_reg));
    strcat(_BuferModB_reg, result);
  }

  // конверптиование данных коилс из глобального массива _CoilsArray
  // в (строку) глобальный char массив _BuferModB_coils с разделителем Ch (# )
  void coils_to_char(char* Ch, int calc, int count){
    char result[1000] = "";
    char word[50] = "";
    for ( int i = 0; i < count; i++){
      itoa( _CoilsArray[i], word, calc);
      // _Debug -> println(word);

      strcat(result, word);
      strcat(result, Ch);
      memset(word, NULL, sizeof(word));
    }
    _Debug -> println(result);
    _Debug -> println(strlen(result));
    memset(_BuferModB_coils, NULL, sizeof(_BuferModB_coils));
    strcat(_BuferModB_coils, result);
  }

  void reg_to_char_ZIP(char* Ch, int calc, int count){
    char result[1000] = "";
    char word[50] = "";
    uint8_t doub = 1;
    char double_ch[10] = "";

    for ( int i = 0; i < count; i++){ //подсчитываем количество совпадений подряд
      if (_RegisterArray[i] == _RegisterArray[i + 1]){
          doub = doub + 1;
          // _Debug -> print(i), _Debug -> print(" = "), _Debug -> println(_RegisterArray[i]);
          // _Debug -> println(doub);
          continue;
      }
      if (_RegisterArray[i] != 0){ // Если значение не равно нулю
        itoa( _RegisterArray[i], word, calc); // То преобразуем значение в строку в массив word в системе исчисления calc
      }
      // _Debug -> print(i), _Debug -> print(" == "), _Debug -> println(_RegisterArray[i]);


      if (doub > 1){
        // _Debug -> println(doub);
        itoa(doub, double_ch, HEX);
        strcat(word, "|");
        strcat(word, double_ch);
        doub =  1;
        // _Debug -> println(word);
      }

      strcat(result, word);
      if ( i == (count - 1)) {continue;}
      strcat(result, Ch);
      memset(word, NULL, sizeof(word));
    }
    // _Debug -> println(result);
    // _Debug -> println(strlen(result));

    int n = 0;
    int i;

    for (int i = 0; i <= strlen(result); i++){
        if (result[i] == '#'){
          n++;
        }
    }
      // _Debug -> print("# = "), _Debug -> println(n);

      // if ((strlen(result)/8) < n){
      //   _Debug -> println("Start compress");
      //   char zip[500] = "";
      //   char ByteZip[50] ="";
      //   byte ZipByte = 0;
      //
      //   n = 0;
      //   int c = 0;
      //   for ( int i = 0; i < strlen(result); i++){
      //     if (result[i] == '#'){
      //       ZipByte |= 1<<n;
      //       _Debug -> print("1");
      //     }
      //     else _Debug -> print("0");
      //
      //     n++;
      //     if (n > 8) {
      //       n = 0;
      //       ByteZip[c] = (char)ZipByte;
      //       _Debug -> println((char)ZipByte);
      //       ZipByte = 0;
      //       c++;
      //     }
      //
      //
      //
      //   }
      //   _Debug -> println();
      //   _Debug -> println(ByteZip);
      //
      // }

    memset(_BuferModB_reg, NULL, sizeof(_BuferModB_reg));
    // _Debug -> println(result);
    strcat(_BuferModB_reg, result);
  }

  void coils_to_char_ZIP(char* Ch, int calc, int count){
    char result[1000] = "";
    char word[50] = "";
    uint8_t doub = 1;
    char double_ch[10] = "";

    for ( int i = 0; i < count; i++){
      if (_CoilsArray[i] == _CoilsArray[i + 1]){
          doub = doub + 1;
          // _Debug -> print(i), _Debug -> print(" = "), _Debug -> println(_RegisterArray[i]);
          // _Debug -> println(doub);
          continue;
      }
      if (_CoilsArray[i] != 0){
        itoa( _CoilsArray[i], word, calc);
      }
      // _Debug -> print(i), _Debug -> print(" == "), _Debug -> println(_RegisterArray[i]);


      if (doub > 1){
        itoa(doub, double_ch, HEX);
        strcat(word, "|");
        strcat(word, double_ch);
        doub =  1;
      }

      strcat(result, word);
      if ( i == (count - 1)) {continue;}
      strcat(result, Ch);
      memset(word, NULL, sizeof(word));
    }
    // _Debug -> println(result);
    // _Debug -> println(strlen(result));

    int n = 0;
    int i;

    for (int i = 0; i <= strlen(result); i++){
        if (result[i] == '#'){
          n++;
        }
    }
      // _Debug -> print("# = "), _Debug -> println(n);

      // if ((strlen(result)/8) < n){
      //   _Debug -> println("Start compress");
      //   char zip[500] = "";
      //   char ByteZip[50] ="";
      //   byte ZipByte = 0;
      //
      //   n = 0;
      //   int c = 0;
      //   for ( int i = 0; i < strlen(result); i++){
      //     if (result[i] == '#'){
      //       ZipByte |= 1<<n;
      //       _Debug -> print("1");
      //     }
      //     else _Debug -> print("0");
      //
      //     n++;
      //     if (n > 8) {
      //       n = 0;
      //       ByteZip[c] = (char)ZipByte;
      //       _Debug -> println((char)ZipByte);
      //       ZipByte = 0;
      //       c++;
      //     }
      //
      //
      //
      //   }
      //   _Debug -> println();
      //   _Debug -> println(ByteZip);
      //
      // }

    memset(_BuferModB_coils, NULL, sizeof(_BuferModB_coils));
  // _Debug -> println(result);
    strcat(_BuferModB_coils, result);
  }

// записываем все данные по модбаз из текущего массиво во второй чтобы
// потом можно было сравнить разницу
  void write_data_ta_last(){
    for (int i = 0; i < 128; i++){
      _RegisterArray_last[i] = _RegisterArray[i];
    }
    for (int i = 0; i < 6; i++){
      _CoilsArray_last[i] = _CoilsArray[i];
    }
  }


  char _BuferModB_reg[500] = "";
  char _BuferModB_coils[500] = "";

  uint16_t _RegisterArray[128];
private:

  uint16_t _RegisterArray_last[128];
  uint16_t _CoilsArray[6];
  uint16_t _CoilsArray_last[6];
  uint16_t _ModB;

  Stream* _Debug;
  Stream* _Ser_DGU;
  int _ModbusAdress;
};

#endif
// . https://waybyte.github.io/package_logicrom_index.json
