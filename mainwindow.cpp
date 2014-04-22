#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setStyleSheet("border: none");
    ui->statusBar->showMessage("Current Encryption/Decryption status: Idle... :'(");

    setWindowIcon(QIcon(":/images/icon.png"));
    fc = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    if (ui->lineEdit_2->text() == "" || !handler.loadKeyFromFile(ui->lineEdit_2->text()))
    {
        QMessageBox::information(this, "Error!", "Please provide a valid key file or generate a new one");
        return;
    }

    QString mode;
    if (ui->radioButton->isChecked())
        mode = "encrypt";
    else
        mode = "decrypt";

    handler.setMode(mode, ui->checkBox->isChecked(), ui->checkBox_2->isChecked(), ui->horizontalSlider->value());
    ui->lineEdit_3->setText(handler.process(ui->lineEdit->text()));
    handler.updateKey();
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                "Please select a key file",
                                                QDir::homePath(),
                                                "V2 Key Files (*.v2key);;All Files (*.*)");

    if (path != "")
        ui->lineEdit_2->setText(path);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                "Enter a file name to write to",
                                                QDir::homePath(),
                                                "V2 Key Files (*.v2key);;All Files (*.*)");

    if (path == "")
        return;

    ui->lineEdit_2->setText(path);
    handler.makeNewKey(path);
    QMessageBox::information(this, "Success", "New key created at " + path);
}

void MainWindow::on_pushButton_3_clicked()
{
    handler.clearKeys();
    QMessageBox::information(this, "Success", "Key Store Cleared!");
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    ui->checkBox_2->setEnabled(checked);
    ui->horizontalSlider->setEnabled(ui->checkBox_2->isChecked());
}

void MainWindow::on_checkBox_2_toggled(bool checked)
{
    ui->horizontalSlider->setEnabled(checked);
}

void MainWindow::fileDone(QString msg)
{
    ui->pushButton_6->setText("Start FIle I/O");
    ui->pushButton_4->setEnabled(true);

    if (msg == "")
        ui->progressBar->setValue(0);

    ui->lineEdit_5->setText(msg);
    ui->statusBar->showMessage("Current Encryption/Decryption status: Idle... :'(");
    delete fc;
    fc = NULL;
    handler.updateKey();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select a file to process", QDir::homePath());

    if (path == "")
        return;

    ui->lineEdit_4->setText(path);
    ui->pushButton_6->setEnabled(true);
}

void MainWindow::on_pushButton_6_clicked()
{
    if (ui->lineEdit_2->text() == "")
    {
        QMessageBox::information(this, "Error", "Please provide a valid key file or generate a new one");
        return;
    }

    if (fc != NULL)
    {
        fc->stopIt = true;
        return;
    }

    QString mode;
    if (ui->radioButton->isChecked())
        mode = "encrypt";
    else
        mode = "decrypt";

    if (!handler.loadKeyFromFile(ui->lineEdit_2->text()))
    {
        QMessageBox::information(this, "Error", "Inavlid Key File");
        return;
    }

    ui->pushButton_6->setText("Cancel");
    ui->pushButton_4->setEnabled(false);

    fc = new FileCrypto(ui->lineEdit_4->text(),
                        ui->lineEdit_2->text(),
                        mode,
                        ui->checkBox->isChecked(),
                        ui->checkBox_2->isChecked(),
                        ui->horizontalSlider->value());
    connectAll();
    fc->start();
}

void MainWindow::connectAll()
{
    connect(fc, SIGNAL(completed(int)), ui->progressBar, SLOT(setValue(int)));
    connect(fc, SIGNAL(msg(QString)), ui->statusBar, SLOT(showMessage(QString)));
    connect(fc, SIGNAL(okie(QString)), this, SLOT(fileDone(QString)));
}
