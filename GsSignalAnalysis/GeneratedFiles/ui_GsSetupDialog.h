/********************************************************************************
** Form generated from reading UI file 'GsSetupDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSSETUPDIALOG_H
#define UI_GSSETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_GsSetupDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QDialog *GsSetupDialog)
    {
        if (GsSetupDialog->objectName().isEmpty())
            GsSetupDialog->setObjectName(QStringLiteral("GsSetupDialog"));
        GsSetupDialog->resize(400, 303);
        buttonBox = new QDialogButtonBox(GsSetupDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        comboBox = new QComboBox(GsSetupDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(120, 30, 250, 25));
        label = new QLabel(GsSetupDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 80, 25));

        retranslateUi(GsSetupDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GsSetupDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GsSetupDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GsSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *GsSetupDialog)
    {
        GsSetupDialog->setWindowTitle(QApplication::translate("GsSetupDialog", "Setup...", 0));
        label->setText(QApplication::translate("GsSetupDialog", "Input Device", 0));
    } // retranslateUi

};

namespace Ui {
    class GsSetupDialog: public Ui_GsSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSSETUPDIALOG_H
