#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "color_converter.h"
#include <iostream>
#include <sstream>
#include <iomanip>

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
    Color::CheckRGB(ui->lineEdit_R, ui->lineEdit_G, ui->lineEdit_B);

    Color::Color color(Color::RGB {
                           ui->lineEdit_R->text().toInt(),
                           ui->lineEdit_G->text().toInt(),
                           ui->lineEdit_B->text().toInt()
                       });

    SetHSV(color);
    SetHEX(color);
    SetVBALong(color);
    SetVBAHex(color);
}

void MainWindow::on_lineEdit_G_editingFinished()
{
    on_lineEdit_R_editingFinished();
}

void MainWindow::on_lineEdit_B_editingFinished()
{
    on_lineEdit_R_editingFinished();
}

void MainWindow::on_lineEdit_H_editingFinished()
{
    Color::CheckHSV(ui->lineEdit_H, ui->lineEdit_S, ui->lineEdit_V);
    Color::Color color(Color::HSV {
                           ui->lineEdit_H->text().toInt(),
                           ui->lineEdit_S->text().toInt(),
                           ui->lineEdit_V->text().toInt()
                       });
    SetRGB(color);
    SetHEX(color);
    SetVBALong(color);
    SetVBAHex(color);
}

void MainWindow::on_lineEdit_S_editingFinished()
{
    on_lineEdit_H_editingFinished();
}

void MainWindow::on_lineEdit_V_editingFinished()
{
    on_lineEdit_H_editingFinished();
}

void MainWindow::on_lineEdit_Hex_editingFinished()
{
    Color::CheckHEX(ui->lineEdit_Hex);
    Color::Color color(Color::HEX {
                           ui->lineEdit_Hex->text().toInt(nullptr, 16)
                       });
    SetRGB(color);
    SetHSV(color);
    SetVBALong(color);
    SetVBAHex(color);
}

void MainWindow::on_lineEdit_VBA_Long_editingFinished()
{
    Color::CheckVBALong(ui->lineEdit_VBA_Long);
    Color::Color color(Color::VBA {
                           ui->lineEdit_VBA_Long->text().toInt()
                       });
    SetRGB(color);
    SetHEX(color);
    SetHSV(color);
    SetVBAHex(color);
}

void MainWindow::on_lineEdit_VBA_Hex_editingFinished()
{
    Color::CheckVBALong(ui->lineEdit_VBA_Long);
    Color::Color color(Color::VBA {
                           ui->lineEdit_VBA_Long->text().toInt(nullptr, 16)
                       });
    SetRGB(color);
    SetHEX(color);
    SetHSV(color);
    SetVBAHex(color);
}

void MainWindow::SetRGB(const Color::Color& color) {
    ui->lineEdit_R->setText(QString::number(color.GetRed()));
    ui->lineEdit_G->setText(QString::number(color.GetGreen()));
    ui->lineEdit_B->setText(QString::number(color.GetBlue()));
}

void MainWindow::SetHEX(const Color::Color& color) {

    ui->lineEdit_Hex->setText(color.GetHex().GetCode());
}

void MainWindow::SetHSV(const Color::Color& color) {
    ui->lineEdit_H->setText(QString::number(color.GetHue()));
    ui->lineEdit_S->setText(QString::number(color.GetSaturation()));
    ui->lineEdit_V->setText(QString::number(color.GetValue()));
}

void MainWindow::SetVBALong(const Color::Color& color) {
    using namespace Color;
    ui->lineEdit_VBA_Long->setText(QString::number(color.GetVba().vba));
}

void MainWindow::SetVBAHex(const Color::Color& color) {
    using namespace Color;
    ui->lineEdit_VBA_Hex->setText(color.GetHex().GetCode());
}
