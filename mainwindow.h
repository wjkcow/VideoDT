#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QThread>
class DecodeSplitStage;
class DecodeSplitResult;
class VideoUI;
class VideoCapture;

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
    void enable_left_panel();
    void disable_left_panel();
private slots:
    //void update_frame(int n);
    void scene_split_done(DecodeSplitResult* result);
    void on_videoFileSelectButton_clicked();

    void on_tmpFilePathButton_clicked();

//    void on_outputPathButton_clicked();

    void on_jumpToFrame_clicked();

    void on_sceneStartButton_clicked();

    void on_sceneEndButton_clicked();

    void on_sceneList_clicked(const QModelIndex &index);

    void on_setStartButton_clicked();

    void on_setEndButton_clicked();

private:
    Ui::MainWindow *ui;
    void set_up_scene_split();
    void set_up_scene_edit();
    DecodeSplitStage *dss;
    DecodeSplitResult *ds_result;
    QThread captureThread;
    VideoCapture* vcap;
    VideoUI* scene_video_ui;
    VideoUI* task_video_ui;
    VideoUI* result_video_ui;

};

#endif // MAINWINDOW_H
