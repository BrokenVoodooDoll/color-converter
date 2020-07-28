#ifndef COLOR_CONVERTER_H
#define COLOR_CONVERTER_H
#include <string>
#include <QLineEdit>
#include <QString>

namespace Color{
static int VBA_LIMIT = 16'777'215;
static int HEX_MAX = 0xffffff;
static int HEX_MIN = 0x000000;

std::string GetHexCode(int);

struct RGB {
    int r;
    int g;
    int b;
};

struct HEX {
    int hex;

    QString GetCode() const {
        return QString::fromStdString(GetHexCode(hex));
    }
};

struct HSV {
    int h;
    int s;
    int v;
};

struct VBA {
    int vba;

    QString GetCode() const {
        return QString::fromStdString(GetHexCode(vba));
    }
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

void CheckField(QLineEdit *comp, int min = 0, int max = 255, int base = 10);

void CheckRGB(QLineEdit *r, QLineEdit *g, QLineEdit *b);

void CheckHEX(QLineEdit *hex);

void CheckHSV(QLineEdit *h, QLineEdit *s, QLineEdit *v);

void CheckVBALong(QLineEdit *vba);

void CheckVBAHex(QLineEdit *vba);

}
#endif // COLOR_CONVERTER_H
