#include "MainWindow.h"
#include "../include/GuitarSori.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    GuitarSori::getInstance()->init(1024, 2, 4, 0x00000004, 44100);
    GuitarSori::getInstance()->runThread();
    while ((sampleBuffer = (int *)GuitarSori::getInstance()->getSampleBuffer()) == NULL) {}
    sampleSizeInByte = GuitarSori::getInstance()->getSampleSizeInBytes();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    GuitarSori::getInstance()->stopThread();
    GuitarSori::releaseInstance();
}
