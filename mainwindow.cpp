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
    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->tableWidget->verticalHeader()->setVisible(true);
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
        this->setWindowTitle("CuDi  *");
    }
}
void MainWindow::on_removeButton_clicked()
{
    if(ui->remove->text().isEmpty())
    {
        ui->alerts->setVisible(true);
        ui->alerts->setText("Type in a row number to delete it");
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
            this->setWindowTitle("CuDi  *");
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file", "/home", tr("CuDi File (*.cudi)"));
    path = filename;
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Couldn't open the file");
        return;
    }

    ui->tableWidget->setRowCount(0);

    QTextStream input(&file);
    while(!input.atEnd())
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QString tmp = input.readLine();
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(tmp));

        tmp = input.readLine();
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(tmp));
    }
    this->setWindowTitle("CuDi");
    file.close();
}

void MainWindow::on_actionNew_triggered()
{
    this->setWindowTitle("CuDi  *");
    ui->tableWidget->setRowCount(0);
    ui->original->setText("");
    ui->translated->setText("");
    path = "";
}

void MainWindow::on_actionSave_triggered()
{
    QFile file;
    if(path.isEmpty())
    {
        QString filename = QFileDialog::getSaveFileName(this, "Save the file", "/home", tr("CuDi File (*.cudi)"));
        file.setFileName(filename);
        path = filename;
    }
    else
    {
        file.setFileName(path);
    }

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
    this->setWindowTitle("CuDi");
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save the file", "/home", tr("CuDi File (*.cudi)"));
    path = filename;
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
    this->setWindowTitle("CuDi");
    file.flush();
    file.close();
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::information(this, "Help", "If you don't know what to do just visit\nhttps://github.com/K0SS4/CuDi");
}

void MainWindow::on_actionAuthor_triggered()
{
    QMessageBox::information(this, "Author", "The author of this application is\nKacper Kossakowski\n\nYou can contact me on\nkacper.kossakowski01@gmail.com");
}
