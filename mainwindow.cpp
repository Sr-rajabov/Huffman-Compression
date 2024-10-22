#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QFile>
#include <QStandardPaths>
#include <encoded.h>
#include <string>
#include <QDebug>
#include <fstream>
#include <decoded.h>
#include <thread>


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


void MainWindow::on_openFileButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        tr("All Files (*);;Text Files (*.txt)"));
    ui->DirectoryPath->setText(fileName);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
}


void MainWindow::on_coding_clicked()
{
    if (!fileName.isEmpty()) {
        std::string to = fileName.toStdString();
        size_t pos = to.rfind('.');
        if (pos != std::string::npos) {
            to.erase(pos);
        }
        to += ".hff";
        std::ifstream inFile(fileName.toStdString(), std::ifstream::binary);
        std::ofstream outFile(to, std::ofstream::binary);    

        encoded(inFile, outFile, ui->progressBar);

        inFile.close();
        outFile.close();
    }
    else {
        qDebug() << "Failed to open file:" << fileName;
    }
}


void MainWindow::on_decoding_clicked()
{
    if (!fileName.isEmpty()) {
        std::string to = fileName.toStdString();
        size_t pos = to.rfind('.');
        if (pos != std::string::npos) {
            to.erase(pos);
        }
        to += "Decoded.pdf";
        std::ifstream inFile(fileName.toStdString(), std::ifstream::binary);
        std::ofstream outFile(to, std::ofstream::binary);
        decoded(inFile, outFile, ui->progressBar);
    }
    else {
        qDebug() << "Failed to open file:" << fileName;
    }
}



