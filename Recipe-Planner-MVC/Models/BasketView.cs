using System.Collections.Generic;

namespace mvc.Models
{
    public class BasketView
    {
        public BasketView()
        {
            this.available_recipes = new List<Recipe>();
            this.user_choice_recipes = new List<Recipe>();
            this.user_choice_ingredient = new List<Ingredient>();
            //this.basket_ingredient = new Ingredient();
        }
        public List<Recipe> available_recipes { get; set; }
        public List<Recipe> user_choice_recipes { get; set; }
        public List<Ingredient> user_choice_ingredient { get; set; }
        //public Ingredient basket_ingredient { get; set; }
    }
}