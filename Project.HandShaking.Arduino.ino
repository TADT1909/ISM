//Project.HandShaking.Arduino.ino
/*Used some libraries and functions of C/C++ language:
  string.h  stdio.h stdlib.h
  strtok()  https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
  atof()    https://www.tutorialspoint.com/c_standard_library/c_function_atof.htm
*/
/*
*05.02.2017 - 3:50 pm
 *split STRING with delimiter SUCCESSFULLY
 *convert string splited to FLOAT SUCCESSFULLY
 INPUT: A1&22&333&4444&55555&666666&7777777&88888888Z
 OUTPUT:
  Float 0 is: 1.00
  Float 1 is: 22.00
  Float 2 is: 333.00
  Float 3 is: 4444.00
  Float 4 is: 55555.00
  Float 5 is: 666666.00
  Float 6 is: 7777777.00
  Float 7 is: 88888888.00
 -------------------------------------------
 *04.02.2017
 Try to fixing
 But not success
 -------------------------------------------
 *03.02.2017 - 8:40 pm
 *COMPLETE handshaking read unlimited serial data with HEADER and FOOTER
 *still have to fix the decode()
 -------------------------------------------
 *03.02.2017 - 5:00 pm
 *read code with delimiter
 *have bugs can resent data received
 -------------------------------------------
 * 02.02.2017
 * first handshaking
 * Just read int code not float
 * Still has some bugs
 * Can't fix now
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// variables for storing serial data
char val;
byte size;
char header = 'A';
char footer = 'Z';
char input[50];
byte n = 0, serialLength = 0;

// variables for decoding

// char *stringArray[30];
float floatArray[50];
byte i = 0, length = 0, floatAmount = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  establishContact();
  if (Serial.available() > 0) //Read code sent from Serial port
  {
    val = Serial.read();
    if (val == header)
    {
      val = Serial.read();
      if ((val != header) and (val != footer))
      {
        storeSerialData();
      }
      if (val == footer)
      {
        decode();
        sendData();
        resetRecievedData();
      }
      if (val == header)
      {
        resetRecievedData();
      }
    }
  }
}
void storeSerialData()
{
  while ((val != header) and (val != footer))
  {
    //store Serial data
    input[n] = val;
    n++;
    serialLength = n;
    //read new Serial data
    val = Serial.read();
    /*
    the order of lines is important
    CAN'T place
      val = Serial.read();
    before
      input[n] = val;
    */
  }
}

void decode()
{
  size = strlen(input); // caculate size of input
  input[size + 1] = 0;

  int size = strlen(input);
  input[size + 1] = 0;
  char *command = strtok(input, "&"); //pointer
  while ((command != 0) && (command != NULL))//while command isn't all splited to tokens
  {
    // stringArray[i] = command;

    // Convert input string to float
    floatArray[i] = atof(command);
    // sscanf(command, "%i" , &floatArray[i]);
    // Find the next command in input string
    command = strtok(0, "&");
    i++;
    length = i;
    if (command == NULL)
    {
      i = 0;
      break;
    }
  }
}
void sendData()
{
  // Serial.print("Recieved input:");   Serial.println(input);
  // Serial.print("Size of input:");   Serial.println(size);
  for (byte i = 0; i < length; i++)
  {
    Serial.print("Float code ");       Serial.print(i); Serial.print(" is: ");
    Serial.println(floatArray[i]);
    // Serial.print("String ");       Serial.print(i); Serial.print(" is: ");
    // Serial.println(stringArray[i]);
  }
}
/*-----------------------------------------------*/
void resetRecievedData()
{
//reset all recieved data to 0
  for (byte i = 0; i < serialLength; i++)
  {
    input[i] = 0;
    floatArray[i] = 0;
  }
  n = 0;
  serialLength = 0;
  i = 0;
  length = 0;
}
void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("A");   // send a capital A
    delay(300);
  }
}
