#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QThread>
class DecodeSplitStage;
class DecodeSplitResult;
class VideoUI;
class VideoCapture;
class TTaskManager;
class Tracking;
class TrackingResult;
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
    void te_draw_start();
    void te_draw_end();
private slots:
    //void update_frame(int n);
    void tracking_done();
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

    void on_nextStepButton_clicked();

    void on_addTracker_clicked();

    void on_candidateTaskView_clicked(const QModelIndex &index);

    void on_teJumpToButton_clicked();

    void on_teTrackerStart_clicked();

    void on_teTrackerEnd_clicked();

    void on_teEditTracker_clicked();

    void on_teSetEnd_clicked();

    void on_startTracking_clicked();

private:
    Ui::MainWindow *ui;
    void set_up_scene_split();
    void set_up_scene_edit();
    void set_up_tracking_task();
    void fake_page_2();
    DecodeSplitStage *dss;
    DecodeSplitResult *ds_result;
    QThread captureThread;
    VideoCapture* vcap;
    VideoUI* scene_video_ui;
    VideoUI* task_video_ui;
    VideoUI* result_video_ui;
    TTaskManager* ttask_manager = nullptr;
    Tracking* tracking;
    TrackingResult* t_result;
};

#endif // MAINWINDOW_H
