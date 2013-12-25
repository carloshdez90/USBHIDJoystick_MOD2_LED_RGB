//HD44780 compatible LCD display via MAX3421E GPOUT support header
//pinout: D[4-7] -> GPOUT[4-7], RS-> GPOUT[2], E ->GPOUT[3]
//Los PWM 10 u 11 son usados por la placa y no funcionan.
//
#include <avr/pgmspace.h>
#include <SPI.h>


#include <avrpins.h>
#include <max3421e.h>
#include <usbhost.h>
#include <usb_ch9.h>
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <address.h>
#include <hid.h>
#include <hiduniversal.h>

#include "hidjoystickrptparser.h"

#include <printhex.h>
#include <message.h>
#include <hexdump.h>
#include <parsetools.h>

#include <max_LCD.h>


USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
JoystickEvents                                  JoyEvents;
JoystickReportParser                            Joy(&JoyEvents);

Max_LCD LCD(&Usb);

int led1 = 5;
int led2 = 6;
int led3 = 9;
int valor = 0;
int aux = 0;
char str[50];

void setup()
{
  LCD.begin(16, 2);
  LCD.home();
  LCD.Print("Inicializando ...");
  delay(2000);
  LCD.clear();
  LCD.home();
  LCD.Print("Joystick USB:");
  LCD.setCursor(0,1);
  LCD.Print("Capturando valores");
  delay(1000);
  LCD.clear();
  LCD.home();  
  Serial.begin( 115200 );
  Serial.println("Start");

  if (Usb.Init() == -1)
      Serial.println("OSC did not start.");
      
  delay( 200 );

  if (!Hid.SetReportParser(0, &Joy))
      ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  ); 
      
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop()
{
    
    Usb.Task();
    analogWrite(led1, (255-JoyEvents.valorX));    
    analogWrite(led2, (255-JoyEvents.valorY)); 
    analogWrite(led3, (255-JoyEvents.valorZ2)); 
    //Serial.println(valor);
    
    LCD.clear();
    LCD.home();
    LCD.Print("LED1:");
    LCD.Print(itoa(JoyEvents.valorX, str, 10));
    LCD.Print("LED2:");
    LCD.Print(itoa(JoyEvents.valorY, str, 10));
    LCD.setCursor(0,1);
    LCD.Print("LED3:");
    LCD.Print(itoa(JoyEvents.valorZ2, str, 10));
    
    delay(30);
 
}
