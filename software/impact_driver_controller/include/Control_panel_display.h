#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class MotorDisplay {
public:
    MotorDisplay(uint8_t width = 128, uint8_t height = 64, uint8_t i2c_addr = 0x3C)
        : _display(width, height, &Wire, -1), _i2cAddr(i2c_addr) {}

    void begin() {
        if(!_display.begin(SSD1306_SWITCHCAPVCC, _i2cAddr)) {
            Serial.println(F("SSD1306 allocation failed"));
            for(;;);
        }
        _display.clearDisplay();
        _display.display();
    }

    void showCurrent(float current) {
        _display.setTextSize(2);
        _display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // bílé písmo na černém pozadí
        _display.setCursor(0, 0);
        _display.print("Current: ");
        _display.print(current, 2);
        _display.println(" A");
        _display.display();
    }

    void showMode(const char* mode) {
        _display.setTextSize(1);
        _display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        _display.setCursor(0, 30);
        _display.print("Mode: ");
        _display.println(mode);
        _display.display();
    }

    void clear() {
        _display.clearDisplay();
        _display.display();
    }

private:
    Adafruit_SSD1306 _display;
    uint8_t _i2cAddr;
};
