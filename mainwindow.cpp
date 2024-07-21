#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "http.cpp"
#include "ImageGraph.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Toronto");
    ui->comboBox->addItem("Kingston");
    ui->comboBox->addItem("Montreal");
    ui->comboBox->addItem("Ottawa");
    ui->comboBox->addItem("Waterloo");
    ui->comboBox->addItem("Vancouver");
    ui->comboBox->addItem("Tokyo");
    ui->comboBox->addItem("Munich");
    ui->comboBox->addItem("My Location");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    radius = ui->spinBox->value();
    ui -> stackedWidget -> setCurrentIndex(3);
}

void MainWindow::on_cartoon1_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    //irregular pentagon
    new Http(ui->comboBox->currentText(), pentagon, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);
}
void MainWindow::on_cartoon2_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    //triangle
    new Http(ui->comboBox->currentText(), triangle, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);
}
void MainWindow::on_cartoon3_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    // square
    new Http(ui->comboBox->currentText(), square, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);

}
void MainWindow::on_cartoon4_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    //irregular hexagon
    new Http(ui->comboBox->currentText(), hexagon, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);
}
void MainWindow::on_cartoon5_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    //regular rhombus
    new Http(ui->comboBox->currentText(), rhombus, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);
}

void MainWindow::on_restartButton_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(0);
    if (this->isTopLevel())
        (QApplication::allWindows())[0]->close();
    else
        (QApplication::allWidgets())[1]->close();
}
