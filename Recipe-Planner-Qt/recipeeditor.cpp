#include "recipeeditor.h"
#include "ui_dialog.h"

RecipeEditor::RecipeEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipeEditor)
{
    ui->setupUi(this);
    ui->quantity_ingredient->setDecimals(2);
    number_of_elements_in_table = 0;
    QWidget *dialog_widget = new QWidget();
}

RecipeEditor::~RecipeEditor()
{
    delete ui;
}

void RecipeEditor::on_btn_confirmation_accepted()
{
    if(ui->name_recipe->text().isEmpty()) //prevent from saving the recipe if file name is empty
    {
        QMessageBox::critical(this, "Error", "Name of recipe cannot be empty!");
        return;
    }
    if(json_content.object().contains(ui->name_recipe->text())) //prevent from saving the recipe if there is recipe wit that name
    {
        QMessageBox::critical(this, "Error", "Recipe with this name already exists!");
        return;
    }
    QJsonObject description_container;
    QVariantMap merge_containers;
    QJsonObject temp_to_add_name;

    description_container.insert("recipe", QJsonArray::fromStringList(ui->description->toPlainText().split('\n',Qt::SkipEmptyParts))); //each line of description is single element in
    merge_containers = description_container.toVariantMap();
    merge_containers.insert(ingredient_info_container.toVariantMap());
    whole_recipe = QJsonObject::fromVariantMap(merge_containers);

    temp_to_add_name.insert(ui->name_recipe->text(), whole_recipe); //temp object to add name to whole recipe

    whole_recipe.swap(temp_to_add_name);
    save_to_json(file_name);

    emit dialog_closed();
    this->hide();

}
void RecipeEditor::on_btn_confirmation_rejected()
{
    emit rejected(); //if user abandon adding/editing object, emit signal (used especially in edition)
    this->hide();
}

void RecipeEditor::on_btn_add_clicked()
{
    if(ingredient_info_container.contains(ui->name_ingredient->text()))
    {
        QMessageBox::critical(this, "Error", "Given ingredient already exists!");
        return;
    }
    if(ui->name_ingredient->text() == "")
    {
        QMessageBox::critical(this, "Error", "Name field is empty!");
        return;
    }
    if(ui->quantity_ingredient->text() == "0")
    {
        QMessageBox::critical(this, "Error", "quantity cannot be equal 0!");
        return;
    }
    if(ui->unit_ingredient->text() == "")
    {
        QMessageBox::critical(this, "Error", "unit field is  empty!");
        return;
    }
    number_of_elements_in_table++;
    ingredient_info_container.insert(ui->name_ingredient->text(), ui->quantity_ingredient->text() + " " + ui->unit_ingredient->text()); // connect name quantity and value

    fill_table();

    ui->name_ingredient->clear();
    ui->quantity_ingredient->clear();
    ui->unit_ingredient->clear();
}

void RecipeEditor::on_btn_edit_clicked()
{
    if(ui->table_of_ingredients->rowHeight(0) == 0)
        {
            QMessageBox::critical(this, "Error", "There are no elements to be edited!");
            return;
        }
    QItemSelectionModel *user_selection = ui->table_of_ingredients->selectionModel();
    QModelIndexList selected_row = user_selection->selectedRows();

    if(selected_row.size() > 1)
    {
        QMessageBox::critical(this, "Error", "Please, choose only one ingredient to edit!");
        return;
    }
    else if(selected_row.size() == 0)
    {
        QMessageBox::critical(this, "Error", "No element was choosed to edit!");
        return;
    }
    ingredient_info_container.remove(table_model->takeItem(QModelIndex(selected_row.takeFirst()).row(),0)->text());
    ingredient_info_container.insert(ui->name_ingredient->text(), ui->quantity_ingredient->text() + " " + ui->unit_ingredient->text());
    fill_table();

    ui->name_ingredient->clear(); // clear values after edition
    ui->quantity_ingredient->clear();
    ui->unit_ingredient->clear();
}

void RecipeEditor::on_btn_delete_clicked()
{
    if(ui->table_of_ingredients->rowHeight(0) == 0)
        {
            QMessageBox::critical(this, "Error", "There are no elements to be removed!");
            return;
        }
    QItemSelectionModel *user_selection = ui->table_of_ingredients->selectionModel();
    QModelIndexList selected_row = user_selection->selectedRows();

    if(selected_row.size() > 1)
    {
        QMessageBox::critical(this, "Error", "Please, choose only one ingredient to delete!");
        return;
    }
    else if(selected_row.size() == 0)
    {
        QMessageBox::critical(this, "Error", "No element was choosed to delete!");
        return;
    }
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Deleting ingredient", "Are you sure you want to remove this ingredient?", QMessageBox::Yes | QMessageBox::No); //make sure user wants to delete object
    if(reply == QMessageBox::No)
        return;
    QString name_of_product_to_delete = table_model->takeItem(QModelIndex(selected_row.takeFirst()).row(),0)->text();
    ingredient_info_container.remove(name_of_product_to_delete);
    number_of_elements_in_table--;
    fill_table();
}

void RecipeEditor::fill_table()
{
    table_model = new QStandardItemModel(number_of_elements_in_table, 2, this); //model for table in editor dialog

    for(int row = 0; row < number_of_elements_in_table; row++)
    {
        for(int col = 0; col < 2; col++)
        {
            QModelIndex index = table_model->index(row, col, QModelIndex());
            if(col == 0)
                table_model->setData(index, ingredient_info_container.keys()[row]);
            else
                table_model->setData(index, ingredient_info_container.value(ingredient_info_container.keys()[row]));
        }
    }

    table_model->setHeaderData(0,Qt::Horizontal,"Name of Ingredient");
    table_model->setHeaderData(1,Qt::Horizontal,"Value");
    ui->table_of_ingredients->setModel(table_model);

    ui->table_of_ingredients->setColumnWidth(0,ui->table_of_ingredients->width()/2);
    ui->table_of_ingredients->setColumnWidth(1,ui->table_of_ingredients->width()/2);
    ui->table_of_ingredients->verticalHeader()->setVisible(false);
}

bool RecipeEditor::save_to_json(QString file_name) //fun. responsible for saving to json file
{
    QFile json_file;
    json_file.setFileName(file_name);
    if(!json_file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QMessageBox::critical(this, "error", "Unexpected error while opening the file!");
        return false;
    }
    QVariantMap merge = whole_recipe.toVariantMap();

    merge.insert(json_content.object().toVariantMap());
    json_file.write(QJsonDocument(QJsonObject::fromVariantMap(merge)).toJson());
    json_file.close();
    return true;
}

void RecipeEditor::on_table_of_ingredients_clicked(const QModelIndex &index) //fun. responsible for filling ingredient text boxes with value of edited ingredient
{
    ui->name_ingredient->setText(table_model->item(index.row(),0)->text());
    QString unit = table_model->item(index.row(),1)->text();
    QString quantity = unit.split(" ").at(0);
    unit.remove(0, quantity.length()+1);
    if(quantity.contains(','))
        ui->quantity_ingredient->setValue(QLocale::system().toDouble(quantity));
    else
        ui->quantity_ingredient->setValue(quantity.toDouble());
    ui->unit_ingredient->setText(unit);

}
void RecipeEditor::fill_window_during_edition(QString name_of_recipe) // fun. responsible for filling table and text boxes before showing the dialog of edited recipe
{
    QJsonObject all_recipes = json_content.object();
    whole_recipe = all_recipes.value(name_of_recipe).toObject();
    QJsonArray description = whole_recipe.value("recipe").toArray();
    QString description_to_string = "";
    for(auto itr = description.begin(); itr != description.end(); itr++)
    {
        description_to_string+=itr->toString() + "\n";
    }
    ui->name_recipe->setText(name_of_recipe);
    ui->description->setPlainText(description_to_string);
    for(auto itr  = whole_recipe.begin(); itr != whole_recipe.end(); itr++)
    {
        if(itr.key() != "recipe")
        {
            number_of_elements_in_table++;
            ingredient_info_container.insert(itr.key(),itr.value());
        }
    }
    this->show();
    fill_table();
}
