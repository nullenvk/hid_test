// Tested on Sparkfun Micro Pro

#include <Wire.h>
#include <HID.h>

const int INIT_DELAY_MS = 1000;

// Descriptor made by okawo80085, I was too lazy to setup WINE for the official HID tool
static const uint8_t USB_HID_Descriptor[] PROGMEM = {
  0x06, 0x03, 0x00,   // USAGE_PAGE (vendor defined)
  0x09, 0x00,         // USAGE (Undefined)
  0xa1, 0x01,         // COLLECTION (Application)
  0x15, 0x00,         //   LOGICAL_MINIMUM (0)
  0x26, 0xff, 0x00,   //   LOGICAL_MAXIMUM (255)
  0x85, 0x01,         //   REPORT_ID (1)
  0x75, 0x08,         //   REPORT_SIZE (16)

  0x95, 0x3f,         //   REPORT_COUNT (1)

  0x09, 0x00,         //   USAGE (Undefined)
  0x81, 0x02,         //   INPUT (Data,Var,Abs) - to the host
  0xc0
};

void setup() {
  static HIDSubDescriptor node(USB_HID_Descriptor, sizeof(USB_HID_Descriptor));
  HID().AppendDescriptor(&node);
  
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  delay(INIT_DELAY_MS);
  Serial.println("OK");
}

void loop() {
  unsigned char data[16] = {
     1, 2, 3, 4,
     5, 6, 7, 8,
     9,10,11,12,
    13,14,15,16
  };
  HID().SendReport(1,data,16);
  delay(1000);
}
