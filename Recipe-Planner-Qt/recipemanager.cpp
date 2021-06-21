#include "recipemanager.h"
#include "ui_recipemanager.h"

RecipeManager::RecipeManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipeManager)
{
    ui->setupUi(this);
}

RecipeManager::~RecipeManager()
{
    delete ui;
}

void RecipeManager::on_btn_add_clicked()
{
    QItemSelectionModel *user_selection = ui->list_all_recipes->selectionModel(); //standard beginning like in previous dialogues
    QModelIndexList selected_row = user_selection->selectedRows();
    QVariant name_of_recipe;

    if(selected_row.size() > 1)
    {
        QMessageBox::critical(this, "Error", "You can choose only one recipe at the time");
        return;
    }
    else if(selected_row.size() == 0)
    {
        QMessageBox::critical(this, "Error", "No recipe was selected");
        return;
    }
    name_of_recipe = selected_row.takeFirst().data();

    recipe_names = new QStringListModel();
    ingredient_names =  new QStringListModel();
    user_recipes.push_back(name_of_recipe.toString()); //adding recipe to  user list
    recipe_names->setStringList(user_recipes);
    ui->list_user_recipes->setModel(recipe_names);
    QJsonObject whole_recipe = json_content.object().value(name_of_recipe.toString()).toObject();
    bool found_duplicate = false;
    QString index;

    for(auto itr = whole_recipe.begin(); itr != whole_recipe.end(); itr++)
    {
        if(user_ingredients.isEmpty() && itr.key() != "recipe")
        {
            QString first_name = itr.key() + " " + itr.value().toString();
            user_ingredients.push_back(first_name);
        }
        else if(itr.key() != "recipe") //we are only interested in ingredients, omit recipe description
        {
            QString name = itr.key();
            QString value = itr.value().toString().split(" ").at(0);
            QString unit = itr.value().toString().remove(0,value.length()+1);
            for(auto itr2 = user_ingredients.begin(); itr2 != user_ingredients.end(); ++itr2)
            {
                if(itr2->toCaseFolded().contains(name) && itr2->toCaseFolded().contains(unit)) // if in list there is already ingredient with that name and unit, set flag and preserve index
                {
                     found_duplicate = true;
                     index = itr2->toCaseFolded();
                     break;
                }
            }
            if(found_duplicate)
                duplicated_data(name, value, unit, index); //calculate new value of duplicated data
            else
            {
                name = itr.key() + " " + itr.value().toString(); //if ingredient was not present on list simply add it
                user_ingredients.push_back(name);
            }
            found_duplicate = false; //refresh flag
        }
    }
    ingredient_names->setStringList(user_ingredients);
    ui->list_ingredients->setModel(ingredient_names);
}

void RecipeManager::on_btn_delete_clicked()
{
    if(user_recipes.isEmpty()) // if list of recipes is empty there is nothing to be removed
        {
            QMessageBox::critical(this, "Error", "There are no elements to be deleted!");
            return;
        }
    QItemSelectionModel *user_selection = ui->list_user_recipes->selectionModel();
    QModelIndexList selected_row = user_selection->selectedRows();
    QVariant name_of_recipe;

    if(selected_row.size() > 1) //standard errors about picking wrong number of rows
    {
        QMessageBox::critical(this, "Error", "You can choose only one recipe at the time");
        return;
    }
    else if(selected_row.size() == 0)
    {
        QMessageBox::critical(this, "Error", "No recipe was selected");
        return;
    }
    recipe_names = new QStringListModel();
    ingredient_names =  new QStringListModel();
    name_of_recipe = selected_row.takeFirst().data();
    user_recipes.remove(user_recipes.indexOf(name_of_recipe));
    recipe_names->setStringList(user_recipes);
    ui->list_user_recipes->setModel(recipe_names);
    QJsonObject whole_recipe = json_content.object().value(name_of_recipe.toString()).toObject();
    QString index;

    for(auto itr = whole_recipe.begin(); itr != whole_recipe.end(); itr++)
    {
        if(itr.key() != "recipe") // omit recipe key while searching for ingredients
        {
            QString name = itr.key();
            QString value = itr.value().toString().split(" ").at(0);
            QString unit = itr.value().toString().remove(0,value.length()+1);
            for(auto itr2 = user_ingredients.begin(); itr2 != user_ingredients.end(); itr2++)
            {
                if(itr2->contains(name) && itr2->contains(unit) && !itr2->contains(value)) //if name and unit are the same but value is different calculate new value
                {
                    index = itr2->toCaseFolded();
                    removes_duplicated_data(name,value,unit,index);
                    break;
                }
                else if(itr2->contains(name) && itr2->contains(unit) && itr2->contains(value)) // if ingredient has the same name unit and quantity, simply remove from ingredient list
                {
                    index = itr2->toCaseFolded();
                    user_ingredients.remove(user_ingredients.indexOf(index));
                    user_ingredients.removeDuplicates();
                    break;
                }
            }
        }
    }
    while(user_recipes.isEmpty() && !user_ingredients.isEmpty())
            user_ingredients.pop_back();
    ingredient_names->setStringList(user_ingredients);
    ui->list_ingredients->setModel(ingredient_names);
}
void RecipeManager::fill_all_recipes() // fun used at the beginning to fill list with all recipes to enable user to add to his own list
{
    recipe_names = new QStringListModel();
    if(json_content.isObject())
    {
        QJsonObject recipes = json_content.object();
        QJsonObject::Iterator itr = recipes.begin();
        while(itr != recipes.end())
        {
            list_of_recipes.push_back(itr.key());
            itr++;
        }
    }
    recipe_names->setStringList(list_of_recipes);
    ui->list_all_recipes->setModel(recipe_names);
}
void RecipeManager::duplicated_data(QString name, QString value, QString unit, QString index) // fun. which set new value while adding the same ingredient to list
{
    QRegularExpression re("(\\d+(?:\\.\\d+))");
    double value_to_edited = re.match(index).captured().toDouble();
    value_to_edited += value.toDouble();
    if(QString::number(value_to_edited,'g',2).contains("."))
        name += " " + QString::number(value_to_edited,'g',2) + " " + unit;
    else
        name += " " + QString::number(value_to_edited,'g',2) + ".0 " + unit;
    user_ingredients.remove(user_ingredients.indexOf(index));
    user_ingredients.push_back(name);
}
void RecipeManager::removes_duplicated_data(QString name, QString value, QString unit, QString index) // fun. which set new value while removing the same ingredient from list
{
    QRegularExpression re("(\\d+(?:\\.\\d+))");
    double value_to_edited = re.match(index).captured().toDouble();
    value_to_edited -= value.toDouble();
    if(QString::number(value_to_edited,'g',2).contains("."))
        name += " " + QString::number(value_to_edited,'g',2) + " " + unit;
    else
        name += " " + QString::number(value_to_edited,'g',2) + ".0" + unit;
    user_ingredients.remove(user_ingredients.indexOf(index));
    user_ingredients.push_back(name);
}

void RecipeManager::on_btn_leave_clicked()
{
    this->hide();
}
