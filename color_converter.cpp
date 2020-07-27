#include "color_converter.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <QString>

template<typename T>
T abs(T value) {
    return value < 0 ? -value : value;
}


namespace Color{
VBA::VBA() {}

VBA::VBA(int rgb_)
    : rgb(rgb_) {

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(6) << std::hex << rgb;
    hex = ss.str();
    boost::to_upper(hex);
}

VBA::VBA(std::string hex_)
    : hex(hex_) {

    rgb = QString::fromStdString(hex).toInt(nullptr, 16);
}

HSV rgb2hsv(RGB rgb) {
    const std::vector<double> colors {rgb.r / 255.0, rgb.g / 255.0, rgb.b / 255.0};
    const double v = *std::max_element(colors.begin(), colors.end());
    const double c = v - *std::min(colors.begin(), colors.end());
    double h;
    if (c == 0) {
        h = 0;
    } else {
        if (v == rgb.r) {
            h = 60. * (0 + (colors[1] - colors[2]) / c);
        } else if (v == rgb.g) {
            h = 60. * (2 + (colors[2] - colors[0]) / c);
        } else {
            h = 60. * (4 + (colors[0] - colors[1]) / c);
        }
    }
    const double s = v == 0 ? 0 : c / v;
    return {static_cast<int>(std::round(h)), static_cast<int>(std::round(100 * s)), static_cast<int>(std::round(100 * v))};

}
RGB hsv2rgb(HSV hsv) {
    const double c = (hsv.v / 100.) * (hsv.s / 100.);
    const int h = std::round(hsv.h / 60);
    const double x = c * (1 - abs(h % 2 - 1));
    double r, g, b;
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
    const double m = (h - c) / 100.;
    return {static_cast<int>((r + m) * 255.),
                static_cast<int>((g + m) * 255.),
                static_cast<int>((b + m) * 255.)};
}

VBA rgb2vba(RGB rgb) {
    VBA vba;
    vba.rgb = rgb.r + rgb.g * 256 + rgb.b * 256 * 256;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(6) << std::hex << vba.rgb;
    vba.hex = ss.str();
    boost::to_upper(vba.hex);

    return vba;
}

RGB vba2rgb(VBA vba) {
    RGB rgb;
    rgb.r = vba.rgb % 256;
    rgb.g = (vba.rgb / 256) % 256;
    rgb.b = (vba.rgb / 256 / 256) % 256;

    return rgb;
}
HSV vba2hsv(VBA vba) {
    return rgb2hsv(vba2rgb(vba));
}

HEX rgb2hex(RGB rgb) {
    return {
        256 * 256 * rgb.r +
                256 * rgb.g +
                rgb.b
    };
}
RGB hex2rgb(HEX hex) {
    RGB rgb;
    rgb.r = (hex.hex / 256 / 256) % 256;
    rgb.g = (hex.hex / 256) % 256;
    rgb.b = hex.hex % 256;

    return rgb;
}
}
