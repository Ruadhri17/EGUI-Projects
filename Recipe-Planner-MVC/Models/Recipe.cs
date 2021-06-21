using System;
using System.Collections.Generic;

namespace mvc.Models
{
    public class Recipe : ICloneable
    {
        public Recipe(Recipe copy) // copy constructor 
        {
            name = copy.name;
            description = new List<string>(copy.description);
            list_of_ingredients = copy.list_of_ingredients.ConvertAll(i => new Ingredient(i));
        }
        public object Clone() // cloning method for deep copy 
        {
            return new Recipe(this);
        }
        public Recipe()
        {
            this.list_of_ingredients = new List<Ingredient>();
            this.description = new List<string>();
        }
        public string name { get; set; }
        public List<string> description { get; set; }
        public List<Ingredient> list_of_ingredients { get; set; }
   }
}