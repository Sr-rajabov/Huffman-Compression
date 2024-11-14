#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFileButton_clicked();

    void on_coding_clicked();

    void on_decoding_clicked();

    void on_format_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QMenu *formatMenu;
};
#endif // MAINWINDOW_H
