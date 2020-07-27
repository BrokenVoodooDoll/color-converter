#ifndef COLOR_CONVERTER_H
#define COLOR_CONVERTER_H
#include <string>

namespace Color{
    static int VBA_RGB_LIMIT = 16777215;
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
        VBA();
        VBA(int rgb_);
        VBA(std::string hex_);

        int rgb;
        std::string hex;
    };

    HSV rgb2hsv(RGB rgb);
    RGB hsv2rgb(HSV hsv);

    HEX rgb2hex(RGB rgb);
    RGB hex2rgb(HEX hex);

    VBA rgb2vba(RGB rgb);
    RGB vba2rgb(VBA vba);
    HSV vba2hsv(VBA vba);
}
#endif // COLOR_CONVERTER_H