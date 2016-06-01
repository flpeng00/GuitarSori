#include "GsSignalAnalysis.h"
#include "../include/GuitarSori.h"

GsSignalAnalysis::GsSignalAnalysis(QWidget *parent)
	: QMainWindow(parent)
{
	GuitarSori::getInstance()->init(1024, 2, 4, 0x00000004, 44100);
	GuitarSori::getInstance()->runThread();
	ui.setupUi(this);

	//SignalThread *pThread = new SignalThread();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
	timer->start(5);
	//pThread->start();
}

GsSignalAnalysis::~GsSignalAnalysis()
{
	pThread->join();
	GuitarSori::getInstance()->stopThread();
	GuitarSori::releaseInstance();
}

void GsSignalAnalysis::onTimeOut()
{
	char *sampleBuffer;
	int sampleSize;
	sampleBuffer = GuitarSori::getInstance()->getSampleBuffer();
	sampleSize = GuitarSori::getInstance()->getSampleSizeInBytes() / sizeof(int);

	QVector<double> x(sampleSize), y(sampleSize); // initialize with entries 0..100
	for (int i = 0; i < sampleSize; i++)
	{
		x[i] = i;
		y[i] = (double)sampleBuffer[i];
	}

	ui.pwmGraph->xAxis->setRange(0, sampleSize);
	ui.pwmGraph->yAxis->setRange(-300, 300);
	ui.pwmGraph->graph(0)->setData(x, y);
	ui.pwmGraph->replot();
}
