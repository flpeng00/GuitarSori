#pragma once

#include <QDialog>
#include "ui_GsSetupDialog.h"

class GsSetupDialog : public QDialog
{
private:
	Ui::GsSetupDialog ui;

public:
	GsSetupDialog(QWidget *parent = 0);
	~GsSetupDialog();
};