#include <stdio.h>
#include <stdlib.h>
#include <hidapi/hidapi.h>
#include <string.h>
#include <stdint.h>

#define PACKET_SIZE 16

hid_device *dev_hndl;

void at_exit(void) {
    hid_close(dev_hndl);
    hid_exit();
}

int main() {
    uint8_t raport_id;
    uint8_t buf[PACKET_SIZE + 1] = {0};

    int res = hid_init();
    dev_hndl = hid_open(0x1b4f, 0x9206, NULL);

    if(dev_hndl == NULL) {
        printf("Connection failed\n");
        exit(1);
    }

    atexit(at_exit);

    buf[0] = 0x0;
    buf[1] = 0x81;
    res = hid_write(dev_hndl, (unsigned char*)buf, PACKET_SIZE + 1);

    while(1) {
        //hid_read(dev_hndl, &raport_id, 1);
        hid_read(dev_hndl, (unsigned char*)buf, PACKET_SIZE + 1);
        
        printf("%02x [", buf[0]);
        for(int i = 1; i < PACKET_SIZE + 1; i++) {
            printf("%02x", buf[i]);
            if(i != PACKET_SIZE) putchar(' ');
        }
        puts("]");
    }

    at_exit();
}
