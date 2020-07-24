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

    void on_lineEdit_R_editingFinished();

    void on_lineEdit_G_editingFinished();

    void on_lineEdit_B_editingFinished();

    void SetHSV(Color::RGB rgb);

    Color::RGB GetRGB() const;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
