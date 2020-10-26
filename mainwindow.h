#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color_converter.h"
#include <QMainWindow>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QColor>

class ColorWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSpinBox *m_r;
    QSpinBox *m_g;
    QSpinBox *m_b;

    QSpinBox *m_h;
    QSpinBox *m_s;
    QSpinBox *m_v;

    QLineEdit *m_hex;
    QSpinBox *m_vba;

    ColorWidget *m_colorWidget;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotColorChanged(const QString& value);

signals:
    void colorChanged(const QColor& color);

private:
    QGroupBox* setupRgb();
    QGroupBox* setupHsv();
    QGroupBox* setupHex();
    QGroupBox* setupVba();
    QGroupBox* setupColorWidget();
    void blockAllSignals(bool b);
};

class ColorWidget : public QWidget {
    Q_OBJECT

    QColor m_color;

protected:
    void paintEvent(QPaintEvent*) override;

public:
    ColorWidget(QWidget* parent = nullptr);

public slots:
    void colorChanged(const QColor& color);
};
#endif // MAINWINDOW_H
