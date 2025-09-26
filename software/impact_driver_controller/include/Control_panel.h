/* =============================================================
 * Project:   impact_driver_controller
 * File:      Control_panel.h
 * Author:    Martin Kriz
 * Company:   Ullmanna s.r.o.
 * Created:   2025-09-26
 * -------------------------------------------------------------
 * Description:
 * Notes:
 * ============================================================= */

#pragma once
#include <Arduino.h>

// Pin assignment
constexpr int PIN_POT1 = 27;
constexpr int PIN_POT2 = 26;
constexpr int PIN_SW_MODE = 18;
constexpr int PIN_SW2 = 5;
constexpr int PIN_LED_STATUS = 17;
constexpr int PIN_LED_ERROR  = 16;

enum class ModeType {
    MANUAL,
    RANDOM,
    SEQUENCE
};

enum class Direction {
    LEFT,
    RIGHT,
    STOP
};
class UserInterface {
private:   
    bool isLeftPressed()  { return digitalRead(PIN_BTN_LEFT)  == LOW; }
    bool isRightPressed() { return digitalRead(PIN_BTN_RIGHT) == LOW; }
    
public:
    UserInterface() {
        pinMode(PIN_POT, INPUT);
        pinMode(PIN_BTN_LEFT, INPUT_PULLUP);
        pinMode(PIN_BTN_RIGHT, INPUT_PULLUP);
        pinMode(PIN_MODE, INPUT_PULLUP);
        pinMode(PIN_INVERSE, INPUT_PULLUP);
        pinMode(PIN_MAN, INPUT_PULLUP);
        pinMode(PIN_SEQ, INPUT_PULLUP);
        pinMode(PIN_LED_SIGNAL, OUTPUT);
        pinMode(PIN_LED_LEFT, OUTPUT);
        pinMode(PIN_LED_RIGHT, OUTPUT);
    }

    Direction getDirection() {
        if (isLeftPressed() && isRightPressed()) {
            return Direction::STOP;
        }
        else if (isLeftPressed()) {
            return Direction::LEFT;
        } else if (isRightPressed()) {
            return Direction::RIGHT;
        } else {
            return Direction::STOP;
        }
    }

    int getDirectionNum() {
        if (isLeftPressed() && isRightPressed()) {
            return 0;
        }
        else if (isLeftPressed()) {
            return -1;
        } else if (isRightPressed()) {
            return 1;
        } else {
            return 0;
        }
    }

    bool isSyncMode()     { return digitalRead(PIN_MODE)    == LOW; }
    bool isInverse()      { return digitalRead(PIN_INVERSE) == LOW; }

    ModeType getModeType() {
        if (digitalRead(PIN_MAN) == LOW)
            return ModeType::MANUAL;
        else if (digitalRead(PIN_SEQ) == LOW)
            return ModeType::SEQUENCE;
        else
            return ModeType::RANDOM;
    }

    float readFilteredPotPercent() {
        int raw = analogRead(PIN_POT);
        return map(raw, 0, 1024, 20, 100);
    }

    void setSignalLed(bool state) { digitalWrite(PIN_LED_SIGNAL, state ? HIGH : LOW); }
    void setLeftLed(bool state)   { digitalWrite(PIN_LED_LEFT,   state ? HIGH : LOW); }
    void setRightLed(bool state)  { digitalWrite(PIN_LED_RIGHT,  state ? HIGH : LOW); }

};
