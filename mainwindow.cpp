#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "color_converter.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <QColor>

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
    using namespace Color;
    CheckRGB(ui->lineEdit_R, ui->lineEdit_G, ui->lineEdit_B);
    QColor color = QColor::fromRgb(ui->lineEdit_R->text().toInt(),
                  ui->lineEdit_G->text().toInt(),
                  ui->lineEdit_B->text().toInt());
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
    using namespace Color;
    CheckHSV(ui->lineEdit_H, ui->lineEdit_S, ui->lineEdit_V);
    QColor color;
    color.fromHsv(ui->lineEdit_H->text().toInt(),
                  ui->lineEdit_S->text().toInt(),
                  ui->lineEdit_V->text().toInt());
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
    using namespace Color;
    CheckHEX(ui->lineEdit_Hex);
    QColor color;
    color.setNamedColor("#" + ui->lineEdit_Hex->text());
    SetRGB(color);
    SetHSV(color);
    SetVBALong(color);
    SetVBAHex(color);
}

void MainWindow::on_lineEdit_VBA_Long_editingFinished()
{
    using namespace Color;
    CheckVBALong(ui->lineEdit_VBA_Long);
    QColor color = FromVBA(ui->lineEdit_VBA_Long->text().toInt());
    SetRGB(color);
    SetHEX(color);
    SetHSV(color);
    SetVBAHex(color);
}

void MainWindow::on_lineEdit_VBA_Hex_editingFinished()
{
    using namespace Color;
    CheckVBALong(ui->lineEdit_VBA_Long);
    QColor color = FromVBA(ui->lineEdit_VBA_Long->text().toInt(nullptr, 16));
    SetRGB(color);
    SetHEX(color);
    SetHSV(color);
    SetVBALong(color);
}

void MainWindow::SetRGB(const QColor& color) {
    ui->lineEdit_R->setText(QString::number(color.red()));
    ui->lineEdit_G->setText(QString::number(color.green()));
    ui->lineEdit_B->setText(QString::number(color.blue()));
}

void MainWindow::SetHEX(const QColor& color) {
    ui->lineEdit_Hex->setText(color.name(QColor::NameFormat::HexRgb).right(6));
}

void MainWindow::SetHSV(const QColor& color) {
    ui->lineEdit_H->setText(QString::number(color.hue()));
    ui->lineEdit_S->setText(QString::number(color.saturation()));
    ui->lineEdit_V->setText(QString::number(color.value()));
}

void MainWindow::SetVBALong(const QColor& color) {
    using namespace Color;
    ui->lineEdit_VBA_Long->setText(QString::number(GetVBA(color)));
}

void MainWindow::SetVBAHex(const QColor& color) {
    using namespace Color;
    ui->lineEdit_VBA_Hex->setText(QString::number(GetVBA(color), 16));
}
