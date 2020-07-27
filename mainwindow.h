#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color_converter.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_lineEdit_R_textEdited();

    void on_lineEdit_G_textEdited();

    void on_lineEdit_B_textEdited();

    void on_lineEdit_H_textEdited();

    void on_lineEdit_S_textEdited();

    void on_lineEdit_V_textEdited();

    void on_lineEdit_Hex_textEdited();

    void on_lineEdit_VBA_Long_textEdited();

    void on_lineEdit_VBA_Hex_textEdited();

    void SetRGB(Color::RGB rgb);

    void SetHEX(Color::HEX hex);

    void SetHSV(Color::HSV hsv);

    void SetVBALong(Color::VBA vba);

    void SetVBAHex(Color::VBA vba);

    void CheckRGB();

    void CheckHEX();

    void CheckHSV();

    void CheckVBALong();

    void CheckVBAHex();

    Color::RGB GetRGB() const;

    Color::HEX GetHEX() const;

    Color::HSV GetHSV() const;

    Color::VBA GetVbaLong() const;

    Color::VBA GetVbaHex() const;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
