#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFileDialog>
#include <QStandardPaths>
#include <encoded.h>
#include <string>
#include <fstream>
#include <QMenu>
#include <decoded.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->DirectoryPath->setFixedHeight(26);

    formatMenu = new QMenu();
    // Добавляем форматы в меню
    formatMenu->addAction(".doc", [&]() { qDebug() << "Выбран формат: .doc"; });
    formatMenu->addAction(".pdf", [&]() { qDebug() << "Выбран формат: .pdf"; });
    formatMenu->addAction(".txt", [&]() { qDebug() << "Выбран формат: .txt"; });
    formatMenu->addAction(".xlsx", [&]() { qDebug() << "Выбран формат: .xlsx"; });
    ui->format->setFixedWidth(60);

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
        to += "Decoded.";
        to += ui->format->text().toStdString();
        std::ifstream inFile(fileName.toStdString(), std::ifstream::binary);
        std::ofstream outFile(to, std::ofstream::binary);
        decoded(inFile, outFile, ui->progressBar);
    }
    else {
        qDebug() << "Failed to open file:" << fileName;
    }
}




void MainWindow::on_format_clicked()
{
    formatMenu->exec(ui->format->mapToGlobal(QPoint(0, ui->format->height())));
    QObject::connect(formatMenu, &QMenu::triggered, [this](QAction *action) {
        this->ui->format->setText(action->text());  // Меняем текст кнопки на выбранный формат
    });
}

