#ifndef _PGV100R_H
#define _PGV100R_H
#include <iostream>
#include <fcntl.h>      // open
#include <termios.h>    // termios, tcgetattr, tcsetattr
#include <unistd.h>     // read, write, close
#include <cstring>      // memset
#include <cstdio>       // printf
#include <string>
using namespace std;

class pgv100r
{
private:
    /* data */
    string port_serial;
    uint32_t baudrate;
    int serial_port;
    uint64_t datamatrix;

    bool connectToPVG(void);
    uint8_t calculateCRC(uint8_t *buffer);
    uint64_t decodeResponse(uint8_t *buffer);
    
public:
    pgv100r(string port_serial,uint32_t baudrate);
    ~pgv100r();
    bool readDataMatrix();
};
#endif