/********************************************************************************
** Form generated from reading UI file 'secondarywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDARYWINDOW_H
#define UI_SECONDARYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SecondaryWindow
{
public:

    void setupUi(QWidget *SecondaryWindow)
    {
        if (SecondaryWindow->objectName().isEmpty())
            SecondaryWindow->setObjectName(QStringLiteral("SecondaryWindow"));
        SecondaryWindow->resize(400, 300);

        retranslateUi(SecondaryWindow);

        QMetaObject::connectSlotsByName(SecondaryWindow);
    } // setupUi

    void retranslateUi(QWidget *SecondaryWindow)
    {
        SecondaryWindow->setWindowTitle(QApplication::translate("SecondaryWindow", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SecondaryWindow: public Ui_SecondaryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDARYWINDOW_H
