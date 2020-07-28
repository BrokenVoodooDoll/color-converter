#include "color_converter.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <QString>
#include <QLineEdit>

namespace Color{
void CheckField(QLineEdit *comp, int min, int max, int base) {
    bool ok = true;

    if (comp->text().toInt(&ok, base) > max) {
        comp->setText(QString::number(max, base));
    } else if (comp->text().toInt(&ok, base) < min) {
        comp->setText(QString::number(min, base));
    }
    if (!ok) {
        comp->setText(QString::number(min, base));
    }
}

void CheckRGB(QLineEdit* r, QLineEdit* g, QLineEdit* b) {
    CheckField(r);
    CheckField(g);
    CheckField(b);
}

void CheckHEX(QLineEdit *hex) {
    CheckField(hex, 0x000000, 0xffffff, 16);
}

void CheckHSV(QLineEdit *h, QLineEdit *s, QLineEdit *v) {
    CheckField(h, 0, 359);
    CheckField(s, 0, 255);
    CheckField(v, 0, 255);
}

void CheckVBALong(QLineEdit *vba) {
    CheckField(vba, 0, 16'777'216);
}

void CheckVBAHex(QLineEdit *vba) {
    CheckField(vba, 0x000000, 0xffffff, 16);
}

int GetVBA(const QColor& color) {
    int r = color.red();
    int g = color.green();
    int b = color.blue();

    return r + g * 256 + b * 256 * 256;
}

QColor FromVBA(int vba) {
    int r = vba % 256;
    int g = (vba / 256) % 256;
    int b = (vba / 256 / 256) % 256;

    return QColor::fromRgb(r, g, b);
}
}
