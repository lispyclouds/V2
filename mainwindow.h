#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include "filecrypto.h"
#include "v2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void fileDone(QString);
    void on_lineEdit_returnPressed();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_checkBox_toggled(bool checked);
    void on_checkBox_2_toggled(bool checked);
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    V2 handler;
    FileCrypto *fc;

    inline void connectAll();
};

#endif // MAINWINDOW_H
