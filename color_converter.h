#ifndef COLOR_CONVERTER_H
#define COLOR_CONVERTER_H
#include <string>

namespace Color{
static int VBA_LIMIT = 16777215;
static int HEX_MAX = 0xffffff;
static int HEX_MIN = 0x000000;

struct RGB {
    int r;
    int g;
    int b;
};

struct HEX {
    int hex;
};

struct HSV {
    int h;
    int s;
    int v;
};

struct VBA {
    int vba;
};

HSV rgb2hsv(RGB rgb);
RGB hsv2rgb(HSV hsv);

HEX rgb2hex(RGB rgb);
RGB hex2rgb(HEX hex);

VBA rgb2vba(RGB rgb);
RGB vba2rgb(VBA vba);

class Color {
public:
    // Конструкторы
    Color(RGB rgb)
        : rgb_(rgb) {
        //конвертация
        hsv_ = rgb2hsv(rgb_);
        hex_ = rgb2hex(rgb_);
        vba_ = rgb2vba(rgb_);
    }
    Color(HSV hsv)
        : hsv_(hsv) {
        //конвертация
        rgb_ = hsv2rgb(hsv_);
        hex_ = rgb2hex(rgb_);
        vba_ = rgb2vba(rgb_);
    }
    Color(HEX hex)
        : hex_(hex) {
        // конвертация
        rgb_ = hex2rgb(hex_);
        hsv_ = rgb2hsv(rgb_);
        vba_ = rgb2vba(rgb_);
    }
    Color(VBA vba)
        : vba_(vba) {
        // конвертация
        rgb_ = vba2rgb(vba_);
        hsv_ = rgb2hsv(rgb_);
        vba_ = rgb2vba(rgb_);
    }

    //Getters
    RGB GetRgb() const { return rgb_; }
    int GetRed() const { return rgb_.r; }
    int GetGreen() const { return rgb_.g; }
    int GetBlue() const { return rgb_.b; }

    HSV GetHsv() const { return hsv_; }
    int GetHue() const { return hsv_.h; }
    int GetSaturation() const { return hsv_.s; }
    int GetValue() const { return hsv_.v; }

    HEX GetHex() const { return hex_; }
    //string GetHexCode

    VBA GetVba() const { return vba_; }
    //int GetVbaValue
    //string GetVbaCode

private:
    RGB rgb_;
    HEX hex_;
    HSV hsv_;
    VBA vba_;
};
}
#endif // COLOR_CONVERTER_H
