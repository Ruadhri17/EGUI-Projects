using System.Collections.Generic;
namespace mvc.Models
{
    public class IngredientView
    {
        public IngredientView()
        {
            this.ingredients = new List<Ingredient>();
            this.ingredient = new Ingredient();
        }
        public Ingredient ingredient { get; set; }
        public List<Ingredient> ingredients { get; set; }
        public string quantity { get; set; }
    }
}