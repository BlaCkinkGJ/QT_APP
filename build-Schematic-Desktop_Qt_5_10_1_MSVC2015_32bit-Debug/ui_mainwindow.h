/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *EnterButton;
    QGraphicsView *graphicsView;
    QPushButton *ResetButton;
    QListView *FurnitureList;
    QLabel *label_4;
    QPushButton *save;
    QPushButton *open;
    QPushButton *extraction;
    QPushButton *exit_2;
    QLabel *alertLabel;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1396, 782);
        MainWindow->setMaximumSize(QSize(1920, 1080));
        MainWindow->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 361, 21));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(1920, 1080));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 91, 31));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(1920, 1080));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 100, 91, 31));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMaximumSize(QSize(1920, 1080));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 50, 111, 31));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMaximumSize(QSize(1920, 1080));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(110, 100, 111, 31));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setMaximumSize(QSize(1920, 1080));
        EnterButton = new QPushButton(centralWidget);
        EnterButton->setObjectName(QStringLiteral("EnterButton"));
        EnterButton->setGeometry(QRect(250, 70, 71, 31));
        sizePolicy.setHeightForWidth(EnterButton->sizePolicy().hasHeightForWidth());
        EnterButton->setSizePolicy(sizePolicy);
        EnterButton->setMaximumSize(QSize(1920, 1080));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(240, 130, 800, 600));
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMaximumSize(QSize(800, 600));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
        ResetButton = new QPushButton(centralWidget);
        ResetButton->setObjectName(QStringLiteral("ResetButton"));
        ResetButton->setGeometry(QRect(340, 70, 71, 31));
        sizePolicy.setHeightForWidth(ResetButton->sizePolicy().hasHeightForWidth());
        ResetButton->setSizePolicy(sizePolicy);
        ResetButton->setMaximumSize(QSize(1920, 1080));
        FurnitureList = new QListView(centralWidget);
        FurnitureList->setObjectName(QStringLiteral("FurnitureList"));
        FurnitureList->setGeometry(QRect(30, 190, 181, 171));
        sizePolicy.setHeightForWidth(FurnitureList->sizePolicy().hasHeightForWidth());
        FurnitureList->setSizePolicy(sizePolicy);
        FurnitureList->setMaximumSize(QSize(1920, 1080));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 150, 121, 31));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMaximumSize(QSize(1920, 1080));
        label_4->setAlignment(Qt::AlignCenter);
        save = new QPushButton(centralWidget);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(70, 410, 100, 23));
        open = new QPushButton(centralWidget);
        open->setObjectName(QStringLiteral("open"));
        open->setGeometry(QRect(70, 450, 100, 23));
        extraction = new QPushButton(centralWidget);
        extraction->setObjectName(QStringLiteral("extraction"));
        extraction->setGeometry(QRect(70, 490, 100, 23));
        exit_2 = new QPushButton(centralWidget);
        exit_2->setObjectName(QStringLiteral("exit_2"));
        exit_2->setGeometry(QRect(70, 530, 100, 23));
        alertLabel = new QLabel(centralWidget);
        alertLabel->setObjectName(QStringLiteral("alertLabel"));
        alertLabel->setGeometry(QRect(430, 70, 441, 41));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(1150, 130, 221, 601));
        listWidget_2 = new QListWidget(centralWidget);
        QBrush brush(QColor(255, 153, 128, 255));
        brush.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem->setBackground(brush);
        QBrush brush1(QColor(251, 231, 178, 255));
        brush1.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem1->setBackground(brush1);
        __qlistwidgetitem1->setForeground(brush1);
        QBrush brush2(QColor(241, 231, 136, 255));
        brush2.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem2->setBackground(brush2);
        QBrush brush3(QColor(175, 227, 19, 255));
        brush3.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem3->setBackground(brush3);
        QBrush brush4(QColor(252, 128, 165, 255));
        brush4.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem4->setBackground(brush4);
        QBrush brush5(QColor(157, 224, 47, 255));
        brush5.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem5->setBackground(brush5);
        QBrush brush6(QColor(147, 223, 184, 255));
        brush6.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem6->setBackground(brush6);
        QBrush brush7(QColor(0, 204, 153, 255));
        brush7.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem7->setBackground(brush7);
        QBrush brush8(QColor(147, 204, 143, 255));
        brush8.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem8 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem8->setBackground(brush8);
        QBrush brush9(QColor(118, 110, 200, 255));
        brush9.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem9 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem9->setBackground(brush9);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(1070, 130, 81, 601));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1396, 17));
        MainWindow->setMenuBar(menuBar);
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "Input width and heigth of your house.", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Width(M)", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Height(M)", nullptr));
        EnterButton->setText(QApplication::translate("MainWindow", "Enter", nullptr));
        ResetButton->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Furniture List", nullptr));
        save->setText(QApplication::translate("MainWindow", "save", nullptr));
        open->setText(QApplication::translate("MainWindow", "open", nullptr));
        extraction->setText(QApplication::translate("MainWindow", "extraction", nullptr));
        exit_2->setText(QApplication::translate("MainWindow", "exit", nullptr));
        alertLabel->setText(QString());

        const bool __sortingEnabled = listWidget_2->isSortingEnabled();
        listWidget_2->setSortingEnabled(false);
        listWidget_2->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
