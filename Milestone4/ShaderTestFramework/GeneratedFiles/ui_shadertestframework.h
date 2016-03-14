/********************************************************************************
** Form generated from reading UI file 'shadertestframework.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHADERTESTFRAMEWORK_H
#define UI_SHADERTESTFRAMEWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "my_openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_ShaderTestFrameworkClass
{
public:
    QAction *actionLoad_Shaders;
    QAction *actionSave_Shaders;
    QAction *actionExit;
    QWidget *centralWidget;
    My_OpenGLWidget *graphicDisplay;
    QPushButton *updateButton;
    QLabel *label;
    QLabel *label_2;
    QPlainTextEdit *vertText;
    QPlainTextEdit *fragText;
    QPushButton *downButton;
    QPushButton *leftButton;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *ShaderTestFrameworkClass)
    {
        if (ShaderTestFrameworkClass->objectName().isEmpty())
            ShaderTestFrameworkClass->setObjectName(QStringLiteral("ShaderTestFrameworkClass"));
        ShaderTestFrameworkClass->resize(1180, 612);
        actionLoad_Shaders = new QAction(ShaderTestFrameworkClass);
        actionLoad_Shaders->setObjectName(QStringLiteral("actionLoad_Shaders"));
        actionSave_Shaders = new QAction(ShaderTestFrameworkClass);
        actionSave_Shaders->setObjectName(QStringLiteral("actionSave_Shaders"));
        actionExit = new QAction(ShaderTestFrameworkClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(ShaderTestFrameworkClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicDisplay = new My_OpenGLWidget(centralWidget);
        graphicDisplay->setObjectName(QStringLiteral("graphicDisplay"));
        graphicDisplay->setGeometry(QRect(10, 10, 751, 571));
        updateButton = new QPushButton(centralWidget);
        updateButton->setObjectName(QStringLiteral("updateButton"));
        updateButton->setGeometry(QRect(900, 540, 141, 41));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(930, 10, 151, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(930, 240, 151, 16));
        vertText = new QPlainTextEdit(centralWidget);
        vertText->setObjectName(QStringLiteral("vertText"));
        vertText->setGeometry(QRect(780, 30, 391, 201));
        vertText->setLineWrapMode(QPlainTextEdit::NoWrap);
        fragText = new QPlainTextEdit(centralWidget);
        fragText->setObjectName(QStringLiteral("fragText"));
        fragText->setGeometry(QRect(780, 260, 391, 271));
        fragText->setLineWrapMode(QPlainTextEdit::NoWrap);
        downButton = new QPushButton(centralWidget);
        downButton->setObjectName(QStringLiteral("downButton"));
        downButton->setGeometry(QRect(1070, 540, 101, 41));
        leftButton = new QPushButton(centralWidget);
        leftButton->setObjectName(QStringLiteral("leftButton"));
        leftButton->setGeometry(QRect(780, 540, 91, 41));
        ShaderTestFrameworkClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ShaderTestFrameworkClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1180, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        ShaderTestFrameworkClass->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad_Shaders);
        menuFile->addAction(actionSave_Shaders);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(ShaderTestFrameworkClass);
        QObject::connect(updateButton, SIGNAL(clicked()), ShaderTestFrameworkClass, SLOT(updateShaders()));
        QObject::connect(leftButton, SIGNAL(clicked()), graphicDisplay, SLOT(rotateLeft()));
        QObject::connect(downButton, SIGNAL(clicked()), graphicDisplay, SLOT(rotateDown()));
        QObject::connect(actionExit, SIGNAL(triggered()), ShaderTestFrameworkClass, SLOT(close()));
        QObject::connect(actionLoad_Shaders, SIGNAL(triggered()), ShaderTestFrameworkClass, SLOT(loadShaders()));
        QObject::connect(actionSave_Shaders, SIGNAL(triggered()), ShaderTestFrameworkClass, SLOT(saveShaders()));

        QMetaObject::connectSlotsByName(ShaderTestFrameworkClass);
    } // setupUi

    void retranslateUi(QMainWindow *ShaderTestFrameworkClass)
    {
        ShaderTestFrameworkClass->setWindowTitle(QApplication::translate("ShaderTestFrameworkClass", "ShaderTestFramework", 0));
        actionLoad_Shaders->setText(QApplication::translate("ShaderTestFrameworkClass", "Load Shaders...", 0));
        actionSave_Shaders->setText(QApplication::translate("ShaderTestFrameworkClass", "Save Shaders...", 0));
        actionExit->setText(QApplication::translate("ShaderTestFrameworkClass", "Exit", 0));
        updateButton->setText(QApplication::translate("ShaderTestFrameworkClass", "Update Shaders", 0));
        label->setText(QApplication::translate("ShaderTestFrameworkClass", "Vertex Shader", 0));
        label_2->setText(QApplication::translate("ShaderTestFrameworkClass", "Fragment Shader", 0));
        downButton->setText(QApplication::translate("ShaderTestFrameworkClass", "Rotate Down", 0));
        leftButton->setText(QApplication::translate("ShaderTestFrameworkClass", "Rotate Left", 0));
        menuFile->setTitle(QApplication::translate("ShaderTestFrameworkClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class ShaderTestFrameworkClass: public Ui_ShaderTestFrameworkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADERTESTFRAMEWORK_H
