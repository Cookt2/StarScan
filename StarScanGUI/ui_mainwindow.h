/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label;
    QLabel *label_2;
    QProgressBar *progressBar;
    QLabel *label_3;
    QFrame *line_2;
    QFrame *line_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 283);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(600, 283));
        MainWindow->setMaximumSize(QSize(600, 283));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(600, 243));
        centralWidget->setMaximumSize(QSize(600, 243));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(330, 490, 61, 41));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(500, 200, 81, 31));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(420, 70, 160, 22));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(35);
        horizontalSlider->setValue(20);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(420, 110, 160, 22));
        horizontalSlider_2->setMinimum(20);
        horizontalSlider_2->setMaximum(240);
        horizontalSlider_2->setValue(125);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(360, 70, 48, 24));
        spinBox->setMinimum(1);
        spinBox->setMaximum(35);
        spinBox->setValue(20);
        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(360, 110, 48, 24));
        spinBox_2->setMinimum(20);
        spinBox_2->setMaximum(240);
        spinBox_2->setValue(125);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(440, 50, 151, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(400, 10, 151, 31));
        QFont font;
        font.setPointSize(16);
        label_2->setFont(font);
        label_2->setFrameShape(QFrame::Box);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 190, 471, 51));
        progressBar->setValue(0);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(440, 90, 121, 20));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(330, 0, 20, 191));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 180, 601, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 80, 311, 21));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 50, 161, 20));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(480, 150, 101, 20));
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(360, 150, 101, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 120, 181, 20));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 150, 311, 21));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 10, 311, 31));
        QFont font1;
        font1.setPointSize(18);
        font1.setItalic(true);
        font1.setUnderline(false);
        label_6->setFont(font1);
        label_6->setLayoutDirection(Qt::LeftToRight);
        label_6->setAutoFillBackground(false);
        label_6->setFrameShape(QFrame::NoFrame);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 220, 311, 16));
        QFont font2;
        font2.setItalic(true);
        label_7->setFont(font2);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(240, 50, 81, 31));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(240, 120, 81, 31));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "StarScan", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Scan", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Scan", 0));
        label->setText(QApplication::translate("MainWindow", "Constellation Restrction", 0));
        label_2->setText(QApplication::translate("MainWindow", "Advanced Settings", 0));
        label_3->setText(QApplication::translate("MainWindow", "Star Restriction", 0));
        label_4->setText(QApplication::translate("MainWindow", "Input Image file location:", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Visual Mode", 0));
        checkBox_2->setText(QApplication::translate("MainWindow", "Debug Mode", 0));
        label_5->setText(QApplication::translate("MainWindow", "Output image file location:", 0));
        label_6->setText(QApplication::translate("MainWindow", "StarScan Version 1.0 by Taylor Cook", 0));
        label_7->setText(QApplication::translate("MainWindow", "waiting...", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Search", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Search", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
