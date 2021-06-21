/********************************************************************************
** Form generated from reading UI file 'recipemanager.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECIPEMANAGER_H
#define UI_RECIPEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_RecipeManager
{
public:
    QGridLayout *gridLayout;
    QListView *list_all_recipes;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QListView *list_user_recipes;
    QLabel *label;
    QPushButton *btn_add;
    QPushButton *btn_delete;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QListView *list_ingredients;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btn_leave;

    void setupUi(QDialog *RecipeManager)
    {
        if (RecipeManager->objectName().isEmpty())
            RecipeManager->setObjectName(QString::fromUtf8("RecipeManager"));
        RecipeManager->resize(914, 722);
        gridLayout = new QGridLayout(RecipeManager);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        list_all_recipes = new QListView(RecipeManager);
        list_all_recipes->setObjectName(QString::fromUtf8("list_all_recipes"));

        gridLayout->addWidget(list_all_recipes, 0, 0, 6, 1);

        horizontalSpacer = new QSpacerItem(124, 348, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 6, 1);

        verticalSpacer_2 = new QSpacerItem(108, 120, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(123, 358, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 6, 1);

        list_user_recipes = new QListView(RecipeManager);
        list_user_recipes->setObjectName(QString::fromUtf8("list_user_recipes"));

        gridLayout->addWidget(list_user_recipes, 0, 4, 6, 2);

        label = new QLabel(RecipeManager);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 2, 1, 1);

        btn_add = new QPushButton(RecipeManager);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));

        gridLayout->addWidget(btn_add, 2, 2, 1, 1);

        btn_delete = new QPushButton(RecipeManager);
        btn_delete->setObjectName(QString::fromUtf8("btn_delete"));

        gridLayout->addWidget(btn_delete, 3, 2, 1, 1);

        label_2 = new QLabel(RecipeManager);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 2, 1, 1);

        verticalSpacer = new QSpacerItem(108, 120, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(889, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 6, 0, 1, 6);

        label_3 = new QLabel(RecipeManager);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 7, 0, 1, 1);

        list_ingredients = new QListView(RecipeManager);
        list_ingredients->setObjectName(QString::fromUtf8("list_ingredients"));

        gridLayout->addWidget(list_ingredients, 8, 0, 1, 6);

        horizontalSpacer_4 = new QSpacerItem(762, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 9, 0, 1, 5);

        btn_leave = new QPushButton(RecipeManager);
        btn_leave->setObjectName(QString::fromUtf8("btn_leave"));

        gridLayout->addWidget(btn_leave, 9, 5, 1, 1);


        retranslateUi(RecipeManager);

        QMetaObject::connectSlotsByName(RecipeManager);
    } // setupUi

    void retranslateUi(QDialog *RecipeManager)
    {
        RecipeManager->setWindowTitle(QCoreApplication::translate("RecipeManager", "Recipe Manager", nullptr));
        label->setText(QCoreApplication::translate("RecipeManager", "<html><head/><body><p align=\"center\">ADD</p></body></html>", nullptr));
        btn_add->setText(QCoreApplication::translate("RecipeManager", ">>>>>>>>", nullptr));
        btn_delete->setText(QCoreApplication::translate("RecipeManager", "<<<<<<<<", nullptr));
        label_2->setText(QCoreApplication::translate("RecipeManager", "<html><head/><body><p align=\"center\">DELETE</p><p align=\"center\"><br/></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("RecipeManager", "Ingredients", nullptr));
        btn_leave->setText(QCoreApplication::translate("RecipeManager", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecipeManager: public Ui_RecipeManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECIPEMANAGER_H
