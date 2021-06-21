#ifndef RECIPEMANAGER_H
#define RECIPEMANAGER_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>

namespace Ui {
class RecipeManager;
}

class RecipeManager : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeManager(QWidget *parent = nullptr);
    ~RecipeManager();
    QJsonDocument json_content;
    void fill_all_recipes();
private slots:
    void on_btn_add_clicked();
    void on_btn_delete_clicked();

    void on_btn_leave_clicked();

private:
    Ui::RecipeManager *ui;

    QStringListModel *recipe_names;
    QStringListModel *ingredient_names;

    QStringList list_of_recipes;
    QStringList user_recipes;
    QStringList user_ingredients;

    void duplicated_data(QString name, QString value, QString unit, QString index);
    void removes_duplicated_data(QString name, QString value, QString unit, QString index);
};

#endif // RECIPEMANAGER_H
