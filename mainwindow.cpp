#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "color_converter.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_R_editingFinished()
{
    SetHSV(GetRGB());
}

void MainWindow::on_lineEdit_G_editingFinished()
{
    SetHSV(GetRGB());
}

void MainWindow::on_lineEdit_B_editingFinished()
{
    SetHSV(GetRGB());
}

void MainWindow::SetHSV(Color::RGB rgb) {
    Color::HSV hsv = rgb2hsv(rgb);

    ui->lineEdit_H->setText(QString::number(hsv.h));
    ui->lineEdit_S->setText(QString::number(hsv.s));
    ui->lineEdit_V->setText(QString::number(hsv.v));
}

Color::RGB MainWindow::GetRGB() const {
    return {
        ui->lineEdit_R->text().toInt(),
        ui->lineEdit_G->text().toInt(),
        ui->lineEdit_B->text().toInt(),
    };
}
