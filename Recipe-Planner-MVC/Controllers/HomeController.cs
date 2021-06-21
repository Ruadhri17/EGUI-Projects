using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using mvc.Models;
using System.Text.Json;
using System.Globalization;
using System.IO;
using System.Threading;

namespace mvc.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        // static variables for communicating between view and model
        private static List<Recipe> list_of_recipes = new List<Recipe>();
        private static List<Ingredient> new_list_of_ingredients = new List<Ingredient>();
        private static List<Recipe> user_choice_list_of_recipes = new List<Recipe>();
        private static List<Ingredient> user_choice_list_of_ingredients = new List<Ingredient>();
        private static List<Recipe> basket_available_recipes = new List<Recipe>();
        private static String preserve_name;

        private static bool is_edited = false;
        public HomeController(ILogger<HomeController> logger)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.CreateSpecificCulture("en-US");
            _logger = logger;
        }

        public IActionResult MainMenu()
        {
            is_edited = false; // mode: either for edition or for adding new recipes
            if(list_of_recipes.Count() == 0) // if there is not recipes on list, try to load one 
                read_json_file();
            return View(list_of_recipes); 
        }
        public IActionResult RecipeText()
        {
            return View(new RecipeView());
        }
        public IActionResult BasketMenu()
        {
            user_choice_list_of_ingredients.Clear(); // clear both for user choice before opening basket menu
            user_choice_list_of_recipes.Clear();
            
            basket_available_recipes = list_of_recipes.ConvertAll(r => new Recipe(r)); // deep copy of all available recipes for user
            
            BasketView fill_basket = new BasketView() // all necessery list of recipes and ingredients for Basket View
            {
                available_recipes = basket_available_recipes.ConvertAll(r => new Recipe(r)),
                user_choice_recipes = user_choice_list_of_recipes.ConvertAll(r => new Recipe(r)),
                user_choice_ingredient = user_choice_list_of_ingredients.ConvertAll(i => new Ingredient(i))
            };
            return View(fill_basket);
        }
        public IActionResult RecipeIngredient()
        {
            list_of_recipes.Find(n => n.name.Contains(preserve_name)).list_of_ingredients = new List<Ingredient>(new_list_of_ingredients); // after finish adding all ingredients, add them to given recipe
            write_json_file(); // update json file
            new_list_of_ingredients.Clear(); // clear list for adding new ingredients
            preserve_name = ""; // clear preserved name
            return RedirectToAction("MainMenu");
        }
        [HttpPost]
        public IActionResult AddTextDesc(RecipeView text_and_description)
        {
            if(is_edited == true) // change between edit mode and add mode 
            {
                foreach(var recipe in list_of_recipes)
                {
                if(recipe.name.Trim().Equals(text_and_description.r_name.Trim()) && text_and_description.r_name.Trim() != preserve_name) // a message for user if he wants to add recipe with the same name
                {
                    ViewBag.message = "This Item already exists!";
                    return View("RecipeText", new RecipeView() {r_description = text_and_description.r_description});
                }
                }
                list_of_recipes.Find(n => n.name.Contains(preserve_name)).name =  text_and_description.r_name;
                preserve_name = text_and_description.r_name; // preserve name to be able to add ingredients to that recipe
                list_of_recipes.Find(n => n.name.Contains(preserve_name)).description.Clear();
                var edit_description = text_and_description.r_description.Split('\n'); // add description by each line 
                foreach (var line in edit_description)
                    list_of_recipes.Find(n => n.name.Contains(preserve_name)).description.Add(line);
                new_list_of_ingredients = list_of_recipes.Find(n => n.name.Contains(preserve_name)).list_of_ingredients; // beacuse we are in edition mode, copy list of ingredients
                var edit_ingredient_list = new IngredientView
                {
                    ingredients = new_list_of_ingredients
                };
                return View("RecipeIngredient", edit_ingredient_list); 
            }
            foreach(var recipe in list_of_recipes)
            {
                if(recipe.name.Trim().Equals(text_and_description.r_name.Trim())) // a message for user if he wants to add recipe with the same name
                {
                    ViewBag.message = "This Item already exists!";
                    return View("RecipeText", new RecipeView() {r_description = text_and_description.r_description});
                }
            }
            // here is similar approach like above but adding new recipe instead of editing 
            Recipe add_recipe = new Recipe();
            add_recipe.name = text_and_description.r_name;
            var separate_lines = text_and_description.r_description.Split('\n');
            foreach (var line in separate_lines)
                add_recipe.description.Add(line);
            list_of_recipes.Add(add_recipe);
            preserve_name = text_and_description.r_name;
            
            return View("RecipeIngredient", new IngredientView());       
        }
        [HttpPost]
        public IActionResult AddIngredient(IngredientView new_ingredient)
        {   
            foreach (var ingredient in new_list_of_ingredients)
                {
                    if(ingredient.name.Trim().Equals(new_ingredient.ingredient.name.Trim())) //a message for user if he wants to add ingredient with the same name
                    {
                        ViewBag.message = "This Item already exists!";
                        new_ingredient.ingredients = new_list_of_ingredients;
                        return View("RecipeIngredient", new_ingredient);
                    }
                }
            Ingredient add_ingredient = new Ingredient();

            add_ingredient.name = new_ingredient.ingredient.name;
            
            if(new_ingredient.quantity.Contains(",")) // input accepts both commas and dots as decimal point but change comma for dot when adding quantity of ingredient
                {
                new_ingredient.quantity = new_ingredient.quantity.Replace(',', '.');
                add_ingredient.quantity = Convert.ToDouble(new_ingredient.quantity);
                }
            else
                add_ingredient.quantity = Convert.ToDouble(new_ingredient.quantity);
            add_ingredient.unit = new_ingredient.ingredient.unit;
            
            new_list_of_ingredients.Add(add_ingredient);
            
            new_ingredient.ingredients = new_list_of_ingredients;

            return View("RecipeIngredient", new_ingredient);
        }
        public IActionResult DeleteRecipe(int id)
        {
            if(id > list_of_recipes.Count && id < 0) // if index number of recipe on the list is wrong, come back to main menu 
                return View("MainMenu");
            list_of_recipes.RemoveAt(id); // remove recipe with given index in table
            write_json_file();
            return RedirectToAction("MainMenu");
        }
        public IActionResult EditRecipe(int id)
        {
            if(id > list_of_recipes.Count && id < 0) // if index number of recipe on the list is wrong, come back to main menu 
                return View("MainMenu");
            RecipeView edit_recipe = new RecipeView  // send all data of edited recipe to View
            {
                r_name = list_of_recipes[id].name,
                r_description = string.Join('\n',list_of_recipes[id].description)
            };
            is_edited = true; // change mode for edition
            preserve_name = list_of_recipes[id].name;
            return View("RecipeText", edit_recipe);
        }
        public IActionResult DeleteIngredient(int id)
        {
            if(id < new_list_of_ingredients.Count && id >= 0) // if index number of ingredient on the list is wrong, come back to main menu 
                new_list_of_ingredients.RemoveAt(id); // remove ingredient with given index in table
            IngredientView delete_ingredient = new IngredientView
            {
                ingredients = new_list_of_ingredients
            };
            return View("RecipeIngredient", delete_ingredient);
        }
        public IActionResult AddToBasket(int id)
        {
            if(id < basket_available_recipes.Count && id >= 0)
            {
                bool added = false;
                basket_available_recipes = list_of_recipes.ConvertAll(r => new Recipe(r)); // refresh basket to prevent from changing quantity of ingredients
                user_choice_list_of_recipes.Add(new Recipe(basket_available_recipes[id]));
            
                for (int i = 0; i < basket_available_recipes[id].list_of_ingredients.Count; i++)
                {
                    for (int j = 0; j < user_choice_list_of_ingredients.Count; j++)
                    {   // check if name and quantity of ingredients are the same
                        if(user_choice_list_of_ingredients[j].name.Trim() == basket_available_recipes[id].list_of_ingredients[i].name.Trim() && user_choice_list_of_ingredients[j].unit.Trim() == basket_available_recipes[id].list_of_ingredients[i].unit.Trim()) 
                            {
                            user_choice_list_of_ingredients[j].quantity += basket_available_recipes[id].list_of_ingredients[i].quantity;
                            added = true; // if they are the same update quantity and set proper flag
                            break;
                            }
                    }
                    if(added == false)
                        user_choice_list_of_ingredients.Add(new Ingredient(basket_available_recipes[id].list_of_ingredients[i])); // if given ingredient does not exist on the list, simply add it
                    added = false; // restore flag
                }
            }
            BasketView add_to_basket = new BasketView() // send data to View 
            {
                available_recipes = basket_available_recipes.ConvertAll(r => new Recipe(r)),
                user_choice_recipes = user_choice_list_of_recipes.ConvertAll(r => new Recipe(r)),
                user_choice_ingredient = user_choice_list_of_ingredients.ConvertAll(i => new Ingredient(i))
            };
            return View("BasketMenu", add_to_basket);
        }
        public IActionResult DeleteFromBasket(int id) // similar approach like in AddToBasket 
        {
            if(id < user_choice_list_of_recipes.Count && id >= 0)
            {
            for (int i = 0; i < user_choice_list_of_recipes[id].list_of_ingredients.Count; i++)
            {
                for (int j = 0; j < user_choice_list_of_ingredients.Count; j++)
                {
                    if(user_choice_list_of_ingredients[j].name.Trim() == user_choice_list_of_recipes[id].list_of_ingredients[i].name.Trim() && user_choice_list_of_ingredients[j].unit.Trim() == user_choice_list_of_recipes[id].list_of_ingredients[i].unit.Trim())
                    {
                        user_choice_list_of_ingredients[j].quantity -= user_choice_list_of_recipes[id].list_of_ingredients[i].quantity;
                        if(user_choice_list_of_ingredients[j].quantity <= 0)
                            user_choice_list_of_ingredients.RemoveAt(j);
                    }
                }
            }
            user_choice_list_of_recipes.RemoveAt(id);
            }
            BasketView remove_from_basket = new BasketView()
            {
                available_recipes = list_of_recipes.ConvertAll(r => new Recipe(r)),
                user_choice_recipes = user_choice_list_of_recipes.ConvertAll(r => new Recipe(r)),
                user_choice_ingredient = user_choice_list_of_ingredients.ConvertAll(i => new Ingredient(i))
            };
            return View("BasketMenu", remove_from_basket);
        }
        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
        private void read_json_file()
        {   
        if(!System.IO.File.Exists("recipes.json")) // if json file does not exists, create new one
          {
            var file = System.IO.File.Create("recipes.json");
            file.Close();
          }
            if(System.IO.File.ReadAllText("recipes.json").Length == 0) // if json file is empty does not read it 
                return;
            string json_string = System.IO.File.ReadAllText("recipes.json"); // read all json to string and then parse it to JsonDocument 
            JsonDocument json_doc = JsonDocument.Parse(json_string);
            
            foreach(JsonProperty recipe in json_doc.RootElement.EnumerateObject()) // as our json file is not standard one, we need to use JsonProperty
            {
                Recipe add_recipe = new Recipe();
                add_recipe.name = recipe.Name;
                foreach(JsonProperty content in recipe.Value.EnumerateObject())
                {
                        if(content.Name != "recipe") // now we read only ingredients, omit recipe description 
                        {
                            Ingredient add_ingredient = new Ingredient();
                            add_ingredient.name = content.Name;
                            var quantity_and_unit = content.Value.ToString().Split(new[] { ' '}, 2); // split quantity and unit to separate variables 
                            add_ingredient.quantity = Convert.ToDouble(quantity_and_unit[0]);
                            add_ingredient.unit = quantity_and_unit[1];
                            add_recipe.list_of_ingredients.Add(add_ingredient);
                        }
                        else // read recipe description 
                            foreach(var line in content.Value.EnumerateArray()) // each line in description is single string 
                                add_recipe.description.Add(line.ToString());              
                }
                list_of_recipes.Add(add_recipe); // add to list all read recipes 
            }
        }
        private void write_json_file()
        {
            var option = new JsonWriterOptions
            {
                Indented = true // preserve all indents 
            };
            FileStream fs = new FileStream("recipes.json", FileMode.Truncate,FileAccess.ReadWrite, FileShare.ReadWrite);
            var write_to_json = new Utf8JsonWriter(fs, option); // write to json using UTF8JsonWriter 
                write_to_json.WriteStartObject();
                foreach(var recipe in list_of_recipes)
                {
                    write_to_json.WriteStartObject(recipe.name);
                
                    write_to_json.WriteStartArray("recipe"); // start writing description as JsonArray
                    recipe.description.ForEach(line => write_to_json.WriteStringValue(line));
                    write_to_json.WriteEndArray();
                    foreach(var ingredient in recipe.list_of_ingredients)
                    {
                        string quantity_string = ingredient.quantity.ToString();
                        if(quantity_string.Contains(","))
                            quantity_string = quantity_string.Replace(',','.'); // if double variable use , as decimal point, change it to .
                        write_to_json.WriteString(ingredient.name, quantity_string + " " + ingredient.unit); // marge quantity and unit 
                    }
                    write_to_json.WriteEndObject();
                }
                write_to_json.WriteEndObject();
                write_to_json.Flush();
                fs.Dispose(); // after finishing writing to Json, dispose file stream to let other function use that json
        }
    }
}
