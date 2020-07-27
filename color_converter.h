#ifndef COLOR_CONVERTER_H
#define COLOR_CONVERTER_H
#include <QLineEdit>
#include <QColor>

namespace Color{
void CheckField(QLineEdit *comp, int min = 0, int max = 255, int base = 10);

void CheckRGB(QLineEdit *r, QLineEdit *g, QLineEdit *b);

void CheckHEX(QLineEdit *hex);

void CheckHSV(QLineEdit *h, QLineEdit *s, QLineEdit *v);

void CheckVBALong(QLineEdit *vba);

void CheckVBAHex(QLineEdit *vba);

int GetVBA(const QColor& color);

QColor FromVBA(int vba);
}
#endif // COLOR_CONVERTER_H
