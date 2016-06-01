#include "GsSignalAnalysis.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GsSignalAnalysis w;
	w.show();
	return a.exec();
}
