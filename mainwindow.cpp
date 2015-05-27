#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    log("Program Started");
    log("Please select file");


}

MainWindow::~MainWindow()
{
    delete ui;
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
    }
}

void MainWindow::on_outputPathButton_clicked()
{
    QString outputPath = QFileDialog::getSaveFileName(this,tr("Select output file path"));
    if(outputPath.size() == 0){
        log("Error: No file selected");
    } else {
        log("file selected " + outputPath );

        ui->tmpPathText->clear();
        ui->tmpPathText->append(outputPath );
    }
}
