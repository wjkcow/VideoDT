#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

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
    void on_videoFileSelectButton_clicked();

    void on_tmpFilePathButton_clicked();

    void on_outputPathButton_clicked();

private:
    Ui::MainWindow *ui;
    void log(const QString& qstr);
};

#endif // MAINWINDOW_H
