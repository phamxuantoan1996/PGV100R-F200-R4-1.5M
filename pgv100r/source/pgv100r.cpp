// #include <iostream>
// #include <fcntl.h>      // open
// #include <termios.h>    // termios, tcgetattr, tcsetattr
// #include <unistd.h>     // read, write, close
// #include <cstring>      // memset
// #include <cstdio>       // printf
// using namespace std;

// uint8_t calculateCRC(uint8_t *buffer)
// {
//     uint8_t crc = 0;

//     for(uint8_t i = 0; i < 20; i++)
//     {
//         crc ^= buffer[i];
//     }

//     return crc;
// }

// uint64_t decodeResponse(uint8_t *buffer)
// {
//     uint64_t response = 0;
//     //byte8 - byte9 , byte 12 - 17
//     response = (buffer[8] << 49) | (buffer[9] << 42) | (buffer[12] << 35) | (buffer[13] << 28) 
//                 | (buffer[14] << 21) | (buffer[15] << 14) | (buffer[16] << 7) | (buffer[17] << 0);

//     return response;
// }

// int main() {
//     const char *port = "/dev/ttyUSB0";   // change to your device
//     int baudrate = B115200;

//     // 1. Open serial port
//     int serial_port = open(port, O_RDWR | O_NOCTTY);
//     if (serial_port < 0) {
//         perror("Error opening serial port");
//         return 1;
//     }

//     // 2. Get current settings
//     struct termios tty{};
//     if (tcgetattr(serial_port, &tty) != 0) {
//         perror("tcgetattr failed");
//         close(serial_port);
//         return 1;
//     }

//     // 3. Set baud rate
//     cfsetospeed(&tty, baudrate);
//     cfsetispeed(&tty, baudrate);

//     // 4. Configure 8-E-1
//     tty.c_cflag &= ~CSIZE;
//     tty.c_cflag |= CS8;          // 8 data bits
//     tty.c_cflag |= PARENB;       // enable even parity
//     tty.c_cflag &= ~PARODD;      
//     tty.c_cflag &= ~CSTOPB;      // 1 stop bit
//     tty.c_cflag &= ~CRTSCTS;     // no flow control
//     tty.c_cflag |= CREAD | CLOCAL;

//     // 5. Input flags
//     tty.c_iflag |= INPCK;        // enable parity checking
//     tty.c_iflag &= ~IGNPAR;      // don't ignore parity errors
//     tty.c_iflag &= ~ISTRIP;      // keep all 8 bits
//     tty.c_iflag &= ~(IXON | IXOFF | IXANY); // no software flow control

//     // 6. Raw mode (no echo, no canonical)
//     tty.c_lflag = 0;
//     tty.c_oflag = 0;

//     // --- Timeout setup ---
//     // VTIME = 50 => timeout 5s (0.1s x 50)
//     tty.c_cc[VMIN]  = 0;   // return even if no byte
//     tty.c_cc[VTIME] = 20;  // timeout = 5 seconds

//     tcflush(serial_port, TCIFLUSH);

//     // Apply settings
//     if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
//         perror("tcsetattr failed");
//         close(serial_port);
//         return 1;
//     }

//     cout << "Serial port configured as 8-E-1, baud 115200" << endl;

//     // 7. Send data (no newline)
//     for(int i = 0; i < 1; i++)
//     {
//         uint8_t message[] = { 0xc8,0x37};
//         ssize_t sent = write(serial_port, message, sizeof(message));
//         if (sent > 0)
//             cout << "Sent " << sent << " bytes." << endl;
//         else
//             perror("Write failed");

//         // 8. Wait and receive data
//         uint8_t buffer[256];
//         cout << "Waiting for data (timeout 5s)..." << endl;

//         ssize_t num_of_byte = read(serial_port, buffer, sizeof(buffer));
//         if (num_of_byte > 0) 
//         {
//             cout << "Received " << num_of_byte << " bytes: ";
//             for (int i = 0; i < num_of_byte; i++)
//                 printf("%02X ", buffer[i]);
            
//             printf("\ncrc calculate : %02X \n",calculateCRC(buffer));
//             printf("value : %ld",decodeResponse(buffer));
//             cout << endl;
//             // Decode data
            
//         } 
//         else if (num_of_byte == 0) 
//         {
//             cout << "Timeout: no data received within 5 seconds." << endl;
//         } else {
//             perror("Read failed");
//         }

//     }
    
//     close(serial_port);
//     return 0;
// }

#include <pgv100r.h>

pgv100r::pgv100r(string port_serial,uint32_t baudrate)
{
    this->port_serial = port_serial;
    this->baudrate = baudrate;
    this->datamatrix = 0;
}


pgv100r::~pgv100r()
{
}
