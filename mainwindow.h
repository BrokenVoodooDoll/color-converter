#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color_converter.h"
#include <QMainWindow>
#include <QColor>

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

    void on_lineEdit_R_editingFinished();

    void on_lineEdit_G_editingFinished();

    void on_lineEdit_B_editingFinished();

    void on_lineEdit_H_editingFinished();

    void on_lineEdit_S_editingFinished();

    void on_lineEdit_V_editingFinished();

    void on_lineEdit_Hex_editingFinished();

    void on_lineEdit_VBA_Long_editingFinished();

    void on_lineEdit_VBA_Hex_editingFinished();

    void SetRGB(const QColor& color);

    void SetHEX(const QColor& color);

    void SetHSV(const QColor& color);

    void SetVBALong(const QColor& color);

    void SetVBAHex(const QColor& color);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
