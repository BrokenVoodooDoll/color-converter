#ifndef COLOR_CONVERTER_H
#define COLOR_CONVERTER_H
#include <string>

namespace Color{
    struct RGB {
        int r;
        int g;
        int b;
    };

    struct HSV {
        int h;
        int s;
        int v;
    };

    struct VBA {
        int rgb;
        std::string hex;
    };

    HSV rgb2hsv(RGB rgb);
    RGB hsv2rgb(HSV hsv);
    VBA rgb2vba(RGB rgb);
    VBA hsv2vba(RGB hsv);
    RGB vba2rgb(VBA vba);
    HSV vba2hsv(VBA vba);
}
#endif // COLOR_CONVERTER_H
