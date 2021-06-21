#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include "recipeeditor.h"
#include "recipemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QJsonDocument json_content;
    QJsonDocument json_copy;
    QString file_name;
private slots:
    void on_btn_edit_clicked();
    void on_btn_add_clicked();
    void on_btn_delete_clicked();
    void reload_table();
    void restore_value();
    void on_action_exit_triggered();
    void on_action_recipe_manager_triggered();

    void on_actionLoad_File_triggered();

private:
    Ui::MainWindow *ui;
    QStringListModel *recipe_names;
    bool read_json(QString file_name);
    void fill_main_list();
    bool save_to_json(QString file_name);


};
#endif // MAINWINDOW_H
