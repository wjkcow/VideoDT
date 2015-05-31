#include <QFileDialog>
#include <QMetaObject>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DecodeSplit/DecodeSplitStage.h"
#include "DecodeSplit/DecodeSplitResult.h"
#include "VideoEdit/videoui.h"
#include "VideoEdit/videocapture.h"
#include "Dectector/TTaskManager.h"
#include "Tracking/Tracking.h"
#include "Tracking/TrackingResult.h"

class Frame;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    log("Program Started");
    log("Please select file");
    dss = new DecodeSplitStage(this);
    scene_video_ui= new VideoUI(ui->videoUI, this);
    task_video_ui = new VideoUI(ui->taskEditVideoUI, this);
    result_video_ui = new VideoUI(ui->resultVideoUI, this);
    ui->videoUI = scene_video_ui;
    set_up_scene_split();
    ui->rightPanel->setEnabled(false);
    fake_page_2();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::enable_left_panel(){
    ui->leftPanel->setEnabled(true);
}

void MainWindow::disable_left_panel(){
    ui->leftPanel->setEnabled(false);
}
void MainWindow::set_up_scene_split(){
    connect(ui->selectHistButton, SIGNAL(pressed()), dss, SLOT(set_hist()));
    connect(ui->selectPHAButton, SIGNAL(pressed()), dss, SLOT(set_pha()));
    connect(ui->selectMethod, SIGNAL(currentIndexChanged(const QString &)), dss, SLOT(set_method(QString)));
    connect(ui->methodThreshold, SIGNAL(valueChanged(double)), dss, SLOT(set_threshold(double)));
    connect(ui->compressX,SIGNAL(valueChanged(int)), dss, SLOT(set_width(int)));
    connect(ui->compressY,SIGNAL(valueChanged(int)), dss, SLOT(set_height(int)));
    connect(ui->runAlgorithm, SIGNAL(pressed()), dss, SLOT(run()));
    connect(dss, SIGNAL(handle_result(DecodeSplitResult*)), this, SLOT(scene_split_done(DecodeSplitResult*)));

}
void MainWindow::set_up_scene_edit(){
    qDebug() << "scene edit se uit";
    vcap = new VideoCapture(scene_video_ui->width(), scene_video_ui->height());
    captureThread.start();
    vcap->moveToThread(&captureThread);
    scene_video_ui->connect(vcap, SIGNAL(frame_ready(Frame*)),
                           SLOT(show_frame(Frame*)));
  //  vcap->load("/Users/wjkcow/Desktop/Fiesta.mp4");
     vcap->load(dss->get_input_file());
    connect(ui->playButton, SIGNAL(clicked()), vcap, SLOT(play()));
    connect(ui->pauseButton, SIGNAL(clicked()), vcap, SLOT(pause()));
    connect(ui->nextFrameButton, SIGNAL(clicked()), vcap, SLOT(next_frame()));
    connect(ui->preFrameButton, SIGNAL(clicked()), vcap, SLOT(pre_frame()));
    connect(ui->addScene, SIGNAL(clicked()), ds_result, SLOT(add_scene()));
    connect(ui->removeScene, SIGNAL(clicked()), ds_result, SLOT(remove_selected_section()));

    connect(vcap, SIGNAL(new_frame_fired(int)), ui->toFrame, SLOT(setValue(int)));
    connect(vcap, SIGNAL(new_frame_fired(int)), ds_result, SLOT(set_current_frame(int)));
}

void MainWindow::scene_split_done(DecodeSplitResult* result_){
    ui->rightPanel->setEnabled(true);
//    ui->nextFrameButton->setEnabled(true);
    ui->nextStepButton->setEnabled(true);

    ds_result = result_;
    set_up_scene_edit();
    ds_result->set_list_view(ui->sceneList);
}

void MainWindow::log(const QString& qstr){
    ui->logText->append(qstr);
}

void MainWindow::on_videoFileSelectButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Videos (*.mp4 *.avi)"));
    if(fileName.size() == 0){
        log("Error: No file selected");
    } else {
        log("File selected " + fileName );

        ui->videoFilePathText->clear();
        ui->videoFilePathText->append(fileName);
        dss->set_video_file(fileName);
    }
}

void MainWindow::on_tmpFilePathButton_clicked()
{
    QString tmpPath = QFileDialog::getExistingDirectory(this, tr("Select tmpfile path"));
    if(tmpPath.size() == 0){
        log("Error: No path selected");
    } else {
        log("Path selected " + tmpPath );

        ui->tmpPathText->clear();
        ui->tmpPathText->append(tmpPath);
        dss->set_tmp_path(tmpPath);
    }
}

//void MainWindow::on_outputPathButton_clicked()
//{
//    QString outputPath = QFileDialog::getSaveFileName(this,tr("Select output file path"));
//    if(outputPath.size() == 0){
//        log("Error: No file selected");
//    } else {
//        log("file selected " + outputPath );

//        ui->outputPathText->clear();
//        ui->outputPathText->append(outputPath);
//        dss->set_output_file(outputPath);
//    }
//}


void MainWindow::on_jumpToFrame_clicked()
{
    if(ui->toFrame->value() > ds_result->get_total_frame()){
        ui->toFrame->setValue(0);
    }
    QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int ,ui->toFrame->value()));
}

void MainWindow::on_sceneStartButton_clicked()
{
   QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int ,ds_result->get_scene_start()));
}

void MainWindow::on_sceneEndButton_clicked()
{
    QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int, ds_result->get_scene_end()));
}

void MainWindow::on_sceneList_clicked(const QModelIndex &index)
{
    ds_result->select_scene(VideoSection(ui->sceneList->item(index.row())->text().toStdString()));

    on_sceneStartButton_clicked();
}

void MainWindow::on_setStartButton_clicked()
{
    ds_result->set_scence_start();
    ui->newFromFrame->setText(QString::number(ui->toFrame->value()));
}

void MainWindow::on_setEndButton_clicked()
{
    ds_result->set_scene_end();
    ui->newToFrame->setText(QString::number(ui->toFrame->value()));
}


void MainWindow::on_nextStepButton_clicked()
{
    if(!ttask_manager){
        set_up_tracking_task();
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::set_up_tracking_task(){
    ttask_manager = new TTaskManager(ds_result, task_video_ui, this);
    ttask_manager->set_ctask_list_view(ui->candidateTaskView);
    ttask_manager->set_task_list_view(ui->taskListView);
    QMetaObject::invokeMethod(vcap, "resize", Q_ARG(QSize,task_video_ui->size()));

    QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int,0));
    if(scene_video_ui){
        disconnect(vcap, SIGNAL(frame_ready(Frame*)),scene_video_ui,
                               SLOT(show_frame(Frame*)));
    }
    ttask_manager->connect(vcap, SIGNAL(frame_ready(Frame*)),
                           SLOT(draw_frame_with_rect(Frame*)));
    connect(ui->tePlayButton, SIGNAL(clicked()), vcap, SLOT(play()));
    connect(ui->tePauseButton, SIGNAL(clicked()), vcap, SLOT(pause()));
    connect(ui->teNextFrame, SIGNAL(clicked()), vcap, SLOT(next_frame()));
    connect(ui->tePreFrame, SIGNAL(clicked()), vcap, SLOT(pre_frame()));
    connect(ui->teAddTracker, SIGNAL(clicked()), ttask_manager, SLOT(add_to_task()));
    connect(task_video_ui, SIGNAL(rect_drawed(const QRect&)), ttask_manager, SLOT(rect_drawed(const QRect&)));
    connect(vcap, SIGNAL(new_frame_fired(int)), ttask_manager, SLOT(set_current_frame(int)));
    connect(vcap, SIGNAL(new_frame_fired(int)), ui->teToFrame, SLOT(setValue(int)));
    connect(ui->teRemoveTask, SIGNAL(clicked()), ttask_manager, SLOT(remove_selected_task()));
}
void MainWindow::fake_page_2(){
    ds_result = new DecodeSplitResult(dss->video_info,std::vector<int>{0,27,52,76,129,155,189,260,389,422,460,516,585,628,698,724,734,738,759});
    if(!ds_result){
        qDebug() << "fake fail";

    }
    ui->nextStepButton->setEnabled(true);
    vcap = new VideoCapture(scene_video_ui->width(), scene_video_ui->height());
    captureThread.start();
    vcap->moveToThread(&captureThread);
    vcap->load("/Users/wjkcow/Desktop/Fiesta.mp4");
}

void MainWindow::on_addTracker_clicked()
{
   ttask_manager->add_tracker(ui->trackerType->currentText(), ui->trackerName->toPlainText());
}

void MainWindow::on_candidateTaskView_clicked(const QModelIndex &index)
{
    ttask_manager->select_ctracking_task(ui->candidateTaskView->item(index.row())->text());
    ui->teFrom->setText(QString::number(ttask_manager->get_tracker_start()));
    ui->teTo->setText(QString::number(ttask_manager->get_tracker_end()));
    ui->teTrackerName->setText(ttask_manager->get_tracker_name());
    on_teTrackerStart_clicked();
}

void MainWindow::on_teJumpToButton_clicked()
{
    if(ui->teToFrame->value() > 1864){//ds_result->get_total_frame()){
        ui->teToFrame->setValue(0);
    }
    QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int ,ui->teToFrame->value()));
}

void MainWindow::on_teTrackerStart_clicked()
{

    QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int ,ttask_manager->get_tracker_start()));
}

void MainWindow::on_teTrackerEnd_clicked()
{
    QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int ,ttask_manager->get_tracker_end()));

}

void MainWindow::on_teEditTracker_clicked()
{
    ttask_manager->edit_selected();
    ui->teFrom->setText(QString::number(ui->teToFrame->value()));

}

void MainWindow::te_draw_start(){
    ui->teLeft->setEnabled(false);
    ui->teRight->setEnabled(false);
    ui->teUp->setEnabled(false);
    ui->teDown->setEnabled(false);
}
void MainWindow::te_draw_end(){
    ui->teLeft->setEnabled(true);
    ui->teRight->setEnabled(true);
    ui->teUp->setEnabled(true);
    ui->teDown->setEnabled(true);
}

void MainWindow::on_teSetEnd_clicked()
{
    ttask_manager->set_end_frame_to_selected();
    ui->teTo->setText(QString::number(ui->teToFrame->value()));
}


void MainWindow::on_startTracking_clicked()
{
    log("Tracking is running");
    tracking = new Tracking(ttask_manager->get_task(), ttask_manager->video_info, this, ui->trackingAlgorithm->currentText());
    connect(tracking, SIGNAL(all_done()), this, SLOT(tracking_done()));
    tracking->run();
    ui->teLeft->setEnabled(false);
    ui->teRight->setEnabled(false);
    ui->teUp->setEnabled(false);
    ui->teDown->setEnabled(false);
}

void MainWindow::tracking_done(){
    qDebug() << "tracking done";
    t_result = tracking->get_result();
    set_up_final_reslut();
}

void MainWindow::set_up_final_reslut(){
    ui->stackedWidget->setCurrentIndex(0);
    t_result->set_list_view(ui->resultList);
    QMetaObject::invokeMethod(vcap, "resize", Q_ARG(QSize,result_video_ui->size()));
    QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int,0));
    if(ttask_manager){
        disconnect(vcap, SIGNAL(frame_ready(Frame*)),ttask_manager,
                               SLOT(draw_frame_with_rect(Frame*)));
    }
    t_result->connect(vcap, SIGNAL(frame_ready(Frame*)),
                           SLOT(draw_frame_with_rect(Frame*)));
    connect(ui->rtPlayButton, SIGNAL(clicked()), vcap, SLOT(play()));
    connect(ui->rtPauseButton, SIGNAL(clicked()), vcap, SLOT(pause()));
    connect(ui->rtNextFrame, SIGNAL(clicked()), vcap, SLOT(next_frame()));
    connect(ui->rtPreFrame, SIGNAL(clicked()), vcap, SLOT(pre_frame()));
    connect(ui->rtEdit, SIGNAL(clicked()), t_result, SLOT(edit_selected()));
    connect(result_video_ui, SIGNAL(rect_drawed(const QRect&)), t_result, SLOT(rect_drawed(const QRect&)));
    connect(vcap, SIGNAL(new_frame_fired(int)), t_result, SLOT(set_current_frame(int)));
    connect(vcap, SIGNAL(new_frame_fired(int)), ui->rtToFrame, SLOT(setValue(int)));

}

void MainWindow::on_rtTrackerStart_clicked()
{
   QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int ,t_result->get_tracker_start()));
}

void MainWindow::on_rtTrackerEnd_clicked()
{
   QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int ,t_result->get_tracker_end()));
}


void MainWindow::on_resultList_clicked(const QModelIndex &index)
{
    t_result->select_tracking_task(ui->resultList->item(index.row())->text());
    ui->rtTrackerName->setText(t_result->get_tracker_name());
    on_rtTrackerStart_clicked();
}
void MainWindow::rt_draw_start(){
    ui->rtLeft->setEnabled(false);
    ui->rtUp->setEnabled(false);
    ui->rtDown->setEnabled(false);
}
void MainWindow::rt_draw_end(){
    ui->rtLeft->setEnabled(true);
    ui->rtUp->setEnabled(true);
    ui->rtDown->setEnabled(true);
}

void MainWindow::on_rtJumpToButton_clicked()
{
    if(ui->rtToFrame->value() > ds_result->get_total_frame()){
        ui->toFrame->setValue(0);
    }
    QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int ,ui->rtToFrame->value()));
}
