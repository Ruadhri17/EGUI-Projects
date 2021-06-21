#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QWidget>
namespace Ui {
class RecipeEditor;
}

class RecipeEditor : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeEditor(QWidget *parent = nullptr);
    ~RecipeEditor();
    void fill_window_during_edition(QString name_of_recipe);
    QJsonDocument json_content;
    QString file_name;

private slots:
    void on_btn_confirmation_accepted();
    void on_btn_confirmation_rejected();
    void on_btn_add_clicked();
    void on_btn_edit_clicked();
    void on_btn_delete_clicked();
    void on_table_of_ingredients_clicked(const QModelIndex &index);

private:
    Ui::RecipeEditor *ui;

    int number_of_elements_in_table;

    QStandardItemModel *table_model;
    QJsonObject ingredient_info_container;
    QJsonObject whole_recipe;

    void fill_table();
    bool save_to_json(QString file_name);

signals:
    void dialog_closed();
};

#endif // DIALOG_H
