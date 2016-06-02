/********************************************************************************
** Form generated from reading UI file 'GsSignalAnalysis.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSSIGNALANALYSIS_H
#define UI_GSSIGNALANALYSIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_GsSignalAnalysisClass
{
public:
    QWidget *centralWidget;
    QCustomPlot *pwmGraph;
	QCustomPlot *fftGraph;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GsSignalAnalysisClass)
    {
        if (GsSignalAnalysisClass->objectName().isEmpty())
            GsSignalAnalysisClass->setObjectName(QStringLiteral("GsSignalAnalysisClass"));
        GsSignalAnalysisClass->resize(1366, 768);
        centralWidget = new QWidget(GsSignalAnalysisClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pwmGraph = new QCustomPlot(centralWidget);
        pwmGraph->setObjectName(QStringLiteral("pwmGraph"));
        pwmGraph->setGeometry(QRect(10, 10, 1091, 361));
		pwmGraph->addGraph();
		fftGraph = new QCustomPlot(centralWidget);
		fftGraph->setObjectName(QStringLiteral("pwmGraph"));
		fftGraph->setGeometry(QRect(10, 380, 1091, 361));
		fftGraph->addGraph();
        GsSignalAnalysisClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GsSignalAnalysisClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GsSignalAnalysisClass->setStatusBar(statusBar);

        retranslateUi(GsSignalAnalysisClass);

        QMetaObject::connectSlotsByName(GsSignalAnalysisClass);
    } // setupUi

    void retranslateUi(QMainWindow *GsSignalAnalysisClass)
    {
        GsSignalAnalysisClass->setWindowTitle(QApplication::translate("GsSignalAnalysisClass", "GsSignalAnalysis", 0));
    } // retranslateUi

};

namespace Ui {
    class GsSignalAnalysisClass: public Ui_GsSignalAnalysisClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSSIGNALANALYSIS_H
