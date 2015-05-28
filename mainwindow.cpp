#include <QFileDialog>
#include <QMetaObject>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DecodeSplit/DecodeSplitStage.h"
#include "DecodeSplit/DecodeSplitResult.h"
#include "VideoEdit/videoui.h"
#include "VideoEdit/videocapture.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    log("Program Started");
    log("Please select file");
    dss = new DecodeSplitStage(this);
    scene_video_ui= new VideoUI(ui->videoUI, this);
    ui->videoUI = scene_video_ui;
    set_up_scene_split();
    ui->rightPanel->setEnabled(false);
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
    qDebug() << "scene scene edit set";
    vcap = new VideoCapture(scene_video_ui->width(), scene_video_ui->height());
    captureThread.start();
    vcap->moveToThread(&captureThread);
    scene_video_ui->connect(vcap, SIGNAL(frame_ready(cv::Mat*)),
                           SLOT(show_frame(cv::Mat*)));
  //  vcap->load(dss->get_input_file());
    vcap->load(dss->get_input_file());
    connect(ui->playButton, SIGNAL(clicked()), vcap, SLOT(play()));
    connect(ui->pauseButton, SIGNAL(clicked()), vcap, SLOT(pause()));
    connect(ui->nextFrameButton, SIGNAL(clicked()), vcap, SLOT(next_frame()));
    connect(ui->preFrameButton, SIGNAL(clicked()), vcap, SLOT(pre_frame()));
}

void MainWindow::scene_split_done(DecodeSplitResult* result_){
    ds_result = result_;
    set_up_scene_edit();
    ds_result->set_list_view(ui->sceneList);
    ui->rightPanel->setEnabled(true);
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

void MainWindow::on_outputPathButton_clicked()
{
    QString outputPath = QFileDialog::getSaveFileName(this,tr("Select output file path"));
    if(outputPath.size() == 0){
        log("Error: No file selected");
    } else {
        log("file selected " + outputPath );

        ui->outputPathText->clear();
        ui->outputPathText->append(outputPath);
        dss->set_output_file(outputPath);
    }
}


void MainWindow::on_jumpToFrame_clicked()
{
}

void MainWindow::on_sceneStartButton_clicked()
{
   QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int ,ds_result->get_scene_start()));
}

void MainWindow::on_sceneEndButton_clicked()
{
    QMetaObject::invokeMethod(vcap, "jump_to_frame", Q_ARG(int, ds_result->get_scene_end()));
}

void MainWindow::on_removeSceneBUtton_clicked()
{

}

void MainWindow::on_sceneList_clicked(const QModelIndex &index)
{
    ds_result->select_scene(VideoSection(ui->sceneList->item(index.row())->text().toStdString()));
}
