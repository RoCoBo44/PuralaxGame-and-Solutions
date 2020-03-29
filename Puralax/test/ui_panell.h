/********************************************************************************
** Form generated from reading UI file 'panell.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELL_H
#define UI_PANELL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Panell
{
public:

    void setupUi(QWidget *Panell)
    {
        if (Panell->objectName().isEmpty())
            Panell->setObjectName(QStringLiteral("Panell"));
        Panell->resize(400, 300);

        retranslateUi(Panell);

        QMetaObject::connectSlotsByName(Panell);
    } // setupUi

    void retranslateUi(QWidget *Panell)
    {
        Panell->setWindowTitle(QApplication::translate("Panell", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Panell: public Ui_Panell {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELL_H
