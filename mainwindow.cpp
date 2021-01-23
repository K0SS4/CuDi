#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->setSizeGripEnabled(false);
    ui->alerts->setVisible(false);
    ui->alerts->setFrameStyle(QFrame::NoFrame);
    ui->remove->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addbutton_clicked()
{
    ui->alerts->setVisible(false);
    if(ui->original->text().isEmpty() || ui->translated->text().isEmpty())
    {
        ui->alerts->setVisible(true);
        ui->alerts->setText("Fill both fields first!");
    }
    else
    {
        QString original = ui->original->text();
        QString translated = ui->translated->text();
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(original));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(translated));
    }
}
void MainWindow::on_removeButton_clicked()
{
    if(ui->remove->text().isEmpty())
    {
        ui->alerts->setVisible(true);
        ui->alerts->setText("Which row do you want to delete?");
    }
    else
    {
        int remove = ui->remove->text().toInt() - 1;
        if(remove > ui->tableWidget->rowCount() - 1)
        {
            ui->alerts->setVisible(true);
            ui->alerts->setText("There's no such row");
        }
        else
        {
            ui->tableWidget->removeRow(remove);
        }
    }
}
