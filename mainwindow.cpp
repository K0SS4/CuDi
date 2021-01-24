#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , path("")
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
        ui->original->setText("");
        ui->translated->setText("");
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
            ui->remove->setText("");
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file", "/home", tr("CuDi File (*.cudi)"));
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Couldn't open the file");
        return;
    }

    on_actionNew_triggered();

    QTextStream input(&file);
    while(!input.atEnd())
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QString tmp = input.readLine();
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(tmp));

        tmp = input.readLine();
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(tmp));
    }
    file.close();
}

void MainWindow::on_actionNew_triggered()
{
    ui->tableWidget->setRowCount(0);
    ui->original->setText("");
    ui->translated->setText("");
    path = "";
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save the file", "/home", tr("CuDi File (*.cudi)"));
    QFile file(filename);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Couldn't save the file");
        return;
    }



    QTextStream output(&file);
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QString tmp = ui->tableWidget->item(i, 0)->text();
        output << tmp << "\n";

        tmp = ui->tableWidget->item(i, 1)->text();
        output << tmp << "\n";
    }

    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{

}
