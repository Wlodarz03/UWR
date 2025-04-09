using Projekt.Models;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace Projekt
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<Product> Products { get; set; }
        public DbSet<User> User { get; set; }
    }
}
