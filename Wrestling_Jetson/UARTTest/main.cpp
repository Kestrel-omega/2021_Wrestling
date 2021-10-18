#include <stdio.h>
#include <iostream>
#include <vector>
#include "uart.h"
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
  Uart u;
  unsigned char m[SIZE_STRING];
  m[0]= (unsigned char) '-';
  m[1]= (unsigned char) '1';
  m[2]= (unsigned char) ',';
  m[3]= (unsigned char) '2';
  m[4]= (unsigned char) '5';
  m[5]= (unsigned char) '7';
  m[6]= (unsigned char) ',';  
  m[7]= (unsigned char) '0';
  m[8]= (unsigned char) '3';
  m[9]= (unsigned char) '9';
  m[10]= (unsigned char) ',';
  m[11]= (unsigned char) '6';
  m[12]= (unsigned char) '4';
  m[13]= (unsigned char) '1';
  m[14]= (unsigned char) ',';
  m[15]= (unsigned char) '-';
  m[16]= (unsigned char) '2';
  m[17]= (unsigned char) '\n';


  // m[0]= 1;
  // m[1]= 2;
  // m[2]= 4;
  // m[3]= 8;
  // m[4]= 16;
  // m[5]= 32;
  // m[6]= 64;
  // m[7]= 128;

  while (1) {
    u.sendUart(m);
    printf("send : %s\r\n", m);

    usleep(1000);
  }
  return 0;
}