#include "color_converter.h"
#include <algorithm>
#include <vector>

template<typename T>
T abs(T value) {
    return value < 0 ? -value : value;
}

namespace Color{
HSV rgb2hsv(RGB rgb) {
    const std::vector<int> colors{rgb.r, rgb.g, rgb.b};
    const int v = *std::max_element(colors.begin(), colors.end());
    const int c = v - *std::min(colors.begin(), colors.end());
    int h;
    if (c == 0) {
        h = 0;
    } else {
        if (v == rgb.r) {
            h = 60 * (0 + (rgb.g - rgb.b) / c);
        } else if (v == rgb.g) {
            h = 60 * (2 + (rgb.b - rgb.r) / c);
        } else {
            h = 60 * (4 + (rgb.r - rgb.g) / c);
        }
    }
    const int s = v == 0 ? 0 : c / v;
    return {static_cast<int>(h), static_cast<int>(s), static_cast<int>(v)};

}
RGB hsv2rgb(HSV hsv) {
    const int c = hsv.v * hsv.s;
    const int h = hsv.h / 60;
    const int x = c * (1 - abs(h % 2 - 1));
    int r, g, b;
    if (h >= 0 && h <= 1) {
        r = c; g = x; b = 0;
    } else if(h > 1 && h <= 2) {
        r = x; g = c; b = 0;
    } else if(h > 2 && h <= 3) {
        r = 0; g = c; b = x;
    } else if(h > 3 && h <= 4) {
        r = 0; g = x; b = c;
    } else if(h > 4 && h <= 5) {
        r = x; g = 0; b = c;
    } else if(h > 5 && h <= 6) {
        r = c; g = 0; b = x;
    } else {
        r = 0; g = 0; b = 0;
    }
    const int m = hsv.v - c;
    return { r + m, g + m, b + m };
}
}
//VBA rgb2vba(RGB rgb);
//VBA hsv2vba(RGB hsv);
//RGB vba2rgb(VBA vba);
//HSV vba2hsv(VBA vba);
