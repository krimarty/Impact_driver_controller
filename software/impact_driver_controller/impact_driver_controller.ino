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

#include "include/Motor.h"
#include "include/UserInterface.h"

// State machine
enum class State {
};
State currentState = ;

// Sequention mode variables
bool goingLeft = true;

// Classes
Motor motor;
UserInterface ui;
std::vector<uint8_t> faultPins = {5, 6, 7};
DRV8874_Indicator drivers(control, faultPins);

if (drivers.isFault(1)) {
    // chyba na pinu 6
}


State nextState(State state)
{
    return state;
}

void setup() {
    Serial.begin(115200);
    pinMode(MS_PIN, INPUT_PULLUP);
    bool isMaster = digitalRead(MS_PIN) == LOW;

    motor.begin();

    // Setup finished
    pinMode(25, OUTPUT);
    digitalWrite(25, HIGH); 
}

void loop() {
    delay(DELAY_MS);
    unsigned long currentMillis = millis();
    unsigned long deltaMillis = currentMillis - lastMillis;

    // Periodical class updates
    motor.dutyUpdate();
    //ui.readFilteredPotPercent();

    // LEDs 
    if (currentState != State::MANUAL)
    {
        ui.setLeftLed(false);
        ui.setRightLed(false);
    }
    if (currentState == State::SEQUENCE || currentState == State::RANDOM)
        ui.setSignalLed(true);
    else if (currentState == State::SYN)
    {
        if (comm_status)
            ui.setSignalLed(true);
        else
        {
            if (currentMillis - lastToggle >= 500)
            {
                ledState = !ledState;
                ui.setSignalLed(ledState ? HIGH : LOW);
                lastToggle = currentMillis;
            }
        }
    }
    else
        ui.setSignalLed(false);

    lastMillis = currentMillis;
}