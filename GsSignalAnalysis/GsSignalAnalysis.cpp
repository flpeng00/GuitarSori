#include "GsSignalAnalysis.h"
#include "../include/GuitarSori.h"

GsSignalAnalysis::GsSignalAnalysis(QWidget *parent)
	: QMainWindow(parent)
{
	GuitarSori::getInstance()->init(2048, 2, 4, paFloat32, 44100);
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
	float *sampleBuffer;
	double *fftBuffer;
	int sampleSize;
	sampleBuffer = (float *)GuitarSori::getInstance()->getSampleBuffer();
	sampleSize = GuitarSori::getInstance()->getSampleSizeInBytes() / 4;

	QVector<double> x(sampleSize), y(sampleSize); // initialize with entries 0..100
	for (int i = 0; i < sampleSize; i++)
	{
		x[i] = i;
		y[i] = (double)sampleBuffer[i];
	}

	ui.pwmGraph->xAxis->setRange(0, sampleSize);
	ui.pwmGraph->yAxis->setRange(-1, 1);
	ui.pwmGraph->graph(0)->setData(x, y);
	ui.pwmGraph->replot();

	fftBuffer = GuitarSori::getInstance()->getSampleBufferFFT();

	for (int i = 0; i < sampleSize / 2; i++)
	{
		x[i] = i;
		y[i] = fftBuffer[i];
	}

	ui.fftGraph->xAxis->setRange(0, sampleSize / 2);
	ui.fftGraph->yAxis->setRange(0, 10);
	ui.fftGraph->graph(0)->setData(x, y);
	ui.fftGraph->replot();
}
