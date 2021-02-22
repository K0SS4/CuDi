#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

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
    void on_addbutton_clicked();

    void on_removeButton_clicked();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionHelp_triggered();

    void on_actionAuthor_triggered();

    void on_eventGroupName_textchanged(QString name);

private:
    Ui::MainWindow *ui;
    QString path;
    QVector<QString> gnames;
    int gnumber;

};
#endif // MAINWINDOW_H
