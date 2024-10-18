/********************************************************************************
** Form generated from reading UI file 'task_one.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_ONE_H
#define UI_TASK_ONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_task_one
{
public:
    QLabel *label_task;
    QLabel *label;
    QPushButton *pushButton_return;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *lineEditMessage;
    QLabel *labelFilePath;
    QLabel *labelMessage;
    QLineEdit *lineEditFilePath;
    QPushButton *pushButton_send;
    QLabel *labelMessageServ;

    void setupUi(QWidget *task_one)
    {
        if (task_one->objectName().isEmpty())
            task_one->setObjectName("task_one");
        task_one->resize(600, 400);
        task_one->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 255, 243);"));
        label_task = new QLabel(task_one);
        label_task->setObjectName("label_task");
        label_task->setGeometry(QRect(20, 10, 121, 21));
        label_task->setStyleSheet(QString::fromUtf8("\n"
"font: 300 9pt \"Yu Gothic UI Light\";"));
        label = new QLabel(task_one);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 340, 141, 20));
        pushButton_return = new QPushButton(task_one);
        pushButton_return->setObjectName("pushButton_return");
        pushButton_return->setGeometry(QRect(20, 240, 131, 31));
        pushButton_return->setStyleSheet(QString::fromUtf8("background-color: rgb(39, 39, 39);\n"
"color: rgb(255, 255, 255);\n"
"font: 300 9pt \"Yu Gothic UI Light\";"));
        verticalLayoutWidget = new QWidget(task_one);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 40, 351, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lineEditMessage = new QLineEdit(verticalLayoutWidget);
        lineEditMessage->setObjectName("lineEditMessage");
        lineEditMessage->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"	border: 1px solid rgb(39,39,39);\n"
"	border-radius: 550px;\n"
"	background-color: rgb(255,255,255);\n"
"}\n"
""));

        gridLayout->addWidget(lineEditMessage, 0, 1, 1, 1);

        labelFilePath = new QLabel(verticalLayoutWidget);
        labelFilePath->setObjectName("labelFilePath");

        gridLayout->addWidget(labelFilePath, 1, 0, 1, 1);

        labelMessage = new QLabel(verticalLayoutWidget);
        labelMessage->setObjectName("labelMessage");

        gridLayout->addWidget(labelMessage, 0, 0, 1, 1);

        lineEditFilePath = new QLineEdit(verticalLayoutWidget);
        lineEditFilePath->setObjectName("lineEditFilePath");
        lineEditFilePath->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"	border: 1px solid rgb(39,39,39);\n"
"	border-radius: 550px;\n"
"	background-color: rgb(255,255,255);\n"
"}\n"
""));

        gridLayout->addWidget(lineEditFilePath, 1, 1, 1, 1);

        pushButton_send = new QPushButton(verticalLayoutWidget);
        pushButton_send->setObjectName("pushButton_send");
        pushButton_send->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_send->setStyleSheet(QString::fromUtf8("background-color: rgb(39, 39, 39);\n"
"color: rgb(255, 255, 255);\n"
"font: 300 9pt \"Yu Gothic UI Light\";"));

        gridLayout->addWidget(pushButton_send, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        labelMessageServ = new QLabel(task_one);
        labelMessageServ->setObjectName("labelMessageServ");
        labelMessageServ->setGeometry(QRect(170, 310, 411, 61));

        retranslateUi(task_one);

        QMetaObject::connectSlotsByName(task_one);
    } // setupUi

    void retranslateUi(QWidget *task_one)
    {
        task_one->setWindowTitle(QCoreApplication::translate("task_one", "Form", nullptr));
        label_task->setText(QCoreApplication::translate("task_one", "TextLabel", nullptr));
        label->setText(QString());
        pushButton_return->setText(QCoreApplication::translate("task_one", "Return to menu", nullptr));
        labelFilePath->setText(QCoreApplication::translate("task_one", "File Path", nullptr));
        labelMessage->setText(QCoreApplication::translate("task_one", "Message", nullptr));
        pushButton_send->setText(QCoreApplication::translate("task_one", "Send", nullptr));
        labelMessageServ->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class task_one: public Ui_task_one {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_ONE_H
