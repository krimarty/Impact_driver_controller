/* =============================================================
 * Project:   impact_driver_controller
 * File:      impact_driver_controller.ino
 * Author:    Martin Kriz
 * Company:   Ullmanna s.r.o.
 * Created:   2025-09-26
 * -------------------------------------------------------------
 * Description:
 *
 * Notes:
 * ============================================================= */

#include "include/DRV8874_motor.h"
#include "include/Control_panel.h"

constexpr long unsigned int  DELAY_MS = 10; // [ms] speed of main loop

DRV8874_control motor;
ControlPanel panel;

bool stop = false;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Starting Motor class test...");

  motor.begin();

  Serial.println("Motor initialized.");
}

void loop() {


    if (stop == false)
    {
      int tmp2 = panel.readPot2();
      for (size_t i = 0; i < tmp2; i++)
      {
          int tmp1 = panel.readPot1();
          motor.left((tmp1 * 100) / 1023);
          motor.dutyUpdate();
          tmp2 = panel.readPot2();
          if(panel.wasSw1Pressed()) 
          {
            stop = true;
            break;
          }
          delay(DELAY_MS);
      }

      size_t a = 0;
      while (tmp2 > a)
      {
          motor.stop();
          motor.dutyUpdate();
          tmp2 = panel.readPot2();
          if(panel.wasSw1Pressed()) {Serial.println("pressed");}
          if(panel.wasSw2Pressed()) 
          {
            stop = false;
            break;
          }
          delay(DELAY_MS);
          ++a;
      }
    }
    else
    {
      if(panel.wasSw2Pressed()) 
        {
          stop = false;
        }
      delay(10);
    }

}