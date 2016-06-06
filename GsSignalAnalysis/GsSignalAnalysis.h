#ifndef GSSIGNALANALYSIS_H
#define GSSIGNALANALYSIS_H

#include <QtWidgets/QMainWindow>
#include "ui_GsSignalAnalysis.h"
#include "GsSetupDialog.h"
#include "../include/GuitarSori.h"

class GsSignalAnalysis : public QMainWindow
{
	Q_OBJECT

private:
	Ui::GsSignalAnalysisClass ui;
	int* sampleBuffer;
	int sampleSizeInByte;
	QTimer *timer;
	QAction *actionSetup;
	static void refrash( LPVOID param );

public:
	GsSignalAnalysis(QWidget *parent = 0);
	~GsSignalAnalysis();

public slots:
	void onTimeOut();
	void showSetupDlg();
};

#endif // GSSIGNALANALYSIS_H
