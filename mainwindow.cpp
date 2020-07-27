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


void MainWindow::on_lineEdit_R_textEdited()
{
    CheckRGB();
    Color::RGB rgb = GetRGB();
    SetHSV(rgb2hsv(rgb));
    SetHEX(rgb2hex(rgb));
    SetVBALong(rgb2vba(rgb));
    SetVBAHex(rgb2vba(rgb));
}

void MainWindow::on_lineEdit_G_textEdited()
{
    on_lineEdit_R_textEdited();
}

void MainWindow::on_lineEdit_B_textEdited()
{
    on_lineEdit_R_textEdited();
}

void MainWindow::on_lineEdit_H_textEdited()
{
    CheckHSV();
    Color::HSV hsv = GetHSV();
    Color::RGB rgb = hsv2rgb(hsv);
    SetRGB(rgb);
    SetHEX(rgb2hex(rgb));
    SetVBALong(rgb2vba(rgb));
    SetVBAHex(rgb2vba(rgb));
}

void MainWindow::on_lineEdit_S_textEdited()
{
    on_lineEdit_H_textEdited();
}

void MainWindow::on_lineEdit_V_textEdited()
{
    on_lineEdit_H_textEdited();
}

void MainWindow::on_lineEdit_Hex_textEdited()
{
    CheckHEX();
    Color::HEX hex = GetHEX();
    Color::RGB rgb = hex2rgb(hex);
    Color::HSV hsv = rgb2hsv(rgb);
    Color::VBA vba = rgb2vba(rgb);
    SetRGB(rgb);
    SetHSV(hsv);
    SetVBALong(vba);
    SetVBAHex(vba);
}

void MainWindow::on_lineEdit_VBA_Long_textEdited()
{
    CheckVBALong();
    Color::VBA vba = GetVbaLong();
    Color::RGB rgb = vba2rgb(vba);
    vba = rgb2vba(rgb);
    Color::HSV hsv = rgb2hsv(rgb);
    Color::HEX hex = rgb2hex(rgb);
    SetRGB(rgb);
    SetHEX(hex);
    SetHSV(hsv);
    SetVBAHex(vba);
}

void MainWindow::on_lineEdit_VBA_Hex_textEdited()
{
    CheckVBAHex();
    Color::VBA vba = GetVbaHex();
    Color::RGB rgb = vba2rgb(vba);
    vba = rgb2vba(rgb);
    Color::HSV hsv = rgb2hsv(rgb);
    Color::HEX hex = rgb2hex(rgb);
    SetRGB(rgb);
    SetHEX(hex);
    SetHSV(hsv);
    SetVBALong(vba);
}

void MainWindow::SetRGB(Color::RGB rgb) {
    ui->lineEdit_R->setText(QString::number(rgb.r));
    ui->lineEdit_G->setText(QString::number(rgb.g));
    ui->lineEdit_B->setText(QString::number(rgb.b));
}

void MainWindow::SetHEX(Color::HEX hex) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(6) << std::hex << hex.hex;
    ui->lineEdit_Hex->setText(QString::fromStdString(ss.str()));
}

void MainWindow::SetHSV(Color::HSV hsv) {
    ui->lineEdit_H->setText(QString::number(hsv.h));
    ui->lineEdit_S->setText(QString::number(hsv.s));
    ui->lineEdit_V->setText(QString::number(hsv.v));
}

void MainWindow::SetVBALong(Color::VBA vba) {
    ui->lineEdit_VBA_Long->setText(QString::number(vba.rgb));
}

void MainWindow::SetVBAHex(Color::VBA vba) {
    ui->lineEdit_VBA_Hex->setText(QString::fromStdString(vba.hex));
}

Color::RGB MainWindow::GetRGB() const {
    return {
        ui->lineEdit_R->text().toInt(),
                ui->lineEdit_G->text().toInt(),
                ui->lineEdit_B->text().toInt(),
    };
}

Color::HEX MainWindow::GetHEX() const {
    return {
        ui->lineEdit_Hex->text().toInt(nullptr, 16)
    };
}

Color::HSV MainWindow::GetHSV() const {
    return {
        ui->lineEdit_H->text().toInt(),
                ui->lineEdit_S->text().toInt(),
                ui->lineEdit_V->text().toInt(),
    };
}

Color::VBA MainWindow::GetVbaLong() const {
    return Color::VBA(ui->lineEdit_VBA_Long->text().toInt());
}
Color::VBA MainWindow::GetVbaHex() const {
    return Color::VBA(ui->lineEdit_VBA_Hex->text().toStdString());
}

void MainWindow::CheckRGB() {
    if (ui->lineEdit_R->text().toInt() > 255) {
        ui->lineEdit_R->setText(QString::number(255));
    } else if (ui->lineEdit_R->text().toInt() < 0) {
        ui->lineEdit_R->setText(QString::number(0));
    }

    if (ui->lineEdit_G->text().toInt() > 255) {
        ui->lineEdit_G->setText(QString::number(255));
    } else if (ui->lineEdit_G->text().toInt() < 0) {
        ui->lineEdit_G->setText(QString::number(0));
    }

    if (ui->lineEdit_B->text().toInt() > 255) {
        ui->lineEdit_B->setText(QString::number(255));
    } else if (ui->lineEdit_B->text().toInt() < 0) {
        ui->lineEdit_B->setText(QString::number(0));
    }
}

void MainWindow::CheckHEX() {
    std::stringstream ss;
    std::string line = ui->lineEdit_Hex->text().toStdString();
    if (line.size() > 6) {
        ui->lineEdit_Hex->setText("ffffff");
        return;
    }
    ss << line;
    int hex;
    ss >> std::hex >> hex;
    if (hex < 0) {
        ui->lineEdit_Hex->setText("000000");
    } else if(hex > 0xffffff) {
        ui->lineEdit_Hex->setText("ffffff");
    }
}

void MainWindow::CheckHSV() {
    if (ui->lineEdit_H->text().toInt() > 359) {
        ui->lineEdit_H->setText(QString::number(359));
    } else if (ui->lineEdit_H->text().toInt() < 0) {
        ui->lineEdit_H->setText(QString::number(0));
    }

    if (ui->lineEdit_S->text().toInt() > 100) {
        ui->lineEdit_S->setText(QString::number(100));
    } else if (ui->lineEdit_S->text().toInt() < 0) {
        ui->lineEdit_S->setText(QString::number(0));
    }

    if (ui->lineEdit_V->text().toInt() > 100) {
        ui->lineEdit_V->setText(QString::number(100));
    } else if (ui->lineEdit_V->text().toInt() < 0) {
        ui->lineEdit_V->setText(QString::number(0));
    }
}

void MainWindow::CheckVBALong() {
    int vba = ui->lineEdit_VBA_Long->text().toInt();
    if (vba < 0) {
        ui->lineEdit_VBA_Long->setText("0");
    } else if (vba > Color::VBA_RGB_LIMIT) {
        ui->lineEdit_VBA_Long->setText(QString::number(Color::VBA_RGB_LIMIT));
    }
}

void MainWindow::CheckVBAHex() {
    std::stringstream ss;
    std::string line = ui->lineEdit_VBA_Hex->text().toStdString();
    if (line.size() > 6) {
        ui->lineEdit_VBA_Hex->setText("FFFFFF");
        return;
    }
    ss << line;
    int hex;
    ss >> std::hex >> hex;
    if (hex < Color::HEX_MIN) {
        ui->lineEdit_VBA_Hex->setText("000000");
    } else if(hex > Color::HEX_MAX) {
        ui->lineEdit_VBA_Hex->setText("FFFFFF");
    }
}
