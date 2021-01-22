#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->alerts->setVisible(false);
    ui->alerts->setFrameStyle(QFrame::NoFrame);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   ui->alerts->setVisible(false);
   if(ui->original->text().isEmpty() || ui->translated->text().isEmpty())
   {
       ui->alerts->setVisible(true);
       ui->alerts->setText("Fill both fields first!");
   }
   else
   {
       //Saving to dictionary file
   }
}
