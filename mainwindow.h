#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QThread>
class DecodeSplitStage;
class DecodeSplitResult;
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
    void scene_split_done(DecodeSplitResult* result);
    void on_videoFileSelectButton_clicked();

    void on_tmpFilePathButton_clicked();

    void on_outputPathButton_clicked();

private:
    Ui::MainWindow *ui;
    void set_up_scene_split();
    void set_up_scene_edit();
    DecodeSplitStage *dss;
    DecodeSplitResult *result;
    QThread captureThread;

};

#endif // MAINWINDOW_H
