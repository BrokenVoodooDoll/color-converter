#include "color_converter.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <QString>

namespace Color{

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
        default: r = 0; g = 0; b = 0; break;
    }
    return {static_cast<int>(r * 255. / 100.),
                static_cast<int>(g * 255. / 100.),
                static_cast<int>(b * 255. / 100.)};
}

HSV rgb2hsv(RGB rgb) {
    const std::vector<double> colors {rgb.r / 255., rgb.g / 255., rgb.b / 255.};
    const double v = *std::max_element(colors.begin(), colors.end());
    const double c = v - *std::min_element(colors.begin(), colors.end());

    double h;
    if (c == 0) {
        h = 0.;
    } else {
        if (v == colors[0] && colors[1] >= colors[2]) {
            h = 60. * (0 + (colors[1] - colors[2]) / c);
        } else if (v == colors[0] && colors[1] < colors[2]) {
            h = 60. * (6 + (colors[1] - colors[2]) / c);
        } else if (v == colors[1]) {
            h = 60. * (2 + (colors[2] - colors[0]) / c);
        } else {
            h = 60. * (4 + (colors[0] - colors[1]) / c);
        }
    }

    const double s = v == 0 ? 0 : c / v;
    return {static_cast<int>(std::round(h)), static_cast<int>(std::round(100 * s)), static_cast<int>(std::round(100 * v))};

}

RGB vba2rgb(VBA vba) {
    return { vba.vba % 256,
                (vba.vba / 256) % 256,
                (vba.vba / 256 / 256) % 256 };
}

VBA rgb2vba(RGB rgb) {
    return { rgb.r + rgb.g * 256 + rgb.b * 256 * 256 };
//    std::stringstream ss;
//    ss << std::setfill('0') << std::setw(6) << std::hex << vba.vba;
//    boost::to_upper(vba.vba);
}

RGB hex2rgb(HEX hex) {
    return { (hex.hex / 256 / 256) % 256,
                (hex.hex / 256) % 256,
                hex.hex % 256 };
}

HEX rgb2hex(RGB rgb) {
    return { 256 * 256 * rgb.r + 256 * rgb.g + rgb.b };
}

}
