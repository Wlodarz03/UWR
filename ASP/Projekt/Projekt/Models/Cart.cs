using System.Collections.Generic;

namespace Projekt.Models
{
    public class Cart
    {
        public List<CartItem> Items { get; set; } = new List<CartItem>();

        public decimal TotalPrice => Items.Sum(item => item.Price * item.Quantity);
    }

    public class CartItem
    {
        public int ProductId { get; set; } // Id produktu
        public string Name { get; set; } // Nazwa produktu
        public decimal Price { get; set; } // Cena produktu
        public int Quantity { get; set; } // Ilość w koszyku
    }
}
