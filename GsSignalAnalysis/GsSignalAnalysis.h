#ifndef GSSIGNALANALYSIS_H
#define GSSIGNALANALYSIS_H

#include <QtWidgets/QMainWindow>
#include "ui_GsSignalAnalysis.h"
#include "../include/GuitarSori.h"

class GsSignalAnalysis : public QMainWindow
{
	Q_OBJECT

private:
	Ui::GsSignalAnalysisClass ui;
	int* sampleBuffer;
	int sampleSizeInByte;
	std::thread *pThread;
	static void refrash( LPVOID param );

public:
	GsSignalAnalysis(QWidget *parent = 0);
	~GsSignalAnalysis();

public slots:
	void onTimeOut();
};


/*
class SignalThread : public QThread
{
	Q_OBJECT

public:
	void run();

signals:
	void signalReceive(char *sampleBuffer, int sampleSize);
};
*/

#endif // GSSIGNALANALYSIS_H
