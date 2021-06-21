using System;
namespace mvc.Models
{
    public class Ingredient : ICloneable
    {
        public Ingredient(Ingredient copy) // copy constructor 
        {
            name = copy.name;
            quantity = copy.quantity;
            unit = copy.unit;
        }
        public object Clone() // cloning method for deep copy 
        {
            return new Ingredient(this);
        }
        public Ingredient()
        {
            this.name = name;
            this.quantity = quantity;
            this.unit = unit;
        }
        public string name { get; set; }
        public double quantity { get; set; }
        public string unit { get; set; }
    }
}