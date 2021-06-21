#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QWidget *wdg = new QWidget(this);
    //QPushButton *asterix_button = new QPushButton(wdg);
    //asterix_button->setText("Add *");
    //asterix_button->clicked();
    //setCentralWidget(wdg);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_add_clicked()
{
    if(file_name.isEmpty())
    {
        QMessageBox::critical(this, "Error", "First you must load a file!");
        return;
    }
    RecipeEditor *add_dialog = new RecipeEditor();
    add_dialog->json_content = json_content;
    add_dialog->file_name = file_name;
    add_dialog->show();
    connect(add_dialog, SIGNAL(dialog_closed()), this, SLOT(reload_table()));
}

void MainWindow::on_btn_edit_clicked()
{
    if(file_name.isEmpty()) //if file was not loaded, prevent from clicking edit button.
    {
        QMessageBox::critical(this, "Error", "First you must load a file!");
        return;
    }
    QItemSelectionModel *user_selection = ui->list_of_recipe->selectionModel(); //creating a model of selection one of the recipes
    QModelIndexList selected_row = user_selection->selectedRows();
    QVariant name_of_recipe;

    if(selected_row.size() > 1) //if more than one row was selected, display error
    {
        QMessageBox::critical(this, "Error", "Please select only one row!");
        return;
    }
    else if(selected_row.size() == 0)
    {
        QMessageBox::critical(this, "Error", "Please select recipe you want to edit!"); // if recipe was not choosed, display error
        return;
    }
    name_of_recipe = selected_row.takeFirst().data();
    RecipeEditor *edit_dialog = new RecipeEditor(); //create a dialog for edition

    edit_dialog->json_content = json_content;
    edit_dialog->file_name = file_name;
    edit_dialog->fill_window_during_edition(name_of_recipe.toString());
    json_copy = json_content; //make a copy of json content in case user decide to abandon edition
    QJsonObject to_remove = json_content.object();
    to_remove.remove(name_of_recipe.toString());
    json_content = QJsonDocument(to_remove);
    save_to_json(file_name);
    edit_dialog->json_content = json_content;
    connect(edit_dialog, SIGNAL(dialog_closed()), this, SLOT(reload_table()));
    connect(edit_dialog, SIGNAL(rejected()), this, SLOT(restore_value()));
}

void MainWindow::on_btn_delete_clicked()
{
    if(file_name.isEmpty()) //check if file was loaded
    {
        QMessageBox::critical(this, "Error", "First you must load a file!");
        return;
    }
    QItemSelectionModel *user_selection = ui->list_of_recipe->selectionModel(); //creating a model of selection one of the recipes
    QModelIndexList selected_row = user_selection->selectedRows();
    QVariant name_of_recipe;

    if(selected_row.size() > 1) // if more than one recipe was chosen, display error
    {
        QMessageBox::critical(this, "Error", "Please select only one row!");
        return;
    }
    else if(selected_row.size() == 0) // if none of recipe was chosen, display error
    {
        QMessageBox::critical(this, "Error", "Please select recipe you want to delete!");
        return;
    }
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Deleting Recipe", "Are you sure you want to remove this recipe?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::No)
        return;
    name_of_recipe = selected_row.takeFirst().data();
    QJsonObject to_remove = json_content.object(); //removal of object which is single recipe in that case
    to_remove.remove(name_of_recipe.toString());
    json_content = QJsonDocument(to_remove);
    save_to_json(file_name);
    fill_main_list();
}

bool MainWindow::read_json(QString file_name) //fun. responsible for reading from json file
{
    QFile json_file;
    json_file.setFileName(file_name);
    if(!json_file.open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(this, "Error", "Unexpeced error while opening the file!");
        return false;
    }
    QByteArray json_content_in_byte_array = json_file.readAll();
    json_file.close();
    json_content = QJsonDocument::fromJson(json_content_in_byte_array);
    if (json_content.isNull())
    {
        QMessageBox::critical(this, "Error", "Unexpeced error while importing the JSON!");
        return false;
    }

    return true;
}

void MainWindow::fill_main_list() // fun responsible for filling main menu recipe list
{
    recipe_names = new QStringListModel();
    QStringList list_of_recipes;

    if(json_content.isObject())
    {
        QJsonObject json_recipe_names = json_content.object();
        QJsonObject::Iterator recipe = json_recipe_names.begin();
        while(recipe!=json_recipe_names.end()) //fill list with all recipes
        {
            list_of_recipes.push_back(recipe.key());
            recipe++;
        }
    }
    recipe_names->setStringList(list_of_recipes);
    ui->list_of_recipe->setModel(recipe_names);

}

void MainWindow::reload_table() //in case of any changes in recipes, reload table
{
    read_json(file_name);
    fill_main_list();
}

bool MainWindow::save_to_json(QString file_name) //save to json if any changes were made in recipes
{
    QFile json_file;
    json_file.setFileName(file_name);
    if(!json_file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Unexpeced error while opening the file!");
        return false;
    }
    json_file.write(json_content.toJson());
    json_file.close();

    return true;
}
void MainWindow::restore_value() //back up copy of recipes if user abandon edition window
{
    json_content = json_copy;
    save_to_json(file_name);
}

void MainWindow::on_action_exit_triggered()
{
    exit(0);
}

void MainWindow::on_action_recipe_manager_triggered() // triggered if user wants to open recipe manager
{
    if(file_name.isEmpty())
    {
        QMessageBox::critical(this, "Error", "First you must load a file!");
        return;
    }
    RecipeManager *manager_dialog = new RecipeManager();
    read_json(file_name);
    manager_dialog->json_content = json_content; //pass all recipes details to manager dialog
    manager_dialog->fill_all_recipes();
    manager_dialog->show();

}

void MainWindow::on_actionLoad_File_triggered() //triggered when user wants to load file
{
    if(!file_name.isEmpty()) //if file was already loaded you cannot
    {
        QMessageBox::critical(this, "Error", "You already loaded file!");
        return;
    }
    file_name = QFileDialog::getOpenFileName(this, tr("Load Json File"), "", tr("Json File (*.json)")); //looking for files only with .json extension
    if(read_json(file_name))
        fill_main_list();
}
