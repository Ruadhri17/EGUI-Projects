/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_recipe_manager;
    QAction *action_exit;
    QAction *actionLoad_File;
    QWidget *centralwidget;
    QListView *list_of_recipe;
    QSplitter *splitter;
    QPushButton *btn_add;
    QPushButton *btn_delete;
    QPushButton *btn_edit;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(779, 606);
        action_recipe_manager = new QAction(MainWindow);
        action_recipe_manager->setObjectName(QString::fromUtf8("action_recipe_manager"));
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QString::fromUtf8("action_exit"));
        actionLoad_File = new QAction(MainWindow);
        actionLoad_File->setObjectName(QString::fromUtf8("actionLoad_File"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        list_of_recipe = new QListView(centralwidget);
        list_of_recipe->setObjectName(QString::fromUtf8("list_of_recipe"));
        list_of_recipe->setGeometry(QRect(11, 11, 761, 501));
        list_of_recipe->setEditTriggers(QAbstractItemView::NoEditTriggers);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(11, 516, 761, 28));
        splitter->setOrientation(Qt::Horizontal);
        btn_add = new QPushButton(splitter);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));
        splitter->addWidget(btn_add);
        btn_delete = new QPushButton(splitter);
        btn_delete->setObjectName(QString::fromUtf8("btn_delete"));
        splitter->addWidget(btn_delete);
        btn_edit = new QPushButton(splitter);
        btn_edit->setObjectName(QString::fromUtf8("btn_edit"));
        splitter->addWidget(btn_edit);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 779, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action_recipe_manager);
        menu->addAction(actionLoad_File);
        menu->addAction(action_exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Reciper v1.0", nullptr));
        action_recipe_manager->setText(QCoreApplication::translate("MainWindow", "Recipe Manager", nullptr));
        action_exit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionLoad_File->setText(QCoreApplication::translate("MainWindow", "Load File", nullptr));
        btn_add->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        btn_delete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        btn_edit->setText(QCoreApplication::translate("MainWindow", "Edit ", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
