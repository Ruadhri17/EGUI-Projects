/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLineEdit *name_recipe;
    QLabel *label_4;
    QDoubleSpinBox *quantity_ingredient;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *unit_ingredient;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_add;
    QPushButton *btn_edit;
    QPushButton *btn_delete;
    QLabel *label_5;
    QTextEdit *description;
    QLabel *label_3;
    QLineEdit *name_ingredient;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *btn_confirmation;
    QSpacerItem *horizontalSpacer_7;
    QTableView *table_of_ingredients;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(666, 666);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        name_recipe = new QLineEdit(Dialog);
        name_recipe->setObjectName(QString::fromUtf8("name_recipe"));

        gridLayout->addWidget(name_recipe, 0, 1, 1, 3);

        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        quantity_ingredient = new QDoubleSpinBox(Dialog);
        quantity_ingredient->setObjectName(QString::fromUtf8("quantity_ingredient"));
        quantity_ingredient->setDecimals(1);
        quantity_ingredient->setMaximum(1000000.000000000000000);

        gridLayout->addWidget(quantity_ingredient, 6, 1, 1, 1);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(904, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 3);

        unit_ingredient = new QLineEdit(Dialog);
        unit_ingredient->setObjectName(QString::fromUtf8("unit_ingredient"));

        gridLayout->addWidget(unit_ingredient, 7, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(692, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 6, 2, 1, 2);

        horizontalSpacer_6 = new QSpacerItem(339, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 7, 2, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(904, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 1, 1, 3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btn_add = new QPushButton(Dialog);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_add->sizePolicy().hasHeightForWidth());
        btn_add->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(btn_add);

        btn_edit = new QPushButton(Dialog);
        btn_edit->setObjectName(QString::fromUtf8("btn_edit"));
        sizePolicy.setHeightForWidth(btn_edit->sizePolicy().hasHeightForWidth());
        btn_edit->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(btn_edit);

        btn_delete = new QPushButton(Dialog);
        btn_delete->setObjectName(QString::fromUtf8("btn_delete"));
        sizePolicy.setHeightForWidth(btn_delete->sizePolicy().hasHeightForWidth());
        btn_delete->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(btn_delete);


        gridLayout->addLayout(horizontalLayout_3, 9, 0, 1, 2);

        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        description = new QTextEdit(Dialog);
        description->setObjectName(QString::fromUtf8("description"));
        description->setAutoFillBackground(false);
        description->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(description, 2, 0, 1, 4);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        name_ingredient = new QLineEdit(Dialog);
        name_ingredient->setObjectName(QString::fromUtf8("name_ingredient"));

        gridLayout->addWidget(name_ingredient, 5, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(339, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 5, 2, 1, 2);

        btn_confirmation = new QDialogButtonBox(Dialog);
        btn_confirmation->setObjectName(QString::fromUtf8("btn_confirmation"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_confirmation->sizePolicy().hasHeightForWidth());
        btn_confirmation->setSizePolicy(sizePolicy1);
        btn_confirmation->setContextMenuPolicy(Qt::DefaultContextMenu);
        btn_confirmation->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        btn_confirmation->setStandardButtons(QDialogButtonBox::Abort|QDialogButtonBox::Save);

        gridLayout->addWidget(btn_confirmation, 9, 3, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(590, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 9, 2, 1, 1);

        table_of_ingredients = new QTableView(Dialog);
        table_of_ingredients->setObjectName(QString::fromUtf8("table_of_ingredients"));
        table_of_ingredients->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_of_ingredients->setSelectionMode(QAbstractItemView::SingleSelection);
        table_of_ingredients->setSelectionBehavior(QAbstractItemView::SelectRows);

        gridLayout->addWidget(table_of_ingredients, 4, 0, 1, 4);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Recipe Creator", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "Unit:", nullptr));
        name_recipe->setText(QString());
        label_4->setText(QCoreApplication::translate("Dialog", "Name of Ingredient:", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Ingredients", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Description", nullptr));
        btn_add->setText(QCoreApplication::translate("Dialog", "Add", nullptr));
        btn_edit->setText(QCoreApplication::translate("Dialog", "Edit", nullptr));
        btn_delete->setText(QCoreApplication::translate("Dialog", "Delete", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "Quantity:", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "Name of recipe:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecipeEditor: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
