/*****************************************************************************
Code written around the following hardware:
- Wareshare 1.54in ePaper display
- Nice!Nano v1 microcontroller

Code modified by Klef Heavy Industries 2026

ORIGINAL-----------------------------------

* | File      	:   epd1in54_V2.cpp
* | Author      :   Waveshare team
* | Function    :   1.54inch e-paper V2
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-06-24
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/

#include <SPI.h>
#include "epd1in54_V2.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <stdio.h>

// E-Paper Display Setup
Epd epd;
unsigned char image[1024];
Paint paint(image, 0, 0);

#define COLORED     0
#define UNCOLORED   1

// Declare Timers
int lastTime = millis();

//Setup
void setup()
{
  //Serial.begin(115200);
  //Serial.println("e-Paper init and clear");
  epd.LDirInit();
  epd.Clear();

  //EPD
  paint.SetWidth(200);
  paint.SetHeight(24);

  epd.HDirInit();
  epd.DisplayPartBaseImage(bmp_tutelStart);

  // Cool boot sequence
  epd.DisplayPartBaseImage(bmp_neuroStartA);
  delay(500);
  epd.SetFrameMemoryPartial(bmp_neuroStartB, 0, 198, 200, 200);
  epd.DisplayPartFrame();
  delay(500);
  epd.SetFrameMemoryPartial(bmp_neuroMainA, 0, 198, 200, 200);
  epd.DisplayPartFrame();
  delay(500);
  epd.SetFrameMemoryPartial(bmp_neuroMainB, 0, 198, 200, 200);
  epd.DisplayPartFrame();
  delay(2000); 
  epd.HDirInit();
  epd.DisplayPartBaseImage(bmp_neuroB);
  delay(500);
  epd.SetFrameMemoryPartial(bmp_neuroA, 0, 198, 200, 200);
  epd.DisplayPartFrame();
  delay(1000);
  epd.SetFrameMemoryPartial(bmp_evilCloseup, 0, 198, 200, 200);
  epd.DisplayPartFrame();
  delay(1000);
  epd.SetFrameMemoryPartial(bmp_twinsCloseup, 0, 198, 200, 200);
  epd.DisplayPartFrame();

  delay(3000);

  //epd.Clear();
  epd.Sleep();

  // Confirm ADC settings
  analogReference(AR_INTERNAL);
  analogReadResolution(10);
}

// Timer Declarations
int lastDebounce = millis();

// ADC Declarations
int battValue = 0;
float battVoltage = 0.0;
char battV[10][10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}; // Counter declaration (TODO: i need to relearn how to code lol)

// Timer setup
#define BATT_SCREEN_UPDATE 300000      // Refresh speed of screen during battery mode

// LOOPING
void loop()
{
  // Update the image
  if (millis()-lastTime > BATT_SCREEN_UPDATE){
    //Get the Battery Voltage
    battVoltage = 0;
    for (int i = 0; i<10;i++) { //Average over 10 Samples
      battVoltage = battVoltage + analogRead(4) * (3600.0/1024.0) * (1.0 + (820000.0/2000000.0)); // There's a voltage divider
      delay(10);
    };
    battVoltage = battVoltage/10.0;
    itoa(battVoltage, battV[0],10); //Convert to char

    // Cycling Images
    epd.HDirInit();
    //Pick a Random Image
    epd.DisplayPartBaseImage(epd_bitmap_allArray[random(0,epd_bitmap_allArray_LEN)]);
    
    //Display Battery Voltage if low (<3.6V)
    if (battVoltage < 3600) {
      paint.SetWidth(120);
      paint.SetHeight(18);
      paint.Clear(UNCOLORED);
      paint.DrawStringAt(90, 3, battV[0], &Font12, COLORED);
      paint.DrawStringAt(2, 3, "Low Battery! ", &Font12, COLORED);
      epd.SetFrameMemoryPartial(paint.GetImage(), 80, 15, paint.GetWidth(), paint.GetHeight());
      epd.DisplayPartFrame();
    }

    //Sleep, power save
    epd.Sleep();

    //Reset Timer
    lastTime = millis();
  }
}



