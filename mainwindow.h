#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
class DecodeSplitStage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void log(const QString& qstr);

private slots:
    void on_videoFileSelectButton_clicked();

    void on_tmpFilePathButton_clicked();

    void on_outputPathButton_clicked();

private:
    Ui::MainWindow *ui;
    DecodeSplitStage *dss;
};

#endif // MAINWINDOW_H
