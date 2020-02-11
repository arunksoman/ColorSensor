#include <Arduino.h>
#include <TCS34725.h>

#define ACTIVATED LOW
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground
// set to false if using a common cathode LED
#define commonAnode true
// our RGB -> eye-recognized gamma color
byte gammatable[256];

My_TCS34725 tcs = My_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_60X);

bool ledEnabled=false;
int lightsMode=0;


void setup() {
  // put your setup code here, to run once:
   for (int i=0; i<256; i++) {
      float x = i;
      x /= 255;
      x = pow(x, 2.5);
      x *= 255;      
      if (commonAnode) {
        gammatable[i] = 255 - x;
      } else {
        gammatable[i] = x;      
      }
   }
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t clear, red, green, blue;
  tcs.getRGBC(&red, &green, &blue, &clear);
 // Figure out some basic hex code for visualization
 uint32_t sum = clear;
 float r, g, b;
 r = red; r /= sum;
 g = green; g /= sum;
 b = blue; b /= sum;
 r *= 255; g *= 255; b *= 255;
 String redHex,greenHex,blueHex, FullHex;
 redHex =  String((int)r, HEX);  
 greenHex =  String((int)g, HEX);  
 blueHex =  String((int)b, HEX);

 FullHex = redHex + greenHex + blueHex;

 Serial.println("Color In RGB Format");
 Serial.println("--------------------------------------");

 Serial.print("R: ");
 Serial.println(((int)r));

 Serial.print("G: ");
 Serial.println(((int)g));

 Serial.print("B: ");
 Serial.println(((int)b));
 delay(1000);
 Serial.println("Color in HEX format");
 Serial.println("-------------------------------------");
 Serial.print("#");
 Serial.println(FullHex);
 delay(1000);
}