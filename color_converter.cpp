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
    const int h = (hsv.h / 60) % 6;
    const double v_min = hsv.v * (100. - hsv.s) / 100.;
    const double a = (hsv.v - v_min) * (hsv.h % 60) / 60.;
    const double v_inc = v_min + a;
    const double v_dec = hsv.v - a;

    double r, g, b;
    switch(h) {
        case 0: r = hsv.v; g = v_inc; b = v_min; break;
        case 1: r = v_dec; g = hsv.v; b = v_min; break;
        case 2: r = v_min; g = hsv.v; b = v_inc; break;
        case 3: r = v_min; g = v_dec; b = hsv.v; break;
        case 4: r = v_inc; g = v_min; b = hsv.v; break;
        case 5: r = hsv.v; g = v_min; b = v_dec; break;
    }
    return {static_cast<int>(r * 255. / 100.),
                static_cast<int>(g * 255. / 100.),
                static_cast<int>(b * 255. / 100.)};
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
